# tools/oneoff/ — 一次性侦察与诊断脚本（冻结归档）

这些脚本**不是**流水线的一部分，也不在维护范围内。它们当初是用来「把问题量化成
清单」的一次性探针 —— 结论已经固化进 `docs/gd_core_truth.md` 与各工具的文档字符串，
脚本本身留着只是为了**可复查**（当初那个数字是怎么数出来的）。

★ 它们**可以随时跑不起来**（依赖当时的临时目录结构、当时的产物形态）。不要拿它们
  当验收判据，也不要在流水线里调用它们。

## 归档理由

| 类别 | 文件 | 用途 | 结论已固化到 |
|---|---|---|---|
| 语法面侦察 | `survey_builtins` `survey_dispatch` `survey_methods` `survey_modnames` `survey_nested` `survey_never_self` `survey_operators` `survey_pykw` `survey_rng` `survey_statics` `survey_strcall` `survey_match` `survey_classrefs` `survey_classrefs2` | 量化 GDScript→Python 的转写需求 | `tools/gd_to_py.py` 文档 + `tools/survey_gd_syntax.py --verify`（**21 项断言，走样即 FAIL**） |
| 调用点探针 | `show_calls` `probe_assembly` `probe_effect_params` `probe_inventory_api` `probe_parent_calls` `probe_pcalls2` | 定位某类调用的真实落点 | `docs/gd_core_truth.md` §5/§6；`tools/count_api_usage.py`（**可复算的替代品**） |
| Godot 源码取证 | `fetch_godot_src` `pcg_align` `fetch_color_table` | 拉 3.6-stable 源码、比对 PCG 实现、抽色表 | `tools/verify_godot_rng.py`（闸门 12）、`tools/gen_color_names.py` |
| 色表旧链路 | `make_colors.py` `_colors_header.txt` `color_table.py` | 由 `fetch_color_table` 的产物合成 `_colors.py` | 已被 `tools/gen_color_names.py` **完全取代**（一步到底，且带 `--check`）。数据指纹 `sha256=70286c7e…`（146 条）迁移前后一致 |
| 本轮缺陷定位 | `diff_assembly` `bisect_engine` `chk_seed` `smoke_gd_engine` | 定位「网格 occupied 平移两次」与「`seed=None` 退化成同一场」两个缺陷 | `docs/gd_core_truth.md` §10.5/§10.7、`tools/check_gd_core_engine.py`（闸门 14）注释 |
| 转写缺口定位（2026-09-27 三轮） | `repro_allitems` `dbg_shadow` `positive_control_drop` `add_gate17` | ① `repro_allitems` = 517 件逐一上场的**最小复现器**，跑出 19 件崩溃 / 六类根因；② `dbg_shadow` = 调试 Python 侧继承链解析（它用的正则**已带单引号**，正是 A 段那个扫描器 bug 的解法）；③ `positive_control_drop` = 人为删一行要求扫描报出；④ `add_gate17` = 闸门 17 的结构化插入脚本（带命中数与行数双 assert） | `tools/scan_translit_gaps.py`（闸门 11）、`tools/check_scan_gaps.py`（闸门 11 正对照）、`tools/check_gd_py_items.py`（闸门 17）、`docs/gd_core_truth.md` §11.2/§11.3 |

## 不在本目录的「转正」脚本

| 原位置 | 现位置 | 为什么转正 |
|---|---|---|
| `output/survey_gd_syntax.py` | `tools/survey_gd_syntax.py` | 它是「可以机械转写」这个论断的**唯一证据来源**，且带 `--verify` 进了流水线 0/14 前置阶段 |
| `output/positive_control_drop.py` | `tools/check_scan_gaps.py` | 「**判据的判据**」不能只做一次 —— 扫描器以后还会被改，正对照必须跟着每次流水线跑。它当场抓出 `re.M` 缺失（`^` 只匹配文件首行 → C 段恒返回「无」） |

★ 转正 ≠ 删除原型：`positive_control_drop.py` 以**硬编码路径 + `--drop` 单次运行**的形态留在这里，
`tools/check_scan_gaps.py` 则会**自动挑目标行**（不写死）、跑完整三段扫描、用 `try/finally` 还原并复核字节一致。
两者用途不同 —— 前者手查，后者守门。

## 保留在 output/ 的非脚本资产

- `output/godot_src/` —— Godot 3.6-stable 源码片段缓存（`color_names.inc` 等），
  `tools/gen_color_names.py` 的数据源。**不要删**（删了要联网重拉）。
- `output/color_table.py` 的等价数据现已由 `tools/gen_color_names.py` 直接产出，
  不再需要中间文件。

## 与 `output/` 的关系

`output/` 在 `.gitignore` 里（不进版本库）。本目录**进**版本库 —— 这正是把脚本放这
而不是留在 `output/` 的原因：`output/` 里的东西随时可能被清掉且无法找回。
