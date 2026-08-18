extends "res://Utility/PooledScene.gd"

var trophyLabel
var animation

func preset():
	trophyLabel = $Label2
	animation = $Ani
	
func showPopup(numTrophies: int):
	trophyLabel.formatParams = {"num": numTrophies}
	trophyLabel.updateText()
	animation.play("Show")
