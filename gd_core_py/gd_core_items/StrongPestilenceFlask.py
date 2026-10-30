# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class StrongPestilenceFlask_2(_R.C("res://gd_core_items/PestilenceFlask.gd")):

	resource_path = "res://gd_core_items/StrongPestilenceFlask.gd"

	def _init_fields(self):
		super()._init_fields()
		self.poisonTimer = None


	def getAffectedItems(self, color=GD_DEFAULT):
		if color is GD_DEFAULT:
			color = _R.C("CoreConst").Affected.Primary
		# ★ np25 evt12 面 GRD 探针（双门控零耗）：aff 格级真值——faceDirection/
		#   collision 全局格/cache 格/命中物品，定 getAffectedItems 错位。
		_r = super().getAffectedItems(color)
		if self.ctx != None and self.ctx.rng != None:
			_cp = self.getCollisionPoints()
			_rc = self.getCellsForGlobalPositions(_cp)
			_cc = self.getAffectedCellsInInventory_cached(color)
			_names = ""
			for _a in _iter(_r):
				_names += String(_a.descriptor.identifier) + "@" + str(_a.occupiedCells) + ","
			self.ctx.rng.trace_diag("GRD", String(self.descriptor.identifier),
					"fd=" + str(self.faceDirection) + " cp=" + str(_cp) + " aff=" + str(_cc), _names + "n=" + str(len(_r)))
		return _r

	def onTriggerPotion(self, triggerEvent=None):
		super().onTriggerPotion(triggerEvent)
		self.poisonTimer.start(self.getP3())


	def poisonTimerTimeout(self):
		self.inflictPoison(self.getP4())


	def onCombatEnd(self):
		self.poisonTimer.stop()

	def _readyInit(self):
		super()._readyInit()
		self.poisonTimer = self.newItemTimer("PoisonTimer", "poisonTimerTimeout", True)


_R.reg("res://gd_core_items/StrongPestilenceFlask.gd", StrongPestilenceFlask_2)
_R.reg("StrongPestilenceFlask", StrongPestilenceFlask_2)
