extends Item
class_name ChessPiece

const destroyParticlesScene = preload("res://Items/Animations/DestroyParticles.tscn")
const noBoardMarkScene = preload("res://Items/Animations/NotInChainMark.tscn")
const captureSounds = [
	preload("res://Assets/Sound/Chess1.ogg"), 
	preload("res://Assets/Sound/Chess2.ogg"), 
	preload("res://Assets/Sound/Chess3.ogg")]


enum PieceColor{
	Black = 0, 
	White = 1
}

var pieceColor: int
var moveCells: Array

var captured: bool
var numCaptures: int

var board = null
var noBoardMark = null


func canAffect(item):
	return item.hasType(Type.ChessPiece) and item.pieceColor != pieceColor

func affectsEmpty(color):
	return true

func _ready():
	if "White" in name:
		pieceColor = PieceColor.White
	else:
		pieceColor = PieceColor.Black

func setBoard(_board):
	board = _board
	if board == null and placed:
		noBoardMark.appear()
	else:
		noBoardMark.disappear()

func prepare():
	setState(occupiedCells[0])
	
	moveCells.clear()
	for cell in getAffectedCells_tilemap():
		moveCells.push_back(cell.rotated(rotation).round())
	
	numCaptures = 0
	
	.prepare()

func getMoveCells():
	return moveCells

func getCaptureCells():
	return moveCells

func onPieceMoved(targetCell):
	
	setState(targetCell)
	

func onPieceCaptured(eliminatedPiece, activateEvent):
	numCaptures += 1
	var targetCell = eliminatedPiece.occupiedCells[0]
	inventory.clearItemCells(eliminatedPiece)
	
	setState(targetCell, false, activateEvent)
	Sound.playSound(captureSounds.pick_random(), 0, Util.randPitch())
	var event = doCapturingEffect(eliminatedPiece)
	return event

func doCapturingEffect(eliminatedPiece):
	pass

func onEliminatedBy(capturingPiece, activateEvent):
	setState(true, false, activateEvent)
	doEliminatedEffect(capturingPiece)
	var particles = ObjectPool.instance(destroyParticlesScene)
	get_parent().add_child(particles)
	particles.global_position = global_position
	var direction = (global_position - capturingPiece.sprite.global_position).normalized() * 1200
	particles.activate(sprite, direction)

func doEliminatedEffect(capturingPiece):
	pass

func repositionPiece(toCell):
	z_index = 3
	moveTo(global_position, inventory.cellToGlobalPos(toCell, true), 0.3)
	inventory.moveItem(self, [toCell])
	movebackTween.tween_callback(self, "resetZ")


func onShopEntered():
	onStateChanged(false)


func onStateChanged(state):
	if typeof(state) == TYPE_VECTOR2:
		var targetCell = state
		repositionPiece(targetCell)
		show()
		
	else:
		captured = state
		if captured:
			hide()
			
			inventory.clearItemCells(self)
		else:
			show()
			

func onAddToInventory():
	if noBoardMark == null:
		noBoardMark = ObjectPool.instance(noBoardMarkScene)
		add_child(noBoardMark)
		noBoardMark.scale = Vector2(0.8, 0.8)
	
	if board == null:
		noBoardMark.appear()

func onRemoveFromInventory():
	if noBoardMark != null:
		noBoardMark.disappear()

func getDescription(wrapInColor = true) -> String:
	var descr = .getDescription(wrapInColor)
	if placed and board == null:
		descr += "\n\n" + Util.wrapInColor(tr("HINT_Chess"), Util.paramColor)
	return descr

func discard(discardGems = true):
	.discard(discardGems)
	if noBoardMark != null:
		ObjectPool.returnInstance(noBoardMark)
		noBoardMark = null

func canBeBlocked() -> bool:
	return true
