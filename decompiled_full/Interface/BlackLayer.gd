extends ColorRect

var wardrobeRect = Rect2(1000, 300, 600, 750)


func _unhandled_input(event):
	if (event.is_action_pressed("ui_accept") and 
		not wardrobeRect.has_point(get_global_mouse_position())):
			
		for classButton in Game.titleScreen.classButtonsNode.get_children():
			if classButton.has_focus():
				return
		
		Game.wardrobe.close()


func _gui_input(event):
	if visible and Util.isActionPressed_event(event, "grab_item"):
		Game.wardrobe.close()

func _notification(what):
	if what == NOTIFICATION_VISIBILITY_CHANGED:
		set_process_unhandled_input(visible)
