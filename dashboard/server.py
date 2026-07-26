"""
Web 控制台服务器 — Flask + SocketIO 实时仪表盘
"""

import os
import sys
import time
import json
import threading
import logging
from pathlib import Path
from datetime import datetime

import yaml
from flask import Flask, render_template, jsonify, request
from flask_socketio import SocketIO, emit

# 添加项目根目录到路径
sys.path.insert(0, str(Path(__file__).parent.parent))

from core.bot import BackpackBot
from core.window_manager import WindowManager
from core.paths import get_resource_dir, get_config_path

logger = logging.getLogger(__name__)

# 模板/静态文件目录（兼容 PyInstaller 打包）
_dash_dir = get_resource_dir() / "dashboard"
app = Flask(
    __name__,
    template_folder=str(_dash_dir / "templates"),
    static_folder=str(_dash_dir / "static"),
)
app.config["SECRET_KEY"] = "backpack-battles-bot"
socketio = SocketIO(app, cors_allowed_origins="*", async_mode="threading")

# 全局状态
bot: BackpackBot = None
bot_thread: threading.Thread = None
dashboard_running = False
status_update_thread: threading.Thread = None


def get_config():
    with open(get_config_path(), "r", encoding="utf-8") as f:
        return yaml.safe_load(f)


def bot_log_callback(level: str, msg: str):
    """Bot 日志 → WebSocket 推送"""
    socketio.emit("log", {
        "level": level,
        "message": msg,
        "time": datetime.now().strftime("%H:%M:%S"),
    })


# === Routes ===

@app.route("/")
def index():
    """主页面"""
    return render_template("index.html")


@app.route("/api/status")
def api_status():
    """获取当前状态"""
    if bot is None:
        return jsonify({
            "connected": False,
            "running": False,
            "state": {},
        })
    return jsonify({
        "connected": True,
        "running": bot.running,
        "paused": bot.paused,
        "step_mode": bot.step_mode,
        "state": bot.get_state(),
    })


@app.route("/api/windows")
def api_windows():
    """查找游戏窗口"""
    wm = WindowManager()
    found = wm.refresh()
    if found:
        w = wm.window
        return jsonify({
            "found": True,
            "title": w.title,
            "pid": w.pid,
            "width": w.width,
            "height": w.height,
            "rect": w.rect,
        })
    return jsonify({"found": False})


@app.route("/api/config")
def api_config():
    """获取配置"""
    return jsonify(get_config())


# === SocketIO Events ===

@socketio.on("connect")
def on_connect():
    emit("log", {
        "level": "info",
        "message": "已连接到控制台",
        "time": datetime.now().strftime("%H:%M:%S"),
    })


@socketio.on("init_bot")
def on_init_bot():
    """初始化机器人"""
    global bot
    try:
        bot = BackpackBot()
        bot.on_log(bot_log_callback)
        if bot.initialize():
            if bot.scan_memory_values():
                emit("status", {"initialized": True, "memory_scan": "ok"})
            else:
                emit("status", {"initialized": True, "memory_scan": "failed"})
            emit_state()
        else:
            emit("status", {"initialized": False, "error": "初始化失败"})
    except Exception as e:
        emit("status", {"initialized": False, "error": str(e)})


@socketio.on("start_bot")
def on_start_bot():
    """启动机器人"""
    global bot, bot_thread
    if bot is None:
        emit("log", {"level": "error", "message": "请先初始化机器人", "time": ""})
        return

    if bot.running:
        emit("log", {"level": "warning", "message": "机器人已在运行中", "time": ""})
        return

    bot.running = True
    bot.paused = False
    bot.step_mode = False
    bot._stop_event.clear()

    bot_thread = threading.Thread(target=bot.start, daemon=True)
    bot_thread.start()

    emit("status", {"running": True, "paused": False})
    emit("log", {"level": "info", "message": "▶ 机器人已启动", "time": datetime.now().strftime("%H:%M:%S")})


