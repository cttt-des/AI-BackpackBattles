"""Build the versioned wheel and the C++ desktop simulator sequentially."""
from pathlib import Path
import subprocess
import sys
import shutil
import argparse

ROOT = Path(__file__).resolve().parents[1]


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--exe-only', action='store_true')
    options = parser.parse_args()
    stage = ROOT / 'output/release_source_v061'
    stage.mkdir(parents=True, exist_ok=True)
    for name in ('simulator', 'gd_core_py', 'backpack_native', 'assets', 'lineups'):
        shutil.copytree(ROOT / name, stage / name, dirs_exist_ok=True,
                        ignore=shutil.ignore_patterns('__pycache__', '*.c'))
    for name in ('pyproject.toml', 'setup.py', 'README.md', 'native_simulator.py'):
        shutil.copyfile(ROOT / name, stage / name)
    destination = str(ROOT / 'dist')
    if not options.exe_only:
        subprocess.run([sys.executable, '-m', 'pip', 'wheel', '.', '--no-deps',
                        '--no-build-isolation', '-w', destination], cwd=stage, check=True)
    subprocess.run([sys.executable, '-m', 'PyInstaller', '--noconfirm', '--onefile', '--windowed',
                    '--name', 'BackpackSimulator', '--distpath', destination, '--workpath', 'build/native',
                    '--specpath', 'build', '--add-binary', str(stage / 'backpack_native/libgdcore.dll') + ';backpack_native',
                    '--add-data', str(stage / 'backpack_native/gd_core_runtime.json') + ';backpack_native',
                    '--add-data', str(stage / 'backpack_native/manifest.json') + ';backpack_native',
                    '--add-data', str(stage / 'backpack_native/sim.py') + ';backpack_native',
                    '--add-data', str(stage / 'backpack_native/selftest_case.json') + ';backpack_native',
                    'native_simulator.py'], cwd=stage, check=True)


if __name__ == '__main__':
    main()
