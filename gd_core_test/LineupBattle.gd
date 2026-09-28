# =============================================================================
# LineupBattle.gd — gd_core 真实阵容端到端验证（Godot 3.6 宿主）
# =============================================================================
# 前 7 道闸门查的是「解析得了 / 契约对 / 单点行为对」。本闸门查的是**最后一公里**：
# 把 8 套真实阵容按 lineup 摆盘装进无头内核，用**原版转译出来的物品行为脚本**
# 从开战打到判胜，看：
#   1. 装配面  每个物品脚本都能按两段式装配成功（_readyInit + 入包 + 插座）
#   2. 运行面  整场无脚本错误、在时限内自然收场（不靠 timed_out 兜底）
#   3. 行为面  物品行为真的在跑（激活次数 / 伤害事件 / 疲劳触发都 > 0，不是空转）
#   4. 确定性  同种子重跑逐位一致（赢家 + 双方血量 + 时长 + 事件计数）
#
# 数据来源：LineupFixture.gd（tools/gen_lineup_fixture.py 生成，含绝对占格）
#
# 装配次序（对齐原版而非模拟器）：
#   原版 ItemBook 实例化 → 物品被 reparent 进背包（入场景树 → _ready 此刻运行）
#   → Inventory.addItem 调 addToInventory。故本闸门是
#   `setup → 注网格元数据 → _readyInit → inventory.addItem`；
#   宝石则在宿主入包之后 setGem（原版也是先摆宿主、再 setGemData）。
#
# 宝石阵容同场跑。Socket 门面的折叠等价性由 GemFacade 闸门单独取证
# （socket 的访问面、getGemMode 四分支、Weapon 模式公式级效果）；
# 本闸门负责端到端那一半：宝石在**真实对局**里必须产生可观测的治疗，
# 见 test_gem_effect 的 A/B（同种子含宝石 / 去宝石，去宝石侧必须为 0）。
#
# 运行：
#   Godot_v3.6-stable_win64.exe --no-window --path gd_core_test --script LineupBattle.gd
# =============================================================================
extends SceneTree


