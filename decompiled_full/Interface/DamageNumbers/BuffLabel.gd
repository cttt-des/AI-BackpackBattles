extends Node2D

enum ChangeType{
	Gain, 
	Resisted, 
	Protected, 
	Reflected
}

const positiveColor = Color(0.590118, 1, 0.566406)
const negativeColor = Color(1, 0.566406, 0.566406)
const labelFormat = "[center][color=#{color}]{text}"
const buffFormat = "[center][color=#{color}]{changeType}{amount}{icon}"
const g = 100.0

var white_html = Color.white.to_html()
var positiveColor_html = positiveColor.to_html()
var negativeColor_html = negativeColor.to_html()

var label
var animation
var linear_velocity = Vector2()
var gravity_scale = 0.0

func preset():
	animation = $AnimationPlayer
	label = $Label

func _physics_process(delta):
	linear_velocity.y += g * delta * gravity_scale
	position += linear_velocity * delta



func spawnLabel(type, amount = 0, changeType = ChangeType.Gain, appliedToOpponent = null):
	Util.localizeFonts(label)
	gravity_scale = 1
	modulate = Color.white
	
	var itemBuff = false
	
	if type == Game.EventType.MissedAttack:
		label.bbcode_text = labelFormat.format({
			"color": white_html, 
			"text": Util.tra("LABEL_Miss")})
		gravity_scale = 5
	
	elif type == Game.EventType.CriticalResisted:
		label.bbcode_text = labelFormat.format({
			"color": positiveColor_html, 
			"text": Util.tra("LABEL_CritResisted")})
	
	elif type == Game.EventType.StunResisted:
		label.bbcode_text = labelFormat.format({
			"color": positiveColor_html, 
			"text": Util.tra("LABEL_StunResisted")})
	
	elif type == Game.EventType.Stun:
		label.bbcode_text = labelFormat.format({
			"color": negativeColor_html, 
			"text": Util.tra("LABEL_Stunned").format({"dur": str(amount, Util.tra("FORMAT_Second"))})})
	
	elif changeType == ChangeType.Resisted:
		if Game.isBuff(type):
			var text = Util.tra("LABEL_BuffNullified").format({
				"amount": amount, 
				"debuff": Util.getIcon(Game.typeToKeyword(type), 40)
			})
			label.bbcode_text = labelFormat.format({
				"color": negativeColor_html, 
				"text": text
			})
		else:
			var text = Util.tra("LABEL_DebuffResisted").format({
				"amount": amount, 
				"debuff": Util.getIcon(Game.typeToKeyword(type), 40)
			})
			label.bbcode_text = labelFormat.format({
				"color": positiveColor_html, 
				"text": text
			})
	
	elif changeType == ChangeType.Protected:
		if Game.isBuff(type):
			var text = Util.tra("LABEL_BuffProtected").format({
				"amount": amount, 
				"buff": Util.getIcon(Game.typeToKeyword(type), 40)
			})
			label.bbcode_text = labelFormat.format({
				"color": positiveColor_html, 
				"text": text
			})
		else:
			var text = Util.tra("LABEL_DebuffProtected").format({
				"amount": amount, 
				"debuff": Util.getIcon(Game.typeToKeyword(type), 40)
			})
			label.bbcode_text = labelFormat.format({
				"color": negativeColor_html, 
				"text": text
			})
	
	elif changeType == ChangeType.Reflected:
		var text = Util.tra("LABEL_DebuffReflected").format({
			"amount": amount, 
			"debuff": Util.getIcon(Game.typeToKeyword(type), 40)
		})
		label.bbcode_text = labelFormat.format({
			"color": positiveColor_html, 
			"text": text
		})
	
	else:
		itemBuff = true
		var color
		
		var positive = Game.isBuff(type)
		if amount < 0:
			positive = not positive
			
		
		if appliedToOpponent:
			positive = not positive
		
		var changePrefix = ""
		if amount > 0:
			changePrefix = "+"
			
		if positive:
			color = positiveColor_html
		else:
			color = negativeColor_html
		
		var icon = Util.getIcon(Game.typeToKeyword(type), 40)
		
		label.bbcode_text = buffFormat.format({
			"color": color, 
			"changeType": changePrefix, 
			"amount": amount, 
			"icon": icon
		})
		
	
	if itemBuff:
		animation.play("ItemBuff")
	else:
		animation.play("Buff")


