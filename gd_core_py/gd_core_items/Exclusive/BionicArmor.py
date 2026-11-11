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
if "_base_cls_Exclusive__BionicArmor" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__BionicArmor





class Exclusive__BionicArmor(_base_cls_Exclusive__BionicArmor):

	resource_path = "res://gd_core_items/Exclusive/BionicArmor.gd"

	def _init_fields(self):
		super()._init_fields()
		self._blockHealthAcc = 0
		self.staminaRegenMalus = None
		self.healthThreshold = None
		self.maxStamina = None
		self.staminaThreshold = None
		self.staminaUsed = None
		self.empower = None
		self.block2 = None

	@property
	def blockHealthAcc(self):
		return self._blockHealthAcc
	@blockHealthAcc.setter
	def blockHealthAcc(self, v):
		self._blockHealthAcc = int(v)

	def onPrepare(self):
		self.blockHealthAcc = 0
		baseStaminaRegen = self.character().baseStaminaRegen
		self.character().giveStaminaRegeneration(self.staminaRegenMalus * baseStaminaRegen)

		self.connectForCombat(self.character(), "character_healed", "onHealOrBlockChanged")
		self.connectForCombat(self.character(), "character_block_changed", "onHealOrBlockChanged")


	def onCombatStart(self):
		self.giveBlock()
		self.activate()


	def onHealOrBlockChanged(self, amount, event):
		if amount > 0:
			self.blockHealthAcc += amount
			numProccs = int(_div(self.blockHealthAcc, self.healthThreshold))
			if numProccs > 0:
				self.blockHealthAcc -= numProccs * self.healthThreshold
				self.giveMaxStaminaTemporary(self.maxStamina * numProccs)
				self.miniActivate()


	def doCooldownEffect(self):
		if self.character().getCurrentStamina() < self.staminaThreshold:
			self.giveBlock(self.block2)
		else:
			self.useStamina(self.staminaUsed)
			self.giveEmpower(self.empower)
		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.staminaRegenMalus = _div(-self.getP('staminaregen'), 100.0)
		self.healthThreshold = self.getP("healtht")
		self.maxStamina = self.getP("maxstamina")
		self.staminaThreshold = self.getP("staminat1")
		self.staminaUsed = self.getP("staminat2")
		self.empower = int(self.getP("empower"))
		self.block2 = int(self.getP("block"))


_R.reg("res://gd_core_items/Exclusive/BionicArmor.gd", Exclusive__BionicArmor)
_R.reg("BionicArmor", Exclusive__BionicArmor)
