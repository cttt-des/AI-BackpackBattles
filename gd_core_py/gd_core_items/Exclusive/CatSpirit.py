# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__CatSpirit(_R.C("res://gd_core_items/Exclusive/SpiritCompanion.gd")):

	resource_path = "res://gd_core_items/Exclusive/CatSpirit.gd"

	def _init_fields(self):
		super()._init_fields()
		self.manaNeeded = None
		self.luck = None
		self.empower = None


	def canAffect(self, item):
		return item.canDamage()


	def onPrepare(self):
		for item in _iter(self.getAffectedItems()):
			item.addCritChancePercent(self.getChance())


	def doCooldownEffect(self):
		if self.character().getMana() >= self.manaNeeded:
			event = self.useMana(self.manaNeeded)
			self.giveLucky(self.luck, event)
			self.giveEmpower(self.empower, event)

		self.activate()



	def playPickupSound(self):
		pass


	def playDropSound(self, volume=0):
		volume += self.impactSoundVolume
		# ★ kernel_r2c 移植补抽：原版此行含 Util.randPitch(0.1)（=randf_range(0.9, 1.1)，
		#   Util.gd:685-686），转译期随音效行被剥——链消耗丢失（activate() 虚分发
		#   后此覆写生效，抽面必须与原版一致）。
		self.ctx.rng.randf_range(0.9, 1.1)

	def _readyInit(self):
		super()._readyInit()
		self.manaNeeded = int(self.getP("manat"))
		self.luck = int(self.getP("luck"))
		self.empower = int(self.getP("empower"))


_R.reg("res://gd_core_items/Exclusive/CatSpirit.gd", Exclusive__CatSpirit)
_R.reg("CatSpirit", Exclusive__CatSpirit)
