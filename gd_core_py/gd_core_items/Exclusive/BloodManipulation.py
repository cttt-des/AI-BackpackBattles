# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__BloodManipulation(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/BloodManipulation.gd"

	def _init_fields(self):
		super()._init_fields()
		self.unhealing = None
		self.vampirism = None
		self.vampiricSpeed = None
		self.bloodAmulet = None


	def canAffect(self, item):
		return item.hasType(_H_1)


	def onPrepare(self):
		self.character().giveUnhealing(self.unhealing)
		self.addSpeed(self.vampiricSpeed * self.getNumAffectedItems())


	def doCooldownEffect(self):
		self.giveVampirism(self.vampirism)
		self.activate()


	def onItemRoll(self, descr):
		pass

	def _readyInit(self):
		super()._readyInit()
		self.unhealing = _div(self.getP('unhealing'), 100.0)
		self.vampirism = int(self.getP("vampirism"))
		self.vampiricSpeed = _div(self.getP('speed'), 100.0)
		self.bloodAmulet = self.ctx.item_book.getDescriptor("Blood Amulet")


_R.reg("res://gd_core_items/Exclusive/BloodManipulation.gd", Exclusive__BloodManipulation)
_R.reg("BloodManipulation", Exclusive__BloodManipulation)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
    _H_1 = _R.C("CoreConst").Type.Vampiric
except AttributeError as _he:
    _H_1 = _HoistPending(_he)
