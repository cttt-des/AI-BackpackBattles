# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class RingEffect(GodotObject):
	def _init_fields(self):
		super()._init_fields()
		self.triggerType = 0
		self.stackType = 0


	def pushEncoded(self, bitStream):
		normalizedStack = self.stackType - _R.C("CoreConst").EventType.Lucky
		bitStream.push(self.triggerType, len(TriggerType))
		bitStream.push(normalizedStack, 16)


	def setFromEncoded(self, bitStream):
		self.triggerType = bitStream.pull(len(TriggerType))
		self.stackType = bitStream.pull(16) + _R.C("CoreConst").EventType.Lucky





class Exclusive__MagicRing(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/MagicRing.gd"

	TriggerType = EnumDict("TriggerType", {"StartOfBattle": 0, "Every": 1, "PlayerLow": 2, "OppoLow": 3})



	def _init_fields(self):
		super()._init_fields()
		self.stackToTypes = { _R.C("CoreConst").EventType.Lucky: _R.C("CoreConst").Type.Nature, _R.C("CoreConst").EventType.Spikes: _R.C("CoreConst").Type.Nature, _R.C("CoreConst").EventType.Regeneration: _R.C("CoreConst").Type.Holy, _R.C("CoreConst").EventType.Heat: _R.C("CoreConst").Type.Fire, _R.C("CoreConst").EventType.Vampirism: _R.C("CoreConst").Type.Vampiric, _R.C("CoreConst").EventType.Empower: _R.C("CoreConst").Type.Holy, _R.C("CoreConst").EventType.Mana: _R.C("CoreConst").Type.Magic, _R.C("CoreConst").EventType.Blind: _R.C("CoreConst").Type.Dark, _R.C("CoreConst").EventType.Cold: _R.C("CoreConst").Type.Ice, _R.C("CoreConst").EventType.Poison: _R.C("CoreConst").Type.Nature, }
		self.stackToColor = { _R.C("CoreConst").EventType.Lucky: Color(0.329826, 1, 0.263672), _R.C("CoreConst").EventType.Spikes: Color(0.700867, 1, 0.263672), _R.C("CoreConst").EventType.Regeneration: Color(1, 0.388672, 0.696724), _R.C("CoreConst").EventType.Heat: Color(1.1, 0.44, 0.24), _R.C("CoreConst").EventType.Vampirism: Color(0.900391, 0.04924, 0.04924), _R.C("CoreConst").EventType.Empower: Color(0.955078, 0.665003, 0.341366), _R.C("CoreConst").EventType.Mana: Color(0.257812, 0.330292, 1), _R.C("CoreConst").EventType.Blind: Color(0.569776, 0.196078, 1), _R.C("CoreConst").EventType.Cold: Color(0.196078, 0.952895, 1), _R.C("CoreConst").EventType.Poison: Color(0.008865, 0.648438, 0.176254) }
		self.effects = []
		self.effectDict = {}
		self.gainedStacks = 0
		self.playerLowTriggered = False
		self.oppoLowTriggered = False
		self.ringTypes = []
		self.textEffect = 0
		self.numEffects = None
		self.healthThreshold = None
		self.opponentHealthThreshold = None
		self.stones = None
		self.symbols = None


	def hasCooldown(self):
		return self.TriggerType.Every in self.effectDict


	def hasStartofBattle(self):
		return self.TriggerType.StartOfBattle in self.effectDict


	def onPrepare(self):
		self.playerLowTriggered = False
		self.oppoLowTriggered = False

		if self.TriggerType.PlayerLow in self.effectDict:
			self.connectForCombat(self.character(), "character_damaged", "onDamaged")

		if self.TriggerType.OppoLow in self.effectDict:
			self.connectForCombat(self.opponent(), "character_damaged", "onOppoDamaged")


	def onCombatStart(self):
		for effect in _iter(self.effectDict[self.TriggerType.StartOfBattle]):
			self.giveStacksFromEffect(effect)


	def doCooldownEffect(self):
		for effect in _iter(self.effectDict[self.TriggerType.Every]):
			self.giveStacksFromEffect(effect)


	def onDamaged(self, _healthChange, event):
		if self.playerLowTriggered:
			return

		relHealth = self.character().getRelativeHealth()
		if relHealth < self.healthThreshold:
			self.playerLowTriggered = True
			for effect in _iter(self.effectDict[self.TriggerType.PlayerLow]):
				self.giveStacksFromEffect(effect, event)


	def onOppoDamaged(self, _healthChange, event):
		if self.oppoLowTriggered:
			return

		relHealth = self.opponent().getRelativeHealth()
		if relHealth < self.opponentHealthThreshold:
			self.oppoLowTriggered = True
			for effect in _iter(self.effectDict[self.TriggerType.OppoLow]):
				self.giveStacksFromEffect(effect, event)


	def giveStacksFromEffect(self, effect, triggerEvent=None):
		target = None
		if _R.C("CoreConst").isBuff(effect.stackType):
			target = self.character()
		else:
			target = self.opponent()

		stackName = self.ctx.event_type_keys[effect.stackType].lower()
		paramScale = self.getP(_strv("scale", effect.triggerType + 1))
		self.giveStacks(target, effect.stackType, 
			self.getScaledParam(stackName, paramScale), triggerEvent)

		self.activate()



	def sortEffects(self):
		self.gainedStacks = 0
		self.effectDict.clear()
		self.ringTypes.clear()

		effectI = 0
		for effect in _iter(self.effects):
			effectI += 1

		if not self.isOnlyForDisplay():

			for effect in _iter(self.effects):
				self.ctx.util.dictAppend(self.effectDict, effect.triggerType, effect)

				self.gainedStacks |= 2 << (effect.stackType - _R.C("CoreConst").EventType.Lucky)

				newType = self.stackToTypes[effect.stackType]
				if not newType in self.ringTypes:
					self.ringTypes.append(newType)


			if self.inventory != None:
				self.inventory.onItemTypeChanged(self)
		else:
			pass


	def getTypes(self):
		return super().getTypes() + self.ringTypes


	def hasType(self, type):
		return type in self.ringTypes or super().hasType(type)


	def getNumStaticTypes(self):
		return super().getNumStaticTypes() + len(self.ringTypes)


	def gainsStack(self, stackType):
		return self.gainedStacks & stackType


	def gainsBuffs(self):
		return self.gainedStacks & _R.C("CoreConst").Stack.Buff


	def inflictsDebuffs(self):
		return self.gainedStacks & _R.C("CoreConst").Stack.Debuff


	def getTextEffect(self):
		return self.textEffect


	def randEffects(self, clearIfOnlyDisplay=True):
		self.effects.clear()

		for i in _iter(self.numEffects):
			effect = RingEffect()
			self.effects.append(effect)
			effect.triggerType = self.ctx.rng.randi_range(0, 3)
			effect.stackType = self.ctx.rng.randi_range(_R.C("CoreConst").EventType.Lucky, 
				_R.C("CoreConst").EventType.Cold)


		self.sortEffects()

		if clearIfOnlyDisplay and self.isOnlyForDisplay():
			self.effects.clear()


	def getScaledParam(self, stackName, paramScale):
		return round(self.getP(stackName) * paramScale)


	def isOnlyForDisplay(self):
		return (self.ownerType == _R.C("CoreConst").Owner.ItemLibrary or 
			self.ownerType == _R.C("CoreConst").Owner.InfoPanelIcon or 
			self.ownerType == _R.C("CoreConst").Owner.Tooltip or 
			self.ownerType == _R.C("CoreConst").Owner.RecipeBook or 
			self.ownerType == _R.C("CoreConst").Owner.BuildViewerIcon)


	def getDescription(self, wrapInColor=True):
		return ""

	def copyFrom(self, otherRing):
		self.setData(otherRing.getData())


	def getData(self):
		pass

	def setData(self, _data):
		pass

	def persistDataInShop(self):
		return True


	def getDataPersistent(self, bitStream):
		for effect in _iter(self.effects):
			effect.pushEncoded(bitStream)





	def getDataPersistentBits(self):
		return self.numEffects * (2 + 4)



	def onCraftedFrom(self, baseItem, ingredients):
		self.effects.clear()
		self.effects.extend(baseItem.effects)
		self.effects.extend(ingredients[0].effects)


		_pop_at(self.effects, self.ctx.rng.randi_range(0, 3))

		self.sortEffects()


















	def _readyInit(self):
		super()._readyInit()
		self.numEffects = int(self.getP("effects"))
		self.healthThreshold = _div(self.getP('healtht'), 100.0)
		self.opponentHealthThreshold = _div(self.getP('healtht_opp'), 100.0)
		self.stones = []
		self.symbols = []
		if (not self.stones):
			for i in _iter(self.numEffects):
				pass

		if self.ownerType == _R.C("CoreConst").Owner.ItemLibrary:
			pass
		else:

			if not self.wasJustCrafted:
				self.randEffects()


Exclusive__MagicRing.RingEffect = RingEffect


_R.reg("res://gd_core_items/Exclusive/MagicRing.gd", Exclusive__MagicRing)
_R.reg("MagicRing", Exclusive__MagicRing)
