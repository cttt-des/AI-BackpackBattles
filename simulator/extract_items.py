# -*- coding: utf-8 -*-
"""extract_items.py — 从解包 GDScript 提取物品行为到行为 DSL

设计：GDScript 的控制流(if/for/return/elif)本就是 Python 语法，差异仅在：
  * 隐式 self. 前缀
  * 方法命名风格 addCritChancePercent -> add_crit_chance_percent
  * getP1() -> get_p(1) / getP_m("x") / getChance() / getGemPower()
  * 大量视觉调用(preload/$/ObjectPool/animation/connector/fluid/Color/Vector2)可剥离

做法：把每个 Item 脚本的方法体转成调用引擎 API 的 Python 函数，存入
battle_items.json 的 behavior.methods[NAME] = <python source>。
无法编译的方法保留原文到 behavior.methods_raw[NAME]，引擎跳过(不崩溃)。
"""
from __future__ import annotations
import os
import re
import json
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ITEMS_SRC = os.path.join(ROOT, "decompiled_full", "Items")
DB_PATH = os.path.join(ROOT, "assets", "battle_items.json")

# ---------- 方法重命名 (GDScript -> 引擎 API) ----------
METHOD_RENAME = {
    "heal": "heal", "giveStamina": "give_stamina", "activate": "visual_activate",
    "miniActivate": "visual_activate", "playActivationAnimation": "visual_activate",
    "triggerPotion": "trigger_potion", "visualActivate": "visual_activate",
    "attack": "attack", "dealDamage": "deal_damage", "dealEffectDamage": "deal_effect_damage",
    "inflictRandomDebuffs": "inflict_random_debuffs",
    "cleanseRandomDebuffs": "cleanse_random_debuffs",
    "removeRandomBuffs": "remove_random_buffs",
    "inflictPoison": "inflict_poison", "inflictDebuff": "inflict_debuff",
    "giveRegeneration": "give_regeneration", "giveBlock": "give_block",
    "giveMaxHealth": "give_max_health", "giveStaminaToAll": "give_stamina_to_all",
    "addCritChancePercent": "add_crit_chance_percent", "addAccuracy": "add_accuracy",
    "addBonusDamageFactor": "add_bonus_damage_factor",
    "reduceBonusDamageFactor": "reduce_bonus_damage_factor",
    "addDamage": "add_bonus_damage",
    "addMaxDamage": "add_max_damage", "reduceMaxDamage": "reduce_max_damage",
    "addBonusDamage": "add_bonus_damage", "reduceBonusDamage": "reduce_bonus_damage",
    "addMaxHealth": "add_max_health", "reduceMaxHealth": "reduce_max_health",
    "cleansePoison": "cleanse_poison", "cleanseDebuff": "cleanse_debuff",
    "cleanseAllDebuffs": "cleanse_all_debuffs",
    "gainStacks": "gain_stacks", "gainStacksTemporary": "gain_stacks_temporary",
    "loseStacks": "lose_stacks", "addStacks": "gain_stacks",
    "connectForCombat": "connect_for_combat",
    "connectToOpponentDebuffs": "connect_to_opponent_debuffs",
    "rollChance": "roll_chance", "getGemPower": "get_gem_power",
    "getAffectedItems": "get_affected_items", "getAffectedItemsNoCache": "get_affected_items",
    "getAffectedItems_nocache": "get_affected_items_nocache",
    "getRelativeHealth": "get_relative_health",
    "addFatigueDamage": "add_fatigue_damage", "takeFatigueDamage": "take_fatigue_damage",
    "changeResistChance": "change_resist_chance",
    "removeRandomBuffs": "remove_random_buffs",
    "reduceHealingEfficiency": "reduce_healing_efficiency",
    "addDamagePercent": "add_damage_percent", "addStaminaFactor": "add_stamina_factor",
    "addSpeed": "add_speed", "reduceSpeed": "reduce_speed",
    "addCritSeverity": "add_crit_severity", "giveCritTokens": "give_crit_tokens",
    "addMaxHealthPercent": "add_max_health_percent",
    "consumePotion": "consume_potion", "consume": "consume",
    "opponent": "opponent", "character": "character_",
    "getCharacter": "character_", "getOpponent": "opponent",
    "getItems": "get_items", "getFirstAffectedItem": "get_first_affected_item",
    "getNumCells": "get_num_cells", "getNumAffectedItems": "get_num_affected_items",
    "getP1": "_get_p1", "getP2": "_get_p2", "getP3": "_get_p3", "getP4": "_get_p4",
    "getP5": "_get_p5", "getP6": "_get_p6",
    "getP_m": "get_p_m", "getChance": "get_chance", "getChance2": "get_chance2",
    "getStamina": "get_stamina_cost", "getBlock": "get_block",
    "getCooldown": "get_cooldown", "getSpeed": "get_speed",
    "isEmpty": "is_empty", "isBag": "is_bag", "isWeapon": "is_weapon",
    "canAffect": "can_affect", "hasType": "has_type", "has_method": "has_method",
    "getP": "get_p", "socket": "socket",
    "useStamina": "use_stamina", "fillUpStamina": "fill_up_stamina",
    "addStamina": "give_stamina", "drainStamina": "drain_stamina",
    "stun": "stun", "curse": "curse", "addLucky": "add_lucky",
    "addMana": "add_mana", "addHeat": "add_heat", "addCold": "add_cold",
    "addPoison": "inflict_poison", "addVampirism": "add_vampirism",
    "addRegen": "give_regeneration", "addSpikes": "add_spikes",
    "addEmpower": "add_empower", "addDodgeChance": "add_dodge_chance",
    "addLifesteal": "add_lifesteal", "addCounterAttack": "add_counter_attack",
    "addInvulnerable": "add_invulnerable", "reflectDamage": "reflect_damage",
    "blockNextAttack": "block_next_attack", "duplicateItem": "duplicate_item",
    "fuse": "fuse", "setDamageMultiplier": "set_damage_multiplier",
    "addDamageMultiplier": "add_damage_multiplier",
    "hasHit": "has_hit", "hasMissed": "has_missed",
    "canDamage": "can_damage",
    "onAfterEffectFinished": "visual_activate",
    "onBeforeEffectFinished": "visual_activate",
    "changeVaryingDamage": "add_bonus_damage",
    "setState": "visual_activate",
    "onStateChanged": "visual_activate",
    "removeVampirism": "remove_vampirism", "loseVampirism": "lose_vampirism",
    "useVampirism": "use_vampirism", "loseSpikes": "lose_spikes", "selfInflictPoison": "self_inflict_poison",
    "selfInflictBlind": "self_inflict_blind",
    "inflictBlind": "inflict_blind", "cleanseBlind": "cleanse_blind",
    "giveMana_capped": "give_mana_capped", "tryUseMana": "try_use_mana",
    "stealLife": "steal_life", "emitCharge": "emit_charge",
    "changePoisonCritChancePercent": "change_poison_crit_chance_percent",
    "getNumAffectedInside": "get_num_affected_inside",
    "getAllInInventoryOfType": "get_all_in_inventory_of_type",
    "countTypes": "count_types", "updateShaderRotation": "visual_activate",
    # 引擎基类方法 (Item/Character) —— 此前漏映射导致驼峰名调用失败
    "hasCooldown": "has_cooldown", "giveStacksTemporary": "give_stacks_temporary",
    "rollChance2": "roll_chance2", "isVulnerable": "is_vulnerable",
    "giveLeastBuffs": "give_least_buffs", "removeMana": "remove_mana",
    "getMostStacks": "get_most_stacks",
    "isCooldownActive": "is_cooldown_active",
    "sendCharge": "send_charge", "chargeReceived": "charge_received",
    "changeAllDebuffsReflectChance": "change_all_debuffs_reflect_chance",
    "giveStamina_capped": "give_stamina_capped",
    "giveAllBuffs": "give_all_buffs", "giveRandomBuffs": "give_random_buffs",
    "stealRandomBuff": "steal_random_buff", "useRandomBuffs": "use_random_buffs",
    "giveLeastBuffs": "give_least_buffs", "giveBuff": "give_buff",
    "loseBuff": "lose_buff", "giveBuffTemporary": "give_buff_temporary",
    "inflictDebuffTemporary": "inflict_debuff_temporary",
    "cleanseAllDebuffs": "cleanse_all_debuffs",
    "giveRegenerationTemporary": "give_regeneration_temporary",
    "giveBlockTemporary": "give_block_temporary", "giveBlockPermanent": "give_block",
    "giveVampirismTemporary": "give_vampirism_temporary",
    "giveSpikesTemporary": "give_spikes_temporary",
    "addTempMaxHealth": "add_max_health", "changeMaxHealth": "change_max_health",
    "reduceMaxHealth": "reduce_max_health", "giveMaxHealth": "give_max_health",
    "addBonusMaxHealth": "add_max_health", "reduceBonusMaxHealth": "reduce_max_health",
    "addHealingEfficiency": "add_healing_efficiency",
    "reduceHealingEfficiency": "reduce_healing_efficiency",
    "changeDamageResistance": "change_damage_resistance",
    "changeDamageReduction": "change_damage_reduction",
    "changeDodgeStacks": "change_dodge_stacks",
    "changeCritResistance": "change_crit_resistance",
    "changeStunResistance": "change_stun_resistance",
    "gainCritResistStacks": "gain_crit_resist_stacks",
    "gainCritTokens": "gain_crit_tokens", "giveCritTokens": "give_crit_tokens",
    "giveUnhealing": "give_unhealing", "reduceUnhealing": "reduce_unhealing",
    "changeEmpowerDamage": "change_empower_damage",
    "changeMeleeSpikesLimit": "change_melee_spikes_limit",
    "changeRangedSpikesLimit": "change_ranged_spikes_limit",
    "changeEffectSpikesLimit": "change_effect_spikes_limit",
    "changeMeleeVampirismLimit": "change_melee_vampirism_limit",
    "changeRangedVampirismLimit": "change_ranged_vampirism_limit",
    "changeEffectVampirismLimit": "change_effect_vampirism_limit",
    "makeInvulnerable": "make_invulnerable", "invulnerabilityEnded": "invulnerability_ended",
    "giveInvulnerable": "make_invulnerable",
    "changeTypedDamageFactor": "change_typed_damage_factor",
    "changeEffectDamageFactor": "change_effect_damage_factor",
    "giveLifesteal": "add_lifesteal", "giveVampirismAll": "add_vampirism_all",
    "addDamageToAll": "add_damage_to_all", "giveCritChanceToAll": "give_crit_chance_to_all",
    "giveStaminaToAll": "give_stamina_to_all",
    "changeDebuffResistStacks": "change_debuff_resist_stacks",
    "changeDebuffReflectStacks": "change_debuff_reflect_stacks",
    "changeBuffProtectStacks": "change_buff_protect_stacks",
    "changeResistChance": "change_resist_chance",
    "changeReflectChance": "change_reflect_chance",
    "changeDebuffResistChances": "change_debuff_resist_chances",
    "changeDebuffReflectChances": "change_debuff_reflect_chances",
    "changeBuffNullifyChances": "change_buff_nullify_chances",
    "addBuffPower": "give_buff_power",
    "changeAmplificationChancePercent": "change_amplification_chance_percent",
    "advanceCooldownPercent": "advance_cooldown_percent",
    "advanceCooldownSeconds": "advance_cooldown_seconds",
    "setBaseCooldown": "set_base_cooldown", "resetBaseCooldown": "reset_base_cooldown",
    "giveDoubleActivationChance": "give_double_activation_chance",
    "giveDoubleAttackEffectChance": "give_double_attack_effect_chance",
    "getOpponent": "opponent", "getCharacter": "character",
    "getStaminaRegeneration": "get_stamina_regeneration",
    "getCurrentStamina": "get_current_stamina", "getMaxStamina": "get_max_stamina",
    "getMaxHealth": "get_max_health", "getCurrentHealth": "get_current_health",
    "getCritChancePercent": "get_crit_chance_percent",
    "getCritSeverity": "get_crit_severity",
    "getModifiedCooldown": "get_modified_cooldown",
    "getTypedDamageFactor": "get_typed_damage_factor",
    "canMiss": "can_miss", "isAttack": "is_attack",
    "getItem": "get_item", "socket": "get_socket",
    "connectToCharacterBuffs": "connect_to_character_buffs",
    "connectToCharacterBuff": "connect_to_character_buffs",
    "getShopChance": "get_shop_chance",
    "giveMostBuffs": "give_most_buffs",
    "getAffectedItemsInside": "get_affected_items_inside",
    "getNumAffected_type": "get_num_affected_type",
    "getAllInInventory": "get_all_in_inventory",
    "getAllOfTypeInInventory": "get_all_of_type_in_inventory",
    "getItemsInSockets": "get_items_in_sockets",
    "doCooldownEffect": "do_cooldown_effect",
    # ---- Character 方法重命名（behavior 里以 GDScript 名调用） ----
    "getMana": "get_mana", "getVampirism": "get_vampirism",
    "getLucky": "get_lucky", "getBlind": "get_blind", "getCold": "get_cold",
    "getHeat": "get_heat", "getEmpower": "get_empower",
    "getSpikes": "get_spikes", "getBlock": "get_block",
    "getRegeneration": "get_regeneration", "getPoison": "get_poison",
    "getStacks": "get_stacks", "getRelativeHealth": "get_relative_health",
    "loseHealth": "lose_health", "loseStamina": "lose_stamina",
    "getStaminaRegeneration": "get_stamina_regeneration",
    "getCurrentHealth": "get_current_health", "getMaxHealth": "get_max_health",
    "getCurrentStamina": "get_current_stamina", "getMaxStamina": "get_max_stamina",
    "setMaxStamina": "set_max_stamina", "setMaxHealth": "set_max_health",
    "giveMaxHealth": "give_max_health", "changeMaxHealthTemporarily": "change_max_health_temporary",
    "changeMaxHealthTemporary": "change_max_health_temporary",
    "gainMaxStaminaTemporary": "gain_max_stamina_temporary",
    "changeMaxStaminaTemporary": "gain_max_stamina_temporary",
    "gainStamina": "gain_stamina", "fillUpStamina": "fill_up_stamina",
    "useStamina": "use_stamina", "drainStamina": "drain_stamina",
    "gainStacks": "gain_stacks", "gainStacksTemporary": "gain_stacks_temporary",
    "loseStacks": "lose_stacks", "useStacks": "use_stacks",
    "gainBlock": "gain_block", "loseBlock": "lose_block", "useBlock": "use_block",
    "gainPoison": "gain_poison", "losePoison": "lose_poison",
    "gainRegeneration": "gain_regeneration", "gainVampirism": "gain_vampirism",
    "gainSpikes": "gain_spikes", "gainLucky": "gain_lucky",
    "gainBlind": "gain_blind", "gainMana": "gain_mana", "useMana": "use_mana",
    "tryUseMana": "try_use_mana", "gainEmpower": "gain_empower",
    "gainHeat": "gain_heat", "gainCold": "gain_cold",
    "changeDamageResistance": "change_damage_resistance",
    "changeDamageReduction": "change_damage_reduction",
    "changeDodgeStacks": "change_dodge_stacks",
    "changeCritResistance": "change_crit_resistance",
    "changeStunResistance": "change_stun_resistance",
    "gainCritResistStacks": "gain_crit_resist_stacks",
    "gainCritTokens": "gain_crit_tokens", "useCritToken": "use_crit_token",
    "getCritTokens": "get_crit_tokens",
    "giveUnhealing": "give_unhealing", "reduceUnhealing": "reduce_unhealing",
    "changeEmpowerDamage": "change_empower_damage",
    "changeMeleeSpikesLimit": "change_melee_spikes_limit",
    "changeRangedSpikesLimit": "change_ranged_spikes_limit",
    "changeEffectSpikesLimit": "change_effect_spikes_limit",
    "changeMeleeVampirismLimit": "change_melee_vampirism_limit",
    "changeRangedVampirismLimit": "change_ranged_vampirism_limit",
    "changeEffectVampirismLimit": "change_effect_vampirism_limit",
    "makeInvulnerable": "make_invulnerable",
    "changeTypedDamageFactor": "change_typed_damage_factor",
    "changeEffectDamageFactor": "change_effect_damage_factor",
    "getHealingEfficiency": "get_healing_efficiency",
    "changeHealingEfficiency": "add_healing_efficiency",
    "addHealingEfficiency": "add_healing_efficiency",
    "reduceHealingEfficiency": "reduce_healing_efficiency",
    "getRelativeHealth": "get_relative_health",
    "cleanseCold": "cleanse_cold",
    "getItem": "get_item", "getSocket": "get_socket",
    "getBonusFatigueDamage": "get_bonus_fatigue_damage",
    "addFatigueDamage": "add_fatigue_damage",
    "takeFatigueDamage": "take_fatigue_damage",
    "setStacks": "set_stacks", "getItems": "get_items",
    "useRegeneration": "use_regeneration",
    "changeStaminaFactor": "change_stamina_factor",
    "rollDoubleAttackEffect": "roll_double_attack_effect",
    "giveStaminaRegeneration": "give_stamina_regeneration",
    "changeDebuffProtectionChance": "change_debuff_protection_chance",
    "connectToOpponentBuffs": "connect_to_opponent_buffs",
    "isBattleRaging": "is_battle_raging",
    "changeRegenPower": "change_regen_power",
    "changeVampirismPower": "change_vampirism_power",
    "changeSpikesPower": "change_spikes_power",
    "changeManaPower": "change_mana_power",
    "changeEmpowerPower": "change_empower_power",
    "changeHeatPower": "change_heat_power",
    "changeColdPower": "change_cold_power",
    "changeLuckyPower": "change_lucky_power",
    "changeBlockPower": "change_block_power",
    "changePoisonPower": "change_poison_power",
    "changeBlindPower": "change_blind_power",
    "getNumAffected": "get_num_affected_items",
    "getPower": "get_gem_power",
    "changeCritChancePercent": "change_crit_chance_percent",
    "changeCritSeverity": "change_crit_severity",
    "changeDamagePercent": "change_damage_percent",
    "changeAccuracy": "change_accuracy",
    "changeCooldownPercent": "change_cooldown_percent",
    "changeCooldown": "change_cooldown",
    "reduceCooldownPercent": "reduce_cooldown_percent",
    "reduceCooldown": "reduce_cooldown",
    "changeItemDamagePercent": "change_item_damage_percent",
    "changeStaminaCost": "change_stamina_cost",
    "changeStaminaRegeneration": "change_stamina_regeneration",
    "changeMaxStamina": "change_max_stamina",
    "changeMaxHealth": "change_max_health",
    "giveDamageToAll": "add_damage_to_all",
    "giveDamagePercentToAll": "give_damage_percent_to_all",
    "giveSpeedToAll": "give_speed_to_all",
    "giveAccuracyToAll": "give_accuracy_to_all",
    "changeSpeed": "change_speed",
    "inflictCold": "inflict_cold", "selfInflictCold": "self_inflict_cold",
    "useHeat": "use_heat", "useLucky": "use_lucky",
    "pickRandomStacks": "pick_random_stacks",
    "getOrigin": "get_origin",
    "preHit": "pre_hit",
    "wasCriticalHit": "was_critical_hit",
    "getStunProtectChance": "get_stun_protect_chance",
    "giveReflectStacks": "give_reflect_stacks",
    "getCounterValue": "get_counter_value",
    "canAffect_global": "can_affect_global",
    "canBeEmpowered": "can_be_empowered",
    "countSocketedGems": "count_socketed_gems",
    "canApplyLifesteal": "can_apply_lifesteal",
    "onHit": "on_hit", "getBaseChance2": "get_base_chance2",
    "giveStacks": "give_stacks", "signalName": "signal_name",
    "drinkStrongDemonicFlask": "drink_strong_demonic_flask",
    "multiplyBuffsLimit": "multiply_buffs_limit",
    "stealBuffsFraction": "steal_buffs_fraction",
    "removeBuffsFraction": "remove_buffs_fraction",
    "deactivateCooldown": "deactivate_cooldown",
    "countItemsInAffectedCells_cached": "count_items_in_affected_cells_cached",
    "giveMaxStaminaTemporary": "give_max_stamina_temporary",
    "changeSpikesCritChancePercent": "change_spikes_crit_chance_percent",
    "isA": "is_a",
    "countSocketedGems": "count_socketed_gems",
    "hasTag": "has_tag",
    "changeAmplificiationChancePercent": "change_amplification_chance_percent",
    "changeAmplificiationChancePercent_allBuffs": "change_amplification_chance_percent_all",
    "inflictFatigueDamage": "inflict_fatigue_damage",
    "checkBlock": "check_block",
    "getDebuffStacks": "get_debuff_stacks",
    "connectToCharacterDebuffs": "connect_to_character_debuffs",
    "countAllInInventoryOfType": "count_all_in_inventory_of_type",
    "addBattleRageDuration": "add_battle_rage_duration",
    "getNumAffectedItems": "get_num_affected_items",
    "giveRandomBuff": "give_random_buff",
    "cleanseCold": "cleanse_cold",
    "getRarity": "get_rarity",
    "changeDamagePercent": "change_damage_percent",
    "changeBuffProtectionChance": "change_buff_protection_chance",
    "startBattleRage": "start_battle_rage",
    "getNumEmptyAffectedCells": "get_num_empty_affected_cells",
    "createAnimation": "visual_activate",
    "tryUseLucky": "try_use_lucky",
    "isTypeInInventory": "is_type_in_inventory",
    "useSpikes": "use_spikes",
    "addTempStamina": "add_temp_stamina",
    "changeTempStamina": "add_temp_stamina",
    "changeStaminaRegeneration": "change_stamina_regeneration",
    "giveCooldownPercentToAll": "give_cooldown_percent_to_all",
    "giveDamageToAll": "add_damage_to_all",
    "getTotalDamage": "get_total_damage",
    "getTotalHeal": "get_total_heal",
    "changeArmorDamageReduction": "change_armor_damage_reduction",
    "giveDoubleActivationChanceToAll": "give_double_activation_chance_to_all",
    "giveCritTokensToAll": "give_crit_tokens_to_all",
    "getItemsInside": "get_items_inside",
    "getNumDistinctAffectedItems": "get_num_distinct_affected_items",
    "removeBlock": "remove_block",
    "getGemsNoNull": "get_gems_no_null",
    "getBuffStacks": "get_buff_stacks",
    "gainsStack": "gains_stack",
    "randomizePosition": "visual_activate",
    "useMana": "use_mana",
    "giveVampirism": "add_vampirism", "giveLifesteal": "add_lifesteal",
    "giveMana": "add_mana", "giveEmpower": "add_empower",
    "giveHeat": "add_heat", "giveCold": "add_cold", "giveLucky": "add_lucky",
    "giveSpikes": "add_spikes", "giveRegen": "give_regeneration",
    "giveDamage": "add_bonus_damage", "giveMinDamage": "add_min_damage",
    "giveMaxDamage": "add_max_damage", "giveCritChance": "add_crit_chance_percent",
    "giveStaminaToAll": "give_stamina_to_all", "giveSpeed": "add_speed",
    "giveDoubleActivationChance": "give_double_activation_chance",
    "giveDoubleAttackEffectChance": "give_double_attack_effect_chance",
    "healthToBlock": "health_to_block", "convertStaminaToDamage": "convert_stamina_to_damage",
    "addMaxHealth": "add_max_health", "addMinDamage": "add_min_damage",
    "addBlock": "give_block", "addVampirismAll": "add_vampirism_all",
    "addStaminaToAll": "give_stamina_to_all",
}

