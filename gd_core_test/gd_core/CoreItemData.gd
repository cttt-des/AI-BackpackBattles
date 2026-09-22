# =============================================================================
# CoreItemData.gd — 无头战斗内核：物品静态数据（ItemDescriptor 的无头子集）
# =============================================================================
# 对齐源码：Items/ItemDescriptor.gd
#   · getP(index)           ItemDescriptor.gd:107（int 下标 → params[]；字符串 → namedParams）
#   · paramBases            首段基名表，供 Item.getParamModified 使用
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

var params: Array = []
var namedParams: Dictionary = {}
var paramBases: Dictionary = {}

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


func hasParam(paramName: String) -> bool:
	return paramName in paramBases


func hasTag(tag) -> bool:
	return tags & tag


func isWeapon() -> bool:
	return (CoreConst.Type.Weapon in types)


func getIndex() -> int:
	return 0


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
	o.minDam = int(d.get("minDam", 0))
	o.maxDam = int(d.get("maxDam", 0))
	o.staminaCost = float(d.get("staminaCost", 0.0))
	o.block = int(d.get("block", 0))
	o.cd = float(d.get("cd", 0.0))
	o.extraCds = d.get("extraCds", [])
	o.accuracy = float(d.get("accuracy", 100.0))
	o.canActivate = bool(d.get("canActivate", true))
	o.chance = float(d.get("chance", 0.0))
	o.chance2 = float(d.get("chance2", 0.0))
	o.shopChance = float(d.get("shopChance", 0.0))
	o.types = d.get("types", [])
	o.tags = int(d.get("tags", 0))
	o.physics = int(d.get("physics", 0))
	o.rarity = int(d.get("rarity", 0))
	o.params = d.get("params", [])
	o.namedParams = d.get("namedParams", {})
	o.paramBases = d.get("paramBases", {})
	o.gainedStacks = int(d.get("gainedStacks", 0))
	o.removedStacks = int(d.get("removedStacks", 0))
	o.usedStacks = int(d.get("usedStacks", 0))
	return o
