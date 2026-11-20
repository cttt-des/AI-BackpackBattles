"""Compose both code-generation layers without installing the pending entry point."""
from pathlib import Path
import sys
import tempfile
import importlib.util
import json

WORK=Path(__file__).resolve().parent
STAGE=WORK.parents[1]
sys.path.insert(0,str(STAGE))
import optimize_native_shared_speed as speed

spec=importlib.util.spec_from_file_location('pending_inline_speed',WORK/'optimize_native_inline_timers_pending.py')
module=importlib.util.module_from_spec(spec)
spec.loader.exec_module(module)
root=Path(tempfile.mkdtemp(prefix='native-speed-compose-'))
native=STAGE/'sim_native/native_sim_cpp/native_sim'
for name in set(module.HASHES)|set(speed.INPUTS):
    path=root/name;path.parent.mkdir(parents=True,exist_ok=True);path.write_bytes((native/name).read_bytes())
module.optimize(root)
for name,sha in speed.OUTPUTS.items():assert speed.digest((root/name).read_text('utf8'))==sha
before={p:(p.read_bytes(),p.stat().st_mtime_ns) for p in root.rglob('*') if p.is_file()}
module.optimize(root)
assert before=={p:(p.read_bytes(),p.stat().st_mtime_ns) for p in before}
base=speed.remove_layer({name:(root/name).read_text('utf8') for name in set(module.HASHES)|set(speed.INPUTS)})
base['gd_rt.hpp']=base['gd_rt.hpp'].removeprefix('#include <cstddef>\n').replace(module.NEW_ARENA,module.OLD_ARENA,1).replace(module.FLAG,'',1).replace(module.RESET_FLAG,'',1)
base['gen/hdrs/Gd__gd_core__CoreItem.hpp']=base['gen/hdrs/Gd__gd_core__CoreItem.hpp'].replace(module.NEW_DECL,module.OLD_DECL,1)
base['gen/shards/shard_00.cpp']=base['gen/shards/shard_00.cpp'].replace(module.NEW_ASSIGN,module.OLD_ASSIGN,1)
base['engine_wrapper.cpp']=base['engine_wrapper.cpp'].replace(module.WRAPPER_FLAG,'',1)
for name,body in base.items():(root/name).write_text(body,encoding='utf8',newline='\n')
module.optimize(root)
assert all(p.read_bytes()==value[0] for p,value in before.items())
(WORK/'shared_speed_pipeline_test.json').write_text(json.dumps({
    'idempotent_bytes_and_mtime':True,'from_pre_inline_timer_input':True,
    'output_matches_candidate_guards':True,'pending_not_installed':True,
},indent=2)+'\n',encoding='utf8',newline='\n')
print('Both layers compose from old/current inputs; repeated bytes and mtimes unchanged')