# 视觉/非战斗调用：整行剥离
VISUAL_PREFIXES = (
    "preload(", "$", "ObjectPool", "Sound.", "EventBus", "animation",
    "connector", "fluid", "Color(", "Vector2(", "Vector3(", "Util.",
    "sprite", "modulate", "particle", "Particles", "drink(", "empty(",
    "fill(", "setState", "updateConnector", "getStarPosition", "resetGradient",
    "discard", "shopEntered", "makeGrabbable", "makeNonRigidBody", "makeRigidBody",
    "add_child", "remove_child", "set_physics_process", "set_process",
    "showCooldown", "scale =", "rotation =", "clickArea", "shadow",
    "bounce", "friction", "mass =", "gravity_scale", "linear_damp",
    "emit_signal", "connect(", "disconnect(", "call_deferred",
    "playAffectedPlacedAnimation", "$Icon", "$BottomCenter", "$ClickArea",
    "$CollisionShape", "$Lock", "$AnimationPlayer", "sockets", "lockAnimation",
    "dragParticles", "specificDragParticles", "progressMaterial", "initSockets",
    "initSpriteMaterial", "cacheCollisionCells", "initPhysicsMaterial",
    "averagedPosition", "updateShadow", "spawnRotationSparks", "previewCells",
    "play(", "stop(", "tween", "SceneTreeTween", "killTween", "Util.",
    "CraftingManager",
    ".start(", "buffTimer", "activationParticles", "light.", "hide(", "show(",
    "playActivationAnimation", "onAfterEffectFinished(", "gemAnimation",
    "particles", "Particles.", "dust", "shake", "flicker", "squish",
    "animate", "Ani", "flash(", "set_visible", "z_index", "modulate",
    "global_position", "global_rotation", "position =", "rotation =", "scale =",
    "faceDirection", "getStarPosition", "cellSize", "halfCellSize",
    "clickArea", "dragParticles", "specificDragParticles", "sockets",
    "lockAnimation", "initSockets", "progressMaterial", "initSpriteMaterial",
    "cacheCollisionCells", "initPhysicsMaterial", "updateShadow",
    "spawnRotationSparks", "previewCells", "progress", "setColor", "Color(",
    "material", "gradient", "levelModification", "foaminess", "scrollAmount",
    "self_modulate", "connector", "updateConnector", "resetGradient",
    "getAffectedCellsAfterRotate", "getAffectedPoints", "getAffectedCells",
)

