"""Observe actual event-param dictionaries; simulate 2/4/8 entry growth without changing them."""
from concurrent.futures import ThreadPoolExecutor
import ctypes
import hashlib
import json
from pathlib import Path
import runpy
import shutil
import subprocess
import tempfile
import psutil

STAGE = Path(__file__).resolve().parent
BASE = STAGE / 'sim_native/native_sim_cpp/native_sim'
ACCEPTED = STAGE / 'native_perf50/grid_cooldown_bundle'
SEMANTIC = STAGE / 'native_perf50/grid_cooldown_prototype'
WORK = STAGE / 'native_perf50/event_param_capacity_probe'
EXPECTED = 'e0bedc4960077407e85763cb5e4af70175a0623cca15e923403fa89174390687'
FIELDS = ('registration_calls', 'registered_dicts', 'retired_reused_headers', 'final_live_headers',
          'new_keys', 'existing_updates', 'successful_erases', 'clears', 'unexpected_capacity',
          'nonstr_empty_candidates', 'nonempty_candidates', 'ordinary_or_open_candidates')
BINS = ('0', '1', '2', '3', '4', '5_8', '9_16', '17_plus')

# Heap-only metadata. create() retires an address before it can be reused by a
# reset arena. A bind_battle gid epoch alone does not retire still-live headers.
HELPER = r'''
namespace {
struct NativeParamCapacity {
    uint32_t cap[3]{}, peak=0;
    uint64_t allocations[3]{}, slots[3]{}, copies[3]{};
};
static thread_local std::unordered_map<const GdDict*,NativeParamCapacity> native_param_records;
static thread_local uint64_t native_param_counts[47]{};
static unsigned native_param_bin(uint32_t n){return n<=4?n:n<=8?5:n<=16?6:7;}
static void native_param_retire(const NativeParamCapacity& record) {
    ++native_param_counts[12+native_param_bin(record.peak)];
    for(unsigned j=0;j<3;++j) {
        native_param_counts[20+j*3]+=record.allocations[j];
        native_param_counts[21+j*3]+=record.slots[j];
        native_param_counts[22+j*3]+=record.copies[j];
    }
}
static void native_param_created(const GdDict* dict) {
    auto it=native_param_records.find(dict);
    if(it!=native_param_records.end()) {
        native_param_retire(it->second);native_param_records.erase(it);++native_param_counts[2];
    }
}
static void native_param_new(const GdDict* dict) {
    auto it=native_param_records.find(dict);if(it==native_param_records.end())return;
    auto& r=it->second;++native_param_counts[4];
    native_param_counts[8]+=r.cap[2]!=dict->cap;
    r.peak=std::max(r.peak,dict->len+1);
    for(unsigned j=0;j<3;++j) {
        if(dict->len>=r.cap[j]) {
            const uint32_t n=r.cap[j]?r.cap[j]*2:(2u<<j);
            r.cap[j]=n;++r.allocations[j];r.slots[j]+=n;r.copies[j]+=dict->len;
        }
    }
}
static void native_param_existing(const GdDict* d) {
    native_param_counts[5]+=native_param_records.find(d)!=native_param_records.end();
}
static void native_param_erased(const GdDict* d) {
    native_param_counts[6]+=native_param_records.find(d)!=native_param_records.end();
}
static void native_param_cleared(const GdDict* d) {
    native_param_counts[7]+=native_param_records.find(d)!=native_param_records.end();
}
}
void native_event_param_observe(BattleCtx& ctx,const GdVal& value,const GdVal& key) {
    ++native_param_counts[0];
    if(!ctx.native_timer_watch.closed_world || value.kind!=GdVal::Kind::Dict || !value.dict) {
        ++native_param_counts[11];return;
    }
    auto* d=value.dict;
    if(native_param_records.find(d)!=native_param_records.end())return;
    if(key.kind!=GdVal::Kind::Str){++native_param_counts[9];return;}
    if(d->len || d->cap || d->entries || d->buckets || d->bucket_cap) {
        ++native_param_counts[10];return;
    }
    native_param_records.emplace(d,NativeParamCapacity{});++native_param_counts[1];
}
'''


def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def once(text, old, new):
    assert text.count(old) == 1, (old, text.count(old))
    return text.replace(old, new, 1)


