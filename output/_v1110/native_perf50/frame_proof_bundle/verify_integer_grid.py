import json
from pathlib import Path
import sys
WORK=Path(__file__).resolve().parent
STAGE=WORK.parents[1]
sys.path.insert(0,str(STAGE))
from prepare_native_frame_proof import BASE,EXPECTED,sha
import verify_native_integer_grid_dict as dictionaries
from verify_native_integer_grid_queries import verify as queries

def main():
    source=WORK/'bundle_src';dll=WORK/'bundle.dll';out=WORK/'integer_grid_tests.json'
    assert not out.exists()
    dictionaries.BASE=BASE;dictionaries.EXPECTED=EXPECTED
    a=dictionaries.verify(source,dll,WORK/'integer_grid_dictionary_tests.json')
    b=queries(source,dll,WORK/'integer_grid_query_tests.json')
    scalar=STAGE/'native_perf50/integer_grid_prototype/slot_correctness.json'
    assert json.loads(scalar.read_bytes())['helper_sha256']==sha(source/'native_integer_grid.hpp')
    result=dict(passed=True,dll_sha256=sha(dll),dictionary_cases=a['cases'],query_cases=b['cases'],scalar_cases=132576,
        actual_optimized_dll_independent_oracles=True,fast_dictionary_queries=a['fast_queries'],
        forced_spatial_fast_queries=b['variants']['forced_grid']['fast_queries'],layouts=a['new_layout'],
        receipt_sha256={name:sha(WORK/name) for name in ('integer_grid_dictionary_tests.json','integer_grid_query_tests.json')},
        scalar_receipt_sha256=sha(scalar))
    out.write_text(json.dumps(result,indent=2)+'\n',encoding='utf8');print(json.dumps(result,indent=2))
if __name__=='__main__':main()
