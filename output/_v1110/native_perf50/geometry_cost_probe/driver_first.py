"""Count spatial dictionary shape, probes and writes after first query; never report timing."""
import ctypes
import hashlib
import json
import os
from pathlib import Path
import runpy
import shutil
import subprocess
import tempfile
from concurrent.futures import ThreadPoolExecutor
import psutil

STAGE=Path(__file__).resolve().parent
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'
ACCEPTED=STAGE/'native_perf50/active_cooldown_bundle'
WORK=STAGE/'native_perf50/geometry_cost_probe'
EXPECTED='55b62a2044b87311a967878a91d88ef4702641d240594989a09c396f67172ece'
ARCHIVE='f67e7c55fd5d4c161b6ab3c81d925d2ba7ea5ffd'
ROLE_FIELDS=('queries','vec2_queries','integer_queries','window16_queries','window32_queries','window64_queries',
    'linear_queries','hashed_queries','slot_probes','hits','registered_dicts','snapshot_entries','snapshot_integer_keys',
    'snapshot_all_integer_dicts','set_existing_after_query','set_new_after_query','erase_hit_after_query','erase_miss_after_query',
    'clear_after_query','max_query_length','max_snapshot_length','query_length_sum','snapshot_window32_keys','snapshot_window64_keys')
EXTRA_FIELDS=('dedup_calls','dedup_length_sum','dedup_slot_tests','dedup_max_length','context_epochs')
COUNT=len(ROLE_FIELDS)*2+len(EXTRA_FIELDS)
DECL='''
namespace gd {
void native_geometry_begin(BattleCtx&,const GdDict*,const GdVal&,unsigned);
void native_geometry_lookup(const GdDict*,const GdVal&,int32_t,unsigned);
void native_geometry_dedup_begin(uint32_t);
void native_geometry_dedup_slot();
}
'''
HELPER=r'''
namespace {
constexpr unsigned GEO_ROLE_FIELDS=24,GEO_EXTRA=48;
static thread_local uint64_t geometry_counts[53]{};
static thread_local int64_t geometry_ranges[8]={INT64_MAX,INT64_MIN,INT64_MAX,INT64_MIN,INT64_MAX,INT64_MIN,INT64_MAX,INT64_MIN};
static thread_local BattleCtx* geometry_context=nullptr;
static thread_local uint64_t geometry_epoch=0;
static thread_local std::unordered_map<const GdDict*,unsigned> geometry_dicts;
// Pure bit parsing avoids adding float comparisons, conversions or FENV flags.
bool geometry_component(double value,int64_t& out) {
    uint64_t bits;std::memcpy(&bits,&value,8);const uint64_t magnitude=bits&UINT64_C(0x7fffffffffffffff);
    if(!magnitude){out=0;return true;}
    const unsigned exponent=unsigned(magnitude>>52);
    if(exponent<1023 || exponent>1032)return false;
    const unsigned shift=52-(exponent-1023);
    const uint64_t mantissa=(magnitude&UINT64_C(0xfffffffffffff))|UINT64_C(0x10000000000000);
    if(mantissa&((UINT64_C(1)<<shift)-1))return false;
    out=int64_t(mantissa>>shift);if(bits>>63)out=-out;return true;
}
bool geometry_key(const GdVal& value,int64_t& x,int64_t& y) {
    return value.kind==GdVal::Kind::Vec2 && geometry_component(value.v2.x,x) && geometry_component(value.v2.y,y);
}
bool geometry_window(int64_t x,int64_t y,int64_t lo,int64_t hi){return x>=lo && x<=hi && y>=lo && y<=hi;}
void geometry_check_epoch() {
    // This diagnostic is executed only through the packed replay bridge, whose
    // BattleCtx is thread_local and alive for the entire replay process.
    if(geometry_context && geometry_context->gid_epoch!=geometry_epoch){geometry_dicts.clear();geometry_epoch=geometry_context->gid_epoch;++geometry_counts[GEO_EXTRA+4];}
}
struct NativeGeometryMutation {
    const GdDict* dict;unsigned roles=0,kind;uint32_t before;
    NativeGeometryMutation(const GdDict* d,unsigned k):dict(d),kind(k),before(d->len) {
        geometry_check_epoch();const auto found=geometry_dicts.find(d);if(found!=geometry_dicts.end())roles=found->second;
    }
    ~NativeGeometryMutation(){for(unsigned role=0;role<2;++role)if(roles&(1u<<role)){
        auto* c=geometry_counts+role*GEO_ROLE_FIELDS;
        if(kind==0)++c[dict->len==before?14:15];
        if(kind==1)++c[dict->len==before?17:16];
        if(kind==2)++c[18];
    }}
};
}
void native_geometry_begin(BattleCtx& ctx,const GdDict* dict,const GdVal& key,unsigned role) {
    if(role<1 || role>2)return;
    if(geometry_context!=&ctx){geometry_context=&ctx;geometry_epoch=ctx.gid_epoch;geometry_dicts.clear();++geometry_counts[GEO_EXTRA+4];}
    geometry_check_epoch();const unsigned r=role-1;auto* c=geometry_counts+r*GEO_ROLE_FIELDS;
    ++c[0];c[1]+=key.kind==GdVal::Kind::Vec2;c[19]=std::max(c[19],uint64_t(dict->len));c[21]+=dict->len;
    int64_t x=0,y=0;
    if(geometry_key(key,x,y)) {
        ++c[2];c[3]+=geometry_window(x,y,0,15);c[4]+=geometry_window(x,y,-8,23);c[5]+=geometry_window(x,y,-16,47);
        auto* range=geometry_ranges+r*4;range[0]=std::min(range[0],x);range[1]=std::max(range[1],x);range[2]=std::min(range[2],y);range[3]=std::max(range[3],y);
    }
    auto& flags=geometry_dicts[dict];if(flags&(1u<<r))return;flags|=1u<<r;
    ++c[10];c[11]+=dict->len;c[20]=std::max(c[20],uint64_t(dict->len));bool all=true;
    for(uint32_t i=0;i<dict->len;++i){if(geometry_key(dict->entries[i].key,x,y)){++c[12];c[22]+=geometry_window(x,y,-8,23);c[23]+=geometry_window(x,y,-16,47);}else all=false;}
    c[13]+=all;
}
void native_geometry_lookup(const GdDict* dict,const GdVal& key,int32_t index,unsigned role) {
    if(role<1 || role>2)return;auto* c=geometry_counts+(role-1)*GEO_ROLE_FIELDS;c[9]+=index>=0;
    if(!dict->buckets || !dict->bucket_cap){++c[6];c[8]+=index<0?dict->len:uint32_t(index)+1;return;}
    ++c[7];if(key.kind!=GdVal::Kind::Vec2)return;
    // Same hash as gd_val_hash(Vec2), calculated without floating point.
    uint64_t bx,by;std::memcpy(&bx,&key.v2.x,8);std::memcpy(&by,&key.v2.y,8);
    if(!(bx&UINT64_C(0x7fffffffffffffff)))bx=0;if(!(by&UINT64_C(0x7fffffffffffffff)))by=0;
    const uint64_t h=splitmix64(bx)^(splitmix64(by)*UINT64_C(0x9e3779b97f4a7c15));
    uint32_t position=uint32_t(h)&(dict->bucket_cap-1);
    for(uint32_t n=0;n<dict->bucket_cap;++n){++c[8];const int32_t at=dict->buckets[position];if(at<0 || at==index)break;position=(position+1)&(dict->bucket_cap-1);}
}
void native_geometry_dedup_begin(uint32_t length){++geometry_counts[GEO_EXTRA];geometry_counts[GEO_EXTRA+1]+=length;geometry_counts[GEO_EXTRA+3]=std::max(geometry_counts[GEO_EXTRA+3],uint64_t(length));}
void native_geometry_dedup_slot(){++geometry_counts[GEO_EXTRA+2];}
'''

