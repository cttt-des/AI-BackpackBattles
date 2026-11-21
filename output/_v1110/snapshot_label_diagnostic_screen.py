"""Preserve the exact helper screened before extending this same-path candidate."""
import hashlib
import json
from pathlib import Path
import shutil

STAGE=Path(__file__).resolve().parent
WORK=STAGE/'native_perf50/lazy_diagnostics_probe'
text=(STAGE/'native_lazy_diagnostics.hpp').read_text('utf8')
text=text.replace('#include "gen/hdrs/Gd__gd_core__CoreBuff.hpp"\n#include "gen/hdrs/Gd__gd_core__CoreBuff__INNER__TemporaryStacks.hpp"\n#include <bit>\n#include <initializer_list>\n','')
start=text.index('\ninline bool native_diagnostic_context_off')
end=text.index('\n// The omitted arguments',start)
text=text[:start]+text[end:]
text=text.replace('    if(!native_diagnostic_context_off(ctx,item.f_ctx))return false;', '''    const auto* context=native_diagnostic_exact<Gd__gd_core__CoreContext>(ctx,item.f_ctx,&META_Gd__gd_core__CoreContext);
    if(!context)return false;
    const auto* rng=native_diagnostic_exact<Gd__gd_core__CoreRng>(ctx,context->f_rng,&META_Gd__gd_core__CoreRng);
    if(!rng || rng->f_oracle_trace.kind!=GdVal::Kind::Bool)return false;
    if(rng->f_oracle_trace.b && (rng->f__stacktrace.kind!=GdVal::Kind::Bool || rng->f__stacktrace.b))return false;''')
expected=json.loads((WORK/'screen.json').read_bytes())['source_sha256']['native_lazy_diagnostics.hpp']
assert hashlib.sha256(text.encode()).hexdigest()==expected
(WORK/'label_helper_screen_snapshot.hpp').write_text(text,encoding='utf8',newline='\n')
for name in ('test_native_lazy_diagnostics.cpp','prepare_native_lazy_diagnostics.py'):
    shutil.copyfile(STAGE/name,WORK/('label_screen_snapshot_'+name))
print('Initial label helper snapshot verified',expected)
