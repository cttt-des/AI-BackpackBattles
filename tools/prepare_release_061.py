"""Stage the verified optimization runtime for the next native release."""
from pathlib import Path
import shutil
import json
import hashlib
ROOT=Path(__file__).resolve().parents[1]
for name in ('libgdcore.dll','sim.py','gd_core_runtime.json','manifest.json'):
    shutil.copyfile(ROOT/'dist/native_1_1_10'/name,ROOT/'backpack_native'/name)
assert hashlib.sha256((ROOT/'backpack_native/libgdcore.dll').read_bytes()).hexdigest()=='593acaf3d6bf1dfedc7926cc5f3659c074a285dd95a9dcf0db95c1f913077670'
for name in ('pyproject.toml','backpack_native/__init__.py','backpack_native/gui.py','backpack_native/selftest_case.json','tools/build_native_release.py','tools/verify_native_release.py'):
    p=ROOT/name
    text=p.read_text('utf8').replace('0.6.0','0.6.1').replace('release_source_v060','release_source_v061')
    if name.endswith('verify_native_release.py'):
        text=text.replace('output/_v1110/native_hot_path_full_gate.json','output/_v1110/native_perf50/lazy_diagnostics_bundle/bundle_full_gate.json')
    p.write_text(text,encoding='utf8',newline='\n')
p=ROOT/'README.md';text=p.read_text('utf8').replace('v0.6.0','v0.6.1').replace('0.6.0-cp314','0.6.1-cp314')
start=text.index('- v0.6.1 发布基准');end=text.index('\n',start)
text=text[:start]+'- 最新内核在固定200场、单线程连续24批中位178.95场/秒，最慢120.12场/秒；本次20%后台负载拟合149.97场/秒。最后一轮32对A/B的CPU耗时中位降低0.52%，墙钟降低0.14%，组间有分歧；不同轮拟合值的上涨不能视为代码提速。'+text[end:]
text=text.replace('output/_v1110/native_hot_path_full_gate.json','output/_v1110/native_perf50/lazy_diagnostics_bundle/bundle_full_gate.json').replace('output/_v1110/native_hot_path_benchmark.json','output/_v1110/native_perf50/lazy_diagnostics_bundle/measurements_summary.json')
text=text.replace('构建前将已验收 `native_hot_path.dll` 放入 `backpack_native/libgdcore.dll`','构建前将已验收 `dist/native_1_1_10` 的DLL、绑定、运行数据和清单同步到 `backpack_native/`')
p.write_text(text,encoding='utf8',newline='\n')
with (ROOT/'.gitignore').open('a',encoding='utf8') as f:f.write('\n# Local profiling, packaged runtimes and release staging (verified snapshots remain tracked).\n/output/_v1110/native_perf50/\n/output/release_source_v*/\n/dist/\n*.gcda\n*.gcno\n')
notes='''# v0.6.1 — 确定性 C++ 性能优化

游戏版本1.1.10；保持2,604场原版逐事件一致，优化前后事件哈希一致。

固定200场单线程连续24批：中位178.95场/秒，最慢120.12场/秒；接电，后台负载3.07%–29.59%。独立校准覆盖7.29%–76.57%，20%负载拟合149.97场/秒。最后一轮32对A/B的CPU耗时中位降低0.52%、墙钟降低0.14%，组间有分歧；跨轮拟合差异不能当作代码收益。

包含事件派发、纯属性读取、类型与构造、物品装配及冗余诊断优化。保留逐帧时序、回调顺序和RNG语义。

下载BackpackSimulator.exe直接运行；wheel适用于CPython3.14、Windows x64，建议AVX2处理器。支持阵容JSON、批量胜率及结果JSON导出。

DLL SHA-256：593acaf3d6bf1dfedc7926cc5f3659c074a285dd95a9dcf0db95c1f913077670。
'''
(ROOT/'docs/release_v0.6.1.md').write_text(notes,encoding='utf8')
