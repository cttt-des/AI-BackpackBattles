"""Apply the existing immutable screen protocol to the declared combined candidate."""
import json
import sys
import probe_native_damage_records_extended as driver
from prepare_native_damage_combo import WORK,OLD,STAGE,EXPECTED,sha
driver.WORK=WORK
driver.DEPENDENCIES=[STAGE/'test_native_damage_records_extended.cpp',STAGE/'test_native_damage_records.cpp',WORK/'preflight_damage_records.hpp',WORK/'native_event_kernel.hpp',WORK/'damage_state_fields.hpp',WORK/'damage_fixture.hpp']

def main():
    driver.main()
    if '--screen' not in sys.argv:
        filename='matched_correctness.json' if '--matched' in sys.argv else 'extended_correctness.json'
        actual=json.loads((WORK/filename).read_bytes());reference=json.loads((OLD/'extended_correctness.json').read_bytes())
        assert actual['cases']==reference['cases']==12920
        assert actual['case_hashes']==reference['case_hashes'] and actual['legacy_counter_hashes']==reference['legacy_counter_hashes']
        proof=dict(passed=True,cases=12920,baseline_dll_sha256=EXPECTED,record_only_independent_oracle_sha256=sha(OLD/'extended_correctness.json'),combined_case_receipt_sha256=sha(WORK/filename),all_original_hashes_and_legacy_counters_equal=True)
        (WORK/('matched_reference_proof.json' if '--matched' in sys.argv else 'reference_proof.json')).write_text(json.dumps(proof,indent=2)+'\n',encoding='utf8')

if __name__=='__main__':main()
