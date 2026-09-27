# =============================================================================
# GemFacade.gd — gd_core 宝石 / Socket 门面契约测试（Godot 3.6 宿主）
# =============================================================================
# 原版宝石走的是**场景树插座**：`sockets: Array = $Icon/Sockets.get_children()`
# （Item.gd:309），`setGem` 最终落到 `gem.addToSocket(sockets[id])`，而宝石自己的
# 每一个身份判定（isOwnable / isPlaced / getInventory / getEffectiveOwnerType …）
# 又都回到 `socket.getItem()`（Gem.gd:36-76）。
#
# 内核无节点树，把「插座」这个身份整体**折叠为宿主物品本身**：
#   `CoreItem.setGem` 把 self 当 socket 交给宝石，`CoreItem.getItem()` 恒返回 self。
# 这条折叠是全宝石行为的地基。它接错不会报错 —— 宝石照样「安静地」跑完一整场，
# 只是不再产生任何效果。故参照 FacadeSmoke 的做法，单独验契约：
#
#   1. 折叠等价性     socket.getItem() 一族必须逐条等于宿主同名方法
#   2. getGemMode     四分支（Weapon/Armor/Inventory/Inactive）+ hasCooldown 口径
#   3. Weapon 模式    宿主 attacked 命中 → heal(ceil(伤害 × lifesteal_weapon%))
#   4. Armor 模式     prepareArmor → 角色治疗效率 +gemPower × P2%
#   5. Inventory 模式 走宝石自身冷却（hasCooldown 为真，doCooldownEffect 生效）
#
# ★ 为什么这里能给出**公式级**断言，而 LineupBattle 只给「有效果」：
#   本闸门用合成数值（伤害 100/57、lifesteal_weapon 7），每一步都在控；真实对局里
#   伤害受 buff/暴击影响，只适合断言方向与存在性。两者互补，缺一不可。
#
# ★ 用**真实转译产物**做被测对象（gd_core_items/Item.gd 适配层 + Gems/Ruby.gd），
#   只有描述符是合成的 —— 验的是「脚本读到的数值与分派对不对」，不是造一个假宝石。
#
# 运行：
#   Godot_v3.6-stable_win64.exe --no-window --path gd_core_test --script GemFacade.gd
# =============================================================================
extends SceneTree


# 探针：只数「只可能由宝石判定路径触发」的钩子。
class GemProbe extends CoreHooks:
	var heals := 0              # 治疗飘字（EventType.Health）总数
	var gem_heals := 0          # 其中起源是宝石的（CoreItem.heal 把 self 传成 origin）
	var gem_heal_sum := 0.0
	var gem_mini := 0           # 宝石的 miniActivate 动画（Ruby.onAttack 每命中一次一跳）

	func spawnLabel_character(_character, type, damage, item = null) -> void :
		if type == CoreConst.EventType.Health:
			heals += 1
			if item != null and item is CoreItem and item.isGem():
				gem_heals += 1
				gem_heal_sum += abs(float(damage))

	func playActivationAnimation(item, aniType, _consume: bool) -> void :
		if aniType == "MiniActivate" and item != null and item is CoreItem and item.isGem():
			gem_mini += 1


const NUM_PARAMS := 10
const ZERO_PARAMS := [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]

var failures: Array = []
var _report: Array = []

var _probe
var _ctx
var _p
var _o
var _combat
var _base_script
var _ruby_script


func say(line: String) -> void:
	print(line)
	_report.push_back(line)
	var fh = File.new()
	if fh.open("res://gem_result.txt", File.WRITE) == OK:
		fh.store_string(PoolStringArray(_report).join("\n") + "\n")
		fh.close()


func check(cond: bool, what: String) -> void:
	if not cond:
		failures.push_back(what)


func _init() -> void:
	say("")
	say("=== gd_core 宝石 / Socket 门面契约测试 ===")
	print("GEM: start")

	_base_script = load("res://gd_core_items/Item.gd")
	_ruby_script = load("res://gd_core_items/Gems/Ruby.gd")
	check(_base_script != null, "适配层 gd_core_items/Item.gd 应可加载")
	check(_ruby_script != null, "gd_core_items/Gems/Ruby.gd 应可加载")
	if _base_script == null or _ruby_script == null:
		say("GEM: FAIL (脚本加载失败)")
		quit(1)
		return

	test_socket_fold()
	print("GEM: test1 done")
	test_gem_mode_dispatch()
	print("GEM: test2 done")
	test_weapon_mode_effect()
	print("GEM: test3 done")
	test_armor_mode_effect()
	print("GEM: test4 done")
	test_inventory_mode_effect()
	print("GEM: test5 done")

	say("")
	if failures.empty():
		say("GEM: PASS")
	else:
		for f in failures:
			say("GEM: FAIL  " + f)
		say("GEM: FAIL (%d 项)" % failures.size())

	quit(0 if failures.empty() else 1)


