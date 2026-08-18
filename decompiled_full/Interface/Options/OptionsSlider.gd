extends BaseSlider
class_name OptionsSlider

func _ready() -> void :
	call_deferred("initialize")

func initialize():
	value = Settings.getValStr(name)

func onValueChanged(newValue):
	Settings.setValStr(name, newValue)
