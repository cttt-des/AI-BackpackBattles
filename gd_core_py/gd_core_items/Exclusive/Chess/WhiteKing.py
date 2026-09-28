# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ...._rt import *  # noqa: F401,F403

from .... import _registry as _R




class Exclusive__Chess__WhiteKing(_R.C("res://gd_core_items/Exclusive/Chess/ChessPiece.gd")):

	resource_path = "res://gd_core_items/Exclusive/Chess/WhiteKing.gd"

	def _init_fields(self):
		super()._init_fields()
		self.empower = None
		self.buffs = None


	def onPrepare(self):
		if self.board != None:
			self.connectForCombat(self.board, "piece_captured", "onAnyPieceCaptured")


	def doCapturingEffect(self, _eliminatedPiece):
		return self.giveEmpower(self.empower)


	def onAnyPieceCaptured(self, capturingPiece, _eliminatedPiece):
		if capturingPiece.pieceColor == self.PieceColor.White:
			if capturingPiece.numCaptures == 1:
				self.giveRandomBuffs(self.buffs)
			else:
				self.giveRandomBuffs(1)

	def _readyInit(self):
		super()._readyInit()
		self.empower = int(self.getP("empower"))
		self.buffs = int(self.getP("buffs"))


_R.reg("res://gd_core_items/Exclusive/Chess/WhiteKing.gd", Exclusive__Chess__WhiteKing)
_R.reg("WhiteKing", Exclusive__Chess__WhiteKing)
