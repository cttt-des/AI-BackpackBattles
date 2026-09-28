extends SceneTree

# dump_translations.gd — 无头导出 .translation 资源里的全部键值（LOG_ 模板真值）。
# 用法：godot --headless --script dump_translations.gd

func _init() -> void:
	var dir := Directory.new()
	var root := "res://Sheets/CSV/"
	var out := []
	dir.open(root)
	dir.list_dir_begin(true, true)
	var fname := dir.get_next()
	while fname != "":
		if fname.ends_with(".en.translation") or fname.ends_with(".zh_Hans_CN.translation"):
			var res = load(root + fname)
			if res != null and res is Translation:
				for key in res.get_message_list():
					var msg = res.get_message(key)
					out.append("%s|%s|%s" % [fname.get_basename(), key, msg.replace("\n", "\\n")])
		fname = dir.get_next()
	var f := File.new()
	f.open("res://../../../output/translations_dump.txt", File.WRITE)
	for line in out:
		f.store_line(line)
	f.close()
	print("DUMPED ", out.size())
	quit()
