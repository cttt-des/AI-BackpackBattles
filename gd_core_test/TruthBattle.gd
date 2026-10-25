# =============================================================================
# TruthBattle.gd — 真值实录阵容复现（docs/consistency_workflow.md §3 Phase 1 / M2）
# =============================================================================
# 目的：三角定位黏黏龙骑士（Dragon Knight）正反馈问题。
#   把一组真值实录（CombatLog_20261001_220653_R19_Win）的双方阵容经
#   tools/gen_fixture_from_lineup.py → lineups/truth_*.json →
#   LineupFixture.gd（tools/gen_lineup_fixture.py 编译）装进无头内核，
#   同一条 LineupBattle 生产装配路径跑完整场，输出：
#     1. res://truth_result.txt —— HookProbe 计数（激活/伤害/治疗/宝石治疗/疲劳/眩晕）
#     2. res://truth_trace.txt  —— 逐事件轨迹（每行 t|id|type|depth|origin|target|params，
#        t = CoreCombatLog.getTimeStamp() 即 combat_time，含每次 DK 攻击的时间戳）
#   三方对照：真值事件流 ↔ 本轨迹 ↔ gd_core_py（python -m simulator.simulate）。
#
# 与 LineupBattle.gd 的差异：只跑一场、种子固定 42（与 Python 侧一致）、
#   轨迹行首加时间戳、不做夹具自检/矩阵/确定性/宝石 A/B。
#
# 运行（经 tools/run_truth_battle.py 包装）：
#   output/godot36/Godot_v3.6-stable_win64.exe --headless --path gd_core_test --script TruthBattle.gd
# =============================================================================
extends SceneTree

const SEED := 7
const P_NAME := "truth_20261001_220653_R19_player"
const O_NAME := "truth_20261001_220653_R19_opponent"
const MAX_TICKS := 20000          # 20000/60 ≈ 333s > CoreCombat.max_time(180s)


# ── 表现钩子探针：与 LineupBattle.gd 的 HookProbe 同构（计数口径一致），
#    轨迹行额外带时间戳 ──
class HookProbe extends CoreHooks:
	var activations := 0
	var damage_events := 0
	var damage_sum := 0.0
	var heal_events := 0
	var heal_sum := 0.0
	var gem_heals := 0
	var gem_heal_sum := 0.0
	var fatigue_ticks := 0
	var stuns := 0

	func snapshotItemMetric(_item, metricIndex: int, _playerId = null,
			_withNextEvent: bool = false) -> void :
		if metricIndex == CoreConst.ItemMetrics.Activations:
			activations += 1

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

	# ═══ 事件流 canonical 序列化（LineupBattle.gd::_eline 同构 + 行首时间戳） ═══
	var event_lines = null

	func _ecells(item) -> String:
		var cells := []
		for c in item.occupiedCells:
			cells.push_back([int(c.x), int(c.y)])
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

	func _ekey(o) -> String:
		if o == null:
			return "-"
		if o is bool:
			return "T" if o else "F"
		if o is int:
			return "i%d" % o
		if o is float:
			return "%.6f" % o
		# 真值大阵容的 params 里会出现 String（LineupBattle 的 8 套小阵容没有）；
		# String 没有 .get()，直接渲染，避免整条事件丢轨迹
		if o is String:
			return "s:" + o
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
		if o.has_method("getName"):
			return "ob:%s" % o.getName()
		return "?"

	# 行格式：`t|id|type|depth|origin|target|params`（t=%.3f 秒，combat_time）
	func _eline(event) -> String:
		var keys: Array = event.params.keys()
		keys.sort()
		var parts := PoolStringArray()
		for k in keys:
			parts.push_back("%s=%s" % [k, _ekey(event.params[k])])
		return "%.3f|%d|%d|%d|%s|%s|%s" % [float(event.timestamp), event.id,
				event.getType(), event.getDepth(),
				_ekey(event.getOrigin()), _ekey(event.target), parts.join(",")]

	func logEvent(event) -> void :
		if event_lines != null:
			event_lines.push_back(_eline(event))


var _report: Array = []
var _descr_cache := {}
var _script_cache := {}


func say(line: String) -> void:
	print(line)
	_report.push_back(line)


func v(cell: Array) -> Vector2:
	return Vector2(int(cell[0]), int(cell[1]))


func vlist(cells: Array) -> Array:
	var out := []
	for c in cells:
		out.push_back(v(c))
	return out


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


# 描述符全局唯一（对齐 LineupBattle.gd 的 _descr_cache 注释：isA 靠引用相等）
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


# 脚本缓存（对齐 LineupBattle.gd：反复 load 同一路径会随机失败）
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
		say("FAIL 脚本无法加载：" + path)
		return null
	var it = script_obj.new()
	it.setup(ctx, descriptor_of(ctx, e["key"]), chr)
	var n := int(LineupFixture.ITEMS[e["key"]]["sockets"])
	for _i in range(n):
		it.gems.push_back(null)
	it.collisionCells = vlist(e["collision"])
	var aff := {}
	for color in e["affected"].keys():
		aff[int(color)] = vlist(e["affected"][color])
	it.affectedTileCells = aff
	return it


