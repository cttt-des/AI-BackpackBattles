extends Item
var activeBlackPieces: Array
var activeWhitePieces: Array
var originCells: Dictionary
var turnColor: int
var goldCost
var blackPieces
var whitePieces
var chessMasterDescr

func onBought():
	pass

func onAddToInventory():
	for item in inventory.getItems():
		if item is ChessPiece:
			item.setBoard(self)


func onRemoveFromInventory():
	for item in inventory.getItems():
		if item is ChessPiece:
			item.setBoard(null)


func onItemAdded(item):
	.onItemAdded(item)
	if item is ChessPiece:
		item.setBoard(self)


func onItemRemoved(item):
	.onItemRemoved(item)
	if item is ChessPiece:
		item.setBoard(null)


func getPiecesForColor(color):
	if color == ChessPiece.PieceColor.Black:
		return activeBlackPieces
	else:
		return activeWhitePieces


func onPrepare():
	if ownerType == CoreConst.Owner.PlayerInventory and ctx.cur_mode != CoreConst.GameMode.History:
		pass
	
	activeBlackPieces.clear()
	activeWhitePieces.clear()
	originCells.clear()
	turnColor = ChessPiece.PieceColor.White
	
	for item in inventory.getItems():
		if item is ChessPiece:
			getPiecesForColor(item.pieceColor).push_back(item)
			originCells[item] = item.occupiedCells


func doCooldownEffect():
	var activePieces = getPiecesForColor(turnColor)
	activePieces.shuffle()
	
	var capturingPiece
	if isTypeInInventory(chessMasterDescr):
		capturingPiece = findBestPieceToCapture(activePieces)
	else:
		capturingPiece = findPieceToCapture(activePieces)
		
	if capturingPiece != null:
		var activateEvent = activate()
		capture(capturingPiece[0], capturingPiece[1], activateEvent)
	else:
		findSpaceToMove(activePieces)
	
	turnColor = ChessPiece.PieceColor.White - turnColor



func findPieceToCapture(activePieces):
	for piece in activePieces:
		var captureCells = piece.getCaptureCells()
		captureCells.shuffle()
		
		
		for cell in captureCells:
			var globalCell = piece.occupiedCells[0] + cell
			var itemInCell = inventory.getItemInCell(globalCell)
			if itemInCell != null:
				
				if piece.canAffect(itemInCell):
					
					return [piece, itemInCell]
	return null


func findBestPieceToCapture(activePieces):
	var bestMovePiece = null
	var bestMoveCapture = null
	var bestMoveScore = - 10000
	
	for piece in activePieces:
		
		var captureCells = piece.getCaptureCells()
		captureCells.shuffle()
		
		for cell in captureCells:
			var globalCell = piece.occupiedCells[0] + cell
			var itemInCell = inventory.getItemInCell(globalCell)
			if itemInCell != null and piece.canAffect(itemInCell):
				
				var score = itemInCell.getPrice()
				if score > bestMoveScore:
					
					if piece.canBeBlocked():
						var length = max(abs(cell.x), abs(cell.y))
						if length > 1:
							var dir = cell / length
							for i in range(1, length):
								var cellToCheck = piece.occupiedCells[0] + i * dir
								
								var itemThere = inventory.getItemInCell(cellToCheck)
								if itemThere != null and itemThere.hasType(CoreConst.Type.ChessPiece):
									
									score -= 100
									break
					
					if score > bestMoveScore:
						bestMoveScore = score
						bestMoveCapture = itemInCell
						bestMovePiece = piece
	
	if bestMoveCapture != null:
		return [bestMovePiece, bestMoveCapture]
	else:
		return null


func capture(capturingPiece, eliminatedPiece, activateEvent):
	var event = capturingPiece.onPieceCaptured(eliminatedPiece, activateEvent)
	eliminatedPiece.onEliminatedBy(capturingPiece, activateEvent)
	
	getPiecesForColor(eliminatedPiece.pieceColor).erase(eliminatedPiece)
	ctx.bus.emitSignal(self, "piece_captured", [capturingPiece, eliminatedPiece])
	

func findSpaceToMove(activePieces):
	for piece in activePieces:
		var moveCells = piece.getMoveCells()
		moveCells.shuffle()
		
		
		for cell in moveCells:
			var globalCell = piece.occupiedCells[0] + cell
			if inventory.isCellEmpty(globalCell):
				
				movePiece(piece, globalCell)
				return


func movePiece(piece, toCell):
	piece.onPieceMoved(toCell)
	



func resetPieces():
	pass

func getGatedDescriptor(rarity):
	pass

func getRelatedItemColumns() -> int:
	return 4


func getRelatedItemHeight() -> int:
	return 100

func _readyInit():
	._readyInit()
	goldCost = int(getP("gold"))
	blackPieces = [
	ctx.item_book.getDescriptor("Black Pawn"), 
	ctx.item_book.getDescriptor("Black Knight"), 
	ctx.item_book.getDescriptor("Black Bishop"), 
	ctx.item_book.getDescriptor("Black Rook"), 
	ctx.item_book.getDescriptor("Black Queen"), 
	ctx.item_book.getDescriptor("Black King")
	]
	whitePieces = [
	ctx.item_book.getDescriptor("White Pawn"), 
	ctx.item_book.getDescriptor("White Knight"), 
	ctx.item_book.getDescriptor("White Bishop"), 
	ctx.item_book.getDescriptor("White Rook"), 
	ctx.item_book.getDescriptor("White Queen"), 
	ctx.item_book.getDescriptor("White King")
	]
	chessMasterDescr = ctx.item_book.getDescriptor("Chess Master")
