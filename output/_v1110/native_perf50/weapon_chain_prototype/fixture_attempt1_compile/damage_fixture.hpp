#include "native_event_kernel.hpp"
#include <xmmintrin.h>
static bool chain_closed=false;
static unsigned chain_daz=0;
#include <bit>
#include <cassert>
#include <cfenv>
#include <iostream>
using V=gd::GdVal;
using Character=Gd__gd_core__CoreCharacter;
using Context=Gd__gd_core__CoreContext;
using Source=Gd__gd_core__CoreDamageSource;
using Result=Gd__gd_core__CoreDamageResult;
static uint64_t mix(uint64_t h,uint64_t x){return(h^x)*1099511628211ULL;}
static uint64_t hash(const V& v){uint64_t h=mix(1469598103934665603ULL,unsigned(v.kind));switch(v.kind){
case V::Kind::Null:return h;case V::Kind::Bool:return mix(h,v.b);case V::Kind::Int:return mix(h,uint64_t(v.i));case V::Kind::Float:return mix(h,std::bit_cast<uint64_t>(v.f));
case V::Kind::Vec2:return mix(mix(h,std::bit_cast<uint64_t>(v.v2.x)),std::bit_cast<uint64_t>(v.v2.y));
case V::Kind::Obj:return mix(mix(h,v.obj?v.obj->meta()->id:0),v.obj?v.obj->gid_:0);
case V::Kind::Arr:if(v.arr){h=mix(h,v.arr->len);for(unsigned i=0;i<v.arr->len;++i)h=mix(h,hash(v.arr->data[i]));}return h;
case V::Kind::Dict:if(v.dict){h=mix(h,v.dict->len);for(unsigned i=0;i<v.dict->len;++i){h=mix(h,hash(v.dict->entries[i].key));h=mix(h,hash(v.dict->entries[i].val));}}return h;
case V::Kind::Str:if(v.str){h=mix(h,v.str->len);for(unsigned i=0;i<v.str->len;++i)h=mix(h,(unsigned char)v.str->data[i]);}return h;default:return h;}}
struct Fixture {
    gd::BattleCtx c{65536};Context* ctx;Character* attacker;Character* defender;Source* source;
    explicit Fixture(unsigned scenario){
        c.native_event_kernel=true;c.native_event_audit=true;c.native_resolved_dispatch=true;c.native_resolved_audit=true;
        V seed[]={V::from_int(42)};ctx=static_cast<Context*>(gd::construct_class(c,&META_Gd__gd_core__CoreContext,seed,1).obj);
        V a[]={V::from_obj(ctx),V::from_int(0)},b[]={V::from_obj(ctx),V::from_int(1)};
        attacker=static_cast<Character*>(gd::construct_class(c,&META_Gd__gd_core__CoreCharacter,a,2).obj);
        defender=static_cast<Character*>(gd::construct_class(c,&META_Gd__gd_core__CoreCharacter,b,2).obj);
        ctx->f_player=V::from_obj(attacker);ctx->f_opponent=V::from_obj(defender);
        attacker->f_opponent=V::from_obj(defender);defender->f_opponent=V::from_obj(attacker);
        attacker->f_curHealth=defender->f_curHealth=V::from_float(1000.0);
        ctx->f_native_label_mode=V::from_int(3);ctx->f_label_rng_enabled=V::from_bool(false);
        source=static_cast<Source*>(gd::construct_class(c,&META_Gd__gd_core__CoreDamageSource,nullptr,0).obj);

        source->f_minDamage=V::from_int(5);source->f_maxDamage=V::from_int(10);
        source->f_types=V::from_arr(gd::GdArr::from_init(c.arena,{V::from_int((scenario/64)%7)}));
        source->f_accuracy=V::from_float(73.25);source->f_critChancePercent=V::from_float(38.5);
        source->f_flags=V::from_int(scenario%64);source->f_origin=V::null();
        const V block=V::from_int((scenario%4)*3);defender->fn_setBlock(&block,1);
        defender->f_damageReduction=V::from_float((scenario%3)*2.0);
        defender->f_damageResistance=V::from_float((scenario%5)*.1);
        defender->f_isDead=V::from_bool(scenario%31==0);
        defender->f_invulnerable=V::from_bool(scenario%17==0);
        defender->f_dodgeStacks=V::from_int(scenario%11==0?1:0);
    }
};
