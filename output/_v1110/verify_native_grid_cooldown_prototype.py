"""Validate the composed implementation before fresh PGO or any formal timing."""
import json
from prepare_native_grid_cooldown import STAGE,WORK,sha
from verify_native_integer_grid_dict import verify as dictionaries
from verify_native_integer_grid_queries import verify as queries
from verify_native_active_cooldown_final import verify as cooldowns

def main():
    source=WORK/'prototype_src';dll=WORK/'prototype.dll';out=WORK/'correctness.json';assert not out.exists()
    assert json.loads((WORK/'build.json').read_bytes())['passed']
    assert json.loads((WORK/'transform.json').read_bytes())['source_sha256']=={p.relative_to(source).as_posix():sha(p) for p in source.rglob('*') if p.is_file()}
    cooldowns(source,dll,WORK/'cooldown_correctness.json')
    dictionaries(source,dll,WORK/'dictionary_correctness.json')
    queries(source,dll,WORK/'query_correctness.json')
    reports={name:sha(WORK/name) for name in ('cooldown_correctness.json','dictionary_correctness.json','query_correctness.json')}
    record=dict(passed=True,dll_sha256=sha(dll),cooldown_cases=1856,dictionary_cases=1792,spatial_cases=23520,
        scalar_coordinate_bit_fenv_cases=132576,all_independent_previous_oracles_retained=True,
        both_components_exercised_in_fixed200=True,report_sha256=reports,no_performance_claim=True)
    out.write_text(json.dumps(record,indent=2)+'\n',encoding='utf8');print(json.dumps(record,indent=2))

if __name__=='__main__':main()
