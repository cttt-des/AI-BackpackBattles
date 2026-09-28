# 背包乱斗 AI — 项目记忆

## 一句话
《Backpack Battles》外置 AI：进程内存读取 + pyautogui 操作，不改游戏文件。核心资产 = Python 战斗模拟器 + 逆向产出的 `gd_core` 无头内核（当前主线）。

## 运行环境（每次会话必用）
- PATH 前缀：`export PATH="/c/Users/Windows/.workbuddy/binaries/PortableGit/versions/1.2.0/usr/bin:/c/Windows/System32:$PATH"`
- Python：`C:/Users/Windows/.workbuddy/binaries/python/versions/3.13.12/python.exe`；**含 pycryptodome** 的：`.../python/envs/default/Scripts/python.exe`
- Godot 3.6 宿主：`output/godot36/Godot_v3.6-stable_win64.exe`
- 长命令一律 `timeout N`；★ heredoc 会吞反斜杠（`\w`→`w`）→ 正则/脚本写成文件再跑
- ★ 并行 Edit 同一文件**会丢改动**（必须串行）；`rm -rf <dir>` 触发 SIGTERM（逐个 `rm -f`）

## 逆向资产
- GDEC 密钥 `8671424952511006d39f4c9e918f821391e2b06a80d946d693fb8757154ce849`（`tools/script_key.txt`）；物品 CSV 另有 `tools/csv_key.txt`
- 容器 `[4 "GDEC"][4 ver][16 MD5(明文)][8 LE 长度][AES-256-ECB]`（无 IV）
- `decompiled_full/` = 820 个 .gd 全量反编译（**权威源码**）；`extracted/` = 原始 .gde/.tscn
- ★ 原版 tscn / CSV 加密，utf-8 直读会**静默出乱码** → 一律走 `tools/item_sheet.py`

