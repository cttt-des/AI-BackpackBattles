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
		# fam_r1 棋族面：decomp Items/Exclusive/Chess/ChessPiece.gd:50-51 按局部格消费（cell.rotated(rotation) 后 ChessBoard.gd:104 occupied[0]+cell 还原全局）；内核 affectedTileCells 为绝对格（装配已烘焙旋转）→ 换算回局部
		moveCells.push_back((cell - occupiedCells[0]).round())
	
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
	# decomp Items/Exclusive/Chess/ChessPiece.gd:74 Sound.playSound(captureSounds.pick_random(), 0, Util.randPitch())——GDScript 实参求值即消耗：randPitch 1 抽
	# 同行 pick_random 走引擎全局链（docs/rng_truth.md §1.4-2）：1 抽，r1_0 台账轮起改道入账
	ctx.rng.pickRandomEngine([null, null, null], "Exclusive/Chess/ChessPiece.gd:74")
	ctx.rng.randf_range(0.9, 1.1)
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
	# r4_2 棋族面：decomp Items/Exclusive/Chess/ChessPiece.gd:93-97 ——
	# z_index/moveTo/movebackTween 为表现面剥离；判定面 inventory.moveItem
	# （Inventory.gd:640-647，捕获者占被吃格）保留 → 内核 CoreGrid.moveItem
	inventory.moveItem(self, [toCell])

func onShopEntered():
	onStateChanged(false)



func onStateChanged(state):
	if typeof(state) == TYPE_VECTOR2:
		var targetCell = state
		repositionPiece(targetCell)
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

