extends Node2D

const ingredientLabelScene = preload("res://Interface/IngredientLabel.tscn")
const catalystHatchingScene = preload("res://Interface/ItemLibrary/CatalystHatching.tscn")
const maxSpacerWidth = 60

onready var itemNameLabel = $ItemName
onready var flavorTextLabel = $VBoxContainer / FlavorText
onready var goldLabel = $Cost
onready var appearRoundLabel = $VBoxContainer / Round
onready var subclassLabel = $VBoxContainer / Subclass
onready var ingredientsBox = $VBoxContainer / HBoxContainer / Ingredients
onready var ingredientsRect = $VBoxContainer / HBoxContainer / Ingredients / Rect
onready var gatedBox = $VBoxContainer / HBoxContainer / Gated
onready var gatedRect = $VBoxContainer / HBoxContainer / Gated / Rect
onready var gatedWidthFactor = ingredientsBox.size_flags_stretch_ratio / (
		ingredientsBox.size_flags_stretch_ratio + gatedBox.size_flags_stretch_ratio)

onready var statLabels = {
	Game.ItemStatistic.SeenInShop: $Shop, 
	Game.ItemStatistic.Acquired: $Acquired, 
	Game.ItemStatistic.BoughtOnSale: $Sale, 
	Game.ItemStatistic.Survivals: $Survivals, 
	Game.ItemStatistic.MostWins: $MostWins, 
	Game.ItemStatistic.BestRankSurvival: $BestRank, 
}
onready var leagueEmblem = $LeagueEmblem
onready var neutralIcon = $Classes / Neutral
onready var classIcons = {
	ItemDescriptor.StuffedClasses.Ranger: $Classes / Ranger, 
	ItemDescriptor.StuffedClasses.Reaper: $Classes / Reaper, 
	ItemDescriptor.StuffedClasses.Berserker: $Classes / Berserker, 
	ItemDescriptor.StuffedClasses.Pyromancer: $Classes / Pyromancer, 
	ItemDescriptor.StuffedClasses.Mage: $Classes / Mage, 
	ItemDescriptor.StuffedClasses.Adventurer: $Classes / Adventurer, 
	ItemDescriptor.StuffedClasses.Engineer: $Classes / Engineer
}

onready var recordStar = $Star

var defaults: Dictionary
var previous = null
var addedNodes = []

func _ready():
	for stat in statLabels:
		defaults[stat] = statLabels[stat].text

func updateLocale():
	updateLocaleForNode(self)
	updateNameAndFlavorText(previous)
	
func updateLocaleForNode(node):
	if node is LocalizedControl:
		node.updateLocale()
	for child in node.get_children():
		updateLocaleForNode(child)

func updateNameAndFlavorText(item: Item):
	itemNameLabel.text = item.getTranslatedName()
	var flavorText = item.getFlavorText()
	if flavorText != "":
		flavorTextLabel.show()
		flavorTextLabel.bbcode_text = ToolTip.highlight(flavorText, false, true)
	else:
		flavorTextLabel.hide()


