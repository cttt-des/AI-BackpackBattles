# build_cython 用法（2026-11-13 更新）

> 一句话：**改完 `.gd`/生成器后重编，用 `--jobs` 并行；默认已自适应分片，不要手搓串行。**

## 1 最常用三条

```bash
cd "D:/文件资料/学习/自动背包AI"

# ① 全量重编（改过生成器 / 大量 .gd 后）——约 20-25 分钟
python -X utf8 tools/build_cython.py --list output/perf/_all_list.txt --msvc

# ② 只编指定模块（改 1-2 个文件时）
python -X utf8 tools/build_cython.py gd_core_py/gd_core/CoreItem.py --msvc

# ③ 验证产物是否新鲜（不编译）
printf '%s\n' gd_core_py/gd_core/CoreCombat.py > /tmp/one.txt
python -X utf8 tools/build_cython.py --list /tmp/one.txt --msvc    # 报「全部目标新鲜」即最新
```

## 2 参数

| 参数 | 说明 |
|---|---|
| `targets...` | 若干 `.py` 相对路径 |
| `--list FILE` | 清单文件，每行一个相对路径（**推荐**，全量时用） |
| `--msvc` | 用 MSVC 后端（本项目正式路径；不加则走 MinGW） |
| `--jobs N` | 并行进程数，默认 `cpu//2`；`--jobs 1` = 旧串行 |
| `--clean` | 删除目标 `.pyd`/`.c`（回滚手段） |

**自适应分片**：cl 分片数 = `clamp(ceil(模块数/12), 1, min(jobs, 模块数))`。
小任务不会被切碎（每片一次 `vcvars` ≈5s 固定开销）。扫参结论：cl 拐点在 4 片，
cython 段偏好更多进程。

## 3 实测性能（本机 4 物理核 / 8 逻辑核）

| 场景 | 耗时 |
|---|---|
| 30 模块 串行逐模块（旧） | **229 s** |
| 30 模块 分批 + 并行（现在） | **66 s**（3.5x） |
| 60 模块 cl 段 `--jobs 2/4/6/8` | 161 / 79 / 87 / 81 s |
| 纯 cython 段加速（24 模块 4×4） | **10.4x**（逐模块 spawn → 单批 CLI） |
| 全量 668 模块（外推） | **约 20–26 分钟** |

两个关键原理（别退回旧写法）：

1. **cython 要分批**：每次单起一个 cython 进程要付 Cython 自身 import（2-3s），
   单模块 4-8.5s 里大半是这个。现在一批（BATCH=12）一次 CLI 调用。
2. **cl 要分片并行**：切成 N 个 bat 并行跑，每片各自 vcvars 一次。

## 4 三个必须知道的坑

| 坑 | 现象 | 原因/对策 |
|---|---|---|
| **中文路径编码** | 全部 `MISS`（`.pyd` 不产出，静默回落 `.py`，闸门照样绿） | cmd 代码页 65001 而 bat 曾按 gbk 写 ⇒ cl 收到乱码路径。**已修**：bat 用 utf-8 写 + 首行 `chcp 65001` |
| **mtime 幂等** | 「重编」却没真正重编 | 判定是 `pyd 晚于 .py 与 .pxd`。改完源必须确认 `.py` mtime 更新（生成器有「内容不变跳过写盘」） |
| **ABI 级联** | 改一个基类 `.pxd` 触发数百模块重编 | `gd_core_items/Item.pxd` 被 **240 个模块** cimport；这是设计使然，只能靠并行摊平，别硬改依赖 |

## 5 编完必做的两步

```bash
# ① 产物与源同步检查（不等同于编译成功）
python -X utf8 tools/gd_to_py.py --check

# ② 确认产物比源新（G-E 编译态纪律）
printf '%s\n' gd_core_py/gd_core/CoreCombat.py > /tmp/one.txt
python -X utf8 tools/build_cython.py --list /tmp/one.txt --msvc   # 应报「全部目标新鲜」
```

> **纪律**：任何「编译态」结论，都必须先能证明 `pyd 比 .py/.pxd 新`。
> 历史上出现过「pyd 存在即跳过」导致多轮重编空转、闸门却全绿的事故。

## 6 快速自检（改完脚本后跑这个）

```bash
python -X utf8 tools/build_cython.py --list output/perf/_par30.txt --msvc --jobs 4
# 期望输出形如：
#   [msvc-list] cython 30 模块 / 4 批 / 4 进程 耗时 7.9s
#   [msvc-list] cl 并行 3 分片 / 30 模块 耗时 57.6s，非零 rc 分片 0
#   [msvc-list] 缺失 0 / 重编目标 30
# 判据：缺失必须为 0；「非零 rc 分片」必须为 0。
```

