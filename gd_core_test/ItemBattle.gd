# =============================================================================
# ItemBattle.gd — gd_core 全物品逐一上场验证（Godot 3.6 宿主）
# =============================================================================
# 闸门 8（LineupBattle）跑的是 8 套**真实阵容**，只覆盖 16 件物品；而转译产物有
# 502 件。本闸门补上剩下那一段：**每件物品各自打一场完整对局**。
#
# 为什么静态闸门替代不了它：
#   · 闸门 6（ItemParseAll）只证明脚本**解析得了**，证明不了「装上之后跑得起来」；
#   · 闸门 8 的真实阵容覆盖面太窄，某件物品特有的分支（罕用 API、少见的回调组合）
#     永远不会被触发；
#   · 而 Godot 3 遇到 `Nonexistent function` / `Invalid call` 只打一行 SCRIPT ERROR
#     就**中断当前函数继续跑**，退出码依然是 0 —— 于是「某行判定静默不执行」在
#     任何只看到「通过/失败」的闸门里都是隐形的，只有外层 stdout 扫描能抓（见
#     tools/run_gd_core.py 的 scan_errors）。
#   实测价值：本轮修掉 `has_node_modal` 的字符串误判后，保留面扩大了 13 个函数，
#   正是这道闸门把「新保留下来的语句引用了视觉变量」这类潜在运行期错误全量扫过。
#
# 每场对局的形态：**被测物品 1 件 vs 木剑假人 1 把**
#   · 对手给一把 Wooden Sword（1-3 伤 / cd 1.4 / 耗体力 1）而不是空手：
#     空手时被测物品的 onDamaged / onAttacked 这类**挨打侧**回调永不触发，
#     覆盖率凭空少一半；木剑又足够弱，不会在物品还没来得及触发时就结束对局。
#
# 断言（能报"失败"的只有这三类，其余靠外层 SCRIPT ERROR 扫描）：
#   1. 装配面  517 件全部实例化成功，且加载到的确实是夹具指定的那份脚本
#   2. 终止面  每场都在 tick 上限内自然收场（不靠 timed_out 兜底）
#   3. 参与面  被测物品确实在背包里（placed + ownerType + 占格非空）
#   输出里另附「0 次触发」清单 —— 那是**信息**不是失败：被动型物品本就可能不触发。
#
# 数据来源：item_battle_fixture.json（tools/gen_lineup_fixture.py 生成，含相对占格）
#
# 运行：
#   Godot_v3.6-stable_win64.exe --no-window --path gd_core_test --script ItemBattle.gd
# =============================================================================
extends SceneTree


# 只数「激活」这一个统计埋点。刻意不复用 LineupBattle 的 HookProbe：
# 那边还数伤害/疲劳/眩晕事件，本闸门 517 场跑下来那些计数只增加开销与输出体积。
class HookProbe extends CoreHooks:
	var activations := 0

	# ★ 计数走统计埋点而非动画钩子：原版 activate() 只在 `animationOverride != null`
	#   时才 playActivationAnimation（Item.gd:4721），常规触发那次不走它，拿它计数
	#   会得到「act=0 但伤害照打」的假警报。而 addMetric(ItemMetrics.Activations)
	#   在每次激活的公共路径上无条件调用（Item.gd:4705 / CoreItem.gd:746）。
	func snapshotItemMetric(_item, metricIndex: int, _playerId = null,
			_withNextEvent: bool = false) -> void :
		if metricIndex == CoreConst.ItemMetrics.Activations:
			activations += 1


const FIXTURE_PATH := "res://item_battle_fixture.json"
const DUMMY_KEY := "Wooden Sword"
const BASE_SEED := 20260924
const MAX_TICKS := 20000

# 角色基础属性：assets/characters.json 里 7 个职业**取值完全相同**（health 25 /
# stamina 5 / regen 1），故此处直接用该值，不必为一件事把整张表也灌进夹具。
# 职业取 Adventurer（只在 Classes_Full 里的兜底职业，对战斗无加成）。
const CHAR_HEALTH := 25
const CHAR_STAMINA := 5.0
const CHAR_REGEN := 1.0

