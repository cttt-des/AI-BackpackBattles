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
if "_base_cls_Exclusive__ElephantRune" not in globals():
	from ..Gems.Gem import Gem as _base_cls_Exclusive__ElephantRune





class Exclusive__ElephantRune(_base_cls_Exclusive__ElephantRune):

	resource_path = "res://gd_core_items/Exclusive/ElephantRune.gd"

	def _init_fields(self):
		super()._init_fields()
		self.stunReadyTime = 0.0
		self.debuffResistChance = 0.0
		self.debuffResistTimer = None
		self.stunCd = None

	gemColor = Color(0.466766, 0.625994, 0.742188)

	def prepareWeapon(self):
		self.connectForCombat(self.getItem(), "attacked", "onAttack")


	def onAttack(self, damageRes):
		if damageRes.hasHit() and self.rollChance():
			if self.ctx.time >= self.stunReadyTime:
				self.stunReadyTime = self.ctx.time + self.stunCd
				self.stun(self.getP_m("dur_stun"), damageRes.event)
				self.miniActivate()


	def prepareArmor(self):
		self.debuffResistChance = self.getGemPower() * self.getChance2()
		self.character().changeDebuffResistChances(self.debuffResistChance)


	def combatStartArmor(self):
		self.debuffResistTimer.start(self.getP_m("dur_resist"))


	def removeDebuffResistance(self):
		self.character().changeDebuffResistChances( - self.debuffResistChance)


	def combatEndArmor(self):
		self.debuffResistTimer.stop()



	def hasCooldown(self):
		return False


	def combatStartInventory(self):
		self.giveMaxHealth()
		self.consume()


	def onHotSwapHoverWithGemEnd(self):
		pass


	def hasInventoryDuration(self):
		return False

	def _readyInit(self):
		super()._readyInit()
		self.debuffResistTimer = self.newItemTimer("DebuffResistTimer", "removeDebuffResistance", False)
		self.stunCd = self.getBaseCooldown()


_R.reg("res://gd_core_items/Exclusive/ElephantRune.gd", Exclusive__ElephantRune)
_R.reg("ElephantRune", Exclusive__ElephantRune)
