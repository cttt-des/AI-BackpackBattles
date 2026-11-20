"""Supplement a serial benchmark with bounded, low-priority background load."""
import argparse
import json
from pathlib import Path
import subprocess
import sys
import time


WORKER = '''
import os
import sys
import time
import psutil

parent = int(sys.argv[1])
start = float(sys.argv[2])
deadline = start + 120
psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
print("ready", flush=True)
while time.perf_counter() < deadline and psutil.pid_exists(parent):
    now = time.perf_counter()
    duty = 0.20 if int((now - start) / 10) % 2 == 0 else 0.85
    busy_until = now + 0.02 * duty
    while time.perf_counter() < busy_until:
        pass
    time.sleep(max(0, now + 0.02 - time.perf_counter()))
'''


def main():
    import os

    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--dll', type=Path, required=True)
    parser.add_argument('--out', type=Path, required=True)
    parser.add_argument('--warmup-seconds', type=float, default=30)
    args = parser.parse_args()
    if not 0 <= args.warmup_seconds <= 60:
        parser.error('--warmup-seconds must be between zero and sixty')
    children = []
    start = time.perf_counter()
    try:
        for _ in range(2):
            process = subprocess.Popen(
                [sys.executable, '-u', '-c', WORKER, str(os.getpid()), str(start)],
                stdout=subprocess.PIPE, text=True, creationflags=subprocess.CREATE_NO_WINDOW)
            children.append(process)
            if process.stdout.readline().strip() != 'ready':
                raise RuntimeError('A background calibration worker failed to start')
        print(f'Warming controlled load for {args.warmup_seconds:g} seconds', flush=True)
        time.sleep(args.warmup_seconds)
        subprocess.run([sys.executable, '-u', str(Path(__file__).with_name('bench_native_corpus.py')),
                        '--dll', str(args.dll), '--workers', '1', '--repeat', '24', '--out', str(args.out)],
                       check=True)
        report = json.loads(args.out.read_bytes())
        report['background_calibration'] = {
            'workers': 2, 'priority': 'below_normal', 'period_seconds': 0.02,
            'busy_fractions': [0.20, 0.85], 'phase_seconds': 10, 'maximum_duration_seconds': 120,
            'elapsed_seconds': time.perf_counter() - start,
            'warmup_seconds': args.warmup_seconds,
        }
        args.out.write_text(json.dumps(report, indent=2)+'\n', encoding='utf8')
    finally:
        for process in children:
            if process.poll() is None:
                process.terminate()
            process.wait(timeout=10)


if __name__ == '__main__':
    main()
