"""Create an isolated comparator variant; preserve the existing benchmark tool."""
import ast
import hashlib
from pathlib import Path

STAGE=Path(__file__).resolve().parent


def main():
    original=STAGE/'compare_native_isolated.py';target=STAGE/'compare_native_isolated_blocks.py'
    assert not target.exists()
    text=original.read_text('utf8')
    text=text.replace('from compare_native_serial import summarize','from compare_native_serial import summarize\nfrom measure_native_corpus_blocks import measure_blocks')
    text=text.replace('        if command.strip() != "run":\n            raise ValueError("Unknown benchmark worker command")\n        result = measure(sim, jobs, 1, load, continuous=True)',
        '        request=command.strip()\n        if request=="run":\n            result=measure(sim,jobs,1,load,continuous=True)\n        elif request.startswith("run:"):\n            count=int(request.split(":",1)[1]);assert 1<=count<=8\n            result=measure_blocks(sim,jobs,count,load)\n        else:raise ValueError("Unknown benchmark worker command")')
    text=text.replace('    def run(self):\n        self.process.stdin.write("run\\n")', '    def run(self,repetitions=1):\n        self.process.stdin.write("run\\n" if repetitions==1 else f"run:{repetitions}\\n")')
    text=text.replace('    args = parser.parse_args()', '    parser.add_argument("--batch-repetitions",type=int,default=4)\n    args = parser.parse_args()\n    if not 1<=args.batch_repetitions<=8:parser.error("batch repetitions must be1..8")',1)
    text=text.replace('              "fights": 200, "workers": 1, "pairs": [],', '              "fights": 200, "workers": 1, "pairs": [],\n              "trial_batch_repetitions":args.batch_repetitions,"observed_fights_per_arm":200*args.batch_repetitions,')
    text=text.replace('        def run(label):\n            result = arms[label].run()', '        def run(label,repetitions=1):\n            result = arms[label].run(repetitions)')
    text=text.replace('                    pair[label] = run(label)', '                    pair[label] = run(label,args.batch_repetitions)')
    assert 'result=measure_blocks(sim,jobs,count,load)' in text and 'run(label,args.batch_repetitions)' in text
    ast.parse(text)
    target.write_text(text,encoding='utf8',newline='\n')
    print('Prepared fixed200x4 comparison; old comparator SHA256 '+hashlib.sha256(original.read_bytes()).hexdigest())


if __name__=='__main__':main()
