# =============================================================================
# CoreItemData.gd — 无头战斗内核：物品静态数据（ItemDescriptor 的无头子集）
# =============================================================================
# 对齐源码：Items/ItemDescriptor.gd
#   · getP(index)           ItemDescriptor.gd:107（int 下标 → params[]；字符串 → namedParams）
#   · paramBases            全名 → 基名（`dur_stun` → `dur`），供 Item.getParamModified 使用
#   · paramBases_inverted   基名 → 全名（`dur` → `dur_stun`），供 ItemDescriptor.hasParam 使用
#   · addNamedParam         上两表 + sortedParamNames 的**唯一**派生点（逐行照搬原版）
#   · 字段命名与 ItemDescriptor 保持一致，便于从既有数据管线（battle_items.json）
#     直接填充，不需要改动数据源。
#
# 说明：完整 CSV 解析（p1..p10 的 `v:name` 形态、cd 逗号分隔、tags 位标志、
#   gained/removed/usedStacks、type 的 "Melee Weapon" 拆分等）属数据层，
#   项目已有实现（engine/data.py + assets/battle_items.json）。
#   本类只负责「内核运行期读取静态数据的接口形态」。
# =============================================================================
extends Reference
class_name CoreItemData


var name: String = ""
var identifier: String = ""     # 对齐 ItemDescriptor.identifier（getName 返回它）
var itemIndex: int = 0          # 对齐 ItemDescriptor.itemIndex（getIndex 返回它）
var minDam: int = 0
var maxDam: int = 0
var staminaCost: float = 0.0    # 对齐 ItemDescriptor.gd:55
var block: int = 0              # 对齐 ItemDescriptor.block（Item.getBlock 读取）
var cd: float = 0.0
var extraCds: Array = []
var accuracy: float = 100.0
var canActivate: bool = true
var chance: float = 0.0
var chance2: float = 0.0
var shopChance: float = 0.0
var types: Array = []
var tags: int = 0
var physics: int = 0
var rarity: int = 0
var price: int = 0              # 对齐 ItemDescriptor.price（getPrice 返回它）
var classes: int = 0            # 对齐 ItemDescriptor.classes（StuffedClasses 位标志）
var randomUniquePool := false   # 对齐 ItemDescriptor.randomUniquePool（isTreasure 读取）
# 对齐 ItemDescriptor.hasBattleRageEffect（ItemBook.gd:1401 由描述文本里的 "$rage[" 标记
# 推出：`item.hasBattleRageEffect = (descr.find("$rage[") != -1)`）。
# 消费方：Item.isBattleRageItem()（Item.gd:5401-5402）→ Character.prepare 用它挑自动战怒物品。
# ★ 数据现状：assets/battle_items.json 目前**不含**该标记（描述文本未导出），
#   故字段默认 false；装配层若能提供该键即自动生效，内核不做任何推测。
var hasBattleRageEffect := false
# 对齐 ItemDescriptor.gatedItems（ItemDescriptor.gd:66）
# 消费方：Item.getRelatedItems()（Item.gd:2352）→ 被 GateItem/相关物品的 tooltip 与
# 「受影响物品」提示使用。装配层从描述符导出的列表填入（元素为描述符标识）。
var gatedItems: Array = []
var startsSubclass: String = "" # 对齐 ItemDescriptor.gd:71（isSubclassItem 读取）
# 对齐 ItemDescriptor.gd:65 `var gateItem = null` —— 「需要先持有某件物品才解锁」的
# 门控目标（ItemBook.gd:1103 从表格的 "gateItem" 列读入）。
# 消费方：Gem.gd:345 `if descriptor.gateItem == ctx.item_book.getDescriptor("Box of Riches")`
# —— 值是**描述符标识字符串**，装配层从数据填；缺省 null 即「无门控」，与只带
# 普通参数的宝石取同一分支（正常情况）。
var gateItem = null
# 对齐 ItemDescriptor.gd:58 `var recipes: = []` / :59 `var recipesAsIngredient: = []` 的
# **上游**表（ItemDescriptor.gd:61）——「合成出本物品的配方」。isCraftedItem() 只看它。
# 消费方：Item.isCrafted()（Item.gd:5736）→ Anvil.canAffect（只有合成品才被铁砧加成）。
# 数据现状：battle_items.json 未导出配方图，默认空 ⇒ isCraftedItem() 恒假。
# ★ 这是**已知缺口**而非「判定为假」：真要接合成品判定，需装配层补该字段。
var originatingRecipes: Array = []

