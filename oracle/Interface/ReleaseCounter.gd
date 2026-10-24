extends RichTextLabel

func _ready():
	if Game.showExclusiveContent():
		queue_free()
		return
	
	var releaseTime = Time.get_unix_time_from_datetime_string("2024-03-08 10:00:00.000")
	var curTime = Time.get_unix_time_from_system()
	
	
	var daysToRelease = (releaseTime - curTime) / (60 * 60 * 24)
	
	
	bbcode_text = "[center]"
	
	if daysToRelease < 0:
		
		bbcode_text += "Backpack Battles is out!"
	elif daysToRelease < 1:
		
		bbcode_text += "Backpack Battles releases today!"
	else:
		
		bbcode_text += "Backpack Battles releases in {days} days!".format({
			"days": Util.wrapInColor(str(floor(daysToRelease)), Util.paramColor)
		})
	