def transform(source):
    header = source / 'gd_rt.hpp'
    header.write_text(once(header.read_text('utf8'), 'struct BattleCtx;',
        'struct BattleCtx;\nvoid native_event_param_observe(BattleCtx&,const GdVal&,const GdVal&);'),
        encoding='utf8', newline='\n')
    rt = source / 'gd_rt.cpp'
    text = rt.read_text('utf8')
    text = once(text, 'GdDict* GdDict::create(BattleArena& arena, uint32_t reserve_cap) {',
                HELPER + '\nGdDict* GdDict::create(BattleArena& arena, uint32_t reserve_cap) {')
    text = once(text, '    auto* d = arena.make<GdDict>();',
                '    auto* d = arena.make<GdDict>();\n    native_param_created(d);')
    begin = text.index('void GdDict::set(')
    end = text.index('\n}', begin) + 2
    method = text[begin:end]
    method = once(method, '    if (idx >= 0) {',
                  '    if (idx >= 0) {\n        native_param_existing(this);')
    method = once(method, '    uint32_t grid_slot=0;',
                  '    native_param_new(this);\n    uint32_t grid_slot=0;')
    text = text[:begin] + method + text[end:]
    text = once(text, '    uint32_t ui = static_cast<uint32_t>(idx);',
                '    native_param_erased(this);\n    uint32_t ui = static_cast<uint32_t>(idx);')
    text = once(text, 'void GdDict::clear() {',
                'void GdDict::clear() {\n    native_param_cleared(this);')
    text += r'''
extern "C" uint64_t gd_diag_native_param_capacity(unsigned n) {
    return n<47?gd::native_param_counts[n]:0;
}
extern "C" void gd_diag_native_param_capacity_reset() {
    gd::native_param_records.clear();for(auto& n:gd::native_param_counts)n=0;
}
extern "C" void gd_diag_native_param_capacity_finish() {
    gd::native_param_counts[3]+=gd::native_param_records.size();
    for(const auto& row:gd::native_param_records)gd::native_param_retire(row.second);
    gd::native_param_records.clear();
}
'''
    rt.write_text(text, encoding='utf8', newline='\n')
    shard = source / 'gen/shards/shard_11.cpp'
    text = shard.read_text('utf8')
    begin = text.index('gd::GdVal Gd__gd_core__CoreEvent::fn_setParam(')
    end = text.index('\n}', begin) + 2
    method = text[begin:end]
    method = once(method, '    { gd::GdVal _t1581 = this->f_params;',
                  '    gd::native_event_param_observe(gd_ctx,this->f_params,lv_paramName);\n'
                  '    { gd::GdVal _t1581 = this->f_params;')
    shard.write_text(text[:begin] + method + text[end:], encoding='utf8', newline='\n')


