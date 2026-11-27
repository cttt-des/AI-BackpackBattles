"""Read-only frame eligibility census in a separate, never deployed DLL."""
import ctypes, hashlib, json, os, runpy, shutil, subprocess, sys, tempfile
from pathlib import Path
from concurrent.futures import ThreadPoolExecutor
import psutil
from native_build_storage import isolated_build
from prepare_frame_guard_reuse import STAGE, inventory, sha

WORK=STAGE/'native_perf50/quiet_interval_bundle'
ACCEPTED=STAGE/'native_perf50/frame_guard_reuse_bundle'
SOURCE=WORK/'diagnostic_src'
NAMES=['active_frames','deferred','idle_calls','delayed_calls','motion','player_flickers','opponent_flickers','lib_fires','particle_draws','critical_shake','active_buff_timers','item_timers','idle_rng_due_within4','character_timer_due_within4','fatigue_due_within4','active_gems','quiet_external_queues','quiet_external_and_no_timers','quiet_all_static_guards','quiet_streak4_frames','active_item_visits','active_buff_visits']
NAMES+=['no_item_or_buff_timers','core_event_free1','core_event_free2','core_event_free4','core_event_free8','core_event_free4_no_gems','core_event_free4_empty_libfires']

CPP=r'''
static thread_local uint64_t quiet_counts[32]{};
extern "C" void gd_diag_quiet_reset(){std::memset(quiet_counts,0,sizeof(quiet_counts));}
extern "C" uint64_t gd_diag_quiet_stat(unsigned i){return i<32?quiet_counts[i]:0;}
static void quiet_census(Gd__gd_core__CoreCombat& combat,Gd__gd_core__CoreContext& ctx,unsigned& streak) {
    if(!gd::gd_truth(combat.f_activated)){streak=0;return;}
    const auto csr=_mm_getcsr();fenv_t env;std::feholdexcept(&env);
    ++quiet_counts[0];bool flags[16]{};
    const auto occupied=[](const gd::GdVal& v){return v.kind!=gd::GdVal::Kind::Arr || !v.arr || v.arr->len;};
    flags[0]=occupied(ctx.f__deferred);flags[1]=occupied(ctx.f__idle_frame_calls);
    flags[2]=occupied(ctx.f__timed);flags[3]=occupied(ctx.f__motion_queue);
    flags[4]=occupied(ctx.f__flickers);flags[5]=occupied(ctx.f__opponent_flickers);
    flags[6]=occupied(ctx.f_lib_fires);
    flags[7]=ctx.f__particle_pending_draws.as_int()!=0 || ctx.f__particle_before_physics.as_int()!=0;
    flags[8]=occupied(ctx.f__critical_shake_delta);
    if(ctx.f__critical_shake_active.kind==gd::GdVal::Kind::Arr)
        for(unsigned i=0;i<ctx.f__critical_shake_active.arr->len;++i)flags[8]|=ctx.f__critical_shake_active.arr->data[i].as_int()!=0;
    const auto expires=[](const gd::GdVal& v){double x=v.as_float();for(unsigned k=0;k<4;++k)x=x-0.01666666753590107;return !(x>=0);};
    for(auto* c:{static_cast<Gd__gd_core__CoreCharacter*>(ctx.f_opponent.obj),static_cast<Gd__gd_core__CoreCharacter*>(ctx.f_player.obj)}) {
        for(unsigned i=0;i<c->f_buffs.dict->len;++i){auto* b=static_cast<Gd__gd_core__CoreBuff*>(c->f_buffs.dict->entries[i].val.obj);if(gd::gd_truth(b->f__timer_active)){flags[9]=true;++quiet_counts[21];}}
        flags[11]|=expires(c->f__idle_animation_left);
        flags[12]|=(gd::gd_truth(c->f__tick_timer_active)&&expires(c->f__tick_timer_left)) || (gd::gd_truth(c->f__rage_active)&&expires(c->f__rage_left)) || (gd::gd_truth(c->f__invul_active)&&expires(c->f__invul_left)) || (gd::gd_truth(c->f__autoRage_active)&&expires(c->f__autoRage_left)) || (gd::gd_truth(c->f_stunnedDuration)&&expires(c->f_stunnedDuration));
        auto* items=static_cast<Gd__gd_core__CoreGrid*>(c->f_inventory.obj)->f_items.arr;
        for(unsigned i=0;i<items->len;++i){auto* item=static_cast<Gd__gd_core__CoreItem*>(items->data[i].obj);flags[10]|=item->f_timers.arr->len!=0;if(gd::gd_truth(item->f__cooldown_active))++quiet_counts[20];
            if(item->f_gems.kind==gd::GdVal::Kind::Arr)for(unsigned j=0;j<item->f_gems.arr->len;++j){const auto& v=item->f_gems.arr->data[j];if(v.kind==gd::GdVal::Kind::Obj){auto* gem=static_cast<Gd__gd_core__CoreItem*>(v.obj);flags[10]|=gem->f_timers.arr->len!=0;flags[14]|=gd::gd_truth(gem->f__cooldown_active);}}
        }
    }
    flags[13]=expires(combat.f_fatigue_next_tick);
    for(unsigned i=0;i<15;++i)quiet_counts[i+1]+=flags[i];
    bool external=false;for(unsigned i=0;i<9;++i)external|=flags[i];
    quiet_counts[16]+=!external;quiet_counts[17]+=!external&&!flags[9]&&!flags[10];
    bool any=external;for(unsigned i=9;i<15;++i)any|=flags[i];
    quiet_counts[18]+=!any;streak=any?0:streak+1;if(streak==4){quiet_counts[19]+=4;streak=0;}
    quiet_counts[22]+=!flags[9]&&!flags[10];
    for(unsigned h:{1u,2u,4u,8u}) {
        const auto due=[h](const gd::GdVal& v,bool inclusive=false,double decrement=0.01666666753590107,int64_t first=0,int64_t epoch=0){if(v.kind!=gd::GdVal::Kind::Float)return true;double x=v.f;for(unsigned k=1;k<=h;++k)if(epoch+int64_t(k)>=first){x=x-decrement;if(inclusive?!(x>0):!(x>=0))return true;}return false;};
        bool blocked=due(combat.f_fatigue_next_tick);
        const auto epoch=ctx.f_timer_pass_epoch.as_int();
        for(auto* c:{static_cast<Gd__gd_core__CoreCharacter*>(ctx.f_opponent.obj),static_cast<Gd__gd_core__CoreCharacter*>(ctx.f_player.obj)}) {
            blocked|=(gd::gd_truth(c->f__tick_timer_active)&&due(c->f__tick_timer_left)) || (gd::gd_truth(c->f__rage_active)&&due(c->f__rage_left)) || (gd::gd_truth(c->f__invul_active)&&due(c->f__invul_left)) || (gd::gd_truth(c->f__autoRage_active)&&due(c->f__autoRage_left)) || (c->f_stunnedDuration.as_float()>0&&due(c->f_stunnedDuration,true));
            int64_t stacks[2]{};
            for(unsigned i=0;i<c->f_buffs.dict->len;++i){const auto& e=c->f_buffs.dict->entries[i];auto* b=static_cast<Gd__gd_core__CoreBuff*>(e.val.obj);if(e.key.as_int()==107)stacks[0]=b->f_current.as_int();if(e.key.as_int()==110)stacks[1]=b->f_current.as_int();if(gd::gd_truth(b->f__timer_active))blocked|=due(b->f__timer_left,false,0.01666666753590107,b->f__timer_first_pass.as_int(),epoch);}
            auto* items=static_cast<Gd__gd_core__CoreGrid*>(c->f_inventory.obj)->f_items.arr;
            const auto item_check=[&](Gd__gd_core__CoreItem* item,bool gem){
                for(unsigned j=0;j<item->f_timers.arr->len;++j){auto* t=static_cast<Gd__gd_core__CoreTimer*>(item->f_timers.arr->data[j].obj);if(!gd::gd_truth(t->f__stopped))blocked|=due(t->f__left,false,0.01666666753590107,t->f__first_pass.as_int(),epoch);}
                if(!gd::gd_truth(item->f__cooldown_active)||c->f_stunnedDuration.as_float()>0)return;
                if(gem){blocked=true;return;}
                double speed=1;const auto* a=item->f_statDisplayOverrides.arr;const auto v=a&&a->len>3?a->data[3]:gd::GdVal::null();
                if(!v.is_null()&&gd::gd_truth(v)){if(!v.is_num()){blocked=true;return;}speed=v.as_float();}
                else if(gd::gd_truth(item->f_placed)&&!item->f_character_.is_null()){const auto bonus=item->f_speedScale.as_float()+double(stacks[0]-stacks[1])*0.02;const auto mod=bonus>=0?1+bonus:1/(1-bonus);speed=mod<0.1?0.1:mod>10?10:mod;}
                blocked|=due(item->f_triggerTime,true,0.01666666753590107*speed);
            };
            for(unsigned i=0;i<items->len;++i){auto* item=static_cast<Gd__gd_core__CoreItem*>(items->data[i].obj);item_check(item,false);if(item->f_gems.kind==gd::GdVal::Kind::Arr)for(unsigned j=0;j<item->f_gems.arr->len;++j){const auto& v=item->f_gems.arr->data[j];if(v.kind==gd::GdVal::Kind::Obj)item_check(static_cast<Gd__gd_core__CoreItem*>(v.obj),true);}}
        }
        const unsigned slot=h==1?23:h==2?24:h==4?25:26;quiet_counts[slot]+=!blocked;
        if(h==4){quiet_counts[27]+=!blocked&&!flags[14];quiet_counts[28]+=!blocked&&!flags[6];}
    }
    std::fesetenv(&env);_mm_setcsr(csr);
}
'''