# 已知全局/枚举(在物品战斗逻辑里一般用不到，但保留以免误删)
GLOBALS = {"Priority", "Game", "EventType", "Affected", "Type", "Item", "Character",
           "Buff", "Util", "Color", "Vector2", "Vector3", "RNG", "BalancedRng",
           "DamageResult", "DamageSource", "ObjectPool", "Sound", "EventBus",
           "INF", "PI", "TAU", "NAN"}

# 类级声明解析（实例变量名集合）
VAR_RE = re.compile(r'^(?:onready\s+var|export\s+var|var|const)\s+([A-Za-z_]\w*)\s*(?::\s*([A-Za-z_][\w\.]*)?)?\s*(?:=.*)?$')
EXTENDS_RE = re.compile(r'^extends\s+(\w+)')
FUNC_RE = re.compile(r'^func\s+([A-Za-z_]\w*)\s*\(([^)]*)\)\s*(?:->\s*\w+)?\s*:')

# GDScript 类型 -> Python 默认值
TYPE_DEFAULTS = {
    "Dictionary": "{}", "Array": "[]", "int": "0", "float": "0.0",
    "bool": "False", "String": "''", "Color": "None", "Vector2": "None",
}


def strip_type_hints(sig_args: str) -> str:
    """去掉参数类型标注与默认值里的类型，仅保留名字(默认用 None/null)。"""
    out = []
    for part in sig_args.split(","):
        part = part.strip()
        if not part:
            continue
        # name: Type = default  -> name=None
        m = re.match(r'([A-Za-z_]\w*)\s*(?::\s*[\w\.\s]+)?\s*(=\s*.+)?$', part)
        name = part.split(":")[0].split("=")[0].strip()
        out.append(name + "=None")
    return ", ".join(out)


