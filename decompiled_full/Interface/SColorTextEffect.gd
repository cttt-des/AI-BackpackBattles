tool
extends RichTextEffect

var bbcode = "sc"




func _process_custom_fx(char_fx: CharFXTransform):






	var env = char_fx.get_environment()
	if char_fx.color == Game.SOFTWHITE:
		if env["len"] > char_fx.relative_index:
			char_fx.color = env["color"]
	
	return true
