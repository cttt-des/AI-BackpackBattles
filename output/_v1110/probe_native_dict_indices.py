"""Count exact integer-key entry-index matches without changing dictionary lookups."""
import argparse
import ctypes
import hashlib
import json
from pathlib import Path
from bench_native_corpus import STAGE,load_simulator,measure,prepare,select_cases

NAMES=('get_calls','get_int_keys','get_int_in_bounds','get_exact_entry_index','get_float_at_int_index',
       'get_string_keys','get_other_keys','get_empty','get_len_1_4','get_len_5_8','get_len_9_16',
       'get_len_17_32','get_len_over_32','find_calls','find_exact_entry_and_hash','find_int_keys')
COUNTERS='''
namespace {
thread_local uint64_t native_dict_indices[16]{};
}
extern "C" uint64_t gd_sim_dict_index_stat(unsigned index) {
    return index < 16 ? native_dict_indices[index] : 0;
}
extern "C" void gd_sim_dict_index_reset() {
    for (auto& counter : native_dict_indices) counter=0;
}
'''
GET='''
    ++native_dict_indices[0];
    if (key.kind == GdVal::Kind::Int) {
        ++native_dict_indices[1];
        if (key.i >= 0 && static_cast<uint64_t>(key.i) < len) {
            ++native_dict_indices[2];
            const auto& stored=entries[static_cast<uint32_t>(key.i)].key;
            native_dict_indices[3] += stored.kind == GdVal::Kind::Int && stored.i == key.i;
            native_dict_indices[4] += stored.kind == GdVal::Kind::Float && stored.f == static_cast<double>(key.i);
        }
    } else if (key.kind == GdVal::Kind::Str) ++native_dict_indices[5];
    else ++native_dict_indices[6];
    ++native_dict_indices[len == 0 ? 7 : len <= 4 ? 8 : len <= 8 ? 9 : len <= 16 ? 10 : len <= 32 ? 11 : 12];
'''
FIND='''
    ++native_dict_indices[13];
    if (key.kind == GdVal::Kind::Int) {
        ++native_dict_indices[15];
        if (key.i >= 0 && static_cast<uint64_t>(key.i) < len) {
            const auto& stored=entries[static_cast<uint32_t>(key.i)];
            native_dict_indices[14] += stored.key.kind == GdVal::Kind::Int && stored.key.i == key.i && stored.hash == h;
        }
    }
'''

def instrument(native):
    path=native/'gd_rt.cpp'
    source=path.read_text('utf8')
    anchor='GdVal GdDict::get(const GdVal& key, const GdVal& def) const {'
    lookup='int32_t GdDict::find_index(const GdVal& key, uint64_t h) const {'
    assert source.count(anchor)==source.count(lookup)==1 and 'native_dict_indices' not in source
    source=source.replace(lookup,COUNTERS+'\n'+lookup+FIND).replace(anchor,anchor+GET)
    path.write_text(source,encoding='utf8',newline='\n')

def inspect(dll,out):
    sim=load_simulator(dll)
    signature=hashlib.sha256()
    jobs=list(prepare(sim,select_cases(200),signature))
    reset=sim.lib.gd_sim_dict_index_reset;reset.argtypes=[];reset.restype=None
    read=sim.lib.gd_sim_dict_index_stat;read.argtypes=[ctypes.c_uint];read.restype=ctypes.c_uint64
    reset()
    result=measure(sim,jobs,1,0,continuous=True)
    reference=json.loads((STAGE/'native_perf50_event_bus_serial.json').read_bytes())
    assert signature.hexdigest()==reference['inputs_sha256'] and result['results_sha256']==reference['results_sha256']
    report={'diagnostic_only':True,'dll_sha256':hashlib.sha256(dll.read_bytes()).hexdigest(),
            'inputs_sha256':signature.hexdigest(),'results_sha256':result['results_sha256'],
            'counts':dict(zip(NAMES,(read(i) for i in range(len(NAMES))),strict=True))}
    out.write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps(report,indent=2))

if __name__=='__main__':
    parser=argparse.ArgumentParser(description=__doc__)
    mode=parser.add_mutually_exclusive_group(required=True)
    mode.add_argument('--instrument',type=Path);mode.add_argument('--dll',type=Path)
    parser.add_argument('--out',type=Path)
    args=parser.parse_args()
    if args.instrument:instrument(args.instrument)
    elif args.out:inspect(args.dll,args.out)
    else:parser.error('--dll requires --out')
