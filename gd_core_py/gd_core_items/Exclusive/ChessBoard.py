# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__ChessBoard(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/ChessBoard.gd"

	def _init_fields(self):
		super()._init_fields()
		self.activeBlackPieces = []
		self.activeWhitePieces = []
		self.originCells = {}
		self.turnColor = 0
		self.goldCost = None
		self.blackPieces = None
		self.whitePieces = None
		self.chessMasterDescr = None


	def onBought(self):
		pass

	def onAddToInventory(self):
		for item in _iter(self.inventory.getItems()):
			if isinstance(item, _R.C("ChessPiece")):
				item.setBoard(self)


	def onRemoveFromInventory(self):
		for item in _iter(self.inventory.getItems()):
			if isinstance(item, _R.C("ChessPiece")):
				item.setBoard(None)


	def onItemAdded(self, item):
		super().onItemAdded(item)
		if isinstance(item, _R.C("ChessPiece")):
			item.setBoard(self)


	def onItemRemoved(self, item):
		super().onItemRemoved(item)
		if isinstance(item, _R.C("ChessPiece")):
			item.setBoard(None)


	def getPiecesForColor(self, color):
		if color == _R.C("ChessPiece").PieceColor.Black:
			return self.activeBlackPieces
		else:
			return self.activeWhitePieces


	def onPrepare(self):
		if self.ownerType == _R.C("CoreConst").Owner.PlayerInventory and self.ctx.cur_mode != _R.C("CoreConst").GameMode.History:
			pass

		self.activeBlackPieces.clear()
		self.activeWhitePieces.clear()
		self.originCells.clear()
		self.turnColor = _R.C("ChessPiece").PieceColor.White

		for item in _iter(self.inventory.getItems()):
			if isinstance(item, _R.C("ChessPiece")):
				self.getPiecesForColor(item.pieceColor).append(item)
				self.originCells[item] = item.occupiedCells


	def doCooldownEffect(self):
		activePieces = self.getPiecesForColor(self.turnColor)
		_shuffle(activePieces)

		capturingPiece = None
		if self.isTypeInInventory(self.chessMasterDescr):
			capturingPiece = self.findBestPieceToCapture(activePieces)
		else:
			capturingPiece = self.findPieceToCapture(activePieces)

		if capturingPiece != None:
			activateEvent = self.activate()
			self.capture(capturingPiece[0], capturingPiece[1], activateEvent)
		else:
			self.findSpaceToMove(activePieces)

		self.turnColor = _R.C("ChessPiece").PieceColor.White - self.turnColor



	def findPieceToCapture(self, activePieces):
		for piece in _iter(activePieces):
			captureCells = piece.getCaptureCells()
			_shuffle(captureCells)


			for cell in _iter(captureCells):
				globalCell = piece.occupiedCells[0] + cell
				itemInCell = self.inventory.getItemInCell(globalCell)
				if itemInCell != None:

					if piece.canAffect(itemInCell):

						return [piece, itemInCell]
		return None


	def findBestPieceToCapture(self, activePieces):
		bestMovePiece = None
		bestMoveCapture = None
		bestMoveScore = - 10000

		for piece in _iter(activePieces):

			captureCells = piece.getCaptureCells()
			_shuffle(captureCells)

			for cell in _iter(captureCells):
				globalCell = piece.occupiedCells[0] + cell
				itemInCell = self.inventory.getItemInCell(globalCell)
				if itemInCell != None and piece.canAffect(itemInCell):

					score = itemInCell.getPrice()
					if score > bestMoveScore:

						if piece.canBeBlocked():
							length = max(abs(cell.x), abs(cell.y))
							if length > 1:
								dir = _div(cell, length)
								for i in _iter(_gd_range(1, length)):
									cellToCheck = piece.occupiedCells[0] + i * dir

									itemThere = self.inventory.getItemInCell(cellToCheck)
									if itemThere != None and itemThere.hasType(_R.C("CoreConst").Type.ChessPiece):

										score -= 100
										break

						if score > bestMoveScore:
							bestMoveScore = score
							bestMoveCapture = itemInCell
							bestMovePiece = piece

		if bestMoveCapture != None:
			return [bestMovePiece, bestMoveCapture]
		else:
			return None


	def capture(self, capturingPiece, eliminatedPiece, activateEvent):
		event = capturingPiece.onPieceCaptured(eliminatedPiece, activateEvent)
		eliminatedPiece.onEliminatedBy(capturingPiece, activateEvent)

		_erase(self.getPiecesForColor(eliminatedPiece.pieceColor), eliminatedPiece)
		self.ctx.bus.emitSignal(self, "piece_captured", [capturingPiece, eliminatedPiece])


	def findSpaceToMove(self, activePieces):
		for piece in _iter(activePieces):
			moveCells = piece.getMoveCells()
			_shuffle(moveCells)


			for cell in _iter(moveCells):
				globalCell = piece.occupiedCells[0] + cell
				if self.inventory.isCellEmpty(globalCell):

					self.movePiece(piece, globalCell)
					return


	def movePiece(self, piece, toCell):
		piece.onPieceMoved(toCell)




	def resetPieces(self):
		pass

	def getGatedDescriptor(self, rarity):
		pass

	def getRelatedItemColumns(self):
		return 4


	def getRelatedItemHeight(self):
		return 100

	def _readyInit(self):
		super()._readyInit()
		self.goldCost = int(self.getP("gold"))
		self.blackPieces = [
		self.ctx.item_book.getDescriptor("Black Pawn"), 
		self.ctx.item_book.getDescriptor("Black Knight"), 
		self.ctx.item_book.getDescriptor("Black Bishop"), 
		self.ctx.item_book.getDescriptor("Black Rook"), 
		self.ctx.item_book.getDescriptor("Black Queen"), 
		self.ctx.item_book.getDescriptor("Black King")
		]
		self.whitePieces = [
		self.ctx.item_book.getDescriptor("White Pawn"), 
		self.ctx.item_book.getDescriptor("White Knight"), 
		self.ctx.item_book.getDescriptor("White Bishop"), 
		self.ctx.item_book.getDescriptor("White Rook"), 
		self.ctx.item_book.getDescriptor("White Queen"), 
		self.ctx.item_book.getDescriptor("White King")
		]
		self.chessMasterDescr = self.ctx.item_book.getDescriptor("Chess Master")


_R.reg("res://gd_core_items/Exclusive/ChessBoard.gd", Exclusive__ChessBoard)
_R.reg("ChessBoard", Exclusive__ChessBoard)