# 对齐 ItemDescriptor.gd:17-21、:82、:349-355
#   isReleased() 的三分支：Demo → 恒真；Full/Unreleased → 问构建特性标志。
#   ★ 原版 `Game.loadUnreleasedContent()` 对 FULLVERSION 有 && 要求，故未发行物品
#     在正式包里恒为 false。内核逐字照搬同一组 OS.has_feature 表达式，
#     好处是「在编辑器宿主里跑的结果」与「在正式包里跑的结果」各自与原版一致
#     （编辑器宿主下 editor=true → loadExclusiveContent 为真，正好等价于正式包的
#      full_version=true）。
enum ReleaseState{
	Demo, 
	Full, 
	Unreleased
}
var releaseState: int = ReleaseState.Full
var _editor := OS.has_feature("editor")
var _playtest := OS.has_feature("playtest")
# 原版是 `OS.has_feature("full_version") or Util.debugOnly(true)`，而 debugOnly 无
# return ⇒ 返回 null。故该式在 feature 为真时得 true、为假时得 null（假值），
# 与直接取 `OS.has_feature("full_version")` **真值等价**（debugOnly 只是打印副作用）。
var _full_version := OS.has_feature("full_version")
var _engineer_test := OS.has_feature("engineertest")

var params: Array = []
var namedParams: Dictionary = {}
# ── 具名参数的「基名」索引（对齐 ItemDescriptor.gd:23, 49-50, 102-108） ──
# 原版在 addNamedParam 里同时维护三张结构：
#   sortedParamNames    —— 按基名分组插入的参数名序（唯一消费方 Item.gd:879 的
#                          getDescription 文本拼装，**不在任何判定路径上**；
#                          内核保留纯为与 addNamedParam 逐行对称，不参与战斗）
#   paramBases          —— 全名 → 基名（`dur_stun` → `dur`；分隔符 `_`）
#                         唯一消费方 Item.getParamModified（Item.gd:3926-3928）
#   paramBases_inverted —— 基名 → 全名（`dur` → `dur_stun`）
#                         唯一消费方 ItemDescriptor.hasParam（ItemDescriptor.gd:145）
# ★ 两张表方向相反、不可互换 —— 内核曾误用 paramBases 实现 hasParam，
#   导致 `hasParam("heal")` 对只带 `heal_food` 的物品判假（Item.gd:5380
#   isHealingItem 的判定路径直接受影响），已按原版改回 paramBases_inverted。
const PARAM_DELIMITER = "_"
var sortedParamNames: Array = []
var paramBases: Dictionary = {}
var paramBases_inverted: Dictionary = {}

var gainedStacks: int = 0
var removedStacks: int = 0
var usedStacks: int = 0

# 无头内核无需视觉激活动画，保留字段仅为接口一致（默认 null）
var activationAni = null


# 对齐 ItemDescriptor.gd:107
func getP(index):
	if index is String:
		return namedParams.get(index, 0.0)
	return params[index]


# 对齐 ItemDescriptor.gd:145
# ★ 走 paramBases_inverted（基名 → 全名）：原版 hasParam 的入参一律是**基名**
#   （物品脚本与内核调用点：Item.gd:5380 `hasParam("heal")`/`"lifesteal"`、
#    Item.gd:5692 `hasParam("dur")`、FalseLife.gd:9 `hasParam("maxhealth")`），
#   故必须用「基名」建索引；用 paramBases 会把带分隔符的具名参数全判假。
func hasParam(paramName: String) -> bool:
	return paramName in paramBases_inverted


