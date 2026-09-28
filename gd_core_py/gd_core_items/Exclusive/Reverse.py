# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Reverse(_R.C("res://gd_core_items/Card.gd")):

	resource_path = "res://gd_core_items/Exclusive/Reverse.gd"

	def _init_fields(self):
		super()._init_fields()
		self.activationParticles = None


	def cardSecondaryEffectActive(self):
		return self.deck and self.deck.countDuplicates(self.chainPosition) == 0


	def doRevealEffect(self):
		self.giveReflectStacks(self.getP("reflect"))

		if self.cardSecondaryEffectActive():
			self.stealRandomBuff(self.getP("steal"))

		self.activate()


	def getCardDescription(self, descr):
		if self.deck:
			duplicates = self.deck.countDuplicates(self.chainPosition)
			state = _R.C("CoreConst").StatModified.No
			if duplicates == 0:
				state = _R.C("CoreConst").StatModified.Positive
			else:
				state = _R.C("CoreConst").StatModified.Negative
			descr += "\n" + self.insertParameter(tr("CARD_DUPLICATES"), "num", duplicates, state, False)
		elif self.placed:
			descr += "\n" + self.ctx.util.wrapInColor(tr("CARD_HINT"), self.ctx.util.paramColor)

		return descr

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Exclusive/Reverse.gd", Exclusive__Reverse)
_R.reg("Reverse", Exclusive__Reverse)
