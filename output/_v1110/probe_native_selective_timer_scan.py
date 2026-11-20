"""Measure sparse-timer opportunities using only relevant array invalidations."""
import argparse
import ctypes
import hashlib
import json
from pathlib import Path
import re

from bench_native_corpus import STAGE, load_simulator, measure, prepare, select_cases
from optimize_native_inline_timers import FLAG as INLINE_FLAG, NEW_ASSIGN
from optimize_native_serial_paths import method_body

DECLARATIONS = '''
uint64_t native_timer_scan_epoch();
uint64_t native_timer_scan_mutations();
uint64_t native_timer_scan_assignments();
void native_timer_scan_mutated(const GdArr* array);
void native_timer_scan_mark(BattleCtx& context, const GdVal& value);
'''
RUNTIME = '''
namespace {
thread_local uint64_t native_scan_epoch=1;
thread_local uint64_t native_scan_mutations=0;
thread_local uint64_t native_scan_assignments=0;
void advance_native_scan_epoch() {
    if (native_scan_epoch != UINT64_MAX) ++native_scan_epoch;
}
}
uint64_t native_timer_scan_epoch() { return native_scan_epoch; }
uint64_t native_timer_scan_mutations() { return native_scan_mutations; }
uint64_t native_timer_scan_assignments() { return native_scan_assignments; }
void native_timer_scan_mutated(const GdArr* array) {
    if (array && array->native_timer_scan_tracked) {
        ++native_scan_mutations;
        advance_native_scan_epoch();
    }
}
void native_timer_scan_mark(BattleCtx& context, const GdVal& value) {
    if (!context.native_sparse_timer_scans) return;
    if (value.kind == GdVal::Kind::Arr && value.arr) value.arr->native_timer_scan_tracked=true;
    ++native_scan_assignments;
    advance_native_scan_epoch();
}
'''
PROBE = '''
namespace {
thread_local uint64_t selective_timer_counts[9]{};
struct NativeTimerCheckpoint {
    const void* character=nullptr;
    const void* items=nullptr;
    uint64_t epoch=0;
    uint32_t length=0;
};
thread_local NativeTimerCheckpoint selective_timer_checkpoints[2];
thread_local uint64_t selective_mutation_start=0, selective_assignment_start=0;
void selective_timer_new_combat() {
    for(auto& row:selective_timer_checkpoints) row={};
}
void selective_timer_visit(gd::BattleCtx& battle, const void* character, const gd::GdArr* items) {
    if(!battle.native_sparse_timer_scans) return;
    if(!items->native_timer_scan_tracked)
        gd::native_timer_scan_mark(battle,gd::GdVal::from_arr(const_cast<gd::GdArr*>(items)));
    const auto epoch=gd::native_timer_scan_epoch();
    auto* checkpoint=&selective_timer_checkpoints[0];
    for(auto& row:selective_timer_checkpoints) {
        if(!row.character || row.character==character) {checkpoint=&row;break;}
    }
    ++selective_timer_counts[0];
    selective_timer_counts[1] += checkpoint->character==character && checkpoint->items==items &&
        checkpoint->length==items->len && checkpoint->epoch==epoch && epoch!=UINT64_MAX;
    *checkpoint={character,items,epoch,items->len};
    for(uint32_t i=0;i<items->len;++i) {
        ++selective_timer_counts[2];
        const auto* item=static_cast<const Gd__gd_core__CoreItem*>(items->data[i].obj);
        const bool own=item->f_timers.arr->len!=0;
        selective_timer_counts[3] += own;
        bool gem_timer=false;
        const auto* gems=item->f_gems.arr;
        selective_timer_counts[5] += gems->len;
        for(uint32_t j=0;j<gems->len;++j) {
            const auto& gem=gems->data[j];
            if(gem.kind==gd::GdVal::Kind::Obj && gem.obj) {
                ++selective_timer_counts[6];
                const bool has=static_cast<const Gd__gd_core__CoreItem*>(gem.obj)->f_timers.arr->len!=0;
                selective_timer_counts[7] += has;
                gem_timer |= has;
            }
        }
        selective_timer_counts[4] += own || gem_timer;
    }
}
void selective_timer_after(uint64_t before) {
    selective_timer_counts[8] += gd::native_timer_scan_epoch()!=before;
}
}
extern "C" uint64_t gd_sim_selective_timer_stat(unsigned index) {
    if(index<9) return selective_timer_counts[index];
    if(index==9) return gd::native_timer_scan_mutations()-selective_mutation_start;
    if(index==10) return gd::native_timer_scan_assignments()-selective_assignment_start;
    return 0;
}
extern "C" void gd_sim_selective_timer_reset() {
    for(auto& value:selective_timer_counts) value=0;
    selective_timer_new_combat();
    selective_mutation_start=gd::native_timer_scan_mutations();
    selective_assignment_start=gd::native_timer_scan_assignments();
}
'''


