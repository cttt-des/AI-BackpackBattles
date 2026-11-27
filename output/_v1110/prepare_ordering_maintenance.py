"""Stage matching repairs to maintained source entrypoints, without installing."""
import ast,json,shutil
from pathlib import Path
from prepare_ordering_correctness import REPO,STAGE,WORK,BASE,sha,save,once

def main():
    pending=WORK/'maintenance_pending';before=WORK/'maintenance_before';assert not pending.exists();pending.mkdir();before.mkdir()
    edits={}
    def stage(relative,data):
        target=REPO/relative;original=target.read_bytes() if target.exists() else None
        if original is not None:
            snapshot=before/relative;snapshot.parent.mkdir(parents=True,exist_ok=True);snapshot.write_bytes(original)
        new=pending/relative;new.parent.mkdir(parents=True,exist_ok=True);new.write_bytes(data)
        edits[relative]=dict(before_sha256=sha(target) if original is not None else None,after_sha256=sha(new))
    root_rt=REPO/'native_sim_cpp/native_sim/gd_rt.cpp';text=root_rt.read_text('utf8')
    start=text.index('void sort_custom_stable(');end=text.index('\n}\n',start)+2;original=text[start:end]
    new=(WORK/'bundle_src/gd_rt.cpp').read_text('utf8');a=new.index('// Preserve this exported symbol');b=new.index('\n}\n',a)+2;replacement=new[a:b]
    if 'NativeTimerMutation' not in original:replacement=replacement.replace('    NativeTimerMutation native_mutation(arr?arr->timer_watch:nullptr);\n','')
    if 'native_timer_observe_object' not in original:replacement=replacement.replace('            native_timer_observe_object(*ctx,obj);\n','')
    text=text[:start]+replacement+text[end:];text=once(text,'#include "gd_rt.hpp"','#include "gd_rt.hpp"\n#include "native_godot_sort.hpp"')
    stage('native_sim_cpp/native_sim/gd_rt.cpp',text.encode('utf8'))
    stage('native_sim_cpp/native_sim/native_godot_sort.hpp',(WORK/'bundle_src/native_godot_sort.hpp').read_bytes())
    old=(WORK/'gd_to_cpp_before.py').read_text('utf8');new=(WORK/'gd_to_cpp_pending.py').read_text('utf8')
    anchor='                lines.append(f"{ind}    for (uint32_t {idx_t} = 0; {idx_t} < _len_{idx_t}; ++{idx_t}) {{")'
    a=new.index('                # EventBus callbacks may grow');b=new.index('                sub_loc = dict(locals_)',a);replacement=new[a:b].rstrip('\n')
    root_gen=(REPO/'native_sim_cpp/tools/gd_to_cpp.py').read_text('utf8');root_gen=once(root_gen,anchor,replacement);ast.parse(root_gen)
    stage('native_sim_cpp/tools/gd_to_cpp.py',root_gen.encode('utf8'))
    stage('output/_v1110/sim_native/native_sim_cpp/tools/gd_to_cpp.py',(WORK/'gd_to_cpp_pending.py').read_bytes())
    stage('output/_v1110/optimize_native_event_bus.py',(WORK/'optimize_native_event_bus_pending.py').read_bytes())
    stage('output/_v1110/optimize_native_verified_bundle.py',(WORK/'verified_bundle_pending.py').read_bytes())
    stage('gd_core_py/_rt.py',(WORK/'python_pending/gd_core_py/_rt.py').read_bytes())
    stage('gd_core_py/_rt.pyd',(WORK/'python_pending/gd_core_py/_rt.pyd').read_bytes())
    stage('gd_core_py/_godot_sort.py',(WORK/'python_pending/gd_core_py/_godot_sort.py').read_bytes())
    # The original tests stay frozen; this is the maintained replacement used by
    # the new release's verifier and backed by the original Godot oracle.
    stage('output/_v1110/test_native_event_kernel_godot.cpp',(WORK/'test_native_event_kernel_godot.cpp').read_bytes())
    save('maintenance_changes.json',edits)
    print('Prepared'+str(len(edits))+' scoped source/runtime maintenance files; live runtime unchanged')
if __name__=='__main__':main()
