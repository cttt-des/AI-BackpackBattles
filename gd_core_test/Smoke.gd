# =============================================================================
# Smoke.gd — gd_core 无头内核 smoke test（Godot 3.6 宿主，SceneTree 主循环）
# =============================================================================
# 目的：在没有场景树 / 渲染 / 音频 / 单例的前提下，让 gd_core 跑完整场战斗，
#       并对照「engine_truth.md」的核心契约做断言。
#
# 覆盖的契约：
#   1. 冷却驱动：首击时刻 ∈ [cd×0.95, cd×1.05]（原版 adjustCooldown 抖动，见下）
#   2. 开战延迟：COMBAT_DELAY=2.5s 后才 activateItems，事件时间戳从 0 起算
#   3. 疲劳时序：FATIGUE_TIME=17，首次疲劳伤害落在 17.0s，之后每 1s
#   4. 判胜：`OPPONENT.curHealth <= 0 → Win`，双方同帧死亦为玩家胜
#   5. 收尾：败者 HP 归 0，胜者至少 1
#   6. 确定性：同种子 + 新建上下文 → 结果、结束时刻、末态 HP 完全一致
#
# 运行：
#   Godot_v3.6-stable_win64.exe --no-window --path gd_core_test --script Smoke.gd
# =============================================================================
extends SceneTree


# ── 假武器行为：逐字对应 Items/Weapon.gd（基类） ──
# doCooldownEffect(): if useStamina() == Sufficient: attack()
# attack():           var res = dealDamage(); activate(res)
class WeaponBehavior extends Reference:
	
	func hasBehavior(item, methodName: String) -> bool:
		return methodName == "doCooldownEffect"
	
	func callBehavior(item, methodName: String, args: Array):
		match methodName:
			"doCooldownEffect":
				doCooldownEffect(item)
	
	func doCooldownEffect(item) -> void:
		if item.useStamina() == CoreCharacter.StaminaResult.Sufficient:
			attack(item)
	
	func attack(item) -> void:
		var res = item.dealDamage()
		item.activate(res)


# ── 记录用钩子：CoreHooks 默认全空实现，这里只接事件流做时间戳取证 ──
class TestHooks extends CoreHooks:
	
	var first_damage_time := -1.0
	var first_crit_time := -1.0
	var events := 0
	
	func logEvent(event) -> void:
		events += 1
		if event.type == CoreConst.EventType.DealDamage:
			if first_damage_time < 0.0:
				first_damage_time = event.timestamp
		elif event.type == CoreConst.EventType.CriticalDamage:
			if first_crit_time < 0.0:
				first_crit_time = event.timestamp


const STEP := 1.0 / 60.0
const MAX_STEPS := 60 * 200      # 200 秒上限

var _weapon = WeaponBehavior.new()
var failures: Array = []
# Godot 的 win64 release 版无控制台，stdout 拿不到；报告同时落盘到 res://smoke_result.txt
var _report: Array = []


func say(line: String) -> void:
	print(line)
	_report.push_back(line)
	# 逐行刷盘：万一某场战斗卡住，也能看到卡在哪一步
	var fh = File.new()
	if fh.open("res://smoke_result.txt", File.WRITE) == OK:
		fh.store_string(PoolStringArray(_report).join("\n") + "\n")
		fh.close()


func _init() -> void:
	say("")
	say("=== gd_core smoke test ===")
	print("SMOKE: start")
	test_basic_combat()
	print("SMOKE: test1 done")
	test_fatigue_contract()
	print("SMOKE: test2 done")
	test_determinism()
	print("SMOKE: test3 done")
	test_timer_contract()
	print("SMOKE: test4 done")
	
	say("")
	if failures.empty():
		say("SMOKE: PASS")
	else:
		for f in failures:
			say("SMOKE: FAIL  " + f)
		say("SMOKE: FAIL (%d 项)" % failures.size())
	
	quit(0 if failures.empty() else 1)


func check(cond: bool, what: String) -> void:
	if not cond:
		failures.push_back(what)


func check_near(value: float, expect: float, tol: float, what: String) -> void:
	check(abs(value - expect) <= tol, "%s（实际 %s，期望 %s ±%s）" % [
		what, str(stepify(value, 0.001)), str(expect), str(tol)])


# ─────────────────────────── 装配辅助 ───────────────────────────

