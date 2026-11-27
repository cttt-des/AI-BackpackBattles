"""Replay all30 production Python fights against the fresh Godot baseline."""
import importlib.util,json,sys
from prepare_ordering_correctness import REPO,WORK,sha,save
def main():
    sys.path.insert(0,str(REPO))
    import gd_core_py._rt as rt
    assert __import__('pathlib').Path(rt.__file__).resolve()==(REPO/'gd_core_py/_rt.pyd').resolve()
    baseline=WORK.with_name(WORK.name+'_revision1')/'python_battle_godot_project/lineup_result.txt'
    spec=importlib.util.spec_from_file_location('ordering_installed_battles',REPO/'tools/check_gd_core_engine.py');module=importlib.util.module_from_spec(spec);spec.loader.exec_module(module)
    module.BASELINE=str(baseline);module.OUT_PATH=str(WORK/'post_install_python_fresh30_results.txt');sys.argv=[str(REPO/'tools/check_gd_core_engine.py')]
    assert len(module.parse_rows(baseline.read_text('utf8')))==30
    assert module.main()==0
    actual=module.parse_rows(__import__('pathlib').Path(module.OUT_PATH).read_text('utf8'));expected=module.parse_rows(baseline.read_text('utf8'));assert actual==expected and len(actual)==30
    save('post_install_python_fresh_battle.json',dict(passed=True,fights=30,rt_sha256=sha(REPO/'gd_core_py/_rt.pyd'),original_Godot_reference_sha256=sha(baseline),actual_sha256=sha(__import__('pathlib').Path(module.OUT_PATH)),winner_time_health_and_all_probe_summaries_exact=True))
if __name__=='__main__':main()
