# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__RandomLoadoutBag(_R.C("res://gd_core_items/Bag.gd")):

	resource_path = "res://gd_core_items/Exclusive/RandomLoadoutBag.gd"

	def _init_fields(self):
		super()._init_fields()
		self.mainBags = { _H_1: ["Ranger Bag", "Vineweave Basket"], _H_2: ["Storage Coffin", "Relic Case"], _H_3: ["Fire Pit", "Portable Altar"], _H_4: ["Berserker Bag", "Toolbox"], _H_5: ["Scholar Bag", "Puzzlebox"], _H_6: ["Bag of Giving", "Sewing Case"], _H_7: ["Engineer Box", "Engineer Bag 2"] }
		self.compensationValue = { _H_1: [0, 0], _H_2: [1, 0], _H_3: [2, 1], _H_4: [1, 0], _H_5: [0, 0], _H_6: [0, 0], _H_7: [0, 0] }
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
		if self.ownerType == _H_8:
			self.ctx.util.callDelayed(self, "createRevealParticles", 0.4)


	def createRevealParticles(self):
		pass

	def _readyInit(self):
		super()._readyInit()
		pass



_R.reg("res://gd_core_items/Exclusive/RandomLoadoutBag.gd", Exclusive__RandomLoadoutBag)
_R.reg("RandomLoadoutBag", Exclusive__RandomLoadoutBag)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
    _H_1 = _R.C("CoreConst").Classes.Ranger
except AttributeError as _he:
    _H_1 = _HoistPending(_he)
try:
    _H_2 = _R.C("CoreConst").Classes.Reaper
except AttributeError as _he:
    _H_2 = _HoistPending(_he)
try:
    _H_3 = _R.C("CoreConst").Classes.Pyromancer
except AttributeError as _he:
    _H_3 = _HoistPending(_he)
try:
    _H_4 = _R.C("CoreConst").Classes.Berserker
except AttributeError as _he:
    _H_4 = _HoistPending(_he)
try:
    _H_5 = _R.C("CoreConst").Classes_Full.Mage
except AttributeError as _he:
    _H_5 = _HoistPending(_he)
try:
    _H_6 = _R.C("CoreConst").Classes_Full.Adventurer
except AttributeError as _he:
    _H_6 = _HoistPending(_he)
try:
    _H_7 = _R.C("CoreConst").Classes_Full.Engineer
except AttributeError as _he:
    _H_7 = _HoistPending(_he)
try:
    _H_8 = _R.C("CoreConst").Owner.PlayerInventory
except AttributeError as _he:
    _H_8 = _HoistPending(_he)
