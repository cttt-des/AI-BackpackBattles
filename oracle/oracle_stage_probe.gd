extends SceneTree
# =============================================================================
# oracle_stage_probe.gd — 阶段2 诊断探针（临时仪器，非交付物）：
# 复刻 oracle_fight.gd::run_case 的装配段，在每个装配阶段边界 dump Util.rng.state，
# 定位「静态清单（2/物品实例 + 8/对手角色）之外的额外链消耗」发生在哪一段。
# 全程无头、只读本地 history.db 快照副本、不加载 Main.tscn（红线同 oracle_fight.gd）。
# =============================================================================
var G = null
var U = null
var IB = null
var BHData = null
var RDScript = null
var ItemScript = null
var CT = null            # CombatTimer 节点（战斗时钟）
var dummy = null

var out_path := ""


class DummyBuildHistory:
	var isOpen := false
	var markedOpponentData = null
	var markedOpponentRound := - 1


func say(line: String) -> void :
	print(line)


func _initialize() -> void :
	# ★ oracle_fight.gd 同款：引导阶段 2（CombatLog 补挂、ItemLibrary 就位）完成于
	#   首个 physics_frame——_initialize 里 autoload onready 尚未就绪，不能直接跑。
	connect("physics_frame", self, "_on_physics_frame")


func _on_physics_frame() -> void :
	var boot = root.get_node_or_null("Main")
	if boot == null or not boot.fully_built or root.get_node("Game").PLAYER == null:
		return
	disconnect("physics_frame", self, "_on_physics_frame")
	_run_probe()


