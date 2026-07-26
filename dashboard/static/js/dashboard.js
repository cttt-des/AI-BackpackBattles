/**
 * 背包乱斗 AI 控制台 — 前端交互逻辑
 */

const socket = io();
let botRunning = false;
let botPaused = false;
let botConnected = false;

// === SocketIO 事件 ===

socket.on("connect", () => {
    console.log("已连接到服务器");
    updateStatus("connected", "已连接");
    document.getElementById("btnInit").disabled = false;
});

socket.on("disconnect", () => {
    updateStatus("disconnected", "连接断开");
    botConnected = false;
    resetUI();
});

socket.on("log", (data) => {
    addLog(data.level, data.message, data.time);
});

socket.on("status", (data) => {
    if (data.initialized !== undefined) {
        botConnected = data.initialized;
        if (data.initialized) {
            updateStatus("connected", "已初始化");
            document.getElementById("btnInit").disabled = true;
            document.getElementById("btnStart").disabled = false;
            document.getElementById("btnStep").disabled = false;
            document.getElementById("btnStop").disabled = false;
            document.getElementById("btnEmergency").disabled = false;
        } else {
            updateStatus("disconnected", "初始化失败: " + (data.error || "未知错误"));
        }
    }

    if (data.running !== undefined) {
        botRunning = data.running;
        botPaused = data.paused || false;
        updateRunningState();
    }
});

socket.on("game_state", (data) => {
    if (data.connected && data.state) {
        updateGameState(data.state);
        updateMemoryInfo(data.state);
    }
});

// === UI 更新 ===

function updateStatus(status, text) {
    const dot = document.querySelector("#statusIndicator .dot");
    const textEl = document.getElementById("statusText");
    dot.className = "dot " + status;
    textEl.textContent = text;
}

function updateRunningState() {
    const dot = document.querySelector("#statusIndicator .dot");
    if (botRunning && !botPaused) {
        dot.className = "dot connected running";
        document.getElementById("statusText").textContent = "运行中";
    } else if (botPaused) {
        dot.className = "dot connected";
        document.getElementById("statusText").textContent = "已暂停";
    }

    document.getElementById("btnStart").disabled = botRunning && !botPaused;
    document.getElementById("btnPause").disabled = !botRunning;
    document.getElementById("btnStep").disabled = botRunning && !botPaused;
    document.getElementById("btnStop").disabled = !botRunning;
    document.getElementById("btnPause").textContent = botPaused ? "▶ 继续" : "⏸ 暂停";
}

function updateGameState(state) {
    // 回合、HP、金币
    document.getElementById("roundNum").textContent = state.round || "-";
    document.getElementById("hpNum").textContent = state.hp || "-";
    document.getElementById("goldNum").textContent = state.gold != null ? state.gold : "-";

    // 状态详情
    const phaseLabel = state.phase === "shop" ? "🛒 商店阶段" : "⚔ 战斗阶段";
    const detailHtml = `
        <div class="state-row"><span class="state-label">阶段</span><span class="state-value">${phaseLabel}</span></div>
        <div class="state-row"><span class="state-label">回合</span><span class="state-value">${state.round} / ${state.max_rounds}</span></div>
        <div class="state-row"><span class="state-label">生命</span><span class="state-value hp">${state.hp} / ${state.max_hp}</span></div>
        <div class="state-row"><span class="state-label">金币</span><span class="state-value gold">${state.gold}</span></div>
        <div class="state-row"><span class="state-label">背包物品</span><span class="state-value">${state.backpack_items || 0}</span></div>
        <div class="state-row"><span class="state-label">储存箱</span><span class="state-value">${state.storage_items || 0}</span></div>
        <div class="state-row"><span class="state-label">商店物品</span><span class="state-value">${state.shop_items || 0}</span></div>
        <div class="state-row"><span class="state-label">总持有</span><span class="state-value">${state.total_owned || 0}</span></div>
    `;
    document.getElementById("stateDetail").innerHTML = detailHtml;

    // 背包网格
    if (state.backpack) {
        updateBackpackGrid(state.backpack);
    }

    // 储存箱物品
    const storage = state.storage || [];
    if (storage.length > 0) {
        document.getElementById("storageItems").innerHTML = storage
            .map(i => `<span class="storage-item">${i.name}</span>`)
            .join("");
    } else {
        document.getElementById("storageItems").innerHTML = '<p class="placeholder">空</p>';
    }

    // 最近操作
    if (state.recent_actions && state.recent_actions.length > 0) {
        state.recent_actions.forEach(a => {
            addLog("info", a, "");
        });
    }
}

