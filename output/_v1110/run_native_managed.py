"""Run one project phase, archive evidence, then always remove its workspace."""
import subprocess,sys
from pathlib import Path
from native_build_storage import workspace
def main():
    script=Path(sys.argv[1]).resolve();repo=Path(__file__).resolve().parents[2]
    assert script.is_file() and script.is_relative_to(repo)
    with workspace(script.stem+'-'+(sys.argv[2] if len(sys.argv)>2 else 'run')):
        result=subprocess.run([sys.executable,'-u','-X','utf8',str(script),*sys.argv[2:]])
    return result.returncode
if __name__=='__main__':sys.exit(main())
