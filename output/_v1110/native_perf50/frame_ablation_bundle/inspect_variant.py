"""Check new dispatch coverage together with the fixed200 result signature."""
import argparse
import ctypes
import hashlib
import json
from pathlib import Path
import sys
sys.path.insert(0,str(Path(__file__).resolve().parents[2]))
from bench_native_corpus import STAGE,load_simulator,measure,prepare,select_cases

def main():
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--dll',type=Path,required=True);p.add_argument('--out',type=Path,required=True)
    args=p.parse_args()
    sim=load_simulator(args.dll);signature=hashlib.sha256()
    jobs=list(prepare(sim,select_cases(200),signature))
    audit=sim.lib.gd_diag_native_resolved_audit;audit.argtypes=[ctypes.c_int];audit.restype=None
    stat=sim.lib.gd_diag_native_resolved_stat;stat.argtypes=[ctypes.c_uint];stat.restype=ctypes.c_uint64
    variant=sim.lib.gd_diag_native_variant_stat;variant.argtypes=[ctypes.c_uint];variant.restype=ctypes.c_uint64
    variant_before=[variant(i) for i in range(10)]
    prop=sim.lib.gd_diag_native_property_stat;prop.argtypes=[ctypes.c_uint];prop.restype=ctypes.c_uint64
    prop_before=[prop(i) for i in range(2)]
    tc=sim.lib.gd_diag_native_type_constructor_stat;tc.argtypes=[ctypes.c_uint];tc.restype=ctypes.c_uint64
    tc_before=[tc(i) for i in range(4)]
    hot=sim.lib.gd_diag_native_hot_slot_stat;hot.argtypes=[ctypes.c_uint];hot.restype=ctypes.c_uint64
    hot_before=[hot(i) for i in range(2)]
    identity=sim.lib.gd_diag_native_event_identity_stat;identity.argtypes=[ctypes.c_uint];identity.restype=ctypes.c_uint64
    typed_before=[identity(i) for i in range(4)]
    lazy=sim.lib.gd_diag_native_lazy_diagnostic_stat;lazy.argtypes=[ctypes.c_uint];lazy.restype=ctypes.c_uint64
    lazy_before=[lazy(i) for i in range(14)]
    frame=sim.lib.gd_diag_native_frame_segment_stat;frame.argtypes=[ctypes.c_uint];frame.restype=ctypes.c_uint64
    frame_before=[frame(i) for i in range(17)]
    audit(1);before=[stat(i) for i in range(6)]
    result=measure(sim,jobs,1,0,continuous=True)
    counts=[stat(i)-before[i] for i in range(6)]
    reference=json.loads((STAGE/'native_perf50_event_bus_serial.json').read_bytes())
    assert signature.hexdigest()==reference['inputs_sha256'] and result['results_sha256']==reference['results_sha256']
    report={'diagnostic_only':True,'dll_sha256':hashlib.sha256(args.dll.read_bytes()).hexdigest(),
        'inputs_sha256':signature.hexdigest(),'results_sha256':result['results_sha256'],
        'coverage':dict(zip(('generic_hits','funcref_hits','lazy_resolutions','unsupported_types','audit_mismatch','selected_fallback'),counts))}
    report['variant_coverage']=dict(zip(('array_size','array_empty','array_has','array_front','array_back','dict_size','dict_empty','dict_has','dict_get','class_lane'),[variant(i)-variant_before[i] for i in range(10)]))
    report['property_coverage']=dict(zip(('field_hits','selected_fallback'),[prop(i)-prop_before[i] for i in range(2)]))
    report['type_constructor_coverage']=dict(zip(('type_hits','type_fallback','fused_initializations','factory_fallback'),[tc(i)-tc_before[i] for i in range(4)]))
    report['hot_slot_coverage']=dict(zip(('new_method_hits','new_field_hits'),[hot(i)-hot_before[i] for i in range(2)]))
    report['event_identity_coverage']=dict(zip(('fast_identities','fallbacks','fast_emissions','emission_fallbacks'),[identity(i)-typed_before[i] for i in range(4)]))
    report['lazy_diagnostic_coverage']={str(site):{'skipped':lazy(site*2)-lazy_before[site*2],'retained':lazy(site*2+1)-lazy_before[site*2+1]} for site in range(7)}
    report['frame_segment_coverage']=[frame(i)-frame_before[i] for i in range(17)]
    assert all(report['frame_segment_coverage'][i]>0 for i in (0,1,2,3,4))
    assert report['lazy_diagnostic_coverage']['0']['skipped']>0
    assert sum(row['skipped'] for key,row in report['lazy_diagnostic_coverage'].items() if key!='0')>0
    assert report['event_identity_coverage']['fast_identities']>0 and report['event_identity_coverage']['fast_emissions']>0
    assert all(value>0 for value in report['hot_slot_coverage'].values())
    assert report['type_constructor_coverage']['type_hits']>0 and report['type_constructor_coverage']['fused_initializations']>0
    assert report['property_coverage']['field_hits']>0
    assert sum(report['variant_coverage'].values())>0
    args.out.write_text(json.dumps(report,indent=2)+'\n',encoding='utf8',newline='\n')
    print(json.dumps(report,indent=2))
    assert all(counts[i]>0 for i in (0,1,2)) and counts[4]==0,report

if __name__=='__main__':main()