# ─────────────────────────── 装配辅助 ───────────────────────────

func new_world(seed_value: int) -> void:
	_probe = GemProbe.new()
	_ctx = CoreContext.new(seed_value, _probe)
	_p = mk_char(CoreCharacter.ID.PLAYER, 200)
	_o = mk_char(CoreCharacter.ID.OPPONENT, 200)
	_combat = CoreCombat.new(_ctx)
	_combat.setup(_p, _o)


func mk_char(pid: int, hp: int) -> CoreCharacter:
	var c = CoreCharacter.new(_ctx, pid)
	c.setMaxHealth(hp)
	c.setCurrentHealth(hp)
	c.maxStamina = 50.0
	c.baseMaxStamina = 50.0
	c.fillUpStamina()
	return c


# 被测对象一律用**真实转译产物**：适配层 Item.gd（502 个物品脚本的直接基类）
func mk_host(descr, chr) -> CoreItem:
	var it = _base_script.new()
	it.setup(_ctx, descr, chr)
	return it


func mk_gem() -> CoreItem:
	var g = _ruby_script.new()
	g.setup(_ctx, ruby_descr(), _p)
	return g


# 插座数由场景决定（原版 `$Icon/Sockets.get_children()`），内核里由装配层给出：
# `gems` 数组先按插座数补齐，再 setGem（对齐原版「先摆宿主、再 setGemData」）
func attach(host, gem, socket_id: int, sockets: int) -> void:
	while host.gems.size() < sockets:
		host.gems.push_back(null)
	host.setGem(socket_id, gem)


func place(item, x: int, y: int) -> void:
	_p.inventory.addItem(item, [Vector2(x, y)])


func weapon_descr():
	return CoreItemData.new().fromDict({
		"name": "Probe Weapon", "identifier": "Probe Weapon",
		"minDam": 4, "maxDam": 7, "cd": 2.8, "accuracy": 100.0,
		"types": [CoreConst.Type.Weapon, CoreConst.Type.Melee],
		"params": ZERO_PARAMS,
	})


func armor_descr():
	return CoreItemData.new().fromDict({
		"name": "Probe Armor", "identifier": "Probe Armor",
		"block": 0, "cd": 0.0,
		"types": [CoreConst.Type.Armor],
		"params": ZERO_PARAMS,
	})


# Chipped Ruby 的真实数值（battle_items.json）：
# p1=lifesteal_weapon=7, p2=healamp=10, p3=flatsteal=4, lifesteal_factor=150
func ruby_descr():
	return CoreItemData.new().fromDict({
		"name": "Probe Ruby", "identifier": "Probe Ruby",
		"cd": 5.0, "canActivate": true,
		"types": [CoreConst.Type.Gem],
		"params": [7, 10, 4, 150, 0, 0, 0, 0, 0, 0],
		"namedParams": {"lifesteal_weapon": 7.0, "healamp": 10.0,
			"flatsteal": 4.0, "lifesteal_factor": 150.0},
	})


# 合成一次「宿主被攻击」的派发（CoreItem.dealDamage 在 Item.gd:4150 一带的等价点）
func dispatch_attacked(host, damage: int, hit: bool) -> void:
	var dr = CoreDamageResult.new()
	dr.hit = hit
	dr.damage = damage
	_ctx.bus.emitSignal(host, "attacked", [dr])


# ─────────────────── 1. Socket 折叠等价性 ───────────────────

