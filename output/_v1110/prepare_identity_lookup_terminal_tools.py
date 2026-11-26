"""Prepare the new round's terminal records, deployment and existing-ref backup."""
import ast
from prepare_native_identity_lookup import STAGE
from setup_native_identity_lookup_bundle import adapt

def once(t,a,b):
    assert t.count(a)==1,(a[:120],t.count(a));return t.replace(a,b,1)
def save(name,t):
    ast.parse(t,filename=name);p=STAGE/name;assert not p.exists();p.write_text(t,encoding='utf8',newline='\n')
def terminal_adapt(t):
    for a,b in [('record_container_builtins_round','record_identity_lookup_round'),('archive_container_builtins_round','archive_identity_lookup_round'),
        ('finish_container_builtins_release','finish_identity_lookup_release'),('verify_container_builtins_goal','verify_identity_lookup_goal'),
        ('close_container_builtins_round','close_identity_lookup_round'),('run_container_builtins_formal','run_identity_lookup_formal')]:t=t.replace(a,b)
    return adapt(t)
def main():
    t=terminal_adapt((STAGE/'record_container_builtins_round.py').read_text('utf8'))
    t=once(t,"MARKER='## 容器内建调用组合终态（2026-11-26）'","MARKER='## 对象身份与容器查找组合终态（2026-11-26）'")
    t=once(t,"('container_builtins_tests.json',128128)]","('container_builtins_tests.json',128128),('identity_lookup_tests.json',396400)]")
    t=once(t,"assert read(WORK/'post_ab_directed_regressions.json')['container_builtin_cases']==128128","assert read(WORK/'post_ab_directed_regressions.json')['container_builtin_cases']==128128\n        assert read(WORK/'post_ab_directed_regressions.json')['identity_lookup_cases']==396400")
    t=t.replace('container_builtins_deployed_retaining_all_prior_components','identity_lookup_deployed_retaining_all_prior_components')
    t=once(t,'total_semantic_cases=463904','identity_lookup_cases=396400,total_semantic_cases=860304')
    start=t.index('。基于实际生产0A6D，');end=t.index('\\n\\n完整{cpu',start)
    description='。基于实际生产5BD3，仅改native_scalar_equal.hpp与gd_rt.cpp：在既有标量相等助手中补充Obj／Dict／ClassRef／Enum／FuncRef／Rng的原纯指针比较，及Str／Arr同一指针返回；不同字符串／数组保留原比较。数组find／count两处和字典find_index三处使用保守查找比较，任何Float查找参数仍调用原gd_eq，Vec2／Color／混合数值／不同嵌套数组仍保留原语义；不按Color同一地址短路，因同一颜色也必须比较含NaN的分量。哈希门槛、桶和顺序、循环起点转换、原gd_eq与call_method体、RNG及全部计数保持。严格逆变换逐字还原两份旧文件，其他711份目录文件、708份C++清单及全部674对象头／GdVal24／GdArr32／GdDict32／CoreItem2112／BattleCtx328／watch64布局不变。此前容器、私有、标量、显示、逐帧和control优化均保留。原型完整20普通对象仅作语义验证；正式完整20插桩／新18PGO，原浮点选项保持。新增396400例（112值形态、200704比较、145152数组查询、2144参数别名、48384字典查询及16单求值检查），逐例比较独立实际基线DLL的结果／异常标志／MXCSR，整数网格额外保留完整观测向量；负数、2^32与极大起点转换、碰撞桶、模式退回、未知种类、嵌套数组、NaN和16浮点模式保持。另保留既有463904语义例，共860304及独立4项registry边界。新增夹具首稿用负坐标初始化0..15整数网格，在任何正式计时前的基线初始化断言处停止；仅将存储坐标修为合法范围，保留全部负查询、计数和旧失败脚本／日志；源码、DLL及构建未改，全部检查随后完成。'
    t=t[:start]+description+t[end:]
    t=t.replace('容器内建调用已部署','对象身份与容器查找已部署').replace('C++模拟器容器内建调用优化记录_2026-11-26.md','C++模拟器对象身份与容器查找优化记录_2026-11-26.md')
    save('record_identity_lookup_round.py',t)

    t=terminal_adapt((STAGE/'archive_container_builtins_round.py').read_text('utf8'))
    scripts=('prepare_native_identity_lookup.py','setup_identity_lookup_semantics.py','build_native_identity_lookup.py',
        'test_native_identity_lookup.cpp','verify_native_identity_lookup.py','verify_identity_lookup_builtins.py',
        'verify_identity_lookup_truth.py','verify_identity_lookup_private.py','verify_identity_lookup_display.py','verify_identity_lookup_control.py',
        'run_native_identity_lookup_semantics.py','resume_native_identity_lookup_semantics.py','prototype_native_identity_lookup_bundle.py',
        'setup_native_identity_lookup_bundle.py','prepare_identity_lookup_terminal_tools.py','run_identity_lookup_formal.py',
        'verify_identity_lookup_build_options.py','review_identity_lookup_release.py','close_identity_lookup_round.py',
        'record_identity_lookup_round.py','archive_identity_lookup_round.py','finish_identity_lookup_release.py','verify_identity_lookup_goal.py',
        'fit_native_serial_load.py','record_container_builtins_followup.py','test_native_scalar_truth.cpp',
        'test_native_identity_snapshots.cpp','test_native_private_buff_loops.cpp','test_native_private_integer_view.cpp')
    start=t.index('SCRIPTS=');end=t.index('\n\n',start);t=t[:start]+'SCRIPTS='+repr(scripts)+t[end:]
    t=t.replace('container-builtins-own-','identity-lookup-own-').replace("STAGE.glob('container_builtins*.log')","STAGE.glob('identity_lookup*.log')").replace("'container_builtins_archive_'","'identity_lookup_archive_'")
    t=t.replace("STAGE/'native_perf50/method_dispatch_probe_20261126'","STAGE/'native_perf50/container_builtins_followup_profile'")
    t=t.replace("paths.add(STAGE/'method_dispatch_counts_first.log')","paths.add(STAGE/'container_builtins_followup_profile_first.log')")
    t=t.replace('C++模拟器容器内建调用优化记录_2026-11-26.md','C++模拟器对象身份与容器查找优化记录_2026-11-26.md')
    t=t.replace('perf: preserve container builtin trial with complete evidence','perf: preserve identity and container lookup trial evidence')
    save('archive_identity_lookup_round.py',t)
    save('finish_identity_lookup_release.py',terminal_adapt((STAGE/'finish_container_builtins_release.py').read_text('utf8')))
    save('verify_identity_lookup_goal.py',terminal_adapt((STAGE/'verify_container_builtins_goal.py').read_text('utf8')))
    print('Prepared terminal tools; no measurements or production files changed',flush=True)

if __name__=='__main__':main()
