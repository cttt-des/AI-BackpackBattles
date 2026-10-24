extends Node2D

const gradients = [
	preload("res://Items/Particles/ChargeGradient1.tres"), 
	preload("res://Items/Particles/ChargeGradient2.tres"), 
	preload("res://Items/Particles/ChargeGradient3.tres"), 
	preload("res://Items/Particles/ChargeGradient4.tres")
]

const modulates = [
	Color(0.984314, 0.92549, 0.721569), 
	Color(0.721569, 0.984314, 0.721569), 
	Color(1, 0.619608, 0.619608), 
	Color(0.498039, 0.803922, 1)
]

const particleScene = preload("res://Items/Animations/ChargedTile.tscn")

const FADE_DUR = 0.5
const MAX_INTENSITY = 0.714
const MIN_INTENSITY = 0.0

var duration: float
var cells: Array
var emitterItem
var lastChargedItem = null
var curChargedItem = null
var inventoryCells
var tween: SceneTreeTween
var poolingHandle

var particles
var particlesSpeedScale
var ball
var ballMaterial
var chargedTileParticles
var chargedTileFrame
var chargedTileAnimation
var chargedTileVisible: bool

func preset():
	Game.connect("combat_end", self, "onCombatEnded")
	particles = $Particles2D
	particlesSpeedScale = particles.speed_scale
	ball = $Sprite
	ball.material = ball.material.duplicate()
	ballMaterial = ball.material
	chargedTileParticles = ObjectPool.instance(particleScene)
	chargedTileFrame = chargedTileParticles.get_node("Frame")
	chargedTileAnimation = chargedTileParticles.get_node("Animation")

func returnToObjectPool():
	Util.killTween(tween)
	lastChargedItem = null
	curChargedItem = null
	emitterItem = null
	
	
	ObjectPool.returnInstance(self)
	Game.playerNode.remove_child(chargedTileParticles)
	chargedTileVisible = false

func seek(_item, _cells: Array, _duration: float, time: float, stop: bool = true):
	start(_item, _cells, _duration, true)
	tween.pause()
	tween.custom_step(time)
	
	if stop:
		tween.stop()
	else:
		tween.play()

func stop():
	tween.pause()


