# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ...._rt import *  # noqa: F401,F403

from .... import _registry as _R




class Exclusive__Chess__BlackQueen(_R.C("res://gd_core_items/Exclusive/Chess/ChessPiece.gd")):

	resource_path = "res://gd_core_items/Exclusive/Chess/BlackQueen.gd"

	def _init_fields(self):
		super()._init_fields()
		self.buffs = None


	def doCapturingEffect(self, _eliminatedPiece):
		if self.numCaptures == 1:
			return self.stealRandomBuff(self.buffs)
		else:
			return self.stealRandomBuff(1)


	def doEliminatedEffect(self, _capturingPiece):
		self.stun(self.getP_m("dur"))

	def _readyInit(self):
		super()._readyInit()
		self.buffs = int(self.getP("buffs"))


_R.reg("res://gd_core_items/Exclusive/Chess/BlackQueen.gd", Exclusive__Chess__BlackQueen)
_R.reg("BlackQueen", Exclusive__Chess__BlackQueen)
