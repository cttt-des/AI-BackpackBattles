"""Retain the accepted experiment pipeline and add a spatial production oracle."""
import ast
import json
from pathlib import Path
STAGE=Path(__file__).resolve().parent
OLD=STAGE/'native_perf50/dispatch_chain_bundle'
WORK=STAGE/'native_perf50/spatial_bundle'
BASE='39c559a0bc4ef04f89444be63b42b842884a7d2fee1d59c4332fcdc7367d8e0b'
ARCHIVE='69cab46bc048500927ca4ed82104e78f7f8818b6'

def main():
    assert not (WORK/'build_bundle.py').exists();WORK.mkdir(exist_ok=True)
    for path in OLD.glob('*.py'):
        if path.name=='summarize_profile_for_brainstorm.py':continue
        source=path.read_text('utf8').replace('dispatch_chain_bundle','spatial_bundle').replace('static_setup_bundle','dispatch_chain_bundle')
        source=source.replace('1bf22370f344d8379b33d6c4d31629e178549ab7',ARCHIVE).replace('00cbcf9d9467feab8d8d99aa437683af507c5f924ee90a9b9f076b661d5c6a60',BASE)
        source=source.replace('native-dispatch-chain-','native-spatial-')
        if path.name=='resume_build.py':source=source.replace("    definition=objects/'instrumented_exports.def'","    exports.add('gd_diag_native_spatial_stat')\n    definition=objects/'instrumented_exports.def'").replace("objects.name.startswith('native-frame-ablation-')","objects.name.startswith('native-spatial-')")
        if path.name=='validate_then_compare.py':source=source.replace("    run('verify_dispatch_chain.py','dispatch_chain_tests.log')","    run('verify_dispatch_chain.py','dispatch_chain_tests.log')\n    run('verify_spatial.py','spatial_tests.log')")
        if path.name=='inspect_variant.py':
            source=source.replace('    audit(1);before=',"    spatial=sim.lib.gd_diag_native_spatial_stat;spatial.argtypes=[ctypes.c_uint];spatial.restype=ctypes.c_uint64\n    spatial_before=[spatial(i) for i in range(4)]\n    audit(1);before=")
            source=source.replace("    args.out.write_text", "    report['spatial_coverage']=dict(zip(('lookups','hits','object_dedup','fallbacks'),[spatial(i)-spatial_before[i] for i in range(4)]))\n    assert all(report['spatial_coverage'][key]>0 for key in ('lookups','hits','object_dedup'))\n    args.out.write_text")
        if path.name=='verify_installed.py':
            source=source.replace("'dispatch_chain_tests.json'","'dispatch_chain_tests.json','spatial_tests.json'")
            source=source.replace("'dispatch_chain_production_cases.json'","'dispatch_chain_production_cases.json','spatial_production_cases.json'")
        if path.name=='save_checkpoint.py':
            source=source.replace('    audit=json.loads',"    paths.update(STAGE/p for p in ('prepare_native_spatial.py','test_native_spatial.cpp','probe_native_spatial.py','prototype_native_spatial_bundle.py','preflight_native_spatial_bundle.py','setup_spatial_bundle.py'))\n    paths.update(p for p in (WORK.parent/'spatial_probe').iterdir() if p.is_file())\n    audit=json.loads",1)
            source=source.replace('perf: flatten behavior and event callback dispatch chains','perf: combine spatial lookup and stable object deduplication').replace('backup: preserve verified behavior and callback dispatch chains','backup: preserve verified spatial queries')
        ast.parse(source,filename=path.name);(WORK/path.name).write_text(source,encoding='utf8',newline='\n')
    for name in ('member_probe_cases.hpp','native_property_test_cases.hpp'):(WORK/name).write_bytes((OLD/name).read_bytes())
    plan=json.loads((OLD/'evaluation_plan.json').read_bytes())
    plan.update(baseline_dll_sha256=BASE,verified_remote_backup=ARCHIVE,components=['single native dictionary lookup','stable object pointer deduplication'],
                retained_deployed_components=['member pointers','character state reuse','static consumers','fixed setup tables','behavior and callback chains'],
                excluded=['layout changes','callback reordering','changed arithmetic or RNG','global mutation watchers'],local_original_dll_cases=11760)
    plan['required'][0]='11760 new spatial cases against actual39c5 DLL plus retained component regressions'
    (WORK/'evaluation_plan.json').write_text(json.dumps(plan,indent=2)+'\n',encoding='utf8')
    print('Prepared spatial candidate; same fixed200x4,3x8 AB/BA,2604 truth and first24 raw batches')

if __name__=='__main__':main()
