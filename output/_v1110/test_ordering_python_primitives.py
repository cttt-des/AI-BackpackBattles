"""Check unaffected primitive and RNG behavior after rebuilding the runtime."""
import argparse,hashlib,json,math,random,struct,sys
from pathlib import Path

def main():
    p=argparse.ArgumentParser();p.add_argument('--package',type=Path,required=True);p.add_argument('--out',type=Path,required=True);a=p.parse_args()
    sys.path.insert(0,str(a.package.resolve()));import gd_core_py._rt as r
    assert Path(r.__file__).resolve().is_relative_to(a.package.resolve())
    hasher=hashlib.sha256();cases=0
    def value(x):
        if isinstance(x,float):return ['float',struct.pack('<d',x).hex()]
        if isinstance(x,(list,tuple)):return [value(v) for v in x]
        if isinstance(x,dict):return [[value(k),value(v)] for k,v in x.items()]
        return [type(x).__name__,x]
    def record(fn,*args):
        nonlocal cases
        try:out=['ok',value(fn(*args))]
        except Exception as e:out=['error',type(e).__name__]
        hasher.update((json.dumps(out,sort_keys=True)+'\n').encode());cases+=1
    numbers=[0.,-0.,1.,-1.,.5,-.5,1.5,-1.5,2**-149,2**-126,2**-1022,5e-324,float('inf'),-float('inf'),float('nan'),0,1,-1,(1<<53)-1,1<<53,(1<<63)-1,-(1<<63)]
    rng=random.Random(0x37629)
    for _ in range(2048):numbers.append(struct.unpack('<d',rng.getrandbits(64).to_bytes(8,'little'))[0])
    for x in numbers:
        for name in ('f32','gd_round','floor','ceil','sign'):record(getattr(r,name),x)
    for x in numbers[:64]:
        for y in numbers[:64]:
            record(r._div,x,y);record(r._mod,x,y)
    for seed in (0,1,42,0xffffffff,0x7fffffffffffffff,0xffffffffffffffff):
        random_source=r.RandomNumberGenerator(seed)
        for _ in range(2048):record(random_source.randi)
        for _ in range(2048):record(random_source.randf)
        for _ in range(256):record(random_source.randf_range,-.2,.2)
    for i in range(1024):
        v=r.Vector2(i*.125,-i*.25);record(lambda v=v:(v.x,v.y));record(lambda v=v:(v+v).length())
    report=dict(rt_module=r.__file__,primitive_cases=cases,primitive_and_rng_sha256=hasher.hexdigest(),sort_intentionally_excluded=True)
    a.out.write_text(json.dumps(report,indent=2)+'\n',encoding='utf8');print(json.dumps(report))
if __name__=='__main__':main()
