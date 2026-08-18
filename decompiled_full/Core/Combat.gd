extends Node2D

const winSound = preload("res://Assets/Sound/Victory.mp3")
const loseSound = preload("res://Assets/Sound/Fanfare_loss.mp3")
const glitterSound = preload("res://Assets/Sound/Confetti2.ogg")
const trophyScene = preload("res://Interface/Trophy.tscn")
const trophySound = preload("res://Assets/Sound/Bell2.mp3")
const survivalSound = preload("res://Assets/Sound/Fatigue.wav")
const rankUpPulse = preload("res://Interface/RankUpPulse.tscn")
const rankUpParticles = preload("res://Interface/LeagueChangeParticles.tscn")
const rankDownParticles = preload("res://Interface/RankDownParticles.tscn")
const rankUpSound = preload("res://Assets/Sound/RankUp.ogg")
const rankUpSound2 = preload("res://Assets/Sound/RankUp2.ogg")
const rankDownSound = preload("res://Assets/Sound/RankDown.ogg")
const combatStartSound = preload("res://Assets/Sound/Drumroll.ogg")
const clipMaterial = preload("res://Shader/MaskClip.material")
const eatTrophyParticles = preload("res://Interface/Combat/EatTrophyParticles.tscn")
const chestnutLandSound = preload("res://Assets/Sound/Impact.ogg")
const swordClashSound = preload("res://Assets/Sound/SwordClash.mp3")

onready var UI = $UI
onready var hideTimer = $HideTimer
onready var runAnimation = $RunAnimation
onready var roundAnimation = $RoundAnimation
onready var roundIdleAnimation = $RoundAnimationIdle
onready var rankedNode = $UI / Ranked
onready var rankedAnimation = $UI / Ranked / RankedAnimation
onready var chestnut = $UI / Chestnut
onready var chestnutPos = $UI / Chestnut / Position2D
onready var chestnutAnimation = $UI / Chestnut / ChestnutAnimation
onready var trophyCounter = $UI / Chestnut / BottomFront / TrophyCounter
onready var backgroundAnimation = $Background / BackgroundAnimation
onready var animationTimer = $AnimationTimer
onready var rankingCounter = $UI / Ranked / Ranking
onready var rankingDiff = $UI / Ranked / Dif
onready var rankingDiffAnimation = $UI / Ranked / Dif / AnimationPlayer
onready var leagueLabel = $UI / Ranked / League
onready var leagueEmblem = $UI / Ranked / LeagueEmblem
onready var leagueProgressBar = $UI / Ranked / LeagueProgressBar
onready var leagueProgressBarMaterial = leagueProgressBar.material
onready var barBorderParticles = $UI / Ranked / BarBorderParticles
onready var emblemAnimation = $UI / Ranked / LeagueEmblem / AnimationPlayer
onready var emblemParticles = $UI / Ranked / EmblemParticles
onready var bonusAnimation = $BonusAnimationPlayer
onready var bonusTrophyParticles = $"UI/10Wins/TrophyParticles"
onready var autobattlerHintAni = $AutobattlerHint / AnimationPlayer
onready var triesLeftLabel = $UI / TriesLeft / TriesLeftLabel
onready var aboveUINode = $AboveUI
onready var hideUIButton = $AboveUI / HideUIButton
onready var currentStats = $AboveUI / CurrentStats
onready var roundResultLabel = $AboveUI / CurrentStats / RoundResult
onready var triesNode = $AboveUI / CurrentStats / HBoxContainer / Tries
onready var customRulesIcon = $AboveUI / CurrentStats / CustomRulesIcon
onready var unrankedBanner = $AboveUI / CurrentStats / UnrankedBanner
onready var unrankedLabel = $AboveUI / CurrentStats / Unranked
onready var leagueEmblem2 = $AboveUI / CurrentStats / LeagueEmblem
onready var rankLabel = $AboveUI / CurrentStats / Rank
onready var rankUpBonusAnimation = $UI / Ranked / BonusAnimationPlayer
onready var rankUpBonusLabel = $UI / Ranked / RankUpBonus
onready var combatLogButton = $CombatLogButtonNode / CombatLogButton
onready var survivalPrompt = $"%SurvivalPrompt"
onready var survivalPromptAnimation = survivalPrompt.get_node("AnimationPlayer")
onready var survivalHealHint = survivalPrompt.get_node("StartSurvival/HealHint")
onready var survivalTrophies = $UI / Trophies / SurvivalTrophies
onready var surviveRoundsCounterAnimation = $UI / SurviveRoundsCounter / AnimationPlayer
onready var surviveRoundsCounterLabel = $UI / SurviveRoundsCounter / Label
onready var surviveRoundsCounter = $UI / SurviveRoundsCounter
onready var subclassRoundHealLabel = $UI / SubclassHealLabel
onready var subclassRoundHealAnimation = $UI / SubclassHealLabel / AnimationPlayer
onready var animationTween = $AnimationTween
onready var runOverLabel = $"%RunOverLabel"
onready var backgroundNode = $Background
onready var darkLayer = $UI / ColorRect
onready var chestnutPupil = $UI / Chestnut / BottomFront / Top / Eye / Pupil

