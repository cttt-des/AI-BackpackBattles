extends Node2D

const scaleCurve = preload("res://Interface/Combat/BlockShieldScale.tres")
const tooltipScene = preload("res://Interface/Tooltips/SimpleTooltip.tscn")

export (String) var keyword
export var scaleThreshold: = 50

onready var character = get_parent()
onready var tween = $Tween
onready var label = $Label
onready var sprite = $Sprite
onready var baseScale = sprite.scale
onready var animation = $AnimationPlayer
var tooltip
var prevValue

func _ready() -> void :
	sprite.scale = Vector2.ZERO
	label.hide()
	tooltip = tooltipScene.instance()
	Game.UINode.add_child(tooltip)
	Game.connect("switch_to_shop", self, "onLeaveCombat")
	Game.connect("return_to_title", self, "onLeaveCombat")
	prevValue = 0
	updateLocale()
	add_to_group("Localized")

func updateLocale():
	tooltip.setParams(Util.tra(keyword + "_NAME"), Util.tra(keyword + "_DESCR"))

func calcScale(value) -> float:
	if value > scaleThreshold:
		value = scaleThreshold + pow((value - scaleThreshold), 0.65)
	
	var s: = 0.5 + sqrt(value / 100.0)
	
	return s

func updateHud(value):
	if value == prevValue:
		return
	
	if value > prevValue:
		animation.play("Increase")
	else:
		animation.play("Decrease")
		
	tween.stop_all()
	tween.remove_all()
	var targetScale
	if value == 0:
		label.hide()
		targetScale = Vector2.ZERO
	else:
		label.show()
		targetScale = baseScale * calcScale(value)
		label.text = String(value)
	
	tween.interpolate_property(sprite, "scale", null, targetScale, 0.3)
	tween.start()
	
	prevValue = value

func onHover():
	if label.visible:
		Game.onHoverInteractable(self)
		tooltip.forceUpdatePosition(global_position, Vector2(100, 0))
		
	
func onHoverEnd():
	if tooltip.visible:
		Game.onHoverInteractableEnd(self)
		hideTooltip()

func onLeaveCombat():
	hideTooltip()

func hideTooltip():
	tooltip.hide()

func _notification(what):
	if what == NOTIFICATION_PREDELETE:
		if is_instance_valid(tooltip):
			tooltip.discard()
