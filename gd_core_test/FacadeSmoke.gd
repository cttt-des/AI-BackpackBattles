# =============================================================================
# FacadeSmoke.gd — gd_core 单例门面契约测试（Godot 3.6 宿主）
# =============================================================================
# 原版战斗逻辑横向依赖 6 个 autoload（Game / Util / Sound / ItemBook / EventBus /
# Settings）。内核按「战斗需要的部分」逐个换成显式对象挂到 ctx 上。这些**门面**
# 若接错，靠它们跑的物品行为会**静默跑偏**（isA 恒假、查询恒空、信号永不到达），
# 解析闸门查不出来 —— 必须单独验契约。
#
# 覆盖的契约：
#   1. 描述符身份   同一标识符 → 同一实例（Item.isA 是引用相等），
#                   `register()` 覆盖真实数据后身份仍一致
#   2. 库存类型查询 本方只算 ownerType ∈ {PlayerInventory, Socket}；对手侧不过滤
#   3. Item 包装层  getAllInInventoryOfType / countAllInInventoryOfType /
#                   isTypeInInventory / countAllPlacedOfType 与 ItemBook 查询一致，
#                   且对手侧物品自动走 _opponent 分支
#   4. Game 状态量  sandbagActive / curMode / curRound 的取值域
#   5. combatTimer 身份  物品用 `connectForCombat(Game.combatTimer, ...)` 订阅疲劳
#                   信号，EventBus 按 emitter.get_instance_id() 配对 ——
#                   故 ctx.combat 必须**就是**发信号的那个 CoreCombat 实例
#   6. 真实物品脚本  用 KingoftheBling / Everburning / Sandbag / LevelUp 的**原版
#                   转译产物**跑一遍，验证判定真的按门面数据分流
#
# ★ 装配注意（踩过的坑）：GDScript 3.6 的 `GDScript.new()` **只接受 0 个实参**，
#   且 `extends "res://..."` 形态的脚本连 `_init` 的参数个数都解析不到。故所有
#   物品脚本（含适配层 Item.gd）一律 `SCRIPT.new()` + `.setup(ctx, data, chr)`。
#
# 运行：
#   Godot_v3.6-stable_win64.exe --no-window --path gd_core_test --script FacadeSmoke.gd
# =============================================================================
extends SceneTree


# 探针：挂在 EventBus 上数回调次数。只用 Reference（无参构造，不碰 CoreItem
# 的构造签名），故不引入任何行为耦合。
class BusProbe extends Reference:
	var hits := 0

	func onFatigueStarted():
		hits += 1


var failures: Array = []
var _report: Array = []


func say(line: String) -> void:
	print(line)
	_report.push_back(line)
	var fh = File.new()
	if fh.open("res://facade_result.txt", File.WRITE) == OK:
		fh.store_string(PoolStringArray(_report).join("\n") + "\n")
		fh.close()


func check(cond: bool, what: String) -> void:
	if not cond:
		failures.push_back(what)


func _init() -> void:
	say("")
	say("=== gd_core 单例门面契约测试 ===")
	print("FACADE: start")
	test_descriptor_identity()
	print("FACADE: test1 done")
	test_inventory_queries()
	print("FACADE: test2 done")
	test_item_wrappers()
	print("FACADE: test3 done")
	test_game_state()
	print("FACADE: test4 done")
	test_combat_timer_identity()
	print("FACADE: test5 done")
	test_real_item_scripts()
	print("FACADE: test6 done")

	say("")
	if failures.empty():
		say("FACADE: PASS")
	else:
		for f in failures:
			say("FACADE: FAIL  " + f)
		say("FACADE: FAIL (%d 项)" % failures.size())

	quit(0 if failures.empty() else 1)


# ─────────────────────────── 装配辅助 ───────────────────────────

func new_character(ctx, pid: int) -> CoreCharacter:
	var c = CoreCharacter.new(ctx, pid)
	c.setMaxHealth(100)
	c.setCurrentHealth(100)
	c.maxStamina = 50.0
	c.baseMaxStamina = 50.0
	c.fillUpStamina()
	return c


