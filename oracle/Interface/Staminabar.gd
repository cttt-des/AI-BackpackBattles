extends Node2D

onready var staminaMat = $Bar.material
onready var label = $Label
onready var character = get_parent().get_parent()

var displayRelStamina: float

func _ready() -> void :
	set_process(false)
	Game.connect("switching_to_combat", self, "onEnteringCombat")
	Game.connect("combat_scene_left", self, "onCombatLeft")
	resetBar()
	call_deferred("ready_deferred")

func onEnteringCombat():
	resetBar()
	set_process(true)

func onCombatLeft():
	set_process(false)

func resetBar():
	staminaMat.set_shader_param("lastDamagePercentage", 1)
	staminaMat.set_shader_param("healthPercentage", 1)
	displayRelStamina = 1.0

func ready_deferred():
	updateNumber()

func _process(_delta: float) -> void :
	var relStamina = character.curStamina / character.getMaxStamina()
	relStamina *= 1.02
	staminaMat.set_shader_param("lastDamagePercentage", relStamina)
	displayRelStamina = lerp(displayRelStamina, relStamina, _delta * 2)
	staminaMat.set_shader_param("healthPercentage", displayRelStamina)
	
	updateNumber()

func updateNumber():
	var currentStamina = Util.floorStepify(character.curStamina, 0.1)
	label.text = str(currentStamina, "/", stepify(character.getMaxStamina(), 0.1))

	
	
	
	
