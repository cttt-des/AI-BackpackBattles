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
if "_base_cls_Gems__CorruptedCrystal" not in globals():
	from .Gem import Gem as _base_cls_Gems__CorruptedCrystal





class Gems__CorruptedCrystal(_base_cls_Gems__CorruptedCrystal):

	resource_path = "res://gd_core_items/Gems/CorruptedCrystal.gd"

	def _init_fields(self):
		super()._init_fields()
		self.damageBonusApplied = False
		self._debuffsInflicted = 0
		self.weaponParticles = None
		self.healthThreshold = None
		self.damageFactor = None
		self.debuffsNeeded = None
		self.blockGain = None

	@property
	def debuffsInflicted(self):
		return self._debuffsInflicted
	@debuffsInflicted.setter
	def debuffsInflicted(self, v):
		self._debuffsInflicted = int(v)
	gemColor = Color(0.938676, 0.24128, 0.988281)

	def prepareWeapon(self):
		self.damageBonusApplied = False
		self.connectForCombat(self.opponent(), "character_damaged", "onOpponentDamaged")


	def onOpponentDamaged(self, _healthChange, _event):
		if self.opponent().getRelativeHealth() < self.healthThreshold:
			if not self.damageBonusApplied:
				self.damageBonusApplied = True
				self.getItem().addBonusDamageFactor(self.damageFactor)
		elif self.damageBonusApplied:
			self.damageBonusApplied = False
			self.getItem().reduceBonusDamageFactor(self.damageFactor)


	def combatEndWeapon(self):
		pass


	def prepareArmor(self):
		self.debuffsInflicted = 0
		self.connectToOpponentDebuffs("onOpponentDebuffsChanged")


	def onOpponentDebuffsChanged(self, amount, event):
		if amount > 0:
			if isinstance(event.getOrigin(), _H_1) and event.getOrigin().character() == self.character():
				self.debuffsInflicted += amount
				activations = int(_div(self.debuffsInflicted, self.debuffsNeeded))
				self.debuffsInflicted %= int(self.debuffsNeeded)
				if activations > 0:
					self.giveBlock(self.getGemPower() * self.blockGain * activations, True, event)
					self.miniActivate()









	def doCooldownEffect(self):
		self.opponent().addFatigueDamage(1)
		self.opponent().takeFatigueDamage(self)
		self.activate()


	def onHotSwapHoverWithGemEnd(self):
		pass


	def _readyInit(self):
		_div__loc = _div
		super()._readyInit()
		self.healthThreshold = _div__loc(self.getP1(), 100.0) - 0.0001
		self.damageFactor = _div__loc(self.getP2(), 100.0)
		self.debuffsNeeded = self.getP3()
		self.blockGain = self.getP4()


_R.reg("res://gd_core_items/Gems/CorruptedCrystal.gd", Gems__CorruptedCrystal)
_R.reg("CorruptedCrystal", Gems__CorruptedCrystal)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
_H_1 = _R.C("Item")
