extends Node2D



onready var animation = $AnimationPlayer
onready var itemNode = $Book / Items
onready var classDropdownButton = $Book / ClassDropdown / Classes
onready var sharedFolder = $Book / Items / Shared
onready var counterLabel = $Book / Counter
onready var closeButton = $Book / CloseButton

var classFolderNodes = []
var isOpen = false
var selectedClass: int





func _ready() -> void :
	
	for c in Game.Classes_Full.size():
		if Game.isClassUnlocked(c):
			classFolderNodes.push_back(itemNode.get_node(Game.Classes_Full.keys()[c]))
	
	
	
	for folder in classFolderNodes + [sharedFolder]:
		for item in folder.get_children():
			if item is Item:
				item.initRecipeBook()
	
	Game.connect("warp_cursor_menu", self, "onCursorWarp")

func updateLocale():
	
	Util.localizeFonts(self)
	addDropDownClasses()
	$Book / Label2.updateLocale()
	$Book / CloseButton.updateLocale()
	
func addDropDownClasses():
	classDropdownButton.clearList()
	for c in Game.Classes_Full.size():
		if Game.isClassUnlocked(c):
			classDropdownButton.addItem(Game.getClassName(c), Game.classIcons[c])
			

func checkCrafted():
	for folder in classFolderNodes + [sharedFolder]:
		for item in folder.get_children():
			if item is Item:
				var crafted = Game.getNumCrafted(item.name) > 0
				
				
				
				if not crafted:
					
					
					
					
					
					item.modulate = Color(0.337891, 0.236021, 0.194346, 0.87)
					item.brightColor = Color.white
					item.defaultColor = item.modulate
					
				else:
					item.modulate = Color(1, 1, 1, 0.87)
					item.brightColor = Color(1.3, 1.3, 1.3, 1)
					item.defaultColor = item.modulate
				
				item.enableTooltip()

func showClassFolder(classI):
	selectedClass = classI
	
	for folder in classFolderNodes:
		folder.hide()
	
	classFolderNodes[classI].show()
	
	var total = 0
	var numCrafted = 0
	
	var folders = [sharedFolder, classFolderNodes[classI]]
	
	for folder in folders:
		for item in folder.get_children():
			if item is Item:
				var crafted = Game.getNumCrafted(item.name) > 0
				if crafted:
					numCrafted += 1
				total += 1
	
	counterLabel.text = str(numCrafted, "/", total)

func onClassSelected(classI, _className):
	showClassFolder(classI)

func open() -> void :
	if not Game.draggedItem and not is_inside_tree():
		Game.UINode.add_child_below_node(Game.UINode.get_node("RecipeBookPlaceholder"), self)
		isOpen = true
		Game.openMenu()
		Game.pause(Game.PauseSource.RecipeBook)
		Sound.playSound_process(Game.transitionSounds[2], 0, 0.9)
		
		updateLocale()
		animation.play("Open")
		InputBlocker.disableAllControls(InputBlocker.Source.Popup, Game.shopSceneNode)
		InputBlocker.disableAllControls(InputBlocker.Source.Popup, Game.playerNode)
		InputBlocker.disableAllControls(InputBlocker.Source.Popup, Game.titleScreen)
		for node in get_tree().get_nodes_in_group("PinnedControl"):
			InputBlocker.disableSingleControl(InputBlocker.Source.Popup, node)
		
		InputBlocker.activate(InputBlocker.Source.PopupAnimation, false)
		
		checkCrafted()
		var selected = Game.curClass
		if not Game.isClassUnlocked(selected):
			selected = Game.Classes.Ranger
		classDropdownButton.selectItemByIndex(selected)
		showClassFolder(selected)
		deactivateParticles(self)

func deactivateParticles(node):
	if node is Particles2D and not node.emitting:
		node.restart()
		node.emitting = false
	for child in node.get_children():
		deactivateParticles(child)
		

func opened():
	InputBlocker.deactivate(InputBlocker.Source.PopupAnimation, false)
	Game.openedMenu()

func close() -> void :
	if animation.current_animation == "":
		animation.play("Close")
		Game.unhoverAndHideTooltips()
		InputBlocker.activate(InputBlocker.Source.PopupAnimation, false)
		Game.unpause(Game.PauseSource.RecipeBook)
		Sound.playSound(Game.transitionSounds[1], 0, 1.2)
		Game.closeMenu()

func closed():
	InputBlocker.deactivate(InputBlocker.Source.PopupAnimation, false)
	InputBlocker.restoreAllControls(InputBlocker.Source.Popup)
	isOpen = false
	get_parent().remove_child(self)


func _unhandled_input(event: InputEvent) -> void :
	if Util.isActionPressed_event(event, "options"):
		if isOpen:
			get_tree().set_input_as_handled()
			close()

func onCursorWarp():
	if isOpen:
		for item in classFolderNodes[selectedClass].get_children():
			if item is Item:
				Game.addItemOfInterest(item)

		for item in sharedFolder.get_children():
			Game.addItemOfInterest(item)
		
		Game.addControlOfInterest(classDropdownButton)
		Game.addControlOfInterest(closeButton)
