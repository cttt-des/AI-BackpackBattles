extends Node2D

onready var sheet = $Sheet / Sheet
onready var animation = $AnimationPlayer
onready var vbox = $Sheet / VBoxContainer
onready var label = $Sheet / VBoxContainer / RichTextLabel
onready var cancelButton = $Sheet / VBoxContainer / CancelButton
onready var confirmButton = $Sheet / VBoxContainer / ConfirmButton

func open(textKey, confirmKey, cancelKey):
	Game.UINode.add_child(self)
	Game.pause(Game.PauseSource.RecipeBook)
	animation.play("Show")
	label.translationKey = textKey
	label.updateLocale()
	cancelButton.translationKey = cancelKey
	cancelButton.updateLocale()
	if confirmKey:
		confirmButton.show()
		confirmButton.translationKey = confirmKey
		confirmButton.updateLocale()
	else:
		confirmButton.hide()

func close():
	if visible and animation.current_animation == "":
		animation.play("Hide")

func onClosed():
	Game.unpause(Game.PauseSource.RecipeBook)
	get_parent().remove_child(self)

func onCancelPressed():
	close()

func onConfirmPressed():
	close()
	Game.switchToCombat()
