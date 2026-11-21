"""Compare every event hash with the actual deployment and aggregate audits."""
import hashlib
import json
from pathlib import Path
import subprocess
import sys

WORK=Path(__file__).resolve().parent
STAGE=WORK.parents[1]

def main():
    subprocess.run([sys.executable,'-X','utf8',str(STAGE/'compare_native_event_receipts.py'),
        '--baseline',str(WORK.parent/'item_locality_bundle/bundle_full_gate.json'),
        '--candidate',str(WORK/'bundle_full_gate.json'),
        '--baseline-prefix','native_item_locality_bundle_bundle_',
        '--candidate-prefix','native_property_control_bundle_bundle_',
        '--out',str(WORK/'bundle_vs_deployed_hashes.json')],check=True)
    fields=('generic_hits','funcref_hits','lazy_resolutions','unsupported_types','audit_mismatch','selected_fallback')
    counts=dict.fromkeys(fields,0);fights=0;old_mismatches=0;receipts=[];property_counts=[0,0]
    dll=hashlib.sha256((WORK/'bundle.dll').read_bytes()).hexdigest()
    for folder in sorted(STAGE.glob('native_property_control_bundle_bundle_*')):
        if not folder.is_dir():continue
        root=folder/'cpp' if (folder/'cpp').is_dir() else folder
        audit=json.loads((root/'native_resolved_audit.json').read_bytes())
        legacy=json.loads((root/'native_type_audit.json').read_bytes())
        prop=json.loads((root/'native_property_audit.json').read_bytes());assert prop['dll_sha256']==dll and prop['verifier_exit_code']==0
        property_counts[0]+=prop['coverage']['field_hits'];property_counts[1]+=prop['coverage']['selected_fallback']
        summary=json.loads((root/'summary.json').read_bytes())
        assert audit['dll_sha256']==legacy['dll_sha256']==summary['dll_sha256']==dll
        assert audit['verifier_exit_code']==legacy['verifier_exit_code']==0
        assert summary['passed']==summary['total']
        fights+=summary['total'];receipts.append(str(root))
        for field in fields:counts[field]+=audit['coverage'][field]
        old_mismatches+=legacy['coverage']['type_mismatch']
    assert property_counts[0]>0
    assert fights==2604 and counts['audit_mismatch']==old_mismatches==0
    report={'candidate_dll_sha256':dll,'fights':fights,'coverage':counts,
        'old_event_kernel_type_mismatches':old_mismatches,'receipts':receipts,'property_coverage':dict(zip(('field_hits','selected_fallback'),property_counts))}
    (WORK/'full_type_audit.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8',newline='\n')
    print(json.dumps(report,indent=2))

if __name__=='__main__':main()
