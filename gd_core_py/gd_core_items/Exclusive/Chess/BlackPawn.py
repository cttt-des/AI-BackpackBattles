# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ...._rt import *  # noqa: F401,F403

from .... import _registry as _R




class Exclusive__Chess__BlackPawn(_R.C("res://gd_core_items/Exclusive/Chess/ChessPiece.gd")):

	resource_path = "res://gd_core_items/Exclusive/Chess/BlackPawn.gd"

	def _init_fields(self):
		super()._init_fields()
		self.mana = None
		self.poison = None


	def doCapturingEffect(self, eliminatedPiece):
		return self.giveMana(self.mana)




	def doEliminatedEffect(self, _capturingPiece):
		self.inflictPoison(self.poison)

	def _readyInit(self):
		super()._readyInit()
		self.mana = int(self.getP("mana"))
		self.poison = int(self.getP("poison"))


_R.reg("res://gd_core_items/Exclusive/Chess/BlackPawn.gd", Exclusive__Chess__BlackPawn)
_R.reg("BlackPawn", Exclusive__Chess__BlackPawn)