def collect_instance_vars(lines):
    """只收集类级(缩进0)的 var/onready var/const。返回 (vars, onready, typed_defaults)。"""
    vars_ = set()
    onready = []  # (name, expr)
    typed_defaults = {}  # 无初始化器的变量: name -> 默认值代码
    i = 0
    n = len(lines)
    while i < n:
        ln = lines[i]
        i += 1
        stripped = ln.strip()
        ind = len(ln) - len(ln.lstrip(" \t"))
        if ind != 0:
            continue
        m = VAR_RE.match(stripped)
        if m:
            name = m.group(1)
            typ = m.group(2)
            vars_.add(name)
            eq = stripped.split("=", 1)
            if len(eq) != 2:
                typed_defaults[name] = TYPE_DEFAULTS.get(typ, "0")
                continue
            expr = eq[1].strip()
            if expr.startswith(("{", "[")) and not expr.endswith(("}", "]")) and "=" not in expr:
                # 多行 dict/list 字面量（onready/const/var，如 chargeCells = [Vector2(..), …）→ 收集到括号闭合
                depth = expr.count("{") + expr.count("[") - expr.count("}") - expr.count("]")
                parts = [expr]
                while depth > 0 and i < n:
                    cont = lines[i].strip()
                    i += 1
                    parts.append(cont)
                    depth += cont.count("{") + cont.count("[") - cont.count("}") - cont.count("]")
                if depth <= 0:
                    onready.append((name, " ".join(parts)))
                else:
                    typed_defaults[name] = "{}" if expr.startswith("{") else "[]"
            else:
                onready.append((name, expr))
    return vars_, onready, typed_defaults