def replace_one(source, old, new):
    if source.count(old) != 1:
        raise ValueError(f"Expected one anchor: {old[:100]}")
    return source.replace(old, new, 1)


def instrument(native):
    runtime_header=native/"gd_rt.hpp"
    header=runtime_header.read_text("utf8")
    if "native_sparse_timer_scans" in header:
        raise ValueError("Use fresh verified sources for this diagnostic")
    header=replace_one(header,"    bool is_pool_real = false;\n",
                       "    bool is_pool_real = false;\n    bool native_timer_scan_tracked = false;\n")
    header=replace_one(header,INLINE_FLAG,"    bool native_sparse_timer_scans = false;\n\n"+INLINE_FLAG)
    header=replace_one(header,"        native_inline_timer_headers = false;\n",
                       "        native_inline_timer_headers = false;\n        native_sparse_timer_scans = false;\n")
    header=replace_one(header,"// Uniform Variant property / subscript / call helpers\n",
                       DECLARATIONS+"\n// Uniform Variant property / subscript / call helpers\n")
    runtime_header.write_text(header,encoding="utf8",newline="\n")

    runtime=native/"gd_rt.cpp";source=runtime.read_text("utf8")
    source=replace_one(source,"GdArr* GdArr::create(BattleArena& arena, uint32_t reserve_cap) {",
                       RUNTIME+"\nGdArr* GdArr::create(BattleArena& arena, uint32_t reserve_cap) {")
    for method in ("push_back","insert_at","pop_at","append_array","pop_front","pop_back",
                   "remove_at","erase_val","resize","fill","invert","set_idx"):
        source,count=re.subn(rf"^((?:void|GdVal) GdArr::{method}\([^\n]*\{{)\n",
                             r"\1\n    native_timer_scan_mutated(this);\n",source,flags=re.M)
        if count!=1:raise ValueError(f"Unexpected array mutation method: {method}")
    source=replace_one(source,"case SYM_clear: a->len = 0;",
                       "case SYM_clear: native_timer_scan_mutated(a); a->len = 0;")
    source=replace_one(source,"case SYM_shuffle:\n",
                       "case SYM_shuffle:\n                    native_timer_scan_mutated(a);\n")
    source=replace_one(source,"case SYM_sort_custom:\n",
                       "case SYM_sort_custom:\n                    native_timer_scan_mutated(a);\n")
    runtime.write_text(source,encoding="utf8",newline="\n")

    item=native/"gen/shards/shard_00.cpp";source=item.read_text("utf8")
    gems="    this->f_gems = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));\n"
    source=replace_one(source,gems,gems+"    gd::native_timer_scan_mark(gd_ctx,this->f_gems);\n")
    source=replace_one(source,NEW_ASSIGN,NEW_ASSIGN+"    gd::native_timer_scan_mark(gd_ctx,this->f_timers);\n")
    for field,symbol in (("gems","SYM_GEN_gems_41"),("timers","SYM_GEN_timers_67")):
        old=f"case {symbol}: this->f_{field} = val; return true;"
        new=f"case {symbol}: this->f_{field} = val; gd::native_timer_scan_mark(gd_ctx,this->f_{field}); return true;"
        source=replace_one(source,old,new)
    item.write_text(source,encoding="utf8",newline="\n")

    wrapper=native/"engine_wrapper.cpp";source=wrapper.read_text("utf8")
    source=replace_one(source,"    battle.native_inline_timer_headers = true;\n",
                       "    battle.native_inline_timer_headers = true;\n    battle.native_sparse_timer_scans = true;\n")
    gems="    ci->f_gems = gd::GdVal::from_arr(gems_arr);\n"
    source=replace_one(source,gems,gems+"    gd::native_timer_scan_mark(battle,ci->f_gems);\n")
    wrapper.write_text(source,encoding="utf8",newline="\n")

    combat=native/"gen/shards/shard_03.cpp";source=combat.read_text("utf8")
    init="void Gd__gd_core__CoreCombat::init_fields(gd::BattleCtx& gd_ctx) {\n"
    source=replace_one(source,init,init+"    selective_timer_new_combat();\n")
    begin="    const auto* items = inventory->f_items.arr;\n"
    source=replace_one(source,begin,begin+"    selective_timer_visit(*this->rt_ctx_,character,items);\n"
                       "    const auto selective_before=gd::native_timer_scan_epoch();\n")
    method=method_body(source,"CoreCombat","_tickCharacterTimers")
    body=replace_one(method[0],"    return gd::GdVal::null();\n",
                     "    selective_timer_after(selective_before);\n    return gd::GdVal::null();\n")
    source=source[:method.start()]+body+source[method.end():]
    source=('#include "../../gd_rt.hpp"\n#include "../hdrs/Gd__gd_core__CoreItem.hpp"\n'+PROBE+source)
    combat.write_text(source,encoding="utf8",newline="\n")
    print("Tracking only timer/gem/inventory arrays and all verified timer/gem field assignments",flush=True)


