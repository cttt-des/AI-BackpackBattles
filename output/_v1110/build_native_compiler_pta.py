"""Apply PTA to both profile phases, with a scoped compiler memory guard."""
import json
from pathlib import Path
import threading
import psutil
from build_native_hot_lto import HOT_UNITS,collect_profiles,build_dll as original_build
from prepare_native_compiler_pta import FLAGS

def build_dll(native,out,jobs,profile_flags=(),*,hot_units=HOT_UNITS,link_flags=()):
    root=Path(native).parent
    stage='instrumented' if any(x.startswith('-fprofile-generate=') for x in profile_flags) else 'release'
    receipt=root/('compiler_'+stage+'_resource.json');assert not receipt.exists()
    memory=psutil.virtual_memory();budget=int(min(memory.total*0.45,memory.available*0.65))
    if memory.available<1.5*2**30:raise RuntimeError('Insufficient free memory to begin PTA build; no formal timing has started')
    owner=psutil.Process();stop=threading.Event()
    state=dict(peak_compiler_rss_bytes=0,memory_limit_bytes=budget,available_before_bytes=memory.available,
        compiler_flags=list(FLAGS),scope='18 hot compilation units and both links; other2 units unchanged',
        resource_guard_triggered=False,owner_pid=owner.pid,owner_created=owner.create_time())
    names={'g++.exe','cc1plus.exe','lto1.exe','ld.exe','collect2.exe','lto-wrapper.exe','mingw32-make.exe'}
    def monitor():
        while not stop.wait(1):
            children=owner.children(recursive=True);rss=0
            for child in children:
                try:
                    if child.name() in names:rss+=child.memory_info().rss
                except psutil.Error:pass
            state['peak_compiler_rss_bytes']=max(state['peak_compiler_rss_bytes'],rss)
            if state['resource_guard_triggered'] or rss>budget or (psutil.virtual_memory().available<1024**3 and rss>1024**3):
                state['resource_guard_triggered']=True
                state['reason']='Owned compiler memory exceeded the predeclared resource budget'
                # Only descendants of this build controller are in scope.
                for child in reversed(children):
                    try:
                        if child.name() in names:child.kill()
                    except psutil.Error:pass
    thread=threading.Thread(target=monitor,daemon=True);thread.start()
    try:
        result=original_build(native,out,min(jobs,2),(*FLAGS,*profile_flags),hot_units=hot_units,link_flags=link_flags)
        if state['resource_guard_triggered']:raise RuntimeError(state['reason'])
        state['passed']=True;return result
    finally:
        stop.set();thread.join()
        receipt.write_text(json.dumps(state,indent=2)+'\n',encoding='utf8')
