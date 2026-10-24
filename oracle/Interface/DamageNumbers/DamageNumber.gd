extends Node2D
class_name NumberLabel











const lifetime = 0.8
const SIZE_CURVE = preload("res://Interface/DamageNumbers/DamageNumberSizeCurve.tres")

var chipDamage: bool = false

var animation
var text
var font

var linear_velocity = Vector2()
var gravity_scale = 0.0
const g = 100.0

func _physics_process(delta):
	linear_velocity.y += g * delta * gravity_scale
	position += linear_velocity * delta

static func isDamageNumber(_type):
	return (_type == Game.EventType.DealDamage or 
			_type == Game.EventType.CriticalDamage)

func preset():
	animation = $AnimationPlayer
	text = $Label
	font = text.get("custom_fonts/normal_font")

func _ready():
	linear_velocity = Vector2.ZERO
	gravity_scale = 0
	text.modulate = Color.white
	text.rect_scale = Vector2(1, 1)
	
	font.set("outline_color", Color.black)
	

func spawnNumber(numberType, amount: int):
	rotation = 0
	if numberType == Game.EventType.Health:
		linear_velocity = Vector2(0, - 200)
		animation.play("Heal")
	else:
		rotation = linear_velocity.x * 0.001
		
		if numberType == Game.EventType.CriticalDamage:
			animation.play("Critical")
			gravity_scale = 9.5
		else:
			gravity_scale = 12
			animation.play("Normal")

	var size = int(SIZE_CURVE.interpolate(float(amount) / 100))
	text.set("custom_fonts/normal_font", Util.damageNumberFonts[size])
	
	text.bbcode_text = Game.damageNumberFormats[numberType].format(
		{"amount": amount})
	text.set("custom_colors/default_color", Game.damageNumberColors[numberType])
	
	text.rect_pivot_offset = text.rect_size * 0.5
	
func delete():
	animation.stop()
	ObjectPool.returnInstance(self, Util.NUMBERLABEL_SCENE)