func new_character(ctx, pid: int, hp: int, max_stamina: float, regen: float) -> CoreCharacter:
	var c = CoreCharacter.new(ctx, pid)
	c.setMaxHealth(hp)
	c.setCurrentHealth(hp)
	c.maxStamina = max_stamina
	c.baseMaxStamina = max_stamina
	c.baseStaminaRegen = regen
	# 对齐 Character.gd:357（cleanse()）—— 战斗不自行补满体力，属装配层职责
	c.fillUpStamina()
	return c


func new_weapon(ctx, character, item_name: String, mind: int, maxd: int, cd: float) -> CoreItem:
	var data = {
		"name": item_name,
		"minDam": mind,
		"maxDam": maxd,
		"cd": cd,
		"staminaCost": 0.0,
		"accuracy": 100.0,
		"block": 0,
		"types": [CoreConst.Type.Weapon, CoreConst.Type.Melee],
	}
	var it = CoreItem.new(ctx, CoreItemData.new().fromDict(data), character)
	it._behavior = _weapon
	it.buildDamageSource()          # 对齐 Items/Weapon.gd:4-5
	return it


# 对齐 Game.gd:3011-3024 + CoreCombat 主循环
func run_battle(ctx, player_hp: int, opponent_hp: int, 
		p_weapons: int, o_weapons: int, dmg: int, cd: float) -> CoreCombat:
	
	var p = new_character(ctx, CoreCharacter.ID.PLAYER, player_hp, 50.0, 20.0)
	var o = new_character(ctx, CoreCharacter.ID.OPPONENT, opponent_hp, 50.0, 20.0)
	
	var p_items: Array = []
	for i in p_weapons:
		p_items.push_back(new_weapon(ctx, p, "TestSword", dmg, dmg, cd))
	var o_items: Array = []
	for i in o_weapons:
		o_items.push_back(new_weapon(ctx, o, "TestSword", dmg, dmg, cd))
	
	var combat = CoreCombat.new(ctx)
	combat.setup(p, o)
	combat.startBattle(p_items, o_items)
	
	var steps := 0
	while not combat.fight_ended and steps < MAX_STEPS:
		combat.physicsTick(STEP)
		steps += 1
	return combat


# ─────────────────────────── 1. 基础对拼 ───────────────────────────

func test_basic_combat() -> void:
	say("")
	say("[1] 基础对拼：玩家 2 武器(5dmg/1.0cd) HP100  vs  对手 1 武器 HP20")
	
	var hooks = TestHooks.new()
	var ctx = CoreContext.new(20260922, hooks)
	var combat = run_battle(ctx, 100, 20, 2, 1, 5, 1.0)
	
	say("    fight_ended=%s  result=%d  用时=%.2fs  events=%d  首击=%.3fs" % [
		str(combat.fight_ended), combat.result, combat.combat_time, 
		hooks.events, hooks.first_damage_time])
	say("    HP  player=%.1f  opponent=%.1f" % [
		combat.player.curHealth, combat.opponent.curHealth])
	
	check(combat.fight_ended, "战斗应结束")
	check(not combat.timed_out, "战斗不应超时")
	check(combat.result == CoreCombat.RoundResult.Win, "对手先倒 → 玩家胜")
	check(combat.opponent.curHealth == 0, "败者 HP 应为 0")
	check(combat.player.curHealth >= 1, "胜者 HP 应至少为 1")
	# 冷却契约：gd_core 取「引擎真值」——原版 Item.gd:3805-3812 的 adjustCooldown
	# 对玩家物品为 cd × randf_range(0.95, 1.05)，故首击 ∈ [0.95, 1.05]×cd。
	# （注意：simulator/ 按用户确认的游戏实际体感取固定 cd；gd_core 对齐 engine/，
	#   即原版代码真值，此处不断言「== cd」。容差另加 1 帧量化。）
	check(hooks.first_damage_time >= 0.95 - 0.02 and hooks.first_damage_time <= 1.05 + 0.02, 
			"首击时刻应在 cd×[0.95,1.05]（实际 %s）" % str(stepify(hooks.first_damage_time, 0.001)))
	# 玩家 2 武器 × 5 = 10/s，对手 20HP → 需 2 轮齐射。每轮间隔同样是抖动后的 cd，
	# 故结束时刻 ∈ 2×[0.95,1.05] = [1.90, 2.10]。
	check(combat.combat_time >= 1.90 - 0.02 and combat.combat_time <= 2.10 + 0.02, 
			"结束时刻应在 2×cd×[0.95,1.05]（实际 %s）" % str(stepify(combat.combat_time, 0.001)))
	# 伤害链交叉验证：对手 5dmg/1.0cd，t=1 必中；t=2 是否命中取决于同帧内
	# ordered_items 的洗牌次序（玩家武器可能先手击杀并挡下对手该帧攻击）
	# → 玩家掉血 5 或 10，末态 HP 应为 95 或 90。
	check(combat.player.curHealth >= 90.0 and combat.player.curHealth <= 95.0, 
			"玩家末态 HP 应在 [90, 95]（实际 %s）" % str(combat.player.curHealth))


