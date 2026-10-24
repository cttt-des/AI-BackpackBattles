extends SceneTree
# oracle_deser_debug.gd — 反序列化逐位排查（临时工具，随 oracle 工作流使用）
# 解析期不引用任何游戏全局类；运行期经 root.get_node 获取 autoload。
# 用法：Godot --headless --path oracle --script oracle_deser_debug.gd [runID roundID]
#       参数走 fight_config.json

var G = null
var U = null
var IB = null
var BSScript = null
var RDScript = null

var _started := false


func _initialize() -> void :
	G = root.get_node("Game")
	U = root.get_node("Util")
	IB = root.get_node("ItemBook")
	BSScript = load("res://Utility/BitStream.gd")
	RDScript = load("res://Utility/RunData.gd")
	connect("physics_frame", self, "_tick")


func _tick() -> void :
	if _started:
		return
	# 与 oracle_fight 相同的开跑闸门：等 bootstrap 阶段 2 与 Game.ready_deferred
	# 的玩家实例化都完成
	var boot = root.get_node_or_null("Main")
	if boot == null or not boot.fully_built or root.get_node("Game").PLAYER == null:
		return
	_started = true
	root.get_node("Game").itemLibrary = boot.G_itemLibrary

	var fh = File.new()
	fh.open("res://fight_config.json", File.READ)
	var cfg = parse_json(fh.get_as_text())
	fh.close()

	# 读 runData/roundData
	var dir = Directory.new()
	var src = ProjectSettings.globalize_path("res://data/history.db")
	var dst = ProjectSettings.globalize_path("user://oracle_history.db")
	if dir.file_exists(dst):
		dir.remove(dst)
	dir.copy(src, dst)
	var SQLite = load("res://addons/godot-sqlite/bin/gdsqlite.gdns")
	var db = SQLite.new()
	db.verbosity_level = 0
	db.path = dst
	db.open_db()
	db.query("select * from runData where runID=" + str(cfg["run_id"]) + ";")
	var run_row = db.query_result[0]
	db.query("select * from roundData where runID=" + str(cfg["run_id"]) +
			" and roundID=" + str(cfg["round_id"]) + ";")
	var round_row = db.query_result[0]
	db.close_db()

	var version = run_row["version"]
	var buildInfo: String = round_row["buildInfo"]
	print("version=", version, " buildInfo len=", buildInfo.length())

	# 逐位复刻 RunData.deserializeStream，带打印
	var bitStream = BSScript.new()
	var res = bitStream.fromGodotString(buildInfo)
	print("fromGodotString -> ", res)

	var totalNumItems = ItemBookModule(IB, version)
	print("totalNumItems=", totalNumItems, " getNumItems=", IB.getNumItems())

	var health = bitStream.pull(G.MAX_HEALTH)
	print("health=", health, " (bitsLeft=", bitStream.bitsLeft(), ")")
	var stamina = bitStream.pull(G.MAX_STAMINA)
	print("stamina=", stamina)

	var n = 0
	while bitStream.bitsLeft() >= 8:
		n += 1
		var index = bitStream.pull(totalNumItems)
		if index >= totalNumItems or index == - 1:
			print("item #", n, ": BAD index ", index, " bitsLeft=", bitStream.bitsLeft())
			break
		var descriptor = IB.getDescriptorFromIndex(index)
		if descriptor == null:
			print("item #", n, ": index ", index, " → descriptor NULL")
			break
		if not descriptor.scene:
			print("item #", n, ": index ", index, " → ", descriptor.getName(), " 无 scene")
			break
		var cx = bitStream.pull(G.PLAYER.INVENTORY.MAX_SIZE.x)
		var cy = bitStream.pull(G.PLAYER.INVENTORY.MAX_SIZE.y)
		var face = bitStream.pull(4)
		print("item #", n, ": index ", index, " = ", descriptor.getName(),
				" cell=(", cx, ",", cy, ") face=", face,
				" bitsLeft=", bitStream.bitsLeft())
		var numSockets = IB.getNumSockets(index)
		if numSockets > 0:
			var hasGems = bitStream.pull(2)
			print("    sockets=", numSockets, " hasGems=", hasGems)
			if hasGems == 1:
				for s in numSockets:
					var gi = bitStream.pull(G.get_node("/root/RunDatabase").totalNumGems)
					print("    gem idx=", gi, " (numGems=", IB.getNumGems(),
							" emptySocketId=", G.get_node("/root/RunDatabase").emptySocketId, ")")
		var instance = G.itemLibrary.getInstance(descriptor)
		if instance.has_method("getDataPersistent"):
			var numBits = instance.getDataPersistentBits()
			var dataAsInt = bitStream.pullBitsize(numBits)
			print("    persistent bits=", numBits, " value=", dataAsInt)
	print("done, items=", n)
	quit(0)


func ItemBookModule(ib, version: int) -> int :
	# 对齐 RunData.deserializeStream：version ≥ 1.1.0 → 现书总数
	var vstr = G.versionToString(version)
	if U.laterOrEqual(vstr, "1.1.0"):
		return ib.getNumItems()
	return 510