function updateMemoryInfo(state) {
    const mem = state.memory;
    if (!mem) {
        document.getElementById("memoryInfo").style.display = "none";
        return;
    }
    document.getElementById("memoryInfo").style.display = "block";
    document.getElementById("memoryAddrs").innerHTML = `
        <div class="memory-addr"><span class="addr-label">金币 (raw)</span><span class="addr-value">${mem.gold_raw != null ? mem.gold_raw : "N/A"}</span></div>
        <div class="memory-addr"><span class="addr-label">HP (raw)</span><span class="addr-value">${mem.hp_raw != null ? mem.hp_raw : "N/A"}</span></div>
        <div class="memory-addr"><span class="addr-label">回合 (raw)</span><span class="addr-value">${mem.round_raw != null ? mem.round_raw : "N/A"}</span></div>
    `;
}

function updateBackpackGrid(items) {
    const grid = document.getElementById("backpackGrid");
    let html = "";

    // 创建 9x7 网格
    for (let r = 0; r < 9; r++) {
        html += "<tr>";
        for (let c = 0; c < 7; c++) {
            html += `<td id="cell-${r}-${c}"></td>`;
        }
        html += "</tr>";
    }
    grid.innerHTML = html;

    // 标记已占用的格子
    let occupiedCount = 0;
    items.forEach(item => {
        const catClass = item.category || "";
        for (let dr = 0; dr < item.height; dr++) {
            for (let dc = 0; dc < item.width; dc++) {
                const r = item.row + dr;
                const c = item.col + dc;
                if (r < 9 && c < 7) {
                    const cell = document.getElementById(`cell-${r}-${c}`);
                    if (cell) {
                        cell.className = `occupied ${catClass}`;
                        // 只在物品左上角显示名字
                        if (dr === 0 && dc === 0) {
                            cell.textContent = item.name.substring(0, 4);
                        }
                        occupiedCount++;
                    }
                }
            }
        }
    });

    document.getElementById("gridStats").textContent =
        `物品: ${items.length} | 占用: ${occupiedCount} | 空格: ${63 - occupiedCount}`;
}

// === 日志 ===

const MAX_LOG_ENTRIES = 200;

function addLog(level, msg, time) {
    const container = document.getElementById("logContainer");
    const entry = document.createElement("div");
    entry.className = `log-entry ${level}`;
    entry.innerHTML = `
        <span class="log-time">${time}</span>
        <span class="log-msg">${escapeHtml(msg)}</span>
    `;

    container.appendChild(entry);

    // 限制日志条数
    while (container.children.length > MAX_LOG_ENTRIES) {
        container.removeChild(container.firstChild);
    }

    // 自动滚动到底部
    container.scrollTop = container.scrollHeight;
}

function escapeHtml(text) {
    const div = document.createElement("div");
    div.textContent = text;
    return div.innerHTML;
}

// === 按钮操作 ===

function initBot() {
    document.getElementById("btnInit").disabled = true;
    document.getElementById("btnStart").disabled = true;
    addLog("info", "正在初始化机器人...", getTime());
    socket.emit("init_bot");
}

function startBot() {
    addLog("info", "正在启动机器人...", getTime());
    socket.emit("start_bot");
}

function pauseBot() {
    socket.emit("pause_bot");
}

function stopBot() {
    addLog("info", "正在停止机器人...", getTime());
    socket.emit("stop_bot");
}

function stepBot() {
    addLog("info", "单步执行...", getTime());
    socket.emit("step_bot");
}

function emergencyStop() {
    if (confirm("确认紧急停止？这将立即终止所有操作！")) {
        socket.emit("emergency_stop");
    }
}

function resetUI() {
    botRunning = false;
    botPaused = false;
    document.getElementById("btnInit").disabled = false;
    document.getElementById("btnStart").disabled = true;
    document.getElementById("btnPause").disabled = true;
    document.getElementById("btnStep").disabled = true;
    document.getElementById("btnStop").disabled = true;
    document.getElementById("btnEmergency").disabled = true;
    document.getElementById("btnPause").textContent = "⏸ 暂停";

    document.getElementById("roundNum").textContent = "-";
    document.getElementById("hpNum").textContent = "-";
    document.getElementById("goldNum").textContent = "-";
    document.getElementById("stateDetail").innerHTML = '<p class="placeholder">等待初始化...</p>';
    document.getElementById("storageItems").innerHTML = '<p class="placeholder">空</p>';
    document.getElementById("memoryInfo").style.display = "none";
}

function getTime() {
    return new Date().toTimeString().substring(0, 8);
}

// === 键盘快捷键 ===
document.addEventListener("keydown", (e) => {
    if (e.key === "Escape") {
        emergencyStop();
    } else if (e.key === " " && !e.target.closest("input,textarea")) {
        e.preventDefault();
        if (botRunning && !botPaused) {
            pauseBot();
        } else if (botRunning && botPaused) {
            startBot();
        }
    }
});

// === 定期刷新 ===
setInterval(() => {
    if (botConnected) {
        socket.emit("get_state");
    }
}, 2000);