## gd_core 无头内核（当前主线）
- 目标：战斗逻辑移植成不依赖场景树的纯逻辑内核，**逻辑 1:1 不变**且更快
- 形态：`gd_core/` 18 脚本 9067 行，全 `extends Reference`；单例→`ctx` 注入；表现→`CoreHooks` 51 个空实现（**全在函数尾部，不参与判定**——保真论证前提）
- ★★ **直挂方案**：`gd_core_items/`（503 份自动生成）= `Item.gd` 适配层 + 502 件物品脚本，**逐字不改**直挂 CoreItem；转译只做「视觉剥离 + 符号映射」
- ★★ `_behavior` **两级派发**：注入优先 → 回落 `callv` 打物品自身，回落**仅限 `SELF_BEHAVIOR_METHODS` 白名单**（只含基类未定义的回调名），否则自我递归。早先只做注入 → 98 件 `onCombatStart` 等回调全静默不执行且零报错
- 验收：`python tools/run_gd_core.py [--bench]` = **十七道闸门**，须 `EXIT=0`；0 阶段 = 7 支生成器 + 1 支前置断言；闸门 9 = 517 件逐一上场（≈22s，**兼产冷却遥测**）；闸门 10 = 宝石 Socket 门面；闸门 11 = 转写缺口扫描**三小步**（`check_gd_py.py` → `scan_translit_gaps.py` → `check_scan_gaps.py`）；闸门 15 = 逐事件对照（4053 条，三级判定）；**闸门 16 = 冷却等价校验**（依赖门 9 的产物）；**闸门 17 = Python 侧 517 件逐一上场**（≈3 分钟墙钟，**全部闸门里最慢**，排最后因不产出下游文件）
- ★ **冷却等价校验（闸门 16，`tools/verify_cooldowns_gd.py`）两半不可互替**：A 静态 = 冷却路径 27 对函数逐行对照（差异须落进「机械改名/语义改写/已声明剥离/内核新增」四类台账，落不进或台账 0 命中即 FAIL）→ 只说「照抄了原版」；B 动态 = 门 9 逐帧轮询 303 件（D1 恒等式 22.8 万帧 0 违背）→ 只说「跑起来是这么算的」。**分工铁律：Godot 侧只观察，判定全在 Python 侧**（内核改错时不会连断言一起改错）
- 覆盖度 **709/998 = 71.0%**（CoreItem 422/628）；**判定路径缺口 0 项**（2026-09-27 归零）
- ★ **Socket = 折叠，不是缺类**：插座身份折叠为宿主物品本身（`setGem` 把 self 当 socket、`getItem()` 恒返回 self）。定裁判据 = **访问面枚举**（`socket.` 共 15 处，战斗路径只有 `socket.getItem()`）。`setGemData`（存档序列化）/`initSockets`（后置条件恒真）本就不参与战斗。★ 若将来有行为脚本用 `socket.getGem()`，折叠即漏 → 需按 socketId 建门面。`lineup_gem_test` 已解锁（原 SKIP 理由陈旧）
- ★ **「零报错 ≠ 生效」**：宝石折叠没接上会安静跑完整场却毫无效果、一行错都不报。故宝石独有两道取证：闸门 8 的 A/B（去宝石侧 `gem_heals` 必须 0）+ 闸门 10 公式级（100→+7、57→+4 验 ceil；Armor 分支反向卡门「不得订阅 attacked」；Inventory 模式推帧让自身冷却自行触发）
- ★ 尚**不得宣称 gd_core 等价原版**：静态覆盖已核；**双引擎已做到逐事件一致**（闸门 15，4053 条 0 值差异）+ **冷却路径已做逐行+逐帧双取证**（闸门 16）。仍缺：① 事件对照只覆盖 8 套阵容 / 56 局（**闸门 17 已让 517 件在 Python 侧逐一上场，但它只判「不崩」不判「算得一样」** —— 数值一致性仍缺，要两侧都落轨迹，规模会从 4053 条涨到数十万条）；② 物品脚本**自带的分支**无逐条对照（静态覆盖 ≠ 分支覆盖）；③ 冷却之外的其余判定路径尚无同等级逐帧恒等式 → 当前只是「无已知偏差」，差别在于**尚未遍历到的分支**
- ★ **静态覆盖 ≠ 分支覆盖**：`gd_core_coverage.py` 的 709/998 是**方法名集合差**（度量基类有没有洞）。直挂方案下 517 件物品脚本自带的方法**不计入该表** → 「判定路径缺口 0」= 基类没洞，**不是**「每条 `if` 两侧都跑过」。闸门 16 A 段只覆盖基类 27 个函数是同一原因
- ★★ **Godot 3.6 实测（探针在 `output/probe_physproc/`）**：脚本里定义了 `_physics_process` 的节点，**入树后 `is_physics_processing()` 为 True**（裸 Node2D 为 False；`set_script()` 与 `PackedScene.instance()` 一致），全库 `.tscn` 无一处覆写 `physics_process` → 原版物品在「入树到首次 `preCombatStart`」之间该谓词为真，内核 `_cooldown_active` 为假。**机制差异，战斗内不可观测**（`preCombatStart` 无条件重置三项状态；读该谓词的战斗路径全在其后；枚举无「半路入树」物品——`BagofGiving/Lootbox/FurciferPrime/PortableAltar` 加的是商店池 `itemPool`）。未定裁残留：该窗口内是否真的推进/触发，需活体观察原版。登记在 `verify_cooldowns_gd.py::TENSIONS` + 文档 §6 张力 20
- ★ 判据纪律（本轮 4 次踩坑换来）：**判据失败时先怀疑判据**；打印精度必须远小于判据容差（`%.10f` 的 5e-10 反算误差逼近 1e-9 容差 = 判据自造假差异）；比值类判据的**分母语义**要回源码核（`descriptor.cd` ≠ `getCooldown()`，`LightningPotion.onPrepare` 会重写基准）；**「什么都没测到」不许冒充「测了且通过」**（Card 系整场零观测曾显示成全零不报错 → 补 `seen`/`start_act` 观测面列）
- ★ **NUMEQ 类的真实含义**：4053 条里 1780 条两侧**数值相等、仅 `int`↔`float` 表示不同**，根因是 **GDScript 的 `var x: int` 赋值时强制转换、Python 不会**（源 `CoreDamageResult.gd:18`）。判据对**截断敏感**：非整数会被 GDScript 截断 → 数值不等 → 立刻降级 DIFF 并指名。故 `DIFF 0` 精确含义 = 「这 56 局触达的转换点上值恰好都是整数」，**不等于**「全路径无非整数转换」
- 取证文档 `docs/gd_core_truth.md`（§5 五条剥离陷阱；§6 **20 条**已知偏差/张力；§7 闸门表（**17 道**）+ 闸门 16 理由（A/B 分工、四类台账、D2 四档）+ **闸门 17 存在理由（六类缺口表 + 三条共同特征 + 两处「判据本身坏了」）**；**§10 Python 转写与模拟器接入**（§10.6 含**闸门 17 的证据边界：只判「不崩」不判「算得一样」**）；§11 本轮新增守卫 + §11.1 闸门 16 抓到的 5 个问题 + **§11.2 变量遮蔽方法（三方案取舍表 + 两侧独立扫描的必要性）+ §11.3 本轮新增守卫**）
- ★ **生成物里不许写死核算结论**：数字必须生成那刻现算，需另一工具才知道的结论只能**指向**它（反例留痕：写死的「判定路径缺口为 0」曾是假断言，09-27 才偶然变成真）
- ★ 原版死代码照搬，但**不给死代码立契约**（`Gem.isInInventory()` 覆写了一个 Item 上不存在的方法、无调用点 → 刻意不写断言）
- ★ 压缩已到地板（`tools/measure_dead_weight.py`，只报告不删除）：死残留 `gd_core` 0.3%（26/9067）/ `gd_core_items` 1.5%（304/20244）。328 个空桩函数看似垃圾，实为原版 `has_method()` 派发落点，删了会让回调静默失效

