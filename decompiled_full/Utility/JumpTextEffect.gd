tool
extends RichTextEffect

const curve = preload("res://Utility/TextCurve.tres")


var bbcode = "jump"

const SPLITTERS = [ord(" "), ord("."), ord(",")]

var _w_char = 0
var _last = 999


func _process_custom_fx(char_fx):
	if char_fx.absolute_index < _last or char_fx.character in SPLITTERS:
		_w_char = char_fx.absolute_index
	
	_last = char_fx.absolute_index
	var relative = char_fx.relative_index / char_fx.get_environment()["len"]
	
	var t = abs(sin(char_fx.elapsed_time * 5.0 + char_fx.absolute_index * 0.2)) * 4.0
	var angle = deg2rad(char_fx.env.get("angle", 0))
	
	
	var offset = curve.interpolate(relative)
	char_fx.offset.y -= offset * 15.0
	char_fx.offset.y += cos(angle) * t
	return true
