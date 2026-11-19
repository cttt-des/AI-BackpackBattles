extends Node

var G
var U
var BHData
var batch_failures := []
var _in_warmup := false
var activated := false
var ended := false
var winner := ""
var out_dir := ""
var case_result := {}
var boot_ready := false
var observed_physics := 0
var observations := {}
var observed_delayed := []

func _physics_process(_delta) -> void:
	observed_physics += 1
	if observed_physics % 120 == 0:
		var game = get_tree().root.get_node("Game")
		print("[NATIVE-PROGRESS] frames=", observed_physics, " boot=", boot_ready,
				" active=", activated, " state=", game.state,
				" combat_time=", game.combatTimer.combatTime, " events=", game.combatLog.events.size())

func _ready() -> void:
	get_tree().root.get_node("Game").connect("continue_loaded", self, "on_boot_ready", [], CONNECT_ONESHOT)
	call_deferred("record_one")

func on_boot_ready() -> void:
	boot_ready = true

func record_one() -> void:
	var tree = get_tree()
	G = tree.root.get_node("Game")
	U = tree.root.get_node("Util")
	BHData = load("res://Interface/BuildHistory/BuildHistoryData.gd")
	for _i in range(1800):
		yield(tree, "idle_frame")
		if boot_ready and is_instance_valid(G.PLAYER) and is_instance_valid(G.combatLog) and is_instance_valid(G.buildHistory):
			break
	if not boot_ready or G.VERSION != "1.1.10" or not is_instance_valid(G.PLAYER) or not is_instance_valid(G.buildHistory):
		fail("Original Main scene failed to initialize")
		return
	for _i in range(180):
		yield(tree, "idle_frame")
	# ItemBook prepares two pooled instances per descriptor on each idle frame.
	# Beginning while that startup work is active consumes the combat RNG stream.
	# Wait for the source's preload to finish; do not disable or rewrite it.
	var item_book = tree.root.get_node("ItemBook")
	for _i in range(1800):
		if item_book.itemPoolingIndex >= item_book.descriptorList.size() - 1:
			break
		yield(tree, "idle_frame")
	if item_book.itemPoolingIndex < item_book.descriptorList.size() - 1:
		fail("Original item preload did not finish")
		return
	observations["startup"] = {"pooling_index": item_book.itemPoolingIndex,
		"descriptor_count": item_book.descriptorList.size(), "physics_frames": observed_physics,
		"locale": TranslationServer.get_locale()}
	var metadata := {}
	for descriptor in item_book.descriptorList:
		metadata[descriptor.identifier] = {"translated_name": descriptor.getTranslatedName(),
			"has_battle_rage_effect": descriptor.hasBattleRageEffect,
			"description_mentions_rage": descriptor.getDescription().find("$rage[") != -1}
	var metadata_root = OS.get_environment("NATIVE_BATTLE_OUT")
	Directory.new().make_dir_recursive(metadata_root)
	var metadata_file = File.new()
	if metadata_file.open(metadata_root.plus_file("descriptor_metadata.json"), File.WRITE) != OK:
		fail("Cannot write original descriptor metadata")
		return
	metadata_file.store_string(JSON.print({"version": G.VERSION, "locale": TranslationServer.get_locale(),
		"count": metadata.size(), "items": metadata}, "  ") + "\n")
	metadata_file.close()
	print("[NATIVE] Main scene initialization completed")
	if tree.current_scene == null or tree.current_scene.filename != "res://Core/Main.tscn":
		fail("Original Main scene is not loaded")
		return
	# BuildHistory is instanced off-tree by the source until the menu is opened.
	# Its real fight entry requires _ready() and the opening animation to finish.
	G.buildHistory.open()
	for _i in range(90):
		yield(tree, "idle_frame")
	if not G.buildHistory.is_inside_tree() or G.buildHistory.animation == null:
		fail("Original history menu failed to initialize")
		return

	var requested = OS.get_environment("NATIVE_BATTLE_CASE").split(",", false)
	var f = File.new()
	if f.open("res://fights.json", File.READ) != OK:
		fail("Cannot read case list")
		return
	var table = JSON.parse(f.get_as_text()).result
	f.close()
	var cases := {}
	for candidate in table["cases"]:
		cases[candidate["case_id"]] = candidate
	if requested.empty():
		fail("No native cases selected")
		return
	for case_id in requested:
		if not cases.has(case_id):
			fail("Unknown case " + case_id)
			return
	var runs = load_history_runs()
	var startup = observations["startup"].duplicate()
	for index in requested.size():
		if index > 0:
			# Use the source button path: the menu's opened callback calls
			# Game.endHistoryRun(), clears combat state and frees the opponent.
			G.combatSceneNode.switchBackToBuildHistory()
			for _i in range(240):
				yield(tree, "idle_frame")
				if G.curHistoryData == null and G.state == G.State.Title and G.buildHistory.is_inside_tree():
					break
			if G.curHistoryData != null or G.state != G.State.Title or not G.buildHistory.is_inside_tree():
				fail("Original history return did not finish")
				return
			for _i in range(30):
				yield(tree, "idle_frame")
		var outcome = record_case(cases[requested[index]], runs, startup, index)
		if outcome is GDScriptFunctionState:
			outcome = yield(outcome, "completed")
		if outcome != true:
			return
	print("[NATIVE-BATCH] completed=", requested.size())
	tree.quit()

