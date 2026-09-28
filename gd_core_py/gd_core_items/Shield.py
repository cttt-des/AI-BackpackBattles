# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class Shield(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Shield.gd"

	def _init_fields(self):
		super()._init_fields()
		self.blockedDamageRes = None


	def prepare(self):
		self.blockedDamageRes = None
		self.connectForCombat(self.character(), "pre_take_damage", "preTakeDamage")
		self.connectForCombat(self.character(), "character_attacked", "onCharacterAttacked")
		super().prepare()


	def getDamageBlock(self):
		return self.getP_m("damblock")


	def beforeBlock(self):
		self.blockedDamageRes.applyDamageReduction(self.getDamageBlock(), self)


	def afterBlock(self):
		pass


	def canBlockDamageRes(self, damageRes):
		return damageRes.triggerOnMeleeAttacked()


	def preTakeDamage(self, damageRes):
		if self.canBlockDamageRes(damageRes) and self.rollChance():
			self.blockedDamageRes = damageRes
			self.beforeBlock()


	def onCharacterAttacked(self, damageRes):
		if self.blockedDamageRes == damageRes:
			self.afterBlock()
			self.ctx.bus.emitSignal(self, "blocked", [self.blockedDamageRes])
			self.blockedDamageRes = None


	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Shield.gd", Shield)
_R.reg("Shield", Shield)
_R.reg("Shield", Shield)
