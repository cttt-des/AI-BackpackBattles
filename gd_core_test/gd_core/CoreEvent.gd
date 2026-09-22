# =============================================================================
# CoreEvent.gd — 无头战斗内核：战斗事件
# =============================================================================
# 对齐源码：Core/CombatEvent.gd（全文 208 行）
#
# 保留（参与判定/被物品行为读取）：id / timestamp / parentEvent / origin / type /
#   target / params，以及 getType / setTarget / setParam / getParam / getAmount /
#   getAmountWithDefault / hasParam / getMainActor / getOrigin / fromCharacter / getDepth
#
# 剥离内容（纯呈现，判定不读）：
#   · formatParams 的文案填充（Util.tra / Util.getIcon / 颜色包裹）
#   · asText()（HTML/魔法文本渲染，1279 行的 CombatLog 职责）
#   · damageColor* 常量与 damageFormat
#   → 事项：`formatParams` 字段保留但不填充，避免任何外部代码因字段缺失崩溃。
# =============================================================================
extends Reference
class_name CoreEvent


enum Target{
	Player, 
	Opponent
}

var id: int
var timestamp
var parentEvent
var origin
var type
var target = null
var params = {}
var formatParams = {}


func _init(_id, _timestamp = 0.0, _parentEvent = null, 
	_origin = null, _type = null):
	
	id = _id
	timestamp = _timestamp
	parentEvent = _parentEvent
	origin = _origin
	type = _type


func getType() -> int:
	return type


func setTarget(_target):
	target = _target


func setParam(paramName, paramVal):
	params[paramName] = paramVal


func getParam(paramName, default):
	return params.get(paramName, default)


func getAmount():
	return params["amount"]


func getAmountWithDefault(default):
	return params.get("amount", default)


func hasParam(param) -> bool:
	return param in params


func getMainActor() -> int:
	if origin is CoreItem:
		return origin.character().playerId
	elif target:
		return target
	else:
		return CoreCharacter.ID.PLAYER


func getOrigin():
	return origin


func fromCharacter(character) -> bool:
	return origin is CoreItem and origin.character() == character


func getDepth() -> int:
	if parentEvent:
		return parentEvent.getDepth() + 1
	else:
		return 0
