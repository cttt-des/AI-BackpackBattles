# =============================================================================
# OracleAlignBattle.gd — 受控神谕三方对齐：gd_core(Godot) 侧批量重放
# （docs/oracle_workflow.md Phase 3；宿主 = tools/verify_oracle.py）
# =============================================================================
# 目的：对 output/oracle/fights/<case>/ 的每场神谕用例，用 gd_core 无头内核在
#   同 (阵容, seed) 下复现整场，导出与神谕 events.json **同 schema** 的事件流，
#   供 tools/verify_oracle.py 做三方逐行比对（oracle ↔ gd_core ↔ gd_core_py）。
#
# 与 TruthBattle.gd 的差异：
#   · 用例来自 res://oracle_align_cases.json（tools/gen_fixture_from_lineup.py
#     --oracle 生成，items 数组 = 神谕 lineups.json 的装配顺序），描述符表运行时
#     读 res://item_battle_fixture.json（同 ItemBattle.gd 的 int() 化口径）；
#   · ★ 激活顺序用**真 Godot 引擎机制**现场复刻神谕：原版开战前
#     duplicate → shuffle → sort_TriggerPriority（Game.gd:3011-3020）走引擎
#     全局链（docs/rng_truth.md §1.4-2），神谕在每场前 seed(S)（oracle_fight.gd
#     :537）。本脚本同样 seed(S) 后对**下标数组** shuffle（与神谕对物品数组
#     shuffle 的比较子结果序列完全一致 → 同一排列），再按 TriggerPriority
#     sort_custom（同一非稳定 introsort）→ 终序与神谕逐位相同；
#   · startBattle(…, preordered=true) 直通该终序（内核不 shuffle、不排序、
#     不消耗 ctx.rng —— gd_core/CoreCombat.gd 的对齐分支）；
#   · ctx.below_master = true（神谕实证：全新 persistent → rating 0 → Bronze，
#     output/oracle/fights/*/rng_log.txt 的 randf_range(0.975,1.05) 分支）；
#   · ctx.cur_round = 回合数（LevelUp.onPrepare 消费，对齐原版 Game.curRound）；
#   · 事件捕获在 hooks.logEvent 处按 ctx.fight_ended 闸断（对齐原版
#     CombatLog.gd:266-267 logEvent 的 fightEnded 早退：判胜后事件不再入日志，
#     但 id 照常被 createEvent 消耗——神谕 dump 的 id 空洞即此来源）；
#   · 判胜后补一条合成的 Win/Loss 终局事件（对齐原版 CombatLog.onCombatEnd →
#     logWin/logLoss(afterFightAllowed=true)，oracle/Core/CombatLog.gd:194-204；
#     id 取 ctx.combat_log.eventNum+1，即「该场下一个 createEvent 的 id」——
#     与神谕同一分配器，事件数逐位同链时 id 也一致）。
#
# 运行（全程无头）：
#   output/godot36/Godot_v3.6-stable_win64.exe --headless --path gd_core_test \
#       --script OracleAlignBattle.gd
# 环境变量：
#   ORACLE_ALIGN_OUT      输出目录（默认 <repo>/output/oracle/align/gdcore）
#   ORACLE_ALIGN_LIMIT    只跑前 N 场（冒烟）
#   ORACLE_ALIGN_CHUNK    本进程最多跑 N 场即优雅退出（断点续跑）
#   ORACLE_ALIGN_SELFCHECK=1  首场跑完立即同种子复跑逐字节自证（默认开）
# 断点续跑（幂等）：<out>/<case_id>/events.json 已存在且 event_count>0 → 跳过。
# =============================================================================
extends SceneTree

