# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ...._rt import *  # noqa: F401,F403

from .... import _registry as _R




class Exclusive__Chess__WhiteRook(_R.C("res://gd_core_items/Exclusive/Chess/ChessPiece.gd")):

	resource_path = "res://gd_core_items/Exclusive/Chess/WhiteRook.gd"

	def _init_fields(self):
		super()._init_fields()
		self.buffTimer = None
		self.damReduction = None


	def doCapturingEffect(self, _eliminatedPiece):
		return self.giveBlock()


	def doEliminatedEffect(self, _capturingPiece):
		self.character().changeDamageResistance(self.damReduction)
		self.buffTimer.start(self.getP_m("dur"))


	def buffEnded(self):
		self.character().changeDamageResistance( - self.damReduction)

	def _readyInit(self):
		super()._readyInit()
		self.buffTimer = self.newItemTimer("BuffTimer", "buffEnded", False)
		self.damReduction = self.getP("dam")


_R.reg("res://gd_core_items/Exclusive/Chess/WhiteRook.gd", Exclusive__Chess__WhiteRook)
_R.reg("WhiteRook", Exclusive__Chess__WhiteRook)
