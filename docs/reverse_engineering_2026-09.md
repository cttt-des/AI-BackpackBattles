# Backpack Battles 逆向工程重做报告（2026-09-18）

## 结论

以官方原版 `Backpack Battles/BackpackBattles.pck.bak`（clean v1.1.7，Godot 3.6.0）为真值完成全量重逆向：

| 项 | 旧轮（2026-08） | 本轮（2026-09-18） |
|----|----------------|-------------------|
| 解包 | `extracted/` 2852 文件，**缺 6530 个**（全部 .import 编译资源：.stex 贴图/.oggstr 音频/材质/翻译/字体等） | **9377/9377 全部提取，逐条目 MD5 校验零缺失** |
| 脚本解密 | 820 .gde（密钥 hook 获取） | **820/820 全部解密**（GDSC 魔数 + 内嵌 MD5 全部通过） |
| CSV 解密 | ItemData_e.csv 未解（旧 csv_key 记录有误） | **已解密**（518 物品行，MD5 与 GDEC 头吻合），覆盖至 `decompiled_full/Sheets/CSV/ItemData_e.csv` |
| 反编译 | 820 .gd，**但源码被第三方 Mod 污染** | **820 .gd + 1028 .tscn + 3817 资源转换零失败，干净官方 v1.1.7** |
| 模拟器对账 | runtime_failures = 3 | **runtime_failures = 0**（干净源码下更优） |

## 重大发现：旧解包源码被 Mod 污染

旧 `decompiled_full/`（2026-08-18）来自当时被 **bpb_enhance Mod（v1.1.8）** 覆盖过的游戏包，33 个文件含 Mod 注入代码：

- `Core/Game.gd`：Mod 服务器 URL（8.153.197.44）、MOD_API、版本 1.1.8
- `Core/Inventory.gd`：`normalizeSymmetricItems()`（胡萝卜/剪刀对称物品归一化）等 Mod 改动
- `Items/Item.gd`：Item Library "FREE ADD" 输入处理
- `Utility/DataValidator.gd`：Mod 用于绕过资源完整性校验的改动
- 其余为 Lobbies/BuildHistory/Tooltip 等 Mod 联机功能

本轮全部替换为干净官方源码。与战斗相关的 787 个脚本两版字节一致，模拟器战斗逻辑不受影响（验收链全过）。

## 加密方案与密钥

GDEC 容器（脚本与 CSV 相同）：`[4 "GDEC"][4 version=1][16 MD5(明文)][8 LE 明文长度][AES-256-ECB 密文]`

| 密钥 | 值（hex） | 验证 |
|------|-----------|------|
| 脚本密钥 | `8671424952511006d39f4c9e918f821391e2b06a80d946d693fb8757154ce849` | 820 个 .gde 全部解密成功 |
| CSV 密钥 | `0001020304c6060708090a0bc30d0e0f101112131415161718191a1b1c1d1e1f` | 80801 字节明文 MD5 与头部一致 |

- CSV 密钥 = 0x00..0x1F 字节流在 **0 起算第 5、12 字节** patch 为 0xC6、0xC3（旧记录"第 5、13 字节"为 1 起算表述，且 csv_key.txt 字面值才是对的）
- 当前反编译源码 `Sheets/ItemBook.gd` 中 `sheetKey` 只是朴素的 0..31（`for i in 32: append(i)`）——出货 CSV 是旧版加密工具用 patch 过的密钥生成的，故与现源码不一致

## 内存扫描过程（密钥取证）

本机游戏进程（含 Steam 正在运行的实例）实测：

1. **AES-256 密钥扩展表扫描**（Rcon 递推特征，numpy 向量化，扫 3092 MB）：0 命中——密钥扩展用完即释放，堆被复用
2. **主模块镜像暴力扫描**（33.6 MB 全部 32 字节窗口 × ECB 试解 → GDSC 魔数）：0 命中——密钥不以明文烘焙在镜像中
3. **全内存历史密钥字节搜索**：0 命中——长时间运行的进程已不含密钥材料

