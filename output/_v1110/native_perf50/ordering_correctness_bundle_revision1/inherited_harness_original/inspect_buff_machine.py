import runpy
from pathlib import Path
import sys
s=Path(__file__).resolve().parents[2];sys.path.insert(0,str(s))
runpy.run_path(str(s/"inspect_retained_buff_assembly_membership_machine.py"),run_name="__main__")
