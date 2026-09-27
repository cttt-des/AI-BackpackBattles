# =============================================================================
# CoreUtil.gd — 无头战斗内核：战斗相关工具函数（Util.gd 子集）
# =============================================================================
# 对齐源码：Utility/Util.gd（全文 1683 行）
#
# 原版 Util 是 autoload 单例，1683 行里绝大部分是「场景树遍历 / 节点生命周期 /
# 字体本地化 / 弹窗 / tween 管理 / 鼠标坐标」这类与战斗无关的工具。本文件只收拢
# **被战斗判定读取**的几个纯函数（判据来自 simulator/extract_items.py:600-606
# 中项目自己的「不剥离」白名单：pickRandomElement/dictAdd/dictSub/flip 属 RNG 与
# 记账语义，剥离会改变战斗结果）。
#
# 逐字对齐：
#   dictAdd        Util.gd:961-964
#   dictSub        Util.gd:966-972
#   dictAddDict    Util.gd:974-976
#   sortDict       Util.gd:1603-1609（DictSorter 在 Util.gd:1643-1653）
#   pickRandomElement → 见 CoreRng.pickRandomElement（对齐 Util.gd:452-453）
#                      取随机必须走注入的 rng，故放在 CoreRng 上而非此处
#
# ★ 与原版的一处**有意偏差**（记入 docs/gd_core_truth.md 第 5 节）：
#   原版 sortDict(dict, shuffleBeforeSort=true) 用 Array.shuffle()，它走 Godot
#   **全局** RNG（Util.gd:76-77 的 randomize 之后无种子），且随后的 sort_custom
#   是 Godot 的非稳定 introsort，因此该函数在原版里本身不可复现。
#   内核改为「先按注入 rng 洗牌、再稳定地按值降序排」，取值域与原版相同
#   （同为「按值降序」，仅同值并列的次序不同），换取同种子逐位可复现。
#   全仓库该分支只被 Item.getStackFraction（Item.gd:5642）一处使用。
# ★ 实例化说明（供物品行为脚本直挂）：
#   原版 `Util` 是 autoload **单例**，物品脚本里写 `Util.flip(0.5)`。
#   内核不引入全局单例，改为 CoreContext 持有一个 CoreUtil 实例（`ctx.util`），
#   转译时把 `Util.` 映射成 `ctx.util.`。**方法签名与原版逐字一致**，行为脚本
#   一行判定都不用改写。带 rng 的方法转发给构造时注入的 CoreRng，使随种子可复现。
# =============================================================================
extends Reference
class_name CoreUtil


# 注入的随机源（对齐原版 Util.rng 这个 autoload 级全局 RNG）
var rng = null

# 由 CoreContext._init 回填 self。仅 callNextFrame / callDelayed 这两个
# 「原版靠 SceneTree 提供帧与时间」的转发需要它，纯函数一律不用（保持 static）。
var _ctx = null


func _init(_rng = null) -> void :
	rng = _rng


# 真值化（GDScript 3.x 没有 bool() 构造函数，那是 4.x 才有的内置转换）。
# 语义 = GDScript 自身的条件真值：null/false/0/0.0/""/空容器 → false，其余 → true。
# 用于把行为脚本（Variant 返回）的返回值收敛成 bool，避免 `bool(x)` 直接报错。
# 实现落在零依赖的 CoreConst 上（CoreItemData 也要用它，两处互相引用会成环）。
static func truth(v) -> bool:
	return CoreConst.truth(v)


# 对齐 Util.gd:961-964
static func dictAdd(dict: Dictionary, key, val = 1, base = 0) -> int:
	var newVal = dict.get(key, base) + val
	dict[key] = newVal
	return newVal


# 对齐 Util.gd:966-972（值降到 <=0 时删键）
static func dictSub(dict: Dictionary, key, val = 1) -> int:
	var val2 = dict.get(key, 0) - val
	if val2 <= 0:
		dict.erase(key)
	else:
		dict[key] = val2
	return val2


