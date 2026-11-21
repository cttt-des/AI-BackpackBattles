"""Refresh the still-deployed1426 binary after the retained candidate's tests."""
from pathlib import Path
import ast

STAGE=Path(__file__).resolve().parent
WORK=STAGE/'native_perf50/type_constructor_bundle'

def main():
    text=(STAGE/'native_perf50/item_locality_bundle/profile_baseline.py').read_text('utf8')
    text=text.replace('444e75c6872fa2acec57f42d88eb6687c29f2dc97a82b88ba3e66fdf849312cc','14263d42d22021a83849baffddf2f6288694886f2733a66c0473850b37407548')
    text=text.replace('post_eager_trace_profile','post_property_control_profile')
    ast.parse(text)
    path=WORK/'profile_baseline.py';assert not path.exists()
    path.write_text(text,encoding='utf8',newline='\n')
    out=STAGE/'native_perf50/post_property_control_profile';out.mkdir(exist_ok=True)
    print(path)

if __name__=='__main__':main()
