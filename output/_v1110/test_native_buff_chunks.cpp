#include "gen/hdrs/Gd__gd_core__CoreCharacter.hpp"
#include "gen/hdrs/Gd__gd_core__CoreBuff.hpp"
#include "gen/hdrs/Gd__gd_core__CoreContext.hpp"
#include "gen/hdrs/Gd__gd_core__CoreItem.hpp"
#include <cassert>
#include <cstring>
#include <functional>
#include <iostream>
#include <limits>
#include <vector>

using V=gd::GdVal;
using Character=Gd__gd_core__CoreCharacter;
using Buff=Gd__gd_core__CoreBuff;
static uint64_t digest=1469598103934665603ull;
static unsigned cases=0;
static void hash(uint64_t v) {digest^=v;digest*=1099511628211ull;}
static uint64_t bits(double v) {uint64_t x;std::memcpy(&x,&v,8);return x;}

struct CallbackBuff: Buff {
    int id;
    std::vector<int>* trace;
    std::function<void()> callback;
    CallbackBuff(gd::BattleCtx* ctx,int i,std::vector<int>* events):Buff(ctx),id(i),trace(events) {}
    bool call_method(gd::BattleCtx& ctx,gd::SymId method,const V* args,int argc,V& out) override {
        if(method!=SYM_GEN_onTimeout_1035) return Buff::call_method(ctx,method,args,argc,out);
        trace->push_back(id);
        auto cb=std::move(callback);
        if(cb) cb();
        out=V::null();return true;
    }
};

static void reference(Character& character,const V& delta) {
    const auto value=gd::gd_coerce_float(delta);
    const auto* buffs=character.f_buffs.dict;
    const auto* entries=buffs->entries;
    for(uint32_t i=0,count=buffs->len;i<count;++i) {
        auto* buff=static_cast<Buff*>(entries[i].val.obj);
        const auto& active=buff->f__timer_active;
        if(active.kind==V::Kind::Bool ? active.b : gd::gd_truth(active)) buff->fn__tick(&value,1);
    }
}

struct Result {
    std::vector<uint64_t> state;
    std::vector<int> trace;
    bool operator==(const Result&) const=default;
};

static Result run(bool candidate,unsigned n,unsigned mask,int position=-1,int mode=-1,bool native=false) {
    gd::BattleCtx ctx(8192);
    ctx.native_event_kernel=native;
    ctx.native_resolved_dispatch=true;
    Gd__gd_core__CoreContext context(&ctx);context.init_fields(ctx);
    context.f_timer_pass_epoch=V::from_int(1);
    Character character(&ctx);character.init_fields(ctx);
    auto* dict=gd::GdDict::create(ctx.arena);
    character.f_buffs=V::from_dict(dict);
    std::vector<int> trace;
    std::vector<CallbackBuff*> buffs;
    auto make=[&](unsigned id) {
        auto* buff=ctx.arena.make<CallbackBuff>(&ctx,id,&trace);buff->init_fields(ctx);
        buff->f_ctx=V::from_obj(&context);
        buff->f__timer_active=V::from_bool(false);
        buff->f__timer_left=V::from_float(0.125);
        buff->f__timer_first_pass=V::from_int(0);
        buffs.push_back(buff);
        return buff;
    };
    for(unsigned i=0;i<n;++i) {
        auto* buff=make(i);
        buff->f__timer_active=V::from_bool((mask>>(i%8))&1);
        // Native tests do not expire into the real timeout effects.
        if(native)buff->f__timer_left=V::from_float(4.0);
        dict->set(ctx.arena,V::from_int(100+i),V::from_obj(buff));
    }
    if(position>=0) {
        const unsigned p=static_cast<unsigned>(position),q=p+1;
        assert(q<n && !native);
        for(auto* b:buffs)b->f__timer_active=V::from_bool(false);
        buffs[p]->f__timer_active=V::from_bool(true);
        if(mode==1)buffs[q]->f__timer_active=V::from_bool(true);
        if(mode==3)dict->entries[q].val=V::null();
        buffs[p]->callback=[&,p,q] {
            switch(mode) {
                case 0:buffs[q]->f__timer_active=V::from_bool(true);break;
                case 1:buffs[q]->f__timer_active=V::from_bool(false);break;
                case 2:{auto* b=make(buffs.size());b->f__timer_active=V::from_bool(true);dict->entries[q].val=V::from_obj(b);break;}
                case 3:dict->entries[q].val=V::from_obj(buffs[q]);buffs[q]->f__timer_active=V::from_bool(true);break;
                case 4:{
                    auto* entries=dict->entries;
                    dict->erase(V::from_int(100));
                    // Preserve a valid last entry for the original captured length.
                    entries[n-1].val=V::from_obj(buffs[q]);
                    buffs[q]->f__timer_active=V::from_bool(true);
                    break;
                }
                case 5:
                    for(unsigned i=0;i<40;++i){auto* b=make(buffs.size());dict->set(ctx.arena,V::from_int(1000+i),V::from_obj(b));}
                    buffs[q]->f__timer_active=V::from_bool(true);break;
                case 6:character.f_buffs=V::from_dict(gd::GdDict::create(ctx.arena));buffs[q]->f__timer_active=V::from_bool(true);break;
                case 7:buffs[q]->f__timer_active=V::from_float(std::numeric_limits<double>::quiet_NaN());break;
                case 8:{
                    buffs[q]->f__timer_active=V::from_bool(true);
                    const V delta=V::from_float(0.25);
                    if(candidate)character.fn_tickBuffs(&delta,1);else reference(character,delta);
                    break;
                }
                case 9:buffs[0]->f__timer_active=V::from_bool(true);buffs[0]->f__timer_left=V::from_float(0.375);break;
            }
        };
    }
    if(mode==10) {
        for(unsigned i=0;i<n;++i) {
            switch(i%6) {
                case 0:buffs[i]->f__timer_active=V::null();break;
                case 1:buffs[i]->f__timer_active=V::from_int(0);break;
                case 2:buffs[i]->f__timer_active=V::from_int(1);break;
                case 3:buffs[i]->f__timer_active=V::from_float(-0.0);break;
                case 4:buffs[i]->f__timer_active=V::from_float(std::numeric_limits<double>::quiet_NaN());break;
                case 5:buffs[i]->f__timer_active=V::from_bool(false);break;
            }
        }
    }
    const V delta=V::from_float(0.25);
    if(candidate)character.fn_tickBuffs(&delta,1);else reference(character,delta);
    Result out;out.trace=trace;
    for(auto* b:buffs) {
        out.state.push_back(static_cast<unsigned>(b->f__timer_active.kind));
        if(b->f__timer_active.kind==V::Kind::Float)out.state.push_back(bits(b->f__timer_active.f));
        else out.state.push_back(b->f__timer_active.as_int());
        out.state.push_back(bits(b->f__timer_left.as_float()));
    }
    out.state.push_back(character.f_buffs.dict->len);
    for(unsigned i=0;i<character.f_buffs.dict->len;++i) {
        out.state.push_back(character.f_buffs.dict->entries[i].key.as_int());
        out.state.push_back(static_cast<CallbackBuff*>(character.f_buffs.dict->entries[i].val.obj)->id);
    }
    return out;
}