func record_case(c, runs, startup, index):
	var tree = get_tree()
	var case_id = c["case_id"]
	activated = false
	ended = false
	winner = ""
	observations = {"startup": startup, "batch_index": index}
	var pending := []
	for entry in observed_delayed:
		if is_instance_valid(entry[1].get_ref()) and entry[0].time_left > 0:
			pending.append(entry)
	observed_delayed = pending
	if "draws" in U.rng:
		U.rng.recording = false
		U.rng.draws.clear()
	var run_id = int(c["run_id"])
	var round_id = int(c["round_id"])
	var opp_run_id = int(c.get("opp_run_id", run_id))
	var opp_round_id = int(c.get("opp_round_id", round_id))
	if not runs.has(run_id) or not runs.has(opp_run_id):
		fail("Missing history runs " + str(batch_failures))
		return false

	out_dir = OS.get_environment("NATIVE_BATTLE_OUT").plus_file(case_id)
	if Directory.new().make_dir_recursive(out_dir) != OK and not Directory.new().dir_exists(out_dir):
		fail("Cannot create " + out_dir)
		return false
	var seed_value = int(c["seed"])
	case_result = {"seed": seed_value, "run_id": run_id, "round_id": round_id,
		"opp_run_id": opp_run_id, "opp_round_id": opp_round_id, "case_id": case_id}
	G.connect("combat_start", self, "on_start", [], CONNECT_ONESHOT)
	G.connect("combat_end", self, "on_end", [], CONNECT_ONESHOT)
	# The selected record is supplied by the batch adapter, as in the single
	# recorder. Reset only the UI selection guard after the previous history run
	# has naturally ended; no combat state or random values are patched here.
	G.buildHistory.curRunId = run_id
	G.buildHistory.fighting = false
	G.buildHistory.markedOpponentData = runs[opp_run_id]
	G.buildHistory.markedOpponentRound = opp_round_id
	G.instanceCharacter(runs[run_id].classI)
	G.buildHistory.curData = runs[run_id]
	G.buildHistory.curRoundNum = round_id
	U.rng.set_seed(seed_value)
	seed(seed_value)
	# Use the source UI entry. It also clears the title's falling items;
	# calling startHistoryRun alone leaves their impact RNG active in combat.
	G.buildHistory.fightBuild()
	var elapsed := 0
	while not ended and elapsed < 5700:
		yield(tree, "physics_frame")
		elapsed += 1
	if not ended:
		fail("No natural game terminal, activation=" + str(activated))
		return false

	case_result["winner"] = winner
	case_result["combat_time"] = G.combatTimer.combatTime
	case_result["ticks"] = int(round(G.combatTimer.combatTime * 60.0))
	dump_events(G.combatLog.events, out_dir, case_result)
	if "draws" in U.rng:
		var rng_file = File.new()
		if rng_file.open(out_dir.plus_file("rng_draws.json"), File.WRITE) != OK:
			fail("Cannot write RNG observations")
			return
		rng_file.store_string(JSON.print(U.rng.draws, "  ") + "\n")
		rng_file.close()
	var diagnostics = File.new()
	if diagnostics.open(out_dir.plus_file("boundaries.json"), File.WRITE) != OK:
		fail("Cannot write preparation observations")
		return false
	diagnostics.store_string(JSON.print(observations, "  ") + "\n")
	diagnostics.close()
	if "recording" in U.rng:
		U.rng.recording = false
	print("[NATIVE] Recorded ", case_id, " ", winner, " events=", G.combatLog.events.size())
	return true

