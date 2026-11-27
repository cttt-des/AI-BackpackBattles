import sys
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[2]))
import json
import sys
from pathlib import Path
WORK=Path(__file__).resolve().parent
sys.path.insert(0,str(WORK.parents[1]))
sys.path.insert(0,str(Path(__file__).resolve().parent))
from prepare_quiet_retained import sha
from verify_assembly_membership_buff_helpers import verify as helpers
sys.path.insert(0,str(WORK))
from verify_assembly_membership_buff_methods import verify as methods
import verify_assembly_membership_buff_methods as methods_module
assert Path(methods_module.__file__).resolve().parent==WORK
if __name__=='__main__':
    target=WORK/'buff_integer_checks';target.mkdir(exist_ok=True)
    receipt=target/'typed_helper_tests.json'
    if receipt.exists():
        from prepare_quiet_retained import EXPECTED
        a=json.loads(receipt.read_bytes())
        assert a['passed'] and a['cases']==204288 and a['operation_checks']==806160
        assert a['dll_sha256']==sha(WORK/'bundle.dll') and a['baseline_dll_sha256']==EXPECTED
        assert a['unchanged_fallback_runtime_cross_compiler_hash_equal']
        raw=target/'typed_helper_tests_checks'
        for name,digest in a['raw_sha256'].items():assert sha(raw/name)==digest
        assert (raw/'baseline_cases.json').read_bytes()==(raw/'candidate_cases.json').read_bytes()
        print('Retained verified full helper observations',flush=True)
    else:a=helpers(WORK/'bundle_src',WORK/'bundle.dll',receipt)
    b=methods(WORK/'bundle_src',WORK/'bundle.dll',target/'method_tests.json')
    assert a['fixture_sha256']=='243f03fb917c95917eb9589403d204cfa50e9ee73f515c43532d4cd6c848ff82'
    assert b['fixture_sha256']=='1430f88f79fc5fdf27d109701a00eec1d0bb7de987e59486030e5a18fcad3825'
    result=dict(passed=True,cases=a['cases']+b['cases'],dll_sha256=sha(WORK/'bundle.dll'),helper_cases=a['cases'],method_cases=b['cases'])
    assert result['cases']==218400
    (WORK/'buff_integer_tests.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf8')
    print(json.dumps(result),flush=True)