## ★ 转写缺口（GD → Python，2026-09-27 立）
一行用户报错 `TypeError('float' object is not callable')` 挖出**整类**问题：Python 侧（**模拟器真正跑的那一份**）此前**从未把 517 件物品过一遍** → 19 件一用就崩，而 16 道闸门全绿。**面完成了，但没走遍。** 缺口三型：
- **A 变量遮蔽方法** —— ★★ **GDScript 双表 ↔ Python 单表**：GDScript 里 `GDScriptInstance::get` 查 **members** 表、`call` 查 **member_functions** 表，**两表独立**，子类 `var speed` 与基类 `func speed()` 可共存（`self.speed` 取变量、`self.speed()` 调方法）。**Python 只有一张表 → 实例属性遮蔽类方法 → `TypeError`**。实测 4 处撞名全是 `speed`（ChessMaster/GirlPower/PerpetuumMobile/Sloth），崩点在 `CoreItem.getSpeed()` 的 `self.speed()`。处置 = 生成器 **R8 撞名消歧**（`speed`→`speed_v`，判据 = 本文件顶层 `var` ∩ 继承链 `func` 名）；**不**改内核名（破坏逐行可核）、**不**改 `_rt`（运行期无法区分同名属性/方法）
- **B 未映射符号**（`NameError`）：`call_deferred` 8 件（→ 生成器 **R9** 映射 `ctx.defer`）/ `typeof`+`TYPE_VECTOR2` 12 件棋类 / `tr` 3 件（仅描述文本）/ `load` 1 件。**全在 GDScript 侧完全正常**（Godot 原生或内置提供）→ 只有 Python 侧会炸
- **C 整行丢失**：GD 有赋值、Python 产物里**连名字都没有**（A、B 都抓不到）→ 需专门的「丢行扫描」

