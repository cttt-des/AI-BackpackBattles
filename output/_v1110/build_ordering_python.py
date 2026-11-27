"""Compile the changed Python runtime in an isolated candidate package."""
import importlib.util,json,os,sys,psutil
from pathlib import Path
from prepare_ordering_correctness import REPO,WORK,sha,save

def main():
    process=psutil.Process();process.nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    target=WORK/'python_pending';assert (target/'gd_core_py/_rt.py').exists()
    (target/'tools').mkdir(exist_ok=True)
    spec=importlib.util.spec_from_file_location('ordering_cython_builder',REPO/'tools/build_cython.py');module=importlib.util.module_from_spec(spec);spec.loader.exec_module(module)
    module.ROOT=str(target);module.BACKEND='msvc';module.OBJ_DIR=str(target/'build/cython_objs')
    before=sha(target/'gd_core_py/_rt.pyd')
    for name in ('GD_LTO','GD_OS','GD_AVX2','GD_PGO','GD_CY_DIRECTIVES'):assert not os.environ.get(name),name
    module.build_one('gd_core_py/_rt.py')
    assert sha(target/'gd_core_py/_rt.pyd')!=before
    save('python_build.json',dict(passed=True,pid=process.pid,created=process.create_time(),old_rt_pyd_sha256=before,new_rt_pyd_sha256=sha(target/'gd_core_py/_rt.pyd'),rt_source_sha256=sha(target/'gd_core_py/_rt.py'),helper_sha256=sha(target/'gd_core_py/_godot_sort.py'),typed_pxd_unchanged=sha(target/'gd_core_py/_rt.pxd')==sha(REPO/'gd_core_py/_rt.pxd'),backend='MSVC O2, original floating defaults, no PGO reuse',binding_true=True,live_rt_unchanged=sha(REPO/'gd_core_py/_rt.pyd')==before))
    print('Isolated compiled Python runtime ready',flush=True)
if __name__=='__main__':main()