const MAX_TICKS := 5400          # 90s 游戏时间（与神谕 MAX_TICKS 同值）
const MAX_TIME := 90.0
# ★（阶段2）旧 ORACLE_SCENE_DRAWS=14 校准常数已删除：它是 run579_r18 单场拟合的
#   「装配期不可见消耗」补丁，全量 917 场实测装配差为 0..444 步（非常数）。
#   真实构成已逻辑一致还原进内核（output/_probe_assembly_steps.py 逐场零残差）：
#     · 物品/宝石实例 = 场景双绑定 2×BalancedRng = 4 步（CoreItem.setup，Item.gd:472
#       经 Item.tscn/Gem.tscn 根绑定 + 覆盖脚本重绑定各跑一遍成员初始化器）；
#     · FlickerAnimation 子节点物品入树 +2 步（CoreItem._readyInit，
#       Items/Animations/FlickerAnimation.gd:13-15 的 callDelayed 实参求值）；
#     · 对手 Character 实例化 4×BalancedRng = 8 步（Character.gd:94-97，
#       神谕在播种后实例化对手——内核同序）；
#     · Character.tscn 场景图 _ready 面实测 0 步（stage 探针 stage6）。


# ── 事件捕获探针：logEvent 是内核唯一事件出口（CoreCombatLog.logEvent →
#    ctx.hooks.logEvent / CoreEventBus.emitAndLog 亦同）。序列化成神谕
#    events.json 的同 schema 记录（oracle_fight.gd::dump_events 同构）。 ──
class CaptureProbe extends CoreHooks:
	var rows := []              # 序列化事件记录（Dictionary）
	var gate_ctx = null         # 开战后赋值；fight_ended 后不再收（对齐原版闸）

	func logEvent(event) -> void :
		if gate_ctx != null and bool(gate_ctx.fight_ended):
			return              # 原版 CombatLog.logEvent 的 fightEnded 早退（:266-267）
		if event != null:
			rows.append(_record(event))

	func _record(event) -> Dictionary:
		var parent_id := - 1
		if event.parentEvent != null:
			parent_id = int(event.parentEvent.id)
		var tn := String(event.getType())
		var etk = gate_ctx.event_type_keys
		if etk != null and etk.has(int(event.getType())):
			tn = String(etk[int(event.getType())])
		return {
			"id": int(event.id),
			"type": int(event.getType()),
			"type_name": tn,
			"timestamp": float(event.timestamp),
			"origin": _j(event.getOrigin()),
			"target": _j(event.target),
			"parent_id": parent_id,
			"params": _j(event.params),
		}

	# oracle_fight.gd::_jsonable_impl 同构（宝石宿主折叠判据一致：先查 socket）
	func _j(o, depth: int = 0) :
		if o == null:
			return null
		if o is bool or o is int or o is float or o is String:
			return o
		if o is Vector2:
			return {"x": o.x, "y": o.y}
		if o is Dictionary:
			if depth > 6:
				return "…"
			var d = {}
			for k in o:
				d[String(k)] = _j(o[k], depth + 1)
			return d
		if o is Array:
			if depth > 6:
				return "…"
			var a = []
			for v in o:
				a.push_back(_j(v, depth + 1))
			return a
		var sock = o.get("socket")
		if sock != null:
			var sid := - 1
			var gs = sock.get("gems")
			if gs != null:
				for i in range(gs.size()):
					if gs[i] == o:
						sid = i
						break
			return {"kind": "gem", "host": _j(sock, depth + 1), "socket_index": sid}
		if o.has_method("getTopLeftCell") and "descriptor" in o:
			var tl = o.getTopLeftCell()
			return {"kind": "item", "name": String(o.getName()),
					"identifier": String(o.descriptor.identifier),
					"owner_type": int(o.ownerType),
					"top_left": {"x": tl.x, "y": tl.y}}
		if "playerId" in o:
			return {"kind": "character", "player_id": int(o.playerId)}
		if o.has_method("getName"):
			return {"kind": "object", "name": String(o.getName())}
		return {"kind": "unknown", "str": str(o).split(":")[0].substr(0, 80)}


# 下标排序器：与原版 Game.ItemSort.sort_TriggerPriority 同一比较子
# （item1.getTriggerPriority() > item2.getTriggerPriority()），作用于下标数组
# ——introsort 只由比较子结果驱动，对下标排序与对物品排序给出同一排列。
class IdxSort:
	var prio := []

	func by_trigger_priority(a, b) -> bool :
		return prio[int(a)] > prio[int(b)]


