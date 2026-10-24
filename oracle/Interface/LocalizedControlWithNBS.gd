extends LocalizedControl

var originalSuffix

func updateLocale():
	if originalSuffix == null:
		originalSuffix = suffix
	if TranslationServer.get_locale() == "fr":
		suffix = Util.nonBreakingSpace + suffix
	else:
		suffix = originalSuffix
	.updateLocale()
