"""Separate shadow DLL: count real operations, never use its speed as evidence."""
import ctypes,hashlib,json,os,re,runpy,shutil,sys,tempfile
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path
import psutil
from native_build_storage import isolated_build
from calibrate_structure_measurement import WORK,ACCEPTED,STAGE,write
from prepare_frame_guard_reuse import inventory,sha
SOURCE=WORK/'diagnostic_src'
NAMES=['arena_requests','arena_requested_bytes','arrays_created','dicts_created','array_storage_growths','explicit_memcpy_bytes','explicit_memmove_bytes','array_find_calls','array_find_comparisons','dict_find_calls','dict_hash_probes','generic_dispatch_calls','generic_argument_cells','frame_calls','cooldown_item_visits','trigger_calls','arena_slow_calls','arena_new_blocks','arena_new_capacity_bytes','ownership_calls','ownership_block_probes','inline_dispatch_calls','inline_argument_cells']
def prepare():
    if SOURCE.exists():
        assert not (WORK/'diagnostic_source.json').exists() and not (WORK/'diagnostic.dll').exists()
        write('diagnostic_prepare_incomplete_attempt.json',dict(reason='dispatch entry declaration has preprocessor qualifiers; pattern matched zero',source_sha256=inventory(SOURCE)))
        for name in inventory(ACCEPTED/'bundle_src'):shutil.copyfile(ACCEPTED/'bundle_src'/name,SOURCE/name)
    else:shutil.copytree(ACCEPTED/'bundle_src',SOURCE)
    header=SOURCE/'gd_rt.hpp';text=header.read_text('utf8')
    mark='// ─────────────────────────── Per-Battle Bump Arena'
    definitions='''// Diagnostic shadow only: these fields are not part of production objects.
extern thread_local unsigned structure_phase;
extern thread_local uint64_t structure_counts[3][32];
inline void structure_hit(unsigned index,uint64_t amount=1) {structure_counts[structure_phase][index]+=amount;}
struct StructurePhase { unsigned previous; explicit StructurePhase(unsigned p):previous(structure_phase){structure_phase=p;} ~StructurePhase(){structure_phase=previous;} };
inline void* structure_copy(void* d,const void* s,size_t n){structure_hit(5,n);return std::memcpy(d,s,n);}
inline void* structure_move(void* d,const void* s,size_t n){structure_hit(6,n);return std::memmove(d,s,n);}
'''
    assert text.count(mark)==1;text=text.replace(mark,definitions+'\n'+mark)
    for old,new in [
      ('void* alloc_raw(size_t bytes, size_t align = 8) {','void* alloc_raw(size_t bytes, size_t align = 8) { structure_hit(0);structure_hit(1,bytes);'),
      ('bool owns_storage(const void* pointer, size_t bytes) const {','bool owns_storage(const void* pointer, size_t bytes) const { structure_hit(19);'),
      ('for (const auto& block : blocks_) {','for (const auto& block : blocks_) { structure_hit(20);'),
      ('void* alloc_raw_slow(size_t bytes, size_t align) {','void* alloc_raw_slow(size_t bytes, size_t align) { structure_hit(16);'),
      ('nb.ptr = new uint8_t[sz];','structure_hit(17);structure_hit(18,sz);nb.ptr = new uint8_t[sz];')]:
        assert text.count(old)==1,old;text=text.replace(old,new)
    header.write_text(text,encoding='utf8',newline='\n')
    path=SOURCE/'gd_rt.cpp';text=path.read_text('utf8')
    operations=[
      ('GdArr* GdArr::create(BattleArena& arena, uint32_t reserve_cap) {','structure_hit(2);'),
      ('GdDict* GdDict::create(BattleArena& arena, uint32_t reserve_cap) {','structure_hit(3);'),
      ('int64_t GdArr::find_val(const GdVal& v, int64_t from) const {','structure_hit(7);'),
      ('int32_t GdDict::find_index(const GdVal& key, uint64_t h) const {','structure_hit(9);'),
      ('GdVal call_method(BattleCtx& ctx, const GdVal& recv, SymId m, const GdVal* args, int argc) {','structure_hit(11);structure_hit(12,argc>0?argc:0);')]
    for old,addition in operations:assert text.count(old)==1,old;text=text.replace(old,old+' '+addition)
    text=text.replace('GdVal* nd = arena.alloc_array<GdVal>(ncap);','structure_hit(4);GdVal* nd = arena.alloc_array<GdVal>(ncap);')
    old='for (uint32_t i = static_cast<uint32_t>(from); i < len; ++i) {';assert text.count(old)==1;text=text.replace(old,old+' structure_hit(8);')
    old='int32_t ei = buckets[pos];';assert text.count(old)==1;text=text.replace(old,'structure_hit(10);'+old)
    text=text.replace('std::memcpy(','structure_copy(').replace('std::memmove(','structure_move(')
    text+='''\nnamespace gd {thread_local unsigned structure_phase=0;thread_local uint64_t structure_counts[3][32]{};}
extern "C" void gd_diag_structure_reset(){gd::structure_phase=0;std::memset(gd::structure_counts,0,sizeof(gd::structure_counts));}
extern "C" uint64_t gd_diag_structure_stat(unsigned p,unsigned i){return p<3&&i<32?gd::structure_counts[p][i]:0;}
'''
    path.write_text(text,encoding='utf8',newline='\n')
    path=SOURCE/'native_inline_dispatch.hpp';text=path.read_text('utf8')
    # Match the public inline dispatch entry, not its declarations/call sites.
    pattern=r'(GdVal\s+native_inline_call\([^\{]+\{)'
    text,n=re.subn(pattern,r'\1 structure_hit(21);structure_hit(22,argc>0?argc:0);',text);assert n==1,n
    old='const auto* row=item->native_call_row_;';assert text.count(old)==1;text=text.replace(old,'structure_hit(14);'+old)
    path.write_text(text,encoding='utf8',newline='\n')
    count=0
    for path in sorted((SOURCE/'gen/shards').glob('*.cpp')):
        text=path.read_text('utf8')
        text,n=re.subn(r'(gd::GdVal [\w]+::fn_trigger\([^\n]+\{)',r'\1 gd::StructurePhase structure_trigger_phase(2);gd::structure_hit(15);',text);count+=n
        old='gd::GdVal Gd__gd_core__CoreCombat::fn_physicsTick(const gd::GdVal* _args, int _argc) {'
        if old in text:text=text.replace(old,old+' gd::StructurePhase structure_frame_phase(1);gd::structure_hit(13);')
        path.write_text(text,encoding='utf8',newline='\n')
    assert count==6,count
    write('diagnostic_source.json',dict(source_sha256=inventory(SOURCE),names=NAMES,phases=['outside_frame_including_setup','frame_excluding_nested_triggers','trigger_and_nested_chain'],all23_counters_observe_actual_operations=True,argument_cells_are_logical_not_machine_copy_bytes=True,explicit_copy_bytes_only_gd_rt_cpp=True,hash_probes_only_bucket_loop=True,unmodified_GdVal_triviality_and_all_object_layouts=True,not_performance_candidate=True))
    print('Cost shadow prepared',flush=True)