static void check(unsigned n,unsigned mask,int p=-1,int mode=-1,bool native=false) {
    auto old=run(false,n,mask,p,mode,native),next=run(true,n,mask,p,mode,native);
    assert(old==next);
    ++cases;
    hash(n);hash(mask);hash(p+1);hash(mode+1);hash(native);
    for(auto v:next.state)hash(v);
    for(auto v:next.trace)hash(v);
}

static unsigned check_cooldown_flags() {
    gd::BattleCtx ctx(8192);
    Gd__gd_core__CoreContext context(&ctx);context.init_fields(ctx);
    context.f_timer_pass_epoch=V::from_int(1);
    context.f_show_cooldown_progress=V::from_bool(false);
    Gd__gd_core__CoreItem item(&ctx);item.init_fields(ctx);
    item.f_ctx=V::from_obj(&context);
    item.f_placed=V::from_bool(false);
    item.f__cooldown_blocked_epoch=V::from_int(-1);
    item.f_iterationCooldown=V::from_float(10.0);
    auto* arr=gd::GdArr::create(ctx.arena);
    auto* dict=gd::GdDict::create(ctx.arena);
    gd::GdColor zero{0,0,0,0},opaque{0,0,0,1};
    std::vector<V> values={V::null(),V::from_bool(false),V::from_bool(true),
        V::from_int(0),V::from_int(-1),V::from_float(-0.0),V::from_float(0.5),
        V::from_float(std::numeric_limits<double>::quiet_NaN()),
        V::from_cstr(ctx.arena,""),V::from_cstr(ctx.arena,"active"),
        V::from_arr(nullptr),V::from_arr(arr),V::from_dict(nullptr),V::from_dict(dict),
        V::from_color(nullptr),V::from_color(&zero),V::from_color(&opaque),
        V::from_funcref(nullptr),V::from_rng(nullptr),V::from_obj(&context)};
    const V delta=V::from_float(0.25);
    unsigned count=0;
    for(unsigned phase=0;phase<2;++phase) {
        for(const auto& value:values) {
            const bool active=gd::gd_truth(value);
            item.f__cooldown_active=value;item.f_triggerTime=V::from_float(10.0);
            item.fn_physicsTick(&delta,1);
            assert(bits(item.f_triggerTime.as_float())==bits(active?9.75:10.0));
            hash(bits(item.f_triggerTime.as_float()));++count;
        }
        arr->push_back(ctx.arena,V::from_int(1));
        dict->set(ctx.arena,V::from_int(1),V::from_int(1));
    }
    return count;
}

int main() {
    register_gen_syms();
    for(unsigned n=0;n<=33;++n)for(unsigned mask=0;mask<32;++mask)check(n,mask);
    for(unsigned p=0;p<23;++p)for(int mode=0;mode<10;++mode)check(24,0,p,mode);
    for(unsigned n=0;n<=33;++n)check(n,0,-1,10);
    for(unsigned n=0;n<=33;++n)for(unsigned mask=0;mask<8;++mask)check(n,mask,-1,-1,true);
    const auto flags=check_cooldown_flags();
    std::cout<<"{\"cases\":"<<cases<<",\"cooldown_flag_cases\":"<<flags<<",\"state_and_callback_digest\":"<<digest<<"}\n";
}