func test_socket_fold() -> void:
	say("")
	say("[1] Socket 折叠等价性：插座身份 == 宿主物品（GemSocket.gd 的全部访问面）")

	new_world(3001)
	var host = mk_host(weapon_descr(), _p)
	host._readyInit()
	place(host, 0, 0)
	var gem = mk_gem()
	gem._readyInit()
	attach(host, gem, 0, 2)

	# ── 折叠的两条腿 ──
	# 原版 Item.setGem 走 `gem.addToSocket(sockets[id])` → `socket = _socket`；
	# 内核把插座折叠为宿主，故 gem.socket 就是宿主物品本身。
	check(gem.socket == host, "gem.socket 应就是宿主物品（对应 Gem.addToSocket）")
	# 原版 GemSocket.getItem() 返回 `item`，`item` 由 Item.initSockets() 的
	# `socket.item = self` 装填（Item.gd:2978-2980）。折叠后该后置条件恒真，
	# 故 CoreItem.getItem() 直接返回 self —— 这正是 initSockets 无事可做的依据。
	check(host.getItem() == host,
		"宿主 getItem() 应返回 self（承担 GemSocket.getItem 的语义）")
	check(gem.getItem() == host, "宝石 getItem() 应经 socket 回到宿主（Gem.gd:60-64）")
	check(gem.getItem() != gem, "宝石 getItem() 不得返回自己（那是没折叠成功的表现）")

	# ── Gem.gd:36-76 其余分支逐条落到宿主同名方法 ──
	check(gem.isOwnable() == host.isOwnable(), "isOwnable 应等于宿主（Gem.gd:36-40）")
	check(gem.isOwnedByOpponent() == host.isOwnedByOpponent(),
		"isOwnedByOpponent 应等于宿主（Gem.gd:42-46）")
	check(gem.getEffectiveOwnerType() == host.getEffectiveOwnerType(),
		"getEffectiveOwnerType 应等于宿主（Gem.gd:48-52）")
	check(gem.getInventory() == host.getInventory(),
		"getInventory 应等于宿主（Gem.gd:54-58）")
	check(gem.isPlaced() == host.isPlaced(), "isPlaced 应等于宿主（Gem.gd:66-70）")
	# host.isOwnable() 对已放置的 PlayerInventory 物品应为真 —— 顺带确证
	# 「等于」不是因为两边都恒假（那也是一种静默失效）
	check(host.isOwnable(), "已入包的宿主应 isOwnable（否则上面的等价比较没有信息量）")
	check(host.isPlaced(), "宿主应已 placed")

	# ── 计数族：走 gems 数组（即原版 sockets 数组） ──
	check(host.hasSockets(), "2 个插座的宿主 hasSockets 应为真")
	check(host.getNumSockets() == 2, "插座数应为 2，实为 %d" % host.getNumSockets())
	check(host.hasGems(), "装了宝石后 hasGems 应为真")
	check(host.getGemsNoNull().size() == 1,
		"getGemsNoNull 应滤掉空插座，实为 %d" % host.getGemsNoNull().size())
	check(host.getGemsOfItems([host]).size() == 1, "getGemsOfItems 应汇总到 1 颗宝石")

	# ── 附注：`isInInventory()` 在原版就是**死代码**，不在此立契约 ──
	# Gem.gd:72-76 覆写了一个 `Item` 上并不存在的方法：socket != null 分支调
	# `socket.getItem().isInInventory()`、else 分支调 `.isInInventory()`，而
	# `Item.isInInventory` 在原版全仓库都不存在（`grep -rn "func isInInventory"
	# decompiled_full/` 只命中 Gem.gd 自身），且该方法无任何调用点。
	# 内核逐字保留其形状（转译产物同样如此），因无人调用而无从触发 ——
	# 属「原版自带的死代码」，与漏实现无关，故不做断言。
	say("    socket == host ✓ / getItem 一族 5 条与宿主一致 ✓ / 计数族 ✓")


# ─────────────────── 2. getGemMode 四分支 ───────────────────

func test_gem_mode_dispatch() -> void:
	say("")
	say("[2] getGemMode 四分支 + hasCooldown 口径（Gem.gd:78-88 / 274-278）")

	new_world(3002)

	# ① 武器宿主 → Weapon（Gem.gd:80-81 按 getItem().isWeapon() 分流）
	var w_host = mk_host(weapon_descr(), _p)
	w_host._readyInit()
	place(w_host, 0, 0)
	var g1 = mk_gem()
	g1._readyInit()
	attach(w_host, g1, 0, 2)
	check(g1.getGemMode() == 0,
		"武器宿主上的宝石应判 Weapon(0)，实为 %d" % g1.getGemMode())
	check(not g1.hasCooldown(),
		"Weapon 模式不走自身冷却（Gem.gd:274-278 只放行 Inventory/Inactive）")

	# ② 非武器宿主 → Armor
	var a_host = mk_host(armor_descr(), _p)
	a_host._readyInit()
	place(a_host, 5, 0)
	var g2 = mk_gem()
	g2._readyInit()
	attach(a_host, g2, 0, 1)
	check(g2.getGemMode() == 1,
		"非武器宿主上的宝石应判 Armor(1)，实为 %d" % g2.getGemMode())
	check(not g2.hasCooldown(), "Armor 模式不走自身冷却")

	# ③ 未入插座但已放置 → Inventory
	var g3 = mk_gem()
	g3._readyInit()
	place(g3, 3, 0)
	check(g3.getGemMode() == 2,
		"未插座但已放置应判 Inventory(2)，实为 %d" % g3.getGemMode())
	check(g3.hasCooldown(), "Inventory 模式应走自身冷却（cd=5）")

	# ④ 未插座也未放置 → Inactive
	var g4 = mk_gem()
	g4._readyInit()
	check(g4.getGemMode() == 3,
		"未插座也未放置应判 Inactive(3)，实为 %d" % g4.getGemMode())

	say("    Weapon(武器) / Armor(非武器) / Inventory(已放置) / Inactive(未放置) ✓；"
		+ "hasCooldown 仅在 Inventory 侧为真 ✓")


