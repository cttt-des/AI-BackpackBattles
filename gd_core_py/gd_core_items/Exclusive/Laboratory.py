# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Laboratory(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/Laboratory.gd"

	def _init_fields(self):
		super()._init_fields()
		self.phase = 0
		self.typesDict = {}
		self.fluidTween = None
		self.fluid = None
		self.fluidMat = None

	params = {
		"luckt": 1, 
		"heatt": 4, 
		"heat_bonus": 1, 
		"heat": 4, 
		"spikest": 6, 
		"spikes_bonus": 1, 
		"spikes": 8, 
		"regent": 8, 
		"regen_bonus": 1, 
		"regen": 10, 
		"vampirism": 12, 
		"vamp_bonus": 1, 
		"vampt": 10, 
		"empower_bonus": 1, 
		"empower": 14
	}
	flashColor = Color(1.3, 1.3, 1.3)
	DUR = 0.2

	def onShopEntered(self):
		self.onStateChanged( - 1)


	def getDescription(self, wrapInColor=True):
		descr = self.descriptor.getDescription()

		for param in _iter(self.params):
			descr = self.insertParameter(descr, _strv("p_", param), self.params[param], 
				_R.C("CoreConst").StatModified.No, False, wrapInColor)

		return self.insertParameters(descr, wrapInColor)


	def onPreCombatStart(self):
		self.setState(0)
		self.typesDict = self.countTypes(self.getAffectedItems())


	def trigger(self):
		self.setState(self.phase + 1)

		super().trigger()





	def canAffect(self, item):
		return (item.hasType(_R.C("CoreConst").Type.Fire) or 
				item.hasType(_R.C("CoreConst").Type.Nature) or 
				item.hasType(_R.C("CoreConst").Type.Holy) or 
				item.hasType(_R.C("CoreConst").Type.Vampiric) or 
				item.isClassItem(_R.C("CoreConst").Classes_Full.Engineer))


	def doCooldownEffect(self):
		if self.phase == 1:
			if self.character().getLucky() >= self.params["luckt"]:
				event = self.useLucky(self.params["luckt"])
				numFire = self.typesDict[_R.C("CoreConst").Type.Fire]
				self.giveHeat(self.params["heat"] + numFire * self.params["heat_bonus"], event)

		elif self.phase == 2:
			if self.character().getHeat() >= self.params["heatt"]:
				event = self.useHeat(self.params["heatt"])
				numNature = self.typesDict[_R.C("CoreConst").Type.Nature]
				self.giveSpikes(self.params["spikes"] + numNature * self.params["spikes_bonus"], event)

		elif self.phase == 3:
			if self.character().getSpikes() >= self.params["spikest"]:
				event = self.useSpikes(self.params["spikest"])
				numHoly = self.typesDict[_R.C("CoreConst").Type.Holy]
				self.giveRegeneration(self.params["regen"] + numHoly * self.params["regen_bonus"], event)

		elif self.phase == 4:
			if self.character().getRegeneration() >= self.params["regent"]:
				event = self.useRegeneration(self.params["regent"])
				numVamp = self.typesDict[_R.C("CoreConst").Type.Vampiric]
				self.giveVampirism(self.params["vampirism"] + numVamp * self.params["vamp_bonus"], event)

		elif self.phase == 5:
			if self.character().getVampirism() >= self.params["vampt"]:
				event = self.useVampirism(self.params["vampt"])
				numEngineer = 0
				for item in _iter(self.getAffectedItems()):
					if item.isClassItem(_R.C("CoreConst").Classes_Full.Engineer):
						numEngineer += 1
				self.giveEmpower(self.params["empower"] + numEngineer * self.params["empower_bonus"], event)

		if self.phase == 5:
			self.onAfterEffectFinished()
		else:
			self.activate()


	def onStateChanged(self, _phase):
		self.phase = _phase
		if self.phase <= 0:
			self.baseCooldownOverride = self.getBaseCooldownIndex(0)
		elif self.phase < 5:
			self.baseCooldownOverride = self.getBaseCooldownIndex(self.phase) - self.getBaseCooldownIndex(self.phase - 1)





	def switchGradient(self):
		pass



	def _readyInit(self):
		super()._readyInit()
		self.phase = - 1
		self.switchGradient()



_R.reg("res://gd_core_items/Exclusive/Laboratory.gd", Exclusive__Laboratory)
_R.reg("Laboratory", Exclusive__Laboratory)
