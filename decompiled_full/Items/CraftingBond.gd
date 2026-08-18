extends Node2D

enum BondType{
	Normal, 
	Catalyst
}

const MIN_STRENGTH: = 0.15
const MIN_STRENGTH_CATALYST: = 0.07
const MIN_LENGTH: = 30.0
const CHANGE_DUR: = 0.3
const WEAK_STRENGTH: = 0.2
const STRONG_STRENGTH: = 0.27

export var stretchFactor = 3.13
export (BondType) var bondType: int

var startNode
var endNode
var poolingHandle
var sprite
var tween
var fadeAcc: = 0.0
var targetStrength: float

func preset():
	sprite = $Sprite
	sprite.modulate.a = MIN_STRENGTH
	
func create(_startNode, _endNode):
	startNode = _startNode
	endNode = _endNode
	set_process(true)
	







func _process(delta: float) -> void :
	if is_instance_valid(startNode) and is_instance_valid(endNode):
		var startPos = startNode.global_position
		var endPos = endNode.global_position
		var dif = endPos - startPos
		var length = dif.length()
		if length < MIN_LENGTH:
			startPos += Vector2.LEFT * MIN_LENGTH * 0.5
			endPos = startPos + Vector2.RIGHT * MIN_LENGTH * 0.5
			length = MIN_LENGTH
		global_position = startPos
		look_at(endPos)
		
		
		Util.stretchSpriteToWidth(sprite, length)
		sprite.material.set_shader_param("xStretch", sprite.scale.x * stretchFactor)
		if (startNode.isMovingBack() or endNode.isMovingBack()):
			fadeAcc = 0.0
		else:
			if fadeAcc == 0.0:
				fadeAcc = 0.6
			fadeAcc += delta * 8.0
		
		sprite.self_modulate.a = clamp(1.0 - (length / 2000), 0.0, 1)
		sprite.self_modulate.a *= clamp(fadeAcc, 0, 1)
	
func setStrong():
	targetStrength = STRONG_STRENGTH
	tween = Util.refreshTween(tween)
	tween.tween_property(sprite, "modulate:a", targetStrength, CHANGE_DUR)

func setWeak():
	targetStrength = WEAK_STRENGTH
	tween = Util.refreshTween(tween)
	tween.tween_property(sprite, "modulate:a", targetStrength, CHANGE_DUR)

func breakBond():
	set_process(false)
	tween = Util.refreshTween(tween)
	var minStrength = MIN_STRENGTH if bondType == BondType.Normal else MIN_STRENGTH_CATALYST
	tween.tween_property(sprite, "modulate:a", minStrength, CHANGE_DUR)
	tween.tween_callback(self, "returnToObjectPool")

func breakInstant():
	set_process(false)
	var minStrength = MIN_STRENGTH if bondType == BondType.Normal else MIN_STRENGTH_CATALYST
	sprite.modulate.a = minStrength
	returnToObjectPool()

func flash():
	tween = Util.refreshTween(tween)
	var flashStrength: float
	if targetStrength == WEAK_STRENGTH:
		flashStrength = 0.3
	elif bondType == BondType.Normal:
		flashStrength = 0.33
	else:
		flashStrength = 0.43
	
	var flashColor = Color(2, 0.9, 0.9, flashStrength)
	var targetColor = Color(1.2, 1.2, 1.2, targetStrength)
	tween.tween_property(sprite, "modulate", flashColor, 0.07)
	tween.tween_property(sprite, "modulate", targetColor, 0.3).from(flashColor)






func returnToObjectPool():
	ObjectPool.returnInstance(self)
