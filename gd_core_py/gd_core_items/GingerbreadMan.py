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
if "_base_cls_GingerbreadMan_2" not in globals():
	from .Food import Food_2 as _base_cls_GingerbreadMan_2





class GingerbreadMan_2(_base_cls_GingerbreadMan_2):

	resource_path = "res://gd_core_items/GingerbreadMan.gd"

	def _init_fields(self):
		super()._init_fields()
		self._luckNeeded = 0
		self._heatNeeded = 0
		self._manaNeeded = 0

	@property
	def luckNeeded(self):
		return self._luckNeeded
	@luckNeeded.setter
	def luckNeeded(self, v):
		self._luckNeeded = int(v)
	@property
	def heatNeeded(self):
		return self._heatNeeded
	@heatNeeded.setter
	def heatNeeded(self, v):
		self._heatNeeded = int(v)
	@property
	def manaNeeded(self):
		return self._manaNeeded
	@manaNeeded.setter
	def manaNeeded(self, v):
		self._manaNeeded = int(v)

	def onCombatStart(self):
		self.giveMaxHealth()
		self.activate()


	def doCooldownEffect(self):
		if self.character().getLucky() >= self.luckNeeded:
			if self.character().getHeat() >= self.heatNeeded:
				if self.character().getMana() >= self.manaNeeded:

					self.ctx.bus.setLoggingMode(self.ctx.bus.LoggingMode.Delayed)
					self.useLucky(self.luckNeeded)
					self.useHeat(self.heatNeeded)
					self.useMana(self.manaNeeded)
					self.giveEmpower(self.getP5())
					self.giveRegeneration(self.getP6())
					self.ctx.bus.flushLoggingQueue()

					self.giveMaxHealth(self.getP_m("maxhealth_use"))

		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.luckNeeded = self.getP2()
		self.heatNeeded = self.getP3()
		self.manaNeeded = self.getP4()


_R.reg("res://gd_core_items/GingerbreadMan.gd", GingerbreadMan_2)
_R.reg("GingerbreadMan", GingerbreadMan_2)
