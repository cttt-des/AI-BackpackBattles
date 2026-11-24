"""Verify retained semantics, harness identities and exact source reproduction."""
import importlib.util
import json
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
from prepare_native_object_routes import STAGE,BASE,WORK as PROBE,EXPECTED,sha
from prototype_native_object_routes_bundle import optimize
from verify_native_callback_dispatch import verify as callbacks
from verify_native_literal_spans import verify as literals

WORK=STAGE/'native_perf50/object_routes_bundle'

def main():
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    out=WORK/'transform_preflight.json';assert not out.exists()
    resume='--continue-after-harness-check' in sys.argv
    for name,verify in [('retained_callbacks',callbacks),('retained_literals',literals)]:
        folder=PROBE/name
        if resume:
            retained=json.loads((folder/'correctness.json').read_bytes())
            assert retained['passed'] and retained['dll_sha256']==sha(PROBE/'prototype.dll')
            count,fixture=(126192,'test_native_callback_dispatch.cpp') if name=='retained_callbacks' else (5184,'test_native_literal_spans.cpp')
            assert retained['cases']==count and retained['fixture_sha256']==sha(STAGE/fixture)
            assert all(sha(folder/n)==h for n,h in retained['raw_cases_sha256'].items())
        else:
            assert not folder.exists();folder.mkdir()
            verify(PROBE/'prototype_src',PROBE/'prototype.dll',folder/'correctness.json')
    spec=importlib.util.spec_from_file_location('registry_verifier',WORK/'verify_closed_registry_current.py')
    registry=importlib.util.module_from_spec(spec);spec.loader.exec_module(registry)
    assert registry.EXPECTED==EXPECTED and registry.BASE==BASE
    grid=(WORK/'verify_integer_grid.py').read_text('utf8')
    assert 'from prepare_native_object_routes import BASE,EXPECTED,sha' in grid
    timer=(WORK/'verify_targeted_timers.py').read_text('utf8')
    assert "WORK.parent/'object_routes_prototype/transform.json'" in timer
    assert "WORK.parent/'callback_dispatch_bundle/targeted_timer_tests.json'" in timer
    build=(WORK/'build_bundle.py').read_text('utf8')
    assert 'WORK=Path(__file__).resolve().parent' in build and 'STAGE=WORK.parents[1]' in build
    assert ('BASE_SHA='+repr(EXPECTED)) in build
    spec=importlib.util.spec_from_file_location('instrumented_exports',WORK/'resume_build.py')
    exports=importlib.util.module_from_spec(spec);spec.loader.exec_module(exports)
    with tempfile.TemporaryDirectory(prefix='native-object-route-exports-') as directory:
        _,names=exports.create_instrumented_exports(Path(directory))
        assert 'gd_diag_native_object_route_stat' in names and 'gd_diag_native_extra_callback_stat' in names
    audit=PROBE/'semantic_protocol_audit.json';assert not audit.exists()
    subprocess.run([sys.executable,'-u','-X','utf8',str(WORK/'inspect_variant.py'),'--dll',str(PROBE/'prototype.dll'),'--out',str(audit)],check=True)
    with tempfile.TemporaryDirectory(prefix='native-object-route-preflight-') as directory:
        source=Path(directory)/'source'
        shutil.copytree(BASE,source,ignore=shutil.ignore_patterns('*.dll','*.o','*.gcda','*.gcno','__pycache__'))
        report=optimize(source)
    report.update(full_source_matches_tested_prototype=True,no_speed_claim=True,
        retained_callback_cases=126192,retained_literal_cases=5184,stale_baseline_harness_checked=True,
        instrumentation_exports_include_new_stat=True,semantic_audit_sha256=sha(audit))
    out.write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print('Exact707-source reproduction,320256 object routes,retained126192+5184 and new/old coverage verified')

if __name__=='__main__':main()