# ── 表现钩子探针：CoreHooks 默认全空实现，这里只数事件，不改变任何判定 ──
# 计数口径全部取「只可能由战斗判定路径触发」的钩子（见 CoreHooks.gd 分区注释）。
class HookProbe extends CoreHooks:
	var activations := 0        # 物品触发一次冷却效果（ItemMetrics.Activations 埋点）
	var damage_events := 0      # 扣血飘字（DealDamage/CriticalDamage/Fatigue/Poison/Spikes）
	var damage_sum := 0.0       # 扣血绝对值累计
	var heal_events := 0        # 治疗飘字（EventType.Health）—— 与扣血分开计
	var heal_sum := 0.0
	# ★ 其中起源是**宝石**的治疗。这是「Socket 折叠链真的通到效果」的唯一硬证据：
	#   Ruby.prepareWeapon → connectForCombat(宿主,"attacked") → onAttack → heal(…, self)
	#   故 heal 的 origin 就是那颗宝石本身（CoreItem.heal 把 self 传进 character().heal）。
	#   此前 gem_test 阵容虽被 SKIP，但它「零报错」曾被误读成「宝石没问题」——
	#   而零报错只说明**没走进宝石代码**，说明不了效果。
	var gem_heals := 0
	var gem_heal_sum := 0.0
	var fatigue_ticks := 0      # 疲劳跳伤（playFatigueAnimation）
	var stuns := 0              # 眩晕（playStunAnimation）

	# ★ 激活计数走**统计埋点**而不是动画钩子：原版 activate() 只在
	#   `animationOverride != null` 时才 playActivationAnimation（Item.gd:4721），
	#   常规触发那次播放不走它 —— 拿它计数会得到「act=0 但伤害照打」的假警报
	#   （闸门 8 首轮就这么误报 30 局）。而 `addMetric(ItemMetrics.Activations)`
	#   在每次激活的公共路径上无条件调用（Item.gd:4705 / CoreItem.gd:746）。
	func snapshotItemMetric(_item, metricIndex: int, _playerId = null,
			_withNextEvent: bool = false) -> void :
		if metricIndex == CoreConst.ItemMetrics.Activations:
			activations += 1

	# 伤害与治疗共用一个钩子入口，靠 EventType 分流（CoreCharacter.gd:483-496 发伤害、
	# :574 发治疗）。早先不分类，把治疗也算进 `dmg=`，宝石一旦生效反而会虚增伤害读数。
	func spawnLabel_character(_character, type, damage, item = null) -> void :
		if type == CoreConst.EventType.Health:
			heal_events += 1
			heal_sum += abs(float(damage))
			if item != null and item is CoreItem and item.isGem():
				gem_heals += 1
				gem_heal_sum += abs(float(damage))
		else:
			damage_events += 1
			damage_sum += abs(float(damage))

	func playFatigueAnimation(_name: String) -> void :
		fatigue_ticks += 1

	func playStunAnimation(_character, _duration) -> void :
		stuns += 1

	# ═══════════ 事件流 canonical 序列化（须与 tools/run_gd_py.py 逐字同构） ═══════════
	#
	# 用途：Task #9「双引擎逐事件对照」。两侧都只有一个事件汇点 ——
	# `CoreCombatLog.logEvent(event)` → `_ctx.hooks.logEvent(event)`。把每次调用压成
	# 一行稳定文本，两侧逐行比对，就能把「56 局摘要一致」升级成「每一次攻击 / 伤害 /
	# 治疗 / 层数 / 眩晕都一致」。
	#
	# ★ 为什么这比摘要强：两句不同的战斗可以有完全相同的
	#   win/t/php/ohp/act/dmg/heal/gem/fat/stun 摘要（某次伤害被挪后一拍、某个层数
	#   施加到了另一件物品）。摘要看不见，事件流看得见。
	# ★ 序列化器在两侧各写一遍（共享不了两种语言）。代价是可能出现「假不一致」
	#   —— 那会当场暴露、人工归因即可；真正的风险是「假一致」，故格式里塞进足够
	#   多字段：事件号 / 类型 / 父链深度 / 起源身份 / 目标 / 全部参数键值。
	# ★ 分隔符选择：**字段**分隔符是 `|`，故 origin / params 值的**内部**绝不能用 `|`。
	#   早先写成 `it:<名字>|<ownerType>|<格>`，结果一行被拆成 8 段、解析直接失败
	#   （而且失败得很安静：整批差异都被归成「格式不可解析」）。键内一律用 `~`。
	#   `gem(<宿主>~<插槽号>)` 同理。

	var event_lines = null     # null = 不记；数组 = 记 canonical 行

	# 占格坐标规范串：按 (x,y) 升序，`x,y` 以 `;` 相连；无格记 `-`
	func _ecells(item) -> String:
		var cells := []
		for c in item.occupiedCells:
			cells.push_back([int(c.x), int(c.y)])
		# 手写插入排序（x 再 y）：避免 sort_custom 需要传入比较器对象
		for i in range(1, cells.size()):
			var cur = cells[i]
			var j := i - 1
			while j >= 0 and (cells[j][0] > cur[0]
					or (cells[j][0] == cur[0] and cells[j][1] > cur[1])):
				cells[j + 1] = cells[j]
				j -= 1
			cells[j + 1] = cur
		var parts := PoolStringArray()
		for c in cells:
			parts.push_back("%d,%d" % [c[0], c[1]])
		if parts.size() == 0:
			return "-"
		return parts.join(";")

	# 把 origin / params 值压成稳定短串
	# ★ 宝石的特殊处理：`setGem` 把插座身份折叠成宿主物品本身
	#   （`gem.socket = self`、`host.gems[socketId] = gem`），宝石自己
	#   `occupiedCells` 被清空 → 单靠名字+格无法区分同名的两颗宝石。
	#   故宝石记成 `gem(<宿主身份>#<插槽号>)`，宿主身份递归复用同一函数。
	#   `socket` 只声明在 Gems/Gem.gd:4，非宝石 `get("socket")` 返回 null。
	func _ekey(o) -> String:
		if o == null:
			return "-"
		if o is bool:
			return "T" if o else "F"
		if o is int:
			return "i%d" % o
		if o is float:
			return "%.6f" % o
		var sock = o.get("socket")
		if sock != null:
			var sid := -1
			var gs = sock.get("gems")
			if gs != null:
				for i in range(gs.size()):
					if gs[i] == o:
						sid = i
						break
			return "gem(%s~%d)" % [_ekey(sock), sid]
		if o is CoreItem:
			return "it:%s~%d~%s" % [o.getName(), o.ownerType, _ecells(o)]
		# 预料外的类型：有名字就带名字，否则只记 `?`。
		# ★ 实测（56 局全部事件）origin 只有 int 与物品两类、params 只有 int/float/bool
		#   三类，走不到这里；留着是为了「出现新类型时不要静默变成同一串」。
		if o.has_method("getName"):
			return "ob:%s" % o.getName()
		return "?"

	# 单条事件 → 一行文本：`id|type|depth|origin|target|params`
	func _eline(event) -> String:
		var keys: Array = event.params.keys()
		keys.sort()
		var parts := PoolStringArray()
		for k in keys:
			parts.push_back("%s=%s" % [k, _ekey(event.params[k])])
		return "%d|%d|%d|%s|%s|%s" % [event.id, event.getType(), event.getDepth(),
				_ekey(event.getOrigin()), _ekey(event.target), parts.join(",")]

	# 事件流记录（51 个钩子里的第 51 个）
	# ★ 这是逐事件对照的取样点：原版的**每一个**战斗事件（攻击 / 伤害 / 治疗 /
	#   层数增减 / 眩晕 / 激活 / 疲劳 …）都经这里过一遍，故这一处就覆盖了整条
	#   判定路径的输出面。
	func logEvent(event) -> void :
		if event_lines != null:
			event_lines.push_back(_eline(event))


