"""Check whether the current emitted cooldown function repeats row validation."""
import json,os,re,shutil,subprocess,tempfile
from pathlib import Path
from prepare_ordering_correctness import STAGE,BASE,sha
WORK=STAGE/'native_perf50/post_ordering_assessment'
def main():
    root=Path(tempfile.mkdtemp(prefix='frame-guard-review-',dir=Path(os.environ['LOCALAPPDATA'])/'CodexNativeBuilds'));binary=root/'current.dll';shutil.copyfile(BASE/'libgdcore.dll',binary)
    names=subprocess.check_output(['D:/mingw64/bin/nm.exe','-g','--defined-only',str(binary)],text=True)
    symbol=[line.split()[-1] for line in names.splitlines() if line.split()[-1].startswith('_ZN2gd25native_frame_segment_tickE')];assert len(symbol)==1,symbol
    text=subprocess.check_output(['D:/mingw64/bin/objdump.exe','-d','-C','--no-show-raw-insn','--disassemble='+symbol[0],str(binary)],text=True)
    if '<gd::native_frame_segment_tick' not in text:
        text=subprocess.check_output(['D:/mingw64/bin/objdump.exe','-d','--no-show-raw-insn','--disassemble='+symbol[0],str(binary)],text=True)
    (WORK/'frame_guard_current_disassembly.txt').write_text(text,encoding='utf8')
    calls=[line.strip() for line in text.splitlines() if '\tcall' in line];print('\n'.join(calls[:35]))
    (WORK/'frame_guard_review.json').write_text(json.dumps(dict(dll_sha256=sha(binary),symbol=symbol[0],disassembly_sha256=sha(WORK/'frame_guard_current_disassembly.txt'),calls=calls,temporary_directory=str(root)),indent=2)+'\n',encoding='utf8')
if __name__=='__main__':main()
