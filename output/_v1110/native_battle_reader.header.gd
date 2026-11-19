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
var res := {}
var boot_ready := false
var observed_physics := 0
var observations := {}

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
	print("[NATIVE] Main scene initialization completed")
	if tree.current_scene == null or tree.current_scene.filename != "res://Core/Main.tscn":
		fail("Original Main scene is not loaded")
		return

	var case_id = OS.get_environment("NATIVE_BATTLE_CASE")
	var f = File.new()
	if f.open("res://fights.json", File.READ) != OK:
		fail("Cannot read case list")
		return
	var table = JSON.parse(f.get_as_text()).result
	f.close()
	var c = null
	for candidate in table["cases"]:
		if candidate["case_id"] == case_id:
			c = candidate
			break
	if c == null:
		fail("Unknown case " + case_id)
		return
	var runs = load_history_runs()
	var run_id = int(c["run_id"])
	var round_id = int(c["round_id"])
	var opp_run_id = int(c.get("opp_run_id", run_id))
	var opp_round_id = int(c.get("opp_round_id", round_id))
	if not runs.has(run_id) or not runs.has(opp_run_id):
		fail("Missing history runs " + str(batch_failures))
		return

	out_dir = OS.get_environment("NATIVE_BATTLE_OUT").plus_file(case_id)
	if Directory.new().make_dir_recursive(out_dir) != OK and not Directory.new().dir_exists(out_dir):
		fail("Cannot create " + out_dir)
		return
	var seed_value = int(c["seed"])
	res = {"seed": seed_value, "run_id": run_id, "round_id": round_id,
		"opp_run_id": opp_run_id, "opp_round_id": opp_round_id, "case_id": case_id}
	G.connect("combat_start", self, "on_start", [], CONNECT_ONESHOT)
	G.connect("combat_end", self, "on_end", [], CONNECT_ONESHOT)
	G.buildHistory.markedOpponentData = runs[opp_run_id]
	G.buildHistory.markedOpponentRound = opp_round_id
	G.instanceCharacter(runs[run_id].classI)
	U.rng.set_seed(seed_value)
	seed(seed_value)
	G.startHistoryRun(runs[run_id], round_id)
	var elapsed := 0
	while not ended and elapsed < 5700:
		yield(tree, "physics_frame")
		elapsed += 1
	if not ended:
		fail("No natural game terminal, activation=" + str(activated))
		return

	res["winner"] = winner
	res["combat_time"] = G.combatTimer.combatTime
	res["ticks"] = int(round(G.combatTimer.combatTime * 60.0))
	dump_events(G.combatLog.events, out_dir, res)
	var diagnostics = File.new()
	if diagnostics.open(out_dir.plus_file("boundaries.json"), File.WRITE) != OK:
		fail("Cannot write preparation observations")
		return
	diagnostics.store_string(JSON.print(observations, "  ") + "\n")
	diagnostics.close()
	print("[NATIVE] Recorded ", case_id, " ", winner, " events=", G.combatLog.events.size())
	tree.quit()

func on_start() -> void:
	activated = true
	dump_lineups(out_dir, res)
	observations["combat_start"] = {"seed": str(U.rng.get_seed()), "state": str(U.rng.get_state()),
		"player_stamina": G.PLAYER.curStamina, "opponent_stamina": G.OPPONENT.curStamina}
	call_deferred("on_started")

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

func on_activate(_items) -> void:
	observations["before_activate"] = {"seed": str(U.rng.get_seed()), "state": str(U.rng.get_state())}

func on_end(result) -> void:
	winner = "player" if result == G.RoundResult.Win else "opponent"
	ended = true

func fail(message: String) -> void:
	printerr("[NATIVE] ", message)
	get_tree().quit(1)