# 对齐 ItemDescriptor.gd:102-108（addNamedParam，逐行照搬）
# ★ 这是 paramBases / paramBases_inverted 的**唯一**派生点。原版描述符由
#   ItemBook 在建表时逐个 addNamedParam 调用构建；无头内核没有资源管线，
#   改由 CoreItemData.fromDict 在装载具名参数时复用本方法（见文件尾）。
func addNamedParam(paramName: String, paramVal):
	namedParams[paramName] = paramVal
	var sortedPos = 0
	for i in sortedParamNames.size():
		if sortedParamNames[i].begins_with(paramName):
			sortedPos = i + 1
	sortedParamNames.insert(sortedPos, paramName)
	paramBases[paramName] = paramName.get_slice(PARAM_DELIMITER, 0)
	paramBases_inverted[paramBases[paramName]] = paramName


func hasTag(tag) -> bool:
	return tags & tag


func isWeapon() -> bool:
	return (CoreConst.Type.Weapon in types)


# ── 对齐 ItemDescriptor.gd:110-166, 299-325（战斗判定读取的描述符访问器） ──

func getIndex() -> int:
	return itemIndex


# 对齐 ItemDescriptor.gd:113-114
func getName() -> String:
	return identifier


# 对齐 ItemDescriptor.gd:123-124
func getRarity() -> int:
	return rarity


# 对齐 ItemDescriptor.gd:147-148
func getShopChance() -> float:
	return shopChance


# 对齐 ItemDescriptor.gd:299-300
func getTypes() -> Array:
	return types


# 对齐 ItemDescriptor.gd:153-158
func isAvailableFor(classId: int) -> bool:
	return (classes & classId) != 0


# 对齐 ItemDescriptor.gd:160-161
func isNeutral() -> bool:
	return classes == CoreConst.StuffedClasses.Neutral


# 对齐 ItemDescriptor.gd:163-165
func isClassItem() -> bool:
	return (classes != CoreConst.StuffedClasses.Neutral and 
		classes != CoreConst.StuffedClasses.None)


# 对齐 ItemDescriptor.gd:324-325
func isSubclassItem() -> bool:
	return startsSubclass != ""


# 对齐 ItemDescriptor.gd:257-258
# 消费方在**战斗路径**上：Item.isCrafted()（Item.gd:5736）→ Anvil.canAffect
# （Item.gd:17-18 `return item.isCrafted()`），只有合成品才被铁砧加成伤害。
func isCraftedItem() -> bool:
	return not originatingRecipes.empty()


# 对齐 ItemDescriptor.gd:260-261
func isGatedItem() -> bool:
	return gateItem != null


# 对齐 ItemDescriptor.gd:311-312
# 消费方在**战斗路径**上：VillainSword.canAffect / MercuryElemental.canAffect
# （决定「近战武器才被加成」）—— 判定失败会静默改变受影响集。
func isMeleeWeapon() -> bool:
	return (CoreConst.Type.Melee in types) and isWeapon()


# 对齐 ItemDescriptor.gd:314-315。消费方：Markswoman.canAffect（远程武器才被加成）。
func isRangedWeapon() -> bool:
	return (CoreConst.Type.Ranged in types) and isWeapon()


# 对齐 ItemDescriptor.gd:337-338
func isStartingWeapon() -> bool:
	return isWeapon() and not identifier == "Stone"