def is_visual_line(line: str) -> bool:
    s = line.strip()
    if not s:
        return False
    if s.startswith("#"):
        return True
    # 控制流/结构行不算视觉
    if re.match(r'^(if|elif|else|for|while|return|match|break|continue|pass|var|func|and|or|not)\b', s):
        # 但 if 行里可能含视觉调用，交给后续；这里不整行剥
        return False
    for p in VISUAL_PREFIXES:
        if p in s:
            return True
    return False


def rename_method(name: str) -> str:
    return METHOD_RENAME.get(name, name)


def transform_expr_token(name: str) -> str:
    """裸标识符：若是已知 self 方法/实例变量 -> 加 _item. 前缀由调用方处理。"""
    return name


def _indent_level(raw: str, uses_tabs: bool) -> int:
    """返回行的缩进层级(以 4 空格为 1 级)。tab 文件按 tab 计，空格文件按 4 空格计。"""
    stripped = raw.lstrip(" \t")
    lead = raw[:len(raw) - len(stripped)]
    nt = lead.count("\t")
    ns = len(lead) - nt
    if uses_tabs:
        return nt
    return ns // 4


def transform_body(body_lines, instance_vars, sibling_methods=None):
    """把 GDScript 方法体转成 Python 源码字符串。返回 (body_py, local_var_names)。

    缩进处理：GDScript 源可能用 tab 或 4 空格缩进，统一按“相对层级”重排为 4 空格，
    避免 tab 被当成 1 字符导致 Python 缩进错位(此前导致大量方法编译失败、落入 methods_raw 被静默跳过)。
    """
    out = []
    local_vars = []   # 方法内 var 声明（提升防 UnboundLocalError）
    uses_tabs = any("\t" in raw for raw in body_lines)
    base_level = None
    paren_skip = 0  # >0: 处于被剥离的多行调用内部，续行需一并丢弃
    for raw in body_lines:
        if not raw.strip():
            out.append("")
            continue
        level = _indent_level(raw, uses_tabs)
        if base_level is None:
            base_level = level
        py_indent = max(0, level - base_level) * 4
        line = raw.strip()

        # 处于被剥离的多行调用内部：直接丢弃续行（修复“视觉/超类调用跨行导致续行悬空缩进”）
        if paren_skip > 0:
            paren_skip += line.count("(") - line.count(")")
            continue

        # 整行视觉剥离 / super 调用（若跨多行，续行一并丢弃）
        visual = is_visual_line(line)
        super_call = bool(re.match(r'^\.[A-Za-z_]\w*\(', line))
        if visual or super_call:
            out.append(" " * py_indent + ("pass  # visual" if visual else "pass  # super"))
            bal = line.count("(") - line.count(")")
            if bal > 0:
                paren_skip = bal
            continue

        # func 内部不能再有 func
        # 布尔/语法替换（先保护 !=，避免被 ! -> not 破坏成 "not ="）
        line = line.replace("!=", "\x00NE\x00")
        line = line.replace("&&", " and ").replace("||", " or ")
        line = line.replace("!", " not ")
        line = line.replace("\x00NE\x00", "!=")
        line = re.sub(r'\bnull\b', 'None', line)   # 词边界，避免误伤 nullify 等
        line = line.replace("true", "True").replace("false", "False")
        # var 声明 -> 普通赋值（兼容 var x / var x: Type / var x = y / var x: Type = y）
        mvar = re.match(r'^var\s+([A-Za-z_]\w*)\s*(?::\s*[\w\.\[\]]*)?\s*(?:=\s*(.+))?$', line)
        if mvar:
            local_vars.append(mvar.group(1))
            init = (mvar.group(2) or 'None').strip()
            line = f'{mvar.group(1)} = {init}'
        line = re.sub(r'^onready\s+var\s+([A-Za-z_]\w*)\s*(?::\s*[\w\.\[\]]*)?\s*(?:=\s*(.+))?$',
                      lambda m: f'{m.group(1)} = {(m.group(2) or "None").strip()}', line)
        # .empty() -> 真值（含方法调用形式 X().empty()）
        line = re.sub(r'not\s+([A-Za-z_]\w*)\.empty\(\)', r'\1', line)
        line = re.sub(r'([A-Za-z_]\w*)\.empty\(\)', r'(not \1)', line)
        line = re.sub(r'not\s+(\([^)]*\))\.empty\(\)', r'\1', line)
        line = re.sub(r'(\([^)]*\))\.empty\(\)', r'(not \1)', line)
        line = line.replace(".push_back(", ".append(")
        line = line.replace(".erase(", ".remove(")
        line = re.sub(r'([\w.]+)\.size\(\)', r'len(\1)', line)
        line = re.sub(r'(\w+\(\))\.size\(\)', r'len(\1)', line)   # X().size() -> len(X())
        # GDScript 数组方法 -> Python
        line = re.sub(r'\.pop_back\(\)', '.pop()', line)
        line = re.sub(r'\.pop_back\(', '.pop(', line)
        line = re.sub(r'\.duplicate\(\)', '.copy()', line)
        line = re.sub(r'\.duplicate\(', '.copy(', line)
        line = re.sub(r'\.append_array\(', '.extend(', line)
        line = re.sub(r'\.size\(\)', '.__len__()', line)  # 任意表达式 X.size() -> X.__len__()
        line = re.sub(r'\.shuffle\(\)', '', line)   # 洗牌顺序对模拟无影响
        # self. -> _item.
        line = line.replace("self.", "_item.")
        # 表达式中的超类调用 .method(...)（如 `return x or .canAffect(item)`）-> 调用引擎基类方法 _base_method
        # 仅当点号前不是标识符/右括号/点/方括号（避免误伤 obj.method / a.b.method / arr[0].method）
        line = re.sub(r'(?<![\w.)\]])\.([A-Za-z_]\w*)\(',
                      lambda m: '_item._base_' + _py_method_name(m.group(1)) + '(', line)
        # character().INVENTORY.getItems() -> character().get_items()
        line = re.sub(r'\.INVENTORY\.', '.', line)
        line = re.sub(r'\binventory\.countSocketedGems\(\)', '_item.character_().count_socketed_gems()', line)
        line = re.sub(r'\.getItems\(\)\.countSocketedGems\(\)', '.count_socketed_gems()', line)
        # 裸 self（作参数传，如 useStacks(buff, n, self)）-> _item
        line = re.sub(r'(?<![\w.])self\b(?!\.)', '_item', line)
        # for X in <expr>: -> for X in _range_or_value(<expr>):  (GDScript 允许 for i in int / X.size())
        line = re.sub(r'^for\s+([A-Za-z_]\w*)\s+in\s+(.+?)\s*:\s*$',
                      r'for \1 in _range_or_value(\2):', line)
        # 基类属性 affectedItems -> _item.get_affected_items()（读取走方法，返回实时邻接）
        line = re.sub(r'(?<![\w.])affectedItems\b', '_item.get_affected_items()', line)
        # affectedItems 作为赋值目标时改为属性（避免“不能给函数调用赋值”）
        line = re.sub(r'(?<![\w.])_item\.get_affected_items\(\)\s*=', '_item.affectedItems =', line)
        # inventory.getItems() / 裸 inventory -> 角色物品列表
        line = re.sub(r'\binventory\.getItems\(', '_item.character_().get_items(', line)
        line = re.sub(r'(?<![\w.])inventory\b', '_item.character_().get_items()', line)
        # descriptor.minDam/maxDam -> 物品数值
        line = line.replace("descriptor.minDam", "_item.min_dam")
        line = line.replace("descriptor.maxDam", "_item.max_dam")
        line = line.replace("descriptor.chance", "_item.get_chance()")
        # int()/float()/min()/max()/abs()/len()/range()/round()/str() 等保持

        # getP1()..getP10() -> _item.get_p(N-1)  (GDScript getP1 = getP(0))
        line = re.sub(r'\bgetP([1-9]\d*)\(([^)]*)\)',
                      lambda m: '_item.get_p(%d)' % (int(m.group(1)) - 1), line)
        # 宝石的 socket.getItem() -> _item.get_socket().get_item()
        line = re.sub(r'\bsocket\.getItem\(', '_item.get_socket().get_item(', line)
        # getP_m("x") -> _item.get_p_m("x")
        line = re.sub(r'\bgetP_m\(', '_item.get_p_m(', line)
        line = re.sub(r'\bgetChance\(\)', '_item.get_chance()', line)
        line = re.sub(r'\bgetChance2\(\)', '_item.get_chance2()', line)
        line = re.sub(r'\bgetGemPower\(\)', '_item.get_gem_power()', line)

        # 方法名重命名 (getP* 已处理；getP1..getP10/getP_m 走专用正则，裸 getP 走这里)
        for gname, pyname in METHOD_RENAME.items():
            if re.match(r'^getP\d+$', gname) or gname == 'getP_m':
                continue
            if sibling_methods and gname in sibling_methods:
                # 脚本内定义的方法（含重载）：交给 repl_call 的 _behavior_call 派发，优先走脚本实现
                continue
            line = re.sub(r'\b' + re.escape(gname) + r'\(', pyname + '(', line)

        # 裸 self 方法 -> _item.  (排除内置函数与控制关键字)
        BUILTINS = {"len", "int", "float", "min", "max", "abs", "round", "str",
                    "range", "print", "bool", "list", "dict", "set", "sum", "pow",
                    "if", "for", "while", "elif", "return", "def", "and", "or",
                    "not", "else", "match", "with", "in", "is", "type", "enumerate",
                    "sorted", "zip", "map", "filter", "any", "all",
                    "_range_or_value", "ceil", "floor", "Vector2", "Vector2i"}

        def repl_call(m):
            nm = m.group(1)
            if nm in BUILTINS:
                return m.group(0)
            # 脚本内定义的同级方法：经由 _behavior_call 派发（避免 _item.<name>() 找不到）
            if sibling_methods and nm in sibling_methods:
                return '_item._behavior_call("%s", ' % nm
            # 已是 _item./obj. 的不加
            return "_item." + m.group(0)
        line = re.sub(r'(?<![\w.])'  # 前面不是字母数字或点
                      r'([A-Za-z_]\w*)\(', repl_call, line)

        # 2) 裸实例变量引用(非调用)：_item.var
        for v in instance_vars:
            line = re.sub(r'(?<![\w.])' + re.escape(v) + r'\b(?!\()', '_item.' + v, line)

        py_indent = max(0, level - base_level) * 4
        out.append(" " * py_indent + line)
    return "\n".join(out), local_vars


