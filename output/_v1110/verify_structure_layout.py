"""Compile both schemas: all674 sizes/alignments, named fields, fixed storage."""
import json,os,re,shutil,subprocess,tempfile
from pathlib import Path
import psutil
from native_build_storage import isolated_build
from prepare_structure_round import WORK,ACCEPTED,sha,save,verify_projection
@isolated_build
def main():
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS);verify_projection(WORK/'bundle_src')
    root=Path(tempfile.mkdtemp(prefix='structure-layout-',dir=Path(os.environ['LOCALAPPDATA'])/'CodexNativeBuilds'));report={}
    plan=json.loads((WORK/'layout_field_plan.json').read_bytes())
    for label,source in [('baseline',ACCEPTED/'bundle_src'),('candidate',WORK/'bundle_src')]:
        headers=sorted((source/'gen/hdrs').glob('*.hpp'));assert len(headers)==674
        text='#include <cstdio>\n#include <cstddef>\n'+''.join('#include "gen/hdrs/'+p.name+'"\n' for p in headers)+'int main(){\n'
        text+='std::printf("{\\\"classes\\\":{");\n'
        for j,p in enumerate(headers):
            text+='std::printf("'+(',' if j else '')+'\\\"'+p.stem+'\\\":[%zu,%zu]",sizeof('+p.stem+'),alignof('+p.stem+'));\n'
        text+='std::printf("},\\\"offsets\\\":{");\n'
        for j,(cls,row) in enumerate(plan.items()):
            name='Gd__gd_core__'+cls;fields=row['original_order']
            if cls=='CoreItem':fields += ['f_timers','native_display_header_','native_display_values_','native_timer_header_','native_bridge_gems_header_']
            text+='std::printf("'+(',' if j else '')+'\\\"'+cls+'\\\":{");\n'
            for i,f in enumerate(fields):text+='std::printf("'+(',' if i else '')+'\\\"'+f+'\\\":%zu",offsetof('+name+','+f+'));\n'
            text+='std::printf("}");\n'
        text+='std::printf("}}\\n");}\n'
        fixture=root/(label+'.cpp');fixture.write_text(text,encoding='utf8');exe=root/(label+'.exe')
        with (WORK/('layout_'+label+'_compile.log')).open('wb') as log:subprocess.run(['D:/mingw64/bin/g++.exe','-O1','-static','-std=c++20','-Wno-invalid-offsetof','-I',str(source),str(fixture),'-o',str(exe)],stdout=log,stderr=subprocess.STDOUT,check=True)
        result=subprocess.check_output([str(exe)]);(WORK/('layout_'+label+'.json')).write_bytes(result);shutil.copyfile(fixture,WORK/('layout_'+label+'.cpp'));report[label]=json.loads(result)
    a,b=report['baseline'],report['candidate'];assert a['classes']==b['classes']
    fixed=['f_timers','native_display_header_','native_display_values_','native_timer_header_','native_bridge_gems_header_']
    assert all(a['offsets']['CoreItem'][f]==b['offsets']['CoreItem'][f] for f in fixed)
    groups={'cooldown':['f__cooldown_active','f__cooldown_blocked_epoch','f_ctx','f_character_','f_statDisplayOverrides','f_speedScale','f_placed','f_triggerTime','f_iterationCooldown'],
      'character_frame':['f_stunnedDuration','f_staminaRegen','f_curStamina','f_maxStamina','f_temporaryMaxStamina','f_buffs','f_inventory','f_playerId','f_ctx'],
      'buff_tick':['f__timer_active','f__timer_left','f_current','f_character','f_type','f_ctx']}
    footprints={}
    for group,fields in groups.items():
        cls='CoreItem' if group=='cooldown' else 'CoreCharacter' if group=='character_frame' else 'CoreBuff'
        align=a['classes']['Gd__gd_core__'+cls][1];shifts=range(0,64,min(64,align))
        footprints[group]={label:[len({(shift+r['offsets'][cls][f]+p)//64 for f in fields for p in (0,8)}) for shift in shifts] for label,r in report.items()}
    save('layout_projection.json',dict(passed=True,all674_object_sizes_and_alignments_identical=True,all_GdVal_fields_same_size_and_slot_offsets=True,five_original_inline_storage_and_timer_alignment_offsets_identical=True,computed_hot_field_cache_line_footprints=footprints,footprint_is_static_not_a_cache_miss_measurement_or_speed_claim=True,raw_sha256={label:sha(WORK/('layout_'+label+'.json')) for label in report}))
    print(json.dumps(footprints,indent=2),flush=True)
if __name__=='__main__':main()
