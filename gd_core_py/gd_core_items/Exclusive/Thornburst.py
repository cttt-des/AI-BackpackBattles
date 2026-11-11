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
if "_base_cls_Exclusive__Thornburst" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__Thornburst





class Exclusive__Thornburst(_base_cls_Exclusive__Thornburst):

	resource_path = "res://gd_core_items/Exclusive/Thornburst.gd"

	def _init_fields(self):
		super()._init_fields()
		self._activationsLeft = 0
		self.spikes = None
		self.uses = None
		self.spikeSpeed = None

	@property
	def activationsLeft(self):
		return self._activationsLeft
	@activationsLeft.setter
	def activationsLeft(self, v):
		self._activationsLeft = int(v)

	def onPrepare(self):
		self.activationsLeft = self.uses
		self.connectForCombat(self.character(), "character_spikes_changed", "onSpikesChanged")


	def doCooldownEffect(self):

		self.stun(self.getP_m("dur_stun"))
		self.giveSpikes(self.spikes)
		self.activationsLeft -= 1
		if self.activationsLeft == 0:
			self.onAfterEffectFinished()
		else:
			self.activate()


	def onSpikesChanged(self, amount, event):
		self.addSpeed(self.spikeSpeed * amount)

	def _readyInit(self):
		super()._readyInit()
		self.spikes = int(self.getP("spikes"))
		self.uses = int(self.getP("max"))
		self.spikeSpeed = _div(self.getP('speed'), 100.0)


_R.reg("res://gd_core_items/Exclusive/Thornburst.gd", Exclusive__Thornburst)
_R.reg("Thornburst", Exclusive__Thornburst)