def _py_method_name(name: str) -> str:
    """GDScript 方法名 -> 引擎 snake_case 方法名"""
    if name in METHOD_RENAME:
        return METHOD_RENAME[name]
    return re.sub(r'(?<!^)(?=[A-Z])', '_', name).lower()


def convert_match_blocks(py_src: str) -> str:
    """把 GDScript 的 match 语句转成 Python 的 if/elif/else。

    GDScript:
        match expr:
            CaseA:
                ...
            CaseB:
                ...
            _:
                ...
    转成:
        if expr == CaseA:
            ...
        elif expr == CaseB:
            ...
        else:
            ...
    （GDScript match 的 case 为相等比较；Python 无 match 等价语法，统一降级为 if/elif。）
    """
    lines = py_src.split("\n")
    out = []
    i = 0
    n = len(lines)
    while i < n:
        line = lines[i]
        m = re.match(r'^(\s*)match\s+(.+?)\s*:\s*$', line)
        if not m:
            out.append(line)
            i += 1
            continue
        indent = len(line) - len(line.lstrip(' '))
        expr = m.group(2).strip()
        i += 1
        case_indent = indent + 4
        first = True
        while i < n:
            cur = lines[i]
            if cur.strip() == "":
                out.append(cur)
                i += 1
                continue
            cind = len(cur) - len(cur.lstrip(' '))
            if cind <= indent:
                break  # match 块结束
            if cind == case_indent:
                cm = re.match(r'^([\w.]+)\s*:\s*$', cur.strip())
                if cm:
                    val = cm.group(1)
                    if val == '_':
                        out.append(' ' * indent + 'else:')
                    else:
                        kw = 'if' if first else 'elif'
                        first = False
                        out.append(' ' * indent + f'{kw} {expr} == {val}:')
                else:
                    out.append(cur)
                i += 1
            else:
                out.append(cur)  # case 体，原样保留
                i += 1
    return "\n".join(out)