def main():
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    assert sha(BASE / 'libgdcore.dll') == EXPECTED
    verification = json.loads((ACCEPTED / 'post_install_verification.json').read_bytes())
    backup = json.loads((ACCEPTED / 'checkpoint_receipt.json').read_bytes())
    assert verification['passed'] and verification['dll_sha256'] == backup['dll_sha256'] == EXPECTED
    remote = subprocess.check_output(['git','ls-remote','--exit-code','origin',
        'refs/heads/codex/native-perf50-verified']).decode().split()[0]
    assert remote == backup['remote_verified_commit']
    assert not WORK.exists()
    WORK.mkdir()
    shutil.copyfile(__file__, WORK / 'driver_first.py')
    source = WORK / 'diagnostic_src'
    shutil.copytree(BASE, source, ignore=shutil.ignore_patterns('*.dll','*.o','*.gcda','*.gcno','__pycache__'))
    manifest = json.loads((ACCEPTED / 'source_before_build.json').read_bytes())
    before = {p.relative_to(source).as_posix():sha(p) for p in source.rglob('*') if p.is_file()}
    assert before == manifest
    semantic = json.loads((SEMANTIC / 'transform.json').read_bytes())['source_sha256']
    assert semantic == manifest
    transform(source)
    after = {p.relative_to(source).as_posix():sha(p) for p in source.rglob('*') if p.is_file()}
    changed = sorted(n for n in before if before[n] != after[n])
    assert changed == ['gd_rt.cpp','gd_rt.hpp','gen/shards/shard_11.cpp']
    original = Path((SEMANTIC / 'objects.txt').read_text('utf8'))
    objects = Path(tempfile.mkdtemp(prefix='native-event-param-capacity-'))
    (WORK / 'objects.txt').write_text(str(objects), encoding='utf8')
    names = ['gd_rt','engine_wrapper','sym_ids','register_all',*[f'shard_{i:02d}' for i in range(16)]]
    hashes = {n:sha(original/(n+'.o')) for n in names}
    modified = {'gd_rt':source/'gd_rt.cpp', 'shard_11':source/'gen/shards/shard_11.cpp'}
    for name in names:
        if name not in modified:
            shutil.copyfile(original/(name+'.o'),objects/(name+'.o'))
    flags = runpy.run_path(str(source/'build_windows.py'))['COMMON']
    assert not any('lto' in f for f in flags)
    compiler = 'D:/mingw64/bin/g++.exe'
    def compile_one(row):
        name, path = row
        subprocess.run([compiler,*flags,'-c',str(path),'-o',str(objects/(name+'.o'))],check=True)
    with ThreadPoolExecutor(max_workers=2) as pool:
        list(pool.map(compile_one,modified.items()))
    subprocess.run([compiler,*flags,'-shared','-static','-o',str(objects/'libgdcore.dll'),
        *[str(objects/(n+'.o')) for n in names]],check=True)
    assert hashes == {n:sha(original/(n+'.o')) for n in names}
    assert all(sha(objects/(n+'.o'))==hashes[n] for n in names if n not in modified)
    dll = WORK / 'diagnostic.dll'
    shutil.copyfile(objects/'libgdcore.dll',dll)
    from bench_native_corpus import load_simulator,measure,prepare,select_cases
    sim = load_simulator(dll)
    signature = hashlib.sha256()
    jobs = list(prepare(sim,select_cases(200),signature))
    stat = sim.lib.gd_diag_native_param_capacity
    stat.argtypes=[ctypes.c_uint];stat.restype=ctypes.c_uint64
    for name in ('reset','finish'):
        fn=getattr(sim.lib,'gd_diag_native_param_capacity_'+name)
        fn.argtypes=[];fn.restype=None
    audit=sim.lib.gd_diag_native_resolved_audit
    audit.argtypes=[ctypes.c_int];audit.restype=None;audit(1)
    old=sim.lib.gd_diag_native_resolved_stat
    old.argtypes=[ctypes.c_uint];old.restype=ctypes.c_uint64
    old_before=[old(i) for i in range(6)]
    sim.lib.gd_diag_native_param_capacity_reset()
    result=measure(sim,jobs,1,0,continuous=True)
    sim.lib.gd_diag_native_param_capacity_finish()
    counts=dict(zip(FIELDS,[stat(i) for i in range(12)]))
    hist=dict(zip(BINS,[stat(12+i) for i in range(8)]))
    policies={str(cap):dict(zip(('allocations','allocated_entry_slots','copied_entries'),
        [stat(20+3*j+i) for i in range(3)])) for j,cap in enumerate((2,4,8))}
    assert counts['registered_dicts']==sum(hist.values())==counts['retired_reused_headers']+counts['final_live_headers']
    assert counts['registered_dicts']>0 and counts['unexpected_capacity']==0
    reference=json.loads((STAGE/'native_perf50_event_bus_serial.json').read_bytes())
    assert signature.hexdigest()==reference['inputs_sha256']
    assert result['results_sha256']==reference['results_sha256'] and result['matched_original_terminal']==200
    old_fields=('generic_hits','funcref_hits','lazy_resolutions','unsupported_types','audit_mismatch','selected_fallback')
    old_counts=dict(zip(old_fields,[old(i)-old_before[i] for i in range(6)]))
    assert old_counts==json.loads((ACCEPTED/'release_audit.json').read_bytes())['coverage']
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    report=dict(diagnostic_only=True,baseline_dll_sha256=EXPECTED,diagnostic_dll_sha256=sha(dll),
        remote_verified_commit=remote,source_before_sha256=before,source_after_sha256=after,
        modified_source_files=changed,recompiled_units=2,reused_abi_identical_objects=18,
        original_objects_unchanged=True,counts=counts,peak_length_histogram=hist,
        shadow_growth_policies=policies,entry_bytes=56,original_six_counters=old_counts,
        inputs_sha256=signature.hexdigest(),results_sha256=result['results_sha256'],
        matched_original_terminal=200,no_throughput_claim=True,production_unchanged=True,
        limits=['Only empty event.params at its first String setParam is enrolled.',
                'Shadow capacities model entry allocation/copy, not execution time or cache misses.',
                'Aliases use the same observed dictionary; create retires reused arena headers.'])
    (WORK/'fixed200_counts.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps({k:v for k,v in report.items() if k not in ('source_before_sha256','source_after_sha256')},indent=2))


if __name__=='__main__':
    main()
