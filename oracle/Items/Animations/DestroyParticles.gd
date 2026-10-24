extends Particles2D

var poolingHandle
var animationPlayer
var sprite
var shadow

func preset():
	animationPlayer = $AnimationPlayer
	sprite = $Sprite
	shadow = $Sprite / Shadow
	
func activate(spriteToCopy: Sprite, knockback: Vector2):
	sprite.texture = spriteToCopy.texture
	shadow.texture = spriteToCopy.texture
	sprite.scale = spriteToCopy.scale
	global_rotation = spriteToCopy.global_rotation
	sprite.position = spriteToCopy.offset * spriteToCopy.global_scale
	shadow.global_position = sprite.global_position + Item.shadowOffset_dropped
	process_material.set_shader_param("scale", 0.12)
	process_material.set_shader_param("sprite", spriteToCopy.texture)
	var resolution = spriteToCopy.texture.get_size() * spriteToCopy.global_scale * 0.7
	process_material.set_shader_param("resolution", resolution)
	amount = resolution.x * resolution.y
	
	
	
	var dir = knockback.normalized()
	dir = dir.rotated( - rotation)
	process_material.set_shader_param("direction", Vector3(dir.x, dir.y, 0))
	process_material.set_shader_param("initial_linear_velocity", knockback.length() * 1.2 + 20)
	animationPlayer.play("Activate")

func returnToObjectPool():
	ObjectPool.returnInstance(self, poolingHandle)
