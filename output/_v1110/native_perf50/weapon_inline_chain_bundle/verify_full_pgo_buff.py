import runpy
from pathlib import Path
import sys
s=Path(__file__).resolve().parents[2];sys.path.insert(0,str(s))
runpy.run_path(str(s/"verify_native_weapon_inline_chain_full_pgo.py"),run_name="__main__")