func new_world(seed_value: int) -> Dictionary:
	var ctx = CoreContext.new(seed_value)
	var p = new_character(ctx, CoreCharacter.ID.PLAYER)
	var o = new_character(ctx, CoreCharacter.ID.OPPONENT)
	var combat = CoreCombat.new(ctx)
	combat.setup(p, o)
	return {"ctx": ctx, "p": p, "o": o, "combat": combat}


# 两段式装配：0 参构造 + setup（原版物品脚本的构造签名解析不了实参）
func build(script_obj, ctx, descr, character):
	var it = script_obj.new()
	it.setup(ctx, descr, character)
	return it


func new_item(ctx, character, descr) -> CoreItem:
	return CoreItem.new(ctx, descr, character)


func v2(x: int, y: int) -> Vector2:
	return Vector2(x, y)


# 按「加入背包」的正规路径登记（CoreGrid.addItem → Item.addToInventory），
# ownerType 由 addToInventory 从 inventory == ctx.player.inventory 推出。
func place(grid, item, x: int, y: int) -> void:
	grid.addItem(item, [v2(x, y)])


# ─────────────────── 1. 描述符身份（isA 契约） ───────────────────

func test_descriptor_identity() -> void:
	say("")
	say("[1] 描述符身份：同一标识符 → 同一实例（Item.isA 依赖引用相等）")

	var w = new_world(1001)
	var ib = w["ctx"].item_book
	check(ib != null, "ctx.item_book 未构造")

	# 生成的名字→标识符表必须覆盖战斗函数实际用到的 ItemBook 成员。
	# ★ `moonArmorDescriptor` 之类是**物品脚本自己的** onready 变量
	#   （`onready var moonArmorDescriptor = ItemBook.getDescriptor("Moon Armor")`），
	#   由转译器映射 `ItemBook.getDescriptor(` 处理，不在本表内。
	for nm in ["magicRingDescriptor", "superiorRingDescriptor",
			"bagtacularDescriptor", "flameDescriptor",
			"platinCardDescriptor", "chessboardDescriptor"]:
		check(CoreItemBook.DESCRIPTOR_IDS.has(nm),
			"DESCRIPTOR_IDS 缺条目：" + nm)
	check(CoreItemBook.DESCRIPTOR_IDS.get("magicRingDescriptor") == "Magic Ring",
		"DESCRIPTOR_IDS 的 名字→标识符 映射须与原版 getDescriptor(...) 一致")
	# 物品脚本直接调 getDescriptor("<显示名>") 的写法也要能命中同一个标识符
	check(ib.getDescriptor(CoreItemBook.DESCRIPTOR_IDS["flameDescriptor"])
			== ib.getDescriptor("Flame"),
		"表内标识符与直接查询必须命中同一实例")

	var d1 = ib.getDescriptor("Magic Ring")
	var d2 = ib.getDescriptor("Magic Ring")
	check(d1 == d2, "getDescriptor 对同一标识符应恒返回同一实例")
	check(d1 != ib.getDescriptor("Superior Ring"), "不同描述符必须是不同实例")
	check(d1.getName() == "Magic Ring", "占位描述符的 identifier 应是查询用的名字")

	# 装配层用真实数据覆盖占位实例后，身份仍要一致（单一真值源，无同步问题）
	var real = CoreItemData.new().fromDict(
		{"name": "Magic Ring", "identifier": "Magic Ring", "price": 30})
	ib.register(real)
	check(ib.getDescriptor("Magic Ring") == real,
		"register 后 getDescriptor 应返回真实数据实例")

	var ring = new_item(w["ctx"], w["p"], real)
	check(ring.isA(ib.getDescriptor("Magic Ring")), "isA：同一实例应判真")
	check(not ring.isA(ib.getDescriptor("Superior Ring")), "isA：不同实例应判假")

	# ── 具名参数的基名索引：hasParam 走「基名 → 全名」（原版 paramBases_inverted） ──
	# ★ 这组断言把守一个已修的真 bug：内核曾用 paramBases（全名 → 基名）实现
	#   hasParam，于是 `hasParam("heal")` 对只带 `heal_food` 的物品判**假**，
	#   而 Item.gd:5380（内核 CoreItem.gd:1616）的 isHealingItem 正是这么调的 ——
	#   属静默跑偏，解析闸门查不出来。
	var dp = CoreItemData.new()
	dp.addNamedParam("dur_stun", 3.0)
	dp.addNamedParam("heal_food", 5.0)
	check(dp.hasParam("dur"), "hasParam 应接受基名 dur（实际参数名为 dur_stun）")
	check(dp.hasParam("heal"), "hasParam 应接受基名 heal（实际参数名为 heal_food）")
	check(not dp.hasParam("dur_stun"), "hasParam 不应接受全名（原版是基名→全名映射）")
	check(dp.paramBases.get("dur_stun") == "dur", "paramBases 应给出基名")
	check(dp.paramBases_inverted.get("heal") == "heal_food",
		"paramBases_inverted 应给出全名")
	check(dp.getP("dur_stun") == 3.0, "具名参数应可按全名取值")
	# 装配层若只给 named_params（battle_items.json 的原始键），也要派生出来
	var dd = CoreItemData.new().fromDict(
		{"name": "X", "named_params": {"dur_blind": 2.0, "maxhealth_use": 7.0}})
	check(dd.hasParam("dur"), "fromDict 应从 named_params 派生基名表（snake 键）")
	check(dd.hasParam("maxhealth"), "fromDict 派生应覆盖 maxhealth_use")
	check(dd.getP("maxhealth_use") == 7.0, "fromDict 应装载具名参数的值")

	say("    DESCRIPTOR_IDS 覆盖 7 项 ✓ / getDescriptor 幂等 ✓ / register 覆盖 ✓ / "
		+ "isA 语义 ✓ / hasParam 基名索引 ✓")


