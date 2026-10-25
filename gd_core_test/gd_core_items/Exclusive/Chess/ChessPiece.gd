extends Item
class_name ChessPiece
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
	return item.hasType(CoreConst.Type.ChessPiece) and item.pieceColor != pieceColor


func affectsEmpty(color):
	return true


func setBoard(_board):
	board = _board
	if board == null and placed:
		pass
	else:
		pass


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
	var event = doCapturingEffect(eliminatedPiece)
	return event


func doCapturingEffect(eliminatedPiece):
	pass


func onEliminatedBy(capturingPiece, activateEvent):
	setState(true, false, activateEvent)
	doEliminatedEffect(capturingPiece)


func doEliminatedEffect(capturingPiece):
	pass


func repositionPiece(toCell):
	pass

func onShopEntered():
	onStateChanged(false)



func onStateChanged(state):
	if typeof(state) == TYPE_VECTOR2:
		var targetCell = state
		
	else:
		captured = state
		if captured:
			
			inventory.clearItemCells(self)
		else:
			pass
			


func onAddToInventory():
	pass

func onRemoveFromInventory():
	pass


func getDescription(wrapInColor = true) -> String:
	var descr = .getDescription(wrapInColor)
	if placed and board == null:
		descr += "\n\n" + ctx.util.wrapInColor(tr("HINT_Chess"), ctx.util.paramColor)
	return descr


func discard(discardGems = true):
	.discard(discardGems)

func canBeBlocked() -> bool:
	return true

func _readyInit():
	._readyInit()
	if "White" in name:
		pieceColor = PieceColor.White
	else:
		pieceColor = PieceColor.Black