func place_and_ready(ctx, chr, e: Dictionary, owner_type: int):
	var it = make_item(ctx, chr, e)
	if it == null:
		return null
	it.occupiedCells = vlist(e["occupied"])
	it.ownerType = owner_type
	it._readyInit()
	chr.inventory.addItem(it, it.occupiedCells)
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


func build_side(ctx, chr, lu: Dictionary, owner_type: int) -> Array:
	var out := []
	for e in lu["items"]:
		if e["storage"]:
			continue
		var it = place_and_ready(ctx, chr, e, owner_type)
		if it != null:
			out.push_back(it)
	return out


func new_battle(seed_value: int, p_name: String, o_name: String) -> Dictionary:
	var probe = HookProbe.new()
	probe.event_lines = []          # 开轨迹（生产装配路径不变）
	var ctx = CoreContext.new(seed_value, probe)
	var pla: Dictionary = LineupFixture.LINEUPS[p_name]
	var opp: Dictionary = LineupFixture.LINEUPS[o_name]
	var p = new_character(ctx, CoreCharacter.ID.PLAYER, pla)
	var o = new_character(ctx, CoreCharacter.ID.OPPONENT, opp)
	var combat = CoreCombat.new(ctx)
	combat.setup(p, o)
	# 物品要在 combat 就绪之后装（_readyInit 依赖 ctx.combat）
	var p_items = build_side(ctx, p, pla, CoreConst.Owner.PlayerInventory)
	var o_items = build_side(ctx, o, opp, CoreConst.Owner.Opponent)
	combat.startBattle(p_items, o_items)
	return {"ctx": ctx, "p": p, "o": o, "combat": combat, "probe": probe,
			"p_items": p_items, "o_items": o_items}


func run_battle(ctx, combat) -> int:
	var ticks := 0
	while not combat.fight_ended and ticks < MAX_TICKS:
		combat.physicsTick(CoreContext.PHYSICS_DELTA)
		ticks += 1
	return ticks


func winner_label(combat) -> String:
	# winner 是方法（CoreCombat.gd `func winner()`），同 LineupBattle.gd 的坑
	var w = combat.winner()
	if w == null:
		return "draw"
	return "P" if w.playerId == CoreCharacter.ID.PLAYER else "O"


func _init() -> void:
	say("=== TruthBattle：真值阵容复现（seed=%d，%s vs %s） ==="
			% [SEED, P_NAME, O_NAME])

	var ok := true
	var w = new_battle(SEED, P_NAME, O_NAME)
	var ticks = run_battle(w["ctx"], w["combat"])
	var probe = w["probe"]

	var n_ev := 0
	for ln in probe.event_lines:
		n_ev += 1
	say("result: win=%s t=%.2f ticks=%d fight_ended=%s timed_out=%s" %
			[winner_label(w["combat"]), float(w["combat"].combat_time), ticks,
			 str(bool(w["combat"].fight_ended)), str(bool(w["combat"].timed_out))])
	say("hp: P=%.0f/%.0f  O=%.0f/%.0f" %
			[float(w["p"].curHealth), float(w["p"].maxHealth),
			 float(w["o"].curHealth), float(w["o"].maxHealth)])
	say("probe: act=%d dmg=%d/%.1f heal=%d/%.1f gem=%d/%.1f fat=%d stun=%d events=%d" %
			[probe.activations, probe.damage_events, probe.damage_sum,
			 probe.heal_events, probe.heal_sum, probe.gem_heals,
			 probe.gem_heal_sum, probe.fatigue_ticks, probe.stuns, n_ev])

	# 空轨迹必须失败：logEvent 没接上时文件会「成功且为空」（对齐 LineupBattle.gd）
	if n_ev == 0:
		ok = false
		say("FAIL 事件轨迹为空 —— logEvent 没被接上")

	# 落轨迹（t|id|type|depth|origin|target|params）
	var fh = File.new()
	if fh.open("res://truth_trace.txt", File.WRITE) == OK:
		fh.store_string(PoolStringArray(probe.event_lines).join("\n") + "\n")
		fh.close()
		say("trace: %d 条事件 → gd_core_test/truth_trace.txt" % n_ev)
	else:
		ok = false
		say("FAIL 无法写 truth_trace.txt")

	var fh2 = File.new()
	if fh2.open("res://truth_result.txt", File.WRITE) == OK:
		fh2.store_string(PoolStringArray(_report).join("\n") + "\n")
		fh2.close()

	say("TRUTH: %s" % ("PASS" if ok else "FAIL"))
	quit(0 if ok else 1)