# 运行参数
const BASE_SEED := 20260923
const PAIR_STRIDE := 101
const TIME_LIMIT := 180.0        # 对齐 CoreCombat.max_time

# ★ 宝石阵容已解锁（原 SKIP 理由经实证为陈旧）：Socket 门面在内核里不是「缺」，
#   而是**折叠**——插座身份整体落到宿主物品上（CoreItem.setGem 把 self 当 socket，
#   GemSocket.getItem() 的语义由 CoreItem.getItem() 返回 self 承担）。
#   战斗路径上宝石只经 `socket.getItem()` 访问宿主，折叠后语义完整；
#   其余 `socket.onPickupGem()` / `socket.gem = null` 之类全在拖拽/丢弃路径上。
#   装配链走 `CoreItem.setGem`（＝原版 setGem + addToSocket 的战斗相关三条），
#   `setGemData` 是**存档序列化**、`initSockets` 是**后置条件恒真的回指**，两者本就不参与战斗。
const SKIPPED := {}

var failures: Array = []
var _report: Array = []
var _rows: Array = []


func say(line: String) -> void:
	print(line)
	_report.push_back(line)
	var fh = File.new()
	if fh.open("res://lineup_result.txt", File.WRITE) == OK:
		fh.store_string(PoolStringArray(_report).join("\n") + "\n")
		fh.close()


func check(cond: bool, what: String) -> void:
	if not cond:
		failures.push_back(what)


func _init() -> void:
	say("")
	say("=== gd_core 真实阵容端到端验证 ===")
	print("LINEUP: start")

	test_fixture_shape()
	print("LINEUP: shape done")
	test_assemble_once()
	print("LINEUP: assemble done")
	test_all_pairs()
	print("LINEUP: pairs done")
	test_determinism()
	print("LINEUP: determinism done")
	test_gem_effect()
	print("LINEUP: gem done")

	say("")
	if failures.empty():
		say("LINEUP: PASS")
	else:
		for f in failures:
			say("LINEUP: FAIL  " + f)
		say("LINEUP: FAIL (%d 项)" % failures.size())

	quit(0 if failures.empty() else 1)