var failures: Array = []
var _report: Array = []
var _table := {}
var _descr_cache := {}
var _script_cache := {}


func say(line: String) -> void:
	print(line)
	_report.push_back(line)
	var fh = File.new()
	if fh.open("res://item_battle_result.txt", File.WRITE) == OK:
		fh.store_string(PoolStringArray(_report).join("\n") + "\n")
		fh.close()


func check(cond: bool, what: String) -> void:
	if not cond:
		failures.push_back(what)


func _init() -> void:
	say("")
	say("=== gd_core 全物品逐一上场验证 ===")
	print("ITEMS: start")

	if not _load_fixture():
		say("ITEMS: FAIL 无法读取 " + FIXTURE_PATH)
		quit(1)
		return

	say("[1] 夹具：可上场物品 %d 件" % _table["items"].size())
	say("[2] 逐件上场：被测物品 1 件 vs 木剑假人 1 把")
	test_all_items()
	print("ITEMS: battles done")

	say("")
	if failures.empty():
		say("ITEMBATTLE: PASS")
	else:
		for f in failures:
			say("ITEMBATTLE: FAIL  " + f)
		say("ITEMBATTLE: FAIL (%d 项)" % failures.size())

	quit(0 if failures.empty() else 1)


func _load_fixture() -> bool:
	var fh = File.new()
	if fh.open(FIXTURE_PATH, File.READ) != OK:
		return false
	var parsed = parse_json(fh.get_as_text())
	fh.close()
	if parsed == null or not (parsed is Dictionary):
		return false
	_table = parsed
	return _table.has("items")


# ─────────────────────────── 装配辅助 ───────────────────────────

func v(cell: Array) -> Vector2:
	# 夹具里的格是 [col, row]（与 tscn 的 (x,y) 同序）；内核向量是 Vector2(x=col, y=row)。
	# ★ JSON 往返后数字全是 float，故必须显式取 int。
	return Vector2(int(cell[0]), int(cell[1]))


func vlist(cells: Array) -> Array:
	var out := []
	for c in cells:
		out.push_back(v(c))
	return out


func iarr(arr: Array) -> Array:
	var out := []
	for x in arr:
		out.push_back(int(x))
	return out


func script_of(path: String):
	# ★ 必须缓存：Godot 3.6 反复 load() 同一路径有概率报
	#   `Condition "err" is true / Cannot load source code from file ...`
	#   （闸门 8 实测 450 余次 load 里失败 82 次，且失败随机）。
	if _script_cache.has(path):
		return _script_cache[path]
	var s = load(path)
	_script_cache[path] = s
	return s


# ★ 描述符**全局唯一**：原版同类型物品共享同一份 .tres，Item.isA 靠引用相等判定。
#   跨对局复用同一实例（每局只把它登记进当场的 item_book），
#   否则同名物品在后一场会覆盖注册表，使前一场那件的 isA 立刻判假。
func descriptor_of(ctx, key: String) -> CoreItemData:
	if _descr_cache.has(key):
		return ctx.item_book.register(_descr_cache[key])
	var d: Dictionary = _table["items"][key]["descr"]
	var made = CoreItemData.new().fromDict({
		"name": d["name"],
		"identifier": d["identifier"],
		"minDam": int(d["minDam"]),
		"maxDam": int(d["maxDam"]),
		"cd": float(d["cd"]),
		"extraCds": d["extraCds"],
		"accuracy": float(d["accuracy"]),
		"staminaCost": float(d["staminaCost"]),
		"block": int(d["block"]),
		"price": int(d["price"]),
		"rarity": int(d["rarity"]),
		"classes": int(d["classes"]),
		"canActivate": bool(d["canActivate"]),
		"chance": float(d["chance"]),
		"chance2": float(d["chance2"]),
		"types": iarr(d["types"]),
		"tags": int(d["tags"]),
		"params": d["params"],
		"namedParams": d["namedParams"],
	})
	_descr_cache[key] = made
	return ctx.item_book.register(made)


