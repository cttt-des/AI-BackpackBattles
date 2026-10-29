# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ...._rt import *  # noqa: F401,F403

from .... import _registry as _R




class ChessPiece(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/Chess/ChessPiece.gd"

	PieceColor = EnumDict("PieceColor", {"Black": 0, "White": 1})



	def _init_fields(self):
		super()._init_fields()
		self._pieceColor = 0
		self.moveCells = []
		self.captured = False
		self._numCaptures = 0
		self.board = None
		self.noBoardMark = None

	@property
	def pieceColor(self):
		return self._pieceColor
	@pieceColor.setter
	def pieceColor(self, v):
		self._pieceColor = int(v)
	@property
	def numCaptures(self):
		return self._numCaptures
	@numCaptures.setter
	def numCaptures(self, v):
		self._numCaptures = int(v)

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
			# fam_r1 棋族面：decomp Items/Exclusive/Chess/ChessPiece.gd:50-51 按局部格消费（cell.rotated(rotation) 后 ChessBoard.gd:104 occupied[0]+cell 还原全局）；内核 affectedTileCells 为绝对格（装配已烘焙旋转）→ 换算回局部
			self.moveCells.append((cell - self.occupiedCells[0]).round())

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
		# decomp Items/Exclusive/Chess/ChessPiece.gd:74 Sound.playSound(captureSounds.pick_random(), 0, Util.randPitch())——GDScript 实参求值即消耗：randPitch 1 抽
		# 同行 pick_random 走引擎全局链（docs/rng_truth.md §1.4-2）：1 抽，r1_0 台账轮起改道入账
		self.ctx.rng.pickRandomEngine([None, None, None], 'Exclusive/Chess/ChessPiece.gd:74')
		self.ctx.rng.randf_range(0.9, 1.1)
		event = self.doCapturingEffect(eliminatedPiece)
		return event


	def doCapturingEffect(self, eliminatedPiece):
		pass


	def onEliminatedBy(self, capturingPiece, activateEvent):
		self.setState(True, False, activateEvent)
		self.doEliminatedEffect(capturingPiece)


	def doEliminatedEffect(self, capturingPiece):
		pass


	def repositionPiece(self, toCell):
		# r4_2 棋族面：decomp Items/Exclusive/Chess/ChessPiece.gd:93-97 ——
		# z_index/moveTo/movebackTween 为表现面剥离；判定面 inventory.moveItem
		# （Inventory.gd:640-647，捕获者占被吃格）保留 → 内核 CoreGrid.moveItem
		self.inventory.moveItem(self, [toCell])

	def onShopEntered(self):
		self.onStateChanged(False)



	def onStateChanged(self, state):
		if typeof(state) == TYPE_VECTOR2:
			targetCell = state
			self.repositionPiece(targetCell)
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
