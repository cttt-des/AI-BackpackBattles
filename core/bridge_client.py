"""
TCP client for communicating with the Bridge autoload inside Godot.
"""
import socket
import json
import time
import logging

logger = logging.getLogger(__name__)


class BridgeClient:
    """Connects to the Backpack Battles Bridge TCP server inside the game."""

    def __init__(self, host: str = "127.0.0.1", port: int = 19527, timeout: float = 5.0):
        self.host = host
        self.port = port
        self.timeout = timeout
        self._sock: socket.socket | None = None
        self._buffer: bytes = b""

    def connect(self) -> bool:
        """Connect to the bridge server. Returns True on success."""
        try:
            self._sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self._sock.settimeout(self.timeout)
            self._sock.connect((self.host, self.port))
            # Read hello message
            hello = self._recv_json()
            if hello and hello.get("type") == "hello":
                logger.info(f"Connected to Bridge: {hello.get('msg', '')}")
                return True
            return False
        except (ConnectionRefusedError, socket.timeout, OSError) as e:
            logger.error(f"Failed to connect to Bridge: {e}")
            return False

    def disconnect(self):
        """Disconnect from the bridge."""
        if self._sock:
            try:
                self._sock.close()
            except Exception:
                pass
            self._sock = None

    def is_connected(self) -> bool:
        return self._sock is not None

    def send_command(self, cmd: str, args: dict = None) -> dict:
        """Send a command and get the response.
        
        Returns the response data dict, or {"ok": False, "error": str} on failure.
        """
        if not self._sock:
            return {"ok": False, "error": "Not connected"}
        
        msg = {"cmd": cmd, "args": args or {}}
        try:
            self._send_json(msg)
            resp = self._recv_json()
            return resp
        except (socket.timeout, ConnectionError, OSError) as e:
            logger.error(f"Command '{cmd}' failed: {e}")
            return {"ok": False, "error": str(e)}

    def ping(self) -> bool:
        """Check if bridge is responsive."""
        resp = self.send_command("ping")
        return resp.get("ok", False)

    def get_game_state(self) -> dict:
        """Get full game state from the bridge."""
        resp = self.send_command("get_game_state")
        return resp.get("data", {}) if resp.get("ok") else {}

    def get_shop_state(self) -> dict:
        """Get shop state (offers, storage, sellbox, etc.)."""
        resp = self.send_command("get_shop_state")
        return resp.get("data", {}) if resp.get("ok") else {}

    def get_inventory_state(self) -> dict:
        """Get player inventory/backpack state."""
        resp = self.send_command("get_inventory_state")
        return resp.get("data", {}) if resp.get("ok") else {}

    def get_player_state(self) -> dict:
        """Get player state (health, gold, round, etc.)."""
        resp = self.send_command("get_player_state")
        return resp.get("data", {}) if resp.get("ok") else {}

    def scan_tree(self) -> dict:
        """Scan the entire scene tree."""
        resp = self.send_command("scan_tree")
        return resp.get("data", {}) if resp.get("ok") else {}

    def scan_autoloads(self) -> dict:
        """Scan autoload singletons."""
        resp = self.send_command("scan_autoloads")
        return resp.get("data", {}) if resp.get("ok") else {}

    def get_node_properties(self, path: str) -> dict:
        """Get properties of a node."""
        resp = self.send_command("get_node_properties", {"path": path})
        return resp.get("data", {}) if resp.get("ok") else {}

    def get_node_methods(self, path: str) -> dict:
        """Get methods of a node."""
        resp = self.send_command("get_node_methods", {"path": path})
        return resp.get("data", {}) if resp.get("ok") else {}

    def get_property(self, path: str, prop: str):
        """Get a specific property value."""
        resp = self.send_command("get_property", {"path": path, "property": prop})
        return resp.get("data", {}).get("value") if resp.get("ok") else None

    def set_property(self, path: str, prop: str, value) -> bool:
        """Set a property value."""
        resp = self.send_command("set_property", {"path": path, "property": prop, "value": value})
        return resp.get("ok", False)

    def call_method(self, path: str, method: str, args: list = None):
        """Call a method on a node."""
        resp = self.send_command("call_method", {"path": path, "method": method, "args": args or []})
        return resp.get("data", {}).get("result") if resp.get("ok") else None

    def simulate_click(self, x: float, y: float) -> bool:
        """Simulate a mouse click at (x, y)."""
        resp = self.send_command("simulate_click", {"x": x, "y": y})
        return resp.get("ok", False)

    def simulate_drag(self, from_x: float, from_y: float, to_x: float, to_y: float) -> bool:
        """Simulate a mouse drag from (from_x, from_y) to (to_x, to_y)."""
        resp = self.send_command("simulate_drag", {
            "from_x": from_x, "from_y": from_y,
            "to_x": to_x, "to_y": to_y
        })
        return resp.get("ok", False)

    def simulate_key(self, key: str, pressed: bool = True) -> bool:
        """Simulate a key press/release."""
        resp = self.send_command("simulate_key", {"key": key, "pressed": pressed})
        return resp.get("ok", False)

    def find_node(self, name: str) -> list:
        """Find nodes by name."""
        resp = self.send_command("find_node", {"name": name})
        return resp.get("data", {}).get("matches", []) if resp.get("ok") else []

    def get_children(self, path: str) -> list:
        """Get children of a node."""
        resp = self.send_command("get_children", {"path": path})
        return resp.get("data", {}).get("children", []) if resp.get("ok") else []

    def _send_json(self, data: dict):
        """Send a JSON message (newline-delimited)."""
        text = json.dumps(data) + "\n"
        self._sock.sendall(text.encode('utf-8'))

    def _recv_json(self) -> dict | None:
        """Receive a JSON message (newline-delimited)."""
        while b"\n" not in self._buffer:
            chunk = self._sock.recv(4096)
            if not chunk:
                return None
            self._buffer += chunk
        
        line, self._buffer = self._buffer.split(b"\n", 1)
        return json.loads(line.decode('utf-8'))
