"""Retain the repaired original-game regression contracts unchanged."""
from prepare_frame_guard_retained import *
from prepare_quiet_round import WORK,ACCEPTED,EXPECTED,verify_projection
BASE=WORK/'retained_reference_src'

def rng_baseline_review(work):
    # nm absolute aliases at address0 are not function entry points.
    root=Path(tempfile.mkdtemp(prefix='quiet-rng-baseline-'));dll=root/'baseline.dll';shutil.copyfile(BASE/'libgdcore.dll',dll)
    names=subprocess.check_output(['D:/mingw64/bin/nm.exe','-g','--defined-only',str(dll)],text=True)
    demangled=subprocess.check_output(['D:/mingw64/bin/nm.exe','-g','-C','--defined-only',str(dll)],text=True)
    addresses={r.split()[0] for r in demangled.splitlines() if 'CoreRng::fn_randf' in r and len(r.split())>=3 and r.split()[1] in ('T','t') and int(r.split()[0],16)!=0}
    symbols=[r.split()[-1] for r in names.splitlines() if len(r.split())>=3 and r.split()[1] in ('T','t') and r.split()[0] in addresses];assert symbols
    text=''.join(subprocess.check_output(['D:/mingw64/bin/objdump.exe','-d','--no-show-raw-insn','--disassemble='+s,str(dll)],text=True) for s in symbols)
    path=work/'baseline_rng_preflight_machine.txt';path.write_text(text,encoding='utf8')
    calls=[line.strip() for line in text.splitlines() if 'call' in line and 'ldexp' in line];assert calls
    write(work/'baseline_rng_preflight.json',dict(passed=True,dll_sha256=sha(BASE/'libgdcore.dll'),actual_current_release_machine=True,symbols=symbols,remaining_ldexp_call_sites=calls,disassembly_sha256=sha(path),no_performance_claim=True))
