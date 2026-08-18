extends OptionsSlider

func initialize():
	value = Settings.getValStr(name)

func onValueChanged(newValue):
	Settings.setValStr(name, newValue)

