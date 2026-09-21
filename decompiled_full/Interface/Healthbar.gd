extends Node2D

onready var healthbarMat = $Bar.material
onready var label = $Label
onready var tween = $Tween
onready var character = get_parent().get_parent()

func _ready() -> void :
	character.connect("health_changed_ui", self, "updateBar")
	healthbarMat.set_shader_param("lastDamagePercentage", 1)
	healthbarMat.set_shader_param("healthPercentage", 1)
	call_deferred("ready_deferred")

func ready_deferred():
	updateNumber()

func updateBar(_damageResult = null):
	var maxHealth = character.getMaxHealth()
	var relHealth = character.getRelativeHealth()
	healthbarMat.set_shader_param("lastDamagePercentage", relHealth)
	tween.stop_all()
	tween.remove_all()
	tween.interpolate_property(healthbarMat, "shader_param/healthPercentage", null, relHealth, 0.5)


	tween.start()
	
	updateNumber()

func updateNumber():
	label.text = String(round(character.curHealth)) + "/" + String(round(character.getMaxHealth()))