def parse_script(path):
    with open(path, encoding="utf-8", errors="replace") as f:
        src = f.read()
    lines = src.split("\n")

    extends = None
    for ln in lines:
        m = EXTENDS_RE.match(ln.strip())
        if m:
            extends = m.group(1)
            break

    instance_vars, onready, typed_defaults = collect_instance_vars(lines)

    methods = {}
    i = 0
    n = len(lines)
    while i < n:
        m = FUNC_RE.match(lines[i])
        if m:
            name = m.group(1)
            args = strip_type_hints(m.group(2))
            # 收集缩进体
            j = i + 1
            body = []
            base_indent = None
            while j < n:
                cur = lines[j]
                if cur.strip() == "":
                    body.append(cur)
                    j += 1
                    continue
                ind = len(cur) - len(cur.lstrip(" \t"))
                if base_indent is None:
                    base_indent = ind
                if ind < base_indent:
                    break
                body.append(cur)
                j += 1
            # 去掉尾部空行
            while body and body[-1].strip() == "":
                body.pop()
            methods[name] = {"args": args, "body": body}
            i = j
        else:
            i += 1

    return extends, instance_vars, onready, typed_defaults, methods


def build_behavior(path):
    extends, instance_vars, onready, typed_defaults, methods = parse_script(path)
    py_methods = {}
    raw_methods = {}
    for name, info in methods.items():
        # 跳过纯视觉/引擎基类方法（prepare 保留：Dagger 等的信号连接在 prepare 里）
        if name in ("_ready", "preset", "combatEnd", "shopEntered",
                    "addToInventory", "removeFromInventory", "onRemoveFromInventory",
                    "onAddToInventory", "ready_deferred", "initItemLibrary",
                    "initTitle", "initTooltip", "initBuildViewer", "initGridStorageIcon",
                    "initInfoPanelIcon", "initBuildViewerIcon", "initRecipeBook",
                    "onSold", "onBought", "onItemAdded", "onItemRemoved",
                    "onItemTypeChanged", "onGateItemRoll", "getDescription",
                    "getTranslatedName", "getName", "getIndex", "getFlavorText",
                    "getBagEffect", "getModeDescription", "getRelatedItemHeight",
                    "getGatedDescriptor", "getShopPriority", "getCraftingOffset",
                    "getAffectedCellsAfterRotate_primary",
                    "getAffectedCellsAfterRotate_secondary", "getBaseDescription",
                    "insertParameter", "insertParameters", "getGatedDescriptor",
                    "cardSecondaryEffectActive", "getTriggerPriority",
                    "onItemInstantiated", "onItemRoll", "onItemRolled",
                    "onAddToInventory_deferred", "onRemoveFromInventory_deferred",
                    "getData", "doRevealEffect",
                    "onHotSwapHoverWithGemEnd", "onHotSwapHoverStart",
                    "onHotSwapHoverEnd", "onFusingAsIngredient", "onPlacedByPlayer",
                    "onRemovedByPlayer", "onItemAddedToSocket", "onItemRemovedFromSocket",
                    "onSpawned", "onCollected", "onDiscarded", "onPooled",
                    "onUnpooled", "onPickedUp", "onDropped", "onClicked",
                    "onHovered", "onUnhovered", "onInfoPanelClicked",
                    "onSoldToShop", "onBoughtFromShop", "onAddToShop",
                    "onRemoveFromShop", "onShopRoll", "onShopEntered",
                    "onRetired", "onReborn", "onLevelUp", "onExperienceGained",
                    "onFuse", "onUnfuse", "onCraftingPreview", "onItemAddedInside",
                    "onItemRemovedInside", "onItemTypeAdded", "onItemTypeRemoved",
                    "getOccupiedCells", "getAffectedCells", "getSocketCells",
                    "getStarPosition", "onAfterEffectFinished_check",
                    "getRandomBuffType", "getAvailableBuffs", "onSocketChanged",
                    "onGemInserted", "onGemRemoved", "onItemInSlotChanged",
                    "updateConnector", "getSockets", "onBagChanged",
                    "getDragParticles", "getSpecificDragParticles",
                    "onItemInstantiated_delayed", "getBuffEffect", "getEffectDescription",
                    "getTriggerDescription", "onAffectedItemAdded",
                    "onAffectedItemRemoved", "onRarityChanged",
                    "onItemAdded_deferred", "onItemRemoved_deferred", "onItemMoved",
                    "onItemRotated", "onItemFlipped", "onItemDroppedOn",
                    "onItemPickedUpFrom", "onItemActivated_check", "getActivationParticles",
                    "getP_check", "getShopDescription", "getItemType", "getItemName",
                    "getRarity", "getMaterial", "getTypes", "getTags", "getStack",
                    "getStars", "getValue", "getPrice", "isLocked", "isPooled",
                    "isItemLibrary", "setLocked", "setPooled", "setFlipped",
                    "flip", "rotate", "getFaceDirection", "setFaceDirection",
                    "updateShaderRotation", "getShaderRotation",
                    "getDimensions", "setDimensions", "getCells", "setCells",
                    "getAnchor", "setAnchor", "getItemBook", "getDescriptor",
                    "getItemData", "getModifiers", "setModifiers", "hasModifier",
                    "addModifier", "removeModifier", "onModifierAdded",
                    "onModifierRemoved", "getSecondaryEffect", "hasSecondaryEffect",
                    "getPrimaryEffect", "hasPrimaryEffect", "onItemEvent",
                    "onGameEvent", "onBuyEvent", "onSellEvent", "onCraftEvent",
                    "getRelatedItems", "getAdjacentItems", "getItemsInAffectedCells",
                    "getItemsInAffectedCells_cached", "getAffectedPoints",
                    "getPointsInAffectedCells", "getAffectedCellsAfterRotate",
                    "getRelatedItemWidth", "getRelatedItemOffset",
                    "getFirstAffectedCell", "getNumCellsOf", "canAffect_color",
                    "getInventory", "getOwner", "setOwner", "getPlayer",
                    "isPlayer", "getCharacter", "getOpposingItem", "getFacingItem",
                    "onItemAddedToBackpack", "onItemRemovedFromBackpack",
                    "onItemAddedToStorageBox", "onItemRemovedFromStorageBox",
                    "onItemBought", "onItemSold", "onItemCrafted", "onItemFused",
                    "onItemConsumed", "onItemActivated_global", "onGlobalItemActivated",
                    "onAnyItemActivated", "onCombatStart_global", "onRoundWon",
                    "onRoundLost", "onBattleEnd", "onGameEnd", "onMatchStart",
                    "onShopRefresh", "onPreparationStart", "onPreparationEnd",
                    "onItemRolledOut", "onItemRolledIn", "onGateOpened",
                    "onGateClosed", "onNextRound", "onPreviousRound"):
            continue
        body_py, local_vars = transform_body(info["body"], instance_vars, set(methods.keys()))
        body_py = convert_match_blocks(body_py)
        # 组装函数源码（方法内 var 声明提升，防 Python UnboundLocalError）
        arglist = "_item" + (", " + info["args"] if info["args"] else "")
        src = f"def {name}({arglist}):\n"
        # 方法内 var 提升：参数名除外（去掉类型默认值部分）
        param_names = {a.split("=")[0].strip() for a in info["args"].split(",") if a.strip()}
        hoisted = [v for v in dict.fromkeys(local_vars) if v not in param_names]
        if hoisted:
            src += "    " + "; ".join(f"{v} = None" for v in hoisted) + "\n"
        if body_py.strip() == "":
            src += "    pass\n"
        else:
            src += "    " + body_py.replace("\n", "\n    ")
            if not body_py.strip().endswith((":", "pass")):
                pass
        # 编译校验
        try:
            compile(src, path + ":" + name, "exec")
            py_methods[name] = src
        except Exception as e:
            raw_methods[name] = "\n".join(info["body"])
    # onready var 初始化 + 无初始化器变量的类型默认值 并入 _onready_init
    if onready or typed_defaults:
        init_src = "def _onready_init(_item):\n"
        for vname, expr in onready:
            e = expr
            # $节点引用 / get_node 等视觉引用 -> None
            e = re.sub(r'\$[\w/]+', 'None', e)
            e = re.sub(r'\bget_node\([^)]*\)', 'None', e)
            e = re.sub(r'\bgetP([1-9]\d*)\(\)',
                       lambda m: '_item.get_p(%d)' % (int(m.group(1)) - 1), e)
            e = re.sub(r'\bgetP_m\(', '_item.get_p_m(', e)
            e = re.sub(r'\bgetChance\(\)', '_item.get_chance()', e)
            e = re.sub(r'\bgetGemPower\(\)', '_item.get_gem_power()', e)
            for gname, pyname in METHOD_RENAME.items():
                if re.match(r'^getP\d+$', gname) or gname == 'getP_m':
                    continue
                e = re.sub(r'\b' + re.escape(gname) + r'\(', pyname + '(', e)
            import builtins as _b
            _BUILT = set(dir(_b)) | {"len", "int", "float", "min", "max", "abs",
                                    "round", "str", "range", "print", "bool", "list",
                                    "dict", "set", "sum", "pow", "if", "for", "while",
                                    "elif", "return", "def", "and", "or", "not", "else",
                                    "_range_or_value", "Vector2", "Vector2i"}

            def _rc(m):
                nm = m.group(1)
                return m.group(0) if nm in _BUILT else "_item." + m.group(0)
            e = re.sub(r'(?<![\w.])' + r'([A-Za-z_]\w*)\(', _rc, e)
            # 每个初始化独立 try/except（视觉引用失败不影响其余）
            init_src += f"    try:\n        _item.{vname} = {e}\n    except Exception:\n        pass\n"
        # 无初始化器变量：按声明类型给默认值
        for vname, default in typed_defaults.items():
            if vname not in [o[0] for o in onready]:
                init_src += f"    _item.{vname} = {default}\n"
        try:
            compile(init_src, path + ":onready", "exec")
            py_methods.setdefault("_onready_init", init_src)
        except Exception:
            pass
    return {
        "extends": extends,
        "instance_vars": sorted(instance_vars),
        "methods": py_methods,
        "methods_raw": raw_methods,
    }


