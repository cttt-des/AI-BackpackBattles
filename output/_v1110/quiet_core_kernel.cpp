// Candidate fragment, inserted into engine_wrapper.cpp by its preparation tool.
// No integer-to-frame-time formula replaces a floating point recurrence.
static thread_local bool quiet_core_enabled=true;
static thread_local uint64_t quiet_core_counts[16]{};
extern "C" void gd_diag_quiet_core_enable(int enabled){quiet_core_enabled=enabled!=0;}
extern "C" uint64_t gd_diag_quiet_core_stat(unsigned i){return i<16?quiet_core_counts[i]:0;}

// The pointer output and scalar input operands are compiler dependencies.
// A bare MXCSR intrinsic does not order otherwise independent FP arithmetic.
// BEGIN_QUIET_FP_BARRIERS
template<class T> static T* quiet_fp_begin(T* pointer) {
    unsigned csr;
    asm volatile("stmxcsr %0" : "=m"(csr) : : "memory");
    csr&=~0x3fu;
    asm volatile("ldmxcsr %1" : "+r"(pointer) : "m"(csr) : "memory");
    return pointer;
}
static unsigned quiet_fp_capture(double first=0.0,double second=0.0) {
    unsigned csr;
    asm volatile("stmxcsr %0" : "=m"(csr) : "x"(first),"x"(second) : "memory");
    return csr&0x3fu;
}
// END_QUIET_FP_BARRIERS