# ─────────────────── 3. Weapon 模式公式级效果 ───────────────────

func test_weapon_mode_effect() -> void:
	say("")
	say("[3] Weapon 模式：宿主 attacked 命中 → heal(ceil(伤害 × lifesteal_weapon%))")

	new_world(3003)
	var host = mk_host(weapon_descr(), _p)
	host._readyInit()
	place(host, 0, 0)
	var gem = mk_gem()
	gem._readyInit()
	attach(host, gem, 0, 2)

	# prepare 走 CoreItem.prepare → Gem.onPrepare（Gem.gd:293-301）→ prepareWeapon
	# → connectForCombat(socket.getItem(), "attacked", "onAttack")。此处经真实
	# startBattle 触发，不手工调内部方法。
	_combat.startBattle([host], [])
	check(_ctx.bus.signalIDs.has("attacked"),
		"prepareWeapon 应已订阅宿主 attacked（事件表里必须有该信号）")
	check(_probe.gem_heals == 0, "开战瞬间不应有宝石治疗（还没命中过）")

	# ① 100 × 7% = 7.0 → ceil = 7
	var before = 100
	_p.setCurrentHealth(before)
	dispatch_attacked(host, 100, true)
	check(_p.curHealth == before + 7,
		"伤害 100 × 7%% 应治 +7，实为 +%d" % (_p.curHealth - before))

	# ② 57 × 7% = 3.99 → ceil = 4（验取整方向是向上而不是四舍五入）
	_p.setCurrentHealth(before)
	dispatch_attacked(host, 57, true)
	check(_p.curHealth == before + 4,
		"伤害 57 × 7%% 应治 +4（ceil 而非 round），实为 +%d" % (_p.curHealth - before))

	# ③ 未命中不治疗（Ruby.gd:11 `if damageRes.hasHit()`）
	_p.setCurrentHealth(before)
	dispatch_attacked(host, 100, false)
	check(_p.curHealth == before,
		"未命中的 attacked 不得治疗，实为 +%d" % (_p.curHealth - before))

	# ④ 治疗与 miniActivate 一一对应（Ruby.gd:12-13 两句同在一个 if 内）
	check(_probe.gem_heals == 2, "应恰好 2 次宝石治疗，实为 %d" % _probe.gem_heals)
	check(_probe.gem_mini == 2, "应恰好 2 次 MiniActivate，实为 %d" % _probe.gem_mini)
	check(is_equal_approx(_probe.gem_heal_sum, 11.0),
		"两次治疗合计应为 7+4=11，实为 %.1f" % _probe.gem_heal_sum)

	# ⑤ 治疗必须记在被治疗者身上：角色治疗飘字总数 ≥ 宝石治疗数
	check(_probe.heals >= _probe.gem_heals,
		"角色治疗飘字 %d 少于宝石治疗 %d（治疗没进角色结算）"
		% [_probe.heals, _probe.gem_heals])

	say("    +7（100 × 7%）/ +4（57 × 7% 向上取整）/ 未命中 0 ✓；"
		+ "miniActivate 与治疗一一对应 ✓")


# ─────────────────── 4. Armor 模式效果 ───────────────────

