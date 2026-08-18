extends Control

const customRulesScript = preload("res://Utility/CustomRules.gd")
const positiveColor = Color(0.590118, 1, 0.566406)
const negativeColor = Color(1, 0.564706, 0.564706)

var poolingHandle
var unselectedBackground
var selectedBackground
var hoveredBackground
var dateLabel
var versionLabel
var classIcon
var randomClassIcon
var rankedNode
var rankingLabel
var rankingDifLabel
var leagueEmblem
var unrankedNode
var lobbyIcon
var customRulesIcon
var winsLabel
var roundsLabel
var triesLabel
var heart
var subclassNode
var skill1Node
var skill2Node
var startingBagNode
var roundButtons: Array
var data: BuildHistoryData
var selected: bool = false
var hovered: bool = false
var placeholder

func preset():
	unselectedBackground = $Unselected
	selectedBackground = $Selected
	hoveredBackground = $Hovered
	dateLabel = $Date
	versionLabel = $Version
	classIcon = $ClassIcon
	randomClassIcon = $RandomClass
	rankedNode = $Ranked
	rankingLabel = $Ranked / Ranking
	rankingDifLabel = $Ranked / RankingDif
	leagueEmblem = $Ranked / LeagueEmblem
	unrankedNode = $Unranked
	lobbyIcon = $Lobby
	customRulesIcon = $CustomRulesIcon
	winsLabel = $Wins
	roundsLabel = $Round
	triesLabel = $Tries
	heart = $Heart
	subclassNode = $Subclass
	skill1Node = $Skill1
	skill2Node = $Skill2
	startingBagNode = $StartingBag
	var roundI = 1
	for button in $RoundButtons.get_children():
		roundButtons.push_back(button)
		button.connect("pressed", self, "onRoundButtonPressed", [roundI])
		roundI += 1

func _ready():
	placeholder = get_parent()

func setHistoryData(_data: BuildHistoryData):
	data = _data
	
	if data.version == Game.versionToInt():
		versionLabel.hide()
	else:
		versionLabel.show()
		versionLabel.text = data.getVersionString()
	
	var timeDif = data.getTimeDif()
	if timeDif.days >= 2:
		dateLabel.translationKey = "UI_Date_Days"
	elif timeDif.days == 1:
		dateLabel.translationKey = "UI_Date_Day"
	elif timeDif.hour > 1:
		dateLabel.translationKey = "UI_Date_Hours"
	elif timeDif.hour == 1:
		dateLabel.translationKey = "UI_Date_Hour"
	elif timeDif.minute > 1:
		dateLabel.translationKey = "UI_Date_Minutes"
	else:
		dateLabel.translationKey = "UI_Date_Minute"
	dateLabel.formatParams = timeDif
	
	classIcon.texture = Game.classIcons[data.classI]
	randomClassIcon.visible = (data.loadout == Game.Loadout.RandomCharacter)
	
	if data.customRules != "":
		customRulesIcon.show()
		var customRules = customRulesScript.new()
		customRules.fromString(data.customRules)
		customRulesIcon.customRules = customRules
		customRulesIcon.lobbyMode = (data.mode == Game.Mode.Lobbies)
		
	else:
		customRulesIcon.hide()
	
	winsLabel.text = String(data.getWins())
	roundsLabel.text = String(data.getRounds())
	
	if data.mode == Game.Mode.Lobbies:
		triesLabel.hide()
		heart.hide()
		lobbyIcon.show()
	else:
		triesLabel.show()
		heart.show()
		triesLabel.text = String(data.getTries())
		lobbyIcon.hide()
	
	
	if data.mode == Game.Mode.Unranked:
		unrankedNode.show()
	else:
		unrankedNode.hide()
	
	var survivalStartRound = data.getSurvivalStartRound()
	var survival = survivalStartRound != - 1
	
	
	if data.mode == Game.Mode.Ranked:
		rankedNode.show()
		var leagueExact = Game.getLeague_exact(data.rating)
		var league = clamp(int(leagueExact), 0, Game.Leagues.Grandma)
		leagueEmblem.setLeague(league)
		rankingLabel.text = String(int(100 * fmod(leagueExact, 1.0)))
		
		var runWasConceded = false
		if data.getTries() > 0:
			if survival:
				runWasConceded = data.getRounds() < Game.MAX_ROUNDS
			else:
				runWasConceded = data.getWins() < Game.MAX_WINS
		
		
		var losses = data.getLosses()
		var tries = data.getTries()
		if runWasConceded:
			var roundsLeft = Game.MAX_ROUNDS - data.getRounds()
			losses += min(roundsLeft, data.getTries())
			losses = min(losses, Game.MAX_TRIES)
			tries = 0
		
		var newRating = Game.calcRunRating(data.rating, data.getWins(), 
			losses, tries, survival, 
			data.getWins(Game.MAX_WINS) == Game.MAX_WINS)
		var rankingDif = int(Game.getLeague_exact(newRating) * 100) - int(leagueExact * 100)
		
		if rankingDif == 0:
			rankingDifLabel.hide()
		else:
			rankingDifLabel.show()
			rankingDifLabel.text = Util.addPlus(rankingDif)
			if rankingDif > 0:
				rankingDifLabel.set("custom_colors/font_color", positiveColor)
			else:
				rankingDifLabel.set("custom_colors/font_color", negativeColor)
		
	else:
		rankedNode.hide()
	
	
	for roundI in roundButtons.size():
		var res = Game.RoundResult.RunOver
		var roundHistory = data.getRoundData(roundI + 1)
		if roundHistory != null:
			res = roundHistory.result
		roundButtons[roundI].setResult(res)
	
	instanceSpecialItems()
	
	Util.updateLocaleInSubtree(self)

