extends Node2D

signal force_start
signal cancel

var label
var issuesLabel
var animation
var forceStartButton
var cancelButton

func preset():
	label = $Label
	issuesLabel = $IssuesLabel
	animation = $AnimationPlayer
	forceStartButton = $ForceStartButton
	cancelButton = $CancelButton
	
	

func setContent(lines: Array):
	var text = ""
	for line in lines:
		if line.begins_with("  - "):
			
			text += "    " + line + "\n"
		elif line.ends_with("："):
			
			text += "• " + line + "\n"
		else:
			text += "• " + line + "\n"
	issuesLabel.bbcode_text = "[center]" + text.trim_suffix("\n")

func showPopup():
	animation.play("Show")

func close():
	animation.play("Hide")

func onClosed():
	animation.stop()
	queue_free()

func onForceStartPressed():
	emit_signal("force_start")
	close()

func onCancelPressed():
	emit_signal("cancel")
	close()
