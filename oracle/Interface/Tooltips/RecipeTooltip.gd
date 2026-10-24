extends ToolTip

const recipePlus = preload("res://Interface/Tooltips/RecipePlus.tscn")
const ingredientScene = preload("res://Interface/Tooltips/Ingredient.tscn")
const X_BORDER = 110
const ingredientsPerRow = 3

onready var hboxContainer = $VBoxContainer / HBoxContainer
onready var hboxContainer2 = $VBoxContainer / HBoxContainer2
onready var hboxContainer3 = $VBoxContainer / HBoxContainer3
onready var divider = $VBoxContainer / Divider
onready var divider2 = $VBoxContainer / Divider2

var itemTooltip
var itemTopLeft
var itemSize
var ingredientControls = []

func setItem(item):
	nameLabel.text = item.getTranslatedName()
	modulate = Color.transparent
	var recipeI = - 1
	
	for i in item.descriptor.originatingRecipes.size():
		recipeI += 1
		
		var recipe = item.descriptor.originatingRecipes[i]
		
		if not recipe.isAvailableForClass(Game.recipeBook.selectedClass):
			recipeI -= 1
			continue
		
		if recipeI == 1:
			divider.show()
		elif recipeI == 2:
			divider2.show()
		
		var ingredients = recipe.getAllIngredients()
		var ingredientNum = ingredients.size()
		var ingredientI = 0
		
		for ingredient in ingredients:
			var ingredientControl = ingredientScene.instance()
			
			
			
			if ingredientI < ingredientsPerRow and recipeI == 0:
				hboxContainer.add_child(ingredientControl)
			elif recipeI == 2:
				hboxContainer3.add_child(ingredientControl)
			else:
				hboxContainer2.add_child(ingredientControl)
			
			ingredientControls.push_back(ingredientControl)
			
			
			if ingredientI < ingredientNum - 1:
				var plus = recipePlus.instance()
				if ingredientI < ingredientsPerRow - 1 and recipeI == 0:
					hboxContainer.add_child(plus)
				elif ingredientI == ingredientsPerRow - 1 and recipeI == 0:
					hboxContainer2.add_child(plus)
					hboxContainer2.move_child(plus, 0)
				elif recipeI == 2:
					hboxContainer3.add_child(plus)
				else:
					hboxContainer2.add_child(plus)
					
					
			if recipe.isTypeIngredient(ingredient):
				var typeName = item.Type.keys()[ingredient]
				ingredientControl.setType(typeName)
			else:
				ingredientControl.setItem(ingredient, recipe.isDescriptorCatalyst(ingredient))
				ingredientControl.call_deferred("positionItem")
			
			ingredientI += 1
	
	Util.localizeFonts(nameLabel)
	Util.callNextFrame(self, "createItemTooltip", [item])

func createItemTooltip(item):
	
	
	if isDiscarded(): return
	
	
	itemTooltip = ObjectPool.instance(item.tooltipScenes[item.getRarity()])
	
	Game.tooltipsNode.add_child(itemTooltip)
	itemTooltip.setItem(item)
	var itemIsLeft = item.global_position.x < rect_global_position.x
	
	var marginToSubTooltip = Vector2( - 50, 0)
	var topLeft: Vector2
	if itemIsLeft:
		topLeft.x = itemTopLeft.x
		topLeft.y = rect_position.y
	else:
		topLeft = rect_position
		topLeft.x += 50
	
	var size: Vector2 = itemSize + rect_size + marginToSubTooltip
	
	itemTooltip.forceUpdatePosition(topLeft, size, Alignment.Top)

func updateSize():
	
	var xSize = vboxcontainer.rect_size.x + X_BORDER
	var ySize = vboxcontainer.rect_size.y + Y_BORDER
	
	
	
	set_end(rect_position)
	set_end(rect_position + Vector2(xSize, ySize))
	

func forceUpdatePosition(toolPos: Vector2, toolSize: Vector2, alignment = Alignment.Center):
	itemSize = toolSize
	itemTopLeft = toolPos
	.forceUpdatePosition(toolPos, toolSize, alignment)

func _process(delta):
	if itemTooltip != null:
		modulate = itemTooltip.modulate

func discard():
	
	
	if itemTooltip != null:
		itemTooltip.discard()
	
	for ingredient in ingredientControls:
		ingredient.discard()
	
	.discard()

func isDiscarded() -> bool:
	return is_queued_for_deletion()