# ─────────────────────────── 装配辅助 ───────────────────────────

func v(cell: Array) -> Vector2:
	# 夹具里的格是 [col, row]（与 tscn 的 (x,y) 同序）；内核向量是 Vector2(x=col, y=row)
	return Vector2(int(cell[0]), int(cell[1]))


func vlist(cells: Array) -> Array:
	var out := []
	for c in cells:
		out.push_back(v(c))
	return out


func live_lineups() -> Array:
	var names := []
	for k in LineupFixture.LINEUPS.keys():
		if not SKIPPED.has(k):
			names.push_back(k)
	names.sort()
	return names


func new_character(ctx, pid: int, lu: Dictionary) -> CoreCharacter:
	var c = CoreCharacter.new(ctx, pid)
	c.characterClass = int(lu["class"])
	c.setMaxHealth(int(lu["health"]))
	c.setCurrentHealth(int(lu["health"]))
	c.maxStamina = float(lu["stamina"])
	c.baseMaxStamina = float(lu["stamina"])
	c.baseStaminaRegen = float(lu["regen"])
	c.staminaRegen = float(lu["regen"])
	c.fillUpStamina()
	return c


# ★ 描述符**全局唯一**：原版所有同类型物品共享同一份 .tres（ItemDescriptor 资源），
#   Item.isA 靠引用相等判定，countAllPlacedOfType 等查询拿描述符当字典键。
#   故这里按 key 缓存实例，跨对局复用（ctx 每局重建，但描述符是纯静态数据）；
#   只把实例登记进当场的 item_book。写成「每次 build 都 new 一份」会让
#   同名物品在后一场被新实例覆盖注册表 —— 前一场那件的 isA 立刻判假
#   （闸门 8 首轮实测：Garlic 在双方阵容里都出现，就报出了这个）。
var _descr_cache := {}


func descriptor_of(ctx, key: String) -> CoreItemData:
	if _descr_cache.has(key):
		return ctx.item_book.register(_descr_cache[key])
	var d: Dictionary = LineupFixture.ITEMS[key]
	var made = CoreItemData.new().fromDict({
		"name": d["name"],
		"identifier": d["identifier"],
		"minDam": d["minDam"],
		"maxDam": d["maxDam"],
		"cd": d["cd"],
		"extraCds": d["extraCds"],
		"accuracy": d["accuracy"],
		"staminaCost": d["staminaCost"],
		"block": d["block"],
		"price": d["price"],
		"rarity": d["rarity"],
		"classes": d["classes"],
		"canActivate": d["canActivate"],
		"chance": d["chance"],
		"chance2": d["chance2"],
		"types": d["types"],
		"tags": d["tags"],
		"params": d["params"],
		"namedParams": d["namedParams"],
	})
	_descr_cache[key] = made
	return ctx.item_book.register(made)


# 装配一个物品（不入包）。返回 null 表示脚本加载失败。
# ── 脚本缓存 ──
# ★ 必须缓存：反复 load() 同一路径时 Godot 3.6 有概率报
#   `Condition "err" is true. Returned: err / Cannot load source code from file ...`
#   （实测 450 余次 load 里失败 82 次，且失败是随机的）。缓存后每个路径只真正
#   load 一次，既消除该噪声，也让每局的装配成本与阵容规模无关。
var _script_cache := {}


func script_of(path: String):
	if _script_cache.has(path):
		return _script_cache[path]
	var s = load(path)
	_script_cache[path] = s
	return s


