extends Node2D








const AffectsInside = 6

const secondPos = Vector2(21, 6)
const thirdPos = Vector2( - 21, 6)

var poolingHandle
var sprites: Dictionary

func _process(delta):
	global_rotation = 0
	

func preset():
	sprites[0] = $Primary
	sprites[2] = $Secondary
	sprites[4] = $Tertiary
	sprites[6] = $Bag
	sprites[7] = $Lightning
	for color in sprites:
		sprites[color].hide()

func setColorActive(color):
	sprites[color].show()
	if color == 2:
		if sprites[0].visible:
			sprites[2].position = secondPos
		else:
			sprites[2].position = Vector2.ZERO
	elif color == 4:
		var numVisible = int(sprites[0].visible) + int(sprites[2].visible)
		if numVisible == 2:
			sprites[4].position = thirdPos
		elif numVisible == 1:
			sprites[4].position = secondPos
		else:
			sprites[4].position = Vector2.ZERO

func returnToObjectPool():
	for color in sprites:
		sprites[color].hide()
	ObjectPool.returnInstance(self)
