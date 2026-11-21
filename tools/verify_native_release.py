"""Check the installed wheel and frozen EXE, including their runtime manifests."""
import hashlib
import json
from pathlib import Path
import subprocess
import shutil
import sys
import tempfile
import zipfile

from PyInstaller.archive.readers import CArchiveReader

ROOT = Path(__file__).resolve().parents[1]


def digest(data):
    return hashlib.sha256(data).hexdigest()


def main():
    exe = ROOT / 'dist/BackpackSimulator.exe'
    wheel = ROOT / 'dist/backpack_battles_sim-0.6.1-cp314-cp314-win_amd64.whl'
    manifest = json.loads((ROOT / 'backpack_native/manifest.json').read_bytes())
    expected = json.loads((ROOT / 'backpack_native/selftest_case.json').read_bytes())['expected']
    gate_bytes = (ROOT / 'output/_v1110/native_perf50/lazy_diagnostics_bundle/bundle_full_gate.json').read_bytes()
    gate = json.loads(gate_bytes)
    assert manifest['gate_sha256'] == digest(gate_bytes)
    runtime = json.loads((ROOT / 'backpack_native/gd_core_runtime.json').read_bytes())
    canonical = json.dumps(runtime, ensure_ascii=False, sort_keys=True, separators=(',', ':'))
    assert digest(canonical.encode('utf8')) == gate['runtime_data_sha256']
    assert manifest['sha256']['libgdcore.dll'] == gate['dll_sha256']
    assert gate['complete']
    archive = CArchiveReader(str(exe))
    with zipfile.ZipFile(wheel) as package:
        for name, sha in manifest['sha256'].items():
            matches = [p for p in package.namelist()
                       if p == 'backpack_native/' + name or p.endswith('/backpack_native/' + name)]
            assert len(matches) == 1, (name, matches)
            assert digest(package.read(matches[0])) == sha, ('wheel', name)
            frozen = [p for p in archive.toc if p.replace('\\', '/') == 'backpack_native/' + name]
            assert len(frozen) == 1, (name, frozen)
            assert digest(archive.extract(frozen[0])) == sha, ('exe', name)
    with tempfile.TemporaryDirectory(prefix='backpack_release_') as directory:
        target = Path(directory)
        installed = target / 'installed'
        subprocess.run([sys.executable, '-m', 'pip', 'install', '--no-deps', '--no-compile',
                        '--target', str(installed), str(wheel)], check=True)
        wheel_report, exe_report = target / 'wheel.json', target / 'exe.json'
        code = (
            'import sys, pathlib, runpy; '
            f'sys.path.insert(0, {str(installed)!r}); '
            'import backpack_native; '
            f'assert pathlib.Path(backpack_native.__file__).is_relative_to({str(installed)!r}); '
            f'sys.argv=["backpack_native.gui", "--selftest", {str(wheel_report)!r}]; '
            'runpy.run_module("backpack_native.gui", run_name="__main__")'
        )
        subprocess.run([sys.executable, '-I', '-c', code], cwd=directory, check=True, timeout=60)
        # Test a fresh deployment, separate from local path-specific compatibility settings.
        deployed_exe = target / exe.name
        shutil.copyfile(exe, deployed_exe)
        subprocess.run([str(deployed_exe), '--selftest', str(exe_report)], cwd=directory,
                       check=True, timeout=60)
        for report in (wheel_report, exe_report):
            assert json.loads(report.read_bytes()) == expected, report
    report = {
        'version': '0.6.1',
        'isolated_wheel_selftest': 'passed',
        'frozen_exe_selftest': 'passed',
        'selftest': 'complex lineup, seeds 42/43, repeated for determinism',
        'runtime_manifest_checks': 'wheel and EXE match all SHA-256 entries',
        'native_dll_sha256': gate['dll_sha256'],
        'existing_event_gate': gate['cohorts'],
        'assets': {p.name: {'bytes': p.stat().st_size, 'sha256': digest(p.read_bytes())}
                   for p in (exe, wheel)},
    }
    destination = ROOT / 'docs/release_v0.6.1_verification.json'
    destination.write_text(json.dumps(report, indent=2) + '\n', encoding='utf8')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