func new_character(ctx, pid: int) -> CoreCharacter:
	var c = CoreCharacter.new(ctx, pid)
	c.characterClass = CoreConst.Classes_Full.Adventurer
	c.setMaxHealth(CHAR_HEALTH)
	c.setCurrentHealth(CHAR_HEALTH)
	c.maxStamina = CHAR_STAMINA
	c.baseMaxStamina = CHAR_STAMINA
	c.baseStaminaRegen = CHAR_REGEN
	c.staminaRegen = CHAR_REGEN
	c.fillUpStamina()
	return c


# 装配一件物品并入包。返回 null 表示脚本加载失败。
func place_one(ctx, chr, key: String, entry: Dictionary, owner_type: int):
	var path: String = entry["script"]
	var script_obj = script_of(path)
	if script_obj == null:
		check(false, "脚本无法加载：%s（物品 %s）" % [path, key])
		return null
	var it = script_obj.new()
	# ★ 校验加载到的确实是夹具指定的那份脚本：路径拼错时 load() 可能拿到别的脚本
	#   （同名 basename 存在于多个子目录），那样这一场测的就不是目标物品了。
	check(it.get_script() != null and it.get_script().resource_path == path,
		"%s 实际脚本 %s ≠ 期望 %s" % [key,
			"null" if it.get_script() == null else it.get_script().resource_path, path])
	it.setup(ctx, descriptor_of(ctx, key), chr)
	# 插座数组按 socket 数建等长（原版 sockets = $Icon/Sockets.get_children()）
	for _i in range(int(entry["sockets"])):
		it.gems.push_back(null)
	# 网格元数据（原版由 cacheCollisionCells() 从 TileMap 读；内核由装配层注入）
	it.collisionCells = vlist(entry["collision"])
	var aff := {}
	for color in entry["affected"].keys():
		aff[int(color)] = vlist(entry["affected"][color])
	it.affectedTileCells = aff
	it.occupiedCells = vlist(entry["occupied"])
	it.ownerType = owner_type
	# 原版次序：物品入场景树时 _ready 先跑，随后 Inventory.addItem 才调 addToInventory
	it._readyInit()
	chr.inventory.addItem(it, it.occupiedCells)
	return it


func new_battle(seed_value: int, key: String) -> Dictionary:
	var probe = HookProbe.new()
	var ctx = CoreContext.new(seed_value, probe)
	var p = new_character(ctx, CoreCharacter.ID.PLAYER)
	var o = new_character(ctx, CoreCharacter.ID.OPPONENT)
	var combat = CoreCombat.new(ctx)
	combat.setup(p, o)
	# 物品要在 combat 就绪之后装（_readyInit 里 newItemTimer 等依赖 ctx.combat）
	var p_items := []
	var it = place_one(ctx, p, key, _table["items"][key], CoreConst.Owner.PlayerInventory)
	if it != null:
		p_items.push_back(it)
	var o_items := []
	var dummy = place_one(ctx, o, DUMMY_KEY, _table["items"][DUMMY_KEY],
		CoreConst.Owner.Opponent)
	if dummy != null:
		o_items.push_back(dummy)
	combat.startBattle(p_items, o_items)
	return {"ctx": ctx, "p": p, "o": o, "combat": combat, "probe": probe,
			"p_items": p_items, "o_items": o_items, "item": it}


func run_battle(combat) -> void:
	var ticks := 0
	while not combat.fight_ended and ticks < MAX_TICKS:
		combat.physicsTick(CoreContext.PHYSICS_DELTA)
		ticks += 1


# ─────────────────────── 逐件上场 ───────────────────────

