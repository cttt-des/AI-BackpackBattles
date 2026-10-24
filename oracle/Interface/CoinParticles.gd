extends Particles2D

var poolingHandle

func preset():
	pass

func activate(numCoins, startPos, targetPos):
	
	var direction = Vector3(0, - 1, 0)
	process_material.set_shader_param("direction", 
		Vector3(direction.x, direction.y, 0))
	process_material.set_shader_param("pullCenter", targetPos)
	amount = numCoins
	restart()
