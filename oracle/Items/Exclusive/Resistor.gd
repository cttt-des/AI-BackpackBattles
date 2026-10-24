extends Item

onready var heatThreshold: = int(getP("heatt"))
onready var heat: = int(getP("heat"))

func onChargeReceived(_charge):
	if character().getHeat() < heatThreshold:
		giveHeat(heat)
		miniActivate()
	else:
		if animation.current_animation == "":
			animation.play("Failed")
	


































