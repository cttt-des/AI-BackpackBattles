"""Prepare complete gates for the enlarged typed-read/arithmetic package."""
import ast
from pathlib import Path

STAGE=Path(__file__).resolve().parent
OLD=STAGE/'native_perf50/typed_read_bundle'
WORK=STAGE/'native_perf50/scalar_math_bundle'


def main():
    for name in ('run_full_gate.py','finish_gate.py','run_release_measurements.py','install_verified.py',
        'save_checkpoint.py','verify_installed.py','qualify_when_ready.py'):
        text=(OLD/name).read_text('utf8').replace('typed_read_bundle','scalar_math_bundle')
        if name=='finish_gate.py':
            text=text.replace('typed_counts=[0,0]','typed_counts=[0,0];numeric_counts=[0]*6')
            text=text.replace("        summary=json.loads", "        numeric=json.loads((root/'native_numeric_audit.json').read_bytes());assert numeric['dll_sha256']==dll and numeric['verifier_exit_code']==0\n        for i,key in enumerate(('add_int','add_real','add_fallback','div_int','div_real','div_fallback')):numeric_counts[i]+=numeric['coverage'][key]\n        summary=json.loads",1)
            text=text.replace('    assert all(value>0 for value in typed_counts)', '    assert numeric_counts[1]>0 and numeric_counts[4]>0\n    assert all(value>0 for value in typed_counts)')
            text=text.replace("'typed_read_coverage':dict", "'numeric_coverage':dict(zip(('add_int','add_real','add_fallback','div_int','div_real','div_fallback'),numeric_counts)),\n        'typed_read_coverage':dict",1)
        if name=='verify_installed.py':
            text=text.replace("'typed_read_test.json','property_test.json'", "'typed_read_test.json','numeric_math_differential.json','numeric_barrier_build_proof.json','property_test.json'")
            text=text.replace("    assert all(value>0 for value in audit['typed_read_coverage'].values())", "    assert audit['numeric_coverage']['add_real']>0 and audit['numeric_coverage']['div_real']>0\n    assert all(value>0 for value in audit['typed_read_coverage'].values())")
            text=text.replace("'typed_read_coverage':audit['typed_read_coverage'],", "'typed_read_coverage':audit['typed_read_coverage'],'numeric_coverage':audit['numeric_coverage'],")
        if name=='save_checkpoint.py':
            text=text.replace("'native_typed_read_audit.json','summary.json'", "'native_typed_read_audit.json','native_numeric_audit.json','summary.json'")
            text=text.replace('    audit=json.loads', "    paths.update(STAGE/p for p in ('prototype_native_typed_read_bundle.py','analyze_native_typed_reads.py','prototype_native_scalar_math_bundle.py','setup_scalar_math_bundle.py','setup_scalar_math_qualification.py','test_native_numeric_math.cpp'))\n    prior=WORK.parent/'typed_read_bundle'\n    paths.update(p for p in prior.iterdir() if p.is_file() and p.suffix in ('.py','.json','.hpp','.txt','.log','.dll'))\n    paths.update(p for p in (prior/'bundle_src').rglob('*') if p.is_file())\n    audit=json.loads",1)
            text=text.replace('perf: deploy typed pure reads with full replay validation','perf: compose exact scalar arithmetic and typed reads with strict validation')
            text=text.replace('backup: preserve verified typed reads and all strict receipts','backup: preserve verified scalar arithmetic and retained read experiments')
        ast.parse(text,filename=name);(WORK/name).write_text(text,encoding='utf8',newline='\n')
    path=WORK/'audit_verify.py';text=path.read_text('utf8');assert 'numeric_before' not in text
    text=text.replace('typed_read_before=[typed_read_stat(i) for i in range(2)]', 'typed_read_before=[typed_read_stat(i) for i in range(2)]\nnumeric_stat=lib.gd_diag_native_numeric_stat;numeric_stat.argtypes=[ctypes.c_uint];numeric_stat.restype=ctypes.c_uint64\nnumeric_before=[numeric_stat(i) for i in range(6)]')
    text=text.replace('raise SystemExit(exit_code)', "numeric_report={'dll_sha256':report['dll_sha256'],'verifier_exit_code':exit_code,'coverage':dict(zip(('add_int','add_real','add_fallback','div_int','div_real','div_fallback'),[numeric_stat(i)-numeric_before[i] for i in range(6)]))}\n(out/'native_numeric_audit.json').write_text(json.dumps(numeric_report,indent=2)+'\\n',encoding='utf8')\nraise SystemExit(exit_code)")
    ast.parse(text);path.write_text(text,encoding='utf8',newline='\n')
    print('Prepared scalar package truth, measurement, deployment and backup gates')


if __name__=='__main__':main()