func _run_probe() -> void :
	print("[probe] _run_probe 开始")
	G = root.get_node("Game")
	U = root.get_node("Util")
	IB = root.get_node("ItemBook")
	BHData = load("res://Interface/BuildHistory/BuildHistoryData.gd")
	RDScript = load("res://Utility/RunData.gd")
	ItemScript = load("res://Items/Item.gd")
	CT = G.combatTimer
	dummy = DummyBuildHistory.new()
	# 用例从命令行环境变量取
	var cid := OS.get_environment("PROBE_CASE")
	var seed_value := int(OS.get_environment("PROBE_SEED"))
	var run_id := int(OS.get_environment("PROBE_RUN"))
	var round_id := int(OS.get_environment("PROBE_ROUND"))
	out_path = OS.get_environment("PROBE_OUT")

	G.setMode(G.Mode.History)
	G.itemLibrary = root.get_node("Main").G_itemLibrary
	G.SELLBOX = root.get_node("Main").G_SELLBOX
	G.STORAGEBOX = root.get_node("Main").G_STORAGEBOX
	G.buildHistory = dummy
	G.state = G.State.Combat

	var runs = load_history_runs()
	var player_run = runs[run_id]
	G.curHistoryData = player_run
	G.curRound = round_id
	G.wins = player_run.getWins(round_id - 1)
	G.losses = player_run.getLosses(round_id - 1)
	G.tries = G.MAX_TRIES if round_id == 1 else player_run.getTries(round_id - 1)
	var pool = root.get_node("ObjectPool")
	for key in pool.instances.keys():
		for inst in pool.instances[key]:
			if is_instance_valid(inst) and not inst.is_inside_tree():
				inst.free()
	pool.instances.clear()
	IB.preparedItemInstances.clear()
	IB.prepareQueue.clear()
	G.instanceCharacter(player_run.classI)
	G.get_node("/root/CustomRules").fromString(player_run.customRules)

	var lines: Array = []
	lines.append("stage0_pre_seed=%d" % U.rng.state)

	# ★ 播种（oracle_fight.gd:554-555 同点）
	U.rng.seed = seed_value
	seed(seed_value)
	lines.append("stage1_seeded=%d" % U.rng.state)

	var p_round = player_run.getRoundData(round_id)
	var p_deser = RDScript.deserializeItems(p_round.items, player_run.getVersionString())
	lines.append("stage2_deserialized=%d" % U.rng.state)
	var p_tuples = p_deser["items"]
	# ★ 显微切片：ItemScript.new() vs descriptor.instantiate() vs 裸场景 instance()
	# （步数差分在 Python 侧按 LCG 复算——这里只 dump 链态）
	var desc0 = p_tuples[0]["d"]
	lines.append("micro_begin=%d" % U.rng.state)
	var bare = ItemScript.new()
	lines.append("micro_itemscript_new=%d" % U.rng.state)
	bare.free()
	var inst0 = desc0.instantiate()
	lines.append("micro_desc_instantiate(%s)=%d" % [inst0.getName(), U.rng.state])
	inst0.free()
	var sc = load(desc0.scene.resource_path)
	var inst2 = sc.instance()
	lines.append("micro_scene_instance(%s)=%d" % [sc.resource_path, U.rng.state])
	inst2.free()
	var base_sc = load("res://Items/Item.tscn")
	var inst3 = base_sc.instance()
	lines.append("micro_baseitem_instance=%d" % U.rng.state)
	inst3.free()
	for sub_path in ["res://Items/Exclusive/GoldCounter.tscn",
			"res://Items/Tiles/BagBorder.tscn"]:
		var sub_sc = load(sub_path)
		var sub_inst = sub_sc.instance()
		lines.append("micro_sub(%s)=%d" % [sub_path, U.rng.state])
		sub_inst.free()
	# ★ 逐件内联 createFromItemTuples（Inventory.gd:1001-1030 逐行同序），打印每件后的链态
	G.PLAYER.INVENTORY.reset()
	p_tuples.sort_custom(G.ItemSort, "sort_BagOrder")
	for tuple in p_tuples:
		var descriptor = tuple["d"]
		var item = IB.instantiateItem(descriptor)
		lines.append("    sub instantiate(%s) = %d" % [item.getName(), U.rng.state])
		item.ownerType = ItemScript.Owner.PlayerInventory
		G.PLAYER.add_child(item)   # Inventory.itemNode = get_parent() = 角色节点
		lines.append("    sub add_child(%s) = %d" % [item.getName(), U.rng.state])
		item.setFaceDirectionInstant(tuple["f"])
		G.PLAYER.INVENTORY.orientItem(item, tuple["c"], tuple["f"])
		if not G.PLAYER.INVENTORY.canAddItemOrBag(item):
			print("[probe] overlapping item: ", item.getName())
		G.PLAYER.INVENTORY.addItemByTopLeft(item, tuple["c"])
		lines.append("    sub placed(%s) = %d" % [item.getName(), U.rng.state])
		if "g" in tuple:
			var gems = tuple["g"]
			for i in gems.size():
				var gemIndex = gems[i]
				if gemIndex != G.RunDatabase.emptySocketId:   # RunDatabaseStub.gd:27 同公式
					var gem = IB.instantiateItem(IB.getGemForIndex(gemIndex))
					item.setGem(i, gem)
		if "pd" in tuple:
			item.setData(tuple["pd"])
		lines.append("  p_item %s = %d" % [item.getName(), U.rng.state])
	lines.append("stage3_player_items=%d items=%d" % [U.rng.state, p_tuples.size()])
	G.PLAYER.setMaxHealth(p_round.health)
	G.PLAYER.setMaxStamina(p_round.stamina)
	G.initRoundResults()
	lines.append("stage4_player_misc=%d" % U.rng.state)

	G.OPPONENT = G.opponentScene.instance()
	lines.append("stage5_opp_instance=%d (expect 4×BalancedRng=8 步)" % U.rng.state)
	G.OPPONENT.playerId = G.OPPONENT.ID.OPPONENT
	G.PLAYER.setOpponent(G.OPPONENT)
	G.OPPONENT.setOpponent(G.PLAYER)
	G.OPPONENT.connect("character_died", G, "endCombat")
	G.OPPONENT.position = Vector2(1920 - G.playerCombatPos, 880)
	G.opponentNode.add_child(G.OPPONENT)
	lines.append("stage6_opp_ready=%d (场景 _ready 面)" % U.rng.state)

	var opp_run = runs[run_id]
	dummy.markedOpponentData = opp_run
	dummy.markedOpponentRound = round_id
	var rc = G.initHistoryOpponent()
	lines.append("stage7_opp_items=%d rc=%d" % [U.rng.state, rc])

	G.fightEnded = false
	G.numTimesOutOfStamina = 0
	G.emit_signal("shop_closed")
	G.emit_signal("switching_to_combat")
	CT.combatTime = 0.0
	CT.initialize()
	lines.append("stage8_signals=%d" % U.rng.state)
	var playerItems = G.PLAYER.INVENTORY.getItems().duplicate()
	playerItems.shuffle()
	playerItems.sort_custom(G.ItemSort, "sort_TriggerPriority")
	var opponentItems = G.OPPONENT.INVENTORY.getItems().duplicate()
	opponentItems.shuffle()
	opponentItems.sort_custom(G.ItemSort, "sort_TriggerPriority")
	lines.append("stage9_shuffle_sort=%d (全局链，Util.rng 应不变)" % U.rng.state)
	lines.append("final_state=%d" % U.rng.state)
	lines.append("opp_items_count=%d player_items_count=%d" % [
			opponentItems.size(), playerItems.size()])
	# 宝石数（getItems 不含宝石；从背包逐件数）
	var gem_count := 0
	for it in G.PLAYER.INVENTORY.getItems():
		var gs = it.get("gems")
		if gs != null:
			for g in gs:
				if g != null:
					gem_count += 1
	for it in G.OPPONENT.INVENTORY.getItems():
		var gs = it.get("gems")
		if gs != null:
			for g in gs:
				if g != null:
					gem_count += 1
	lines.append("gem_count=%d" % gem_count)

	var fh = File.new()
	var err = fh.open(out_path, File.WRITE)
	print("[probe] 写 %s err=%d" % [out_path, err])
	fh.store_string(PoolStringArray(lines).join("\n") + "\n")
	fh.close()
	print("[probe] 完成")
	quit(0)


