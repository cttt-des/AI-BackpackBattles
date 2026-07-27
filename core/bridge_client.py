"""
桥接客户端 —— 通过 TCP 连接游戏内桥接 GDScript，获取运行时数据。

桥接脚本（bpb_ai_bridge.gd）注入到游戏 PCK 后，在游戏进程内启动
一个 TCP 服务器（默认端口 19527）。本客户端从外部 Python 进程
连接到该服务器，发送 JSON 命令获取联动/价格等数据。

使用桥接 vs 直读内存：
- 桥接可访问 GDScript 运行时成员（按名称读取属性）
- 直读内存只能通过偏移量读取已知结构
- 桥接优先：若连接成功则使用桥接，否则回退到内存读取
"""
from __future__ import annotations

import json
import logging
import socket
import time
from typing import Any, Dict, List, Optional

logger = logging.getLogger(__name__)

BRIDGE_HOST = "127.0.0.1"
BRIDGE_PORT = 19527
CONNECT_TIMEOUT = 2.0
RECV_TIMEOUT = 5.0


class BridgeClient:
    """游戏内桥接 TCP 客户端。"""

    def __init__(self, host: str = BRIDGE_HOST, port: int = BRIDGE_PORT):
        self.host = host
        self.port = port
        self.sock: Optional[socket.socket] = None
        self._buf = b""

    # ─── 连接管理 ───

    def connect(self) -> bool:
        """连接到游戏内桥接服务器。"""
        try:
            self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.sock.settimeout(CONNECT_TIMEOUT)
            self.sock.connect((self.host, self.port))
            self.sock.settimeout(RECV_TIMEOUT)
            logger.info("已连接到桥接服务器 %s:%d", self.host, self.port)
            return True
        except (socket.timeout, ConnectionRefusedError, OSError) as e:
            logger.debug("桥接连接失败: %s", e)
            self.sock = None
            return False

    def disconnect(self):
        if self.sock:
            try:
                self.sock.close()
            except Exception:
                pass
            self.sock = None

    @property
    def connected(self) -> bool:
        return self.sock is not None

    def ensure_connected(self, max_retries: int = 3, retry_delay: float = 0.5) -> bool:
        """确保连接（带重试）。"""
        for i in range(max_retries):
            if self.connected:
                return True
            if self.connect():
                return True
            if i < max_retries - 1:
                time.sleep(retry_delay)
        return False

    # ─── 发送 / 接收 ───

    def send_command(self, cmd: str, args: dict = None) -> Optional[dict]:
        """发送命令并接收响应。"""
        if not self.connected:
            logger.warning("桥接未连接")
            return None

        payload = {"cmd": cmd, "args": args or {}}
        msg = json.dumps(payload, ensure_ascii=False) + "\n"

        try:
            self.sock.sendall(msg.encode("utf-8"))
            return self._recv_response()
        except (socket.timeout, OSError, BrokenPipeError) as e:
            logger.warning("桥接通讯失败: %s", e)
            self.disconnect()
            return None

    def _recv_response(self) -> Optional[dict]:
        """接收一行 JSON 响应。"""
        while b"\n" not in self._buf:
            try:
                chunk = self.sock.recv(65536)
                if not chunk:
                    self.disconnect()
                    return None
                self._buf += chunk
            except socket.timeout:
                logger.warning("桥接接收超时")
                return None
            except OSError as e:
                logger.warning("桥接接收失败: %s", e)
                self.disconnect()
                return None

        line, self._buf = self._buf.split(b"\n", 1)
        try:
            return json.loads(line.decode("utf-8"))
        except json.JSONDecodeError:
            logger.warning("桥接响应非 JSON: %s", line[:200])
            return None

    # ─── 业务命令 ───

    def ping(self) -> bool:
        """检查桥接是否存活。"""
        resp = self.send_command("ping")
        return resp is not None and resp.get("ok") and resp.get("data", {}).get("pong")

    def get_full_game_state(self) -> Optional[dict]:
        """获取完整游戏状态（含联动 + 价格）。"""
        return self.send_command("get_full_game_state")

    def get_item_details(self, zone: str = "all") -> Optional[dict]:
        """获取物品详细属性（按区域）。"""
        return self.send_command("get_item_details", {"zone": zone})

    def get_shop_offers(self) -> Optional[dict]:
        """获取商店报价与物品价格。"""
        return self.send_command("get_shop_offers")

    def get_backpack_items_full(self) -> Optional[dict]:
        """获取背包物品完整属性。"""
        return self.send_command("get_backpack_items_full")

    def get_connector_data(self, item_path: str) -> Optional[dict]:
        """获取指定物品的连接器数据。"""
        return self.send_command("get_connector_data", {"item_path": item_path})

    def get_item_price(self, item_path: str) -> Optional[dict]:
        """获取指定物品的价格。"""
        return self.send_command("get_item_price", {"item_path": item_path})

    def scan_tree(self, max_depth: int = 3) -> Optional[dict]:
        """扫描场景树。"""
        return self.send_command("scan_tree")

    def scan_autoloads(self) -> Optional[dict]:
        """扫描自动加载的单例。"""
        return self.send_command("scan_autoloads")

    def get_node_properties(self, path: str) -> Optional[dict]:
        """获取指定路径节点的所有属性。"""
        return self.send_command("get_node_properties", {"path": path})

    def get_property(self, path: str, prop: str) -> Optional[dict]:
        """获取指定节点单个属性的值。"""
        return self.send_command("get_property", {"path": path, "property": prop})

    def get_game_state(self) -> Optional[dict]:
        """获取基本游戏状态。"""
        return self.send_command("get_game_state")

    # ─── 数据提取辅助 ───

    def extract_prices(self, shop_data: dict = None) -> Dict[str, int]:
        """从商店数据中提取物品价格。"""
        prices = {}
        if shop_data is None:
            resp = self.get_shop_offers()
            if resp:
                shop_data = resp.get("data", {})
        if shop_data:
            for item in shop_data.get("shop_items", []):
                props = item.get("properties", {})
                name = item.get("name", "?")
                # 尝试各种可能的价格属性名
                for key in ["price", "item_price", "base_price", "gold_cost", "cost",
                            "sell_price", "buy_price", "member_price"]:
                    val = props.get(key)
                    if val is not None and isinstance(val, (int, float)) and 0 < val < 100000:
                        prices[name] = int(val)
                        break
        return prices

    def extract_synergy(self, items_data: dict = None) -> Dict[str, dict]:
        """从物品数据中提取联动/连接器信息。"""
        synergy = {}
        if items_data is None:
            resp = self.get_item_details()
            if resp:
                items_data = resp.get("data", {})

        for zone in ("backpack", "shop", "storage"):
            for item in items_data.get(zone, []):
                name = item.get("name", "?")
                props = item.get("properties", {})
                connectors = []

                # 检查连接器相关属性
                for key in props:
                    if any(k in key.lower() for k in ("connector", "synergy", "adjacent",
                                                       "connect", "socket", "gem")):
                        connectors.append({key: props[key]})

                # 检查子节点连接器
                for child_key in props:
                    child = props.get(child_key)
                    if isinstance(child, dict):
                        cname = child.get("class", "")
                        if "Connector" in cname:
                            connectors.append({
                                "type": cname,
                                "position": child.get("position"),
                                "node_path": props.get(child_key + "_path", ""),
                            })

                synergy[name] = {
                    "zone": zone,
                    "position": item.get("position"),
                    "rotation": item.get("rotation"),
                    "connectors": connectors,
                    "properties": {k: v for k, v in props.items()
                                   if not isinstance(v, (dict, list))},
                }
        return synergy


# 便捷单例
_default_client: Optional[BridgeClient] = None


def get_bridge() -> BridgeClient:
    global _default_client
    if _default_client is None:
        _default_client = BridgeClient()
    return _default_client


def is_available() -> bool:
    """检查桥接是否可用（快速连接检查）。"""
    c = get_bridge()
    if c.connected:
        return c.ping()
    if c.connect():
        alive = c.ping()
        if not alive:
            c.disconnect()
        return alive
    return False
