# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__SpeakwithAnimals(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/SpeakwithAnimals.gd"

	def _init_fields(self):
		super()._init_fields()
		self.petDescriptors = [[], [], [], [], []]
		self.salesChance = None

	pets = [
		"Rat", "Squirrel", "Rat Chef", "Hedgehog", "Squirrel Archer", 
		"Hyper Hedgehog", "Carrot Goobert", "Snowmaster", "Forest Dragon", 
		"Toad", "Poison Goobert", "Poison Frog", "Ruby Chonk", "Frog Prince", 
		"Crow", "Ice Dragon", 
		"Courage Puppy", "Wisdom Puppy", "Power Puppy", 
		"Armored Courage Puppy", "Armored Wisdom Puppy", "Armored Power Puppy", 
		"Cheese Goobert", "Steel Dragon", 
		"Chili Goobert", "Fire Shelly", "Phoenix", "Phoenix2", 
		"Emerald Whelp", "Sapphire Whelp", "Amethyst Whelp", "Obsidian Dragon", 
		"Cat Spirit", "Owl Spirit", "Badger Spirit", "Cupcake Goobert", "Cupcake Dragon", 
		"Broccoli Goobert", "Dragon Knight", "Jynx Staff", 
		"Robodog", "Toast Goobert", "Mecha Bat", "Thunder Drake", 
		"Goobling", "Shelly", "Steel Goobert", "Blood Goobert", "Ruby Whelp", 
	]

	def onSaleRoll(self, item):
		pass

	def getGatedDescriptor(self, rarity):
		pass

	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Pet)


	def doCooldownEffect(self):
		for item in _iter(self.getAffectedItems()):
			item.giveDoubleActivationChance(self.getChance())

		self.activate()


	def getRelatedItems(self):
		return self.ctx.util.flatten(self.petDescriptors)


	def getRelatedItemColumns(self):
		return 6


	def getRelatedItemHeight(self):
		return 100

	def _readyInit(self):
		super()._readyInit()
		self.salesChance = _div(self.getP('sale'), 100.0)
		for pet in _iter(self.pets):
			desc = self.ctx.item_book.getDescriptor(pet)
			if desc.isReleased():
				self.petDescriptors[desc.getRarity()].append(desc)



_R.reg("res://gd_core_items/Exclusive/SpeakwithAnimals.gd", Exclusive__SpeakwithAnimals)
_R.reg("SpeakwithAnimals", Exclusive__SpeakwithAnimals)
