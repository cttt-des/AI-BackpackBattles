"""Count existing ordered scans without changing their eligibility decisions."""
import hashlib
import json
from pathlib import Path
import sys
import psutil

psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
WORK=Path(__file__).resolve().parent
STAGE=WORK.parents[1]
sys.path.insert(0,str(STAGE))
import build_native_assembly as trial

def instrument(src):
    path=src/'gen/shards/shard_02.cpp'
    text=path.read_text('utf8')
    anchor='gd::GdVal Gd__gd_core__CoreCharacter::fn_tickBuffs(const gd::GdVal* args, int argc) {'
    assert text.count(anchor)==1
    text=text.replace(anchor,'''static thread_local uint64_t native_scan_counts[12]{};
extern "C" uint64_t gd_diag_native_scan_stat(unsigned index) {
    return index<12 ? native_scan_counts[index] : 0;
}
void native_scan_hit(unsigned index) { ++native_scan_counts[index]; }
'''+anchor,1)
    old='''    for (uint32_t i = 0, count = buffs->len; i < count; ++i) {
        auto* buff = static_cast<Gd__gd_core__CoreBuff*>(entries[i].val.obj);
        const auto& active = buff->f__timer_active;
        if (active.kind == gd::GdVal::Kind::Bool ? active.b : gd::gd_truth(active)) buff->fn__tick(&delta, 1);
    }'''
    new='''    ++native_scan_counts[0];
    unsigned inactive_in_chunk=0;
    for (uint32_t i = 0, count = buffs->len; i < count; ++i) {
        auto* buff = static_cast<Gd__gd_core__CoreBuff*>(entries[i].val.obj);
        const auto& active = buff->f__timer_active;
        ++native_scan_counts[1];
        const bool is_bool=active.kind == gd::GdVal::Kind::Bool;
        const bool ticking=is_bool ? active.b : gd::gd_truth(active);
        if (!is_bool) ++native_scan_counts[3];
        if (is_bool && !active.b) ++inactive_in_chunk;
        if ((i&7u)==7u) {
            ++native_scan_counts[4];
            if(inactive_in_chunk==8) ++native_scan_counts[5];
            inactive_in_chunk=0;
        }
        if (ticking) { ++native_scan_counts[2]; buff->fn__tick(&delta, 1); }
    }'''
    assert text.count(old)==1
    path.write_text(text.replace(old,new,1),encoding='utf8',newline='\n')
    path=src/'gen/shards/shard_03.cpp';text=path.read_text('utf8')
    anchor='gd::GdVal Gd__gd_core__CoreCombat::fn__tickCharacterTimers(const gd::GdVal* args, int argc) {'
    assert text.count(anchor)==1
    text=text.replace(anchor,'void native_scan_hit(unsigned);\n'+anchor,1)
    old='''        if (item->f_timers.arr->len) item->fn__tickTimers(&delta, 1);
        const auto* gems = item->f_gems.arr;
        for (uint32_t j = 0, sockets = gems->len; j < sockets; ++j) {
            const auto& slot = gems->data[j];
            if (slot.kind == gd::GdVal::Kind::Obj && slot.obj) {
                auto* gem = static_cast<Gd__gd_core__CoreItem*>(slot.obj);
                if (gem->f_timers.arr->len) gem->fn__tickTimers(&delta, 1);
            }
        }'''
    new='''        native_scan_hit(6);
        if (item->f_timers.arr->len) { native_scan_hit(7); item->fn__tickTimers(&delta, 1); }
        const auto* gems = item->f_gems.arr;
        for (uint32_t j = 0, sockets = gems->len; j < sockets; ++j) {
            native_scan_hit(8);
            const auto& slot = gems->data[j];
            if (slot.kind == gd::GdVal::Kind::Obj && slot.obj) {
                native_scan_hit(9);
                auto* gem = static_cast<Gd__gd_core__CoreItem*>(slot.obj);
                if (gem->f_timers.arr->len) { native_scan_hit(10); gem->fn__tickTimers(&delta, 1); }
            }
        }'''
    assert text.count(old)==1
    path.write_text(text.replace(old,new,1),encoding='utf8',newline='\n')

def main():
    trial.expected='1be75dced83e9e90fdbe61dd86f91bc27e19bb44acf9449d295849e928d9cec5'
    trial.work=WORK
    trial.base=Path((STAGE/'native_perf50/inline_dispatch_bundle/bundle_objects.txt').read_text('utf8'))
    trial.baseline={unit:trial.base/(unit+'.o') for unit in trial.units}
    assert all(p.is_file() for p in trial.baseline.values())
    before={name:hashlib.sha256(p.read_bytes()).hexdigest() for name,p in trial.baseline.items()}
    dll=trial.build('scan_activity',instrument,probe=True)
    assert before=={name:hashlib.sha256(p.read_bytes()).hexdigest() for name,p in trial.baseline.items()}
    (WORK/'build_provenance.json').write_text(json.dumps({'diagnostic_only':True,
        'baseline_dll_sha256':trial.expected,'diagnostic_dll_sha256':hashlib.sha256(dll.read_bytes()).hexdigest(),
        'recompiled':['shard_02','shard_03'],'baseline_object_sha256':before,
        'formal_timing_forbidden':True},indent=2)+'\n',encoding='utf8')

if __name__=='__main__': main()
