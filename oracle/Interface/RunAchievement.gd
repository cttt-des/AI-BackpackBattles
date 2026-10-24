extends Node2D

const particlesScene = preload("res://Interface/GlowingConfetti.tscn")

onready var itemNameLabel = $ItemName
onready var itemRect = $ItemRect
onready var rectSize = itemRect.rect_size
onready var recordStar = $Star
onready var categoryLabel = $Category
onready var counterLabel = $Counter
onready var timer = $Timer
onready var animation = $AnimationPlayer
onready var nextButton = $NextButton
onready var previousButton = $PreviousButton


var statisticKeys = {
	Game.ItemStatistic.SeenInShop: "RECORD_Shop", 
	Game.ItemStatistic.Acquired: "RECORD_Acquired", 
	Game.ItemStatistic.BoughtOnSale: "RECORD_Sale", 
	Game.ItemStatistic.Survivals: "RECORD_Survivals", 
	Game.ItemStatistic.MostWins: "RECORD_Wins", 
	Game.ItemStatistic.BestRankSurvival: "STATS_Rank", 
}

var firstTimeKeys = {
	Game.ItemStatistic.Survivals: "RECORD_FirstSurvival"
}

var recordQueue: Array
var curRecord: int = 0

func _ready():
	hide()
	Game.connect("records_updated", self, "open")
	Game.connect("warp_cursor_combat", self, "onCursorWarp")
	Util.localizeFonts(self)

func open():
	recordQueue = Game.getRecordQueue()
	if recordQueue.size() > 0:
		show()
		animation.play("Appear")
		curRecord = 0
		updateRecord()
		timer.start(2)
		var particles = ObjectPool.particleOneShot(particlesScene, get_parent())
		particles.global_position = global_position

func close():
	if visible:
		timer.stop()
		animation.play("Close")

func onTimeout():
	if recordQueue.size() == 1: return
	timer.start(3)
	showNext()

func onShowNextPressed():
	if recordQueue.size() == 1: return
	timer.stop()
	timer.start(5)
	showNext()

func onShowPreviousPressed():
	if recordQueue.size() == 1: return
	timer.stop()
	timer.start(5)
	showPrevious()

func showNext():
	curRecord = (curRecord + 1) % recordQueue.size()
	updateRecord()

func showPrevious():
	curRecord = (curRecord + recordQueue.size() - 1) % recordQueue.size()
	updateRecord()

func updateRecord():
	for oldItem in itemRect.get_children():
		oldItem.discard()
	
	var recordData = recordQueue[curRecord]
	var itemIndex = recordData[0]
	var statistic = recordData[1]
	var value = recordData[2]
	var item = ItemBook.getDescriptorFromIndex(itemIndex).instantiate_pooled()
	item.ownerType = Item.Owner.Tooltip
	
	itemNameLabel.text = item.getTranslatedName()
	var key = ""
	if value == 1 and statistic in firstTimeKeys:
		key = firstTimeKeys[statistic]
	else:
		key = statisticKeys[statistic]
		
	categoryLabel.text = Util.tra(key).format({"num": String(value)})
	
	itemRect.add_child(item)
	item.initTooltip()
	item.scaleToFit(rectSize, 0.8)
	item.position = rectSize * 0.5
	item.position += item.getSpriteOffset()
	
	
	counterLabel.text = String(curRecord + 1) + " / " + String(recordQueue.size())
	
	recordStar.show()
	if statistic == Game.ItemStatistic.MostWins:
		if value == Game.MAX_ROUNDS:
			recordStar.setStarType(Game.ItemRecordStar.Diamond)
		elif value == Game.MAX_ROUNDS - 1:
			recordStar.setStarType(Game.ItemRecordStar.Gold)
		elif value >= Game.MAX_WINS:
			recordStar.setStarType(Game.ItemRecordStar.Bronze)
	elif statistic == Game.ItemStatistic.Survivals:
		if value == 1:
			recordStar.setStarType(Game.ItemRecordStar.Silver)
	
	

func onCursorWarp():
	if visible:
		Game.addControlOfInterest(nextButton)
		Game.addControlOfInterest(previousButton)
