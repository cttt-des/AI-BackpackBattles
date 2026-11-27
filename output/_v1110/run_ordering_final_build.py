"""Check the completed semantic rebuild, then make the final full release."""
import json,psutil,subprocess,sys,time
from prepare_ordering_correctness import STAGE,WORK,verify_projection
def main():
    while not (WORK/'live_semantic_build.json').exists():time.sleep(1)
    row=json.loads((WORK/'live_semantic_build.json').read_bytes())
    try:p=psutil.Process(row['pid'])
    except psutil.NoSuchProcess:p=None
    if p and p.create_time()==row['created']:
        while p.is_running():
            try:p.wait(timeout=30)
            except psutil.TimeoutExpired:continue
            break
    verify_projection(WORK/'bundle_src')
    subprocess.run([sys.executable,'-u','-X','utf8',str(STAGE/'verify_ordering_contracts.py'),'--dll',str(WORK/'prototype.dll'),'--source',str(WORK/'bundle_src'),'--tag','prototype'],check=True)
    subprocess.run([sys.executable,'-u','-X','utf8',str(STAGE/'build_ordering_release.py')],check=True)
if __name__=='__main__':main()
