# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ...._rt import *  # noqa: F401,F403

from .... import _registry as _R




class Exclusive__Chess__BlackBishop(_R.C("res://gd_core_items/Exclusive/Chess/ChessPiece.gd")):

	resource_path = "res://gd_core_items/Exclusive/Chess/BlackBishop.gd"

	def _init_fields(self):
		super()._init_fields()
		self.debuffs = None
		self.healReduction = None
		self.maxHealthReduction = None


	def doCapturingEffect(self, _eliminatedPiece):
		return self.inflictRandomDebuffs(self.debuffs)


	def doEliminatedEffect(self, _capturingPiece):
		self.opponent().reduceHealingEfficiency(self.healReduction)
		self.opponent().changeMaxHealthGain(self.maxHealthReduction)


	def _readyInit(self):
		super()._readyInit()
		self.debuffs = int(self.getP("debuffs"))
		self.healReduction = _div(self.getP('healreduction'), 100.0)
		self.maxHealthReduction = _div(-self.getP('healthreduction'), 100.0)


_R.reg("res://gd_core_items/Exclusive/Chess/BlackBishop.gd", Exclusive__Chess__BlackBishop)
_R.reg("BlackBishop", Exclusive__Chess__BlackBishop)