var _report := []
var _descr_cache := {}
var _script_cache := {}
var _table := {}            # item_battle_fixture.json
# 神谕语料根（每场 rng_state.txt 的来源）；_init 里填
var _fights_root := ""


func say(line: String) -> void :
	print(line)
	_report.push_back(line)


func vlist(cells: Array) -> Array:
	var out := []
	for c in cells:
		out.push_back(Vector2(int(c[0]), int(c[1])))
	return out


func descriptor_of(ctx, key: String) -> CoreItemData:
	# ★ 描述符全局唯一（Item.isA 靠引用相等；跨场复用同一实例）
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
		# 配方图（tools/enrich_recipes.py）：战斗语义只消费非空性
		#（isCraftedItem → Cog/Anvil 的 canAffect），CoreItemData.fromDict 原生读此键
		"originatingRecipes": d.get("originatingRecipes", []),
		# 攻击动画场景（tools/enrich_animation_scene.py）：playAnimation 的闸
		"animationScene": bool(d.get("animationScene", false)),
		# FlickerAnimation 子节点（tools/enrich_flicker_animation.py，阶段2 装配期
		# 对齐）：入树 +2 步 + 战斗期 playAni +2 步（CoreItem._readyInit/flickerPlayAni）
		"flickerAni": bool(d.get("flickerAni", false)),
		"flickerMinDist": float(d.get("flickerMinDist", 0.1)),
		"flickerMaxDist": float(d.get("flickerMaxDist", 3.0)),
		"flickerMinSpeed": float(d.get("flickerMinSpeed", 0.3)),
		"flickerMaxSpeed": float(d.get("flickerMaxSpeed", 1.0)),
		# 连接器/宝石 _ready 抽（同阶段2 装配期对齐，消费点 CoreItem._readyInit）
		"connectorReadyRoll": bool(d.get("connectorReadyRoll", false)),
		"gemRoll": bool(d.get("gemRoll", false)),
	})
	_descr_cache[key] = made
	return ctx.item_book.register(made)


func iarr(a: Array) -> Array:
	var out := []
	for x in a:
		out.push_back(int(x))
	return out


func script_of(path: String):
	if _script_cache.has(path):
		return _script_cache[path]
	var s = load(path)
	_script_cache[path] = s
	return s


func new_character(ctx, pid: int, side: Dictionary) -> CoreCharacter:
	var c = CoreCharacter.new(ctx, pid)
	c.characterClass = int(side["class"])
	c.setMaxHealth(int(side["health"]))
	c.setCurrentHealth(int(side["health"]))
	c.maxStamina = float(side["stamina"])
	c.baseMaxStamina = float(side["base_max_stamina"])
	c.baseStaminaRegen = float(side["regen"])
	c.staminaRegen = float(side["regen"])
	c.fillUpStamina()
	return c


# 装配一件物品并入包（装配序 = 夹具 items 数组顺序）。失败返回 null。
func place_one(ctx, chr, entry: Dictionary, owner_type: int):
	var key: String = entry["key"]
	var path: String = entry["script"]
	var script_obj = script_of(path)
	if script_obj == null:
		say("FAIL 脚本无法加载：%s（物品 %s）" % [path, key])
		return null
	var it = script_obj.new()
	if it.get_script() == null or it.get_script().resource_path != path:
		say("FAIL 脚本不匹配：%s（物品 %s）" % [path, key])
		return null
	it.setup(ctx, descriptor_of(ctx, key), chr)
	for _i in range(int(_table["items"][key]["sockets"])):
		it.gems.push_back(null)
	it.collisionCells = vlist(entry["collision"])
	var aff := {}
	for color in entry["affected"].keys():
		aff[int(color)] = vlist(entry["affected"][color])
	it.affectedTileCells = aff
	it.occupiedCells = vlist(entry["occupied"])
	it.ownerType = owner_type
	# ★ 朝向（战斗判定输入，CoreConst.FaceDirection 0..3 = 顺时针 1/4 圈）：
	#   夹具条目的 rotation 是度数（gen_fixture_from_lineup.py 由神谕 face_direction
	#   ×90 得到）。此前内核恒 UP——电荷路径（Battery.chargeCells 等**本地格**
	#   常量，经 Item.getGlobalPointsForCells 的节点旋转变换映射进背包）与
	#   SpintoWin/LongSpear/RainbowPotion 的朝向分流全部按 0° 计算。
	it.faceDirection = int(entry["rotation"]) / 90
	# 原版次序：_ready 先于 addItem；宝石在宿主入包之后 setGem
	it._readyInit()
	chr.inventory.addItem(it, it.occupiedCells)
	for gi in range((entry["gems"] as Array).size()):
		var g = entry["gems"][gi]
		if g == null:
			continue
		var gem = place_gem(ctx, chr, g, owner_type)
		if gem != null:
			it.setGem(gi, gem)
	return it