func spawnLabelOnItem(type: int, amount):
	Util.localizeFonts(label)
	gravity_scale = 1
	modulate = Game.damageNumberColors[type]
	
	if type == Game.EventType.DealDamage:
		label.bbcode_text = str("[center]", amount)
		
		animation.play("Damage")
	
	elif type == Game.EventType.CriticalDamage:
		label.bbcode_text = str("[center][shake rate=20 level=30]", amount)
		modulate = Game.damageNumberColors[type]
		
		animation.play("Damage")
	
	elif type == Game.EventType.Health:
		label.bbcode_text = str("[center]+", amount)
		
		animation.play("Damage")
	
	elif type == Game.EventType.TemporaryMaxHealth:
		label.bbcode_text = str("[center]+", amount)
		
		animation.play("Damage")
	
	elif type == Game.EventType.MissedAttack:
		label.bbcode_text = "[center]" + Util.tra("LABEL_Miss")
		animation.play("Damage")
	
	elif type == Game.EventType.Stamina:
		label.bbcode_text = str("[center]+", amount)
		animation.play("Damage")
	
	elif type == Game.EventType.TemporaryMaxStamina:
		label.bbcode_text = str("[center]+", amount)
		animation.play("Damage")
	
	elif type == Game.EventType.Fatigue:
		label.bbcode_text = str("[center]", amount)
		modulate = Game.damageNumberColors[type]
		animation.play("Damage")
	
	elif type == Game.EventType.DamageBuff:
		var imgBb = Util.imageToBbcode(Util.weaponIcons[Item.Stat.MaxDamage].get_path(), 40)
		
		if amount > 0:
			
			label.bbcode_text = buffFormat.format({
				"changeType": "+", 
				"amount": amount, 
				"color": positiveColor_html, 
				"icon": imgBb
			})
		else:
			
			
			label.bbcode_text = buffFormat.format({
				"changeType": "", 
				"amount": amount, 
				"color": negativeColor_html, 
				"icon": imgBb
			})
		animation.play("ItemBuff")
	
	elif type == Game.EventType.CooldownAdvance:
		var imgBb = Util.imageToBbcode(Util.weaponIcons[Item.Stat.Cooldown].get_path(), 40)
		
		amount = stepify(amount, 0.1)
		
		label.bbcode_text = buffFormat.format({
			"color": positiveColor_html, 
			"changeType": "", 
			"amount": str(amount, Util.tra("FORMAT_Second")), 
			"icon": imgBb
		})
		animation.play("ItemBuff")


func spawnStatLabelOnItem(stat: int, amount, onOpponent):
	Util.localizeFonts(label)
	gravity_scale = 1
	
	var prettyAmount = str(stepify(amount, 0.1))
	prettyAmount += CharacterStatIcon.suffixes[stat]
	
	var positive: bool = amount > 0
	
	var color
	if positive:
		if onOpponent:
			color = negativeColor_html
		else:
			color = positiveColor_html
	else:
		if onOpponent:
			color = positiveColor_html
		else:
			color = negativeColor_html
	
	if not positive:
		stat *= - 1
	var imgBb = Util.imageToBbcode(Util.statIcons[stat].get_path(), 50)
	
	
	label.bbcode_text = buffFormat.format({
		"color": color, 
		"changeType": "+" if positive else "", 
		"amount": prettyAmount, 
		"icon": imgBb
	})
	animation.play("StatChange")
	

func delete():
	animation.stop()
	ObjectPool.returnInstance(self, Util.BUFFLABEL_SCENE)
