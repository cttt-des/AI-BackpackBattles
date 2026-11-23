"""Run one non-release calibration; retain an uncovered 20% point as missing."""
import hashlib
import json
from pathlib import Path
import subprocess
import sys
import psutil

STAGE = Path(__file__).resolve().parent
WORK = STAGE / 'native_perf50/event_factory_bundle'

def sha(p):
    return hashlib.sha256(p.read_bytes()).hexdigest()

def main():
    psutil.Process().nice(psutil.NORMAL_PRIORITY_CLASS)
    decision = json.loads((WORK / 'candidate_decision.json').read_bytes())
    assert decision['status'] in ('inconclusive_retained', 'consistent_regression_bundle_only') and decision['not_deployed']
    dll = WORK / 'bundle.dll'
    assert sha(dll) == decision['candidate_dll_sha256']
    raw, fit, receipt = [WORK / n for n in (
        'rejected_load_calibration.json', 'rejected_load20.json', 'rejection_receipt.json')]
    assert not any(p.exists() for p in (raw, fit, receipt)), 'Never repeat observed calibration'
    subprocess.run([sys.executable, '-u', '-X', 'utf8', str(STAGE / 'bench_native_load_calibration.py'),
                    '--dll', str(dll), '--warmup-seconds', '30', '--out', str(raw)], check=True)
    with (WORK / 'rejected_load20_fit.log').open('wb') as log:
        fitted = subprocess.run([sys.executable, '-X', 'utf8', str(STAGE / 'fit_native_serial_load.py'),
                                 str(raw), '--reference-load', '20', '--out', str(fit)],
                                stdout=log, stderr=subprocess.STDOUT)
    report = json.loads(raw.read_bytes())
    assert report['dll_sha256'] == sha(dll)
    assert report['inputs_sha256'] == 'd94b16d42cc88e9a3850a77c9360b9c4c4fdd676cb252e463044a903db2a5fef'
    assert report['results_sha256'] == '2e74b45caa87f7ee6ac72ffc35d98cc8db140b47031614d26542e183cef5d2c9'
    assert report['workers'] == 1 and report['repeat'] == len(report['samples']) == 24
    loads = [r['background_load_pct'] for r in report['samples']]
    covered = min(loads) <= 20 <= max(loads)
    if not covered:
        assert fitted.returncode != 0 and not fit.exists()
    else:
        assert fitted.returncode == 0
    normalized = json.loads(fit.read_bytes()) if fit.exists() else None
    result = dict(status=decision['status'], candidate_dll_sha256=sha(dll), not_deployed=True,
                  no_more_same_source_groups=True, non_release_calibration=True, not_release_raw24=True,
                  single_run_all_samples_retained=True, background_load_range_pct=[min(loads), max(loads)],
                  on_ac_all=all(r['on_ac_before'] is True and r['on_ac_after'] is True for r in report['samples']),
                  fitted_fights_per_second_at20=normalized['fitted_fights_per_second_at_reference_load'] if normalized else None,
                  fit_validation=normalized['validation'] if normalized else None,
                  missing_reason=None if normalized else '20% outside observed range; extrapolation rejected',
                  raw_sha256=sha(raw), fit_exit_code=fitted.returncode)
    receipt.write_text(json.dumps(result, indent=2) + '\n', encoding='utf8')
    print(json.dumps(result, indent=2), flush=True)

if __name__ == '__main__':
    main()
