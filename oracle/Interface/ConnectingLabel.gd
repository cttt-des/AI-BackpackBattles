extends RichTextLabel

var hiddenChars = 3

var charsToHide = 3

func _ready() -> void :
	add_to_group("Localized")
	updateLocale()
	
func updateLocale():
	if TranslationServer.get_locale() == "zh_Hans_CN":
		charsToHide = 3
	else:
		charsToHide = 4
	
	hiddenChars = charsToHide
	bbcode_text = tr("UI_Connecting")
	visible_characters = text.length() - hiddenChars

func timeout():
	hiddenChars = ((hiddenChars - 1) + charsToHide) % charsToHide
	visible_characters = text.length() - hiddenChars

