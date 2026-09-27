# =============================================================================
# CoreCombat.gd — 无头战斗内核：战斗驱动（主循环 / 时钟 / 疲劳 / 判胜 / 收尾）
# =============================================================================
# 对齐源码：
#   Core/Game.gd:2978-3032       switchToCombat（开战准备：洗牌 + 排序 + 延迟激活）
#   Core/Game.gd:3257-3262       prepareItems
#   Core/Game.gd:3264-3280       activateItems
#   Core/Game.gd:3282-3310       endCombat（判胜）
#   Core/Game.gd:3312-3377       combatEndDeferred（收尾）
#   Core/Game.gd:3379-3386       forceLoseCombat
#   Core/Character.gd:328-336    combatStart（TickTimer.start()）
#   Core/Character.gd:401-414    onTick（每 1s）
#   Core/Character.gd:1029-1035  _physics_process（体力再生 / 眩晕倒计时）
#   Items/Item.gd:4453-4458      _physics_process（冷却推进 → trigger）
#   Interface/CombatTimer/CombatTimer.gd  全部计时与疲劳（FATIGUE_TIME=17）
#
# ── 帧内次序（本内核的显式定义）────────────────────────────────────────────
# 原版所有 `_physics_process` 由 Godot 按节点树次序派发，节点树次序对判定并非
# 稳定契约（同一场战斗内固定，但跨版本/跨场景装配会变）。本内核把它显式固定为：
#   1. 物品冷却（ordered_items 次序，= 原版 activateItems 的入参次序）
#   2. 角色物理帧（玩家 → 对手）：体力再生 + 眩晕倒计时
#   3. 角色 onTick（TickTimer 1s 周期）
#   4. Buff 临时栈超时（原版为每个 Buff 自带的 Godot Timer）
#   5. 疲劳（CombatTimer）：疲劳计时 → 疲劳伤害
# 该次序与项目内已验证的 Python 引擎（engine/combat.py:_tick）逐条一致，
# 后者已通过 274/274 首触发校验与 56 场双引擎对照。
#
# ★ 原版一帧内**所有**节点的 `_physics_process` 都会跑完：判胜只把 `fightEnded`
#   置真，用来挡下 EventBus 派发（EventBus.emitAndLog 首行 return），并不会中断
#   本帧剩余节点的 tick。本内核照此实现：判胜后本帧不 return，收尾（combatEndDeferred）
#   按原版 `call_deferred` 语义延到帧末 flush。
#
# ── 时钟 ────────────────────────────────────────────────────────────────
#   ctx.combat_time —— 对齐 CombatTimer.combatTime（开战清零，事件时间戳来源）
#   ctx.time        —— 对齐 Util.time（全局物理帧累加，**跨场不清零**）。
#                      Buff 临时栈用绝对时间 `Util.time + duration` 记录到期点，
#                      Item 触发/激活同帧限流用它判「是否同一帧」。
#                      批量无头运行时若需模拟「游戏已运行一段时间」，
#                      可在开战前设置 ctx.time。
# =============================================================================
extends Reference
class_name CoreCombat


signal combat_start
signal combat_end(result)
signal round_result

# 对齐 Game.gd:124-129
enum RoundResult{
	Win, 
	Loss, 
	Draw, 
	RunOver
}

const FATIGUE_TIME := 17.0        # CombatTimer.gd:4
const FATIGUE_START_DELAY := 3.0  # startFatigue 里 fatigueTickTimer.start(3)
const FATIGUE_SLOW_TIME := 60.0   # combatTime < 60 用 0.1 增长，否则 0.2

var ctx
var player
var opponent

# 参战物品（对齐 prepareItems/activateItems 的入参 items 数组）
var ordered_items: Array = []

# 对齐 Game.roundResults[curRound - 1]
var result: int = -1
var fight_ended := false

# ── CombatTimer 状态 ──
var combat_time := 0.0
var fatigue_counter := 0
var fatigue_started := false
var fatigue_next_tick := 0.0
var fatigue_interval := 0.0
var time_advance := 0.0
var speed_scale := 1.0            # 对齐 Engine.time_scale（无头恒 1.0，不参与判定）

# ── 开战延迟（对齐 Util.callDelayed(self, "activateItems", COMBAT_DELAY)） ──
var _activate_countdown := 0.0
var activated := false

# ── 角色 TickTimer（Character.tscn 的 TickTimer：wait_time=1、循环） ──
var _tick_timer_left := 0.0
var _tick_timer_active := false

# 无头保护：超过该时长仍未分胜负则按超时结算（原版由疲劳必然收场）
var max_time := 180.0
var timed_out := false

# 对齐 Game.gd:3310 `call_deferred("combatEndDeferred")`：收尾延到帧末执行
var _pending_deferred := false