struct QuietCorePlan {
    using V=gd::GdVal;
    static constexpr unsigned width=8,capacity=512;
    struct Lane {
        V* field;
        double initial,increment,limit;
        int64_t first,blocked;
        unsigned mode,expression_flags; // 0 subtract, 1 stamina clamp, 2 add, 3 end-time bound.
        bool inclusive;
        double values[width];
    };
    Lane lanes[capacity];uintptr_t unique[1024]{};unsigned count=0,horizon=width;
    unsigned flags[width]{};
    int64_t epoch=0,frame=0,masks[2]{};
    Gd__gd_core__CoreCharacter* chars[2]{};
    static bool number(const V& v){return v.kind==V::Kind::Float&&std::isfinite(v.f);}
    static bool boolean(const V& v){return v.kind==V::Kind::Bool;}
    static bool integer(const V& v){return v.kind==V::Kind::Int;}
    template<class T> static bool exact(const gd::GdObj* o){return o&&typeid(*o)==typeid(T);}
    static bool array(const V& v){return v.kind==V::Kind::Arr&&v.arr;}
    static bool empty(const V& v){return array(v)&&v.arr->len==0;}
    bool add(V& v,double increment,unsigned mode=0,bool inclusive=false,
             int64_t first=INT64_MIN,int64_t blocked=INT64_MIN,double limit=0,unsigned expression_flags=0) {
        if(count==capacity||!number(v)||!std::isfinite(increment)||!std::isfinite(limit))return false;
        // A segment shorter than two frames cannot pay for its certificate.
        // Reject it before validating the remainder of the object graph.
        if(mode==0||mode==3){double x=v.f;for(unsigned n=0;n<2;++n){
            if(epoch+int64_t(n)+1>=first&&epoch+int64_t(n)+1!=blocked){
                x=mode==3?x+increment:x-increment;
                if(mode==0&&(inclusive?!(x>0):!(x>=0)))return false;
                if(mode==3&&x>limit)return false;
            }
        }}
        // Reject aliases rather than silently double-materializing one slot.
        const auto address=reinterpret_cast<uintptr_t>(&v);unsigned slot=unsigned((address>>3)*11400714819323198485ull)>>22;
        slot&=1023;while(unique[slot]){if(unique[slot]==address)return false;slot=(slot+1)&1023;}unique[slot]=address;
        lanes[count++]={&v,v.f,increment,limit,first,blocked,mode,expression_flags,inclusive,{}};return true;
    }
    bool timer_item(Gd__gd_core__CoreItem& item,Gd__gd_core__CoreContext& ctx) {
        if(item.f_ctx.obj!=&ctx||!array(item.f_timers))return false;
        for(unsigned i=0;i<item.f_timers.arr->len;++i){
            const auto& v=item.f_timers.arr->data[i];
            if(v.kind!=V::Kind::Obj||!exact<Gd__gd_core__CoreTimer>(v.obj))return false;
            auto* t=static_cast<Gd__gd_core__CoreTimer*>(v.obj);
            if(!boolean(t->f__stopped)||!integer(t->f__first_pass)||t->f__ctx.obj!=&ctx)return false;
            if(!t->f__stopped.b&&!add(t->f__left,0.01666666753590107,0,false,t->f__first_pass.i))return false;
        }return true;
    }
    bool character(Gd__gd_core__CoreCharacter& c,Gd__gd_core__CoreContext& ctx,unsigned side) {
        if(c.rt_ctx_!=ctx.rt_ctx_||c.f_ctx.obj!=&ctx||!number(c.f_stunnedDuration))return false;
        const bool stunned=c.f_stunnedDuration.f>0;
        if(stunned&&!add(c.f_stunnedDuration,0.01666666753590107,0,true))return false;
        if(!number(c.f_staminaRegen)||!number(c.f_maxStamina)||!number(c.f_temporaryMaxStamina))return false;
        const auto* stamina_source=quiet_fp_begin(&c);
        const auto regen=stamina_source->f_staminaRegen.f*0.01666666753590107;const auto stamina_limit=stamina_source->f_maxStamina.f+stamina_source->f_temporaryMaxStamina.f;
        const auto stamina_flags=quiet_fp_capture(regen,stamina_limit);
        if(!add(c.f_curStamina,regen,1,false,INT64_MIN,INT64_MIN,stamina_limit,stamina_flags))return false;
        V* active[]={&c.f__tick_timer_active,&c.f__rage_active,&c.f__invul_active,&c.f__autoRage_active};
        V* left[]={&c.f__tick_timer_left,&c.f__rage_left,&c.f__invul_left,&c.f__autoRage_left};
        for(unsigned i=0;i<4;++i){if(!boolean(*active[i]))return false;if(active[i]->b){masks[side]|=int64_t(1)<<i;if(!add(*left[i],0.01666666753590107))return false;}}
        if(c.f_buffs.kind!=V::Kind::Dict||!c.f_buffs.dict)return false;
        int64_t stacks[2]{};
        for(unsigned i=0;i<c.f_buffs.dict->len;++i){const auto& e=c.f_buffs.dict->entries[i];
            if(e.val.kind!=V::Kind::Obj||!exact<Gd__gd_core__CoreBuff>(e.val.obj))return false;
            auto* b=static_cast<Gd__gd_core__CoreBuff*>(e.val.obj);
            if(b->f_ctx.obj!=&ctx||!boolean(b->f__timer_active)||!integer(b->f__timer_first_pass))return false;
            if(b->f__timer_active.b&&!add(b->f__timer_left,0.01666666753590107,0,false,b->f__timer_first_pass.i))return false;
            if(!integer(e.key))return false;
            if(e.key.i==107||e.key.i==110){if(!integer(b->f_current))return false;stacks[e.key.i==110]=b->f_current.i;}
        }
        // Bound the integer difference before using the original arithmetic.
        if(stacks[0]<-1000000000||stacks[0]>1000000000||stacks[1]<-1000000000||stacks[1]>1000000000)return false;
        const auto* stack_source=quiet_fp_begin(stacks);
        const double bonus=static_cast<double>(stack_source[0]-stack_source[1])*0.02;const auto bonus_flags=quiet_fp_capture(bonus);
        if(c.f_inventory.kind!=V::Kind::Obj||!exact<Gd__gd_core__CoreGrid>(c.f_inventory.obj))return false;
        const auto* grid=static_cast<Gd__gd_core__CoreGrid*>(c.f_inventory.obj);
        if(!array(grid->f_items))return false;
        const auto check_item=[&](Gd__gd_core__CoreItem& item,bool gem){
            if(!timer_item(item,ctx)||!boolean(item.f__cooldown_active))return false;
            if(!item.f__cooldown_active.b)return true;
            if(gem||item.f_character_.obj!=&c||!integer(item.f__cooldown_blocked_epoch))return false;
            const auto* row=item.native_call_row_;
            if(!row||!row->metadata||(row->type_mask&1))return false; // RTTI row proof was already checked at entry.
            if(stunned)return true;
            if(!array(item.f_statDisplayOverrides)||!boolean(item.f_placed))return false;
            const auto* speed_source=quiet_fp_begin(&item);
            const auto* a=speed_source->f_statDisplayOverrides.arr;
            const auto v=a->len>3?a->data[3]:V::null();double speed=1;unsigned speed_flags=0;
            if(!v.is_null()&&gd::native_scalar_truth(v)){
                if(!v.is_num())return false;speed=v.as_float();
            }else if(speed_source->f_placed.b){
                if(!number(speed_source->f_speedScale))return false;
                const auto b=speed_source->f_speedScale.f+bonus;const auto m=b>=0?1+b:1/(1-b);
                speed=m<0.1?0.1:m>10?10:m;
                speed_flags|=bonus_flags;
            }
            const auto decrement=0.01666666753590107*speed;speed_flags|=quiet_fp_capture(decrement);
            return add(item.f_triggerTime,decrement,0,true,INT64_MIN,item.f__cooldown_blocked_epoch.i,0,speed_flags);
        };
        for(unsigned i=0;i<grid->f_items.arr->len;++i){const auto& v=grid->f_items.arr->data[i];
            if(v.kind!=V::Kind::Obj||!v.obj||!v.obj->native_call_row_||!v.obj->native_call_row_->metadata||!gd::native_resolved_row_matches(v.obj,v.obj->native_call_row_))return false;
            auto* item=dynamic_cast<Gd__gd_core__CoreItem*>(v.obj);
            if(!item||!check_item(*item,false)||!array(item->f_gems))return false;
            for(unsigned j=0;j<item->f_gems.arr->len;++j){const auto& g=item->f_gems.arr->data[j];if(g.is_null())continue;
                if(g.kind!=V::Kind::Obj||!g.obj||!g.obj->native_call_row_||!g.obj->native_call_row_->metadata||!gd::native_resolved_row_matches(g.obj,g.obj->native_call_row_))return false;
                auto* gem=dynamic_cast<Gd__gd_core__CoreItem*>(g.obj);if(!gem||!check_item(*gem,true))return false;
            }
        }return true;
    }
    bool tail(Gd__gd_core__CoreContext& ctx) {
        if(!empty(ctx.f__deferred)||!empty(ctx.f__idle_frame_calls)||!empty(ctx.f_lib_fires)||!array(ctx.f__timed)||!array(ctx.f__motion_queue))return false;
        // Unknown delayed calls are harmless only before their original due frame.
        for(unsigned i=0;i<ctx.f__timed.arr->len;++i){const auto& v=ctx.f__timed.arr->data[i];
            if(!array(v)||v.arr->len<4||!number(v.arr->data[2]))return false;
            double x=v.arr->data[2].f;
            for(unsigned n=0;n<horizon;++n){x=static_cast<double>(static_cast<float>(x-0.01666666753590107));if(x<0){horizon=n;break;}}
        }
        for(const V* list:{&ctx.f__opponent_flickers,&ctx.f__flickers}){
            if(!array(*list))return false;
            for(unsigned i=0;i<list->arr->len;++i){const auto& v=list->arr->data[i];
                if(v.kind!=V::Kind::Obj||!exact<Gd__gd_core__CoreContext__INNER__NativeFlicker>(v.obj))return false;
                auto* f=static_cast<Gd__gd_core__CoreContext__INNER__NativeFlicker*>(v.obj);
                if(f->f_ctx.obj!=&ctx||!boolean(f->f_playing)||!boolean(f->f_inside_tree)||!number(f->f_position)||!number(f->f_speed)||!number(f->f_length))return false;
                if(!gd::native_resolved_row_matches(f,f->native_call_row_))return false;
                if(f->f_playing.b&&f->f_inside_tree.b){double x=f->f_position.f;
                    for(unsigned n=0;n<horizon;++n){const double inc=static_cast<double>(static_cast<float>(0.01666666753590107*f->f_speed.f));x=static_cast<double>(static_cast<float>(x+inc));if(x>=f->f_length.f){horizon=n;break;}}
                }
            }
        }
        // Character visual interpolation has no gameplay callback. Charge paths do.
        for(unsigned i=0;i<ctx.f__motion_queue.arr->len;++i){const auto& v=ctx.f__motion_queue.arr->data[i];
            if(!array(v)||v.arr->len<3||!integer(v.arr->data[0])||v.arr->data[0].i!=0)return false;
            const auto& receiver=v.arr->data[1];if(receiver.kind!=V::Kind::Obj||(receiver.obj!=chars[0]&&receiver.obj!=chars[1]))return false;
            if(!gd::native_resolved_row_matches(receiver.obj,receiver.obj->native_call_row_))return false;
        }
        return true;
    }
    bool prepare(Gd__gd_core__CoreCombat& combat,Gd__gd_core__CoreContext& ctx,unsigned available) {
        horizon=std::min(width,available);
        if(!quiet_core_enabled||horizon<2||!ctx.rt_ctx_->native_event_kernel||!ctx.rt_ctx_->native_resolved_dispatch||ctx.rt_ctx_->native_resolved_collect||ctx.rt_ctx_->native_event_audit||ctx.rt_ctx_->native_resolved_audit)return false;
        const auto& watch=ctx.rt_ctx_->native_timer_watch;
        if(!watch.enabled||!watch.closed_world||!watch.usable||watch.depth)return false;
        if(typeid(combat)!=typeid(Gd__gd_core__CoreCombat)||typeid(ctx)!=typeid(Gd__gd_core__CoreContext)||combat.f_ctx.obj!=&ctx||combat.f_player.obj!=ctx.f_player.obj||combat.f_opponent.obj!=ctx.f_opponent.obj)return false;
        if(!boolean(combat.f_fight_ended)||combat.f_fight_ended.b||!boolean(ctx.f_fight_ended)||ctx.f_fight_ended.b||!boolean(ctx.f_native_frame_rng))return false;
        if(!boolean(combat.f_activated)||!combat.f_activated.b||!boolean(combat.f__pending_deferred)||combat.f__pending_deferred.b||!boolean(combat.f__track_hidden_log)||combat.f__track_hidden_log.b)return false;
        if(!boolean(ctx.f_show_cooldown_progress)||ctx.f_show_cooldown_progress.b||!boolean(ctx.f_deferred_flush_enabled)||!ctx.f_deferred_flush_enabled.b||!boolean(ctx.f_replay_native_scene_delays)||!ctx.f_replay_native_scene_delays.b)return false;
        if(!integer(ctx.f_timer_pass_epoch)||!integer(ctx.f_frame_counter)||!number(combat.f_max_time))return false;
        epoch=ctx.f_timer_pass_epoch.i;frame=ctx.f_frame_counter.i;
        if(epoch<0||frame<0||epoch>INT64_MAX-16||frame>INT64_MAX-16)return false;
        if(ctx.f_rng.kind!=V::Kind::Obj||!exact<Gd__gd_core__CoreRng>(ctx.f_rng.obj))return false;
        auto* rng=static_cast<Gd__gd_core__CoreRng*>(ctx.f_rng.obj);
        if(!boolean(rng->f_oracle_trace)||rng->f_oracle_trace.b||!integer(rng->f_draw_seq)||rng->f_draw_seq.i>=0||rng->f_rng.kind!=V::Kind::Rng||!rng->f_rng.rng)return false;
        if(ctx.f_opponent.kind!=V::Kind::Obj||ctx.f_player.kind!=V::Kind::Obj||ctx.f_opponent.obj==ctx.f_player.obj)return false;
        chars[0]=static_cast<Gd__gd_core__CoreCharacter*>(ctx.f_opponent.obj);chars[1]=static_cast<Gd__gd_core__CoreCharacter*>(ctx.f_player.obj);
        if(!exact<Gd__gd_core__CoreCharacter>(chars[0])||!exact<Gd__gd_core__CoreCharacter>(chars[1]))return false;
        if(!tail(ctx)||horizon<2||!add(combat.f_fatigue_next_tick,0.01666666753590107)||!add(ctx.f_time,0.01666666753590107,2)||!add(combat.f_combat_time,0.01666666753590107,3,false,INT64_MIN,INT64_MIN,combat.f_max_time.f)||!character(*chars[0],ctx,0)||!character(*chars[1],ctx,1))return false;
        for(unsigned n=0;n<horizon;++n){
            auto* frame_lanes=quiet_fp_begin(lanes);unsigned expression_flags=0;
            for(unsigned i=0;i<count;++i){auto& l=frame_lanes[i];double x=n?l.values[n-1]:l.initial;
                if(epoch+int64_t(n)+1>=l.first&&epoch+int64_t(n)+1!=l.blocked){
                    expression_flags|=l.expression_flags;
                    if(l.mode==1){x=x+l.increment;x=x<0?0:x>l.limit?l.limit:x;}
                    else if(l.mode>=2)x=x+l.increment;else x=x-l.increment;
                    if(l.mode==0&&(l.inclusive?!(x>0):!(x>=0))){horizon=n;return horizon>=2;}
                    if(l.mode==3&&x>l.limit){horizon=n;return horizon>=2;}
                }l.values[n]=x;
            }flags[n]=quiet_fp_capture()|expression_flags;
        }return true;
    }
    void commit(Gd__gd_core__CoreCombat& combat,Gd__gd_core__CoreContext& ctx,unsigned n) {
        for(unsigned i=0;i<count;++i)*lanes[i].field=V::from_float(lanes[i].values[n]);
        chars[0]->f__physics_timer_mask=V::from_int(masks[0]);chars[1]->f__physics_timer_mask=V::from_int(masks[1]);
        ctx.f_timer_pass_epoch=V::from_int(epoch+n+1);ctx.f_frame_counter=V::from_int(frame+n+1);
        ctx.f_in_physics_timer_pass=V::from_bool(false);ctx.f_in_item_physics_pass=V::from_bool(false);
        ctx.f_combat_time=combat.f_combat_time;
        _mm_setcsr(_mm_getcsr()|flags[n]);
    }
};