onready var winParticles1 = $UI / WinParticles1
onready var winParticles2 = $UI / WinParticles2
onready var loseParticles1 = $UI / LoseParticles1
onready var loseParticles2 = $UI / LoseParticles2


onready var lobbyResultAni = $UI / LobbyResult / AnimationPlayer
onready var lobbyResultScoreLabel = $UI / LobbyResult / Result_Score
onready var lobbyResultRankLabel = $UI / LobbyResult / Result_Rank
onready var lobbyTrophyPosition = $UI / LobbyResult / TrophyPosition

var lobbyResultsReceived: = false
var buildViewer = null

var phase = Phase.Combat
var trophies: = []
var hearts: = []
var lobbyTrophies: = []
var result
var curRanking
var postCombatBgmStarted = false
var animatedTime = 0.0
var survivalPromptActive = false
var clippedNodes: = []

enum Phase{
	Combat, 
	OffScreen, 
	RoundResult, 
	RoundResultSkippable, 
	RunResult, 
	RunResultSkippable
}

const NUM_TROPHIES_OVERRIDE = 16

func _ready() -> void :
	set_process_unhandled_input(false)
	
	Game.connect("shop_closed", self, "onSwitchingToCombat")
	Game.connect("combat_scene_entered", self, "onSwitchedToCombat")
	Game.connect("combat_start", self, "onCombatStart")
	Game.connect("combat_end", self, "onCombatEnd")
	Game.connect("shop_opened", self, "reset")
	Game.connect("returned_to_title", self, "reset")
	Game.connect("warp_cursor_combat", self, "onCursorWarp")
	
	barBorderParticles.emitting = false
	currentStats.hide()
	
	for child in $UI / Trophies.get_children():
		if child.name.begins_with("Trophy"):
			trophies.push_back(child)
		
	for child in survivalTrophies.get_children():
		trophies.push_back(child)
	
	for child in $UI / Hearts.get_children():
		if child.name.begins_with("Heart"):
			hearts.push_back(child)
	
	for child in backgroundNode.get_children():
		if child.is_in_group("Clipped"):
			clippedNodes.push_back(child)
	
	combatLogButton.disabled = true
	combatLogButton.hide()
	
	
	hide()
	set_process(false)
	
	chestnutPupil.deactivate()
	
	call_deferred("ready_deferred")

func ready_deferred():
	if Game.LOBBIES_ENABLED:
		RunDatabase.lobbies.connect("all_end_results_received", self, "onLobbyResultsReceived")

func onSwitchingToCombat():
	show()
	hideTimer.stop()
	animationTween.stop_all()
	animationTween.remove_all()
	
	backgroundAnimation.play("Round")
	backgroundAnimation.seek(0, true)
	
	if Game.getNumStartedRuns() == 1 and Game.curRound == 1:
		autobattlerHintAni.play("ShowHint")
	
	Util.callDelayed(self, "clashSwords", 1.0)

func onSwitchedToCombat():
	combatLogButton.disabled = false
	combatLogButton.show()
	
	

func clashSwords():
	Game.PLAYER.animation.play("CombatStart")
	Game.OPPONENT.animation.play("OpponentCombatStart")
	Util.callDelayed(Sound, "playSound", 1, [swordClashSound, - 5, Util.rng.randf_range(0.9, 1.0)])

func onCombatStart():
	phase = Phase.Combat

func onCombatEnd(roundResult):

	onShowUI()
	hideUIButton.showButton()
	
	
	
	backgroundAnimation.stop()
	animationTimer.stop()
	Util.callDelayed(self, "reactToRoundResult", 0.5)
	
	if Game.curMode == Game.Mode.Ranked or Game.isRankedSwitchMode():
		unrankedBanner.hide()
		unrankedLabel.hide()
		leagueEmblem2.show()
		leagueEmblem2.setLeague(Game.getLeague(Game.curClass))
		rankLabel.show()
		rankLabel.text = String(Game.getRanking(Game.curClass))
	
	elif Game.curMode == Game.Mode.Unranked:
		unrankedBanner.show()
		unrankedLabel.show()
		leagueEmblem2.hide()
		rankLabel.hide()
	else:
		unrankedBanner.hide()
		unrankedLabel.hide()
		leagueEmblem2.hide()
		rankLabel.hide()
	
	$AboveUI / CurrentStats / HBoxContainer / Round / Round.text = String(Game.curRound)
	$AboveUI / CurrentStats / HBoxContainer / Wins / Wins.text = String(Game.getNumWins())
	
	customRulesIcon.visible = CustomRules.areCustomRulesActive()
	customRulesIcon.lobbyMode = (Game.getEffectiveMode() == Game.Mode.Lobbies)
	
	if Game.getEffectiveMode() == Game.Mode.Lobbies:
		triesNode.hide()
	else:
		triesNode.show()
		$AboveUI / CurrentStats / HBoxContainer / Tries / Tries.text = String(Game.getTries())

	if roundResult == Game.RoundResult.Win:
		roundResultLabel.translationKey = "UI_RoundWon"
	else:
		roundResultLabel.translationKey = "UI_RoundLost"
	
	roundResultLabel.updateLocale()

