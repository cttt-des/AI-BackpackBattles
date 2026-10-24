extends Node2D

const MIN_STRENGTH = 0.15
const CHANGE_DUR = 0.3

var startNode
var endNode
var poolingHandle
var sprite
var tween

func preset():
	sprite = $Sprite
	sprite.material.set_shader_param("laserSize", MIN_STRENGTH)

func create(_startNode, _endNode, flip):
	startNode = _startNode
	endNode = _endNode
	sprite.flip_h = flip
	Util.killTween(tween)
	tween = create_tween()
	tween.tween_property(sprite.material, "shader_param/laserSize", 0.24, CHANGE_DUR)
	orient()
	set_physics_process(true)
	
func orient():
	var startPos = startNode.getCraftingPreviewPosition()
	var endPos = endNode.getCraftingPreviewPosition()
	var dif = endPos - startPos
	var length = dif.length()
	global_position = startPos
	look_at(endPos)
	z_index = Util.getGlobalZ(startNode) + 1
	
	Util.stretchSpriteToWidth(sprite, min(80, length))
	sprite.material.set_shader_param("xStretch", sprite.scale.x * 3.13)

func _physics_process(delta: float) -> void :
	if is_instance_valid(startNode) and is_instance_valid(endNode):
		orient()

func stopOrientation():
	set_physics_process(false)

func breakBond():
	Util.killTween(tween)
	tween = create_tween()
	tween.tween_property(sprite.material, "shader_param/laserSize", MIN_STRENGTH, CHANGE_DUR)
	tween.tween_callback(self, "returnToObjectPool")
	

func returnToObjectPool():
	ObjectPool.returnInstance(self)
