"""Keep all combined evidence; test the prioritized member component alone."""
import ast
import json
from pathlib import Path
STAGE=Path(__file__).resolve().parent
OLD=STAGE/'native_perf50/member_frame_bundle'
WORK=STAGE/'native_perf50/member_only_bundle'
def main():
    assert not WORK.exists();WORK.mkdir()
    for p in OLD.glob('*.py'):
        text=p.read_text('utf8').replace('member_frame_bundle','member_only_bundle').replace('native-member-frame-','native-member-only-')
        if p.name=='resume_build.py':text=text.replace("    exports.add('gd_diag_native_frame_segment_stat')\n",'')
        if p.name=='inspect_variant.py':text='\n'.join(line for line in text.splitlines() if not any(token in line for token in ('frame=sim.lib.gd_diag_native_frame_segment_stat','frame_before=','frame_segment_coverage')))+'\n'
        if p.name=='verify_components.py':
            text=text.replace("(('member','test_native_member_fields.cpp',['-DGD_MEMBER_PRODUCTION']),('frame','test_native_frame_segments.cpp',[]))","(('member','test_native_member_fields.cpp',['-DGD_MEMBER_PRODUCTION']),)")
            text=text.replace("    assert reports['frame']['cases']==6912\n",'')
        ast.parse(text,filename=p.name);(WORK/p.name).write_text(text,encoding='utf8',newline='\n')
    for name in ('member_probe_cases.hpp','native_property_test_cases.hpp'):(WORK/name).write_bytes((OLD/name).read_bytes())
    plan=json.loads((OLD/'evaluation_plan.json').read_bytes())
    plan['components']=['member pointers for43 pure property rows']
    plan['excluded'].append('frame segment reuse')
    plan['reason']='Combined24pairs had CPUmedian0.3656%reduction but wallmedian1.6654%increase and mixed groups. Preserve all data; ablate the frame component rather than repeating the same bundle until favorable.'
    (WORK/'evaluation_plan.json').write_text(json.dumps(plan,indent=2)+'\n',encoding='utf8')
    print('Prepared independent member-only ablation; baseline593a and original gates unchanged')
if __name__=='__main__':main()
