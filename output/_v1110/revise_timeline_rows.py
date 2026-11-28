"""Retain r2's passing semantics/failed coverage; accept inherited base methods."""
import json,shutil
from pathlib import Path
from prepare_timeline_round import WORK,STAGE,once,sha,inventory,save,verify_projection
def main():
    verify_projection(WORK/'bundle_src');assert not (WORK/'ab_fixed_1.json').exists()
    gate=json.loads((WORK/'bundle_full_gate.json').read_bytes());events=json.loads((WORK/'bundle_event_hashes.json').read_bytes());assert gate['complete'] and events['unchanged_cpp_event_streams']==2604
    counts={k:0 for k in ['motion_entries','typed_visual_steps','typed_charge_steps','delay_entries']};paths=[]
    for folder in STAGE.glob('native_timeline_typed_'+sha(WORK/'bundle.dll')[:8]+'_*'):
        for p in folder.rglob('timeline_coverage.json'):
            r=json.loads(p.read_bytes());assert r['verifier_exit_code']==0 and r['dll_sha256']==sha(WORK/'bundle.dll');paths.append(str(p))
            for k,v in r['counts'].items():counts[k]+=v
    assert counts['typed_charge_steps']==0 and len(paths)==10
    save('r2_semantic_coverage_gate.json',dict(semantic_passed=True,cases=2604,ordered_eventroot=events['ordered_case_and_cpp_event_hashes_sha256'],coverage_gate_passed=False,coverage=counts,coverage_receipts=paths,reason='Exact CoreItem metadata rejected real derived item receivers although their cached method slot has the identical CoreItem implementation',no_AB_samples=True))
    archive=WORK/'rejected_r2';assert not archive.exists();archive.mkdir()
    for n in ['native_typed_timeline.hpp','gen/shards/shard_07.cpp']:shutil.copyfile(WORK/'bundle_src'/n,archive/(Path(n).name+'.r2'))
    keep={'baseline.dll','fixed200_reference.json','formal_ab_protocol.json','aa_analysis.json','calibration_plan.json','architecture_selection.json','user_boundary_before.json'}
    for p in list(WORK.iterdir()):
        if p.name in keep or p.name in ['bundle_src','rejected_r1','rejected_r2'] or p.name.startswith('timeline_goal_driver'):continue
        shutil.move(p,archive/p.name)
    header=WORK/'bundle_src/native_typed_timeline.hpp';text=header.read_text('utf8')
    text=once(text,'namespace gd::typed_timeline {','namespace gd {template<class C,GdVal(C::*Method)(const GdVal*,int)> GdVal native_resolved_invoke(GdObj*,const GdVal*,int);}\nnamespace gd::typed_timeline {')
    text=once(text,'if(!row || row->metadata!=(data[0].i==0?&META_Gd__gd_core__CoreCharacter:&META_Gd__gd_core__CoreItem))return false;','if(!row || (data[0].i==0 ? row->metadata!=&META_Gd__gd_core__CoreCharacter : row->methods[native_resolved_slots[SYM_GEN__tickChargePath_506]]!=&native_resolved_invoke<Item,&Item::fn__tickChargePath>))return false;')
    header.write_text(text,encoding='utf8',newline='\n');shutil.copyfile(archive/'source_changes.json',WORK/'source_changes.json');save('source_before_build.json',inventory(WORK/'bundle_src'));save('source_projection.json',verify_projection(WORK/'bundle_src'))
    save('revision_r3.json',dict(reason='Accept real derived receivers only when cached charge method is the identical CoreItem implementation; overridden methods fall back',actual_CEA_row_probe_receipt_sha256=sha(WORK.parent/'row_guard_resume_probe_receipt.json'),normal_real200_coverage_required_before_PGO=True,FP_math_and_callback_tail_unchanged=True,no_AB_before_revision=True))
    print('Prepared r3 inherited-method identity guard; r2 full semantics and zero-coverage evidence retained',flush=True)
if __name__=='__main__':main()