# ─────────────────── 2. 库存类型查询（ItemBook 侧） ───────────────────

func test_inventory_queries() -> void:
	say("")
	say("[2] 库存类型查询：本方只算 PlayerInventory + Socket，对手侧不过滤")

	var w = new_world(1002)
	var ctx = w["ctx"]
	var p = w["p"]
	var o = w["o"]
	var ib = ctx.item_book

	var dA = ib.getDescriptor("Stone")
	var dB = ib.getDescriptor("Garlic")
	var dC = ib.getDescriptor("Banana")

	place(p.inventory, new_item(ctx, p, dA), 0, 0)
	place(p.inventory, new_item(ctx, p, dA), 1, 0)
	place(p.inventory, new_item(ctx, p, dB), 2, 0)

	check(ib.getItemsInInventoryOfType(dA).size() == 2, "本方 dA 应查到 2 件")
	check(ib.countItemsInInventoryOfType(dA) == 2, "本方 dA 计数应为 2")
	check(ib.countItemsInInventoryOfType(dB) == 1, "本方 dB 计数应为 1")
	check(ib.isItemInInventory(dA), "本方应含 dA")
	check(not ib.isItemInInventory(dC), "本方不该含未放置的 dC")
	check(ib.countItemsInInventoryOfType(dC) == 0, "未放置描述符计数应为 0")
	check(ib.getItemsInInventoryOfType(dC).empty(), "未放置描述符应查到空数组")
	check(ib.getItemsInInventoryOfType_opponent(dA).empty(),
		"对手网格为空时对手侧查询应为空")

	place(o.inventory, new_item(ctx, o, dA), 0, 0)
	check(ib.getItemsInInventoryOfType_opponent(dA).size() == 1,
		"对手 dA 应查到 1 件")
	check(ib.countItemsInInventoryOfType_opponent(dA) == 1,
		"对手 dA 计数应为 1")
	check(ib.isItemInInventory_opponent(dA), "对手侧应含 dA")
	check(ib.countItemsInInventoryOfType(dA) == 2,
		"对手物品不得计入本方查询（两侧口径必须分离）")

	say("    本方 2/1 ✓ / 未放置 0 ✓ / 对手 1 ✓ / 两侧隔离 ✓")


# ─────────────────── 3. Item 包装层一致性 ───────────────────

