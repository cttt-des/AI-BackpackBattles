"""Only enabled by the project managed-build launcher's PYTHONPATH."""
import os,sys
from pathlib import Path
if os.environ.get('NATIVE_BUILD_SESSION'):
    sys.path.insert(0,str(Path(__file__).resolve().parents[1]))
    from native_build_storage import activate
    activate()