func _init(_ctx = null) -> void :
	ctx = _ctx


func setup(_player, _opponent) -> void :
	player = _player
	opponent = _opponent
	ctx.player = _player
	ctx.opponent = _opponent
	# 对齐 Game.combatTimer 的身份：物品脚本用
	# `connectForCombat(Game.combatTimer, "fatigue_start", ...)` 订阅疲劳信号，
	# 而信号正是由本对象用 self 发出的（EventBus 按 emitter.get_instance_id() 配对），
	# 故这里必须把 self 暴露成 ctx.combat。
	ctx.combat = self
	player.setOpponent(opponent)
	opponent.setOpponent(player)
	# 对齐 Game.gd:2549 / 2986：双方 character_died 都连到 endCombat
	player.clearCharacterDiedHandlers()
	opponent.clearCharacterDiedHandlers()
	player.registerCharacterDied(funcref(self, "endCombat"))
	opponent.registerCharacterDied(funcref(self, "endCombat"))


# ─────────────────────────── 开战（对齐 Game.gd:3002-3032） ───────────────────────────

func startBattle(player_items: Array, opponent_items: Array) -> void :
	ctx.fight_ended = false
	fight_ended = false
	result = -1
	timed_out = false
	activated = false
	_pending_deferred = false
	ctx.out_of_stamina_count = 0      # 对齐 Game.numTimesOutOfStamina = 0
	
	combat_time = 0.0
	ctx.combat_time = 0.0
	fatigue_counter = 0
	fatigue_started = false
	fatigue_interval = 0.0
	fatigue_next_tick = 0.0
	speed_scale = 1.0
	
	# 对齐 Game.gd:3011-3020：各自 duplicate() → shuffle() → 按 TriggerPriority 降序
	# （Godot 的 sort_custom 非稳定排序，并列优先级次序由洗牌决定）
	var p_items: Array = player_items.duplicate()
	ctx.rng.shuffle(p_items)
	p_items.sort_custom(CoreItemSort.new(), "sort_TriggerPriority")
	
	var o_items: Array = opponent_items.duplicate()
	ctx.rng.shuffle(o_items)
	o_items.sort_custom(CoreItemSort.new(), "sort_TriggerPriority")
	
	ordered_items = p_items + o_items
	
	# 对齐 Game.gd:3023：`call_deferred("prepareItems", ...)`
	# （deferred 在本帧末执行，仍在 2.5s 延迟之前，故此处同步调用等价）
	prepareItems(ordered_items)
	
	# 对齐 Game.gd:3024：COMBAT_DELAY 秒后 activateItems
	_activate_countdown = CoreContext.COMBAT_DELAY


# 对齐 Game.gd:3257-3262。原版在**商店/摆放阶段**就把物品放进 INVENTORY 了
# （Inventory.addItem → Item.addToInventory），到战斗开始时 Game.gd:3023 只是
#   call_deferred("prepareItems", 双方物品) → PLAYER.prepare / OPPONENT.prepare / 逐件 prepare。
# 本方法因此遵循两条不变式：
#   ① **不清空**背包——清空会连放置期已经建好的格子映射与受影响集一起抹掉；
#   ② **不重复登记**已 placed 的物品——重放 addItem 会二次 push 进 items 并重复触发
#      onItemAdded/onAffectedItemAdded，使受影响集里出现同一物品的两份。
# 需要「一场干净的新战斗」时由装配层显式调 resetInventories()。
func prepareItems(items: Array) -> void :
	for character in [player, opponent]:
		if character.inventory == null:
			character.inventory = CoreGrid.new(character)
	
	for item in items:
		if item.ctx == null:
			item.ctx = ctx
		if item.placed:
			continue          # 已在放置期登记过（Inventory.addItem 的等价路径）
		var ch = item.character()
		if ch != null and ch.inventory == null:
			ch.inventory = CoreGrid.new(ch)
		var grid = ch.inventory if ch != null else player.inventory
		grid.addItem(item, item.occupiedCells)
	
	player.prepare()
	opponent.prepare()
	
	for item in items:
		item.prepare()


# 装配层用具：显式把双方背包恢复为空场（物品需各自重新登记）。
# 原版没有对应方法——原版一场战斗结束后玩家重新摆放，背包由商店/背包 UI 重建。
func resetInventories() -> void :
	for character in [player, opponent]:
		if character.inventory != null:
			character.inventory.cleanUp()
		for item in character.items:
			item.placed = false
			item.consumed = false