func start(_item, _cells: Array, _duration: float, replaying: bool = false):
	duration = _duration
	cells = _cells
	emitterItem = _item
	
	if not chargedTileParticles.is_inside_tree():
		Game.playerNode.add_child(chargedTileParticles)
		
		
		var gradient
		var particleMod
		if (emitterItem.isA(ItemBook.batteryDescriptor) or 
			emitterItem.isA(ItemBook.generatorDescriptor) or 
			emitterItem.isA(ItemBook.cogBadgeDescriptor)):
			gradient = gradients[0]
			particleMod = modulates[0]
		elif (emitterItem.isA(ItemBook.chargeSplitterDescriptor) or 
			emitterItem.isA(ItemBook.contraptronDescriptor)):
			gradient = gradients[1]
			particleMod = modulates[1]
		elif emitterItem.isA(ItemBook.lightningStaffDescriptor):
			gradient = gradients[2]
			particleMod = modulates[2]
		elif emitterItem.isA(ItemBook.manaCrystalDescriptor):
			gradient = gradients[3]
			particleMod = modulates[3]
		
		ballMaterial.set_shader_param("tone_mapping", gradient)
		particles.modulate = particleMod
		chargedTileParticles.modulate = particleMod
		
		chargedTileParticles.restart()
		
		particles.speed_scale = particlesSpeedScale
		
	if replaying:
		chargedTileParticles.emitting = true
	else:
		chargedTileParticles.restart()
		particles.speed_scale = particlesSpeedScale
	
	chargedTileFrame.self_modulate.a = 1.0
	
	tween = Util.refreshTween(tween)
	tween.set_parallel()
	
	var startSize = 1.0
	var endSize = 1.0
	
	if emitterItem.isA(ItemBook.batteryDescriptor):
		startSize = 0.5
		endSize = 1.5
	elif emitterItem.isA(ItemBook.chargeSplitterDescriptor):
		startSize = 0.5
		endSize = 1.5
	elif emitterItem.isA(ItemBook.lightningStaffDescriptor):
		startSize = 0.8
		endSize = 1.5
	
	tween.tween_property(self, "scale", Vector2(endSize, endSize), 
		duration).from(Vector2(startSize, startSize))
	
	var cellCenters = emitterItem.getGlobalPointsForCells(cells)
	inventoryCells = emitterItem.inventory.getCellsForGlobalPositions(cellCenters)
	
	var halfCellDur = 0.5 * duration / (cells.size() - 1)
	
	
	var startPos: Vector2
	var endPos: Vector2
	var delay = 0.0
	
	
	
	for i in cells.size() - 1:
		
		
		startPos = (cellCenters[i] + cellCenters[i + 1]) * 0.5
		
		if i == 0:
			position = startPos
			if not replaying:
				onNewCellEntered(1)
			moveParticlesToCell(cellCenters[1])
		
		endPos = cellCenters[i + 1]
		tween.tween_property(self, "position", endPos, halfCellDur).from(startPos).set_delay(delay)
		delay += halfCellDur
		
		
		var oldStartPos = startPos
		startPos = endPos
		if i == cells.size() - 2:
			endPos = endPos + endPos - oldStartPos
		else:
			endPos = (cellCenters[i + 1] + cellCenters[i + 2]) * 0.5
		
		tween.tween_property(self, "position", endPos, halfCellDur).from(startPos).set_delay(delay)
		
		delay += halfCellDur
		
		
		if not replaying:
			tween.tween_callback(self, "onNewCellEntered", [i + 2]).set_delay(delay)
		
		if i < cells.size() - 2:
			tween.tween_callback(self, "moveParticlesToCell", [cellCenters[i + 2]]).set_delay(delay)
		
	
	tween.tween_property(particles, "scale", 
		Vector2.ONE, FADE_DUR).from(Vector2.ZERO)
	tween.tween_property(ballMaterial, "shader_param/intensityFactor", 
		MAX_INTENSITY, FADE_DUR).from(MIN_INTENSITY)
	
	
	delay = duration - FADE_DUR
	
	tween.tween_property(particles, "scale", 
		Vector2.ZERO, FADE_DUR).from(Vector2.ONE).set_delay(delay)
	tween.tween_property(ballMaterial, "shader_param/intensityFactor", 
		MIN_INTENSITY, FADE_DUR).from(MAX_INTENSITY).set_delay(delay)
	
	
	
	tween.tween_property(chargedTileFrame, "self_modulate:a", 
		0.0, FADE_DUR).from(1.0).set_delay(delay)
	
	if not replaying:
		tween.tween_callback(self, "returnToObjectPool").set_delay(duration)
	

func logEvent(event):
	Game.combatLog.logElectricalCharge(event, duration, cells)

func onNewCellEntered(cellIndex: int):
	lastChargedItem = curChargedItem
	
	if cellIndex == inventoryCells.size():
		
		curChargedItem = null
	else:
		var curInventoryCell = inventoryCells[cellIndex]
		curChargedItem = emitterItem.inventory.getItemInCell(curInventoryCell)
	
	emitterItem.onChargeEnteredCell(self, cellIndex)
	
	if curChargedItem != lastChargedItem:
		if lastChargedItem != null:
			lastChargedItem.chargeLeft(self)
		
		if curChargedItem != null:
			curChargedItem.chargeReceived(self)
			if curChargedItem.hasOnChargeReceivedEffect:
				var zap = ObjectPool.instance(Util.zapScene)
				get_parent().add_child(zap)
				var targetPos = curChargedItem.getGlobalCenter()
				zap.zap(global_position, targetPos, zap.ZapStyle.Small)

func moveParticlesToCell(cellCenter):
	chargedTileParticles.position = cellCenter - Vector2(35, 35)
	chargedTileAnimation.play("MoveTile")
	
	
	
	








func disappear(delay: float):
	
	tween.tween_property(particles, "scale", 
		Vector2.ZERO, FADE_DUR).set_delay(delay)
	
	tween.tween_property(ballMaterial, "shader_param/intensityFactor", 
		MIN_INTENSITY, FADE_DUR).set_delay(delay)
	
	chargedTileParticles.emitting = false

func deactivateParticles():
	chargedTileParticles.emitting = false

func onCombatEnded(_roundResult):
	if is_inside_tree():
		tween = Util.refreshTween(tween)
		tween.set_parallel()
		disappear(0)
		
		returnToObjectPool()
