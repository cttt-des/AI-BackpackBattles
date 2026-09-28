extends SceneTree

# 实测 GDScript 3.6 的 `for x in <非容器>` 迭代语义 —— Python 侧 _iter 的权威依据。
# 关注：float 到底走不走 range()，迭代值是什么类型，边界（0.5 / -1.0 / 0）。

func show(label: String, vals: Array) -> void:
	print("ITER: %-24s -> %s" % [label, str(vals)])

func it_int(n: int) -> Array:
	var out := []
	for i in n:
		out.push_back([i, typeof(i)])
	return out

func it_float(n: float) -> Array:
	var out := []
	for i in n:
		out.push_back([i, typeof(i)])
	return out

func it_str(s: String) -> Array:
	var out := []
	for c in s:
		out.push_back(c)
	return out

func it_dict(d: Dictionary) -> Array:
	var out := []
	for k in d:
		out.push_back(k)
	return out

func _init() -> void:
	show("int 5", it_int(5))
	show("int 0", it_int(0))
	show("int -3", it_int(-3))
	show("float 3.0", it_float(3.0))
	show("float 2.5", it_float(2.5))
	show("float 0.5", it_float(0.5))
	show("float -1.5", it_float(-1.5))
	show("float 0.0", it_float(0.0))
	show("string 'abc'", it_str("abc"))
	show("dict {a:1,b:2}", it_dict({"a": 1, "b": 2}))
	print("ITER: typeof(int)=2 typeof(float)=3")
	quit(0)