func test_armor_mode_effect() -> void:
	say("")
	say("[4] Armor 模式：prepareArmor → 角色治疗效率 +gemPower × P2%（Ruby.gd:18）")

	new_world(3004)
	var host = mk_host(armor_descr(), _p)
	host._readyInit()
	place(host, 0, 0)
	var gem = mk_gem()
	gem._readyInit()
	attach(host, gem, 0, 1)

	var eff0 = _p.getHealingEfficiency()
	_combat.startBattle([host], [])
	check(gem.getGemMode() == 1, "护甲上的宝石应走 Armor 模式，实为 %d" % gem.getGemMode())
	# gemPower 初始 1.0 × P2(healamp)=10 / 100 = +0.1
	check(is_equal_approx(_p.getHealingEfficiency(), eff0 + 0.1),
		"应给角色 +0.1 治疗效率（1.0 × 10%%），实为 %s" % str(_p.getHealingEfficiency()))

	# 护甲模式**不得**订阅宿主 attacked（那是 Weapon 分支的事）——反向卡一道
	# 门，防止 getGemMode 分流写反了却因为两边都「跑得通」而看不出来。
	_p.setCurrentHealth(100)
	dispatch_attacked(host, 100, true)
	check(_p.curHealth == 100,
		"Armor 模式不该因宿主 attacked 而治疗（Weapon 分支没走）")

	say("    治疗效率 %s → %s ✓；Armor 分支未订阅 attacked ✓"
		% [str(eff0), str(_p.getHealingEfficiency())])


# ─────────────────── 5. Inventory 模式效果 ───────────────────

func test_inventory_mode_effect() -> void:
	say("")
	say("[5] Inventory 模式：走宝石自身冷却，doCooldownEffect = stealLife(P3, factor)")

	new_world(3005)
	# 不挂插座、单独放进背包：这是原版「宝石没插在装备上」的形态
	var gem = mk_gem()
	gem._readyInit()
	place(gem, 0, 0)

	_combat.startBattle([gem], [])
	check(gem.getGemMode() == 2, "已放置未插座应走 Inventory 模式，实为 %d" % gem.getGemMode())
	check(gem.hasCooldown(), "Inventory 模式应走自身冷却")

	# ① 冷却机制：本宝石的冷却不是 startBattle 里立刻建的 —— 它在**激活阶段**由
	#    preCombatStart 启动（CoreItem.preCombatStart：hasCooldown → triggerTime = iterationCooldown
	#    → activateCooldown）。故必须真的推进物理帧走到那一步。
	var ticks := 0
	while gem.triggerTime <= 0.0 and ticks < 900:
		_combat.physicsTick(CoreContext.PHYSICS_DELTA)
		ticks += 1
	check(gem.triggerTime > 0.0,
		"冷却应已启动（triggerTime > 0），实为 %s（推进 %d 帧后）"
		% [str(gem.triggerTime), ticks])
	check(gem.isCooldownActive(), "冷却应处于激活态")
	# cd=5，照原版 adjustCooldown 的 ±5% 落在 [4.75, 5.25]
	check(gem.triggerTime >= 4.75 and gem.triggerTime <= 5.25,
		"首个冷却到期时刻应落在 [4.75, 5.25]，实为 %s" % str(gem.triggerTime))

	# ② 自然触发：再推进一个冷却周期，让**冷却回路**自己去调 doCooldownEffect
	#    （Ruby.gd:5-6 stealLife(P3=4, lifesteal_factor=150%)）。不手工调用 ——
	#    手工调只能证明「函数能跑」，推帧才能证明「冷却真的会调到它」。
	_p.setCurrentHealth(100)
	var hp_p = _p.curHealth
	var hp_o = _o.curHealth
	ticks = 0
	while _o.curHealth >= hp_o and ticks < 900:
		_combat.physicsTick(CoreContext.PHYSICS_DELTA)
		ticks += 1
	check(_o.curHealth < hp_o,
		"宝石的自身冷却应在 %d 帧内触发（对手血量仍为 %s）" % [ticks, str(_o.curHealth)])
	check(hp_o - _o.curHealth == 4,
		"stealLife 应对对手造成 P3=4 点伤害，实为 %d" % (hp_o - _o.curHealth))
	check(_p.curHealth > hp_p,
		"stealLife 的吸血部分应回补自身，自身血量仍为 %s" % str(_p.curHealth))
	check(_p.curHealth - hp_p == 6,
		"吸血应为 4 × 150%% = 6，实为 %d" % (_p.curHealth - hp_p))

	say("    Inventory 模式：冷却 [%.2f, %.2f]s 启动 ✓ / 自行触发 → 对手 %s→%s、自身 %s→%s ✓"
		% [gem.triggerTime - 0.05, gem.triggerTime + 0.05,
		   str(hp_o), str(_o.curHealth), str(hp_p), str(_p.curHealth)])