# ─────────────────────────── 2. 疲劳契约 ───────────────────────────

func test_fatigue_contract() -> void:
	say("")
	say("[2] 疲劳契约：双方空手 HP30，靠疲劳收场")
	
	var hooks = TestHooks.new()
	var ctx = CoreContext.new(777, hooks)
	var combat = run_battle(ctx, 30, 30, 0, 0, 0, 1.0)
	
	say("    fight_ended=%s  result=%d  用时=%.2fs  fatigue_counter=%d" % [
		str(combat.fight_ended), combat.result, combat.combat_time, 
		combat.fatigue_counter])
	say("    HP  player=%.1f  opponent=%.1f" % [
		combat.player.curHealth, combat.opponent.curHealth])
	
	check(combat.fight_ended, "战斗应结束（疲劳必然收场）")
	check(not combat.timed_out, "不应走到 max_time 兜底")
	check(combat.hasFatigueStarted(), "疲劳应已启动")
	# 双方同帧死 → 依契约判玩家胜
	check(combat.result == CoreCombat.RoundResult.Win, "双方同帧死 → 玩家胜")
	check(combat.opponent.curHealth == 0, "败者 HP 应为 0")
	# 疲劳递增序列 1,2,3,4,5,6,7,8 累计 36 > 30 → 第 8 次(24s)分胜负
	check_near(combat.combat_time, 24.0, 0.1, "疲劳收场时刻")


# ─────────────────────────── 3. 确定性 ───────────────────────────

func test_determinism() -> void:
	say("")
	say("[3] 确定性：同种子 + 独立上下文，两次对战逐位一致")
	
	var a = _snapshot(run_battle(CoreContext.new(424242, TestHooks.new()), 
		60, 60, 2, 2, 3, 0.8))
	var b = _snapshot(run_battle(CoreContext.new(424242, TestHooks.new()), 
		60, 60, 2, 2, 3, 0.8))
	
	say("    run A = " + a)
	say("    run B = " + b)
	check(a == b, "同种子的两场对战结果应完全一致")


func _snapshot(combat) -> String:
	return "%d|%.4f|%.1f|%.1f|%d" % [
		combat.result, combat.combat_time, 
		combat.player.curHealth, combat.opponent.curHealth, 
		combat.fatigue_counter]


# ─────────────────────────── 4. 计时器契约 ───────────────────────────
# 动机：原版这三个计时器是 Character.tscn 里的 Godot Timer 节点，由信号连接驱动：
#   InvulnerabilityTimer.timeout → invulnerabilityEnded()
#   BattleRageTimer.timeout      → endBattleRage()
#   AutoRageTimer.timeout        → startAutoRage()
# 内核把它们改成物理帧步进。一旦步进漏写（曾如此：_invul_left 只写不推进，
# 无敌永不结束）战斗结果会静默跑偏，故必须锁住「超时点触发 + 延长语义」。

