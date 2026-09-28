# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ...._rt import *  # noqa: F401,F403

from .... import _registry as _R




class Exclusive__Chess__WhitePawn(_R.C("res://gd_core_items/Exclusive/Chess/ChessPiece.gd")):

	resource_path = "res://gd_core_items/Exclusive/Chess/WhitePawn.gd"

	def _init_fields(self):
		super()._init_fields()
		self.luck = None
		self.regen = None


	def doCapturingEffect(self, _eliminatedPiece):
		return self.giveRegeneration(self.regen)


	def doEliminatedEffect(self, _capturingPiece):
		self.giveLucky(self.luck)

	def _readyInit(self):
		super()._readyInit()
		self.luck = int(self.getP("luck"))
		self.regen = int(self.getP("regen"))


_R.reg("res://gd_core_items/Exclusive/Chess/WhitePawn.gd", Exclusive__Chess__WhitePawn)
_R.reg("WhitePawn", Exclusive__Chess__WhitePawn)
