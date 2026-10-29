# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Ukulele(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/Ukulele.gd"

	def _init_fields(self):
		super()._init_fields()
		self.nonMusicalItems = []
		self._activateIndex = 0
		self.options = []
		self.speedPerItem = None
		self.cdAdvance = None
		self.healAmp = None
		self.buffs = None
		self.cold = None

	@property
	def activateIndex(self):
		return self._activateIndex
	@activateIndex.setter
	def activateIndex(self, v):
		self._activateIndex = int(v)

	def canAffect(self, item):
		return True


	def canAffect_secondary(self, item):
		return item.hasType(_R.C("CoreConst").Type.Musical)


	def onPrepare(self):
		self.activateIndex = 0
		self.nonMusicalItems.clear()
		for item in _iter(self.inventory.getItems()):
			if ( not item.hasType(_R.C("CoreConst").Type.Musical) and 
				item.hasCooldown()):
				self.nonMusicalItems.append(item)

		if not (not self.nonMusicalItems):
			self.ctx.rng.shuffleEngine(self.nonMusicalItems, 'Exclusive/Ukulele.gd:34')

			for item in _iter(self.getAffectedItems(_R.C("CoreConst").Affected.Secondary)):
				self.connectForCombat(item, "activated", "onItemActivated")

		self.addSpeed(self.speedPerItem * self.getNumAffectedItems())

		self.character().addHealingEfficiency(self.healAmp)

		for item in _iter(self.inventory.getItems()):
			item.changeAmplificiationChancePercent_allBuffs(self.getChance())

		self.options = [0, 1, 2]


	def onItemActivated(self, event):


		while True:
			if (not self.nonMusicalItems):
				return

			item = self.nonMusicalItems[self.activateIndex]

			if item.isCooldownActive():


				item.advanceCooldownPercent(self.cdAdvance)
				self.activateIndex = _mod(self.activateIndex + 1, len(self.nonMusicalItems))
				break
			else:


				_erase(self.nonMusicalItems, item)
				if not (not self.nonMusicalItems):
					self.activateIndex %= len(self.nonMusicalItems)


	def doCooldownEffect(self):
		rng = self.ctx.util.pickRandomElement(self.options)
		if rng == 0:
			self.heal()
		elif rng == 1:
			self.giveRandomBuffs(self.buffs)
		else:
			self.inflictCold(self.cold)

		self.activate()

		self.options = [0, 1, 2]
		_erase(self.options, rng)


	def playPickupSound(self):
		# decomp Items/Exclusive/Ukulele.gd:90 Sound.playSound_process(pickupSound, - 4, Util.randPitch(0.15))——GDScript 实参求值即消耗：randPitch 1 抽
		self.ctx.rng.randf_range(0.9, 1.1)
		pass


	def playDropSound(self, volume=0):
		volume += self.impactSoundVolume

		# decomp Items/Exclusive/Ukulele.gd:94 Sound.playSound(dropSound, volume - 4, Util.randPitch(0.15))——GDScript 实参求值即消耗：randPitch 1 抽
		self.ctx.rng.randf_range(0.9, 1.1)
	def _readyInit(self):
		super()._readyInit()
		self.speedPerItem = _div(self.getP('speed'), 100.0)
		self.cdAdvance = self.getP("advance")
		self.healAmp = _div(self.getP('healamp'), 100.0)
		self.buffs = int(self.getP("buffs"))
		self.cold = int(self.getP("cold"))


_R.reg("res://gd_core_items/Exclusive/Ukulele.gd", Exclusive__Ukulele)
_R.reg("Ukulele", Exclusive__Ukulele)