func reactToRoundResult():
	phase = Phase.RoundResult
	
	Game.unhoverAllItems()
	Game.hideTooltips()
	
	if (Game.isSurvivalMode() or 
		Game.curMode == Game.Mode.Lobbies or 
		Game.curMode == Game.Mode.History and Game.wins > 10):
		survivalTrophies.show()
	else:
		survivalTrophies.hide()
	
	var trophyNum: int
	var heartNum: int
	
	result = Game.getLastRoundResult()
	
	if result == Game.RoundResult.Loss:
		if Game.curMode == Game.Mode.Lobbies:
			roundAnimation.play("Lose_Lobby")
		else:
			roundAnimation.play("Lose")
		roundIdleAnimation.play("Lose")
		Sound.playSound_process(loseSound, - 10)
		trophyNum = Game.wins
		
		heartNum = Game.triesBeforeFight
	
	elif result == Game.RoundResult.Win:
		if Game.curMode == Game.Mode.Lobbies:
			roundAnimation.play("Win_Lobby")
		else:
			roundAnimation.play("Win")
		roundIdleAnimation.play("Win")
		Sound.playSound_process(winSound, - 6)
		trophyNum = Game.wins - 1



		heartNum = Game.tries
		trophies[trophyNum].show()

	for i in trophyNum:
		trophies[i].show()
		trophies[i].setFull()
	
	for heart in hearts:
		heart.setEmpty()
	
	for i in heartNum:
		hearts[i].setFull()

	if Game.canStartSurvivalMode():
		Util.callDelayed(self, "showSurvivalPrompt", 1)
	else:
		Util.callDelayed(self, "startRoundResultSkippable", 1)
	
	if (Game.curMode != Game.Mode.History and 
		Game.survivalMode and 
		Game.tries > 0 and 
		Game.curRound < Game.MAX_ROUNDS):
		
		var roundsToSurvive = Game.getRoundsToSurvive()
		surviveRoundsCounterLabel.text = Util.tra("UI_SurviveCounter").format({"rounds": roundsToSurvive + 1})
		surviveRoundsCounterAnimation.play("Show")

func popInTrophy():
	if (Game.isArenaMode() and 
		Game.curRound == Game.SUBCLASS_ROUND and 
		Game.getTries() > 0 and 
		Game.getTries() < Game.MAX_TRIES):
		
		subclassRoundHealAnimation.play("Appear")
		refillHeart()
		Game.giveTry()
	
	trophies[Game.wins - 1].popIn()

func loseHeart():
	if (Game.isArenaMode() and 
		Game.curRound == Game.SUBCLASS_ROUND and 
		Game.getTries() > 0):
		
		subclassRoundHealAnimation.play("Appear")
		loseAndRefillHeart()
		Game.giveTry()
	else:
		hearts[Game.tries].loseHeart()

func playGlitterSound():
	Sound.playSound(glitterSound, - 5, Util.rng.randf_range(0.9, 1.1))

func playTrophySound():
	Sound.playSound(trophySound)

func startRoundResultSkippable():
	phase = Phase.RoundResultSkippable
	set_process_unhandled_input(true)

func _unhandled_input(event: InputEvent) -> void :
	if InputBlocker.isActive(): return
	
	if ((event.is_action_pressed("ui_accept") or 
		event is InputEventMouseButton and 
		event.button_index == BUTTON_LEFT) and 
		event.is_pressed()):
	
		skipIfPossible()

func skipIfPossible():
	if UI.visible:
		if phase == Phase.RoundResultSkippable:
			skipRoundResult()
		elif phase == Phase.RunResultSkippable:
			skipRunResult()

