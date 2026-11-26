"""Await the identified live build, then validate before any formal timing."""
import argparse
import hashlib
import json
from pathlib import Path
import subprocess
import sys
import psutil

WORK=Path(__file__).resolve().parent
STAGE=WORK.parents[1]

def run(script,log,*args):
    print('Starting '+script,flush=True)
    with (WORK/log).open('w',encoding='utf8') as output:
        subprocess.run([sys.executable,'-u','-X','utf8',str(WORK/script),*map(str,args)],stdout=output,stderr=subprocess.STDOUT,check=True)
    print('Passed '+script,flush=True)

def main():
    parser=argparse.ArgumentParser();parser.add_argument('--build-pid',type=int,required=True)
    parser.add_argument('--created',type=float,required=True);args=parser.parse_args()
    process=None
    if args.build_pid>0:
        try:process=psutil.Process(args.build_pid)
        except psutil.NoSuchProcess:pass
    if process is not None:
        # Native shell argument formatting may round the sub-millisecond fraction.
        assert abs(process.create_time()-args.created)<0.001,(process.create_time(),args.created)
        assert any('container_builtins_bundle/build_bundle.py' in part.replace('\\','/') for part in process.cmdline())
        print('Waiting on live build PID '+str(process.pid),flush=True)
        while process.is_running():
            try:process.wait(timeout=30)
            except psutil.TimeoutExpired:continue
            break
    dll=WORK/'bundle.dll'
    assert dll.is_file(),'Build ended without a release DLL; inspect original build log, do not restart automatically'
    assert (WORK/'fresh_profile_source.json').is_file(),'Use the fully trained final source candidate'
    assert hashlib.sha256((STAGE/'sim_native/native_sim_cpp/native_sim/libgdcore.dll').read_bytes()).hexdigest()=='0a6d24f459eb1011a0bfcc1bc5c4188c1ca67add410b9caf0e04c8f5d30d44d4'
    print('Freezing release object/compiler evidence before any timing',flush=True)
    subprocess.run([sys.executable,'-u','-X','utf8',str(STAGE/'verify_container_builtins_build_options.py')],check=True)
    run('prepare_regeneration.py','regeneration_pipeline.log')
    run('generate_property_tests.py','property_test_generation.log')
    run('generate_type_constructor_tests.py','type_constructor_test_generation.log')
    run('verify_event_identity.py','event_identity_tests.log')
    run('verify_lazy_diagnostics.py','lazy_diagnostics_tests.log')
    run('verify_components.py','component_tests.log')
    run('verify_static_collections.py','static_collections_tests.log')
    run('verify_static_setup.py','static_setup_tests.log')
    run('verify_dispatch_chain.py','dispatch_chain_tests.log')
    run('verify_spatial.py','spatial_tests.log')
    run('verify_motion_indices.py','motion_indices_tests.log')
    run('verify_targeted_timers.py','targeted_timer_tests.log')
    run('verify_active_cooldowns.py','active_cooldown_tests.log')
    run('verify_container_builtins.py','container_builtins_tests.log')
    run('verify_scalar_truth.py','scalar_truth_tests.log')
    run('verify_private_snapshots.py','private_snapshots_tests.log')
    run('verify_control_word.py','control_word_tests.log')
    run('verify_display_storage.py','display_storage_tests.log')
    run('verify_integer_grid.py','integer_grid_tests.log')
    run('verify_event_factory.py','event_factory_tests.log')
    run('verify_literal_spans.py','literal_span_tests.log')
    run('verify_callback_dispatch.py','callback_dispatch_tests.log')
    run('verify_object_routes.py','object_routes_tests.log')
    run('verify_resolved.py','verify.log')
    run('inspect_variant.py','release_audit.log','--dll',dll,'--out',WORK/'release_audit.json')
    run('test_regeneration_guards.py','regeneration_guards.log')
    run('test_full_regeneration.py','full_regeneration.log')
    # Only this process and the two serial A/B workers remain; no more preparation.
    assert json.loads((WORK/'buff_chunk_differential.json').read_bytes())['passed']
    run('run_comparison.py','comparison.log')
    print('All preflight checks and three comparison groups completed; deployment still gated',flush=True)

if __name__=='__main__':main()