def inspect(dll,out):
    sim=load_simulator(dll);signature=hashlib.sha256()
    jobs=list(prepare(sim,select_cases(200),signature))
    reset=sim.lib.gd_sim_selective_timer_reset;reset.argtypes=[];reset.restype=None
    read=sim.lib.gd_sim_selective_timer_stat;read.argtypes=[ctypes.c_uint];read.restype=ctypes.c_uint64
    reset();result=measure(sim,jobs,1,0,continuous=True)
    reference=json.loads((STAGE/"native_perf50_event_bus_serial.json").read_bytes())
    assert signature.hexdigest()==reference["inputs_sha256"] and result["results_sha256"]==reference["results_sha256"]
    names=("character_passes","reusable_epoch_passes","parent_visits","parents_with_own_timers",
           "parents_with_any_timers","socket_visits","nonnull_gems","gems_with_timers",
           "passes_with_midpass_mutation","watched_mutator_entries","watched_field_assignments")
    values=dict(zip(names,(read(i) for i in range(len(names))),strict=True))
    report={"diagnostic_only":True,"dll_sha256":hashlib.sha256(dll.read_bytes()).hexdigest(),
            "inputs_sha256":signature.hexdigest(),"results_sha256":result["results_sha256"],"counts":values,
            "epoch_reuse_fraction":values["reusable_epoch_passes"]/values["character_passes"],
            "parent_eligible_fraction":values["parents_with_any_timers"]/values["parent_visits"],
            "scope":"12 array mutator entries, clear/shuffle/sort_custom, timer/gem init and setters, final gem assembly; captured inventory arrays are marked at phase entry"}
    out.write_text(json.dumps(report,indent=2)+"\n",encoding="utf8");print(json.dumps(report,indent=2))


if __name__=="__main__":
    parser=argparse.ArgumentParser(description=__doc__)
    mode=parser.add_mutually_exclusive_group(required=True)
    mode.add_argument("--instrument",type=Path);mode.add_argument("--dll",type=Path)
    parser.add_argument("--out",type=Path);args=parser.parse_args()
    if args.instrument:instrument(args.instrument)
    elif args.out:inspect(args.dll,args.out)
    else:parser.error("--dll requires --out")
