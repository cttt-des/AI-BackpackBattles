extends Reference
class_name CombatEvent

enum Target{
	Player, 
	Opponent
}

var id: int
var timestamp
var parentEvent
var origin
var type
var snapshot
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
	if target == Character.ID.PLAYER:
		formatParams["target"] = Util.tra("LOG_PLAYER")
	else:
		formatParams["target"] = Util.tra("LOG_OPPONENT")

func setParam(paramName, paramVal):
	params[paramName] = paramVal
	formatParams[paramName] = paramVal

func getParam(paramName, default):
	return params.get(paramName, default)

func getAmount():
	return params["amount"]

func getAmountWithDefault(default):
	return params.get("amount", default)

func hasParam(param) -> bool:
	return param in params

func getMainActor() -> int:
	if origin is Item:
		return origin.character().playerId
	elif target:
		return target
	else:
		return Character.ID.PLAYER

func getOrigin():
	return origin

func fromCharacter(character) -> bool:
	return origin is Item and origin.character() == character











func getDepth() -> int:
	if parentEvent:
		return parentEvent.getDepth() + 1
	else:
		return 0

const damageColorPlayer = Color(0.755859, 0.008859, 0)
const damageColorOpponent = Color(1, 0.59079, 0.585938)
var damageColorPlayer_html = damageColorPlayer.to_html(false)
var damageColorOpponent_html = damageColorOpponent.to_html(false)
const damageFormat = "[b]{damage}[/b]"
var damageFormatDict = {"damage": 0}

	
func asText() -> String:
	var amount = getParam("amount", 0)
	
	
	
	var typeStr = Game.eventTypeKeys[type]
	var key = "LOG_"
	if "amount" in params:
		formatParams["amount"] = abs(amount)
		
		if type == Game.EventType.DamIncrease or type == Game.EventType.DamReduction:
			key += typeStr
			if "type" in params:
				key += "_TYPED"
				formatParams["type"] = Util.getIcon(DamageSource.damTypeNames[params["type"]])
			if "duration" in params:
				key += "_TEMP"
			if params["isPercent"]:
				formatParams["amount"] = str(formatParams["amount"]) + "%"
		
		elif "timeout" in params:
			key += "BuffTimeout"
			formatParams["buff"] = Util.getIcon(Game.typeToKeyword(type))
		else:
			if Game.isBuff(type):
				formatParams["buff"] = Util.getIcon(Game.typeToKeyword(type))
			elif Game.isDebuff(type):
				formatParams["debuff"] = Util.getIcon(Game.typeToKeyword(type))
			
			if getParam("used", false):
				key += "USE_BUFF"
			
			elif getParam("resisted", false):
				if Game.isBuff(type):
					key += "NULLIFY_BUFF"
				else:
					if getParam("reflected", false):
						key += "REFLECT_RESIST"
					else:
						key += "RESIST_DEBUFF"
			
			elif getParam("protected", false):
				if Game.isBuff(type):
					key += "PROTECT_BUFF"
				else:
					key += "PROTECT_DEBUFF"
			else:
				var reflect = getParam("reflected", false)
				if reflect:
					key += "REFLECT_"
				elif amount < 0:
					key += "LOSE_"
				else:
					key += "GAIN_"
				
				if Game.isBuff(type):
					key += "BUFF"
					if amount < 0:
						if getMainActor() == target:
							key += "_SELF"
					else:
						if "duration" in params:
							key += "_TEMP"
						if getMainActor() != target:
							
							key += "_OPPONENT"
						
				
				elif Game.isDebuff(type):
					key += "DEBUFF"
					if not reflect and amount > 0 and getMainActor() == target:
						key += "_SELF"
					if "duration" in params:
						key += "_TEMP"
				else:
					key += typeStr
		
		
	else:
		key += typeStr
	
	if type == Game.EventType.CriticalDamage:
		var damage = getParam("damage", 0)
		if getMainActor() == Character.ID.PLAYER:
			damageFormatDict["damage"] = Util.wrapInColor_html(damage, damageColorPlayer_html)
		else:
			damageFormatDict["damage"] = Util.wrapInColor_html(damage, damageColorOpponent_html)
		
		formatParams["damage"] = damageFormat.format(damageFormatDict)
	
	if origin is Item:
		formatParams["origin"] = origin.getTranslatedName()
		
		if origin.character().isPlayer():
			formatParams["actor"] = Util.tra("LOG_PLAYER")
		else:
			formatParams["actor"] = Util.tra("LOG_OPPONENT")
	else:
		
		var keyword = Game.typeToKeyword(origin)
		var icon = Util.getIcon(keyword)
		if icon:
			formatParams["origin"] = icon
		else:
			formatParams["origin"] = Util.tra(keyword + "_NAME")
	
	var text
	var depth = getDepth()
	if depth == 0:
		text = "%2.2f" % timestamp + ":  "
	else:
		text = "  ".repeat(depth) + " > "
	text += Util.tra(key)
	text = text.format(formatParams)
	
	return text
