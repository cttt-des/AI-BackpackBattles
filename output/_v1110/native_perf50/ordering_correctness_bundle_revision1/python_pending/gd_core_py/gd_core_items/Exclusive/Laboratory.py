# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import (  # noqa: F401

    Color,
    Dictionary,
    EnumDict,
    FuncRef,
    GD_DEFAULT,
    INF,
    NAN,
    Node,
    Node2D,
    OS_has_feature,
    Object,
    PCG32,
    PI,
    PoolStringArray,
    RandomNumberGenerator,
    Reference,
    Resource,
    Signal,
    String,
    TAU,
    TYPE_VECTOR2,
    Vector2,
    Vector3,
    _HoistPending,
    _bind_battle,
    _div,
    _dup,
    _erase,
    _fill,
    _find,
    _gd_fmt,
    _gd_range,
    _gd_str,
    _get_slice,
    _gid,
    _has_behavior_cache_get,
    _has_behavior_cache_put,
    _hash,
    _invert,
    _iter,
    _join,
    _load,
    _mod,
    _os_environ_get,
    _pick_random,
    _pop_at,
    _resize,
    _shuffle,
    _sort_custom,
    _strv,
    _substr,
    ceil,
    clamp,
    deg2rad,
    f32,
    floor,
    fmod,
    gd_round,
    get_stack,
    inverse_lerp,
    is_equal_approx,
    is_instance_valid,
    lerp,
    move_toward,
    posmod,
    pow,
    rad2deg,
    randomize,
    round,
    sign,
    smoothstep,
    snapped,
    sqrt,
    stepify,
    tr,
    typeof,
    wrapf,
    wrapi
,
)

if "GodotObject" not in globals():
	from ..._rt import GodotObject  # 纯 py 补绑；编译态 pxd 已预绑

from ... import _registry as _R
if "_base_cls_Exclusive__Laboratory" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__Laboratory





class Exclusive__Laboratory(_base_cls_Exclusive__Laboratory):

	resource_path = "res://gd_core_items/Exclusive/Laboratory.gd"

	def _init_fields(self):
		super()._init_fields()
		self._phase = 0
		self.typesDict = {}
		self.fluidTween = None
		self.fluid = None
		self.fluidMat = None

	@property
	def phase(self):
		return self._phase
	@phase.setter
	def phase(self, v):
		self._phase = int(v)
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

		for param in (self.params if self.params.__class__ is list else _iter(self.params)):
			descr = self.insertParameter(descr, _strv("p_", param), self.params[param], 
				_H_1, False, wrapInColor)

		return self.insertParameters(descr, wrapInColor)


	def onPreCombatStart(self):
		self.setState(0)
		self.typesDict = self.countTypes(self.getAffectedItems())


	def trigger(self):
		self.setState(self.phase + 1)

		super().trigger()





	def canAffect(self, item):
		return (item.hasType(_H_2) or 
				item.hasType(_H_3) or 
				item.hasType(_H_4) or 
				item.hasType(_H_5) or 
				item.isClassItem(_H_6))


	def doCooldownEffect(self):
		if self.phase == 1:
			if self.character().getLucky() >= self.params["luckt"]:
				event = self.useLucky(self.params["luckt"])
				numFire = self.typesDict[_H_2]
				self.giveHeat(self.params["heat"] + numFire * self.params["heat_bonus"], event)

		elif self.phase == 2:
			if self.character().getHeat() >= self.params["heatt"]:
				event = self.useHeat(self.params["heatt"])
				numNature = self.typesDict[_H_3]
				self.giveSpikes(self.params["spikes"] + numNature * self.params["spikes_bonus"], event)

		elif self.phase == 3:
			if self.character().getSpikes() >= self.params["spikest"]:
				event = self.useSpikes(self.params["spikest"])
				numHoly = self.typesDict[_H_4]
				self.giveRegeneration(self.params["regen"] + numHoly * self.params["regen_bonus"], event)

		elif self.phase == 4:
			if self.character().getRegeneration() >= self.params["regent"]:
				event = self.useRegeneration(self.params["regent"])
				numVamp = self.typesDict[_H_5]
				self.giveVampirism(self.params["vampirism"] + numVamp * self.params["vamp_bonus"], event)

		elif self.phase == 5:
			if self.character().getVampirism() >= self.params["vampt"]:
				event = self.useVampirism(self.params["vampt"])
				numEngineer = 0
				for item in _iter(self.getAffectedItems()):
					if item.isClassItem(_H_6):
						numEngineer += 1
				self.giveEmpower(self.params["empower"] + numEngineer * self.params["empower_bonus"], event)

		if self.phase == 5:
			self.onAfterEffectFinished()
		else:
			self.activate()


	def onStateChanged(self, _phase):
		_phase = int(_phase)
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


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").StatModified.No
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
try:
	_H_2 = _R.C("CoreConst").Type.Fire
except AttributeError as _he:
	_H_2 = _HoistPending(_he)
try:
	_H_3 = _R.C("CoreConst").Type.Nature
except AttributeError as _he:
	_H_3 = _HoistPending(_he)
try:
	_H_4 = _R.C("CoreConst").Type.Holy
except AttributeError as _he:
	_H_4 = _HoistPending(_he)
try:
	_H_5 = _R.C("CoreConst").Type.Vampiric
except AttributeError as _he:
	_H_5 = _HoistPending(_he)
try:
	_H_6 = _R.C("CoreConst").Classes_Full.Engineer
except AttributeError as _he:
	_H_6 = _HoistPending(_he)