## ★ 转写器自身的两个静默坑
- ★ **`mask_strings()` 在改写前把字符串字面量换成占位符** → 任何**依赖引号**的正则判据**恒不命中**。活例：`gd_to_py.py` 的 `load→_load` 规则写成 `load\s*\(\s*(?=\")`，**从写下起一次都没命中过**，垫片 `_rt._load` 一直是死代码。放宽为 `load\s*\(` 才生效（全库无自定义 `func load(`）
- ★ **`find_block_end()` 纯按缩进判块结束**，而多行字面量的 `}` 落在**第 0 列** → 块被提前判结束 → 该行整行被丢（波及 18 个文件）。**GDScript 解析器不看续行缩进**，所以另一侧毫无征兆。修：加括号深度跟踪。活例 `gd_core_items/Exclusive/WandofDissonance.gd`

## GDScript 3.x 坑位（改 gd_core 必看）
- `log`/`seed` 是内置函数，不能作成员名/形参；`class_name` 互相引用含自引用报 cyclic dependency
- ★★ **成员/方法两张表**：`var speed` 与 `func speed()` 可共存（`self.speed` 取变量、`self.speed()` 调方法），GDScript 不报错 —— 但**转写成 Python 必崩**（`TypeError: 'float' object is not callable`）。写 gd_core 新增变量前先查继承链上有没有同名方法
- `round()`/`ceil()` 返 float，不能直接 return 给 `-> int`
- 无头跑须 `--script` + `extends SceneTree` + `_init`；Godot 每脚本**只报首个** parse error（逐文件 `load` 批量暴露）
- ★ **报错行号取自「函数真正定义的脚本」**（`PoisonIvy.gd:1441` 实为 `CoreItem.gd` 的行号）→ 按「函数名 + 行号」回内核找
- Godot 遇 `Nonexistent function` 只打 `SCRIPT ERROR` 后**继续执行，退出码仍 0** → 流水线必须扫 stdout
- 控制台中文按 CP936 输出
- **冷却语义三方分歧（勿混用）**：`engine/` 与 `gd_core/` 照搬原版 `cd×randf_range(0.95,1.05)`；`simulator/` 返回固定 `cd`

## Python 侧模块
- `simulator/` = 主模拟器（tkinter GUI + 打包 exe），数据源 `assets/battle_items.json`（**多段流水线产物**，整文件重生成会抹掉后续字段 → 定点重写）
- `engine/` = 早期引擎；`core/` + `gui/` = 外挂 AI 本体；`tools/` = 逆向与生成工具；`tools/oneoff/` = **一次性侦察脚本冻结归档（31 个，进版本库）**，`output/` 是 `.gitignore`（丢了找不回）
- ★ 构建产物直接留 `dist/`，不要单独 present exe 让用户另存；打包 `PyInstaller --windowed --onefile`，覆盖前先 `Stop-Process` 杀进程
- `gd_core_py/` = gd_core 的 Python 转写（521 产物 + 10 手写）；模拟器第三内核 `--engine gd_core`（`simulator/gd_core_engine.py` 适配层）；吞吐 ≈2.8× `engine`
- `_rt.py` 垫片补齐史：`Array.shuffle()` 要 `randi()` → `_math_rng()` 由裸 `PCG32` 换成 `RandomNumberGenerator`（**实测两者随机流逐位相同**：`PCG32(s).next_u32()` 前 5 项 == `RandomNumberGenerator(s).randi()` 前 5 项，所以换法不改变随机性，只是补方法）
- ★ 手写文件（`_rt.py`/`_registry.py`/`_bootstrap.py`/`_colors.py`/`__init__.py`）**也要过语法体检**（`check_gd_py.py` 的 HANDWRITTEN ≠ 跳过体检，只是不计入产物口径）
- ★ 色表 `gd_core_py/_colors.py` 由 `tools/gen_color_names.py` **生成**（不是手写）；数据指纹 146 条 `sha256=70286c7e…`