def scan_scripts():
    """递归扫描 Items 目录下所有 .gd 脚本，返回 {规范名(小写无空格): 完整路径}。

    覆盖 Exclusive/、Exclusive/Chess/、Exclusive/Animations/、Gems/、Animations/、Tiles/ 等任意层级。
    """
    idx = {}
    for root, _, files in os.walk(ITEMS_SRC):
        for fn in sorted(files):
            if not fn.endswith(".gd"):
                continue
            norm = fn[:-3].lower().replace(" ", "")
            idx.setdefault(norm, os.path.join(root, fn))
    return idx


def match_script_key(key, idx):
    """按物品名在脚本索引中匹配 .gd 路径。

    兼容：子目录规范化(已在 scan_scripts 完成)、大小写、空格、品质前缀
    (Chipped/Flawed/.../Strong)、特例前缀(Unstable/Stable/...)、尾部 "New" 后缀、数字后缀。
    例: "Book of Ice New" -> BookofIce ; "Unstable Recombobulator" -> Recombobulator。
    """
    cands = [key, key.lower(), key.replace(" ", ""), key.lower().replace(" ", ""),
             key.replace("-", ""), key.lower().replace("-", ""),
             key.replace(" ", "").replace("-", ""), key.lower().replace(" ", "").replace("-", "")]
    for c in cands:
        if c in idx:
            return idx[c]
    k = key
    for q in ("Chipped ", "Flawed ", "Regular ", "Flawless ", "Perfect ",
              "Strong ", "Unstable ", "Stable ", "Lesser ", "Greater "):
        if k.startswith(q):
            k = k[len(q):]
            break
    k2 = k
    if k2.endswith(" New"):
        k2 = k2[:-4]
    k2 = k2.rstrip("0123456789 ").strip()
    for c in (k, k2, k.lower(), k2.lower(), k.replace(" ", ""), k2.replace(" ", ""),
              k.lower().replace(" ", ""), k2.lower().replace(" ", "")):
        if c in idx:
            return idx[c]
    return None


def main():
    db = json.load(open(DB_PATH, encoding="utf-8"))
    items = db.get("items", db)
    idx = scan_scripts()
    print(f"脚本索引: {len(idx)}  数据库物品: {len(items)}")

    matched = 0
    skipped_no_script = 0
    for key in items:
        scr = items[key].get("script")
        sp = None
        if scr:
            norm = scr[:-3].lower().replace(" ", "") if scr.endswith(".gd") else scr.lower().replace(" ", "")
            sp = idx.get(norm)
        if sp is None:
            sp = match_script_key(key, idx)
        if sp is None:
            skipped_no_script += 1
            continue
        try:
            beh = build_behavior(sp)
        except Exception as e:
            print(f"  [PARSE ERR] {key}: {e}")
            continue
        if beh["methods"] or beh["methods_raw"]:
            items[key]["behavior"] = beh
            items[key]["behavior"]["script_file"] = os.path.basename(sp)
            matched += 1

    print(f"已写入 behavior 的物品: {matched}  无脚本匹配: {skipped_no_script}")
    json.dump(db, open(DB_PATH, "w", encoding="utf-8"), ensure_ascii=False, indent=1)
    print("已写出", DB_PATH)


if __name__ == "__main__":
    main()
