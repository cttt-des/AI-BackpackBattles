# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ...._rt import *  # noqa: F401,F403

from .... import _registry as _R




class Exclusive__Chess__BlackKing(_R.C("res://gd_core_items/Exclusive/Chess/ChessPiece.gd")):

	resource_path = "res://gd_core_items/Exclusive/Chess/BlackKing.gd"

	def _init_fields(self):
		super()._init_fields()
		self.weaponSpeed = None
		self.buffs = None


	def onPrepare(self):
		if self.board != None:
			self.connectForCombat(self.board, "piece_captured", "onAnyPieceCaptured")


	def doCapturingEffect(self, _eliminatedPiece):
		for item in _iter(self.inventory.getItems()):
			if item.isWeapon():
				item.addSpeed(self.weaponSpeed)


	def onAnyPieceCaptured(self, capturingPiece, _eliminatedPiece):
		if capturingPiece.pieceColor == self.PieceColor.Black:
			if capturingPiece.numCaptures == 1:
				self.removeRandomBuffs(self.buffs)
			else:
				self.removeRandomBuffs(1)

	def _readyInit(self):
		super()._readyInit()
		self.weaponSpeed = _div(self.getP('speed'), 100.0)
		self.buffs = int(self.getP("buffs"))


_R.reg("res://gd_core_items/Exclusive/Chess/BlackKing.gd", Exclusive__Chess__BlackKing)
_R.reg("BlackKing", Exclusive__Chess__BlackKing)
