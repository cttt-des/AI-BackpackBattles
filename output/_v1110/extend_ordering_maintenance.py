"""Keep the older maintained generated EventBus source consistent too."""
import json,re,subprocess
from prepare_ordering_correctness import REPO,WORK,sha,save
def main():
    relative='native_sim_cpp/native_sim/gen/shards/shard_11.cpp';target=REPO/relative
    canonical=lambda value:value.replace(b'\r\n',b'\n')
    assert canonical(subprocess.check_output(['git','show','HEAD:'+relative],cwd=REPO))==canonical(target.read_bytes()),'Preserve any user edit'
    text=target.read_text('utf8');start=text.index('gd::GdVal Gd__gd_core__CoreEventBus::fn_emitAndLog(');end=text.index('\n}\n',start)+2;body=text[start:end]
    pattern=r'for \(uint32_t (_t\d+) = 0; \1 < _len_\1; \+\+\1\) \{'
    matches=list(re.finditer(pattern,body));assert len(matches)==1
    m=matches[0];prefix=body[:m.start()];array=re.search(r'gd::GdArr\* (_t\d+) = .*?;\n\s*uint32_t _len_'+m[1]+r' =',prefix).group(1)
    fixed=f'for (uint32_t {m[1]} = 0; {array} && {m[1]} < {array}->len; ++{m[1]}) {{';body=body[:m.start()]+fixed+body[m.end():]
    old=WORK/'maintenance_before'/relative;old.parent.mkdir(parents=True,exist_ok=True);old.write_bytes(target.read_bytes())
    pending=WORK/'maintenance_pending'/relative;pending.parent.mkdir(parents=True,exist_ok=True);pending.write_text(text[:start]+body+text[end:],encoding='utf8',newline='\n')
    rows=json.loads((WORK/'maintenance_changes.json').read_bytes());assert relative not in rows;rows[relative]=dict(before_sha256=sha(target),after_sha256=sha(pending));save('maintenance_changes.json',rows)
    save('maintained_event_bus_source_correction.json',dict(passed=True,path=relative,only_declared_loop_changed=True,old_loop=m[0],new_loop=fixed,user_file_original_matches_HEAD=True))
    print('Staged the older generated EventBus source repair; live files unchanged')
if __name__=='__main__':main()