func skipRoundResult():
	phase = Phase.OffScreen
	set_process_unhandled_input(false)
	
	roundAnimation.advance(5)
	
	if Game.curMode == Game.Mode.History:
		switchBackToBuildHistory()
	elif Game.curMode == Game.Mode.Lobbies:
		if Game.leaveLobbyPending:
			forceReturnToTitle()
			Game.leavingLobby = true
			Game.leaveLobbyPending = false
		else:
			if Game.curRound == Game.MAX_ROUNDS_LOBBIES + 1:
				endRun()
			else:
				hideRoundResultAndSwitchBackToShop()
	else:
		if Game.isSurvivalMode():
			if Game.tries == 0:
				$"%RunOverLabel".text = Util.tra("BANNER_GameOver")
				endRun()
			elif Game.hasSurvived():
				$"%RunOverLabel".text = Util.tra("BANNER_Survived")
				endRun()
			else:
				hideRoundResultAndSwitchBackToShop()
		else:
			if Game.wins == Game.MAX_WINS:
				$"%RunOverLabel".text = Util.tra("BANNER_GameWon")
				endRun()
			elif Game.tries == 0:
				$"%RunOverLabel".text = Util.tra("BANNER_GameOver")
				endRun()
			else:
				hideRoundResultAndSwitchBackToShop()

func hideRoundResultAndSwitchBackToShop():
	hideRoundResult()
	switchBackToShop()

func hideRoundResult():
	if result == Game.RoundResult.Loss:
		roundAnimation.play("LoseHide")
	else:
		roundAnimation.play("WinHide")
	
	if surviveRoundsCounter.visible:
		surviveRoundsCounterAnimation.advance(2)
		surviveRoundsCounterAnimation.play("Hide")
	
	if subclassRoundHealLabel.visible:
		subclassRoundHealAnimation.play("Disappear")
		

func switchBackToShop():
	Game.switchToShop()
	switchAway()

func switchAway():
	Game.combatLog.close()
	combatLogButton.disabled = true
	combatLogButton.hide()
	InputBlocker.restoreAllControls(InputBlocker.Source.CombatUI)
	Game.PLAYER.INVENTORY.enableItemTooltips()
	hideTimer.start(5)
	
	startClipping()

func switchBackToBuildHistory():
	hideRoundResult()
	
	Game.buildHistory.open(true)
	switchAway()

func showSurvivalPrompt():
	survivalPromptActive = true
	
	var cancelLabel = survivalPrompt.get_node("TakeWin/RichTextLabel")
	var survivalLabel = survivalPrompt.get_node("StartSurvival/RichTextLabel")
	
	cancelLabel.bbcode_text = "[center]" + Util.tra("UI_CancelSurvival")
	
	survivalLabel.bbcode_text = "[center]" + Util.tra("UI_StartSurvival").format({
		"rounds": Util.wrapInColor(String(Game.MAX_ROUNDS), Util.paramColor), 
		"roundsLeft": Util.wrapInColor(String(Game.getRoundsToSurvive()), Util.paramColor)
	})
	
	if Game.curMode == Game.Mode.Ranked or Game.isRankedSwitchMode():
		var rankLow = Util.addPlus(Game.getRankingDif_survival_worst())
		var rankHigh = Util.addPlus(Game.getRankingDif_survival_best())
		var rank_noSurvival = Util.addPlus(Game.getRankingDif_noSurvival())
		
		survivalLabel.bbcode_text += "\n" + Util.tra("UI_StartSurvival_Ranked").format(
			{"rankLow": Util.wrapInColor(rankLow, Util.paramColor), 
			"rankHigh": Util.wrapInColor(rankHigh, Util.paramColor)})
		
		cancelLabel.bbcode_text += "\n" + Util.tra("UI_CancelSurvival_Ranked").format(
			{"rank": Util.wrapInColor(rank_noSurvival, Util.paramColor)})
		
	survivalPromptAnimation.play("Show")
	
	survivalHealHint.visible = Game.tries < Game.MAX_TRIES
	
	updateSurvivalCounter()
	
func cancelSurvivalMode():
	if not survivalPromptActive: return
	
	survivalPromptActive = false
	Game.cancelSurviveMode()
	survivalPromptAnimation.play("Cancel")
	survivalPromptAnimation.advance(0.01)
	Util.callDelayed(self, "cancelSurvivalMode_continue", 1.0)

func cancelSurvivalMode_continue():
	skipRoundResult()

func refillHeart():
	if Game.getTries() < Game.MAX_TRIES:
		hearts[Game.getTries()].heal()

func loseAndRefillHeart():
	if Game.getTries() < Game.MAX_TRIES:
		hearts[Game.getTries()].loseAndHealBack()

func startSurvivalMode():
	if not survivalPromptActive: return
	
	survivalPromptActive = false
	refillHeart()
	Game.startSurvivalMode()
	
	survivalPromptAnimation.play("Confirm")
	survivalPromptAnimation.advance(0.01)
	Util.callDelayed(self, "startSurvivalMode_continue", 1.0)
	InputBlocker.activate(InputBlocker.Source.SceneSwitch)
	Sound.playSound(survivalSound)

