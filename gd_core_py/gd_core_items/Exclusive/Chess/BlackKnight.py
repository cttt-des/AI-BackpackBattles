# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ...._rt import *  # noqa: F401,F403

from .... import _registry as _R




class Exclusive__Chess__BlackKnight(_R.C("res://gd_core_items/Exclusive/Chess/ChessPiece.gd")):

	resource_path = "res://gd_core_items/Exclusive/Chess/BlackKnight.gd"

	def _init_fields(self):
		super()._init_fields()
		self.vampirism = None
		self.stamina = None


	def doCapturingEffect(self, _eliminatedPiece):
		return self.giveVampirism(self.vampirism)


	def doEliminatedEffect(self, _capturingPiece):
		self.drainStamina(self.stamina)


	def canBeBlocked(self):
		return False

	def _readyInit(self):
		super()._readyInit()
		self.vampirism = int(self.getP("vampirism"))
		self.stamina = self.getP("stamina")


_R.reg("res://gd_core_items/Exclusive/Chess/BlackKnight.gd", Exclusive__Chess__BlackKnight)
_R.reg("BlackKnight", Exclusive__Chess__BlackKnight)