# 对齐 Util.gd:974-976
static func dictAddDict(dict1: Dictionary, dict2: Dictionary) -> void :
	for key in dict2:
		dictAdd(dict1, key, dict2[key])


# 对齐 Util.gd:979-983
static func dictAppend(dict: Dictionary, key, value) -> void :
	if key in dict:
		dict[key].append(value)
	else:
		dict[key] = [value]


# 对齐 Util.gd:984-989
static func dictErase(dict: Dictionary, key, valueToErase) -> void :
	if key in dict:
		var arr = dict[key]
		arr.erase(valueToErase)
		if arr.empty():
			dict.erase(key)


# 对齐 Util.gd:1603-1609 —— DictSorter（Util.gd:1649-1650）比较的是
# `dict[key1] > dict[key2]`，即按值降序。
static func sortDict(dict: Dictionary, rng, shuffleBeforeSort = false) -> Array:
	var sorted: Array = dict.keys()
	if shuffleBeforeSort:
		rng.shuffle(sorted)
	sorted.sort_custom(DictSorter.new(dict), "sort")
	return sorted


# 对齐 Util.gd:1643-1653
class DictSorter extends Reference:
	var dict: Dictionary
	
	func _init(_dict):
		dict = _dict
	
	func sort(key1, key2):
		return dict[key1] > dict[key2]
	
	func sort_reverse(key1, key2):
		return dict[key1] < dict[key2]


# ─────────────────── 随机（转发 CoreRng，签名对齐 Util.gd） ───────────────────
# 原版这些都是 `rng.xxx(...)` 的一行包装，转发后语义与随机数消耗序列完全一致。

# 对齐 Util.gd:1007-1008
func roll(maximum = 100.0) -> float:
	return rng.roll(maximum)


# 对齐 Util.gd:1010-1011
func flip(chance = 0.5) -> bool:
	return rng.flip(chance)


# 对齐 Util.gd:1013-1014
func flipPercent(chance) -> bool:
	return rng.flipPercent(chance)


# 对齐 Util.gd:1017-1018
func flipRound(chance) -> int:
	return rng.flipRound(chance)


# 对齐 Util.gd:1021-1033
func flipWeighted(weights: Array) -> int:
	return rng.flipWeighted(weights)


# 对齐 Util.gd:452-453
func pickRandomElement(array: Array):
	return rng.pickRandomElement(array)


# 对齐 Util.gd:455-459
func getArrayElement(array: Array, index: int, default = null):
	if index > array.size() - 1:
		return default
	else:
		return array[index]


# ─────────────────── 计时器 / 延迟调用（Util.gd:725-741、1591-1593） ───────────────────
# ★ 为什么必须建模而不是当表现剥掉：这几处承载的是**判定**，且缺失的后果比「少一个效果」
#   更隐蔽 —— Godot 3 遇到 `Nonexistent function` 只打印 SCRIPT ERROR 然后**中断当前函数**，
#   该函数在调用点之后的判定全部静默不执行，而进程退出码仍为 0。实测消费点：
#     CritwoodStaff.onPreDealDamage_early  Util.changeTimer(critTimer, critBuffDur)
#       → 重置暴击 buff 时长；到期由 tscn 的 timeout → buffEnded 收回暴击率
#     Sandbag.onPreCombatStart             Util.changeTimer(buffTimer, getBuffDur())
#       → 沙袋伤害减免的生效时长
#     Lightsaber.onBlindingLightTimeout    Util.callNextFrame(character(), "endBlindingLight")
#       → 帧末结束致盲光（少了它就永不结束）
#     DragonEgg.startHatching              Util.callDelayed(self, "hatch", DUR - 0.1)
#       → 孵化计时
#   注：物品侧对 `Util.` 的调用经转译统一落到 `ctx.util.*`；下面 static 的两个是纯转发，
#   带 ctx 的两个转发给 CoreContext 的按时队列。

