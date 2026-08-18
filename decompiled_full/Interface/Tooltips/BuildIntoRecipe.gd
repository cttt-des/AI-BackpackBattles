extends "res://Interface/Tooltips/TooltipItemLayout.gd"

const ingredientLabelScene = preload("res://Interface/IngredientLabel.tscn")
const catalystHatchingScene = preload("res://Interface/ItemLibrary/CatalystHatching.tscn")
const ownedIconScene = preload("res://Interface/Tooltips/OwnedIcon.tscn")
const shopIconScene = preload("res://Interface/Tooltips/ShopIcon.tscn")

const ownedIconScale = Vector2(0.5, 0.5)
const shopIconScale = Vector2(0.3, 0.3)

onready var equals = $Equals
onready var animation = $AnimationPlayer


var pooled = []
var maxWidth: int
var ownedCounter: Dictionary
var shopCounter: Dictionary

func setRecipe(recipe, tooltip):
	
	
	var labelToTypeIngredient = {}
	
	rect_min_size.x = maxWidth
	
	var widthPerIngredient = maxWidth - equals.rect_size.x - MARGIN * 0.5
	widthPerIngredient /= recipe.getNumIngredients() + 2
	var maxSize = Vector2(widthPerIngredient, rect_min_size.y - MARGIN * 0.5)
	
	var actualWidth = 0
	
	
	var fusedItem = addItem(recipe.fusedItem, maxSize, tooltip)
	addedItems.push_back(fusedItem)
	actualWidth += fusedItem.getTextureSize().x
	actualWidth += equals.rect_size.x
	addedItems.push_back(equals)
	
	for ingredientDescriptor in recipe.getAllIngredients():
		
		if recipe.isTypeIngredient(ingredientDescriptor):
			
			var label = ingredientLabelScene.instance()
			add_child(label)
			var type = fusedItem.Type.keys()[ingredientDescriptor]
			label.translationKey = "INGREDIENT_" + type
			label.prefix = "   " + Util.getIcon(type.to_lower()) + " "
			label.updateLocale()
			
			actualWidth += label.rect_size.x
			addedItems.push_back(label)
			labelToTypeIngredient[label] = ingredientDescriptor
		else:
			var ingredient = addItem(ingredientDescriptor, maxSize, tooltip)
			











			
			addedItems.push_back(ingredient)
			var texSize = ingredient.getTextureSize()
			actualWidth += texSize.x
			
			if recipe.isDescriptorCatalyst(ingredientDescriptor):
				var hatching = ObjectPool.instance(catalystHatchingScene)
				
				hatching.rect_size = texSize / ingredient.scale + Vector2(10, 10)
				ingredient.add_child(hatching)
				pooled.push_back(hatching)
				hatching.rect_position = - hatching.rect_size * 0.5
				hatching.rect_position -= ingredient.getSpriteOffset() * 2
	
	var SHRINK_THRESHOLD = 100.0
	
	var spaceLeft = maxWidth - (actualWidth + MARGIN)
	var extraSpace = 0
	if spaceLeft > SHRINK_THRESHOLD:
		var shrinkFactor = (spaceLeft - SHRINK_THRESHOLD) / SHRINK_THRESHOLD
		extraSpace = min(shrinkFactor * 20, (spaceLeft - 50) / (addedItems.size() - 1))
		
	
	var totalWidth = actualWidth + MARGIN + extraSpace * (addedItems.size() - 1)
	rect_min_size.x = max(300, totalWidth)
	
	var numOwnedIngredients = 0
	
	var leftBorder = 0
	for ingredient in addedItems:
		if ingredient is RichTextLabel:
				
			ingredient.rect_position.y = rect_size.y * 0.4
			ingredient.rect_position.x = leftBorder
			leftBorder += ingredient.rect_size.x
			
			
			var hasCheckmark = false
			var type = labelToTypeIngredient[ingredient]
			for descriptor in ownedCounter:
				if descriptor.hasType(type):
					var icon = ObjectPool.instance(ownedIconScene)
					pooled.push_back(icon)
					add_child(icon)
					icon.position = Vector2(leftBorder, ingredient.rect_position.y + 40)
					icon.scale = ownedIconScale
					numOwnedIngredients += 1
					hasCheckmark = true
					break
			if not hasCheckmark:
				for descriptor in shopCounter:
					if descriptor.hasType(type):
						var icon = ObjectPool.instance(shopIconScene)
						pooled.push_back(icon)
						add_child(icon)
						icon.position = Vector2(leftBorder, ingredient.rect_position.y + 40)
						icon.scale = shopIconScale
		
		elif ingredient == equals:
			
			ingredient.rect_position.x = leftBorder
			leftBorder += ingredient.rect_size.x
		
		elif ingredient is Control:
			ingredient.rect_position.y = 0
			ingredient.rect_position.x = leftBorder
			leftBorder += ingredient.rect_size.x
		
		else:
			ingredient.position.y = rect_size.y * 0.5
			ingredient.position.x = leftBorder
			ingredient.position.x += ingredient.getTextureSize().x * 0.5
			ingredient.position += ingredient.getSpriteOffset() * 2.0
			leftBorder += ingredient.getTextureSize().x
			
			if ingredient.descriptor in ownedCounter:
				var icon = ObjectPool.instance(ownedIconScene)
				pooled.push_back(icon)
				ingredient.add_child(icon)
				icon.position = (ingredient.getTextureSize() * 0.5) / ingredient.scale - Vector2(10, 10)
				icon.global_scale = ownedIconScale
				Util.dictSub(ownedCounter, ingredient.descriptor)
				if ingredient.descriptor != recipe.fusedItem:
					numOwnedIngredients += 1
			elif ingredient.descriptor in shopCounter:
				var icon = ObjectPool.instance(shopIconScene)
				pooled.push_back(icon)
				ingredient.add_child(icon)
				icon.position = (ingredient.getTextureSize() * 0.5) / ingredient.scale - Vector2(10, 10)
				icon.scale = shopIconScale
				Util.dictSub(shopCounter, ingredient.descriptor)
		
		leftBorder += extraSpace
		
	call_deferred("center", totalWidth)
	
	if numOwnedIngredients == recipe.getNumIngredients() + 1:
		animation.play("CanCraft")
	

func center(totalWidth):
	var offset = ((rect_size.x) - totalWidth) * 0.5
	for ingredient in addedItems:
		if ingredient is Control:
			ingredient.rect_position.x += offset
		else:
			ingredient.position.x += offset

func discard():
	.discard()
	for node in pooled:
		ObjectPool.returnInstance(node)
