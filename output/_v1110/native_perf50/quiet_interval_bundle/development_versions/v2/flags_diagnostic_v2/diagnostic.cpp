#include "native_active_cooldowns.hpp"
#include "gen/hdrs/Gd__gd_core__CoreCombat.hpp"
#include "gen/hdrs/Gd__gd_core__CoreRng.hpp"
#include "gen/hdrs/Gd__gd_core__CoreTimer.hpp"
#include "gen/hdrs/Gd__gd_core__CoreContext__INNER__NativeFlicker.hpp"
#include <cassert>
#include <bit>
#include <cerrno>
#include <cfenv>
#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>
#include <xmmintrin.h>
using V=gd::GdVal;
using Context=Gd__gd_core__CoreContext;
using Combat=Gd__gd_core__CoreCombat;
using Character=Gd__gd_core__CoreCharacter;
using Buff=Gd__gd_core__CoreBuff;
using Item=Gd__gd_core__CoreItem;
using Grid=Gd__gd_core__CoreGrid;
using Timer=Gd__gd_core__CoreTimer;
using Rng=Gd__gd_core__CoreRng;
using Flicker=Gd__gd_core__CoreContext__INNER__NativeFlicker;
extern "C" void gd_init_all_classes();
using Advance=unsigned (*)(Combat*,Context*,unsigned,void*);
static Advance advance;
struct Hash {
    uint64_t value=1469598103934665603ull;
    void word(uint64_t x){value=(value^x)*1099511628211ull;}
    void val(const V& v){word(unsigned(v.kind));switch(v.kind){
        case V::Kind::Null:break;
        case V::Kind::Bool:word(v.b);break;
        case V::Kind::Int:word(v.i);break;
        case V::Kind::Float:word(std::bit_cast<uint64_t>(v.f));break;
        case V::Kind::Vec2:word(std::bit_cast<uint64_t>(v.v2.x));word(std::bit_cast<uint64_t>(v.v2.y));break;
        case V::Kind::Color:if(v.col){word(std::bit_cast<uint64_t>(v.col->r));word(std::bit_cast<uint64_t>(v.col->g));word(std::bit_cast<uint64_t>(v.col->b));word(std::bit_cast<uint64_t>(v.col->a));}else word(0);break;
        case V::Kind::ClassRef:word(v.cls?v.cls->id:0);break;
        case V::Kind::Enum:if(v.en){for(const char* p=v.en->name;*p;++p)word(static_cast<unsigned char>(*p));word(v.en->len);for(unsigned i=0;i<v.en->len;++i)word(v.en->items[i].val);}else word(0);break;
        case V::Kind::FuncRef:if(v.fr){word(v.fr->instance?v.fr->instance->gid_:0);word(v.fr->method);val(V::from_arr(v.fr->binds));}else word(0);break;
        case V::Kind::Obj:word(v.obj?v.obj->gid_:0);break;
        case V::Kind::Arr:word(v.arr?v.arr->len:0);if(v.arr)for(unsigned i=0;i<v.arr->len;++i)val(v.arr->data[i]);break;
        case V::Kind::Dict:word(v.dict?v.dict->len:0);if(v.dict)for(unsigned i=0;i<v.dict->len;++i){val(v.dict->entries[i].key);val(v.dict->entries[i].val);}break;
        case V::Kind::Rng:word(v.rng?v.rng->get_state():0);break;
        case V::Kind::Str:word(v.str?v.str->len:0);if(v.str)for(unsigned i=0;i<v.str->len;++i)word(static_cast<unsigned char>(v.str->data[i]));break;
        default:assert(false);
    }}
    void capture(const Gd__gd_core__CoreContext& o){val(o.f_rng);val(o.f_util);val(o.f_bus);val(o.f_hooks);val(o.f_combat_log);val(o.f_player);val(o.f_opponent);val(o.f_fight_ended);val(o.f_time);val(o.f_probe_pass);val(o.f_frame_counter);val(o.f_combat_time);val(o.f_below_master);val(o.f_label_rng_enabled);val(o.f_lobbies_mode);val(o.f_custom_health_multiplier);val(o.f__drawseq_enabled);val(o.f_lib_fires);val(o.f_combat);val(o.f_item_book);val(o.f_sandbag_active);val(o.f_cur_mode);val(o.f_cur_round);val(o.f_rope_speedups);val(o.f_cube_advanced);val(o.f_event_type_keys);val(o.f_class_resources);val(o.f_unhealingDamageSource);val(o.f_fatigueDamageSource);val(o.f_stealLifeDamageSource);val(o.f_out_of_stamina_count);val(o.f_warn_unknown_api);val(o.f_show_cooldown_progress);val(o.f__deferred);val(o.f__idle_frame_calls);val(o.f__timed);val(o.f_deferred_flush_enabled);val(o.f_eb_relay_mirrored);val(o.f_keyed_stop_clears_seen);val(o.f_keyed_cleanse_biggest_first);val(o.f__emptyGrid);val(o.f_activation_rng_state);val(o.f_idle_timer_initial);val(o.f_timer_pass_epoch);val(o.f_in_physics_timer_pass);val(o.f_in_item_physics_pass);val(o.f_replay_buff_state);val(o.f_replay_engine_rng);val(o.f_native_frame_rng);val(o.f_native_label_mode);val(o.f_training_start);val(o.f_replay_native_scene_delays);val(o.f__opening_delay_ready);val(o.f_replay_util_time);val(o.f__critical_shake_delta);val(o.f__critical_shake_active);val(o.f__critical_shake_frame);val(o.f__critical_shake_after_idle);val(o.f__particle_draws);val(o.f_particle_draw_frame);val(o.f__particle_pending_draws);val(o.f__particle_before_physics);val(o.f__motion_queue);val(o.f_flicker_initial);val(o.f__flickers);val(o.f__opponent_flickers);}
void capture(const Gd__gd_core__CoreCombat& o){val(o.f_ctx);val(o.f_player);val(o.f_opponent);val(o.f_ordered_items);val(o.f_result);val(o.f_fight_ended);val(o.f_combat_time);val(o.f_fatigue_counter);val(o.f_fatigue_started);val(o.f_fatigue_next_tick);val(o.f_fatigue_interval);val(o.f_time_advance);val(o.f_speed_scale);val(o.f__activate_countdown);val(o.f_activated);val(o.f__track_hidden_log);val(o.f__tick_timer_left);val(o.f__tick_timer_active);val(o.f_max_time);val(o.f_timed_out);val(o.f__pending_deferred);}
void capture(const Gd__gd_core__CoreCharacter& o){val(o.f_ctx);val(o.f_playerId);val(o.f_opponent);val(o.f_isDead);val(o.f_buffs);val(o.f_maxHealth);val(o.f_curHealth);val(o.f_temporaryMaxHealth);val(o.f_temporaryMaxHealthGain);val(o.f_baseMaxStamina);val(o.f_maxStamina);val(o.f_curStamina);val(o.f_temporaryMaxStamina);val(o.f_baseStaminaRegen);val(o.f_staminaRegen);val(o.f_allowStaminaOverflow);val(o.f_staminaUpdateQueued);val(o.f_statsDisplay);val(o.f_damageResistance);val(o.f_damageReduction);val(o.f_invulnerable);val(o.f_dodgeStacks);val(o.f_critResistance);val(o.f_critResistStacks);val(o.f_critTokens);val(o.f_stunResistance);val(o.f_unhealingAmount);val(o.f_healingEfficiency);val(o.f_critTokensUsed);val(o.f_debuffResistStacks);val(o.f_debuffReflectStacks);val(o.f_buffProtectStacks);val(o.f_bonusFatigueDamage);val(o.f_empowerDamage);val(o.f_blindingLightActive);val(o.f_stunnedDuration);val(o.f_tickCounter);val(o.f_typedDamageFactors);val(o.f_meleeSpikesLimit);val(o.f_rangedSpikesLimit);val(o.f_effectSpikesLimit);val(o.f_meleeVampirismLimit);val(o.f_rangedVampirismLimit);val(o.f_battleRageAura);val(o.f_battleRageBonusDur);val(o.f_accuracyRng);val(o.f_critRng);val(o.f_critResistanceRng);val(o.f_stunResistanceRng);val(o.f_items);val(o.f_inventory);val(o.f_INVENTORY);val(o.f_character_died_handlers);val(o.f_poisonDamageSource);val(o.f_spikeDamageSource);val(o.f_characterClass);val(o.f_chibi);val(o.f_invulnerabilityItem);val(o.f__invul_left);val(o.f__invul_active);val(o.f_autoRageItem);val(o.f__rage_left);val(o.f__rage_active);val(o.f__autoRage_left);val(o.f__autoRage_active);val(o.f__rage_wait);val(o.f__invul_wait);val(o.f_attack_moving_forward);val(o.f_attack_sound_ready_time);val(o.f__tick_timer_left);val(o.f__tick_timer_active);val(o.f_damage_anim_current);val(o.f__visual_x);val(o.f__visual_y);val(o.f__visual_from_x);val(o.f__visual_from_y);val(o.f__visual_to_x);val(o.f__visual_to_y);val(o.f__visual_forward);val(o.f__visual_back);val(o.f__visual_elapsed);val(o.f__visual_kind);val(o.f__visual_stage);val(o.f__visual_generation);val(o.f__idle_animation_left);val(o.f__physics_timer_mask);}
void capture(const Gd__gd_core__CoreRng& o){val(o.f_rng);val(o.f_debug_flip_tag);val(o.f_oracle_trace);val(o.f_oracle_trace_log);val(o.f__stacktrace);val(o.f_draw_seq);val(o.f_globalChainOpen);}
void capture(const Gd__gd_core__CoreBuff& o){val(o.f_type);val(o.f_isBuff);val(o.f_character);val(o.f_current);val(o.f_permanentStacks);val(o.f_resistChancePercent);val(o.f_resistStacks);val(o.f_reflectChancePercent);val(o.f_cleanseProtectionChancePercent);val(o.f_signalName);val(o.f_temporaryStacks);val(o.f_nextTemporaryTimeout);val(o.f_MAX_STACKS);val(o.f__timer_left);val(o.f__timer_active);val(o.f__timer_wait);val(o.f__timer_first_pass);val(o.f__timer_member_epoch);val(o.f_ctx);}
void capture(const Gd__gd_core__CoreItem& o){val(o.f_descriptor);val(o.f_ctx);val(o.f_character_);val(o.f_inventory);val(o.f_placed);val(o.f_name);val(o.f_chargeFrame);val(o.f_speedScale);val(o.f_bonusMaxDam);val(o.f_bonusMinDam);val(o.f_removableDam);val(o.f_bonusDamageFactor);val(o.f_staminaFactor);val(o.f_critChancePercent);val(o.f_critTokens);val(o.f_critSeverity);val(o.f_bonusChancePercent_mult);val(o.f_bonusChancePercent_additive1);val(o.f_bonusChancePercent_additive2);val(o.f_bonusAccuracy);val(o.f_buffPowers);val(o.f_buffAmplificationChances);val(o.f_damageSource);val(o.f_doubleActivationChance);val(o.f_doubleAttackEffectChance);val(o.f_paramMult);val(o.f_paramAdd);val(o.f_numCharges);val(o.f_baseCooldownOverride);val(o.f_chanceRng);val(o.f_damageRangeRng);val(o.f_statDisplayOverrides);val(o.f_lastActivationTime);val(o.f_activationsThisFrame);val(o.f_lastTriggerTime);val(o.f_triggersThisFrame);val(o.f_triggerTime);val(o.f_iterationCooldown);val(o.f_itemMetrics);val(o.f__grid);val(o.f__behavior);val(o.f__cooldown_changed_epoch);val(o.f__cooldown_blocked_epoch);val(o.f_dynamicTypes);val(o.f_combatConnections);val(o.f_ownerType);val(o.f_placedByPlayer);val(o.f_dragged);val(o.f_occupiedCells);val(o.f_collisionCells);val(o.f_extensionCells);val(o.f_affectedExtensionCells);val(o.f_affectedCellsCache);val(o.f_currentAffectedItems);val(o.f_cachedAffectedItems);val(o.f_affectedTileCells);val(o.f_consumed);val(o.f_hasPreDealDamageEarlyEffect);val(o.f_hasPreDealDamageLateEffect);val(o.f_hasDealtDamageEffect);val(o.f_hasOnChargeReceivedEffect);val(o.f_hasOnChargeLeftEffect);val(o.f_gems);val(o.f__cooldown_active);val(o.f_buffLabelPositionTimestamps);val(o.f_replacementPending);val(o.f_faceDirection);val(o.f_rotation);}
void capture(const Gd__gd_core__CoreGrid& o){val(o.f_filledCells);val(o.f_bagCells);val(o.f_items);val(o.f_character);val(o.f_curHovered);}
void capture(const Gd__gd_core__CoreTimer& o){val(o.f__ctx);val(o.f__owner);val(o.f_name);val(o.f_wait_time);val(o.f_one_shot);val(o.f_multi);val(o.f_callback_method);val(o.f_timestamps);val(o.f_fire_count);val(o.f__left);val(o.f__stopped);val(o.f__first_pass);val(o.f__member_epoch);}
void capture(const Gd__gd_core__CoreContext__INNER__NativeFlicker& o){val(o.f_ctx);val(o.f_limits);val(o.f_position);val(o.f_speed);val(o.f_length);val(o.f_playing);val(o.f_inside_tree);val(o.f_loop);}
};
struct Scene {
    gd::BattleCtx battle{65536};gd::GdRng util;
    Context* ctx;Combat* combat;Rng* rng;Character* chars[2];
    std::vector<Item*> items;std::vector<Timer*> timers;std::vector<Buff*> buffs;
    std::vector<Grid*> grids;std::vector<Flicker*> flickers;
    template<class T>T* make(const gd::GdClassMeta& meta){auto* o=static_cast<T*>(meta.alloc_fn(battle));o->init_fields(battle);return o;}
    static V arr(gd::BattleCtx& b){return V::from_arr(gd::GdArr::create(b.arena));}
    Scene(unsigned seed,unsigned mode):util(123+seed){
        battle.bind_battle(97+seed);battle.native_resolved_dispatch=true;battle.native_event_kernel=true;
        battle.native_inline_timer_headers=true;battle.native_timer_watch.enabled=true;battle.native_timer_watch.closed_world=true;
        ctx=make<Context>(META_Gd__gd_core__CoreContext);combat=make<Combat>(META_Gd__gd_core__CoreCombat);rng=make<Rng>(META_Gd__gd_core__CoreRng);
        rng->f_rng=V::from_rng(&util);rng->f_oracle_trace=V::from_bool(false);rng->f_draw_seq=V::from_int(-1);ctx->f_rng=V::from_obj(rng);
        ctx->f_native_frame_rng=V::from_bool(seed&1);ctx->f_replay_native_scene_delays=V::from_bool(true);ctx->f_deferred_flush_enabled=V::from_bool(true);
        ctx->f_show_cooldown_progress=V::from_bool(false);ctx->f_fight_ended=V::from_bool(false);ctx->f_time=V::from_float(2.0);ctx->f_combat_time=V::from_float(2.0);
        ctx->f_timer_pass_epoch=V::from_int(17);ctx->f_frame_counter=V::from_int(137);
        ctx->f__deferred=arr(battle);ctx->f__idle_frame_calls=arr(battle);ctx->f__timed=arr(battle);ctx->f__motion_queue=arr(battle);
        ctx->f_lib_fires=arr(battle);ctx->f__flickers=arr(battle);ctx->f__opponent_flickers=arr(battle);ctx->f__critical_shake_delta=arr(battle);
        ctx->f__critical_shake_active=arr(battle);ctx->f__particle_draws=arr(battle);ctx->f__particle_pending_draws=V::from_int(0);ctx->f__particle_before_physics=V::from_int(0);
        combat->f_ctx=V::from_obj(ctx);combat->f_activated=V::from_bool(true);combat->f_fight_ended=V::from_bool(false);
        combat->f__pending_deferred=V::from_bool(false);combat->f__track_hidden_log=V::from_bool(false);combat->f_combat_time=V::from_float(2.0);combat->f_max_time=V::from_float(300.0);combat->f_fatigue_next_tick=V::from_float(100.0);
        for(unsigned s=0;s<2;++s){auto* c=make<Character>(META_Gd__gd_core__CoreCharacter);chars[s]=c;
            c->f_ctx=V::from_obj(ctx);c->f_playerId=V::from_int(s);c->f_stunnedDuration=V::from_float(0);
            c->f_curStamina=V::from_float(7.0);c->f_staminaRegen=V::from_float(0.8);c->f_maxStamina=V::from_float(10.0);c->f_temporaryMaxStamina=V::from_float(0.0);
            c->f__idle_animation_left=V::from_float(mode==1?0.02:7.0);c->f__tick_timer_active=V::from_bool(true);c->f__tick_timer_left=V::from_float(0.5);
            c->f__rage_active=V::from_bool(false);c->f__invul_active=V::from_bool(false);c->f__autoRage_active=V::from_bool(false);
            c->f_buffs=V::from_dict(gd::GdDict::create(battle.arena));
            for(int64_t key=100;key<=110;++key){auto* b=make<Buff>(META_Gd__gd_core__CoreBuff);buffs.push_back(b);b->f_ctx=V::from_obj(ctx);b->f_character=V::from_obj(c);b->f_type=V::from_int(key);b->f_current=V::from_int((seed+key+s)%7);b->f__timer_active=V::from_bool(key==101);b->f__timer_first_pass=V::from_int(17);b->f__timer_left=V::from_float(0.5);c->f_buffs.dict->set(battle.arena,V::from_int(key),V::from_obj(b));}
            auto* grid=make<Grid>(META_Gd__gd_core__CoreGrid);grids.push_back(grid);c->f_inventory=V::from_obj(grid);grid->f_items=arr(battle);
            for(unsigned i=0;i<8;++i){auto* item=make<Item>(META_Gd__gd_core__CoreItem);items.push_back(item);item->f_ctx=V::from_obj(ctx);item->f_character_=V::from_obj(c);item->f_placed=V::from_bool(true);item->f__cooldown_active=V::from_bool(true);item->f__cooldown_blocked_epoch=V::from_int(-1);item->f_triggerTime=V::from_float(1.0+0.1*i);item->f_speedScale=V::from_float((int(seed+i)%9-4)*0.13);item->f_statDisplayOverrides=arr(battle);item->f_statDisplayOverrides.arr->resize(battle.arena,5);item->f_gems=arr(battle);item->f_timers=arr(battle);grid->f_items.arr->push_back(battle.arena,V::from_obj(item));
                auto* t=make<Timer>(META_Gd__gd_core__CoreTimer);timers.push_back(t);t->f__ctx=V::from_obj(ctx);t->f__owner=V::from_obj(item);t->f__stopped=V::from_bool(false);t->f__first_pass=V::from_int(17);t->f__left=V::from_float(0.5);item->f_timers.arr->push_back(battle.arena,V::from_obj(t));
            }
        }
        ctx->f_player=V::from_obj(chars[1]);ctx->f_opponent=V::from_obj(chars[0]);combat->f_player=ctx->f_player;combat->f_opponent=ctx->f_opponent;
        switch(mode){
            case 2:items[seed%16]->f_triggerTime=V::from_float(0.06);break;
            case 3:timers[seed%16]->f__left=V::from_float(0.06);break;
            case 4:buffs[1]->f__timer_left=V::from_float(0.06);break;
            case 5:chars[0]->f_stunnedDuration=V::from_float(0.06);break;
            case 6:combat->f_fatigue_next_tick=V::from_float(0.06);break;
            case 7:chars[1]->f__tick_timer_left=V::from_float(0.06);break;
            case 8:items[0]->f__cooldown_blocked_epoch=V::from_int(18);break;
            case 9:timers[0]->f__first_pass=V::from_int(21);buffs[1]->f__timer_first_pass=V::from_int(21);break;
            case 10:items[0]->f_statDisplayOverrides.arr->data[3]=V::from_float(1.75);break;
            case 11:items[0]->f_statDisplayOverrides.arr->data[3]=V::from_str(gd::make_static_str("unknown"));break;
            case 12:items[0]->f__cooldown_active=V::from_int(1);break;
            case 13:items[0]->f_triggerTime=V::from_float(std::bit_cast<double>(uint64_t(0x7ff8000000000123)));break;
            case 14:items[0]->f_speedScale=V::from_float(std::bit_cast<double>(uint64_t(1)));break;
            case 15:chars[0]->f_curStamina=V::from_float(-0.0);chars[0]->f_staminaRegen=V::from_float(-0.0);break;
            case 16:grids[0]->f_items.arr->push_back(battle.arena,V::from_obj(items[0]));break;
            case 17:items[1]->f_timers.arr->push_back(battle.arena,V::from_obj(timers[0]));break;
            case 18:ctx->f_show_cooldown_progress=V::from_bool(true);break;
            case 19:battle.native_resolved_collect=true;break;
            case 20:ctx->f_deferred_flush_enabled=V::from_bool(false);break;
            case 21:combat->f_max_time=V::from_float(2.06);break;
            case 22:chars[0]->f_stunnedDuration=V::from_float(5.0);break;
            case 23:items[0]->f_placed=V::from_bool(false);break;
            case 32:chars[0]->f_staminaRegen=V::from_float(std::bit_cast<double>(uint64_t(0x100)));break;
            case 33:items[0]->f_statDisplayOverrides.arr->data[3]=V::from_float(std::bit_cast<double>(uint64_t(0x100)));break;
            case 34:chars[0]->f_curStamina=V::from_float(std::bit_cast<double>(uint64_t(0x100)));break;
            case 35:items[0]->f_statDisplayOverrides.arr->data[3]=V::from_float(std::bit_cast<double>(uint64_t(0x7fefffffffffffff)));break;
            case 36:chars[0]->f_maxStamina=V::from_float(std::bit_cast<double>(uint64_t(0x7fefffffffffffff)));chars[0]->f_temporaryMaxStamina=chars[0]->f_maxStamina;break;
            case 37:chars[0]->f_curStamina=V::from_float(std::bit_cast<double>(uint64_t(0x7fefffffffffffff)));chars[0]->f_staminaRegen=chars[0]->f_curStamina;break;
            case 38:ctx->f_time=V::from_float(std::bit_cast<double>(uint64_t(0xffefffffffffffff)));break;
            case 39:items[0]->f_triggerTime=V::from_float(std::bit_cast<double>(uint64_t(0x0010000000000000)));items[0]->f_statDisplayOverrides.arr->data[3]=V::from_float(std::bit_cast<double>(uint64_t(0x8010000000000000)));break;
            case 40:case 41:
                ctx->f_time=V::from_float(0.0);ctx->f_combat_time=V::from_float(0.0);combat->f_combat_time=V::from_float(0.0);
                for(auto* c:chars){c->f_curStamina=V::from_float(0.0);c->f_staminaRegen=V::from_float(mode==40?0.8:1.0);}
                for(auto* item:items){item->f_placed=V::from_bool(false);if(mode==41){item->f_triggerTime=V::from_float(0.0);item->f_statDisplayOverrides.arr->data[3]=V::from_float(-0.8);}}
                break;
        }
        if(mode==24||mode==25){auto* f=make<Flicker>(META_Gd__gd_core__CoreContext__INNER__NativeFlicker);flickers.push_back(f);f->f_ctx=V::from_obj(ctx);f->f_playing=V::from_bool(true);f->f_inside_tree=V::from_bool(true);f->f_loop=V::from_bool(false);f->f_position=V::from_float(mode==24?0.1:2.94);f->f_speed=V::from_float(1.1);f->f_length=V::from_float(3.0);f->f_limits=arr(battle);for(double x:{0.1,0.2,0.8,1.2})f->f_limits.arr->push_back(battle.arena,V::from_float(x));ctx->f__flickers.arr->push_back(battle.arena,V::from_obj(f));}
        if(mode==26||mode==27){auto entry=arr(battle);entry.arr->push_back(battle.arena,V::null());entry.arr->push_back(battle.arena,V::from_str(gd::make_static_str("unknown")));entry.arr->push_back(battle.arena,V::from_float(mode==26?0.5:0.06));entry.arr->push_back(battle.arena,arr(battle));ctx->f__timed.arr->push_back(battle.arena,entry);}
        if(mode==28||mode==29){auto entry=arr(battle);entry.arr->push_back(battle.arena,V::from_int(mode==28?0:1));entry.arr->push_back(battle.arena,V::from_obj(chars[0]));entry.arr->push_back(battle.arena,V::from_int(3));ctx->f__motion_queue.arr->push_back(battle.arena,entry);auto* c=chars[0];c->f__visual_generation=V::from_int(3);c->f__visual_kind=V::from_int(1);c->f__visual_stage=V::from_int(0);c->f__visual_elapsed=V::from_float(0.0);c->f__visual_forward=V::from_float(0.05);c->f__visual_back=V::from_float(0.1);c->f__visual_to_x=V::from_float(2.0);c->f__visual_to_y=V::from_float(1.0);}
        if(mode==30){ctx->f_native_frame_rng=V::from_bool(true);ctx->f__critical_shake_frame=V::from_int(0);auto window=Context::get_static_const_or_enum(battle,SYM_GEN_CRITICAL_SHAKE_WINDOW_1456).as_int();ctx->f__critical_shake_delta.arr->resize(battle.arena,unsigned(window));for(unsigned i=0;i<unsigned(window);++i)ctx->f__critical_shake_delta.arr->data[i]=V::from_int(i==1?1:0);for(int64_t i:{1,2,3})ctx->f__critical_shake_active.arr->push_back(battle.arena,V::from_int(i));}
        if(mode==31){ctx->f_native_frame_rng=V::from_bool(true);ctx->f_particle_draw_frame=V::from_int(0);ctx->f__particle_before_physics=V::from_int(2);ctx->f__particle_pending_draws=V::from_int(1);for(int64_t i:{1,0,0})ctx->f__particle_draws.arr->push_back(battle.arena,V::from_int(i));}
    }
    uint64_t hash(){Hash h;h.capture(*ctx);h.capture(*combat);h.capture(*rng);for(auto* c:chars)h.capture(*c);for(auto* o:grids)h.capture(*o);for(auto* o:buffs)h.capture(*o);for(auto* o:items)h.capture(*o);for(auto* o:timers)h.capture(*o);for(auto* o:flickers)h.capture(*o);h.word(battle.math_rng.get_state());h.word(util.get_state());return h.value;}
};
int main(int argc,char** argv){
    gd_init_all_classes();auto module=GetModuleHandleA("libgdcore.dll");assert(module);advance=reinterpret_cast<Advance>(GetProcAddress(module,"gd_diag_quiet_core_advance"));
    const bool original_only=argc==2;std::ifstream lengths;if(original_only)lengths.open(argv[1]);else assert(advance);
    fenv_t env;std::fegetenv(&env);auto csr=_mm_getcsr();unsigned cases=0,accepted=0,mismatches=0;std::vector<uint64_t> hashes;std::vector<unsigned> segment_lengths;
    for(auto rounding:{FE_TONEAREST,FE_UPWARD,FE_DOWNWARD,FE_TOWARDZERO})for(unsigned daz=0;daz<4;++daz)
    for(unsigned seed=0;seed<8;++seed)for(unsigned mode=0;mode<42;++mode)for(unsigned available:{1u,2u,3u,4u,8u,9u})for(unsigned preset=0;preset<2;++preset){
        std::fesetround(rounding);_mm_setcsr((_mm_getcsr()&~(0x8040u|0x3fu))|((daz&1)?0x40u:0)|((daz&2)?0x8000u:0));
        Scene candidate(seed,mode);const auto before=candidate.hash();std::feclearexcept(FE_ALL_EXCEPT);if(preset)std::feraiseexcept(FE_INVALID|FE_DIVBYZERO);const auto initial_flags=std::fetestexcept(FE_ALL_EXCEPT);errno=EDOM;
        const auto initial_csr=_mm_getcsr();unsigned n=0;
        if(original_only){lengths>>n;assert(lengths.good());const auto delta=V::from_float(0.01666666753590107);for(unsigned i=0;i<n;++i)candidate.combat->fn_physicsTick(&delta,1);}
        else n=advance(candidate.combat,candidate.ctx,available,nullptr);
        const auto candidate_flags=std::fetestexcept(FE_ALL_EXCEPT);const auto candidate_csr=_mm_getcsr();const auto candidate_errno=errno;const auto actual=candidate.hash();
        if(n&&!original_only){++accepted;Scene original(seed,mode);std::feclearexcept(FE_ALL_EXCEPT);_mm_setcsr(initial_csr);errno=EDOM;const auto delta=V::from_float(0.01666666753590107);
            if(preset)std::feraiseexcept(FE_INVALID|FE_DIVBYZERO);for(unsigned i=0;i<n;++i)original.combat->fn_physicsTick(&delta,1);
            const auto original_flags=std::fetestexcept(FE_ALL_EXCEPT);const auto original_csr=_mm_getcsr();const auto original_errno=errno;const auto expected=original.hash();
            if(actual!=expected||candidate_flags!=original_flags||candidate_csr!=original_csr||candidate_errno!=original_errno){std::cerr<<"Mismatch seed="<<seed<<" mode="<<mode<<" available="<<available<<" n="<<n<<" state="<<(actual==expected)<<" flags="<<candidate_flags<<','<<original_flags<<" csr="<<candidate_csr<<','<<original_csr<<" errno="<<candidate_errno<<','<<original_errno<<'\n';++mismatches;}
        }else if(!n){assert(before==actual);assert(candidate_csr==initial_csr);assert(candidate_flags==initial_flags);assert(candidate_errno==EDOM);}else ++accepted;
        Hash h;h.word(actual);h.word(n);h.word(candidate_flags);h.word(candidate_csr);h.word(candidate_errno);hashes.push_back(h.value);segment_lengths.push_back(n);++cases;
    }
    std::fesetenv(&env);_mm_setcsr(csr);assert(accepted>=400);
    std::cout<<"{\"diagnostic_only\":true,\"passed\":false,\"cases\":"<<cases<<",\"accepted_segments\":"<<accepted<<",\"hashes\":[";for(unsigned i=0;i<hashes.size();++i){if(i)std::cout<<',';std::cout<<hashes[i];}std::cout<<"],\"lengths\":[";for(unsigned i=0;i<segment_lengths.size();++i){if(i)std::cout<<',';std::cout<<segment_lengths[i];}std::cout<<"]}\n";
return mismatches?2:0;
}