func make_item(ctx, chr, e: Dictionary):
	var path: String = e["script"]
	var script_obj = script_of(path)
	if script_obj == null:
		failures.push_back("脚本无法加载：" + path)
		return null
	var it = script_obj.new()
	it.setup(ctx, descriptor_of(ctx, e["key"]), chr)
	# 插座数组按 socket 数建等长（原版 sockets = $Icon/Sockets.get_children()）
	var n := int(LineupFixture.ITEMS[e["key"]]["sockets"])
	for _i in range(n):
		it.gems.push_back(null)
	# 网格元数据（原版由 cacheCollisionCells() 从 TileMap 读；内核由装配层注入，
	# 见 CoreItem.cacheCollisionCells 的注释）
	it.collisionCells = vlist(e["collision"])
	var aff := {}
	for color in e["affected"].keys():
		aff[int(color)] = vlist(e["affected"][color])
	it.affectedTileCells = aff
	return it


func place_and_ready(ctx, chr, e: Dictionary, owner_type: int, with_gems := true):
	var it = make_item(ctx, chr, e)
	if it == null:
		return null
	it.occupiedCells = vlist(e["occupied"])
	it.ownerType = owner_type
	# 原版次序：物品入场景树时 _ready 先跑，随后 Inventory.addItem 才调 addToInventory
	it._readyInit()
	chr.inventory.addItem(it, it.occupiedCells)
	# 宝石在宿主入包之后才 setGem（对齐原版「先摆宿主、再 setGemData」的次序）
	if not with_gems:
		return it
	for gi in range((e["gems"] as Array).size()):
		var gkey: String = e["gems"][gi]
		var gd := {
			"key": gkey,
			"script": e["gemScripts"][gi],
			"collision": [[0, 0]],
			"affected": {},
			"occupied": [],
		}
		var gem = make_item(ctx, chr, gd)
		if gem == null:
			continue
		gem._readyInit()
		it.setGem(gi, gem)
	return it


func build_side(ctx, chr, lu: Dictionary, owner_type: int, with_gems := true) -> Array:
	var out := []
	for e in lu["items"]:
		if e["storage"]:
			continue          # 储物箱里的物品不参战（对齐原版：只装背包）
		var it = place_and_ready(ctx, chr, e, owner_type, with_gems)
		if it != null:
			out.push_back(it)
	return out


# 新建一局：返回 {ctx, p, o, combat, probe, p_items, o_items, time}
# `with_gems=false` 用于宝石实效的 A/B 对照（同种子、同摆盘，只去掉宝石）。
func new_battle(seed_value: int, p_name: String, o_name: String,
		with_gems := true, trace := false) -> Dictionary:
	# ★ trace 只打开 `event_lines` 记录，**不换 probe 类** —— 走的是与生产完全同一
	#   条装配路径，这样事件流取证才代表真正被验收的那个装配。
	var probe = HookProbe.new()
	if trace:
		probe.event_lines = []
	var ctx = CoreContext.new(seed_value, probe)
	var pla: Dictionary = LineupFixture.LINEUPS[p_name]
	var opp: Dictionary = LineupFixture.LINEUPS[o_name]
	var p = new_character(ctx, CoreCharacter.ID.PLAYER, pla)
	var o = new_character(ctx, CoreCharacter.ID.OPPONENT, opp)
	var combat = CoreCombat.new(ctx)
	combat.setup(p, o)
	# 物品要在 combat 就绪之后装（_readyInit 里 newItemTimer 等依赖 ctx.combat）
	var p_items = build_side(ctx, p, pla, CoreConst.Owner.PlayerInventory, with_gems)
	var o_items = build_side(ctx, o, opp, CoreConst.Owner.Opponent, with_gems)
	combat.startBattle(p_items, o_items)
	return {"ctx": ctx, "p": p, "o": o, "combat": combat, "probe": probe,
			"p_items": p_items, "o_items": o_items}


const MAX_TICKS := 20000


func run_battle(ctx, combat) -> void:
	var ticks := 0
	while not combat.fight_ended and ticks < MAX_TICKS:
		combat.physicsTick(CoreContext.PHYSICS_DELTA)
		ticks += 1


func winner_label(combat) -> String:
	# ★ winner 是**方法**（CoreCombat.gd:439 `func winner()`），写成 `combat.winner`
	#   会拿到 funcref 并报 Invalid get index（Gate 8 首轮就踩了）。
	var w = combat.winner()
	if w == null:
		return "draw"
	return "P" if w.playerId == CoreCharacter.ID.PLAYER else "O"


