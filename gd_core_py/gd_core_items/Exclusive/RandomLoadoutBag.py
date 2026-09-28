# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__RandomLoadoutBag(_R.C("res://gd_core_items/Bag.gd")):

	resource_path = "res://gd_core_items/Exclusive/RandomLoadoutBag.gd"

	def _init_fields(self):
		super()._init_fields()
		self.mainBags = { _R.C("CoreConst").Classes.Ranger: ["Ranger Bag", "Vineweave Basket"], _R.C("CoreConst").Classes.Reaper: ["Storage Coffin", "Relic Case"], _R.C("CoreConst").Classes.Pyromancer: ["Fire Pit", "Portable Altar"], _R.C("CoreConst").Classes.Berserker: ["Berserker Bag", "Toolbox"], _R.C("CoreConst").Classes_Full.Mage: ["Scholar Bag", "Puzzlebox"], _R.C("CoreConst").Classes_Full.Adventurer: ["Bag of Giving", "Sewing Case"], _R.C("CoreConst").Classes_Full.Engineer: ["Engineer Box", "Engineer Bag 2"] }
		self.compensationValue = { _R.C("CoreConst").Classes.Ranger: [0, 0], _R.C("CoreConst").Classes.Reaper: [1, 0], _R.C("CoreConst").Classes.Pyromancer: [2, 1], _R.C("CoreConst").Classes.Berserker: [1, 0], _R.C("CoreConst").Classes_Full.Mage: [0, 0], _R.C("CoreConst").Classes_Full.Adventurer: [0, 0], _R.C("CoreConst").Classes_Full.Engineer: [0, 0] }
		self.excludeNames = [ "Acorn Collar", "Unstable Recombobulator", "Draconic Orb", "Stone Skin Potion", "Divine Potion" ]
		self.bagCells = []

	bagRarityWeights = {
		_R.C("CoreConst").Rarity.Common: 2, 
		_R.C("CoreConst").Rarity.Rare: 0.5, 
		_R.C("CoreConst").Rarity.Epic: 0.2, 
		_R.C("CoreConst").Rarity.Legendary: 0.1, 
		_R.C("CoreConst").Rarity.Godly: 0.05, 
	}

	def addBagWherePossible(self, bag, startPos):
		pass

	def addItemWherePossible(self, item):
		pass

	def shopOpened(self):
		pass

	def prepareParticles(self):
		if self.ownerType == _R.C("CoreConst").Owner.PlayerInventory:
			self.ctx.util.callDelayed(self, "createRevealParticles", 0.4)


	def createRevealParticles(self):
		pass

	def _readyInit(self):
		super()._readyInit()
		pass



_R.reg("res://gd_core_items/Exclusive/RandomLoadoutBag.gd", Exclusive__RandomLoadoutBag)
_R.reg("RandomLoadoutBag", Exclusive__RandomLoadoutBag)