func startSurvivalMode_continue():
	skipRoundResult()
	roundAnimation.play("WinHide")
	switchBackToShop()

func updateSurvivalCounter():
	
	var roundsToSurvive = Game.getRoundsToSurvive()
	if roundsToSurvive == 1:
		surviveRoundsCounterLabel.text = Util.tra("UI_SurviveCounter_OneRound")
	else:
		surviveRoundsCounterLabel.text = Util.tra("UI_SurviveCounter").format({"rounds": roundsToSurvive})

func hideTimerTimeout():
	
	hide()
	chestnutPupil.deactivate()

func startClipping():
	set_process(true)
	
	for node in clippedNodes:
		node.set_material(clipMaterial)
	
	Util.callDelayed(self, "stopClipping", 1)

func stopClipping():
	set_process(false)
	
	for node in clippedNodes:
		node.set_material(null)
	
	hideUIButton.hideButton()

func _process(delta):
	var xPos = backgroundNode.position.x
	xPos /= 1920
	xPos = - (1.0 + xPos)
	xPos += 0.02
	clipMaterial.set_shader_param("xPosition", xPos)

func endRun():
	phase = Phase.RunResult
	
	roundAnimation.advance(5)
	trophyCounter.setCurrent(Game.trophiesPreRun)
	
	var delay = 0.0
	if Game.curMode == Game.Mode.Lobbies:
		runAnimation.play("RunOver_Lobby")
		instanceLobbyTrophies()
		delay = 1.0
	else:
		runAnimation.play("RunOver")
		
		if Game.isSurvivalMode():
			if Game.wasPerfectSurvival():
				givePerfectRunBonus()
				delay = 1.5
			elif Game.hasSurvived():
				giveMaxWinsBonus()
				delay = 1.0
		else:
			if Game.wasPerfectRun():
				givePerfectRunBonus()
				delay = 1.5
			elif Game.wasMaxWins():
				giveMaxWinsBonus()
				delay = 1.0
	
	
	chestnutPupil.activate()
	chestnutAnimation.play("DropAndOpen")
	Util.callDelayed(self, "feedTrophies", 1 + delay)
	
	if isARankedMode():
		Util.callDelayed(self, "playRankedAnimation", Game.wins * 0.1 + 0.5 + delay)
	elif Game.curMode == Game.Mode.Unranked:
		Util.callDelayed(self, "startRunResultSkippable", 3 + delay)
	elif Game.curMode == Game.Mode.Lobbies:
		
		var buildViewerScene = load("res://Interface/Lobbies/LobbyBuildViewer.tscn")
		buildViewer = buildViewerScene.instance()
		UI.add_child(buildViewer)
		
		if lobbyResultsReceived:
			
			showLobbyResults()

func isARankedMode() -> bool:
	return Game.curMode == Game.Mode.Ranked or Game.wasRankedSwitchMode

func instanceLobbyTrophies():
	for i in Game.wins:
		var trophy = trophyScene.instance()
		lobbyTrophies.push_back(trophy)
		lobbyTrophyPosition.add_child(trophy)
		trophy.setFull()
		trophy.self_modulate = Color.transparent

func givePerfectRunBonus():
	var perfectRunLabel = $UI / PerfectRun / Label
	if Game.isSurvivalMode():
		perfectRunLabel.translationKey = "BANNER_PerfectSurvival"
	else:
		perfectRunLabel.translationKey = "BANNER_PerfectWin"
	
	perfectRunLabel.updateText()
	
	var label = $"UI/10Wins/Label"
	
	if Game.isSurvivalMode():
		label.translationKey = "BANNER_Survival"
	else:
		label.translationKey = "BANNER_10Wins"
	
	label.updateLocale()
	
	var delay = 0.8
	Util.callDelayed(bonusAnimation, "play", delay, ["PerfectRun"])
	bonusTrophyParticles.amount = Game.getBonusTrophies()
	
func giveMaxWinsBonus():
	var label = $"UI/10Wins/Label"
	
	if Game.isSurvivalMode():
		label.translationKey = "BANNER_Survival"
	else:
		label.translationKey = "BANNER_10Wins"
	
	label.updateLocale()
	
	var delay = 0.8
	Util.callDelayed(bonusAnimation, "play", delay, ["10Wins"])
	if Game.tries == 1:
		triesLeftLabel.text = Util.tra("BANNER_1TryLeft")
	else:
		triesLeftLabel.text = Util.tra("BANNER_xTriesLeft").replace("$num", String(Game.tries))
	
	bonusTrophyParticles.amount = Game.getBonusTrophies()

