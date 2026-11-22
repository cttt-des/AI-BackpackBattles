"""Count dictionary work on a diagnostic-only copy; reuse 19 verified ABI-identical objects."""
import ctypes
import hashlib
import json
from pathlib import Path
import runpy
import shutil
import subprocess
import sys
import tempfile
import psutil

STAGE=Path(__file__).resolve().parent
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'
ACCEPTED=STAGE/'native_perf50/closed_timer_bundle'
WORK=STAGE/'native_perf50/dict_cost_probe'
EXPECTED='686f0d6cdb2fc223d4ed50319b31e786eea14383b4ffb9a8fe8633395ee07b43'
ARCHIVE='e5356be288c04804dc645fced2ab24fd360b2238'
FIELDS=('created','created_large_reserved','reserved_capacity_sum','find_calls','linear_find_calls','large_reserved_linear_find_calls',
        'linear_slot_tests','large_reserved_linear_slot_tests','hashed_find_calls','hashed_slot_tests',
        'get_calls','get_large_reserved_linear','get_direct_int_hits','set_calls','set_large_reserved_linear','set_existing','set_new','set_growth',
        'duplicate_calls','duplicate_entries','duplicate_large','duplicate_deep','duplicate_int_keys','duplicate_string_keys','duplicate_other_keys',
        'maximum_find_length','index_rebuilds','find_int_keys','find_string_keys','find_other_keys')
BINS=('0','1','2','3','4','5_8','9_16','17_32','33_plus')

HELPER=r'''
namespace {
static thread_local uint64_t native_dict_cost[57]{};
static unsigned native_dict_cost_bin(uint32_t n){return n<=4?n:n<=8?5:n<=16?6:n<=32?7:8;}
}
'''

def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def once(text,old,new):
    assert text.count(old)==1,(old,text.count(old));return text.replace(old,new,1)

def transform(text):
    text=once(text,'GdDict* GdDict::create(BattleArena& arena, uint32_t reserve_cap) {',HELPER+'''GdDict* GdDict::create(BattleArena& arena, uint32_t reserve_cap) {
    ++native_dict_cost[0];native_dict_cost[1]+=reserve_cap>8;native_dict_cost[2]+=reserve_cap;
    ++native_dict_cost[30+native_dict_cost_bin(reserve_cap)];''')
    text=once(text,'void GdDict::rebuild_index(BattleArena& arena) {','void GdDict::rebuild_index(BattleArena& arena) {\n    native_dict_cost[26]+=cap>8;')
    text=once(text,'int32_t GdDict::find_index(const GdVal& key, uint64_t h) const {', '''int32_t GdDict::find_index(const GdVal& key, uint64_t h) const {
    ++native_dict_cost[3];native_dict_cost[25]=std::max(native_dict_cost[25],uint64_t(len));
    ++native_dict_cost[key.kind==GdVal::Kind::Int?27:key.kind==GdVal::Kind::Str?28:29];''')
    text=once(text,'''    if (!buckets || bucket_cap == 0) {
        for (uint32_t i = 0; i < len; ++i) {
            if (entries[i].hash == h''','''    if (!buckets || bucket_cap == 0) {
        ++native_dict_cost[4];const bool large_reserved=cap>8;
        if(large_reserved){++native_dict_cost[5];++native_dict_cost[39+native_dict_cost_bin(len)];}
        for (uint32_t i = 0; i < len; ++i) {
            ++native_dict_cost[6];native_dict_cost[7]+=large_reserved;
            if (entries[i].hash == h''')
    begin=text.index('int32_t GdDict::find_index(');end=text.index('\n}',begin)+2
    method=text[begin:end]
    method=once(method,'    uint32_t mask = bucket_cap - 1;','    ++native_dict_cost[8];\n    uint32_t mask = bucket_cap - 1;')
    method=once(method,'    while (true) {','    while (true) {\n        ++native_dict_cost[9];')
    text=text[:begin]+method+text[end:]
    text=once(text,'GdVal GdDict::get(const GdVal& key, const GdVal& def) const {', '''GdVal GdDict::get(const GdVal& key, const GdVal& def) const {
    ++native_dict_cost[10];native_dict_cost[11]+=cap>8 && (!buckets || bucket_cap==0);''')
    text=once(text,'if (entry.key.kind == GdVal::Kind::Int && entry.key.i == key.i) return entry.val;',
              'if (entry.key.kind == GdVal::Kind::Int && entry.key.i == key.i) {++native_dict_cost[12];return entry.val;}')
    text=once(text,'void GdDict::set(BattleArena& arena, const GdVal& key, const GdVal& val) {', '''void GdDict::set(BattleArena& arena, const GdVal& key, const GdVal& val) {
    ++native_dict_cost[13];native_dict_cost[14]+=cap>8 && (!buckets || bucket_cap==0);''')
    begin=text.index('void GdDict::set(');end=text.index('\n}',begin)+2;method=text[begin:end]
    method=once(method,'    if (idx >= 0) {','    if (idx >= 0) {\n        ++native_dict_cost[15];')
    method=once(method,'    if (len == cap) {','    ++native_dict_cost[16];\n    if (len == cap) {\n        ++native_dict_cost[17];')
    text=text[:begin]+method+text[end:]
    text=once(text,'GdDict* GdDict::duplicate(BattleArena& arena, bool deep) const {', '''GdDict* GdDict::duplicate(BattleArena& arena, bool deep) const {
    ++native_dict_cost[18];native_dict_cost[19]+=len;native_dict_cost[20]+=len>8;native_dict_cost[21]+=deep;
    ++native_dict_cost[48+native_dict_cost_bin(len)];''')
    text=once(text,'        GdVal k = entries[i].key, v = entries[i].val;', '''        GdVal k = entries[i].key, v = entries[i].val;
        ++native_dict_cost[k.kind==GdVal::Kind::Int?22:k.kind==GdVal::Kind::Str?23:24];''')
    text+='''
extern "C" uint64_t gd_diag_native_dict_probe_stat(unsigned n){return n<57?gd::native_dict_cost[n]:0;}
extern "C" void gd_diag_native_dict_probe_reset(){for(auto& n:gd::native_dict_cost)n=0;}
'''
    return text

