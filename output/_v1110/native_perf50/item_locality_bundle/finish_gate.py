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
        '--baseline',str(WORK.parent/'eager_trace_bundle/bundle_full_gate.json'),
        '--candidate',str(WORK/'bundle_full_gate.json'),
        '--baseline-prefix','native_eager_trace_bundle_bundle_',
        '--candidate-prefix','native_item_locality_bundle_bundle_',
        '--out',str(WORK/'bundle_vs_deployed_hashes.json')],check=True)
    fields=('generic_hits','funcref_hits','lazy_resolutions','unsupported_types','audit_mismatch','selected_fallback')
    counts=dict.fromkeys(fields,0);fights=0;old_mismatches=0;receipts=[]
    dll=hashlib.sha256((WORK/'bundle.dll').read_bytes()).hexdigest()
    for folder in sorted(STAGE.glob('native_item_locality_bundle_bundle_*')):
        if not folder.is_dir():continue
        root=folder/'cpp' if (folder/'cpp').is_dir() else folder
        audit=json.loads((root/'native_resolved_audit.json').read_bytes())
        legacy=json.loads((root/'native_type_audit.json').read_bytes())
        summary=json.loads((root/'summary.json').read_bytes())
        assert audit['dll_sha256']==legacy['dll_sha256']==summary['dll_sha256']==dll
        assert audit['verifier_exit_code']==legacy['verifier_exit_code']==0
        assert summary['passed']==summary['total']
        fights+=summary['total'];receipts.append(str(root))
        for field in fields:counts[field]+=audit['coverage'][field]
        old_mismatches+=legacy['coverage']['type_mismatch']
    assert fights==2604 and counts['audit_mismatch']==old_mismatches==0
    report={'candidate_dll_sha256':dll,'fights':fights,'coverage':counts,
        'old_event_kernel_type_mismatches':old_mismatches,'receipts':receipts}
    (WORK/'full_type_audit.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8',newline='\n')
    print(json.dumps(report,indent=2))

if __name__=='__main__':main()