func test_item_wrappers() -> void:
	say("")
	say("[3] Item 包装层：包装方法须与 ItemBook 查询同结果，对手物品自动走 _opponent")

	var w = new_world(1003)
	var ctx = w["ctx"]
	var p = w["p"]
	var o = w["o"]
	var ib = ctx.item_book
	# 包装方法在适配层 Item.gd 上（= 469 个物品脚本的直接基类），不在 CoreItem 上
	var item_base = load("res://gd_core_items/Item.gd")
	check(item_base != null, "适配层 Item.gd 应可加载")
	if item_base == null:
		return

	var dA = ib.getDescriptor("Stone")
	var dC = ib.getDescriptor("Banana")

	var a1 = build(item_base, ctx, dA, p)
	var a2 = build(item_base, ctx, dA, p)
	place(p.inventory, a1, 0, 0)
	place(p.inventory, a2, 1, 0)

	check(a1.getAllInInventoryOfType(dA).size() == 2, "getAllInInventoryOfType 应为 2")
	check(a1.countAllInInventoryOfType(dA) == 2, "countAllInInventoryOfType 应为 2")
	check(a1.isTypeInInventory(dA), "isTypeInInventory 应为真")
	check(not a1.isTypeInInventory(dC), "未放置类型应为假")
	check(a1.countAllInInventoryOfType(dC) == 0, "未放置类型计数应为 0")

	# Socket 侧（宝石）恒计入，且不受 placed 影响 —— 对齐 ItemBook.gd:294-303
	check(a1.countAllPlacedOfType(dA) == 2, "两件均已放置，placed 计数应为 2")
	a1.placed = false
	check(a1.countAllPlacedOfType(dA) == 1, "placed=false 应被 placed 计数排除")
	check(a1.countAllInInventoryOfType(dA) == 2, "placed 不影响 inventory 计数")
	# 还原 a1，再把 a2 变成 Socket **且 placed=false**：此时能凑出 2 的唯一解释
	# 就是「Socket 绕过 placed 判定」—— 对齐 ItemBook.gd:294-303
	# `(placed and ownerType == PlayerInventory) or ownerType == Socket`
	a1.placed = true
	a2.placed = false
	a2.ownerType = CoreConst.Owner.Socket
	check(a1.countAllPlacedOfType(dA) == 2,
		"Socket 侧应计入 placed 计数（且不受 placed=false 影响）")
	check(a1.countAllInInventoryOfType(dA) == 2, "Socket 侧应计入 inventory 计数")

	# 对手物品：isOwnedByOpponent() → 走 _opponent 分支（不过滤 ownerType）
	var oa = build(item_base, ctx, dA, o)
	place(o.inventory, oa, 0, 0)
	check(oa.isOwnedByOpponent(), "对手物品应判 isOwnedByOpponent")
	check(oa.getAllInInventoryOfType(dA).size() == 1, "对手物品应看到对手侧 1 件")
	check(oa.countAllInInventoryOfType(dA) == 1, "对手物品计数应为 1")
	check(oa.isTypeInInventory(dA), "对手物品应含 dA")

	say("    包装层结果一致 ✓ / Socket 计入 ✓ / placed 语义 ✓ / 对手分支 ✓")


# ─────────────────── 4. Game 状态量 ───────────────────

func test_game_state() -> void:
	say("")
	say("[4] Game 状态量：sandbagActive / curMode / curRound 的取值域")

	var w = new_world(1004)
	var ctx = w["ctx"]
	var combat = w["combat"]

	check(ctx.sandbag_active == false, "每场战斗开局 sandbagActive 应为假")
	ctx.sandbag_active = true
	check(ctx.sandbag_active, "sandbagActive 应可写")
	check(ctx.cur_mode == CoreConst.GameMode.Ranked, "curMode 默认应为 Ranked")
	check(ctx.cur_mode != CoreConst.GameMode.History,
		"默认模式不应是 History（ChessBoard.onPrepare 的分支依赖它）")
	check(CoreConst.GameMode.History == 4, "GameMode 取值须对齐 Game.gd:148-154")
	check(ctx.cur_round == 0, "curRound 默认应为 0")

	say("    sandbagActive ✓ / curMode=Ranked(≠History) ✓ / curRound=0 ✓")


