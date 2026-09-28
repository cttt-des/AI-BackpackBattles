# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ...._rt import *  # noqa: F401,F403

from .... import _registry as _R




class Exclusive__Chess__WhiteKnight(_R.C("res://gd_core_items/Exclusive/Chess/ChessPiece.gd")):

	resource_path = "res://gd_core_items/Exclusive/Chess/WhiteKnight.gd"

	def _init_fields(self):
		super()._init_fields()
		self.boardSpeed = None
		self.stamina = None


	def doCapturingEffect(self, _eliminatedPiece):
		self.board.addSpeed(self.boardSpeed)



	def doEliminatedEffect(self, _capturingPiece):
		self.giveMaxStaminaTemporary(self.stamina)


	def canBeBlocked(self):
		return False

	def _readyInit(self):
		super()._readyInit()
		self.boardSpeed = _div(self.getP('speed'), 100.0)
		self.stamina = self.getP("stamina")


_R.reg("res://gd_core_items/Exclusive/Chess/WhiteKnight.gd", Exclusive__Chess__WhiteKnight)
_R.reg("WhiteKnight", Exclusive__Chess__WhiteKnight)
