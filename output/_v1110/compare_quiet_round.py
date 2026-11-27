"""Use the calibrated frozen24-quad protocol for the numerical segment DLL."""
import sys
from prepare_quiet_round import WORK,STAGE
import json
if sys.argv[1]=='timing':
    gate=json.loads((WORK/'complete_correctness_gate.json').read_bytes())
    assert gate['optimization_enabled_full2604']
    assert json.loads((WORK/'formal_quiet_fast_full_tests.json').read_bytes())['passed']
text=(STAGE/'compare_structure_round.py').read_text('utf8').replace('from prepare_structure_round import','from prepare_quiet_round import').replace("'compare_structure_round.py'","'compare_quiet_round.py'")
exec(compile(text,str(STAGE/'compare_structure_round.py'),'exec'),dict(__name__='__main__',__file__=__file__))