func place_gem(ctx, chr, g: Dictionary, owner_type: int):
	var key: String = g["key"]
	var script_obj = script_of(g["script"])
	if script_obj == null:
		say("FAIL 宝石脚本无法加载：%s（%s）" % [g["script"], key])
		return null
	var gem = script_obj.new()
	gem.setup(ctx, descriptor_of(ctx, key), chr)
	for _i in range(int(_table["items"][key]["sockets"])):
		gem.gems.push_back(null)
	gem.collisionCells = [Vector2(0, 0)]
	gem.affectedTileCells = {}
	gem.occupiedCells = []
	gem.ownerType = owner_type
	gem._readyInit()
	return gem


# ★ 激活顺序复刻（与 oracle_fight.gd:589-595 逐机制等价）：
#   seed(S) → playerItems.shuffle() → sort_TriggerPriority
#          → opponentItems.shuffle() → sort_TriggerPriority
#   全局链只有这一个播种点、两条 shuffle 连续消费——下标数组版与物品数组版
#   的链消耗与比较子结果序列完全一致（shuffle 不看元素内容）。
func activation_order(seed_value: int, p_items: Array, o_items: Array) -> Dictionary:
	seed(seed_value)
	var p_idx := []
	for i in range(p_items.size()):
		p_idx.push_back(i)
	var o_idx := []
	for i in range(o_items.size()):
		o_idx.push_back(i)
	var ps := IdxSort.new()
	for it in p_items:
		ps.prio.push_back(int(it.getTriggerPriority()))
	p_idx.shuffle()
	p_idx.sort_custom(ps, "by_trigger_priority")
	var os := IdxSort.new()
	for it in o_items:
		os.prio.push_back(int(it.getTriggerPriority()))
	o_idx.shuffle()
	o_idx.sort_custom(os, "by_trigger_priority")
	return {"player": p_idx, "opponent": o_idx}


func by_order(items: Array, order: Array) -> Array:
	var out := []
	for i in order:
		out.push_back(items[int(i)])
	return out


# ── ★ 阶段1 rng state 读取（docs/alignment_fix_workflow.md §2 阶段1）──────────
# 神谕在「战斗装配完成后、开战序列与首次 tick 之前」导出的
# output/oracle/fights/<case_id>/rng_state.txt（oracle_fight.gd，双 u64：
# seed=<get_seed()> / state=<Util.rng.state>）。GDScript int 是有符号 64 位
# 视角，state 为 u64 溢出时为负——Godot 的 state setter 直通 pcg.state 字
# （按 2^64 回绕），原值赋回去即逐位还原，无需手工归一。
# 返回空串 = 文件缺失（调用方 fail-fast：state 注入是阶段1 的判定前提，
# 静默退回 seed 重放会让「对齐」变成假阳性）。
func read_rng_state(case_id: String) -> String:
	var p = _fights_root.plus_file(case_id).plus_file("rng_state.txt")
	var fh = File.new()
	if not fh.file_exists(p):
		return ""
	fh.open(p, File.READ)
	var txt = fh.get_as_text()
	fh.close()
	for ln in txt.split("\n", false):
		if ln.begins_with("state="):
			return ln.substr(6)
	return ""


