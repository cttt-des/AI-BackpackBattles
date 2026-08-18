extends FocusGrabbingTextureButton
class_name HistoryRoundButton

var normalTextures = {
	Game.RoundResult.Win: preload("res://Interface/BuildHistory/RoundResultTriangle.png"), 
	Game.RoundResult.Loss: preload("res://Interface/BuildHistory/RoundResultTriangle_Loss.png"), 
	Game.RoundResult.RunOver: null
}


func setResult(res: int):
	match res:
		Game.RoundResult.Win:
			show()


		Game.RoundResult.Loss:
			show()
			
			
		Game.RoundResult.RunOver:
			hide()
		
	texture_normal = normalTextures[res]

func onHover():
	.onHover()
	self_modulate = Color(1.2, 1.2, 1.2)

func onHoverEnd():
	.onHoverEnd()
	self_modulate = Color.white
