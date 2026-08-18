extends Item

var activeBlackPieces: Array
var activeWhitePieces: Array
var originCells: Dictionary

var turnColor: int

onready var goldCost: = int(getP("gold"))

onready var blackPieces = [
	ItemBook.getDescriptor("Black Pawn"), 
	ItemBook.getDescriptor("Black Knight"), 
	ItemBook.getDescriptor("Black Bishop"), 
	ItemBook.getDescriptor("Black Rook"), 
	ItemBook.getDescriptor("Black Queen"), 
	ItemBook.getDescriptor("Black King")
	]
onready var whitePieces = [
	ItemBook.getDescriptor("White Pawn"), 
	ItemBook.getDescriptor("White Knight"), 
	ItemBook.getDescriptor("White Bishop"), 
	ItemBook.getDescriptor("White Rook"), 
	ItemBook.getDescriptor("White Queen"), 
	ItemBook.getDescriptor("White King")
	]

onready var chessMasterDescr = ItemBook.getDescriptor("Chess Master")

func onBought():
	if Game.getGold() >= goldCost:
		Game.spendGold(goldCost)
		var pawn1 = ItemBook.generateAndStorageItem("White Pawn", global_position)
		var pawn2 = ItemBook.generateAndStorageItem("Black Pawn", global_position)
		Game.saveRunState()
		activate()

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
	if ownerType == Owner.PlayerInventory and Game.curMode != Game.Mode.History:
		Game.connect("pre_shop_opened_from_combat", self, "resetPieces", [], CONNECT_ONESHOT)
	
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
								if itemThere != null and itemThere.hasType(Type.ChessPiece):
									
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
	EventBus.emitSignal(self, "piece_captured", [capturingPiece, eliminatedPiece])
	
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
	
	for piece in originCells:
		inventory.moveItem(piece, originCells[piece])
		piece.occupiedCells = originCells[piece]
		piece.moveTo(piece.global_position, inventory.cellToGlobalPos(originCells[piece][0], true), 0.3)

func getGatedDescriptor(rarity):
	var numBlack = 0
	for blackPiece in blackPieces:
		numBlack += ItemBook.countOwnedItemsOfType(blackPiece)
		
	var numWhite = 0
	for whitePiece in whitePieces:
		numWhite += ItemBook.countOwnedItemsOfType(whitePiece)
	
	if rarity == Rarity.Godly and Util.flip():
		rarity += 1
	
	if numBlack > numWhite:
		return whitePieces[rarity]
	
	elif numWhite > numBlack:
		return blackPieces[rarity]
	
	else:
		if Util.flip():
			return whitePieces[rarity]
		else:
			return blackPieces[rarity]

func getRelatedItemColumns() -> int:
	return 4

func getRelatedItemHeight() -> int:
	return 100
