extends Sprite

onready var default = texture

const localized = {
	"ja": preload("res://Assets/TitleScreen/Title_Japanese.png"), 
	"zh_Hans_CN": preload("res://Assets/TitleScreen/Title_SimplifiedChinese.png"), 
}

func updateLocale():
	var locale = TranslationServer.get_locale()
	if locale in localized:
		texture = localized[locale]
	else:
		texture = default
