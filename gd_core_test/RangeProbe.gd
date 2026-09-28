extends SceneTree

# 实测 GDScript 3.6 的 range() 对 float 实参的转换方式（截断？floor？），
# 以及 from>to、incr 符号等边界 —— Python 侧 _gd_range 的权威依据。

func show(label: String, arr) -> void:
	print("RANGE: %-26s -> %s (size=%d)" % [label, str(arr), arr.size()])

func _init() -> void:
	show("range(3)", range(3))
	show("range(2.5)", range(2.5))
	show("range(2.9)", range(2.9))
	show("range(-2.5)", range(-2.5))
	show("range(1.5, 4.5)", range(1.5, 4.5))
	show("range(1.9, 4.1)", range(1.9, 4.1))
	show("range(-1.5, 2.7)", range(-1.5, 2.7))
	show("range(0, 5, 1.9)", range(0, 5, 1.9))
	show("range(5, 0, -1)", range(5, 0, -1))
	show("range(5, 0, -1.7)", range(5, 0, -1.7))
	show("range(0, 5, -1)", range(0, 5, -1))
	show("range(5, 0, 1)", range(5, 0, 1))
	show("range(0.4)", range(0.4))
	show("range(-0.4)", range(-0.4))
	show("range(3, 3)", range(3, 3))
	show("range(0)", range(0))
	# 类型：元素必须是 int
	var r = range(2.5)
	print("RANGE: typeof(elem)=", typeof(r[0]), " str(elem)=", str(r[0]))
	quit(0)
