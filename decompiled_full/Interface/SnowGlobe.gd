extends Node2D

onready var particles1 = $Particles1
onready var particles2 = $Particles2
onready var snowZ = particles1.z_index
var active: = false

func _ready():
	$Button.connect("pressed", self, "onButtonPressed")
	Game.connect("pre_shop_opened_from_title", self, "onEnteringShop")
	Game.connect("return_to_title", self, "onShopToTitle")

func onButtonPressed():
	active = not active
	if active:
		particles1.activate()
		particles2.activate()
	else:
		particles1.deactivate()
		particles2.deactivate()

func onShopToTitle():
	particles1.z_index = 20

func onEnteringShop():
	particles1.z_index = snowZ