func run_case(c: Dictionary, out_root: String) -> Dictionary:
	var case_id: String = c["case_id"]
	var seed_value: int = int(c["seed"])
	var dir = out_root.plus_file(case_id)
	var res = {"status": "FAIL", "case_id": case_id, "seed": seed_value,
			"ticks": 0, "combat_time": 0.0, "events": 0, "winner": "-", "dir": dir}

	var probe = CaptureProbe.new()
	var ctx = CoreContext.new(seed_value, probe)
	probe.gate_ctx = ctx
	# 神谕约定（见文件头）：below_master=true + cur_round=回合数
	ctx.below_master = true
	ctx.cur_round = int(c["round_id"])

	# ★ 装配期链约定（对齐 oracle_fight.gd:505-537 的实证语义）：
	#   神谕复用 PLAYER（其角色构造的链消耗发生在本场播种前，被 seed 抹除），
	#   随后任何物品实例创建之前 Util.rng.seed = S。内核照做：先构造玩家角色
	#   （8 步 BalancedRng），再重播种抹掉它，然后补神谕场景装配的额外消耗，
	#   最后构造对手角色（神谕的对手场景在播种后实例化，消耗照常入链）。
	var trace_on := OS.get_environment("ORACLE_ALIGN_TRACE") != ""
	var p = new_character(ctx, CoreCharacter.ID.PLAYER, c["player"])
	ctx.rng.rng.seed = seed_value
	# ★ 逐抽追踪自播种即开启（阶段2）：装配期的每次链抽取都进 rng_trace.txt，
	#   与神谕 rng_log.txt（含装配期包装抽）做子序列值对齐用。
	if trace_on:
		ctx.rng.oracle_trace = true
	# （阶段2）播种后不再补空转：装配期消耗=内核物品双绑定+Flicker 入树+对手
	# 角色 8 步，已与神谕逐场零残差（见文件头 ORACLE_SCENE_DRAWS 删除说明）。
	# ★ 阶段3 次序修正（oracle_fight.gd:567-597 实证）：播种后的装配次序必须是
	#   「玩家物品（startHistoryRun:2711 createFromItemTuples，post-seed）→
	#   对手角色（finishSwitchingToCombat:2581 opponentScene.instance()，8 步
	#   BalancedRng）→ 对手物品（initHistoryOpponent）」——此前对手角色的 8 步
	#   插在玩家物品之前，总步数虽同（阶段2 状态零残差），但每个装配抽取的
	#   **值**随链位漂移；入树抽取（Flicker/Connector/Gem）的值作为 callDelayed
	#   时长等侧效应泄漏进战斗期，注入后无法对齐（run1122_r11 逐抽对位实证：
	#   玩家 Oil Lamp 闪烁时长 2.586 vs 神谕 1.521）。
	var p_items := []
	for e in c["player"]["items"]:
		var it = place_one(ctx, p, e, CoreConst.Owner.PlayerInventory)
		if it == null:
			res["status"] = "assembly-fail"
			return res
		p_items.push_back(it)
	var o = new_character(ctx, CoreCharacter.ID.OPPONENT, c["opponent"])
	var combat = CoreCombat.new(ctx)
	combat.max_time = MAX_TIME
	combat.setup(p, o)
	var o_items := []
	for e in c["opponent"]["items"]:
		var it = place_one(ctx, o, e, CoreConst.Owner.Opponent)
		if it == null:
			res["status"] = "assembly-fail"
			return res
		o_items.push_back(it)

	var order := activation_order(seed_value, p_items, o_items)
	res["activation_order"] = order
	# ★ 阶段1 神谕 rng state 注入：装配（角色+物品实例）完成后、startBattle 的
	#   prepareItems/activateItems 与逐 tick 判定链之前，把神谕捕获的 Util.rng
	#   state 直灌内核（ctx.set_state → rng.state 直写，不前进不重播）——绕开
	#   装配期消耗差异，隔离战斗期。机制前提：两侧 prepareItems 同点把全部
	#   BalancedRng 重置归零（原版 Item.gd:3345-3351 / Character.gd:294-317；
	#   内核 CoreItem.gd:531 / CoreCharacter.gd:259），链 state 唯一决定后续掷点。
	# ★ 阶段2 无注入模式（ORACLE_ALIGN_NO_INJECT=1）：不读 rng_state.txt、不
	#   set_state——装配期消耗面已与神谕逐场零残差，从 seed 起跑整条链即为
	#   阶段2 的判定本体（docs/alignment_fix_workflow.md §2 阶段2 退出标准）。
	#   默认关 = 阶段1 注入行为不变。
	var no_inject := OS.get_environment("ORACLE_ALIGN_NO_INJECT") != ""
	if no_inject:
		res["rng_state_injected"] = false
	else:
		var rng_state_txt := read_rng_state(case_id)
		if rng_state_txt.empty():
			say("FAIL %s 缺 rng_state.txt（%s）——先重跑神谕批量补导出"
					% [case_id, _fights_root])
			res["status"] = "missing-rng-state"
			return res
		ctx.set_state(int(rng_state_txt))

	# 物品要在 combat.setup() 之后装；preordered=true 直通激活顺序
	# ★ 阶段2 装配对齐探针（ORACLE_ALIGN_DUMP_STATE=1）：无注入模式下把
	#   startBattle 前的链状态落盘，与神谕 rng_state.txt 直接对表——
	#   逐位一致 = 装配期消耗面（次数+次序合并效果）完全等价。
	if OS.get_environment("ORACLE_ALIGN_DUMP_STATE") != "":
		var d2 = Directory.new()
		if not d2.dir_exists(dir):
			d2.make_dir_recursive(dir)
		var sf = File.new()
		sf.open(dir.plus_file("kernel_state.txt"), File.WRITE)
		sf.store_string("seed=%d" % ctx.rng.rng.get_seed())
		sf.store_string("state=%d" % ctx.rng.rng.state)

		sf.close()
	combat.startBattle(by_order(p_items, order["player"]),
			by_order(o_items, order["opponent"]), true)

	var ticks := 0
	var tick_states := []
	while not combat.fight_ended and ticks < MAX_TICKS:
		combat.physicsTick(CoreContext.PHYSICS_DELTA)
		ticks += 1
		# ★ 逐 tick 链状态（与神谕 oracle_fight.gd 的 _cur_tick_states 同构：
		#   每物理 tick 结束时的 Util.rng.state）——跨引擎「首个分叉 tick」
		#   定位用（ORACLE_ALIGN_TICKS=1 时落盘）。
		if trace_on:
			tick_states.push_back(ctx.rng.rng.state)
	res["ticks"] = ticks
	res["combat_time"] = float(combat.combat_time)
	res["fight_ended"] = bool(combat.fight_ended)
	res["timed_out"] = bool(combat.timed_out)
	res["player_hp"] = float(p.curHealth)
	res["player_max_hp"] = float(p.maxHealth)
	res["opponent_hp"] = float(o.curHealth)
	res["opponent_max_hp"] = float(o.maxHealth)

	if combat.fight_ended:
		var w = combat.winner()
		res["winner"] = "player" if w.playerId == CoreCharacter.ID.PLAYER else "opponent"
		# 合成终局事件（对齐原版 CombatLog.onCombatEnd → logWin/logLoss：
		# afterFightAllowed=true 绕过 fightEnded 闸；id = 下一个 createEvent 的 id）
		var is_win: bool = res["winner"] == "player"
		var etype: int = 111 if is_win else 112
		probe.rows.append({
			"id": int(ctx.combat_log.eventNum) + 1,
			"type": etype,
			"type_name": "Win" if is_win else "Loss",
			"timestamp": float(combat.combat_time),
			"origin": etype,
			"target": null,
			"parent_id": - 1,
			"params": {},
		})
	else:
		res["status"] = "timeout"

	res["events"] = probe.rows.size()
	if probe.rows.empty():
		res["status"] = "no-events"

	var d = Directory.new()
	if not d.dir_exists(dir):
		d.make_dir_recursive(dir)
	var fh = File.new()
	var payload = {
		"case_id": case_id, "seed": seed_value, "round_id": int(c["round_id"]),
		"below_master": true, "preordered": true,
		"rng_state_injected": not no_inject,
		"no_inject": no_inject,
		"combat_time": res["combat_time"], "ticks": res["ticks"],
		"fight_ended": res["fight_ended"], "timed_out": res["timed_out"],
		"winner": res["winner"],
		"player_hp": res["player_hp"], "player_max_hp": res["player_max_hp"],
		"opponent_hp": res["opponent_hp"], "opponent_max_hp": res["opponent_max_hp"],
		"activation_order": order,
		"event_count": probe.rows.size(), "events": probe.rows,
	}
	if fh.open(dir.plus_file("events.json"), File.WRITE) == OK:
		fh.store_string(JSON.print(payload, "  "))
		fh.close()
	else:
		res["status"] = "io-fail"
	if trace_on and not ctx.rng.oracle_trace_log.empty():
		var tf = File.new()
		if tf.open(dir.plus_file("rng_trace.txt"), File.WRITE) == OK:
			var rows := []
			for e in ctx.rng.oracle_trace_log:
				# 栈签名（ORACLE_ALIGN_STACKTRACE=1 时第 6 列）逐抽附调用方
				if e.size() > 5:
					rows.append("%d %s %s %s => %s | %s" % [e[0], e[1], e[2], e[3], e[4], e[5]])
				else:
					rows.append("%d %s %s %s => %s" % [e[0], e[1], e[2], e[3], e[4]])
			tf.store_string(PoolStringArray(rows).join("\n") + "\n")
			tf.close()
	if trace_on and not tick_states.empty():
		var sf = File.new()
		if sf.open(dir.plus_file("tick_states.txt"), File.WRITE) == OK:
			var srows := []
			for s in tick_states:
				srows.append(String(s))
			sf.store_string(PoolStringArray(srows).join("\n") + "\n")
			sf.close()
	if res["status"] == "FAIL":
		res["status"] = "ok"
	return res


