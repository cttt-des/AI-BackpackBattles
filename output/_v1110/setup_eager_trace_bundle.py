"""Prepare a fresh composition against the accepted runtime, without sparse state."""
from pathlib import Path

STAGE=Path(__file__).resolve().parent
OLD=STAGE/'native_perf50/sparse_timer_lazy_bundle'
WORK=STAGE/'native_perf50/eager_trace_bundle'

def main():
    WORK.mkdir()
    for name in ('build_bundle.py','resume_build.py','validate_then_compare.py','verify_resolved.py',
                 'prepare_regeneration.py','test_regeneration_guards.py','inspect_variant.py',
                 'run_comparison.py','assess_resolved.py','audit_verify.py'):
        text=(OLD/name).read_text('utf8')
        text=text.replace('sparse_timer_lazy_bundle','eager_trace_bundle').replace('native-sparse-timer-lazy-','native-eager-trace-')
        if name=='build_bundle.py':
            text=text.replace("ARCHIVE='8255e52317f8b160e5ba45cffa2b943ba9196c7d'","ARCHIVE='7da8b44d591caa4f65a7c1a177d1a81b0950dba0'")
            text=text.replace('from prototype_native_eager_trace_bundle import optimize','from prototype_native_eager_trace_bundle import optimize')
        if name=='prepare_regeneration.py':
            text=text.replace("OLD=WORK.parent/'sparse_timer_bundle'","OLD=WORK.parent/'scan_bundle'")
            text=text.replace("'native_perf50/sparse_timer_bundle'","'native_perf50/scan_bundle'")
        if name=='validate_then_compare.py':
            text=text.replace("    run('probe_epoch.py','epoch_probe.log')\n",'')
        if name=='verify_resolved.py':
            begin=text.index('    tests=((')
            end=text.index('("test_native_variant_inline.cpp"',begin)
            text=text[:begin]+'    tests=(("test_native_eager_rows.cpp","eager_rows_test.json",[]),\n           '+text[end:]
            anchor='    tests=(('
            differential='''    trace_results={}
    for label,header in [('baseline',STAGE/'sim_native/native_sim_cpp/native_sim'),('candidate',src)]:
        folder=directory/label
        executable=folder/'addspeed_trace.exe'
        subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O2','-std=c++20','-ffp-contract=off','-I',str(header),str(STAGE/'test_native_addspeed_trace.cpp'),str(folder/'libgdcore.dll'),'-o',str(executable)],check=True)
        trace_results[label]=json.loads(subprocess.check_output([str(executable)],text=True))
    assert trace_results['baseline']==trace_results['candidate'],trace_results
    (WORK/'addspeed_trace_differential.json').write_text(json.dumps({'passed':True,'dll_sha256':digest(dll),'results':trace_results},indent=2)+'\\n',encoding='utf8')
    print('AddSpeed diagnostic and fallback differential cases matched baseline',flush=True)
'''
            text=text.replace(anchor,differential+anchor,1)
        (WORK/name).write_text(text,encoding='utf8',newline='\n')
    # Keep preparation and comparison sequential; no auto timing until the new
    # diagnostic test exists and all source/behavior checks pass.
    print(WORK)

if __name__=='__main__':main()
