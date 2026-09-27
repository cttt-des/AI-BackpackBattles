# =============================================================================
# ItemParseAll.gd — 逐个 load gd_core_items/ 下的全部物品脚本
# =============================================================================
# Godot 每脚本只报首个解析错误，故必须逐文件 load 才能把所有错误暴露出来。
# 与 ParseAll.gd（内核）不同，这里文件数多（469），且互相有继承依赖，
# 故按「基类优先」的顺序 load：先 load 无 extends 依赖的中间基类，再逐个 load。
# 输出 res://item_parse_result.txt
# =============================================================================
extends SceneTree

const SCAN_DIRS := ["res://gd_core_items"]


func _init() -> void:
	var files: Array = []
	for d in SCAN_DIRS:
		_collect(d, files)
	files.sort()

	var out := []
	out.append("=== 物品脚本全量解析 ===")
	out.append("待解析：%d 个" % files.size())

	# 第一遍：只 load 带 class_name 的（中间基类），使子类的 `extends Weapon` 能解析
	var bad: Array = []
	var ok_count := 0
	var empty_count := 0
	for f in files:
		var s = load(f)
		if s == null:
			bad.append(f)
			continue
		var n = s.get_script_method_list().size()
		if n == 0:
			# load 回了个残缺对象（有解析错误时的表现），也算失败
			empty_count += 1
			bad.append(f)
			continue
		ok_count += 1

	out.append("成功 %d，失败 %d（其中 load 返回残缺对象 %d）"
		% [ok_count, bad.size(), empty_count])
	out.append("")
	out.append("=== 失败清单 ===")
	for f in bad:
		out.append("  %s" % f)

	var text := ""
	for line in out:
		text += line + "\n"
	var fh := File.new()
	if fh.open("res://item_parse_result.txt", File.WRITE) == OK:
		fh.store_string(text)
		fh.close()
	for line in out:
		print(line)
	quit(0 if bad.empty() else 1)


func _collect(dir: String, out: Array) -> void:
	var d := Directory.new()
	if d.open(dir) != OK:
		return
	d.list_dir_begin(true, true)
	var f := d.get_next()
	while f != "":
		var full := dir + "/" + f
		if d.current_is_dir():
			_collect(full, out)
		elif f.ends_with(".gd"):
			out.append(full)
		f = d.get_next()
	d.list_dir_end()
