extends "res://Interface/Combat/BlockHud.gd"

export var cooldown = 2.0
export var offset = 0.0
export (PackedScene) var activationAnimation

var particles

func _ready():
	Game.connect("combat_start", self, "onCombatStart")
	particles = activationAnimation.instance()
	sprite.add_child(particles)
	sprite.material = sprite.material.duplicate()
	sprite.material.set_shader_param("progress", 1.0)
	set_process(false)

func onCombatStart():
	set_process(true)

func onLeaveCombat():
	.onLeaveCombat()
	set_process(false)

func _process(delta):
	var progress = fmod(Game.getCombatOrReplayTime() - offset, cooldown) / cooldown
	sprite.material.set_shader_param("progress", 1.0 - progress)

func activate():
	particles.activate()