func outcome(w: Dictionary) -> String:
	var combat = w["combat"]
	var p = w["p"]
	var probe = w["probe"]
	return "win=%s t=%.2f php=%.0f ohp=%.0f act=%d dmg=%d/%s heal=%d/%s gem=%d/%s fat=%d stun=%d" % [
		winner_label(combat), combat.combat_time, p.curHealth,
		w["o"].curHealth, probe.activations, probe.damage_events,
		("%.1f" % probe.damage_sum), probe.heal_events,
		("%.1f" % probe.heal_sum), probe.gem_heals,
		("%.1f" % probe.gem_heal_sum), probe.fatigue_ticks, probe.stuns]


# ─────────────────────── 1. 夹具自检 ───────────────────────

func test_fixture_shape() -> void:
	say("")
	say("[1] 夹具自检：枚举已按 CoreConst 转成 int、几何已转成绝对格")

	check(LineupFixture.ITEMS.size() >= 16,
		"夹具物品数异常：%d" % LineupFixture.ITEMS.size())
	check(LineupFixture.LINEUPS.size() == 8,
		"夹具阵容数应为 8，实为 %d" % LineupFixture.LINEUPS.size())

	# types/tags 必须是 int（内核 hasType/hasTag 读的是 CoreConst 枚举）
	var bad := []
	for k in LineupFixture.ITEMS.keys():
		var d: Dictionary = LineupFixture.ITEMS[k]
		for t in d["types"]:
			if not (t is int):
				bad.push_back(k + ".types")
				break
		if not (d["tags"] is int):
			bad.push_back(k + ".tags")
	check(bad.empty(), "类型/标签未转成 int：" + str(bad))

	# 占格：必须落在背包内（7 行 × 10 列）、不得重复
	# ★ 坐标系 Vector2(x=col, y=row)：x 上限 10（列），y 上限 7（行）
	#   （2026-09-28 occupied 坐标修复后与 run_gd_py.py 同步）
	for name in LineupFixture.LINEUPS.keys():
		var lu: Dictionary = LineupFixture.LINEUPS[name]
		var seen := {}
		var out_of_bounds := 0
		for e in lu["items"]:
			for c in e["occupied"]:
				if int(c[0]) < 0 or int(c[0]) >= 10 or int(c[1]) < 0 or int(c[1]) >= 7:
					out_of_bounds += 1
				var k = str(c[0]) + "," + str(c[1])
				if seen.has(k):
					check(false, "阵容 %s 摆盘重叠于格 %s" % [name, k])
				seen[k] = true
		check(out_of_bounds == 0,
			"阵容 %s 有 %d 个占格越出 7×10 背包" % [name, out_of_bounds])

	var n_items := 0
	for name in LineupFixture.LINEUPS.keys():
		n_items += (LineupFixture.LINEUPS[name]["items"] as Array).size()
	say("    物品 %d / 阵容 %d / 摆盘件数 %d ✓（枚举 int 化 ✓、无重叠 ✓、不越界 ✓）"
		% [LineupFixture.ITEMS.size(), LineupFixture.LINEUPS.size(), n_items])


# ─────────────────────── 2. 单场装配自检 ───────────────────────