# 从上一行状态步进到当前 state 的步数（用 stages 的差分在 Python 侧算，这里不重复实现）
func _steps_from(_cur, _lines) -> int :
	return 0


func load_history_runs() -> Dictionary :
	var src = ProjectSettings.globalize_path("res://data/history.db")
	var dst = ProjectSettings.globalize_path("user://oracle_history.db")
	var dir = Directory.new()
	if dir.file_exists(dst):
		dir.remove(dst)
	dir.copy(src, dst)
	var SQLite = load("res://addons/godot-sqlite/bin/gdsqlite.gdns")
	var db = SQLite.new()
	db.verbosity_level = 0
	db.path = dst
	db.open_db()
	var out = {}
	db.query("select * from runData;")
	for row in db.query_result:
		var bh = BHData.new()
		bh.version = row["version"]
		bh.time = row["time"]
		bh.customRules = row["custom"]
		bh.classI = row["class"]
		bh.loadout = row["loadout"]
		bh.id = row["runID"]
		bh.subclassIndex = row["subclass"]
		bh.skill1Index = row["skill1"]
		bh.skill2Index = row["skill2"]
		var rank = row["rank"]
		if rank == - 1:
			bh.mode = G.Mode.Unranked
		elif rank == - 2:
			bh.mode = G.Mode.Lobbies
		else:
			bh.mode = G.Mode.Ranked
			bh.rating = rank
		out[bh.id] = bh
	db.query("select * from roundData;")
	for row in db.query_result:
		var run = out.get(row["runID"], null)
		if run == null:
			continue
		var valid = true
		for entry in row:
			if row[entry] == null:
				valid = false
				break
		if not valid:
			continue
		run.addRoundData(row["roundID"], row["result"], row["tries"],
				row["health"], row["stamina"], row["buildInfo"])
	db.close_db()
	return out
