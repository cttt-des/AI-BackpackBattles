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
			state = _H_1
			if duplicates == 0:
				state = _H_2
			else:
				state = _H_3
			descr += "\n" + self.insertParameter(tr("CARD_DUPLICATES"), "num", duplicates, state, False)
		elif self.placed:
			descr += "\n" + self.ctx.util.wrapInColor(tr("CARD_HINT"), self.ctx.util.paramColor)

		return descr

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Exclusive/Reverse.gd", Exclusive__Reverse)
_R.reg("Reverse", Exclusive__Reverse)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").StatModified.No
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
try:
	_H_2 = _R.C("CoreConst").StatModified.Positive
except AttributeError as _he:
	_H_2 = _HoistPending(_he)
try:
	_H_3 = _R.C("CoreConst").StatModified.Negative
except AttributeError as _he:
	_H_3 = _HoistPending(_he)