def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def once(t,a,b):
    assert t.count(a)==1,(a[:100],t.count(a));return t.replace(a,b,1)

def transform(src):
    path=src/'gd_rt.hpp';path.write_text(path.read_text('utf8')+DECL,encoding='utf8',newline='\n')
    path=src/'gd_rt.cpp';text=path.read_text('utf8')
    text=once(text,'GdDict* GdDict::create(BattleArena& arena, uint32_t reserve_cap) {',HELPER+'\nGdDict* GdDict::create(BattleArena& arena, uint32_t reserve_cap) {')
    for sig,kind in [('void GdDict::set(BattleArena& arena, const GdVal& key, const GdVal& val) {',0),('void GdDict::erase(const GdVal& key) {',1),('void GdDict::clear() {',2)]:
        text=once(text,sig,sig+f'\n    NativeGeometryMutation geometry_mutation(this,{kind});')
    text+='''
extern "C" uint64_t gd_diag_native_geometry_stat(unsigned n){return n<53?gd::geometry_counts[n]:0;}
extern "C" int64_t gd_diag_native_geometry_range(unsigned n){return n<8?gd::geometry_ranges[n]:0;}
extern "C" void gd_diag_native_geometry_reset(){for(auto& x:gd::geometry_counts)x=0;gd::geometry_dicts.clear();gd::geometry_context=nullptr;gd::geometry_epoch=0;for(unsigned i=0;i<8;++i)gd::geometry_ranges[i]=(i%2)?INT64_MIN:INT64_MAX;}
'''
    path.write_text(text,encoding='utf8',newline='\n')
    path=src/'gen/shards/shard_13.cpp';text=path.read_text('utf8')
    text=once(text,'const GdVal& key,GdVal& value) {','const GdVal& key,GdVal& value,unsigned geometry_role) {')
    text=once(text,'        const auto index=dict->find_index(key);','        native_geometry_begin(ctx,dict,key,geometry_role);\n        const auto index=dict->find_index(key);\n        native_geometry_lookup(dict,key,index,geometry_role);')
    for field,role,n in [('f_filledCells',1,2),('f_bagCells',2,1)]:
        old=f'gd::native_spatial_lookup(gd_ctx, this->{field}, lv_cell, lv_spatial_value)'
        assert text.count(old)==n;text=text.replace(old,old[:-1]+f', {role})')
    text=once(text,'        const auto* items=result.arr;','        const auto* items=result.arr;\n        native_geometry_dedup_begin(items->len);')
    text=once(text,'            const auto& entry=items->data[i];','            native_geometry_dedup_slot();\n            const auto& entry=items->data[i];')
    path.write_text(text,encoding='utf8',newline='\n')

