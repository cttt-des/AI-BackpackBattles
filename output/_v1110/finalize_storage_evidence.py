"""Freeze original storage profiles and append the final, non-deployment outcome."""
import hashlib
import json
from pathlib import Path
import shutil

STAGE = Path(__file__).resolve().parent
WORK = STAGE / 'native_perf50/storage_bundle'
REPO = STAGE.parents[1]

def sha(p):
    return hashlib.sha256(p.read_bytes()).hexdigest()

def main():
    profile = json.loads((WORK / 'fresh_profile_source.json').read_bytes())
    objects = Path((WORK / 'bundle_objects.txt').read_text('utf8'))
    frozen = WORK / 'frozen_pgo_counts'
    frozen.mkdir(exist_ok=True)
    for name, digest in profile['hot_profiles_sha256'].items():
        source = objects / 'pgo' / (name + '.gcda')
        assert sha(source) == digest
        target = frozen / source.name
        if target.exists():
            assert sha(target) == digest
        else:
            shutil.copyfile(source, target)
    record = dict(dll_sha256=profile['dll_sha256'],
                  source_manifest_sha256=profile['source_manifest_sha256'],
                  counts=profile['hot_profiles_sha256'])
    (WORK / 'frozen_pgo_manifest.json').write_text(json.dumps(record, indent=2)+'\n', encoding='utf8')
    receipt = json.loads((WORK / 'rejection_receipt.json').read_bytes())
    assert receipt['not_deployed'] and receipt['single_run_all_samples_retained']
    note = '''

## storage组合最终收尾（2026-11-23）

全20单元插桩／全新18热单元PGO、完整前置回归和实际正式DLL的87,425项存储差分均完成。固定200单线程首24对按冻结规则追加最后8对，32对最终CPU配对中位降耗-2.1651%、墙钟-1.9841%，累计降耗-1.2045%／-1.4373%；各组方向不一致，记录inconclusive_retained，不部署、不再追加同源码组。减少1,463,599次分配调用没有转化为可采纳收益，不能用分配次数代替测速。

唯一一次非发布24批校准：20%负载换算120.6888场/秒，原始中位105.2763、最低72.6014、最高124.2127。实际负载覆盖16.4273%至54.2851%，全程AC，拟合相对时间误差中位2.1312%、P90 4.2721%；该校准不是发布raw24，不与历史不同环境的换算值直接计算代码收益。A/B未通过，所以未运行后置2604验收、发布raw24或部署。生产两处DLL仍d8a736。

全部进程已结束，原始32对和校准原样保留；目录native_perf50/storage_bundle，查看candidate_decision.json、ab_assessment_32.json、rejection_receipt.json。下一轮从已部署d8a736重新评估事件字面量参数的非逃逸传递及惰性物化，不继承未采纳storage组合。持续目标仍为20%负载200场/秒，尚未达到。
'''
    for name in ('C++模拟器性能优化清单.md', 'C++模拟器下一阶段优化评估.md', 'C++模拟器优化交接_2026-11-23.md'):
        path = REPO / 'docs' / name
        text = path.read_text('utf8')
        assert '## storage组合最终收尾（2026-11-23）' not in text
        with path.open('a', encoding='utf8', newline='\n') as stream:
            stream.write(note)
    print('Frozen 18 original PGO counts and recorded final non-deployment outcome')

if __name__ == '__main__':
    main()
