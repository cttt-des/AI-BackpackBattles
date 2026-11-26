import runpy
from pathlib import Path
import sys
s=Path(__file__).resolve().parents[2];sys.path.insert(0,str(s))
runpy.run_path(str(s/"inspect_native_weapon_chain_machine.py"),run_name="__main__")
