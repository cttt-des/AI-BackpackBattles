# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ...._rt import *  # noqa: F401,F403

from .... import _registry as _R




class ChessPiece(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/Chess/ChessPiece.gd"

	PieceColor = EnumDict("PieceColor", {"Black": 0, "White": 1})



	def _init_fields(self):
		super()._init_fields()
		self.pieceColor = 0
		self.moveCells = []
		self.captured = False
		self.numCaptures = 0
		self.board = None
		self.noBoardMark = None


	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.ChessPiece) and item.pieceColor != self.pieceColor


	def affectsEmpty(self, color):
		return True


	def setBoard(self, _board):
		self.board = _board
		if self.board == None and self.placed:
			pass
		else:
			pass


	def prepare(self):
		self.setState(self.occupiedCells[0])

		self.moveCells.clear()
		for cell in _iter(self.getAffectedCells_tilemap()):
			self.moveCells.append(cell.rotated(self.rotation).round())

		self.numCaptures = 0

		super().prepare()


	def getMoveCells(self):
		return self.moveCells


	def getCaptureCells(self):
		return self.moveCells


	def onPieceMoved(self, targetCell):

		self.setState(targetCell)



	def onPieceCaptured(self, eliminatedPiece, activateEvent):
		self.numCaptures += 1
		targetCell = eliminatedPiece.occupiedCells[0]
		self.inventory.clearItemCells(eliminatedPiece)

		self.setState(targetCell, False, activateEvent)
		event = self.doCapturingEffect(eliminatedPiece)
		return event


	def doCapturingEffect(self, eliminatedPiece):
		pass


	def onEliminatedBy(self, capturingPiece, activateEvent):
		pass

	def doEliminatedEffect(self, capturingPiece):
		pass


	def repositionPiece(self, toCell):
		pass

	def onShopEntered(self):
		self.onStateChanged(False)



	def onStateChanged(self, state):
		if typeof(state) == TYPE_VECTOR2:
			targetCell = state

		else:
			self.captured = state
			if self.captured:

				self.inventory.clearItemCells(self)
			else:
				pass



	def onAddToInventory(self):
		pass

	def onRemoveFromInventory(self):
		pass


	def getDescription(self, wrapInColor=True):
		descr = super().getDescription(wrapInColor)
		if self.placed and self.board == None:
			descr += "\n\n" + self.ctx.util.wrapInColor(tr("HINT_Chess"), self.ctx.util.paramColor)
		return descr


	def discard(self, discardGems=True):
		super().discard(discardGems)

	def canBeBlocked(self):
		return True

	def _readyInit(self):
		super()._readyInit()
		if "White" in self.name:
			self.pieceColor = self.PieceColor.White
		else:
			self.pieceColor = self.PieceColor.Black



_R.reg("res://gd_core_items/Exclusive/Chess/ChessPiece.gd", ChessPiece)
_R.reg("ChessPiece", ChessPiece)
_R.reg("ChessPiece", ChessPiece)
