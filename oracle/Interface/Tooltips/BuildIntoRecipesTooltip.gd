extends ToolTip

const dividerScene = preload("res://Interface/Tooltips/RecipeTooltipDivider.tscn")
const recipeScene = preload("res://Interface/Tooltips/BuildIntoRecipe.tscn")
const relatedItemsScene = preload("res://Interface/Tooltips/RelatedItems.tscn")
const lockSound = preload("res://Assets/Sound/Lock.wav")
const ninePatchMargin = 110

var entries = []
var growToRight = true
var maxWidth = 420

onready var recipesHeader = $VBoxContainer / Header
onready var lockHint = $LockHint
onready var lockIcon = $LockHint / Lock
onready var animation = $LockHint / AnimationPlayer

func _ready():
	
	if Game.usingController:
		lockHint.formatParams = {"button": Util.getControllerIconBbcode("show_hints_controller")}
	else:
		lockHint.formatParams = {"button": (Util.getTextForEvent(InputMap.get_action_list("show_hints")[0], true))}
	
	lockHint.updateText()

func setItem(item, asSubTooltip: bool):
	var descriptor = item.descriptor
	var ninePatchMaxWidth = maxWidth + ninePatchMargin
	
	vboxcontainer = $VBoxContainer
	var recipeI = 0
	
	var allRecipes = descriptor.recipes + descriptor.recipesAsIngredient
	allRecipes = Util.filterDuplicates(allRecipes)
	
	if allRecipes.size() > 0:
		var classRecipes = []
		var otherClassRecipes = []
		
		for recipe in allRecipes:
			if recipe.isAvailableForClass(Game.curClass):
				classRecipes.push_back(recipe)
			else:
				otherClassRecipes.push_back(recipe)
		
		var numRecipes = allRecipes.size()
		var headerParams = {}
		headerParams["total"] = numRecipes
		
		if numRecipes > 8:
			if classRecipes.empty():
				allRecipes = otherClassRecipes
			else:
				allRecipes = classRecipes
			
			numRecipes = allRecipes.size()
			recipesHeader.translationKey = "TOOLTIP_Recipe_Subset"
			headerParams["shown"] = numRecipes
		else:
			allRecipes = classRecipes + otherClassRecipes
			if numRecipes == 1:
				recipesHeader.translationKey = "TOOLTIP_Recipe_Single"
			else:
				recipesHeader.translationKey = "TOOLTIP_Recipe_Full"
		
		recipesHeader.formatParams = headerParams
		recipesHeader.updateLocale()
		
		var heightPerRecipe = clamp(880 / numRecipes, 50, 170)
		var ownedCounter = ItemBook.getOwnedCounter()
		var shopCounter = {}
		for item in Game.shopSceneNode.getItemsNoNull():
			Util.dictAdd(shopCounter, item.descriptor)
		
		
		for recipe in allRecipes:
			if recipeI != 0:
				vboxcontainer.add_child(dividerScene.instance())
			recipeI += 1
			
			var entry = recipeScene.instance()
			entry.maxWidth = maxWidth
			entry.rect_min_size.y = heightPerRecipe
			entry.ownedCounter = ownedCounter.duplicate()
			entry.shopCounter = shopCounter.duplicate()
			vboxcontainer.add_child(entry)
			entry.setRecipe(recipe, self)
			entries.push_back(entry)
	else:
		recipesHeader.hide()
	
	
	
	var relatedItems = item.getRelatedItems()
	if not relatedItems.empty():
		var grid = relatedItemsScene.instance()
		entries.push_back(grid)
		vboxcontainer.add_child(grid)
		grid.setItem(item, self)

	
	
	
	var largestSize = 0
	for entry in vboxcontainer.get_children():
		if entry.rect_min_size.x > largestSize:
			largestSize = entry.rect_min_size.x
		
	vboxcontainer.rect_min_size.x = largestSize
	vboxcontainer.rect_size.x = largestSize
	rect_size.x = largestSize + ninePatchMargin
	rect_size.y = 0
	
	var sizeDif = rect_size.x - ninePatchMaxWidth
	if not growToRight:
		rect_position.x -= sizeDif
	
	rect_size.y = vboxcontainer.rect_size.y + Y_BORDER
	
	
	if asSubTooltip:
		lockHint.hide()
	
	show()

func onTooltipLocked():
	for entry in entries:
		entry.enableFocus()
	
	lockIcon.rect_pivot_offset.x = vboxcontainer.rect_size.x * 0.5
	animation.play("Lock")
	Sound.playSound(lockSound, 0, Util.rng.randf_range(0.95, 1.05))

func discard():
	for entry in entries:
		entry.discard()
	queue_free()
