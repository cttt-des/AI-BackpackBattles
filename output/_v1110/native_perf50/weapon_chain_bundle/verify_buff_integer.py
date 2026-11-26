import json
import sys
from pathlib import Path
WORK=Path(__file__).resolve().parent
sys.path.insert(0,str(WORK.parents[1]))
from prepare_native_weapon_chain import sha
from verify_weapon_chain_buff_helpers import verify as helpers
from verify_weapon_chain_buff_methods import verify as methods
if __name__=='__main__':
    target=WORK/'buff_integer_checks';assert not target.exists();target.mkdir()
    a=helpers(WORK/'bundle_src',WORK/'bundle.dll',target/'typed_helper_tests.json')
    b=methods(WORK/'bundle_src',WORK/'bundle.dll',target/'method_tests.json')
    assert a['fixture_sha256']=='243f03fb917c95917eb9589403d204cfa50e9ee73f515c43532d4cd6c848ff82'
    assert b['fixture_sha256']=='1430f88f79fc5fdf27d109701a00eec1d0bb7de987e59486030e5a18fcad3825'
    result=dict(passed=True,cases=a['cases']+b['cases'],dll_sha256=sha(WORK/'bundle.dll'),helper_cases=a['cases'],method_cases=b['cases'])
    assert result['cases']==218400
    (WORK/'buff_integer_tests.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf8')
    print(json.dumps(result),flush=True)
