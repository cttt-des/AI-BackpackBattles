extends LocalizedControl

const jumpCode = "[jump angle=180 len={len}][center]"

func updateLocale():
	prefix = jumpCode.format({"len": Util.tr(translationKey).length()})
	.updateLocale()
