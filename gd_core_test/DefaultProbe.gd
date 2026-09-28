extends SceneTree

# 实测 GDScript 3.6 里「带类型但无初值」的成员变量默认值。
# 这是 Python 侧 _rt 生成 _init_fields 的依据：若 Array 的默认值是 null，
# 则 gd_core 里 `self.types.append(...)` 在原版也会崩 —— 反过来则说明
# 转写器必须按类型给默认值，而不是一律 None。

var t_arr: Array
var t_dict: Dictionary
var t_int: int
var t_float: float
var t_str: String
var t_bool: bool
var t_vec2: Vector2
var t_color: Color
var t_ref: Reference
var t_node: Node
var t_untyped
var t_colon = []
var t_rmap: Dictionary
var t_rng: RandomNumberGenerator
var t_func: FuncRef
var t_pool: PoolStringArray

func _init() -> void:
	print("DEFAULT: arr=", t_arr, " is_null=", t_arr == null, " type=", typeof(t_arr))
	print("DEFAULT: dict=", t_dict, " is_null=", t_dict == null, " type=", typeof(t_dict))
	print("DEFAULT: int=", t_int, " type=", typeof(t_int))
	print("DEFAULT: float=", t_float, " type=", typeof(t_float))
	print("DEFAULT: str='", t_str, "' is_null=", t_str == null, " type=", typeof(t_str))
	print("DEFAULT: bool=", t_bool, " type=", typeof(t_bool))
	print("DEFAULT: vec2=", t_vec2, " type=", typeof(t_vec2))
	print("DEFAULT: color=", t_color, " type=", typeof(t_color))
	print("DEFAULT: ref=", t_ref, " is_null=", t_ref == null, " type=", typeof(t_ref))
	print("DEFAULT: node=", t_node, " is_null=", t_node == null, " type=", typeof(t_node))
	print("DEFAULT: untyped=", t_untyped, " is_null=", t_untyped == null, " type=", typeof(t_untyped))
	print("DEFAULT: rmap=", t_rmap, " is_null=", t_rmap == null, " type=", typeof(t_rmap))
	print("DEFAULT: rng=", t_rng, " is_null=", t_rng == null, " type=", typeof(t_rng))
	print("DEFAULT: func=", t_func, " is_null=", t_func == null, " type=", typeof(t_func))
	print("DEFAULT: pool=", t_pool, " is_null=", t_pool == null, " type=", typeof(t_pool))

	# 关键行为：默认值就是 [] 时，能否直接 append
	t_arr.append(1)
	print("DEFAULT: arr_after_append=", t_arr)
	t_dict["k"] = 1
	print("DEFAULT: dict_after_set=", t_dict)

	# 数组/字典的默认值是否**每个实例独立**（Python 里类属性会共享）
	var a = Inner.new()
	var b = Inner.new()
	a.list.append("x")
	print("DEFAULT: inner_a=", a.list, " inner_b=", b.list, " shared=", a.list == b.list)

	print("DEFAULT: typeof(Array)=", typeof([]), " typeof(null)=", typeof(null))

	quit(0)


class Inner:
	var list: Array
