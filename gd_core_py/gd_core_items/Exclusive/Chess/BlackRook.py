# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ...._rt import *  # noqa: F401,F403

from .... import _registry as _R




class Exclusive__Chess__BlackRook(_R.C("res://gd_core_items/Exclusive/Chess/ChessPiece.gd")):

	resource_path = "res://gd_core_items/Exclusive/Chess/BlackRook.gd"

	def _init_fields(self):
		super()._init_fields()
		self.buffTimer = None
		self.spikes = None
		self.crit = None


	def doCapturingEffect(self, _eliminatedPiece):
		return self.giveSpikes(self.spikes)


	def doEliminatedEffect(self, _capturingPiece):
		self.changeAllItemsCritRate(self.crit)
		self.buffTimer.start(self.getP_m("dur"))


	def buffEnded(self):
		self.changeAllItemsCritRate( - self.crit)

	def _readyInit(self):
		super()._readyInit()
		self.buffTimer = self.newItemTimer("BuffTimer", "buffEnded", False)
		self.spikes = int(self.getP("spikes"))
		self.crit = self.getP("crit")


_R.reg("res://gd_core_items/Exclusive/Chess/BlackRook.gd", Exclusive__Chess__BlackRook)
_R.reg("BlackRook", Exclusive__Chess__BlackRook)
