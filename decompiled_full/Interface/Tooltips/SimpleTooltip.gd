extends ToolTip

onready var descrLabel = $VBoxContainer / Description

func setParams(header, description):
	if header == "":
		nameLabel.hide()
	else:
		nameLabel.show()
		nameLabel.bbcode_text = centerStr + replaceReferences(highlight(header), 40)
	descrLabel.bbcode_text = replaceReferences(highlight(description))
	Util.localizeFonts(self)