func test_all_items() -> void:
	var keys: Array = _table["items"].keys()
	keys.sort()
	check(_table["items"].has(DUMMY_KEY), "夹具缺少假人 " + DUMMY_KEY)
	check(not keys.empty(), "夹具里可上场物品为空")
	# JSON 往返后数字是 float，故按 int 比（`[0,0] == [0.0,0.0]` 在 Array 比较里
	# 不一定成立，GDScript 3 的 Array.== 对元素类型敏感）。
	var anchor: Array = _table["anchor"]
	check(int(anchor[0]) == 0 and int(anchor[1]) == 0,
		"锚点应为 (0,0)，实为 %s（换了锚点的话占格可能越界）" % str(anchor))

	var no_act := []
	var zero_act_count := 0
	var total_act := 0
	var max_act := 0
	var max_act_key := ""
	var dispatch_seen := 0
	for i in range(keys.size()):
		var key: String = keys[i]
		var w = new_battle(BASE_SEED + i * 7, key)
		var it = w["item"]
		if it == null:
			continue
		# 参与面：物品确实装进了背包
		check(it.placed, "%s 未入包（placed 为假）" % key)
		check(it.ownerType == CoreConst.Owner.PlayerInventory,
			"%s 的 ownerType 应为 PlayerInventory，实为 %d" % [key, it.ownerType])
		check(it.occupiedCells.size() > 0, "%s 应占至少 1 格" % key)
		check(w["p_items"].size() == 1, "%s 应恰好装配出 1 件" % key)
		check(w["o_items"].size() == 1, "假人 %s 应恰好装配出 1 件" % DUMMY_KEY)

		# 派发可达性：**物品实现的每个回调都必须被内核看见**。
		# ★ 为什么单独断言：接缝只认注入的 _behavior 对象，而没有任何物品脚本会拿到它，
		#   于是「脚本里写了 onCombatStart / onDealtDamage」与「内核真的会调它」是两件事。
		#   曾经两者不一致（98 件开场回调 + 21 件伤害回调静默不执行、零报错），
		#   而本闸门当时只断言「有激活」，激活来自 doCooldownEffect 的多态调用，
		#   压根不经过接缝 —— 全套闸门绿着放过了它。
		#   这里用 has_method（脚本事实）对比内核的派发判定，两侧必须逐项一致。
		for probe_name in ["onCombatStart", "onPreDealDamage_early", "onPreDealDamage_late",
				"onDealtDamage", "onChargeReceived", "onChargeLeft"]:
			if it.has_method(probe_name):
				dispatch_seen += 1
				check(it._hasBehaviorMethod(probe_name),
					"%s 实现了 %s，但内核派发判定看不见它（回调会静默不执行）"
					% [key, probe_name])
		# ★ 刻意**不**比较 hasStartofBattle() 与 has_method("onCombatStart")：
		#   MagicRing 一类物品会覆写 hasStartofBattle 判「本物品的 effectDict 里
		#   有没有 StartOfBattle 条目」（原版 Exclusive/MagicRing.gd:61-62），
		#   那是**正当的细化**，与基类的 has_method 语义本就不同。
		check(it.hasPreDealDamageEarlyEffect == it.has_method("onPreDealDamage_early"),
			"%s 的 hasPreDealDamageEarlyEffect 与 has_method 不一致" % key)
		check(it.hasDealtDamageEffect == it.has_method("onDealtDamage"),
			"%s 的 hasDealtDamageEffect 与 has_method 不一致" % key)
		check(it.hasOnChargeReceivedEffect == it.has_method("onChargeReceived"),
			"%s 的 hasOnChargeReceivedEffect 与 has_method 不一致" % key)

		run_battle(w["combat"])
		# 终止面：必须自然收场，不靠 MAX_TICKS 或 timed_out 兜底
		check(w["combat"].fight_ended,
			"%s 在 %d tick 内未收场" % [key, MAX_TICKS])
		check(not w["combat"].timed_out,
			"%s 靠 timed_out 兜底收场（时限内没能分出胜负）" % key)

		var a: int = w["probe"].activations
		total_act += a
		if a == 0:
			zero_act_count += 1
			no_act.push_back(key)
		elif a > max_act:
			max_act = a
			max_act_key = key

	say("    已跑 %d 场；本次结束方式全为自然收场 / 时限内 ✓" % keys.size())
	say("    触发合计 %d 次；触发最多 %s（%d 次）；0 次触发 %d 件（信息项，非失败）"
		% [total_act, max_act_key, max_act, zero_act_count])
	say("    回调实现数 %d 处（每处都须被内核派发判定看见）" % dispatch_seen)
	if not no_act.empty():
		# 只列前 40 件：被动型物品（盾/甲/静态加成）本就可能一次都不触发，
		# 这份清单是给人工扫一眼「有没有本该触发的漏网」，不是断言。
		say("    0 次触发清单（前 40）：" + ", ".join(no_act.slice(0, 40)))