func playRankedAnimation():
	rankedAnimation.play("Appear")
	setLeague(Game.leaguePreRun)
	setLeagueProgress(Game.leagueProgressPreRun)
	
	
	
	var newRating: float
	if Game.wasRankedSwitchMode:
		curRanking = Game.getRanking(null)
		newRating = Game.getSwitchModeRating()
		rankedNode.get_node("Class").text = Util.tra("BUTTON_SwitchMode")
		
	else:
		curRanking = Game.getRanking(Game.curClass)
		newRating = Game.getRunRating(Game.curClass)
	
	rankingCounter.setCurrent(Game.rankingPreRun)
	
	var leagueExact = Game.getLeague_exact(newRating)
	
	
	
	var diff = int(leagueExact * 100) - int(Game.leagueExactPreRun * 100)
	
	
	
	
	if diff < 0:
		rankingDiff.prefix = ""
		rankingDiff.set("custom_colors/font_color", Color(0.933594, 0.444916, 0.444916))
	else:
		rankingDiff.prefix = "+"
		rankingDiff.set("custom_colors/font_color", Color(0.472865, 0.933594, 0.361038))
	
	rankingDiff.setCurrent(diff)
	
	Util.callDelayed(self, "setNewRanking", 2, [leagueExact])
	
	Util.callDelayed(self, "startRunResultSkippable", 1)

const TROPHY_MOVE_DUR = 1.0
const TROPHY_DELAY = 0.1

func feedTrophies():
	var numTrophies = Game.wins


	
	var trophies_
	var offset = 0.0
	if Game.curMode == Game.Mode.Lobbies:
		trophies_ = lobbyTrophies
	else:
		trophies_ = trophies
	
	for i in numTrophies:
		if Game.curMode == Game.Mode.Lobbies:
			offset = Util.rng.randf_range( - 100, 100)
		Util.callDelayed(trophies_[i], "moveToPos", i * TROPHY_DELAY, [chestnutPos.global_position + Vector2(offset, 0)])
		Util.callDelayed(self, "onTrophyFed", TROPHY_MOVE_DUR + i * TROPHY_DELAY)
	
	Util.callDelayed(self, "trophiesFinished", numTrophies * TROPHY_DELAY + 1.5)
	Util.callDelayed(trophyCounter, "setTarget", 0.5, [Game.getTrophies()])

func onTrophyFed():
	chestnutAnimation.stop()
	chestnutAnimation.play("EatTrophy")
	ObjectPool.particleOneShot(eatTrophyParticles, chestnut)
	

func trophiesFinished():
	chestnutAnimation.play("Close")
	
	if Game.curMode == Game.Mode.Lobbies:
		for trophy in lobbyTrophies:
			trophy.queue_free()
		lobbyTrophies.clear()

func rankingDiffCountingFinished():
	rankingDiffAnimation.play("Hide")

const BASE_LEAGUE_BAR_DURATION = 1.0
const RELATIVE_LEAGUE_BAR_DURATION = 1.0

func setNewRanking(leagueExact):
	
	rankingDiff.setTarget(0)
	barBorderParticles.emitting = true
	emblemParticles.modulate = Game.leagueColors[Game.leaguePreRun].lightened(0.2)
	
	var progressTween = create_tween()
	
	var newLeague = int(leagueExact)
	var previousProgress = Game.leagueProgressPreRun
	var newProgress = fmod(leagueExact, 1.0)
	
	if newLeague > Game.leaguePreRun:
		var dur = (1.0 - previousProgress) * RELATIVE_LEAGUE_BAR_DURATION + BASE_LEAGUE_BAR_DURATION
		
		progressTween.tween_method(self, "setLeagueProgress", previousProgress, 1.0, dur)
		progressTween.tween_callback(self, "updateLeague", [newLeague, true, curRanking])
		
		progressTween.tween_method(self, "setLeagueProgress", 0.0, newProgress, dur).set_delay(0.2)
		emblemParticles.amount = 30
		emblemAnimation.play("IncreasePower")
		rankingCounter.setTarget(100)
		Sound.playSound(rankUpSound)
		
	elif newLeague < Game.leaguePreRun:
		var dur = previousProgress * RELATIVE_LEAGUE_BAR_DURATION + BASE_LEAGUE_BAR_DURATION
		
		progressTween.tween_method(self, "setLeagueProgress", previousProgress, 0.0, dur)
		progressTween.tween_callback(self, "updateLeague", [newLeague, false, curRanking])
		
		progressTween.tween_method(self, "setLeagueProgress", 1.0, newProgress, dur).set_delay(0.2)
		emblemParticles.amount = 5
		emblemAnimation.play("DecreasePower")
		rankingCounter.setTarget(0)
		Sound.playSound(rankDownSound)
	
	else:
		var dur = abs(newProgress - previousProgress) * RELATIVE_LEAGUE_BAR_DURATION + BASE_LEAGUE_BAR_DURATION
		
		progressTween.tween_method(self, "setLeagueProgress", previousProgress, newProgress, dur)
		rankingCounter.setTarget(curRanking)
		
		if newProgress > previousProgress:
			emblemAnimation.play("IncreasePower")
			Sound.playSound(rankUpSound)
		else:
			emblemAnimation.play("DecreasePower")
			Sound.playSound(rankDownSound)
			
		
	progressTween.tween_callback(self, "stopParticles")
	
	