func test_timer_contract() -> void:
	say("")
	say("[4] 计时器契约：无敌 / 战怒 / 自动战怒（Godot Timer → 物理帧步进）")
	
	var ctx = CoreContext.new(777, null)
	var p = new_character(ctx, CoreCharacter.ID.PLAYER, 100, 50.0, 20.0)
	var o = new_character(ctx, CoreCharacter.ID.OPPONENT, 100, 50.0, 20.0)
	var combat = CoreCombat.new(ctx)
	combat.setup(p, o)
	combat.prepareItems([])
	combat.activateItems([])
	
	# ① 无敌按时结束（对齐 invulnerabilityTimer.start(invuDur) → timeout）
	p.makeInvulnerable(0.5, null)
	check(p.invulnerable, "makeInvulnerable 后应处于无敌")
	_tick(p, 0.4)
	check(p.invulnerable, "0.4s 时仍应无敌（0.5s 未到）")
	_tick(p, 0.2)
	check(not p.invulnerable, "0.6s 后无敌应结束")
	
	# ② 已无敌时再触发 = 延长而非覆盖（对齐 Util.changeTimer：start(t + timeLeft)）
	p.makeInvulnerable(0.5, null)
	_tick(p, 0.3)
	p.makeInvulnerable(0.5, null)
	check(p.invulnerable, "延长后应仍无敌")
	_tick(p, 0.6)
	check(p.invulnerable, "0.3+0.5 延长后 0.9s 时仍应无敌（总 1.0s）")
	_tick(p, 0.2)
	check(not p.invulnerable, "超过总时长后无敌应结束")
	
	# ③ 战怒按时结束（对齐 battleRageTimer.start(fullDur) → timeout）
	check(not p.isBattleRaging(), "初始不应处于战怒")
	p.startBattleRage(null, 0.5)
	check(p.isBattleRaging(), "startBattleRage 后应处于战怒")
	_tick(p, 0.4)
	check(p.isBattleRaging(), "0.4s 时仍在战怒")
	_tick(p, 0.2)
	check(not p.isBattleRaging(), "0.6s 后战怒应结束")
	
	# ④ applyBonus：默认吃到 battleRageBonusDur，传 false 时不吃
	p.battleRageBonusDur = 0.5
	p.startBattleRage(null, 0.2)
	check_near(p._rage_left, 0.7, 1e-6, "applyBonus 默认 true 应叠加 battleRageBonusDur")
	_tick(p, 1.0)
	p.startBattleRage(null, 0.2, null, false)
	check_near(p._rage_left, 0.2, 1e-6, "applyBonus=false 不应叠加")
	_tick(p, 0.3)
	
	# ⑤ 已战怒时再触发 = 延长
	p.battleRageBonusDur = 0.0
	p.startBattleRage(null, 1.0)
	_tick(p, 0.4)
	p.startBattleRage(null, 1.0, null, false)
	check_near(p._rage_left, 1.6, 0.02, "已战怒时再触发应为延长（1.0-0.4+1.0）")
	
	test_auto_rage()


# ⑥ 自动战怒全链：prepare 选品 → combatStart 起 AUTO_RAGE_DELAY → 超时自动开大
func test_auto_rage() -> void:
	var ctx = CoreContext.new(31337, null)
	var p = new_character(ctx, CoreCharacter.ID.PLAYER, 100, 50.0, 20.0)
	var o = new_character(ctx, CoreCharacter.ID.OPPONENT, 100, 50.0, 20.0)
	
	# hasBattleRageEffect=true 的物品（对齐 ItemBook.gd:1401 由描述 "$rage[" 推出的标记）
	var data = {
		"name": "AngryRock",
		"cd": 1.0,
		"accuracy": 100.0,
		"types": [CoreConst.Type.Accessory],
		"hasBattleRageEffect": true,
	}
	var item = CoreItem.new(ctx, CoreItemData.new().fromDict(data), p)
	item.occupiedCells = [Vector2(0, 0)]
	item.collisionCells = [Vector2(0, 0)]
	p.inventory.addItem(item, item.occupiedCells)
	check(item.isBattleRageItem(), "isBattleRageItem 应读 descriptor.hasBattleRageEffect")
	
	var combat = CoreCombat.new(ctx)
	combat.setup(p, o)
	combat.prepareItems([])      # → p.prepare()：挑 autoRageItem
	check(p.autoRageItem == item, "prepare 应把该物品选为 autoRageItem")
	
	combat.activateItems([])     # → p.combatStart()：起 AutoRageTimer
	check(not p.isBattleRaging(), "自动战怒延迟期间不应已处于战怒")
	_tick(p, CoreCharacter.AUTO_RAGE_DELAY - 0.5)
	check(not p.isBattleRaging(), "AUTO_RAGE_DELAY 未到不应开大")
	_tick(p, 1.0)
	check(p.isBattleRaging(), "AUTO_RAGE_DELAY 到点应自动开大")
	_tick(p, CoreCharacter.AUTO_RAGE_DUR + 0.5)
	check(not p.isBattleRaging(), "AUTO_RAGE_DUR 到点应结束")
	say("    AUTO_RAGE_DELAY=%.1fs  AUTO_RAGE_DUR=%.1fs" 
		% [CoreCharacter.AUTO_RAGE_DELAY, CoreCharacter.AUTO_RAGE_DUR])


func _tick(c, seconds: float) -> void:
	var n = int(round(seconds / STEP))
	for i in n:
		c.physicsTick(STEP)
