# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ...._rt import *  # noqa: F401,F403

from .... import _registry as _R




class Exclusive__Chess__WhiteQueen(_R.C("res://gd_core_items/Exclusive/Chess/ChessPiece.gd")):

	resource_path = "res://gd_core_items/Exclusive/Chess/WhiteQueen.gd"

	def _init_fields(self):
		super()._init_fields()
		self.heat = None
		self.heatFirstCapture = None


	def doCapturingEffect(self, _eliminatedPiece):
		if self.numCaptures == 1:
			return self.giveHeat(self.heatFirstCapture)
		else:
			return self.giveHeat(self.heat)


	def doEliminatedEffect(self, _capturingPiece):
		self.character().makeInvulnerable(self.getP_m("dur"), self)

	def _readyInit(self):
		super()._readyInit()
		self.heat = int(self.getP("heat2"))
		self.heatFirstCapture = int(self.getP("heat1"))


_R.reg("res://gd_core_items/Exclusive/Chess/WhiteQueen.gd", Exclusive__Chess__WhiteQueen)
_R.reg("WhiteQueen", Exclusive__Chess__WhiteQueen)