@socketio.on("pause_bot")
def on_pause_bot():
    """暂停/继续"""
    global bot
    if bot is None:
        return
    if bot.paused:
        bot.resume()
        emit("status", {"running": True, "paused": False})
    else:
        bot.pause()
        emit("status", {"running": True, "paused": True})


@socketio.on("stop_bot")
def on_stop_bot():
    """停止机器人"""
    global bot, bot_thread
    if bot is None:
        return
    bot.stop()
    bot_thread = None
    emit("status", {"running": False, "paused": False})
    emit("log", {"level": "info", "message": "⏹ 机器人已停止", "time": datetime.now().strftime("%H:%M:%S")})


@socketio.on("step_bot")
def on_step_bot():
    """单步执行"""
    global bot
    if bot is None:
        emit("log", {"level": "error", "message": "请先初始化机器人", "time": ""})
        return

    if not bot.running:
        bot.running = True
        bot.paused = False
        bot.step_mode = True
        t = threading.Thread(target=bot.step, daemon=True)
        t.start()
    else:
        bot.paused = False
        t = threading.Thread(target=bot.step, daemon=True)
        t.start()

    emit("status", {"running": True, "paused": True})


@socketio.on("emergency_stop")
def on_emergency_stop():
    """紧急停止"""
    global bot
    if bot is None:
        return
    bot.stop()
    if bot.actions:
        bot.actions.emergency_stop()
    emit("status", {"running": False, "paused": False})
    emit("log", {"level": "error", "message": "⚠ 紧急停止！", "time": datetime.now().strftime("%H:%M:%S")})


@socketio.on("get_state")
def on_get_state():
    """获取实时状态"""
    emit_state()


def emit_state():
    """推送完整状态到前端"""
    if bot is None:
        socketio.emit("game_state", {
            "connected": False,
            "running": False,
            "state": {},
        })
        return

    try:
        state = bot.get_state()
        socketio.emit("game_state", {
            "connected": True,
            "running": bot.running,
            "paused": bot.paused,
            "step_mode": bot.step_mode,
            "state": state,
        })
    except Exception as e:
        socketio.emit("game_state", {
            "connected": True,
            "running": bot.running,
            "paused": bot.paused,
            "error": str(e),
        })


def status_update_loop():
    """后台线程：定期推送状态更新"""
    global bot, dashboard_running
    interval = 0.5
    while dashboard_running:
        time.sleep(interval)
        if bot and bot.running:
            try:
                emit_state()
            except Exception:
                pass


def start_dashboard(host="127.0.0.1", port=8080, auto_open=True):
    """启动 Web 控制台"""
    global dashboard_running, status_update_thread

    dashboard_running = True
    status_update_thread = threading.Thread(target=status_update_loop, daemon=True)
    status_update_thread.start()

    if auto_open:
        import webbrowser
        threading.Timer(1.0, lambda: webbrowser.open(f"http://{host}:{port}")).start()

    print(f"\n{'='*50}")
    print(f"  背包乱斗 AI 控制台")
    print(f"  地址: http://{host}:{port}")
    print(f"{'='*50}\n")

    socketio.run(app, host=host, port=port, debug=False, allow_unsafe_werkzeug=True)


if __name__ == "__main__":
    import argparse
    parser = argparse.ArgumentParser(description="背包乱斗 AI Web 控制台")
    parser.add_argument("--host", default="127.0.0.1", help="监听地址")
    parser.add_argument("--port", type=int, default=8080, help="监听端口")
    parser.add_argument("--no-browser", action="store_true", help="不自动打开浏览器")
    args = parser.parse_args()

    config = get_config()
    dash_cfg = config.get("dashboard", {})
    host = args.host or dash_cfg.get("host", "127.0.0.1")
    port = args.port or dash_cfg.get("port", 8080)
    auto_open = not args.no_browser and dash_cfg.get("auto_open", True)

    start_dashboard(host, port, auto_open)