func _init() -> void :
	say("ORACLE-ALIGN(gd_core): 受控神谕三方对齐——gd_core 侧批量重放（无头）")
	var t0 := OS.get_ticks_usec()

	var fh = File.new()
	if not fh.file_exists("res://oracle_align_cases.json"):
		say("FAIL 缺 res://oracle_align_cases.json（先跑 tools/gen_fixture_from_lineup.py --oracle）")
		quit(1)
		return
	fh.open("res://oracle_align_cases.json", File.READ)
	var parsed = parse_json(fh.get_as_text())
	fh.close()
	if typeof(parsed) != TYPE_DICTIONARY or not (parsed.get("cases", []) is Array):
		say("FAIL oracle_align_cases.json 格式错误")
		quit(1)
		return
	var cases: Array = parsed["cases"]

	# 可选定向（ORACLE_ALIGN_CASES=id1,id2,…）：只跑指定用例（保文件顺序）。
	# 阶段1 试点用（docs/alignment_fix_workflow.md §2）：按物品数选
	# 中位/最大/最小各一先做逐行比对。
	var only_ids := {}
	for only_id in OS.get_environment("ORACLE_ALIGN_CASES").split(",", false):
		only_ids[only_id] = true
	if not only_ids.empty():
		var only_kept: Array = []
		for c in cases:
			if only_ids.has(String(c["case_id"])):
				only_kept.push_back(c)
		cases = only_kept
		say("★ 定向：ORACLE_ALIGN_CASES → %d 场" % cases.size())

	var tf = File.new()
	tf.open("res://item_battle_fixture.json", File.READ)
	_table = parse_json(tf.get_as_text())
	tf.close()
	if _table == null or not _table.has("items"):
		say("FAIL item_battle_fixture.json 缺 items 表")
		quit(1)
		return

	var out_root = OS.get_environment("ORACLE_ALIGN_OUT")
	if out_root.empty():
		out_root = ProjectSettings.globalize_path("res://..").plus_file("output/oracle/align/gdcore")
	var d = Directory.new()
	if not d.dir_exists(out_root):
		d.make_dir_recursive(out_root)
	# 神谕语料根（rng_state.txt 来源）——gd_core_test 的 res://.. 即仓库根
	_fights_root = ProjectSettings.globalize_path("res://..").plus_file("output/oracle/fights")

	# 断点续跑（幂等）：events.json 已存在且 event_count>0 → 跳过
	var limit := int(OS.get_environment("ORACLE_ALIGN_LIMIT"))
	var chunk := int(OS.get_environment("ORACLE_ALIGN_CHUNK"))
	var pending: Array = []
	var skipped := 0
	for c in cases:
		if limit > 0 and pending.size() >= limit:
			break
		if case_done(out_root.plus_file(String(c["case_id"]))):
			skipped += 1
			continue
		pending.push_back(c)
	say("用例 %d 场（resume 跳过 %d，本进程待跑 %d）" % [cases.size(), skipped, pending.size()])

	var fails: Array = []
	var first_done := false
	var first_summary := ""
	var selfcheck := OS.get_environment("ORACLE_ALIGN_SELFCHECK") != "0"
	var run_here := 0
	for i in range(pending.size()):
		var c: Dictionary = pending[i]
		var t1 = OS.get_ticks_usec()
		var res = run_case(c, out_root)
		run_here += 1
		var ms = (OS.get_ticks_usec() - t1) / 1000.0
		var row = "[%4d/%d] %-16s %-8s ticks=%4d t=%6.2f ev=%5d %6.0f ms" % [
			i + 1, pending.size(), c["case_id"], res["status"], int(res["ticks"]),
			float(res["combat_time"]), int(res["events"]), ms]
		say("  " + row)
		if res["status"] != "ok":
			fails.append(String(c["case_id"]) + ": " + String(res["status"]))
		if not first_done and res["status"] == "ok":
			first_done = true
			if selfcheck:
				# 确定性自证：同种子紧邻复跑，事件 JSON 逐字节比对（神谕 [M7] 同款）
				var p1 = out_root.plus_file(String(c["case_id"])).plus_file("events.json")
				var f1 = File.new()
				f1.open(p1, File.READ)
				var first_text = f1.get_as_text()
				f1.close()
				var res2 = run_case(c, out_root)
				var f2 = File.new()
				f2.open(p1, File.READ)
				var second_text = f2.get_as_text()
				f2.close()
				if res2["status"] == "ok" and second_text == first_text:
					say("  [selfcheck] %s 同种子复跑逐字节一致 ✓" % String(c["case_id"]))
				else:
					fails.append(String(c["case_id"]) + ": selfcheck-复跑不一致")
					say("  [selfcheck] FAIL %s 复跑不一致（首跑留档见上）" % String(c["case_id"]))
				first_summary = "（selfcheck 已消耗一次复跑）"
		if chunk > 0 and run_here >= chunk:
			say("[chunk] 本进程配额 %d 场已满，优雅退出；重跑自动续接" % chunk)
			break

	var secs = (OS.get_ticks_usec() - t0) / 1000000.0
	var ok := fails.empty()
	say("")
	say("ORACLE-ALIGN(gd_core): %s（实跑 %d 场，跳过 %d，用时 %.1fs%s）"
			% ["PASS" if ok else "FAIL", run_here, skipped, secs, first_summary])
	for f in fails:
		say("  - " + f)
	var rf = File.new()
	if rf.open(out_root.plus_file("_align_gd_summary.txt"), File.WRITE) == OK:
		rf.store_string(PoolStringArray(_report).join("\n") + "\n")
		rf.close()
	quit(0 if ok else 1)


# 断点续跑判据：events.json 存在且 event_count>0
func case_done(dir: String) -> bool :
	var fh = File.new()
	var p = dir.plus_file("events.json")
	if not fh.file_exists(p):
		return false
	fh.open(p, File.READ)
	var txt = fh.get_as_text()
	fh.close()
	if txt.empty():
		return false
	var parsed = parse_json(txt)
	if typeof(parsed) != TYPE_DICTIONARY:
		return false
	return int(parsed.get("event_count", 0)) > 0