## 本仓库的「断言纪律」（踩过多次）
- ★★ **注释/文档里的每个「N 处」都必须可现算**，工具：`tools/count_api_usage.py`（`--bare` 区分**全局内建**与**对象方法** —— 混用会得出相反结论）、`tools/survey_gd_syntax.py --verify`（断言 `gd_to_py.py` 文档里的 21 个数字，进了流水线 0 阶段）
- ★★ **断言必须双侧**：只断言「正常路径未发生 X」是不够的 —— 若那根表笔没接上，断言恒真等于没断言。范例：`run_gd_py.py` 的 `[7]` 既验「`_RANDOMIZED` 仍为 False」，又用 `CoreRng(0)` **正对照**证明它能翻成 True
- ★★★ **判据的判据：「0 命中」有两种解释 —— 「真的没有」或「扫描器坏了」，两者输出一模一样。** 凡「0 命中即通过」的判据，必须配**可证伪的正对照**（删掉一条真缺口，要求它报出来）。`tools/check_scan_gaps.py` 就是这么做的；它当场抓出扫描器**三个 bug**：`_resolve_ext` 只认 `res://Items/` 不认 `res://gd_core/`（继承链断）/ `RES_PATH_RE` 只认双引号而 `ast.unparse()` 输出**单引号** / `_GD_ASSIGN_RE` 少 `re.M`（`^` 只匹配文件首行）。三个 bug 的**共同表现都是「恒返回无」**
- ★ **误报也要修**：`@property`/`@x.setter` 不算「被遮蔽的方法」（`_rt.RandomNumberGenerator.seed` 是**防遮蔽的正当写法**）；`enum` 块与 dict-key 形态要排除（曾一次性消掉 147 处枚举成员误报）
- ★ `grep -E "Color\.White"` 会误匹配 `PieceColor.White` → **伪足迹**。搜符号后缀要带词边界/前置断言
- ★ 序列化格式里**一个字段值不得含有字段分隔符**（曾用 `|` 同时作字段分隔与 origin 键内分隔 → 整批差异被静默归成「格式不可解析」）
- ★ **不要把整个文件交给「重排/迁移」脚本**：本轮一次重排脚本漏拼一段切片，直接删掉了 `docs/gd_core_truth.md` 的整节 §10（该文件当时未提交、无副本 → 只能按上下文与权威源重建，并在文档里标注）。改结构类脚本必须**先算命中数、再核对总行数**

## Godot 内存布局（2026-07-26 活体标定，本机构建有效）
```
OS::singleton RVA=0x1eba290 → +0x1d0 main_loop(SceneTree) → +0x148 root Viewport（★+0x230 是 current_scene）
Node: parent=+0xf0, children=CowData@+0x108, name(+0x130→_Data→String@+0x10), script_instance=+0x58
GDScriptInstance: script=+0x10, members Vector<Variant>=+0x20；CowData 元素数在 _ptr-4；Variant=24B
Game = root.children[8]；成员下标 gold=72, hp=68, round=65；Node2D 局部pos=+0x270, 全局origin=+0x260；背包格 80px
物品树 Main/Player/<物品>=摆盘、Main/Shop/Storagebox=储物箱、Main/Shop/Items=商店
格坐标 = floor((物品pos − Player/Inventory pos(50,60)) / 80)；排除 SocketsNode/BagBorder/Tiles/Animations
```

## GitHub Release
- `gh` 不在 PATH：`python -c "import zipfile;zipfile.ZipFile('gh.zip').extractall('gh_tmp')"` → 用 `gh_tmp/bin/gh.exe`；凭据在 keyring（cttt-des，`repo`），**无需 PAT**
- `github.com` 主站常不可达，但 `api.github.com`/`uploads.github.com` 稳定；GitHub MCP 对 Release **只读**
- ★ 稳妥流程：`gh release create <tag> --draft` → `gh release upload <tag> --clobber <files>` → `edit --draft=false`
- 已发标签：v0.0.1 / v0.1.0 / v0.1.1 / v0.1.2

## 用户偏好（工程）
- 「**如没有则先不实现**」（底层数据未就位就不提前开发）、「**宁可少删**」（清理/重构保守）
- 要求与原版逐项对齐，做不到或不确定**宁可暂缓也不臆测**；权威源 = backpackbattles.wiki.gg + iyingdi.com + 逆向代码三方交叉
- 输出偏好：结构化表格、分步骤状态、根因分析；常一次性抛多个编号问题，期待按序逐条处理
