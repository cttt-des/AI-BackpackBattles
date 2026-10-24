extends Label

export var displayFactor = 1.0

func updateLabel(newValue):
	text = "x" + String(newValue * displayFactor)