extern "C" unsigned gd_diag_quiet_core_advance(Gd__gd_core__CoreCombat* combat,
    Gd__gd_core__CoreContext* ctx,unsigned available,ReplayHostRng* host) {
    if(!quiet_core_enabled||available<2||!QuietCorePlan::boolean(combat->f_activated)||!combat->f_activated.b||ctx->rt_ctx_->native_resolved_collect)return 0;
    const auto csr=_mm_getcsr();
    // Other FP modes retain the original complete frame implementation.
    if((csr&(0x6000u|0x8040u|0x1f80u))!=0x1f80u||std::fegetround()!=FE_TONEAREST)return 0;
    ++quiet_core_counts[0];
    fenv_t env;std::fegetenv(&env);
    QuietCorePlan plan;const bool valid=plan.prepare(*combat,*ctx,available);
    std::fesetenv(&env);_mm_setcsr(csr);
    if(!valid){++quiet_core_counts[1];return 0;}
    ++quiet_core_counts[2];quiet_core_counts[3]+=plan.horizon;quiet_core_counts[4]+=plan.count;
    const auto delta=gd::GdVal::from_float(0.01666666753590107);
    for(unsigned n=0;n<plan.horizon;++n){
        if(gd::native_scalar_truth(ctx->f_native_frame_rng))ctx->fn_beginCriticalShakeFrame(nullptr,0);
        plan.commit(*combat,*ctx,n);
        ctx->fn_flushDeferred(nullptr,0);ctx->fn_flushIdleFrameCalls(nullptr,0);
        if(host)apply_host_draws(*host,*ctx,combat->f_combat_time.as_float(),0);
        combat->fn_stepCharacterIdle(&delta,1);
        ctx->fn_flushDeferred(nullptr,0);
        ctx->fn_lib_fires_tick(&delta,1);ctx->fn__flushTimed(nullptr,0);ctx->fn_tickMotion(&delta,1);
        ctx->fn_flushDeferred(nullptr,0);
        if(host)apply_host_draws(*host,*ctx,combat->f_combat_time.as_float(),1);
    }
    return plan.horizon;
}