# 对齐 ItemDescriptor.gd:349-355（+ Game.gd:724-734 的 loadExclusiveContent /
# loadUnreleasedContent）。只有三条分支的**真值**，不做「未发行物品一律当已发行」的
# 简化 —— 那会让 ItemPool / Recipe 多捞出本不该出现的物品。
func isReleased() -> bool:
	if releaseState == ReleaseState.Demo:
		return true
	elif releaseState == ReleaseState.Full:
		return _playtest or _full_version or _editor
	else:
		return _full_version and (_editor or _playtest or _engineer_test)


# 对齐 ItemDescriptor.gd:236-243
func getPrice():
	return price


func getSellPrice():
	return ceil(getPrice() * 0.5)


func getSalePrice():
	return ceil(getPrice() * 0.5)


func getTranslatedName() -> String:
	return name


# 由既有数据（battle_items.json 或测试用字典）填充
# ★ 注意：本方法刻意做成**实例工厂**（`.new().fromDict(d)`），而不是 static 工厂。
#   原因：GDScript 3 不允许脚本用自身的 class_name 自引用（`CoreItemData.new()` /
#   `-> CoreItemData` 都会触发 "couldn't be fully loaded (cyclic dependency)"）。
#   实例式工厂与 CoreDamageSource.init / CoreBuff.init 的既有写法一致。
func fromDict(d: Dictionary):
	var o = self
	o.name = str(d.get("name", ""))
	o.identifier = str(d.get("identifier", d.get("name", "")))
	o.itemIndex = int(d.get("index", 0))
	o.minDam = int(d.get("minDam", 0))
	o.maxDam = int(d.get("maxDam", 0))
	o.staminaCost = float(d.get("staminaCost", 0.0))
	o.block = int(d.get("block", 0))
	o.cd = float(d.get("cd", 0.0))
	o.extraCds = d.get("extraCds", [])
	o.accuracy = float(d.get("accuracy", 100.0))
	o.canActivate = CoreConst.truth(d.get("canActivate", true))
	o.chance = float(d.get("chance", 0.0))
	o.chance2 = float(d.get("chance2", 0.0))
	o.shopChance = float(d.get("shopChance", 0.0))
	o.types = d.get("types", [])
	o.tags = int(d.get("tags", 0))
	o.physics = int(d.get("physics", 0))
	o.rarity = int(d.get("rarity", 0))
	o.price = int(d.get("price", 0))
	o.classes = int(d.get("classes", 0))
	o.randomUniquePool = CoreConst.truth(d.get("randomUniquePool", false))
	o.hasBattleRageEffect = CoreConst.truth(d.get("hasBattleRageEffect", false))
	o.gatedItems = d.get("gatedItems", [])
	o.startsSubclass = str(d.get("startsSubclass", ""))
	# 门控 / 合成来源 / 发行状态（见字段处注释）。键名同时接受 camel 与
	# ItemBook 表格列名的 snake 形态，装配层从任一来源填都行。
	o.gateItem = d.get("gateItem", d.get("gate_item", null))
	o.originatingRecipes = d.get("originatingRecipes", d.get("originating_recipes", []))
	o.releaseState = int(d.get("releaseState", d.get("release_state", ReleaseState.Full)))
	o.params = d.get("params", [])
	# 具名参数：camel（内核/测试）与 snake（battle_items.json 的原始键）都接受。
	# ★ paramBases / paramBases_inverted **只从具名参数派生**（原版唯一来源就是
	#   addNamedParam），不再从字典另读一份 —— 单一真值源，避免两表打架。
	#   漏了这一步的后果：任何 getP_m("<带分隔符的具名参数>") 会在
	#   getParamModified 里 `descriptor.paramBases[...]` 直接报错（Sandbag 的
	#   getBuffDur → getP_m("dur") 即此路径）。
	var np = d.get("namedParams", d.get("named_params", {}))
	for k in np:
		o.addNamedParam(k, np[k])
	o.gainedStacks = int(d.get("gainedStacks", 0))
	o.removedStacks = int(d.get("removedStacks", 0))
	o.usedStacks = int(d.get("usedStacks", 0))
	return o