# ─────────────────── 5. combatTimer 身份 ───────────────────

func test_combat_timer_identity() -> void:
	say("")
	say("[5] combatTimer 身份：ctx.combat 必须就是发疲劳信号的那个 CoreCombat")

	var w = new_world(1005)
	var ctx = w["ctx"]
	var combat = w["combat"]
	var p = w["p"]

	check(ctx.combat != null, "ctx.combat 未回填（CoreCombat._init 应写 self）")
	check(ctx.combat == combat, "ctx.combat 应等于当前 CoreCombat 实例")

	# 真实疲劳路径：CoreCombat.dealFatigueDamage 首跳发 fatigue_start
	var probe = BusProbe.new()
	ctx.bus.connectEvent(ctx.combat, "fatigue_start", probe, "onFatigueStarted")
	combat.fatigue_counter = 0
	combat.dealFatigueDamage()
	check(probe.hits == 1,
		"经 ctx.combat 订阅的 fatigue_start 应被真实疲劳路径打到")

	# emitter 身份必须精确配对：换成别的 emitter 不得命中
	var probe2 = BusProbe.new()
	ctx.bus.connectEvent(ctx.combat, "fatigue_start", probe2, "onFatigueStarted")
	ctx.bus.emitSignal(p, "fatigue_start")
	check(probe2.hits == 0, "换一个 emitter 不应命中（EventBus 按 emitter 配对）")
	ctx.bus.emitSignal(ctx.combat, "fatigue_start")
	check(probe2.hits == 1, "同一 emitter 应命中")

	say("    ctx.combat == CoreCombat 实例 ✓ / 真实疲劳路径命中 ✓ / emitter 精确配对 ✓")


# ─────────────────── 6. 真实物品脚本端到端 ───────────────────