func setLeagueProgress(progress: float):
	leagueProgressBarMaterial.set_shader_param("progress", progress)
	
	var barSize = leagueProgressBar.region_rect.size.x * leagueProgressBar.global_scale.x
	var barStart = leagueProgressBar.global_position.x - barSize * 0.5
	
	barBorderParticles.global_position.x = barStart + progress * barSize

func stopParticles():
	barBorderParticles.emitting = false

func setLeague(league):
	leagueLabel.text = Game.getLeagueName(league)
	leagueLabel.set("custom_colors/font_color", Game.leagueColors[league])
	leagueEmblem.setLeague(league)
	barBorderParticles.modulate = Game.leagueColors[league].lightened(0.2)
	leagueProgressBar.modulate = Game.leagueColors[league]

func updateLeague(league, rankedUp, ranking):
	setLeague(league)
	var particles
	if rankedUp:
		rankingCounter.setCurrent(0)
		rankUpBonusLabel.text = Util.addPlus(Game.RANK_UP_BONUS_RANKING)
		rankUpBonusAnimation.play("ShowBonus")
		var pulse = ObjectPool.playAnimation(rankUpPulse, "Activate", rankedNode, leagueEmblem)
		pulse.self_modulate = Game.leagueColors[league].lightened(0.2)
		pulse.global_position = leagueEmblem.global_position
		particles = ObjectPool.particleOneShot(rankUpParticles, rankedNode)
		emblemAnimation.play("RankUp")
		Sound.playSound(rankUpSound2, 6)
		
	else:
		rankingCounter.setCurrent(100)
		particles = ObjectPool.particleOneShot(rankDownParticles, rankedNode)
		emblemAnimation.play("RankDown")
	
	particles.modulate = Game.leagueColors[league].lightened(0.2)
	particles.global_position = leagueEmblem.global_position
	rankingCounter.setTarget(ranking)
	

func startRunResultSkippable():
	phase = Phase.RunResultSkippable
	set_process_unhandled_input(true)
	
func skipRunResult():
	phase = Phase.OffScreen
	set_process_unhandled_input(false)
	
	if Game.curMode == Game.Mode.Lobbies:
		runAnimation.play("ReturnToTitle_Lobbies")
	else:
		runAnimation.play("ReturnToTitle")
	
	if isARankedMode():
		rankedAnimation.play("Disappear")
	
	bonusAnimation.play("Disappear")
	
	Game.combatLog.close()
	combatLogButton.disabled = true
	combatLogButton.hide()
	
	InputBlocker.restoreAllControls(InputBlocker.Source.CombatUI)
	Game.returnToTitle_afterRun()
	hideTimer.start(5)
	startClipping()

func reset():
	runAnimation.play("RESET")
	roundAnimation.play("RESET")
	rankingDiffAnimation.play("RESET")
	roundIdleAnimation.stop()
	survivalPromptAnimation.play("RESET")
	surviveRoundsCounterAnimation.play("RESET")
	subclassRoundHealAnimation.play("RESET")
	Game.PLAYER.enableClicking()
	phase = Phase.OffScreen
	survivalPromptActive = false
	for trophy in trophies:
		trophy.setEmpty()
	for i in range(10, 20):
		trophies[i].hide()
	postCombatBgmStarted = false

func clearParticles():
	for particles in [winParticles1, winParticles2, loseParticles1, loseParticles2]:
		particles.restart()
		particles.emitting = false

func hideUI():
	UI.hide()
	combatLogButton.disabled = false
	
	
	if (Game.getNumStartedRuns() >= 3 and 
		Game.getNumStartedRuns() < 10 and 
		not Game.isTutorialDone(Game.TutorialSteps.CombatLog)):
		
		Game.combatLog.tutorialAni.play("Tutorial")
	
	currentStats.show()
	InputBlocker.restoreAllControls(InputBlocker.Source.CombatUI)
	Game.PLAYER.INVENTORY.enableItemTooltips()
	Game.OPPONENT.INVENTORY.enableItemTooltips()
	
	
	clearParticles()
	
	if survivalPromptActive:
		survivalPrompt.hide()
	
	if not postCombatBgmStarted:
		postCombatBgmStarted = true
		if Game.survivalMode:
			Sound.playBGM(Sound.postFightBGM_survival, - 3)
		else:
			Sound.playBGM(Sound.postFightBGM, - 4)
	
	