func onRoundButtonPressed(roundI):
	if Input.is_action_just_released("right_click"):
		Game.buildHistory.setOpponentMark(roundI, self)
	else:
		Game.buildHistory.updateBuild(roundI, placeholder)

func onEntryPressed():
	if Input.is_action_just_released("right_click"):
		Game.buildHistory.setOpponentMark(data.getRounds(), self)
	else:
		Game.buildHistory.updateBuild(data.getRounds(), placeholder)

func select():
	unselectedBackground.hide()
	hoveredBackground.hide()
	selectedBackground.show()
	selected = true

func unselect():
	unselectedBackground.show()
	selectedBackground.hide()
	selected = false
	if hovered:
		onHovered()

func instanceSpecialItems():
	if data.subclassIndex != null:
		initItem(data.subclassIndex, subclassNode)
	if data.skill1Index != null:
		initItem(data.skill1Index, skill1Node)
	if data.skill2Index != null:
		initItem(data.skill2Index, skill2Node)
	
	
	var startingBagIndex = Game.classResources[data.classI].getStartingBag(data.loadout).itemIndex
	initItem(startingBagIndex, startingBagNode, Vector2(60, 50))

var specialItems = []

func initItem(itemIndex, parent, maxSize = Vector2(70, 60)):
	var item = ItemBook.getDescriptorFromIndex(itemIndex).instantiate_pooled()
	item.ownerType = item.Owner.BuildViewerIcon
	specialItems.push_back(item)
	parent.add_child(item)
	item.initBuildViewerIcon()
	item.scaleToFit(maxSize, 0.7)
	item.position = item.getSpriteOffset()
	var hoverArea = parent.get_node("HoverArea")
	hoverArea.connect("mouse_entered", self, "onItemHovered", [item])
	hoverArea.connect("mouse_exited", self, "onItemHoverEnd", [item])
	hoverArea.show()

func clearItems():
	for item in specialItems:
		item.hoverEnd()
		var parent = item.get_parent()
		var hoverArea = parent.get_node("HoverArea")
		hoverArea.disconnect("mouse_entered", self, "onItemHovered")
		hoverArea.disconnect("mouse_exited", self, "onItemHoverEnd")
		hoverArea.hide()
		item.discard()
	
	specialItems.clear()
	

func onItemHovered(item):
	item.hover()
	

func onItemHoverEnd(item):
	item.hoverEnd()
	







func returnToObjectPool():
	unselect()
	hovered = false
	clearItems()
	ObjectPool.returnInstance(self)


func onHovered():
	hovered = true
	if not selected:
		hoveredBackground.show()
		unselectedBackground.hide()

func onHoverEnd():
	hovered = false
	if not selected:
		unselectedBackground.show()
		hoveredBackground.hide()
