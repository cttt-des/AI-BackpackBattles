"""Store proven Int/Bool Buff locals as scalars; retain arithmetic and callback order."""
import argparse
import hashlib
from pathlib import Path
from optimize_native_serial_paths import method_body

ORIGINAL_SHA256 = '06caa727976b8903fa12ccd0c5f9bb5e1b2e5ca935aa3d36b1d7abb758d6962c'
CANDIDATE_SHA256 = 'a20b593fd8072c7bd26e54c494cd45900f56fbf291587477c72cfe89911aaad3'
PATCHES = [('    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();\n    lv_amount = gd::gd_coerce_int(lv_amount);\n', '    // These locals are coerced once; amount assignments already coerce to Int.\n    struct NativeBuffInteger {\n        int64_t value;\n        explicit NativeBuffInteger(const gd::GdVal& input):value(gd::gd_coerce_int(input).i) {}\n        NativeBuffInteger& operator=(const gd::GdVal& input) {value=input.i;return *this;}\n        operator gd::GdVal() const {return gd::GdVal::from_int(value);}\n    };\n    struct NativeBuffBoolean {\n        bool value;\n        explicit NativeBuffBoolean(const gd::GdVal& input):value(gd::gd_coerce_bool(input).b) {}\n        operator gd::GdVal() const {return gd::GdVal::from_bool(value);}\n    };\n    NativeBuffInteger lv_amount((_argc > 0) ? _args[0] : gd::GdVal::null());\n', 1), ('    gd::GdVal lv_reflect = (_argc > 4) ? _args[4] : (gd::GdVal::from_bool(false));\n    lv_reflect = gd::gd_coerce_bool(lv_reflect);\n', '    const NativeBuffBoolean lv_reflect((_argc > 4) ? _args[4] : gd::GdVal::from_bool(false));\n', 1), ('gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_amount, gd::GdVal::from_int(0LL))))', '(lv_amount.value == 0)', 1), ('gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(lv_reflect)))', '(!lv_reflect.value)', 2)]


def normalize(source):
    match=method_body(source,'CoreBuff','gainTemporary');body=match[0]
    digest=hashlib.sha256(body.encode()).hexdigest()
    if digest==ORIGINAL_SHA256:return source
    if digest!=CANDIDATE_SHA256:raise ValueError('The verified Buff gain method changed')
    for old,new,count in reversed(PATCHES):
        if body.count(new)!=count:raise ValueError('A scalar-local region changed')
        body=body.replace(new,old)
    assert hashlib.sha256(body.encode()).hexdigest()==ORIGINAL_SHA256
    return source[:match.start()]+body+source[match.end():]


def transform(source):
    source=normalize(source);match=method_body(source,'CoreBuff','gainTemporary');body=match[0]
    for old,new,count in PATCHES:
        if body.count(old)!=count:raise ValueError('The scalar-local source region changed')
        body=body.replace(old,new)
    assert hashlib.sha256(body.encode()).hexdigest()==CANDIDATE_SHA256
    return source[:match.start()]+body+source[match.end():]


def optimize(native):
    runtime=(native/'gd_rt.cpp').read_text('utf8')
    for proof in ('GdVal gd_coerce_int(const GdVal& v) { return GdVal::from_int(v.as_int()); }',
                  'GdVal gd_coerce_bool(const GdVal& v) { return GdVal::from_bool(gd_truth(v)); }'):
        if runtime.count(proof)!=1:raise ValueError('A scalar coercion invariant changed')
    path=native/'gen/shards/shard_00.cpp';source=path.read_text('utf8');output=transform(source)
    if path.read_bytes()!=output.encode():path.write_text(output,encoding='utf8',newline='\n')
    print('Scalar Buff amount/reflect locals; original coercions, numeric operations and callbacks retained',flush=True)


if __name__=='__main__':
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('native',type=Path);optimize(p.parse_args().native)
