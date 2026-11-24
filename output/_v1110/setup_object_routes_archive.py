"""Prepare scoped preservation and the single rejected-round calibration entry."""
import ast
import re
from prepare_native_object_routes import STAGE,once
from setup_object_routes_bundle import update

SCRIPTS=('probe_native_object_routes.py','analyze_native_object_routes.py','prepare_native_object_routes.py',
    'build_native_object_routes.py','test_native_object_routes.cpp','verify_native_object_routes.py',
    'debug_native_object_route_fixture.py','prototype_native_object_routes_bundle.py','setup_object_routes_bundle.py',
    'preflight_native_object_routes.py','run_object_routes_formal.py','setup_object_routes_archive.py',
    'archive_object_routes_round.py','close_object_routes_round.py','analyze_native_dispatch.py',
    'object_routes_probe_first.log','object_routes_semantic_first.log','object_routes_correctness_first.log',
    'object_routes_correctness_revision2.log','object_routes_preflight_first.log','object_routes_preflight_resumed.log','review_object_routes_release.py','snapshot_object_routes_link_inputs.py','resume_object_routes_link.py','recover_object_routes_build.py','object_routes_recovered_driver_first.log','record_object_routes_deployment.py')

def main():
    out=STAGE/'archive_object_routes_round.py';assert not out.exists()
    text=update((STAGE/'archive_callback_dispatch_round.py').read_text('utf8'))
    text=re.sub(r'^SCRIPTS=.*$','SCRIPTS='+repr(SCRIPTS),text,flags=re.M)
    text=once(text,"(WORK,WORK.parent/'object_routes_prototype',WORK.parent/'bound_callbacks_prototype')", "(WORK,WORK.parent/'object_routes_prototype')")
    text=text.replace('callback-dispatch-backup-20261123','object-routes-backup-20261124')
    text=text.replace('preserve exact-type callback dispatch evaluation','preserve measured object dispatch evaluation')
    text=text.replace('preserve callback dispatch trials with actual production runtime','preserve object route trials with actual production runtime')
    ast.parse(text);out.write_text(text,encoding='utf8',newline='\n')
    out=STAGE/'close_object_routes_round.py';assert not out.exists()
    text=update((STAGE/'close_callback_dispatch_round.py').read_text('utf8'));ast.parse(text)
    out.write_text(text,encoding='utf8',newline='\n')
    print('Prepared scoped archive and one non-release calibration if rejected; no unfinished candidate uploaded')

if __name__=='__main__':main()
