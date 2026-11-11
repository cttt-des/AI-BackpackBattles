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
if "_base_cls_Exclusive__TigerRune" not in globals():
	from ..Gems.Gem import Gem as _base_cls_Exclusive__TigerRune





class Exclusive__TigerRune(_base_cls_Exclusive__TigerRune):

	resource_path = "res://gd_core_items/Exclusive/TigerRune.gd"

	def _init_fields(self):
		super()._init_fields()
		self.buffCounter = 0
		self.vampChance = None
		self.vampirism = None
		self.buffsNeeded = None
		self.blockForBuffs = None

	gemColor = Color(3, 2.501563, 0.8)

	def canModifyChance(self):
		return True


	def prepareInventory(self):
		for item in _iter(self.inventory.getItemsAndGems()):
			item.changeAmplificiationChancePercent_allBuffs(self.getChance())


	def prepareWeapon(self):
		self.connectForCombat(self.socket.getItem(), "pre_deal_damage_late", "preAttack")


	def preAttack(self, damageRes):
		if damageRes.hasHit() and self.rollChance(self.vampChance):
			self.giveVampirism(self.vampirism)
			self.miniActivate()


	def prepareArmor(self):
		self.buffCounter = 0
		self.connectToCharacterBuffs("onBuffsChanged")


	def onBuffsChanged(self, amount, event):
		if amount > 0:
			self.buffCounter += amount
			relBuffs = _div(self.buffCounter, self.buffsNeeded)
			block = relBuffs * self.blockForBuffs
			self.buffCounter %= self.buffsNeeded
			if block > 0:
				self.giveBlock(self.getGemPower() * block, event)
				self.showCooldownSmooth(relBuffs, True)
			else:
				self.showCooldownSmooth(relBuffs, False)


	def onHotSwapHoverWithGemEnd(self):
		pass

	def _readyInit(self):
		super()._readyInit()
		self.vampChance = self.getP("chance_vamp")
		self.vampirism = int(self.getP("vampirism"))
		self.buffsNeeded = int(self.getP("buffs"))
		self.blockForBuffs = int(self.getP("block"))


_R.reg("res://gd_core_items/Exclusive/TigerRune.gd", Exclusive__TigerRune)
_R.reg("TigerRune", Exclusive__TigerRune)