# 对齐 Game.gd:3264-3280
func activateItems(items: Array) -> void :
	emit_signal("combat_start")
	
	# combatTimer.start()：combatTime 清零 + fatigueStartTimer.start(FATIGUE_TIME - 3)
	combat_time = 0.0
	ctx.combat_time = 0.0
	fatigue_next_tick = FATIGUE_TIME - FATIGUE_START_DELAY - time_advance
	fatigue_interval = 0.0
	fatigue_started = false
	
	player.combatStart()
	opponent.combatStart()
	
	# Character.combatStart 里的 tickTimer.start()（wait_time 1s，循环）
	_tick_timer_left = 1.0
	_tick_timer_active = true
	
	for item in items:
		item.preCombatStart()
	
	for item in items:
		item.combatStart()
	
	for item in items:
		item.postCombatStart()
	
	activated = true


# ─────────────────────────── 主循环（每物理帧 60Hz） ───────────────────────────

func physicsTick(delta: float) -> void :
	# Godot 的 call_deferred 在帧末统一 flush。判胜当帧由本函数末尾 flush；
	# 此分支兜底处理「外部在帧外触发判胜」的情形。
	if _pending_deferred:
		_flushDeferred()
		return
	
	if fight_ended:
		return
	
	# 0. 开战延迟：未激活前只推进时钟
	#    （对齐 Util.callDelayed 用 Timer 计时；该期间 combatTimer 尚未 start，
	#      combatTime 不增长，故事件时间戳仍从 0 开始）
	if not activated:
		_activate_countdown -= delta
		if _activate_countdown <= 0.0:
			activateItems(ordered_items)
		ctx.flushDeferred()
		return
	
	# 1. combatTimer._physics_process: combatTime += delta
	combat_time += delta
	
	# 2. Util 全局物理时钟（跨场不清零，见文件头说明）
	ctx.advancePhysicsFrame(delta)
	
	# 3. 物品冷却推进（Items/Item.gd:4453-4458 的 _physics_process）
	for item in ordered_items:
		item.physicsTick(delta)
	
	# 4. 角色物理帧（体力再生 + 眩晕倒计时）
	for character in [player, opponent]:
		character.physicsTick(delta)
	
	# 5. 角色 onTick（Character.tscn 的 TickTimer：wait_time 1s、循环）
	if _tick_timer_active:
		_tick_timer_left -= delta
		if _tick_timer_left <= 0.0:
			for character in [player, opponent]:
				character.onTick()
			_tick_timer_left += 1.0
	
	# 6. Buff 临时栈超时（原版为每个 Buff 的 Godot Timer）
	for character in [player, opponent]:
		character.tickBuffs(delta)
	
	# 7. 疲劳（CombatTimer）
	_fatigueTick()
	
	# 8. 无头保护：超时按原版 forceLoseCombat 语义（超时判负）
	if not fight_ended and combat_time > max_time:
		timed_out = true
		forceLoseCombat()
	
	# 帧末 flush（对齐 call_deferred）
	if _pending_deferred:
		_flushDeferred()
	
	# 帧末 flush 延迟调用队列（Character.changeBaseMaxStamina 等）
	ctx.flushDeferred()


func run() -> void :
	while not fight_ended:
		physicsTick(CoreContext.PHYSICS_DELTA)


# ─────────────────────────── 疲劳（对齐 CombatTimer.gd） ───────────────────────────

func _fatigueTick() -> void :
	fatigue_next_tick -= CoreContext.PHYSICS_DELTA
	if fatigue_next_tick > 0:
		return
	
	if not fatigue_started:
		startFatigue()
	else:
		dealFatigueDamage()
	
	fatigue_next_tick = fatigue_interval


# 对齐 CombatTimer.gd:145-151（注意：原版 startFatigue **不**发 fatigue_start 信号，
# 该信号在 dealFatigueDamage 首次执行时发出）
func startFatigue() -> void :
	ctx.hooks.playFatigueAnimation("Start")
	
	fatigue_started = true
	fatigue_counter = 0
	fatigue_interval = FATIGUE_START_DELAY


# 对齐 CombatTimer.gd:153-179
func dealFatigueDamage() -> void :
	if fatigue_counter == 0:
		ctx.hooks.playFatigueSound()
		ctx.bus.emitSignal(self, "fatigue_start")
	
	if combat_time < FATIGUE_SLOW_TIME:
		fatigue_counter += 1 + int(floor(0.1 * fatigue_counter))
	else:
		fatigue_counter += 1 + int(floor(0.2 * fatigue_counter))
	
	ctx.fatigueDamageSource.setDamage(fatigue_counter)
	
	ctx.bus.emitSignal(self, "fatigue_damage_changed")
	
	# 原版顺序：先 OPPONENT 后 PLAYER（CombatTimer.gd:167-168）
	opponent.takeFatigueDamage()
	player.takeFatigueDamage()
	ctx.hooks.playFatigueAnimation("Tick")
	
	fatigue_interval = 1.0


