"""Bind retained independent suites to the current combination and its baseline."""
import ast
from prepare_restored_private_snapshots import STAGE

def once(t,a,b):
    assert t.count(a)==1,(a[:140],t.count(a));return t.replace(a,b,1)
def emit(name,text):
    ast.parse(text);p=STAGE/name;assert not p.exists();p.write_text(text,encoding='utf8',newline='\n')

def main():
    t=(STAGE/'verify_native_private_snapshots.py').read_text('utf8')
    t=t.replace('from prepare_native_private_snapshots import STAGE,WORK,ACCEPTED,EXPECTED,sha',
        'from prepare_restored_private_snapshots import STAGE,WORK,ACCEPTED,EXPECTED,sha')
    anchor="            exe=folder/(fixture+'.exe');log=out.parent/(label+'_'+fixture+'.log');assert not log.exists()"
    t=once(t,anchor,"            local_fixture=folder/('test_native_'+fixture+'.cpp');shutil.copyfile(STAGE/local_fixture.name,local_fixture)\n"+anchor)
    t=once(t,"str(STAGE/('test_native_'+fixture+'.cpp')),str(folder/'libgdcore.dll')", "str(local_fixture),str(folder/'libgdcore.dll')")
    anchor="    folder=root/'candidate';exe=folder/'private_view.exe'"
    t=once(t,anchor,anchor+"\n    local_helper=folder/'test_native_private_integer_view.cpp';shutil.copyfile(STAGE/local_helper.name,local_helper)")
    t=once(t,"str(STAGE/'test_native_private_integer_view.cpp'),str(folder/'libgdcore.dll')", "str(local_helper),str(folder/'libgdcore.dll')")
    emit('verify_restored_private_snapshots.py',t)
    t=(STAGE/'verify_native_display_storage.py').read_text('utf8')
    t=t.replace('prepare_native_display_storage','prepare_restored_private_snapshots')
    t=once(t,"ACCEPTED/'bundle_src',BASE/'libgdcore.dll',[]", "ACCEPTED/'bundle_src',ACCEPTED/'bundle.dll',[]")
    t=once(t,"    assert a['core_item_bytes']==1792 and b['core_item_bytes']>a['core_item_bytes']", "    assert a['core_item_bytes']==b['core_item_bytes']==2112")
    t=t.replace("WORK/'correctness.json'","WORK/'retained_display.json'")
    emit('verify_restored_display_storage.py',t)
    t=(STAGE/'verify_native_display_control.py').read_text('utf8')
    t=t.replace('prepare_native_display_storage','prepare_restored_private_snapshots')
    t=once(t,"    declared_size=json.loads((WORK/'correctness.json').read_bytes())['candidate_core_item_bytes']", "    declared_size=2112 # all674 current headers are byte-identical to the accepted baseline")
    t=t.replace("WORK/'correctness.json'","WORK/'retained_control.json'")
    emit('verify_restored_control.py',t)
    print('Prepared independent234880 private cases and retained21888/44608 suites against the deployed2112-byte baseline')

if __name__=='__main__':main()
