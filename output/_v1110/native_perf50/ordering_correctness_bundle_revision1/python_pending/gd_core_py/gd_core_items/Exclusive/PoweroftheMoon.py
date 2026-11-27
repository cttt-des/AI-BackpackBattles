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
if "_base_cls_Exclusive__PoweroftheMoon" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__PoweroftheMoon





class Exclusive__PoweroftheMoon(_base_cls_Exclusive__PoweroftheMoon):

	resource_path = "res://gd_core_items/Exclusive/PoweroftheMoon.gd"

	def _init_fields(self):
		super()._init_fields()
		self.boosted = 0
		self.moonArmorDescriptor = None
		self.moonShieldDescriptor = None
		self.manaOrbDescriptor = None
		self.timeAdvance = None
		self.blind = None


	def canAffect(self, item):
		return item.isA(self.moonArmorDescriptor) or item.isA(self.moonShieldDescriptor)


	def getData(self):
		return self.boosted


	def setData(self, data):
		if data != None:
			self.boosted = data


	def onBought(self):
		self.boosted = 1


	def onPostCombatStart(self):
		# ★ np25w_f10：此处必须是**死调用**。受控神谕语料的真值：oracle_bootstrap.gd:108
		#   把 Main/Combat 搭成裸 Node2D（不挂 Core/Combat.gd）→ 原版
		#   `Game.combatSceneNode.advanceTime(timeAdvance)` 在神谕 harness 内
		#   "Nonexistent function" 脚本错误中断 = 无操作 → 语料全库疲劳起点恒为
		#   CombatTimer.start() 的 FATIGUE_TIME-3=14s（首笔疲劳伤 + fatigue_start
		#   信号在 17.0167=+3s tick+1tick；514 场 >17s 语料全数实证、0 提前例）。
		#   gd 若真推进时钟（CoreCombat.advanceTime），PotM time=6 ×2 件把疲劳
		#   提前到 5.0333（run741_r9/run926_r11 实证=本面首分歧）。镜像死调用语义：
		#   不推进、不改 time_advance。CoreCombat.advanceTime 本体保留（无其他调用点）。
		pass


	def onPrepare(self):
		self.connectForCombat(self.ctx.combat, "fatigue_start", "onFatigueStarted")

		for item in _iter(self.getAffectedItems()):
			if item.isA(self.moonArmorDescriptor):

				self.connectForCombat(item, "activated", "onMoonArmorActivated")
			else:

				self.connectForCombat(item, "activated", "onMoonShiedActivated")


	def onFatigueStarted(self):
		bonusHealth = _div(self.getP_m('maxhealth'), 100.0) * self.character().getMaxHealth()
		self.giveMaxHealth(bonusHealth)
		self.activate()


	def onMoonArmorActivated(self, event):
		self.inflictBlind(self.blind, event)


	def onMoonShiedActivated(self, event):
		self.giveReflectStacks(1)


	def onItemRoll(self, descr):
		pass

	def onItemRolled(self, descr):
		if descr == self.manaOrbDescriptor:
			self.boosted -= 1

	def _readyInit(self):
		super()._readyInit()
		self.moonArmorDescriptor = self.ctx.item_book.getDescriptor("Moon Armor")
		self.moonShieldDescriptor = self.ctx.item_book.getDescriptor("Moon Shield")
		self.manaOrbDescriptor = self.ctx.item_book.getDescriptor("Mana Orb")
		self.timeAdvance = self.getP("time")
		self.blind = int(self.getP("blind"))


_R.reg("res://gd_core_items/Exclusive/PoweroftheMoon.gd", Exclusive__PoweroftheMoon)
_R.reg("PoweroftheMoon", Exclusive__PoweroftheMoon)
