extends Node2D
class_name CharacterStatIcon

const suffixes = {
	Character.Stat.HealEfficiency: "%", 
	Character.Stat.DamageResistance: "%", 
	Character.Stat.CritResistance: "%", 
	Character.Stat.StunResistance: "%", 
	Character.Stat.MeleeDmgFactor: "%", 
	Character.Stat.RangedDmgFactor: "%", 
	Character.Stat.EffectDmgFactor: "%", 
	Character.Stat.Unhealing: "%", 
	Character.Stat.StaminaRegen: "%", 
	Character.Stat.MaxHealthGain: "%"
}

const removeMinus = {
	Character.Stat.HealEfficiency: true, 
	Character.Stat.DamageResistance: true, 
	Character.Stat.StaminaRegen: true, 
	Character.Stat.MaxHealthGain: true
}

onready var label = $Label
onready var icon = $TextureRect

var poolingHandle
var stat: int
var tween = null
var active: = false
var default = null
var suffix: = ""
var positiveTexture
var negativeTexture
var positiveKeyword: String
var negativeKeyword: String

func preset():
	pass

func setStat(_stat: int):
	stat = _stat
	var statName = Character.Stat.keys()[stat]
	positiveKeyword = "STAT_" + statName
	negativeKeyword = positiveKeyword + "_NEGATIVE"
	var fileName = "res://Interface/Combat/StatIcons/" + statName
	positiveTexture = load(fileName + ".png")
	Util.statIcons[stat] = positiveTexture
	if Util.sharedDirectory.file_exists(fileName + "_negative.png.import"):
		negativeTexture = load(fileName + "_negative.png")
		Util.statIcons[ - stat] = negativeTexture
	icon.texture = positiveTexture
	suffix = suffixes.get(stat, "")
	hide()

func setStatValue(value):
	if default == null:
		default = value
		return
	
	if is_equal_approx(value, default):
		if active:
			disappear()
		else:
			pass
	else:
		if active:
			updateLabel(value)
			
		else:
			appear()
			updateLabel(value)
			

func updateLabel(value):
	if value > 0:
		icon.keyword = positiveKeyword
		icon.texture = positiveTexture
	else:
		icon.keyword = negativeKeyword
		icon.texture = negativeTexture
		
		if stat in removeMinus:
			value = abs(value)
		
	label.text = str(stepify(value, 0.1)) + suffix
	icon.nameParams = {"val": Util.highlight(label.text)}

func appear():
	active = true
	if Game.combatSceneNode.phase != Game.combatSceneNode.Phase.OffScreen:
		show()
		scale = Vector2.ZERO
		tween = Util.refreshTween(tween)
		tween.tween_property(self, "scale", Vector2.ONE, 0.2)
		tween.set_speed_scale(0)
		set_physics_process(true)

func disappear():
	active = false
	tween = Util.refreshTween(tween)
	tween.tween_property(self, "scale", Vector2.ZERO, 0.3)
	tween.tween_callback(self, "disappeared")
	tween.set_speed_scale(0)
	set_physics_process(true)

func disappeared():
	hide()
	icon.hideTooltip()

func _physics_process(delta):
	if Util.isTweenRunning(tween):
		tween.set_speed_scale(1)
		tween.custom_step(1 / 60.0)
		tween.set_speed_scale(0)
	else:
		set_physics_process(false)