def save(n,v):(WORK/n).write_text(json.dumps(v,indent=2,ensure_ascii=False)+'\n',encoding='utf8')
def prepare():
    assert not SOURCE.exists();WORK.mkdir(parents=True,exist_ok=True)
    shutil.copytree(ACCEPTED/'bundle_src',SOURCE)
    p=SOURCE/'engine_wrapper.cpp';old=p.read_text('utf8');text=old
    text='#include <cfenv>\n#include <xmmintrin.h>\n#include "gen/hdrs/Gd__gd_core__CoreGrid.hpp"\n#include "gen/hdrs/Gd__gd_core__CoreBuff.hpp"\n#include "gen/hdrs/Gd__gd_core__CoreTimer.hpp"\n'+text
    at=text.index('static void run_one_internal(');text=text[:at]+CPP+'\n'+text[at:]
    a='    int32_t ticks = 0;';assert text.count(a)==1;text=text.replace(a,a+'\n    unsigned quiet_streak=0;')
    a='        combat_obj->fn_physicsTick(tick_args, host ? 2 : 1);';assert text.count(a)==1;text=text.replace(a,'        quiet_census(*combat_obj,*ctx_obj,quiet_streak);\n'+a)
    p.write_text(text,encoding='utf8',newline='\n')
    save('diagnostic_source.json',dict(baseline_dll_sha256=sha(ACCEPTED/'bundle.dll'),baseline_source_sha256=inventory(ACCEPTED/'bundle_src'),source_sha256=inventory(SOURCE),only_modified_file='engine_wrapper.cpp',names=NAMES,observational_only=True,no_speed_claim=True,recurrence_and_expiry_prechecks_are_only_census_not_a_correctness_certificate=True))