func test_real_item_scripts() -> void:
	say("")
	say("[6] 真实物品脚本：原版转译产物的判定须按门面数据分流")

	var w = new_world(1006)
	var ctx = w["ctx"]
	var p = w["p"]
	var o = w["o"]
	var ib = ctx.item_book

	# ── KingoftheBling.canAffect：描述符身份直接决定联动是否成立 ──
	var kb_script = load("res://gd_core_items/Exclusive/KingoftheBling.gd")
	check(kb_script != null, "KingoftheBling.gd 应可加载")
	if kb_script != null:
		var kb = build(kb_script, ctx, ib.getDescriptor("King of the Bling"), p)
		kb._readyInit()
		check(kb.canAffect(new_item(ctx, p, ib.getDescriptor("Magic Ring"))),
			"magicRing 描述符应被 canAffect 接受")
		check(kb.canAffect(new_item(ctx, p, ib.getDescriptor("Superior Ring"))),
			"superiorRing 描述符应被 canAffect 接受")
		check(not kb.canAffect(new_item(ctx, p, ib.getDescriptor("Banana"))),
			"无关描述符应被 canAffect 拒绝")
		say("    KingoftheBling.canAffect 按描述符分流 ✓")

	# ── Everburning.onPrepare：按描述符统计背包内 Flame 数量 ──
	var ev_script = load("res://gd_core_items/Exclusive/Everburning.gd")
	check(ev_script != null, "Everburning.gd 应可加载")
	if ev_script != null:
		var ev = build(ev_script, ctx, ib.getDescriptor("Everburning"), p)
		ev._readyInit()
		place(p.inventory, new_item(ctx, p, ib.getDescriptor("Flame")), 5, 0)
		place(p.inventory, new_item(ctx, p, ib.getDescriptor("Flame")), 6, 0)
		place(p.inventory, new_item(ctx, p, ib.getDescriptor("Banana")), 7, 0)
		ev.onPrepare()
		check(ev.numFlames == 2,
			"Everburning.numFlames 应为 2（只数 Flame），实为 %s" % str(ev.numFlames))
		say("    Everburning.onPrepare 数到 %s 个 Flame ✓" % str(ev.numFlames))

	# ── Sandbag.onPreCombatStart：Game.sandbagActive 闸门决定是否重复降抗 ──
	var sb_script = load("res://gd_core_items/Exclusive/Sandbag.gd")
	check(sb_script != null, "Sandbag.gd 应可加载")
	if sb_script != null:
		# damReduction = getP1() → params[0]；dur 是**具名参数**，走 getP_m("dur")
		# → paramBases 派生。LeatherHelm.onPreCombatStart 里真的会调
		# buffTimer.start(getBuffDur())，缺 dur 就会在 getParamModified 报
		# `Invalid get index 'dur'` —— 故这里顺带把该路径验掉。
		var sd = ib.register(CoreItemData.new().fromDict(
			{"name": "Sandbag", "identifier": "Sandbag", "params": [8.0],
				"namedParams": {"dur": 4.0}}))
		ctx.sandbag_active = false
		var sb1 = build(sb_script, ctx, sd, p)
		sb1._readyInit()
		check(is_equal_approx(sb1.damReduction, 8.0),
			"damReduction 应取到 params[0]，实为 %s" % str(sb1.damReduction))
		check(is_equal_approx(sb1.getBuffDur(), 4.0),
			"getBuffDur 应取到具名参数 dur=4，实为 %s" % str(sb1.getBuffDur()))
		sb1.onPreCombatStart()
		check(ctx.sandbag_active, "首个沙袋应把 sandbagActive 置真")
		check(is_equal_approx(o.damageResistance, 8.0),
			"首个沙袋应把对手抗性 +8，实为 %s" % str(o.damageResistance))

		var sb2 = build(sb_script, ctx, sd, p)
		sb2._readyInit()
		sb2.onPreCombatStart()
		check(is_equal_approx(o.damageResistance, 8.0),
			"第二个沙袋不得重复降抗（原版 Game.sandbagActive 闸门）")
		sb1.buffEnded()
		check(not ctx.sandbag_active, "buffEnded 应把 sandbagActive 复位")
		check(is_equal_approx(o.damageResistance, 0.0), "buffEnded 应撤销抗性")
		say("    沙袋闸门 + 复位 ✓")

	# ── LevelUp.onPrepare：meta 回合数（Game.curRound）驱动速度加成 ──
	var lu_script = load("res://gd_core_items/Exclusive/LevelUp.gd")
	check(lu_script != null, "LevelUp.gd 应可加载")
	if lu_script != null:
		var ld = ib.register(CoreItemData.new().fromDict({
			"name": "Level Up", "identifier": "Level Up",
			"namedParams": {"skillround": 2.0, "speed": 10.0}}))
		ctx.cur_round = 5
		var lu = build(lu_script, ctx, ld, p)
		lu._readyInit()
		check(lu.buyRound == 2, "buyRound 应取到 skillround=2，实为 %s" % str(lu.buyRound))
		check(is_equal_approx(lu.speedPerRound, 0.1),
			"speedPerRound 应为 0.1，实为 %s" % str(lu.speedPerRound))
		# 入库后才算 placed → hasCharacter() 为真（getSpeed 需要角色；addSpeed 不需要）
		place(p.inventory, lu, 3, 4)
		lu.onPrepare()
		# ★ 注意用 `speed()` 而**不是** `speed`：原版 Item.gd:4832 是
		#   `func speed() -> float: return speedScale`（方法），addSpeed 改的
		#   就是 speedScale；而 getSpeed()（Item.gd:3742）是**派生倍率**
		#   clamp(1 + speed, 0.1, 10)。写成 `lu.speed` 会拿到 funcref。
		check(is_equal_approx(lu.speed(), 0.3),
			"(curRound 5 - buyRound 2) × 0.1 应为 0.3，实为 %s" % str(lu.speed()))
		check(is_equal_approx(lu.getSpeed(), 1.3),
			"同一 0.3 加成经 getSpeed 派生应为 1.3，实为 %s" % str(lu.getSpeed()))
		say("    LevelUp 速度加成 = (5-2)×0.1 = 0.3 → getSpeed 1.3 ✓")
