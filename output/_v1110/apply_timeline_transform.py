"""Reapply the frozen post-generation transform, or verify an existing copy."""
import argparse,json,shutil
from pathlib import Path
from prepare_timeline_round import STAGE,BASE,ACCEPTED,WORK,inventory,verify_projection
def apply(source):
    source=Path(source).resolve();assert source.drive.upper()=='D:'
    assert source==BASE.resolve() or source.is_relative_to(WORK.resolve()) or source.is_relative_to(Path('D:/CodexNativeBuilds/work').resolve())
    current=inventory(source);candidate=json.loads((WORK/'source_before_build.json').read_bytes())
    if current==candidate:return verify_projection(source)
    assert current==json.loads((ACCEPTED/'source_before_build.json').read_bytes()),'Apply after the existing CEA maintenance pipeline, not an unrelated generated tree'
    file=source/'gen/shards/shard_07.cpp';text=file.read_text('utf8')
    for old,new in json.loads((WORK/'source_changes.json').read_bytes()):assert text.count(old)==1;text=text.replace(old,new,1)
    file.write_text(text,encoding='utf8',newline='\n');shutil.copyfile(WORK/'bundle_src/native_typed_timeline.hpp',source/'native_typed_timeline.hpp');return verify_projection(source)
if __name__=='__main__':
    parser=argparse.ArgumentParser();parser.add_argument('source',type=Path);a=parser.parse_args();print(json.dumps(apply(a.source),indent=2))
