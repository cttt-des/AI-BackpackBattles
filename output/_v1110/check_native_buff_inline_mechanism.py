"""Check that the new source changes the intended compiler mechanism."""
import json
import subprocess
from prepare_native_buff_inline_types import STAGE,WORK,HELPERS,sha,verify_projection

def main():
    verify_projection(WORK/'prototype_src')
    old=json.loads((STAGE/'native_perf50/buff_integer_kernel_bundle/machine_code_receipt.json').read_bytes())
    before=[(n,c) for n,c in old['static_direct_call_sites'] if 'native_buff_integer_' in n or 'native_buff_boolean_' in n]
    assert sum(c for n,c in before)==11
    symbols=subprocess.check_output(['D:/mingw64/bin/nm.exe','--defined-only','prototype.dll'],cwd=WORK,text=True)
    after=[l for l in symbols.splitlines() if 'native_buff_integer_' in l or 'native_buff_boolean_' in l]
    assert not after
    assert HELPERS.count('__attribute__((always_inline))')==6
    assert 'from_int(gd::gd_coerce_int(a).i)' in HELPERS and 'from_bool(gd::gd_coerce_bool(a).b)' in HELPERS
    result=dict(passed=True,semantic_dll_sha256=sha(WORK/'prototype.dll'),previous_formal_dll_sha256=old['dll_sha256'],
        previous_static_direct_helper_sites=before,current_defined_outlined_helper_symbols=after,
        all_six_helpers_forced_inline=True,coercion_return_kinds_constructed_on_both_branches=True,
        no_speed_claim=True,scope='Mechanism check in normal semantic prototype; formal PGO must independently retain zero helper calls')
    out=WORK/'mechanism_probe.json';assert not out.exists();out.write_text(json.dumps(result,indent=2)+'\n',encoding='utf8')
    print(json.dumps(result),flush=True)

if __name__=='__main__':main()
