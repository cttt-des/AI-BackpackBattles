extends Node2D

const healthLostParticles = preload("res://Interface/Combat/HealthLostParticles.tscn")
const barWidth = 216

onready var bar = $Bar
onready var healthbarMat = bar.material
onready var label = $Label
onready var tween = $Tween
onready var character = get_parent().get_parent()
var lastRelHealth = 1.0
var updateQueued: = false

func _ready() -> void :
	character.connect("health_changed_ui", self, "onHealthChanged")
	healthbarMat.set_shader_param("lastDamagePercentage", 1)
	healthbarMat.set_shader_param("healthPercentage", 1)
	call_deferred("ready_deferred")

func ready_deferred():
	updateNumber()

func onHealthChanged(_damageResult = null):
	if not updateQueued:
		updateQueued = true
		call_deferred("updateBar")

func updateBar():
	updateQueued = false
	
	var maxHealth = character.getMaxHealth()
	var relHealth = character.getRelativeHealth()
	healthbarMat.set_shader_param("lastDamagePercentage", relHealth)
	tween.stop_all()
	tween.remove_all()
	tween.interpolate_property(healthbarMat, "shader_param/healthPercentage", null, relHealth, 0.5)


	tween.start()
	
	if relHealth < lastRelHealth:
		var amount = round((lastRelHealth - relHealth) * 130)
		if amount > 0:
			var particles = ObjectPool.particleOneShot(healthLostParticles, bar)
			particles.amount = amount
			var leftBorder = relHealth * barWidth
			var rightBorder = lastRelHealth * barWidth
			var xPos = 0.5 * (rightBorder + leftBorder)
			particles.position = Vector2(xPos, 22)
			var boxWidth = 0.5 * (rightBorder - leftBorder)
			particles.process_material.emission_box_extents.x = boxWidth
	
	updateNumber()
	
	lastRelHealth = relHealth

func updateNumber():
	label.text = String(round(character.curHealth)) + "/" + String(round(character.getMaxHealth()))