@isolated_build
def preflight():
    subprocess.run(['D:/mingw64/bin/g++.exe','-std=c++20','-ffp-contract=off','-fsyntax-only',str(SOURCE/'engine_wrapper.cpp')],check=True)

@isolated_build
def build():
    assert not (WORK/'diagnostic.dll').exists();psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    obj=Path(tempfile.mkdtemp(prefix='quiet-census-'))/'objects'
    os.environ.update(NATIVE_SIM_OBJ=str(obj),NATIVE_SIM_CXX='D:/mingw64/bin/g++.exe')
    module=runpy.run_path(str(SOURCE/'build_windows.py'));module['build'].__globals__['ThreadPoolExecutor']=lambda max_workers:ThreadPoolExecutor(max_workers=min(2,max_workers))
    library=module['build']();shutil.move(library,WORK/'diagnostic.dll')
    assert len(list(obj.glob('*.o')))==20
    save('diagnostic_build.json',dict(passed=True,dll_sha256=sha(WORK/'diagnostic.dll'),full20_units=True,max_workers=2,below_normal=True,intermediates=str(obj),no_speed_claim=True))

def inspect():
    from bench_native_corpus import load_simulator,prepare as jobs_for,select_cases,measure
    sim=load_simulator(WORK/'diagnostic.dll');digest=hashlib.sha256();jobs=list(jobs_for(sim,select_cases(200),digest))
    reset=sim.lib.gd_diag_quiet_reset;reset.argtypes=[];reset.restype=None
    stat=sim.lib.gd_diag_quiet_stat;stat.argtypes=[ctypes.c_uint];stat.restype=ctypes.c_uint64
    reset();r=measure(sim,jobs,1,0,continuous=True)
    assert digest.hexdigest()=='d94b16d42cc88e9a3850a77c9360b9c4c4fdd676cb252e463044a903db2a5fef'
    assert r['results_sha256']=='2e74b45caa87f7ee6ac72ffc35d98cc8db140b47031614d26542e183cef5d2c9'
    counts={n:stat(i) for i,n in enumerate(NAMES)}
    save('diagnostic_counts.json',dict(passed=True,counts=counts,inputs_sha256=digest.hexdigest(),results_sha256=r['results_sha256'],dll_sha256=sha(WORK/'diagnostic.dll'),no_speed_claim=True))
    print(json.dumps(counts,indent=2),flush=True)

if __name__=='__main__':{'prepare':prepare,'preflight':preflight,'build':build,'inspect':inspect}[sys.argv[1]]()