# 对齐 Util.gd:1591-1593
static func changeTimer(timer, t: float) -> void :
	var timeLeft = timer.get_time_left()
	timer.start(t + timeLeft)


# 对齐 Util.gd:734-735 —— `get_tree().connect("idle_frame", target, method, args, ONESHOT)`
# 即「本帧末调用一次」。内核无场景树，等价物是 ctx 的帧末队列（CoreCombat 物理帧
# 末尾 flush），入队次序 = 原版同一帧内 connect 的次序。
func callNextFrame(target, methodName: String, arguments: Array = []) -> void :
	_ctx.defer(target, methodName, arguments)


# 对齐 Util.gd:725-727 —— `get_tree().create_timer(delay, false)` + timeout → method。
# 第二个参数 false 即 process_always=false，SceneTree 会挂到**物理帧**上等；
# 无头内核只有物理帧，故与 callDelayed_process 落在同一时间轴，共用一份实现。
func callDelayed(target, methodName: String, delay: float, binds: Array = []) -> void :
	_ctx.callDelayed(target, methodName, delay, binds)


# 对齐 Util.gd:729-731
func callDelayed_process(target, methodName: String, delay: float, binds: Array = []) -> void :
	_ctx.callDelayed(target, methodName, delay, binds)


# ─────────────────── 纯函数（无状态，保持 static 以免误用实例） ───────────────────

# 对齐 Util.gd:814-818
static func arrayAsIndexDict(array: Array) -> Dictionary:
	var invertedDict = Dictionary()
	for i in array.size():
		invertedDict[array[i]] = i
	return invertedDict


# 对齐 Util.gd:808-812
static func invertDictionary(dict: Dictionary) -> Dictionary:
	var invertedDict = Dictionary()
	for key in dict:
		invertedDict[dict[key]] = key
	return invertedDict


# 对齐 Util.gd:499-503
# ★ 用 Dictionary 去重 → 返回的是 `dict.keys()`，**顺序不保证**。原版即如此，
#   故调用方（DeckofCards.countDuplicates）只取 size 差值，不依赖顺序。
static func filterDuplicates(arr: Array) -> Array:
	var dict = Dictionary()
	for a in arr:
		dict[a] = true
	return dict.keys()


# 对齐 Util.gd:513-516
static func countDuplicates(arr: Array) -> int:
	var before = arr.size()
	var filtered = filterDuplicates(arr)
	return before - filtered.size()


# 对齐 Util.gd:1001-1005 —— 仅**一层**展开（不是递归）
static func flatten(arr: Array) -> Array:
	var flattened = []
	for inner in arr:
		flattened.append_array(inner)
	return flattened


# 对齐 Util.gd:170-174（角度差取最小回环）
static func rotDif(rot1, rot2):
	var rot = abs(rot1 - rot2)
	if rot > PI:
		return 2 * PI - rot
	return rot


# 对齐 Util.gd:1449-1450。原版判 `object is ItemDescriptor`，内核的描述符类型是
# CoreItemData，故做类型等价映射（不是行为改动）。
# ★ 用运行期 `load()` 比较脚本引用，而不是编译期 `is CoreItemData`：后者会让
#   CoreUtil 与 CoreItemData 互相引用，构成 class_name 依赖环，Godot 3 直接拒绝加载。
static func isItemDescriptor(object) -> bool:
	if object == null:
		return false
	return object.get_script() == load("res://gd_core/CoreItemData.gd")


# 对齐 Util.gd:207-209 —— 原版只在 editor 特性下 assert
static func eassert(toTest: bool = false) -> void :
	if OS.has_feature("editor"):
		assert (toTest)


# 对齐 Util.gd:196-205
static func eprint(text, arg1 = null, arg2 = null, arg3 = null) -> void :
	if OS.has_feature("editor"):
		if arg3 != null:
			print("-", text, arg1, arg2, arg3)
		elif arg2 != null:
			print("-", text, arg1, arg2)
		elif arg1 != null:
			print("-", text, arg1)
		else:
			print("-", text)