func test_assemble_once() -> void:
	say("")
	say("[2] 装配自检：物品脚本 / 网格 / 描述符 / 入包四条路径逐件走通")

	var names := live_lineups()
	check(names.size() >= 7, "可用阵容应 ≥ 7，实为 %d" % names.size())

	var w = new_battle(BASE_SEED, names[0], names[1])
	var ctx = w["ctx"]
	var p = w["p"]
	var lu: Dictionary = LineupFixture.LINEUPS[names[0]]

	check(w["p_items"].size() == lu["items"].size(),
		"玩家侧装配件数 %d 应等于阵容件数 %d"
		% [w["p_items"].size(), lu["items"].size()])

	for it in w["p_items"]:
		check(it != null, "装配出 null 物品")
		check(it.placed, "%s 应已入包（placed）" % it.getName())
		check(it.ownerType == CoreConst.Owner.PlayerInventory,
			"%s 的 ownerType 应为 PlayerInventory，实为 %d" % [it.getName(), it.ownerType])
		check(it.occupiedCells.size() > 0, "%s 应占至少 1 格" % it.getName())
		check(ctx.item_book.getDescriptor(it.getName()) == it.descriptor,
			"%s 的描述符应就是注册表里那一个实例（isA 前提）" % it.getName())
	for it in w["o_items"]:
		check(it.ownerType == CoreConst.Owner.Opponent,
			"对手侧 %s 的 ownerType 应为 Opponent，实为 %d" % [it.getName(), it.ownerType])

	say("    玩家 %d 件 / 对手 %d 件装配成功 ✓（placed ✓ / ownerType ✓ / 描述符身份 ✓）"
		% [w["p_items"].size(), w["o_items"].size()])


# ─────────────────────── 3. 全对局矩阵 ───────────────────────

func test_all_pairs() -> void:
	say("")
	say("[3] 全对局矩阵：%d 套阵容的两两对战（含每件物品确实参与）" % live_lineups().size())

	var names := live_lineups()
	var zero_act := []
	var timeouts := []
	var no_damage := []
	var trace := []
	for a in names:
		for b in names:
			if a == b:
				continue          # 自己打自己在对决矩阵里无信息量
			var seed_value = BASE_SEED + PAIR_STRIDE * names.find(a) + names.find(b)
			# ★ 开 trace：同一条生产装配路径，只多一次 push_back。
			#   事件流是 Task #9 逐事件对照的取样面（见 tools/compare_events.py）。
			var w = new_battle(seed_value, a, b, true, true)
			run_battle(w["ctx"], w["combat"])
			trace.push_back("## %s|%s|%d" % [a, b, seed_value])
			trace.append_array(w["probe"].event_lines)
			var probe = w["probe"]
			var row = "%s vs %s：%s" % [a.replace("lineup_", ""), b.replace("lineup_", ""),
									   outcome(w)]
			_rows.push_back(row)
			if not w["combat"].fight_ended:
				check(false, "对局未收场（超过 %d tick）：%s" % [MAX_TICKS, row])
				timeouts.push_back(row)
				continue
			if w["combat"].timed_out:
				timeouts.push_back(row)
			if probe.activations == 0:
				zero_act.push_back(row)
			if probe.damage_events == 0:
				no_damage.push_back(row)

	say("    已完成 %d 局" % _rows.size())
	for r in _rows:
		say("      " + r)
	check(timeouts.empty(), "有 %d 局靠 timed_out 兜底收场：%s"
		% [timeouts.size(), str(timeouts.slice(0, 3))])
	check(zero_act.empty(), "有 %d 局物品一次都没触发（行为没跑起来）：%s"
		% [zero_act.size(), str(zero_act.slice(0, 3))])
	check(no_damage.empty(), "有 %d 局没有任何伤害事件：%s"
		% [no_damage.size(), str(no_damage.slice(0, 3))])

	# ── 落事件轨迹（Task #9 逐事件对照的输入） ──
	# ★ 空轨迹必须是失败：若 logEvent 因任何原因没被调用（钩子没接上），文件会
	#   「生成成功且为空」，逐行对照就成了「0 = 0 通过」——典型的空断言。
	var n_ev := 0
	for ln in trace:
		if not ln.begins_with("##"):
			n_ev += 1
	check(n_ev > 0, "事件轨迹为空 —— logEvent 没被接上，逐事件对照会退化成空断言")
	var fh = File.new()
	if fh.open("res://event_trace.txt", File.WRITE) == OK:
		fh.store_string(PoolStringArray(trace).join("\n") + "\n")
		fh.close()
	say("    事件轨迹：%d 局 / %d 条事件 → gd_core_test/event_trace.txt"
		% [_rows.size(), n_ev])