func hasFatigueStarted() -> bool:
	return fatigue_counter > 0


# 对齐 CombatTimer.gd:184-196（advanceTime：把疲劳起点提前）
func advanceTime(_time: float) -> void :
	time_advance += _time
	
	var time_left = fatigue_next_tick
	var new_time = time_left - _time
	if new_time > 0:
		fatigue_next_tick = new_time
	else:
		# fatigueStartTimer.stop() → startFatigue()（其内部把 TickTimer 起为 3s）
		startFatigue()
		fatigue_next_tick = fatigue_interval


# 对齐 CombatTimer.gd:78-79
func getEffectiveTime() -> float:
	return CoreContext.COMBAT_DELAY + combat_time + time_advance


# ─────────────────────────── 判胜 / 收尾 ───────────────────────────

# 对齐 Game.gd:3282-3310
# ★ 由 Character.death() → "character_died" 信号在**伤害链中途**同步调用，
#   因此 fightEnded 在死亡那一刻即为 true（后续 EventBus 派发被挡下），
#   而收尾动作（combatEndDeferred）原版是 call_deferred 到帧末执行。
func endCombat() -> void :
	if fight_ended:
		return
	
	fight_ended = true
	ctx.fight_ended = true
	
	# 对齐 Game.gd:3290-3291：`OPPONENT.curHealth <= 0` → 玩家胜（双方同帧死亦为玩家胜）
	if opponent.curHealth <= 0:
		result = RoundResult.Win
	else:
		result = RoundResult.Loss
	
	_pending_deferred = true


# 对齐 Game.gd:3379-3386
func forceLoseCombat() -> void :
	if fight_ended:
		return
	fight_ended = true
	ctx.fight_ended = true
	result = RoundResult.Loss
	_pending_deferred = true


func _flushDeferred() -> void :
	_pending_deferred = false
	combatEndDeferred()


# 对齐 Game.gd:3312-3328（剥离：信号 emit 之外的 UI/成就/存档/音效/BGM）
func combatEndDeferred() -> void :
	emit_signal("combat_end", result)
	emit_signal("round_result")
	
	# 对齐 Game.gd:3315-3318
	ctx.bus.disconnectAll()
	player.combatEnd()
	opponent.combatEnd()
	_tick_timer_active = false
	_tick_timer_left = 0.0
	ctx.hooks.playFatigueAnimation("Hide")     # CombatTimer.gd:103/107
	ctx.fatigueDamageSource.setDamage(0)       # CombatTimer.gd:102
	
	# 对齐 Game.gd:3320-3325：败者血量归 0，胜者至少 1
	if result == RoundResult.Win:
		opponent.setCurrentHealth(0)
		player.setCurrentHealth(max(1, player.getCurrentHealth()))
	else:
		player.setCurrentHealth(0)
		opponent.setCurrentHealth(max(1, opponent.getCurrentHealth()))
	
	# 对齐 Game.gd:3327-3328
	for item in ordered_items:
		item.combatEnd()

	# ★ 对齐 Game.gd:3330-3332 —— 战斗收尾必须清空的**跨回合残留状态**。
	#   此前内核在 item.combatEnd() 之后直接结束，漏了这三行，构成一类**静默跨回合
	#   漂移**（单场测试全绿，连打多场才现形）：
	#   · ropeSpeedups / cubeAdvanced 不清 → 第二场里 Rope 读到的「已加速量」是上一场
	#     的残值，直接顶穿 maxSpeed 上限；方块读到的「已推进过」也是上一场的物品，
	#     而物品实例已换，penaltyFactor 判定随之走偏。
	#   · sandbagActive 不清 → 若上一场在沙袋 buff 生效中途结束（buffEnded 未被调用，
	#     Sandbag.gd:25 的置 false 就没机会执行），下一场 Sandbag.onPreCombatStart 会
	#     走 `elif buffsActive > 0` 分支而**不再施加** changeDamageResistance(damReduction)。
	#   原版靠这里兜底，故必须同位置同序补齐。
	ctx.rope_speedups.clear()
	ctx.cube_advanced.clear()
	ctx.sandbag_active = false


func playerWins() -> bool:
	return result == RoundResult.Win


func winner():
	if result == RoundResult.Win:
		return player
	elif result == RoundResult.Loss:
		return opponent
	return null


# ─────────────────────────── 排序器（对齐 Game.gd:6097-6098 ItemSort） ───────────────────────────

class CoreItemSort extends Reference:
	func sort_TriggerPriority(item1, item2) -> bool:
		return item1.getTriggerPriority() > item2.getTriggerPriority()
