"""Exercise the production Python assembly path on its56 Godot reference fights."""
import argparse,importlib.util,json,sys
from pathlib import Path
STAGE=Path(__file__).resolve().parent
REPO=STAGE.parents[1]
WORK=STAGE/'native_perf50/ordering_correctness_bundle'

def main():
    parser=argparse.ArgumentParser();parser.add_argument('--candidate',action='store_true');a=parser.parse_args()
    sys.path.insert(0,str(REPO))
    if a.candidate:sys.path.insert(0,str(WORK/'python_pending'))
    import gd_core_py._rt as rt
    label='candidate' if a.candidate else 'baseline'
    if a.candidate:assert Path(rt.__file__).resolve().is_relative_to((WORK/'python_pending').resolve())
    spec=importlib.util.spec_from_file_location('ordering_python_battle_checker',REPO/'tools/check_gd_core_engine.py');module=importlib.util.module_from_spec(spec);spec.loader.exec_module(module)
    module.OUT_PATH=str(WORK/(label+'_python_56_results.txt'));sys.argv=[str(REPO/'tools/check_gd_core_engine.py')]
    status=module.main()
    report=dict(passed=status==0,rt_module=rt.__file__,original_godot_baseline=str(module.BASELINE),result=str(module.OUT_PATH),exit_code=status)
    (WORK/(label+'_python_battle_check.json')).write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    raise SystemExit(status)
if __name__=='__main__':main()
