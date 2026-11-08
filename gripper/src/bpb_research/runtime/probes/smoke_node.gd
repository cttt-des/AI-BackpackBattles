## 冒烟测试（Node 版）：Steam 初始化 + 找排行榜，结果写 JSON
extends Node

var output_path = ""
var started = 0
var stage = "init"
var done = false
var response = {"status": "running", "stage": "init"}

func _ready():
	var args = OS.get_cmdline_args()
	var marker = args.find("--")
	if marker < 0 or marker + 1 >= args.size():
		get_tree().quit(2)
		return
	output_path = args[marker + 1]
	started = OS.get_ticks_msec()
	call_deferred("_start")

func _start():
	response["engine"] = Engine.get_version_info()
	var init = Steam.steamInit(false)
	response["steam_init"] = init
	response["app_id"] = str(Steam.getAppID())
	response["logged_on"] = Steam.loggedOn()
	if init.get("status", 0) != 1:
		_fail("Steam 初始化失败")
		return
	stage = "leaderboard"
	Steam.connect("leaderboard_find_result", self, "_found")
	Steam.findLeaderboard("bpb-runs3")

func _process(_delta):
	if done:
		return
	Steam.run_callbacks()
	var elapsed = OS.get_ticks_msec() - started
	if elapsed > 60000:
		_fail("总超时")
	elif stage == "leaderboard" and elapsed > 25000 and not response.has("found"):
		_fail("找排行榜超时")

func _found(handle, found):
	if done:
		return
	response["leaderboard_handle"] = str(handle)
	response["found"] = found
	if found != 1 or handle == 0:
		_fail("未找到排行榜 bpb-runs3")
		return
	response["leaderboard_name"] = Steam.getLeaderboardName(handle)
	response["entry_count"] = Steam.getLeaderboardEntryCount(handle)
	response["status"] = "complete"
	_finish()

func _fail(message):
	response["status"] = "failed"
	response["error"] = message
	response["elapsed_ms"] = OS.get_ticks_msec() - started
	printerr(message)
	_finish()

func _finish():
	if done:
		return
	done = true
	response["elapsed_ms"] = OS.get_ticks_msec() - started
	var f = File.new()
	if f.open(output_path, File.WRITE) == OK:
		f.store_string(JSON.print(response))
		f.close()
	call_deferred("_quit")

func _quit():
	get_tree().quit(0 if response.get("status") != "failed" else 1)
