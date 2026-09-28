# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ...._rt import *  # noqa: F401,F403

from .... import _registry as _R




class Exclusive__Chess__WhiteBishop(_R.C("res://gd_core_items/Exclusive/Chess/ChessPiece.gd")):

	resource_path = "res://gd_core_items/Exclusive/Chess/WhiteBishop.gd"

	def _init_fields(self):
		super()._init_fields()
		self.cleanses = None
		self.healamp = None


	def doCapturingEffect(self, _eliminatedPiece):
		return self.cleanseRandomDebuffs(self.cleanses)


	def doEliminatedEffect(self, _capturingPiece):
		self.character().addHealingEfficiency(self.healamp)

	def _readyInit(self):
		super()._readyInit()
		self.cleanses = int(self.getP("cleanse"))
		self.healamp = _div(self.getP('healamp'), 100.0)


_R.reg("res://gd_core_items/Exclusive/Chess/WhiteBishop.gd", Exclusive__Chess__WhiteBishop)
_R.reg("WhiteBishop", Exclusive__Chess__WhiteBishop)
