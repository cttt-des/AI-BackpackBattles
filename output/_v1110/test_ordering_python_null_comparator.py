"""Check null comparator return/call schedule against the live Godot oracle."""
import argparse,json,sys
from pathlib import Path
def main():
    parser=argparse.ArgumentParser();parser.add_argument('--package',type=Path,required=True);parser.add_argument('--work',type=Path,required=True);parser.add_argument('--out',type=Path,required=True);a=parser.parse_args()
    sys.path.insert(0,str(a.package.resolve()));from gd_core_py import _rt
    class Compare:
        def __init__(self):self.comparisons=[]
        def compare(self,x,y):self.comparisons.extend((x,y));return None
    compare=Compare();items=list(range(8));_rt._sort_custom(items,compare,'compare')
    actual=dict(order=items,comparisons=compare.comparisons);expected=json.loads((a.work/'timer_sort_original.json').read_bytes())['result'];assert actual==expected
    a.out.write_text(json.dumps(dict(passed=True,result=actual,compiled_rt=_rt.__file__),indent=2)+'\n',encoding='utf8');print('Python null comparator matches original Godot14-call schedule')
if __name__=='__main__':main()