def main():
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    verified=json.loads((ACCEPTED/'post_install_verification.json').read_bytes());assert verified['passed'] and verified['dll_sha256']==EXPECTED
    backup=json.loads((ACCEPTED/'checkpoint_receipt.json').read_bytes());assert backup['remote_verified_commit']==ARCHIVE and backup['dll_sha256']==EXPECTED
    assert subprocess.check_output(['git','ls-remote','--exit-code','origin','refs/heads/codex/native-perf50-verified']).decode().split()[0]==ARCHIVE
    assert not WORK.exists();WORK.mkdir();src=WORK/'diagnostic_src'
    shutil.copytree(BASE,src,ignore=shutil.ignore_patterns('*.dll','*.o','*.gcda','*.gcno','__pycache__'))
    before={p.relative_to(src).as_posix():sha(p) for p in src.rglob('*') if p.is_file()}
    assert before==json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    p=src/'gd_rt.cpp';p.write_text(transform(p.read_text('utf8')),encoding='utf8',newline='\n')
    after={p.relative_to(src).as_posix():sha(p) for p in src.rglob('*') if p.is_file()}
    assert [name for name in before if before[name]!=after[name]]==['gd_rt.cpp']
    original=Path((ACCEPTED/'bundle_objects.txt').read_text('utf8'))
    names=['gd_rt','engine_wrapper','sym_ids','register_all',*[f'shard_{i:02d}' for i in range(16)]]
    original_hashes={name:sha(original/(name+'.o')) for name in names}
    objects=Path(tempfile.mkdtemp(prefix='native-dict-cost-'))
    (WORK/'objects.txt').write_text(str(objects),encoding='utf8')
    for name in names:
        if name!='gd_rt':shutil.copyfile(original/(name+'.o'),objects/(name+'.o'))
    flags=runpy.run_path(str(src/'build_windows.py'))['COMMON'];compiler='D:/mingw64/bin/g++.exe'
    subprocess.run([compiler,*flags,'-c',str(src/'gd_rt.cpp'),'-o',str(objects/'gd_rt.o')],check=True)
    subprocess.run([compiler,*flags,'-flto=2','-shared','-static','-o',str(objects/'libgdcore.dll'),*[str(objects/(name+'.o')) for name in names]],check=True)
    assert original_hashes=={name:sha(original/(name+'.o')) for name in names}
    assert all(sha(objects/(name+'.o'))==original_hashes[name] for name in names if name!='gd_rt')
    dll=WORK/'diagnostic.dll';shutil.copyfile(objects/'libgdcore.dll',dll)
    from bench_native_corpus import load_simulator,measure,prepare,select_cases
    sim=load_simulator(dll);signature=hashlib.sha256();jobs=list(prepare(sim,select_cases(200),signature))
    stat=sim.lib.gd_diag_native_dict_probe_stat;stat.argtypes=[ctypes.c_uint];stat.restype=ctypes.c_uint64
    reset=sim.lib.gd_diag_native_dict_probe_reset;reset.argtypes=[];reset.restype=None;reset()
    result=measure(sim,jobs,1,0,continuous=True)
    reference=json.loads((STAGE/'native_perf50_event_bus_serial.json').read_bytes())
    assert signature.hexdigest()==reference['inputs_sha256'] and result['results_sha256']==reference['results_sha256'] and result['matched_original_terminal']==200
    counts=dict(zip(FIELDS,[stat(i) for i in range(len(FIELDS))]))
    histograms={label:dict(zip(BINS,[stat(offset+i) for i in range(9)])) for label,offset in [('reserve_capacity',30),('large_reserved_linear_length',39),('duplicate_length',48)]}
    assert sum(histograms['reserve_capacity'].values())==counts['created']
    assert sum(histograms['large_reserved_linear_length'].values())==counts['large_reserved_linear_find_calls']
    assert sum(histograms['duplicate_length'].values())==counts['duplicate_calls']
    assert counts['linear_find_calls']+counts['hashed_find_calls']==counts['find_calls']
    assert counts['set_existing']+counts['set_new']==counts['set_calls']
    assert sum(counts[k] for k in ('duplicate_int_keys','duplicate_string_keys','duplicate_other_keys'))==counts['duplicate_entries']
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    report=dict(diagnostic_only=True,baseline_dll_sha256=EXPECTED,diagnostic_dll_sha256=sha(dll),verified_remote_backup=ARCHIVE,
        inputs_sha256=signature.hexdigest(),results_sha256=result['results_sha256'],matched_original_terminal=200,
        counts=counts,histograms=histograms,reused_abi_identical_objects=19,recompiled_units=1,original_objects_unchanged=True,
        only_modified_file='gd_rt.cpp',source_before_sha256=before['gd_rt.cpp'],source_after_sha256=after['gd_rt.cpp'],
        no_throughput_claim=True,production_unchanged=True)
    (WORK/'fixed200_counts.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8');print(json.dumps(report,indent=2))

if __name__=='__main__':main()