# ─────────────────────── 4. 确定性 ───────────────────────

func test_determinism() -> void:
	say("")
	say("[4] 确定性：同种子重跑，赢家/血量/时长/事件计数须逐位一致")

	var names := live_lineups()
	var diff := []
	for i in range(names.size()):
		var a = names[i]
		var b = names[(i + 1) % names.size()]
		var seed_value = BASE_SEED + 7777 + i
		var r1 := []
		var r2 := []
		for rep in range(2):
			var w = new_battle(seed_value, a, b)
			run_battle(w["ctx"], w["combat"])
			var line = outcome(w)
			if rep == 0:
				r1 = [line, w["p"].curHealth, w["o"].curHealth, w["combat"].combat_time]
			else:
				r2 = [line, w["p"].curHealth, w["o"].curHealth, w["combat"].combat_time]
		if str(r1) != str(r2):
			diff.push_back("%s vs %s：%s ≠ %s" % [a, b, str(r1), str(r2)])
	check(diff.empty(), "有 %d 组同种子结果不一致：%s" % [diff.size(), str(diff.slice(0, 3))])
	say("    复跑 %d 组 ✓" % names.size())


# ─────────────────────── 5. 宝石实效（A/B 对照） ───────────────────────

func test_gem_effect() -> void:
	say("")
	say("[5] 宝石实效 A/B：同种子含宝石 / 去宝石，宝石必须真的产生治疗")

	# 宿主 Cursed Dagger 有 2 个插座、装 1 颗 Chipped Ruby（lifesteal_weapon = 7）。
	# 武器宿主 → 宝石走 Weapon 模式：Ruby.prepareWeapon 订阅宿主的 attacked，
	# 每次命中 → heal(ceil(伤害 × 7%))。
	var a_name := "lineup_gem_test"
	var b_name := "lineup_dagger_swarm"
	var seed_value := BASE_SEED + 9101

	var with_gem = new_battle(seed_value, a_name, b_name, true)
	run_battle(with_gem["ctx"], with_gem["combat"])
	var without_gem = new_battle(seed_value, a_name, b_name, false)
	run_battle(without_gem["ctx"], without_gem["combat"])

	var pa = with_gem["probe"]
	var pb = without_gem["probe"]
	var sa := outcome(with_gem)
	var sb := outcome(without_gem)
	say("    含宝石：%s" % sa)
	say("    去宝石：%s" % sb)

	# ① 对照局一次宝石治疗都不能有 —— 同时验证探针的归属判据（item.isGem()）没误伤
	check(pb.gem_heals == 0,
		"去宝石对照局不该有宝石治疗，实为 %d 次" % pb.gem_heals)

	# ② 含宝石侧必须真的治疗过。★ 这一条才是关键：宝石链路若断在任意一环
	#    （setGem 没接上 / getGemMode 判错 / prepareWeapon 没跑 / attacked 没派发），
	#    整场照样**零报错**地跑完，只有这个计数能揭穿它。
	check(pa.gem_heals > 0,
		"gem_test 的宝石一次都没治疗 —— 宝石效果静默失效")

	# ③ 每次宝石治疗的量必须 ≥ 1（公式 ceil(伤害 × 7%) 对任意正伤害都不小于 1）
	check(pa.gem_heal_sum >= float(pa.gem_heals),
		"宝石治疗合计 %.1f 小于 %d 次 × 1 HP —— 公式下界被破坏"
		% [pa.gem_heal_sum, pa.gem_heals])

	# ④ 宝石必须改变战局：治疗量非零，则我方治疗总量必然高于对照局
	check(pa.heal_events > pb.heal_events,
		"含宝石局治疗次数 %d 未高于对照局 %d —— 宝石治疗未进入角色结算"
		% [pa.heal_events, pb.heal_events])
	say("    宝石治疗 %d 次 / 合计 %.1f HP；对照局 0 次 ✓（治疗总数 %d > %d）"
		% [pa.gem_heals, pa.gem_heal_sum, pa.heal_events, pb.heal_events])
