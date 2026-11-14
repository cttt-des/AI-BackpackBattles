### 4.5 受控试错协议（G 类每题开工前必读）

```
step 0  备份：git commit && git push origin master     ← 远端必须有，本地提交不算备份
step 1  隔离：git switch -c try/<名称>   或   git worktree add ../try-<名称>
step 2  实现（只改实现；不许改判据/语料/夹具）
step 3  偏移检测（按顺序，红了就停在这一步）：
          python -X utf8 tools/check_seed_dual.py      # 秒级
          verify_oracle --cases <REG9>                 # 1 分钟
          verify_oracle --cases <60 场>                # 1 分钟
          verify_oracle --force（1690）                # 20 分钟，必须回读 match 分布
step 4  偏移 → 修实现（不是修判据）。时间盒：
          ≤2 轮修复尝试 / 每轮 ≤2 小时；超时即进入 step 5
          常见偏移源：求值次序、浮点结合律、dict 迭代序、RNG 抽取代数
step 5  修不动 → git switch master；把「试过什么 + 偏移在哪 + 卡在哪」记入 §4.7
step 6  成功 → 合入 + 收益实测（mean_ms 交错 A/B，n≥40，≥3 轮，报 3σ）
```

> **红线不在此列**：G5（GPU 浮点归约）、惰性触发（改帧内调用集合）、`/fp:fast`、
> `f32` 降精度 —— 这些不是「有风险所以不敢做」，是**必然破坏可检测的语义闸**，
> 试错的期望值为负。区分「有风险」与「确定不可行」，是这份协议成立的前提。

### 4.6 试错记录（失败也留证据，避免重复踩）

| 方向 | 尝试了什么 | 结果 | 卡在哪 |
|---|---|---|---|
| （暂无） | — | — | — |
