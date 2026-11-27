"""Syntax check the maintained EventBus with its own older generated headers."""
import subprocess
from prepare_ordering_correctness import REPO,WORK,sha,save
def main():
    import psutil
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    relative='native_sim_cpp/native_sim/gen/shards/shard_11.cpp';pending=WORK/'maintenance_pending'/relative
    # Include paths in a generated shard are relative to the original shard dir.
    with (WORK/'maintained_event_bus_syntax.log').open('wb') as log:
        subprocess.run(['D:/mingw64/bin/g++.exe','-fsyntax-only','-std=c++20','-ffp-contract=off','-I',str(REPO/'native_sim_cpp/native_sim/gen/shards'),str(pending)],stdout=log,stderr=subprocess.STDOUT,check=True)
    save('maintained_event_bus_syntax.json',dict(passed=True,source_sha256=sha(pending),log_sha256=sha(WORK/'maintained_event_bus_syntax.log')));print('Maintained EventBus syntax passed')
if __name__=='__main__':main()