func setItem(item: Item):
	
	for node in addedNodes:
		if node is Item:
			node.disconnect("info_panel_clicked", self, "onSubitemClicked")
			node.discard()
		elif "poolingHandle" in node:
			ObjectPool.returnInstance(node)
		else:
			node.queue_free()
	addedNodes.clear()
	
	
	
	var copy = item.descriptor.instantiate_pooled()
	addedNodes.push_back(copy)
	previous = copy
	
	copy.ownerType = Item.Owner.InfoPanelIcon
	$Node2D.add_child(copy)
	copy.initInfoPanelIcon()
	copy.scaleToFit(Vector2(120, 170), 0.7)
	copy.position = copy.getSpriteOffset() * 2.0
	
	
	updateNameAndFlavorText(item)
	
	goldLabel.text = String(item.getPrice())
	
	
	
	for stat in statLabels:
		var value = Game.getItemStatistics(stat, item.descriptor)
		if value != null:
			
			
			if stat == Game.ItemStatistic.BestRankSurvival:
				var ranking = stepify(value, 0.01)
				statLabels[stat].text = String(int(fmod(ranking, 1.0) * 100.0))
				leagueEmblem.show()
				leagueEmblem.setLeague(int(ranking))
			else:
				statLabels[stat].text = String(value)
		else:
			statLabels[stat].text = defaults[stat]
			
			if stat == Game.ItemStatistic.BestRankSurvival:
				leagueEmblem.hide()
	
	recordStar.setItem(item)
	
	
	
	if item.descriptor.isNeutral():
		neutralIcon.visible = true
		for classI in classIcons:
			classIcons[classI].visible = false
	else:
		neutralIcon.visible = false
		for classI in classIcons:
			classIcons[classI].visible = item.descriptor.isAvailableForStuffed(classI)

	
	
	if Game.SKILLS_ENABLED:
		if item.descriptor.isTreasure():
			appearRoundLabel.show()
			appearRoundLabel.translationKey = "ITEMLIBRARY_AppearRound_Range"
			appearRoundLabel.formatParams = {
				"r1": Util.highlight(item.descriptor.earliestRound), 
				"r2": Util.highlight(item.descriptor.latestRound)}
			appearRoundLabel.updateLocale()
		
		elif item.hasType(Item.Type.Skill):
			appearRoundLabel.show()
			var rounds = item.descriptor.appearRounds
			if rounds.size() == 1:
				appearRoundLabel.translationKey = "ITEMLIBRARY_AppearRound_Single"
				appearRoundLabel.formatParams = {
				"r1": Util.highlight(rounds[0])}
			else:
				appearRoundLabel.translationKey = "ITEMLIBRARY_AppearRound_Double"
				appearRoundLabel.formatParams = {
				"r1": Util.highlight(rounds[0]), 
				"r2": Util.highlight(rounds[1])}
			appearRoundLabel.updateLocale()
		else:
			appearRoundLabel.hide()
	else:
		appearRoundLabel.hide()
	
	if item.descriptor.startsSubclass != "":
		subclassLabel.show()
		var subclassName = Game.getTranslatedSubclassName(item.descriptor.startsSubclass)
		var color = Game.classResources[Util.log2(item.descriptor.classes)].color
		subclassLabel.formatParams = {
			"subclass": Util.wrapInColor(subclassName, color)}
		subclassLabel.updateText()
	else:
		subclassLabel.hide()
	
	
	
	if item.descriptor.isCraftedItem():
		var newIngredients = []
		
		var rectWidth = $VBoxContainer / HBoxContainer.rect_size.x

		var actualWidth = 0.0
		var numRecipes = item.descriptor.originatingRecipes.size()
		
		var spacerWidth = maxSpacerWidth
		if item.descriptor.isGatedItem():
			rectWidth *= gatedWidthFactor
			spacerWidth *= 0.6
			rectWidth -= spacerWidth * (numRecipes - 1)
	
		ingredientsBox.show()
		var numTotalIngredients = 0
		for recipe in item.descriptor.originatingRecipes:
			numTotalIngredients += recipe.getNumIngredients() + 1
		
		var widthPerIngredient = rectWidth
		widthPerIngredient -= spacerWidth * (numRecipes - 1)
		widthPerIngredient /= numTotalIngredients
		
		
		for i in item.descriptor.originatingRecipes.size():
			if i != 0:
				
				var spacer = Control.new()
				spacer.rect_min_size = Vector2(spacerWidth, 1)
				ingredientsRect.add_child(spacer)
				addedNodes.push_back(spacer)
				newIngredients.push_back(spacer)
				actualWidth += spacerWidth
				
			var recipe: Recipe = item.descriptor.originatingRecipes[i]
			var maxSize = Vector2(widthPerIngredient, ingredientsRect.rect_size.y)
			
			for ingredientDescriptor in recipe.getAllIngredients():
				if recipe.isTypeIngredient(ingredientDescriptor):
					var label = ingredientLabelScene.instance()
					ingredientsRect.add_child(label)
					addedNodes.push_back(label)

					var type = Item.Type.keys()[ingredientDescriptor]
					label.translationKey = "INGREDIENT_" + type
					label.prefix = "   " + Util.getIcon(type.to_lower()) + " "
					label.updateLocale()
					actualWidth += label.rect_size.x
					newIngredients.push_back(label)
				else:
					var ingredient = ingredientDescriptor.instantiate_pooled()
					ingredient.ownerType = Item.Owner.InfoPanelIcon
					newIngredients.push_back(ingredient)
					ingredientsRect.add_child(ingredient)
					addedNodes.push_back(ingredient)
					ingredient.initInfoPanelIcon()
					ingredient.scaleToFit(maxSize, 0.7)
					var texSize = ingredient.getTextureSize()
					actualWidth += texSize.x
					
					if recipe.isDescriptorCatalyst(ingredientDescriptor):
						var hatching = ObjectPool.instance(catalystHatchingScene)
						
						hatching.rect_size = texSize / ingredient.scale + Vector2(10, 10)
						ingredient.add_child(hatching)
						addedNodes.push_back(hatching)
						hatching.rect_position = - hatching.rect_size * 0.5
						hatching.rect_position -= ingredient.getSpriteOffset() * 2
				
		
		var leftBorder = (rectWidth - actualWidth) * 0.5
		for ingredient in newIngredients:
			if ingredient is RichTextLabel:
				ingredient.rect_position.y = ingredientsRect.rect_size.y * 0.35
				ingredient.rect_position.x = leftBorder
				leftBorder += ingredient.rect_size.x
			elif ingredient is Control:
				ingredient.rect_position.y = 0
				ingredient.rect_position.x = leftBorder
				leftBorder += ingredient.rect_size.x
			else:
				ingredient.position.y = ingredientsRect.rect_size.y * 0.5
				ingredient.position.x = leftBorder
				ingredient.position.x += ingredient.getTextureSize().x * 0.5
				ingredient.position += ingredient.getSpriteOffset()
				leftBorder += ingredient.getTextureSize().x
			
		
	else:
		ingredientsBox.hide()
	
	
	
	if item.descriptor.isGatedItem():
		var rectSize = Vector2($VBoxContainer / HBoxContainer.rect_size.x, 
			gatedRect.rect_size.y)
		if item.descriptor.isCraftedItem():
			rectSize.x *= (1 - gatedWidthFactor)
		gatedBox.show()
		var gatedBy = item.descriptor.gateItem.instantiate_pooled()
		gatedBy.ownerType = Item.Owner.InfoPanelIcon
		gatedRect.add_child(gatedBy)
		addedNodes.push_back(gatedBy)
		gatedBy.initInfoPanelIcon()
		gatedBy.scaleToFit(rectSize, 0.7)
		gatedBy.position = rectSize * 0.5
		gatedBy.position += gatedBy.getSpriteOffset()
	else:
		gatedBox.hide()
	
	for node in addedNodes:
		if node is Item:
			node.connect("info_panel_clicked", self, "onSubitemClicked", [node])

func onSubitemClicked(item):
	Game.itemLibrary.setSpotlightDescriptor(item.descriptor)