def main():
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    assert json.loads((ACCEPTED/'post_install_verification.json').read_bytes())['dll_sha256']==EXPECTED
    assert json.loads((ACCEPTED/'checkpoint_receipt.json').read_bytes())['remote_verified_commit']==ARCHIVE
    assert subprocess.check_output(['git','ls-remote','--exit-code','origin','refs/heads/codex/native-perf50-verified']).decode().split()[0]==ARCHIVE
    assert not WORK.exists();WORK.mkdir();src=WORK/'diagnostic_src'
    shutil.copytree(BASE,src,ignore=shutil.ignore_patterns('*.dll','*.o','*.gcda','*.gcno','__pycache__'))
    before={p.relative_to(src).as_posix():sha(p) for p in src.rglob('*') if p.is_file()}
    assert before==json.loads((ACCEPTED/'source_before_build.json').read_bytes());transform(src)
    after={p.relative_to(src).as_posix():sha(p) for p in src.rglob('*') if p.is_file()}
    assert sorted(n for n in before if before[n]!=after[n])==['gd_rt.cpp','gd_rt.hpp','gen/shards/shard_13.cpp']
    original=Path((ACCEPTED/'bundle_objects.txt').read_text('utf8'))
    names=['gd_rt','engine_wrapper','sym_ids','register_all',*[f'shard_{i:02d}' for i in range(16)]]
    hashes={n:sha(original/(n+'.o')) for n in names};objects=Path(tempfile.mkdtemp(prefix='native-geometry-cost-'))
    (WORK/'objects.txt').write_text(str(objects),encoding='utf8');changed={'gd_rt','shard_13'}
    for n in names:
        if n not in changed:shutil.copyfile(original/(n+'.o'),objects/(n+'.o'))
    flags=runpy.run_path(str(src/'build_windows.py'))['COMMON'];compiler='D:/mingw64/bin/g++.exe'
    def compile_one(name):
        cpp=src/('gd_rt.cpp' if name=='gd_rt' else 'gen/shards/shard_13.cpp')
        subprocess.run([compiler,*flags,'-flto=2','-c',str(cpp),'-o',str(objects/(name+'.o'))],check=True)
    with ThreadPoolExecutor(max_workers=2) as pool:list(pool.map(compile_one,sorted(changed)))
    os.environ['MAKE']='D:/mingw64/bin/mingw32-make.exe'
    subprocess.run([compiler,*flags,'-flto=2','-shared','-static','-o',str(objects/'libgdcore.dll'),*[str(objects/(n+'.o')) for n in names]],check=True)
    assert hashes=={n:sha(original/(n+'.o')) for n in names}
    assert all(sha(objects/(n+'.o'))==hashes[n] for n in names if n not in changed)
    dll=WORK/'diagnostic.dll';shutil.copyfile(objects/'libgdcore.dll',dll)
    from bench_native_corpus import load_simulator,measure,prepare,select_cases
    sim=load_simulator(dll);signature=hashlib.sha256();jobs=list(prepare(sim,select_cases(200),signature))
    stat=sim.lib.gd_diag_native_geometry_stat;stat.argtypes=[ctypes.c_uint];stat.restype=ctypes.c_uint64
    ranges=sim.lib.gd_diag_native_geometry_range;ranges.argtypes=[ctypes.c_uint];ranges.restype=ctypes.c_int64
    reset=sim.lib.gd_diag_native_geometry_reset;reset.argtypes=[];reset.restype=None;reset()
    audit=sim.lib.gd_diag_native_resolved_audit;audit.argtypes=[ctypes.c_int];audit.restype=None;audit(1)
    old_stat=sim.lib.gd_diag_native_resolved_stat;old_stat.argtypes=[ctypes.c_uint];old_stat.restype=ctypes.c_uint64
    old_before=[old_stat(i) for i in range(6)];result=measure(sim,jobs,1,0,continuous=True)
    reference=json.loads((STAGE/'native_perf50_event_bus_serial.json').read_bytes())
    assert signature.hexdigest()==reference['inputs_sha256'] and result['results_sha256']==reference['results_sha256'] and result['matched_original_terminal']==200
    old_counts=dict(zip(('generic_hits','funcref_hits','lazy_resolutions','unsupported_types','audit_mismatch','selected_fallback'),[old_stat(i)-old_before[i] for i in range(6)]))
    assert old_counts==json.loads((ACCEPTED/'release_audit.json').read_bytes())['coverage']
    role_counts={name:dict(zip(ROLE_FIELDS,[stat(role*len(ROLE_FIELDS)+i) for i in range(len(ROLE_FIELDS))])) for role,name in enumerate(('filled','bags'))}
    report=dict(diagnostic_only=True,baseline_dll_sha256=EXPECTED,diagnostic_dll_sha256=sha(dll),verified_remote_backup=ARCHIVE,
        inputs_sha256=signature.hexdigest(),results_sha256=result['results_sha256'],matched_original_terminal=200,
        counts=role_counts,extra=dict(zip(EXTRA_FIELDS,[stat(2*len(ROLE_FIELDS)+i) for i in range(len(EXTRA_FIELDS))])),
        query_ranges={name:dict(zip(('min_x','max_x','min_y','max_y'),[ranges(role*4+i) for i in range(4)])) for role,name in enumerate(('filled','bags'))},
        old_six_counters=old_counts,reused_objects=18,recompiled_units=2,original_objects_unchanged=True,
        no_object_or_container_layout_change=True,header_only_adds_free_function_declarations=True,
        mutation_scope='Only set/erase/clear after the first observed spatial query in each live packed battle; writes before registration are excluded',
        slot_probe_counts_not_cpu_time=True,no_throughput_claim=True,production_unchanged=sha(BASE/'libgdcore.dll')==EXPECTED)
    assert all(c['queries']==c['linear_queries']+c['hashed_queries'] for c in role_counts.values())
    (WORK/'fixed200_counts.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    shutil.copyfile(__file__,WORK/'driver_first.py');print(json.dumps(report,indent=2))

if __name__=='__main__':main()
