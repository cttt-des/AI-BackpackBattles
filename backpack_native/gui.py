"""Native simulator desktop entry and packaged-runtime self-test."""
import argparse
import json
from pathlib import Path
import queue
import threading
import tkinter as tk
from tkinter import ttk, filedialog
from . import run_mc


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--selftest', type=Path, metavar='REPORT_JSON')
    args = parser.parse_args()
    if args.selftest:
        case = json.loads((Path(__file__).parent / 'selftest_case.json').read_bytes())
        result = run_mc(case['player'], case['opponent'], runs=2)
        assert result == case['expected']
        assert result == run_mc(case['player'], case['opponent'], runs=2)
        args.selftest.write_text(json.dumps(result, indent=2), encoding='utf8')
        return
    app = tk.Tk()
    app.title('BackpackSimulator v0.6.1 · C++ · 游戏 1.1.10')
    app.geometry('840x610')
    form = ttk.Frame(app, padding=16)
    form.pack(fill='both', expand=True)
    files = [tk.StringVar(), tk.StringVar()]
    for row, label in enumerate(('玩家阵容 JSON', '对手阵容 JSON')):
        ttk.Label(form, text=label).grid(row=row, column=0, sticky='w', pady=5)
        ttk.Entry(form, textvariable=files[row], width=65).grid(row=row, column=1, sticky='ew')
        def choose(index=row):
            selected = filedialog.askopenfilename(filetypes=[('JSON', '*.json')])
            if selected:
                files[index].set(selected)
        ttk.Button(form, text='选择', command=choose).grid(row=row, column=2)
    seed, runs = tk.StringVar(value='42'), tk.StringVar(value='200')
    ttk.Label(form, text='起始种子').grid(row=2, column=0, sticky='w')
    ttk.Entry(form, textvariable=seed).grid(row=2, column=1, sticky='w')
    ttk.Label(form, text='模拟场数').grid(row=3, column=0, sticky='w')
    ttk.Entry(form, textvariable=runs).grid(row=3, column=1, sticky='w')
    output = tk.Text(form, wrap='word')
    output.grid(row=5, column=0, columnspan=3, sticky='nsew', pady=12)
    messages = queue.Queue()
    latest = None

    def start():
        try:
            sides = [json.loads(Path(v.get()).read_text('utf8-sig')) for v in files]
            options = dict(seed=int(seed.get()), runs=int(runs.get()), workers=1)
        except Exception as error:
            output.insert('end', str(error) + '\n')
            return
        button.config(state='disabled')
        output.delete('1.0', 'end')
        output.insert('end', '模拟中…\n')
        def compute():
            try:
                messages.put(run_mc(*sides, **options))
            except Exception as error:
                messages.put(str(error))
        threading.Thread(target=compute, daemon=True).start()

    def poll():
        nonlocal latest
        try:
            result = messages.get_nowait()
            output.delete('1.0', 'end')
            if isinstance(result, dict):
                latest = result
                output.insert('end', f"胜率 {result['win_rate']:.2%}，{result['wins']}/{result['runs']} 场获胜\n\n")
                output.insert('end', json.dumps(result, ensure_ascii=False, indent=2))
            else:
                output.insert('end', result)
            button.config(state='normal')
        except queue.Empty:
            pass
        app.after(100, poll)

    def save():
        if latest is not None:
            name = filedialog.asksaveasfilename(defaultextension='.json')
            if name:
                Path(name).write_text(json.dumps(latest, ensure_ascii=False, indent=2), encoding='utf8')
    button = ttk.Button(form, text='开始模拟', command=start)
    button.grid(row=4, column=1, sticky='w', pady=8)
    ttk.Button(form, text='保存结果 JSON', command=save).grid(row=4, column=2)
    form.columnconfigure(1, weight=1)
    form.rowconfigure(5, weight=1)
    poll()
    app.mainloop()


if __name__ == '__main__':
    main()
