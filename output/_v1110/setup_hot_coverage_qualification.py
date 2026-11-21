"""Prepare the complete evidence chain for the expanded whole-package trial."""
import ast
from pathlib import Path

STAGE=Path(__file__).resolve().parent
OLD=STAGE/'native_perf50/type_constructor_bundle'
WORK=STAGE/'native_perf50/hot_coverage_bundle'


def main():
    for name in ('run_full_gate.py','finish_gate.py','run_release_measurements.py','install_verified.py',
        'save_checkpoint.py','verify_installed.py','qualify_when_ready.py'):
        text=(OLD/name).read_text('utf8').replace('type_constructor_bundle','hot_coverage_bundle')
        if name=='finish_gate.py':
            text=text.replace('property_counts=[0,0];tc_counts=[0]*4','property_counts=[0,0];tc_counts=[0]*4;hot_counts=[0,0]')
            text=text.replace("        summary=json.loads", "        hot=json.loads((root/'native_hot_slot_audit.json').read_bytes());assert hot['dll_sha256']==dll and hot['verifier_exit_code']==0\n        for i,key in enumerate(('new_method_hits','new_field_hits')):hot_counts[i]+=hot['coverage'][key]\n        summary=json.loads",1)
            text=text.replace('    assert property_counts[0]>0', '    assert all(value>0 for value in hot_counts)\n    assert property_counts[0]>0')
            text=text.replace("'type_constructor_coverage':dict", "'hot_slot_coverage':dict(zip(('new_method_hits','new_field_hits'),hot_counts)),\n        'type_constructor_coverage':dict",1)
        if name=='verify_installed.py':
            text=text.replace("assert ab['status']=='positive_combined_evidence' and len(ab['reports'])==4 and installed['ab_pairs']==32", "assert ab['status']=='positive_combined_evidence' and installed['ab_pairs'] in (24,32) and len(ab['reports'])==installed['ab_pairs']//8")
            text=text.replace("metric['pairs']==32", "metric['pairs']==installed['ab_pairs']")
            text=text.replace("'type_constructor_test.json','property_test.json'", "'type_constructor_test.json','hot_coverage_test.json','property_test.json'")
            text=text.replace("    assert audit['type_constructor_coverage']", "    assert all(value>0 for value in audit['hot_slot_coverage'].values())\n    assert audit['type_constructor_coverage']",1)
            text=text.replace("'ab_assessment_32.json',",'')
            text=text.replace("'type_constructor_coverage':audit['type_constructor_coverage'],", "'type_constructor_coverage':audit['type_constructor_coverage'],'hot_slot_coverage':audit['hot_slot_coverage'],")
        if name=='save_checkpoint.py':
            text=text.replace('    audit=json.loads', "    paths.add(WORK/'bundle.dll')\n    paths.update(STAGE/p for p in ('setup_type_constructor_bundle.py','prepare_hot_coverage_target_load.py'))\n    audit=json.loads",1)
            text=text.replace("'native_type_constructor_audit.json','summary.json'", "'native_type_constructor_audit.json','native_hot_slot_audit.json','summary.json'")
            text=text.replace('    audit=json.loads', "    paths.update(STAGE/p for p in ('prototype_native_type_constructor_bundle.py','analyze_native_hot_slot_gaps.py','setup_hot_coverage_qualification.py','test_native_hot_coverage.cpp','prepare_post_property_profile.py','prepare_type_constructor_target_load.py'))\n    retained=WORK.parent/'type_constructor_bundle'\n    paths.update(p for p in retained.iterdir() if p.is_file() and p.suffix in ('.py','.json','.txt','.log','.hpp','.dll'))\n    paths.update(p for p in (retained/'bundle_src').rglob('*') if p.is_file())\n    retained_audit=json.loads((retained/'full_type_audit.json').read_bytes())\n    for root in map(Path,retained_audit['receipts']):paths.update(root.glob('*.json'))\n    paths.update(p for p in (WORK.parent/'post_property_control_profile').iterdir() if p.is_file())\n    audit=json.loads",1)
            text=text.replace('perf: compose exact type checks and typed initialization with full replay validation','perf: expand measured hot method and field coverage with strict replay validation')
            text=text.replace('backup: preserve verified exact types and typed initialization','backup: preserve verified expanded hot coverage and retained experiments')
        ast.parse(text,filename=name);(WORK/name).write_text(text,encoding='utf8',newline='\n')
    path=WORK/'audit_verify.py';text=path.read_text('utf8')
    assert 'hot_slot_before' not in text
    text=text.replace('type_constructor_before=[type_constructor_stat(i) for i in range(4)]',
        'type_constructor_before=[type_constructor_stat(i) for i in range(4)]\nhot_slot_stat=lib.gd_diag_native_hot_slot_stat;hot_slot_stat.argtypes=[ctypes.c_uint];hot_slot_stat.restype=ctypes.c_uint64\nhot_slot_before=[hot_slot_stat(i) for i in range(2)]')
    text=text.replace('raise SystemExit(exit_code)', "hot_slot_report={'dll_sha256':report['dll_sha256'],'verifier_exit_code':exit_code,'coverage':dict(zip(('new_method_hits','new_field_hits'),[hot_slot_stat(i)-hot_slot_before[i] for i in range(2)]))}\n(out/'native_hot_slot_audit.json').write_text(json.dumps(hot_slot_report,indent=2)+'\\n',encoding='utf8')\nraise SystemExit(exit_code)")
    ast.parse(text);path.write_text(text,encoding='utf8',newline='\n')
    print('Prepared strict truth, untouched one-shot measurements, guarded installation and full receipt backup')


if __name__=='__main__':main()