func on_start() -> void:
	activated = true
	dump_lineups(out_dir, case_result)
	observations["combat_start"] = {"seed": str(U.rng.get_seed()), "state": str(U.rng.get_state()),
		"player_stamina": G.PLAYER.curStamina, "opponent_stamina": G.OPPONENT.curStamina,
		"util_time": "%.17f" % U.time, "clock_time": "%.17f" % U.clockTime}
	var animations := []
	for character in [G.OPPONENT, G.PLAYER]:
		var timer = character.idleAniSpeedTimer
		animations.append({"owner": character.playerId, "left": timer.get_time_left(),
			"left_precise": "%.17f" % timer.get_time_left(),
			"wait_time": timer.wait_time, "process_mode": timer.process_mode,
			"stopped": timer.is_stopped()})
	observations["idle_animation_timers"] = animations
	var flickers := {}
	collect_flickers(get_tree().root, flickers)
	for entry in observed_delayed:
		var target = entry[1].get_ref()
		if is_instance_valid(target) and entry[0].time_left > 0:
			flickers[target] = true
	var flicker_states := []
	for target in flickers:
		var pending := []
		for entry in observed_delayed:
			if entry[1].get_ref() == target and entry[0].time_left > 0:
				pending.append({"left": "%.17f" % entry[0].time_left, "method": entry[2]})
		var host = target
		while host != null and not ("descriptor" in host and "ownerType" in host):
			host = host.get_parent()
		var identity = null
		if host != null:
			var cell = host.getTopLeftCell() if not host.occupiedCells.empty() else Vector2(-999, -999)
			identity = {"name": host.descriptor.identifier, "owner": host.ownerType,
				"top_left": [cell.x, cell.y], "relative_path": str(host.get_path_to(target))}
			var origin = _jsonable(host)
			if origin is Dictionary and origin.get("kind") == "gem":
				identity["gem_identity"] = origin.get("identity")
		var animation = target.get_animation(target.ani)
		flicker_states.append({"identity": identity, "pending": pending,
			"playing": target.is_playing(), "position": target.current_animation_position,
			"position_precise": "%.17f" % target.current_animation_position,
			"speed_precise": "%.17f" % target.playback_speed,
			"limits": [target.minDist, target.maxDist, target.minSpeed, target.maxSpeed],
			"speed": target.playback_speed, "animation": target.ani, "length": animation.length,
			"loop": animation.loop, "inside_tree": target.is_inside_tree(),
			"path": str(target.get_path()) if target.is_inside_tree() else "off-tree"})
	observations["flicker_states"] = flicker_states
	call_deferred("on_started")

func on_delayed_timer(timer, target, method_name) -> void:
	if is_instance_valid(target) and target.get_script() != null and target.get_script().resource_path.ends_with("/FlickerAnimation.gd"):
		observed_delayed.append([timer, weakref(target), method_name])

func collect_flickers(node, found) -> void:
	if node.get_script() != null and node.get_script().resource_path.ends_with("/FlickerAnimation.gd"):
		found[node] = true
	for child in node.get_children():
		collect_flickers(child, found)

func on_started() -> void:
	var state := {"seed": str(U.rng.get_seed()), "state": str(U.rng.get_state()), "items": []}
	for side in [G.PLAYER, G.OPPONENT]:
		for item in side.INVENTORY.getItems():
			state["items"].append({"name": item.getName(), "owner": item.ownerType,
				"trigger_time": item.triggerTime, "speed": item.getSpeed()})
	observations["activated"] = state

func on_prepare(items) -> void:
	var order := []
	for item in items:
		var cell = item.getTopLeftCell()
		order.append({"name": item.getName(), "owner": item.ownerType,
			"top_left": [cell.x, cell.y]})
	observations["prepare"] = {"seed": str(U.rng.get_seed()), "state": str(U.rng.get_state()), "order": order}
	var engine_seed = OS.get_environment("NATIVE_BATTLE_ENGINE_SEED")
	if not engine_seed.empty():
		seed(int(engine_seed))
		observations["prepare"]["engine_seed"] = engine_seed

func on_activate(_items) -> void:
	observations["before_activate"] = {"seed": str(U.rng.get_seed()), "state": str(U.rng.get_state())}
	observations["before_activate"]["buff_state"] = observe_buff_state()
	var engine_seed = OS.get_environment("NATIVE_BATTLE_ENGINE_SEED")
	if not engine_seed.empty():
		var activation_seed = int(engine_seed) + 1
		seed(activation_seed)
		observations["before_activate"]["engine_seed"] = str(activation_seed)
	if "recording" in U.rng:
		U.rng.recording = true

func on_end(result) -> void:
	observations["terminal_buff_state"] = observe_buff_state()
	winner = "player" if result == G.RoundResult.Win else "opponent"
	ended = true

func observe_buff_state() -> Array:
	var state := []
	for character in [G.PLAYER, G.OPPONENT]:
		var rows := []
		for type in character.buffs:
			var buff = character.buffs[type]
			if buff.current != 0 or buff.permanentStacks != 0 or not buff.temporaryStacks.empty():
				rows.append([type, buff.current, buff.permanentStacks, buff.temporaryStacks.size()])
		state.append(rows)
	return state

func fail(message: String) -> void:
	printerr("[NATIVE] ", message)
	get_tree().quit(1)
