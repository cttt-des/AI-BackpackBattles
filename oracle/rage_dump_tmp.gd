extends SceneTree
# 诊断：dump 含 "$rage[" 描述的物品键（hasBattleRageEffect 数据面提取器）。
# 用法：output/godot36/Godot_v3.6-stable_win64.exe --headless --audio-driver Dummy \
#   --path oracle --script rage_dump_tmp.gd > out.log 2>&1
# 依据：ItemBook.gd:1401 `item.hasBattleRageEffect = (descr.find("$rage[") != -1)`，
#   descr = Util.tra(descriptionKey + "_DESCR")（运行 locale 相关——oracle 宿主
#   跑在系统 locale，中文环境取 zh_Hans_CN）。提取后写进 enrich 工具（静态化），
#   内核不再依赖翻译环境。

func _init():
	var n = 0
	# 全物品键清单：ItemBook descriptor 名（用 battle_items.json 侧表太重，
	# 这里直接扫 ItemBook descriptors —— 神谕工程里 ItemBook 已是 autoload）
	var book = ItemBook
	var d = book.get_script()
	# descriptors 字典名以工程实际为准：常见 "items" / "descriptors"
	var pool = null
	for cand in ["items", "descriptors", "itemDescriptors"]:
		if book.get(cand) != null:
			pool = book.get(cand)
			break
	if pool == null:
		print("[RAGE-DUMP] no descriptor pool found")
		quit()
		return
	for k in pool.keys():
		var item = pool[k]
		var key = item.descriptionKey if "descriptionKey" in item else String(k)
		var descr: String = Util.tra(String(key) + "_DESCR")
		if descr.find("$rage[") != - 1:
			print("[RAGE] %s" % String(k))
			n += 1
	print("[RAGE-DUMP] total %d" % n)
	quit()