结论：该定制 Godot 构建（GodotSteam）的密钥仅在**启动加载脚本的一瞬间**于堆上重构，随后释放。取证方法：`tools/inject_gdec_hook.py`——正常启动 `--headless` 实例 → 在前 5s 内以 20ms 间隔快速注入 `gdec_hook.dll` → 趁启动解密风暴期间（~3s 内 50+ 次调用）捕获 r8 密钥候选 → 结束进程 → 离线 AES-256-ECB + GDSC + MD5 验证候选。

**实测结果：注入延迟 29ms 时捕到 50 个候选，脚本密钥 td 路径（`this+0x20` 指针链）命中，GDSC+MD5 双重验证通过。**

> 注：两处安装（工作区副本与 Steam 目录）的 `BackpackBattles.pck` 均为 2026-09-17 桥接注入补丁包（原版都以 `.pck.bak` 保存）。补丁包沿用原脚本密钥（脚本条目 MD5 与原版一致）。

## 工具链（本轮新增/修复）

| 工具 | 作用 |
|------|------|
| `tools/pck_inspect.py` | 解析 pck 目录（版本/条目/MD5），输出清单供对账 |
| `tools/pck_full_extract.py` | 全量提取（9377 条目 + 逐条目 MD5 校验，零跳过） |
| `tools/mem_key_scan.py` | AES-256 密钥扩展表内存扫描（mbedtls LE 递推特征，含自测） |
| `tools/mem_rawkey_scan.py` / `mem_key_scan_focused.py` | 原始密钥窗口暴力扫描（全内存 / 主模块聚焦） |
| `tools/launch_fresh_and_scan.py` | 新实例挂起 + 密钥取证一条龙（本轮密钥扫描的正解） |
| `tools/gdre/gdre_tools.exe` | GDSDECOMP v2.6.4：`--recover --key=<脚本密钥>` 全项目恢复 |

## 复现

```bash
# 1. 全量解包（MD5 校验）
python tools/pck_full_extract.py

# 2. 全项目恢复（脚本反编译 + 资源转文本）
tools/gdre/gdre_tools.exe --headless \
  --recover="Backpack Battles/BackpackBattles.pck.bak" \
  --key=8671424952511006d39f4c9e918f821391e2b06a80d946d693fb8757154ce849 \
  --output=decompiled_full

# 3. 解密加密 CSV（用 csv_key.txt）
python tools/decrypt_gde.py --key-file tools/csv_key.txt extracted/Sheets/CSV/ItemData_e.csv

# 4. 密钥取证（可选，需游戏可启动）
python tools/launch_fresh_and_scan.py

## Hook 动态确认（2026-09-18 追加）

inject_gdec_hook.py 用以下方式直接验证了密钥候选：
- 注入 `tools/gdec_hook.dll`（`arm_hook()` 导出，CreateRemoteThread + LoadLibraryW）
- DLL 挂载 x64 绝对跳转 hook（mov rax,imm64; jmp rax，15 字节）至 RVA 0x1621820
- Hook 入口在游戏启动解密风暴期间被触发 50+ 次（calls=50，stat 文件记录）
- 从 r8（Vector\<uint8_t\> 引用）读取 32 字节候选，`safe_read` + VirtualQuery 保护
- 日志文件：`C:/Users/Windows/AppData/Local/Temp/bp_hook_candidates.log`
- 离线 AES-256-ECB 试解密 + GDSC 魔数 + 完整明文 MD5 验证候选

**动态确认结果（2026-09-18）：**

| 密钥 | Hook 捕获值 | GDSC+MD5 验证 | GDRE 反编译 |
|------|-------------|---------------|-------------|
| 脚本密钥 | `8671424952511006d39f4c9e918f821391e2b06a80d946d693fb8757154ce849` | ✓ 820/820 .gde | ✓ 820/820 .gd |
| CSV 密钥 | （启动风暴期间无 CSV 解密，候选集为空） | ✓ MD5 吻合 | — |

注：CSV 密钥由历史已知密钥（`0001020304c606...`）离线爆破确认，与 GDEC 头 MD5 吻合。

## 全量验收

```
extracted/         total=9377
  .gde  total=820   GDSC+MD5  ok=820  bad=0
  .csv  GDEC ok=1   MD5 吻合（plain_len=80801，明文为 CSV 格式）
  .gdc  total=0
decompiled_full/  .gd=820
```
