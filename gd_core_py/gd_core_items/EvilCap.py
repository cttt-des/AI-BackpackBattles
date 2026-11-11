# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import (  # noqa: F401

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
	from .._rt import GodotObject  # 纯 py 补绑；编译态 pxd 已预绑

from .. import _registry as _R
if "_base_cls_EvilCap_2" not in globals():
	from .Item import Item_2 as _base_cls_EvilCap_2





class EvilCap_2(_base_cls_EvilCap_2):

	resource_path = "res://gd_core_items/EvilCap.gd"

	def _init_fields(self):
		super()._init_fields()
		self.nullifyApplied = False
		self.buffsActive = 0
		self.buffTimer = None
		self.activationParticles = None
		self.damReduction = None


	def onPrepare(self):
		self.opponent().reduceHealingEfficiency(_div(self.getP3(), 100.0))
		self.nullifyApplied = False


	def onPreCombatStart(self):
		self.character().changeDamageResistance(self.damReduction)


	def onCombatStart(self):
		if not self.nullifyApplied:
			self.nullifyApplied = True
			self.opponent().changeBuffNullifyChances(self.getChance())

		self.buffTimer.start(self.getP_m("dur"))
		self.buffsActive += 1
		self.setState(self.buffsActive)
		self.activate()


	def buffEnded(self):
		self.character().changeDamageResistance( - self.damReduction)
		self.buffsActive -= 1
		self.setState(self.buffsActive)


	def onCombatEnd(self):
		self.buffTimer.stop()


	def onShopEntered(self):
		self.buffsActive = 0
		self.onStateChanged(self.buffsActive)


	def onStateChanged(self, _buffsActive):
		if _buffsActive > 0:
			pass
		else:
			pass

	def _readyInit(self):
		super()._readyInit()
		self.buffTimer = self.newItemTimer("BuffTimer", "buffEnded", True)
		self.damReduction = self.getP1()


_R.reg("res://gd_core_items/EvilCap.gd", EvilCap_2)
_R.reg("EvilCap", EvilCap_2)