@isolated_build
def build():
    assert not (WORK/'diagnostic.dll').exists();psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    root=Path(tempfile.mkdtemp(prefix='structure-diagnostic-',dir=Path(os.environ['LOCALAPPDATA'])/'CodexNativeBuilds'));obj=root/'objects'
    os.environ.update(NATIVE_SIM_OBJ=str(obj),NATIVE_SIM_CXX='D:/mingw64/bin/g++.exe')
    module=runpy.run_path(str(SOURCE/'build_windows.py'));module['build'].__globals__['ThreadPoolExecutor']=lambda max_workers:ThreadPoolExecutor(max_workers=min(2,max_workers))
    dll=module['build']();shutil.move(dll,WORK/'diagnostic.dll')
    write('diagnostic_build.json',dict(passed=True,dll_sha256=sha(WORK/'diagnostic.dll'),object_directory=str(obj),maximum_workers=2,below_normal=True,not_for_speed_or_deployment=True))
def inspect():
    from bench_native_corpus import load_simulator,prepare as prepare_jobs,select_cases,measure
    psutil.Process().cpu_affinity([2]);sim=load_simulator(WORK/'diagnostic.dll');digest=hashlib.sha256();jobs=list(prepare_jobs(sim,select_cases(200),digest))
    reset=sim.lib.gd_diag_structure_reset;reset.argtypes=[];reset.restype=None
    stat=sim.lib.gd_diag_structure_stat;stat.argtypes=[ctypes.c_uint,ctypes.c_uint];stat.restype=ctypes.c_uint64
    reset();r=measure(sim,jobs,1,0,continuous=True)
    ref=json.loads((WORK/'fixed200_reference.json').read_bytes());assert digest.hexdigest()==ref['inputs_sha256'] and r['results_sha256']==ref['results_sha256']
    counts={p:{name:stat(i,j) for j,name in enumerate(NAMES)} for i,p in enumerate(['setup_and_outside_frame','frame_excluding_trigger','trigger_chain'])}
    write('diagnostic_counts.json',dict(passed=True,dll_sha256=sha(WORK/'diagnostic.dll'),inputs_sha256=digest.hexdigest(),results_sha256=r['results_sha256'],counts=counts,no_timing_claim=True))
    print(json.dumps(counts,indent=2),flush=True)
if __name__=='__main__':{'prepare':prepare,'build':build,'inspect':inspect}[sys.argv[1]]()