func showUI():
	UI.show()
	onShowUI()
	Game.combatLog.close()
	if survivalPromptActive:
		survivalPrompt.show()

func isPostCombatScreenVisible() -> bool:
	return darkLayer.is_visible_in_tree()

func onShowUI():
	currentStats.hide()
	InputBlocker.disableSingleControl(InputBlocker.Source.CombatUI, combatLogButton)
	
	
	InputBlocker.disableAllControls(InputBlocker.Source.CombatUI, Game.PLAYER)
	InputBlocker.disableAllControls(InputBlocker.Source.CombatUI, Game.OPPONENT)
	Game.unhoverAndHideTooltips()
	Game.PLAYER.INVENTORY.disableItemTooltips()
	Game.OPPONENT.INVENTORY.disableItemTooltips()
	Game.clearAffectedLines()

func stopTimeTween():
	animationTween.stop_all()
	animationTween.remove_all()



const ADVANCE_SPEED = 5.0

func advanceTime(time):
	Game.combatTimer.advanceTime(time)
	backgroundAnimation.playback_speed = ADVANCE_SPEED
	var dur = time / (ADVANCE_SPEED - 1.0)
	Util.changeTimer(animationTimer, dur)
	
	









func onAnimationTimerTimeout():
	backgroundAnimation.playback_speed = 1.0
	backgroundAnimation.seek(Game.combatTimer.getEffectiveTime())

func interpolateTime(time):
	stopTimeTween()
	var dur = 0.1 + abs(time - animatedTime) * 0.05
	animationTween.interpolate_method(self, "setTime", animatedTime, time, dur, Tween.TRANS_LINEAR, Tween.EASE_IN_OUT)
	animationTween.start()

func setTime(time):
	
	animatedTime = time
	backgroundAnimation.seek(Game.COMBAT_DELAY + animatedTime, true)


func forceSwitchToShop():
	Game.closeAllMenus()
	if phase != Phase.OffScreen:
		phase = Phase.OffScreen
		if not UI.visible:
			showUI()
		
		hideRoundResultAndSwitchBackToShop()

func forceReturnToTitle():
	if not UI.visible:
		showUI()
	
	hideRoundResult()
	Game.combatLog.close()
	combatLogButton.disabled = true
	combatLogButton.hide()
	
	InputBlocker.restoreAllControls(InputBlocker.Source.CombatUI)
	Game.returnToTitle_afterRun()
	hideTimer.start(5)
	startClipping()
	
	

func onLobbyResultsReceived():
	lobbyResultsReceived = true
	if phase == Phase.RunResult:
		showLobbyResults()

func showLobbyResults():
	lobbyResultAni.play("Appear")
	lobbyResultRankLabel.formatParams = {"rank": RunDatabase.lobbies.getResultRank()}
	lobbyResultRankLabel.updateText()
	
	lobbyResultScoreLabel.formatParams = {"score": RunDatabase.lobbies.getResultScore()}
	lobbyResultScoreLabel.updateText()
	
func onLobbyFinishButtonPressed():
	
	skipRunResult()
	
	lobbyResultAni.play("Disappear")
	lobbyResultsReceived = false
	buildViewer.close()
	buildViewer = null
	
	RunDatabase.lobbies.leaveLobby()
	
	if Game.hasArenaRunState():
		Game.initPlayerFromRunstate(Game.Mode.Unranked)
		Game.readRoundResultsFromRunState(Game.Mode.Unranked)



func playDropSound():
	pass

func playLandSound():
	Sound.playSound(chestnutLandSound)

func playOpenSound():
	Sound.playSound(Game.SELLBOX.openSound)

func playCloseSound():
	Sound.playSound(Game.SELLBOX.closeSound)

onready var combatTimerNodes = [Game.combatTimer.fastButton, 
	Game.combatTimer.pauseButton, Game.combatTimer.speedSlider]

func onCursorWarp():
	if not Game.fightEnded:
		for node in combatTimerNodes:
			if Util.isControlEnabled(node):
				Game.addControlOfInterest(node)
	else:
		if hideUIButton.visible:
			Game.addControlOfInterest(hideUIButton)
	
	if darkLayer.is_visible_in_tree():
		Game.addPointOfInterest(Vector2(960, 960))
	else:
		Game.addControlOfInterest(combatLogButton)
		
		for character in [Game.PLAYER, Game.OPPONENT]:
			for item in character.INVENTORY.getItemsAndGems():
				Game.addItemOfInterest(item)
			
			for buffI in character.buffs:
				var buff = character.buffs[buffI]
				if buff.getStacks() > 0:
					Game.addPointOfInterest(buff.counter.global_position + Vector2(20, 20))
			
			for icon in character.statsDisplay.activeIcons:
				Game.addPointOfInterest(icon.global_position + Vector2(20, 20))
