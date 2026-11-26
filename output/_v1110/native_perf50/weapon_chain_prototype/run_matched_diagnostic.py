from pathlib import Path
import sys
sys.path.insert(0,str(Path('output/_v1110').resolve()))
import verify_native_weapon_chain as v
code=Path('output/_v1110/verify_native_weapon_chain.py').read_text(encoding='utf8')
code=code.replace("('baseline',ACCEPTED/'bundle_src',ACCEPTED/'bundle.dll')","('baseline',WORK.parent/'buff_inline_types_prototype/prototype_src',WORK.parent/'buff_inline_types_prototype/prototype.dll')")
code=code.replace("if __name__=='__main__':verify(WORK/'prototype_src',WORK/'prototype.dll',WORK/'weapon_chain_tests.json')",'')
ns=dict(__name__='weapon_chain_matched_diagnostic');exec(compile(code,'matched_diagnostic','exec'),ns)
ns['verify'](v.WORK/'prototype_src',v.WORK/'prototype.dll',v.WORK/'matched_normal_diagnostic.json')
