"""Compare actual baseline/candidate arithmetic results, argument order and RNG."""
import hashlib
import json
from pathlib import Path
import shutil
import subprocess
import tempfile

WORK=Path(__file__).resolve().parent
STAGE=WORK.parents[1]


def main():
    baseline=STAGE/'sim_native/native_sim_cpp/native_sim/libgdcore.dll'
    candidate=WORK/'bundle.dll';reports={}
    with tempfile.TemporaryDirectory(prefix='native-numeric-math-') as directory:
        root=Path(directory).resolve();assert root.is_relative_to(Path(tempfile.gettempdir()).resolve())
        for label,header,dll in (('baseline',baseline.parent,baseline),('candidate',WORK/'bundle_src',candidate)):
            folder=root/label;folder.mkdir();shutil.copyfile(dll,folder/'libgdcore.dll')
            executable=folder/'numeric.exe'
            extra=['-DGD_NUMERIC_CANDIDATE'] if label=='candidate' else []
            subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-march=native','-std=c++20','-ffp-contract=off',
                *extra,'-I',str(header),str(STAGE/'test_native_numeric_math_ordered.cpp'),str(folder/'libgdcore.dll'),'-o',str(executable)],check=True)
            reports[label]=json.loads(subprocess.check_output([str(executable)],text=True))
            (WORK/f'numeric_{label}_cases.json').write_text(json.dumps(reports[label],indent=2)+'\n',encoding='utf8')
    assert reports['baseline']['case_hashes']==reports['candidate']['case_hashes'],'Inspect saved per-case hashes; do not discard differences'
    assert reports['baseline']['cases']==reports['candidate']['cases']>4000
    assert reports['baseline']['directed_cases']==reports['candidate']['directed_cases']>=64
    assert reports['baseline']['skipped_undefined_divisions']==reports['candidate']['skipped_undefined_divisions']==1
    assert all(count>0 for count in reports['candidate']['numeric_counts'])
    report={'passed':True,'dll_sha256':hashlib.sha256(candidate.read_bytes()).hexdigest(),
        'baseline_dll_sha256':hashlib.sha256(baseline.read_bytes()).hexdigest(),
        'cases':reports['candidate']['cases'],'directed_cases':reports['candidate']['directed_cases'],
        'skipped_undefined_divisions':1,'original_reference_and_candidate_bits_kinds_containers_unchanged':True,
        'argument_order_alias_mutation_and_rng_unchanged':True,'floating_exception_flags_equal_to_actual_baseline':True,
        'numeric_counts':reports['candidate']['numeric_counts']}
    (WORK/'numeric_math_differential.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps(report,indent=2))


if __name__=='__main__':main()
