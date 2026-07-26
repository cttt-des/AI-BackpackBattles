"""
进程内存读取器 — 通过 Windows API 读取游戏进程内存中的关键数值
无需修改游戏文件，纯外置方式运行
"""

import ctypes
import ctypes.wintypes
import logging
import struct
from typing import Optional, List, Tuple
from dataclasses import dataclass

logger = logging.getLogger(__name__)

# Windows API 常量
PROCESS_VM_READ = 0x0010
PROCESS_QUERY_INFORMATION = 0x0400
PROCESS_VM_OPERATION = 0x0008
MEM_COMMIT = 0x1000
PAGE_READWRITE = 0x04
PAGE_READONLY = 0x02

kernel32 = ctypes.windll.kernel32


# --- 64 位地址安全的 API 原型声明（避免地址被截断为 32 位） ---
class MEMORY_BASIC_INFORMATION(ctypes.Structure):
    _fields_ = [
        ("BaseAddress", ctypes.c_void_p),
        ("AllocationBase", ctypes.c_void_p),
        ("AllocationProtect", ctypes.wintypes.DWORD),
        ("__alignment1", ctypes.wintypes.DWORD),
        ("RegionSize", ctypes.c_size_t),
        ("State", ctypes.wintypes.DWORD),
        ("Protect", ctypes.wintypes.DWORD),
        ("Type", ctypes.wintypes.DWORD),
        ("__alignment2", ctypes.wintypes.DWORD),
    ]


kernel32.OpenProcess.argtypes = [ctypes.wintypes.DWORD, ctypes.wintypes.BOOL, ctypes.wintypes.DWORD]
kernel32.OpenProcess.restype = ctypes.wintypes.HANDLE

kernel32.ReadProcessMemory.argtypes = [
    ctypes.wintypes.HANDLE, ctypes.c_void_p, ctypes.c_void_p,
    ctypes.c_size_t, ctypes.POINTER(ctypes.c_size_t),
]
kernel32.ReadProcessMemory.restype = ctypes.wintypes.BOOL

kernel32.VirtualQueryEx.argtypes = [
    ctypes.wintypes.HANDLE, ctypes.c_void_p,
    ctypes.POINTER(MEMORY_BASIC_INFORMATION), ctypes.c_size_t,
]
kernel32.VirtualQueryEx.restype = ctypes.c_size_t

# EnumProcessModules 在现代 Windows 上从 Psapi 迁移到 kernel32.dll 后，
# 导出名变为 K32EnumProcessModules；旧名 EnumProcessModules 只是转发别名，
# ctypes 用 GetProcAddress 按名查找会失败，因此需按候选名依次尝试。
try:
    _EnumProcessModules = kernel32.EnumProcessModules
except AttributeError:
    try:
        _EnumProcessModules = kernel32.K32EnumProcessModules
    except AttributeError:
        _psapi = ctypes.WinDLL('psapi')
        _EnumProcessModules = _psapi.EnumProcessModules

_EnumProcessModules.argtypes = [
    ctypes.wintypes.HANDLE,
    ctypes.POINTER(ctypes.c_void_p),
    ctypes.wintypes.DWORD,
    ctypes.POINTER(ctypes.wintypes.DWORD),
]
_EnumProcessModules.restype = ctypes.wintypes.BOOL

kernel32.CloseHandle.argtypes = [ctypes.wintypes.HANDLE]
kernel32.CloseHandle.restype = ctypes.wintypes.BOOL


@dataclass
class MemoryRegion:
    """内存区域"""
    base: int
    size: int
    state: int
    protect: int
    type: int


class MemoryReader:
    """游戏进程内存读取器"""

    def __init__(self, process_id: int):
        self.pid = process_id
        self.handle: Optional[int] = None
        self.module_base: int = 0
        self._open()
        self._resolve_module_base()

    def _open(self):
        """打开进程句柄"""
        self.handle = kernel32.OpenProcess(
            PROCESS_VM_READ | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION,
            False,
            self.pid
        )
        if not self.handle:
            raise OSError(f"无法打开进程 PID={self.pid}，请以管理员权限运行")

    def _resolve_module_base(self):
        """获取主模块（游戏 exe）基址，供结构性读取计算固定 RVA。"""
        try:
            MAX = 1024
            arr = (ctypes.c_void_p * MAX)()
            # 注意：EnumProcessModules 第二参类型是 POINTER(c_void_p)，
            # 必须传数组本身（或 cast 后的指针），不能用 byref(数组)（会被视为
            # “指向数组的指针”，与声明不符而抛 TypeError）。
            pmods = ctypes.cast(arr, ctypes.POINTER(ctypes.c_void_p))
            needed = ctypes.c_uint()
            ok = _EnumProcessModules(
                self.handle, pmods,
                ctypes.sizeof(arr), ctypes.byref(needed),
            )
            if ok:
                count = needed.value // ctypes.sizeof(ctypes.c_void_p)
                if count > 0:
                    self.module_base = arr[0]
                    return
        except Exception as e:  # noqa: BLE001
            logger.warning("枚举模块基址失败: %s", e)
        self.module_base = 0

    def close(self):
        if self.handle:
            kernel32.CloseHandle(self.handle)
            self.handle = None

    def read(self, address: int, size: int) -> Optional[bytes]:
        """读取指定地址的内存"""
        buf = ctypes.create_string_buffer(size)
        bytes_read = ctypes.c_size_t(0)
        if kernel32.ReadProcessMemory(self.handle, address, buf, size, ctypes.byref(bytes_read)):
            return buf.raw[:bytes_read.value]
        return None

    def read_int32(self, address: int) -> Optional[int]:
        data = self.read(address, 4)
        return struct.unpack('<i', data)[0] if data else None

    def read_float(self, address: int) -> Optional[float]:
        data = self.read(address, 4)
        return struct.unpack('<f', data)[0] if data else None

    def read_int64(self, address: int) -> Optional[int]:
        data = self.read(address, 8)
        return struct.unpack('<q', data)[0] if data else None

    def read_string(self, address: int, max_len: int = 256) -> Optional[str]:
        """读取以 null 结尾的 UTF-8 字符串"""
        data = self.read(address, max_len)
        if not data:
            return None
        null_pos = data.find(b'\x00')
        if null_pos >= 0:
            data = data[:null_pos]
        try:
            return data.decode('utf-8', errors='replace')
        except Exception:
            return None

    def enumerate_regions(self) -> List[MemoryRegion]:
        """枚举进程的可读内存区域"""
        regions = []
        addr = 0
        mbi = MEMORY_BASIC_INFORMATION()
        MAX_ADDR = 0x7FFFFFFFFFFF  # 用户态地址上限

        while addr < MAX_ADDR:
            result = kernel32.VirtualQueryEx(
                self.handle, ctypes.c_void_p(addr), ctypes.byref(mbi),
                ctypes.sizeof(mbi),
            )
            if result == 0:
                break

            # BaseAddress 为 0 时 c_void_p.value 返回 None，需回退到查询地址
            base = mbi.BaseAddress if mbi.BaseAddress is not None else addr
            size = mbi.RegionSize or 0
            state = mbi.State
            protect = mbi.Protect
            mem_type = mbi.Type

            if size <= 0:
                # 防止死循环
                addr += 0x1000
                continue

            if state == MEM_COMMIT and (protect & (PAGE_READWRITE | PAGE_READONLY)):
                regions.append(MemoryRegion(base, size, state, protect, mem_type))

            addr = base + size

        return regions

    def scan_int32(self, value: int, max_results: int = 100) -> List[int]:
        """扫描进程内存中匹配的 int32 值"""
        results = []
        target = struct.pack('<i', value)

        for region in self.enumerate_regions():
            if region.size > 512 * 1024 * 1024:  # 跳过大于 512MB 的区域
                continue
            data = self.read(region.base, region.size)
            if not data:
                continue
            pos = 0
            while pos <= len(data) - 4:
                if data[pos:pos + 4] == target:
                    results.append(region.base + pos)
                    if len(results) >= max_results:
                        return results
                pos += 4

        return results

    def scan_float(self, value: float, max_results: int = 100) -> List[int]:
        """扫描进程内存中匹配的 float 值"""
        results = []
        target = struct.pack('<f', value)

        for region in self.enumerate_regions():
            if region.size > 512 * 1024 * 1024:
                continue
            data = self.read(region.base, region.size)
            if not data:
                continue
            pos = 0
            while pos <= len(data) - 4:
                if data[pos:pos + 4] == target:
                    results.append(region.base + pos)
                    if len(results) >= max_results:
                        return results
                pos += 4

        return results

    def find_pointer_chain(
        self, base_addr: int, offsets: List[int]
    ) -> Optional[int]:
        """跟随指针链读取最终地址"""
        addr = base_addr
        for i, offset in enumerate(offsets):
            ptr = self.read_int64(addr)
            if ptr is None or ptr == 0:
                return None
            addr = ptr + offset
        return addr


class MemoryScanner:
    """
    交互式差分内存扫描器（CheatEngine 式多轮缩小）。

    正确定位一个数值需要多轮：
      1. first_scan(当前看到的值) —— 得到成千上万个候选地址
      2. 游戏里让该数值变化（如买东西金币减少），next_scan(新值) 缩小候选
      3. 重复 2 直到候选唯一 → 该地址即为真实地址

    同时尝试多种数据类型（int32/int64/float/double），
    因为 Godot 里整数常以 int64、浮点以 double 存储。
    """

    # 类型名 -> (struct 格式, 字节数, 是否浮点)
    TYPES = {
        "int32": ("<i", 4, False),
        "int64": ("<q", 8, False),
        "float": ("<f", 4, True),
        "double": ("<d", 8, True),
    }

    def __init__(self, reader: MemoryReader, types: Optional[List[str]] = None):
        self.reader = reader
        self.types = types or ["int32", "int64", "float", "double"]
        self.candidates: dict = {}  # addr -> type_name
        self.scan_count = 0

    def _pack(self, value, tname: str) -> bytes:
        fmt, _, is_float = self.TYPES[tname]
        return struct.pack(fmt, float(value) if is_float else int(value))

    def _read_typed(self, addr: int, tname: str):
        fmt, size, _ = self.TYPES[tname]
        data = self.reader.read(addr, size)
        if not data or len(data) < size:
            return None
        return struct.unpack(fmt, data)[0]

    def first_scan(self, value, max_candidates: int = 400000) -> int:
        """首次扫描：在可写内存区域中查找匹配值的所有地址。"""
        self.candidates = {}
        targets = []
        for t in self.types:
            try:
                targets.append((t, self._pack(value, t)))
            except Exception:
                pass

        for region in self.reader.enumerate_regions():
            if region.size > 256 * 1024 * 1024:
                continue
            # 只扫可写区域——游戏可变数值（金币/血量/回合）都在可写内存里
            if not (region.protect & PAGE_READWRITE):
                continue
            data = self.reader.read(region.base, region.size)
            if not data:
                continue
            for tname, target in targets:
                start = 0
                while True:
                    idx = data.find(target, start)
                    if idx == -1:
                        break
                    self.candidates[region.base + idx] = tname
                    start = idx + 1
            if len(self.candidates) >= max_candidates:
                break

        self.scan_count = 1
        return len(self.candidates)

    def next_scan(self, value) -> int:
        """缩小扫描：仅保留当前值仍等于 value 的候选。"""
        remaining = {}
        for addr, tname in self.candidates.items():
            v = self._read_typed(addr, tname)
            if v is None:
                continue
            _, _, is_float = self.TYPES[tname]
            if is_float:
                if abs(v - float(value)) < 0.5:
                    remaining[addr] = tname
            elif int(v) == int(value):
                remaining[addr] = tname
        self.candidates = remaining
        self.scan_count += 1
        return len(self.candidates)

    @property
    def count(self) -> int:
        return len(self.candidates)

    def best_address(self) -> Optional[int]:
        """返回首个候选地址（缩小到唯一时即为真实地址）。"""
        return next(iter(self.candidates)) if self.candidates else None

    def best_type(self) -> Optional[str]:
        addr = self.best_address()
        return self.candidates.get(addr) if addr is not None else None


class MemoryGameState:
    """
    基于内存读取的游戏状态。
    只有被"校准锁定"的字段（addr 已设置）才会读取真实数值；
    未锁定字段保持 None，避免用随机地址污染显示。
    """

    def __init__(self, reader: MemoryReader):
        self.reader = reader
        self.gold_addr: Optional[int] = None
        self.hp_addr: Optional[int] = None
        self.round_addr: Optional[int] = None

        # 每个字段的数据类型（由校准确定）
        self._types: dict = {"gold": "int32", "hp": "int32", "round": "int32"}

        self.gold: Optional[int] = None
        self.hp: Optional[int] = None
        self.current_round: Optional[int] = None

    def set_field(self, field: str, addr: int, type_name: str = "int32"):
        """锁定某字段的地址与类型。field ∈ {gold, hp, round}"""
        setattr(self, f"{field}_addr", addr)
        self._types[field] = type_name

    def clear_field(self, field: str):
        setattr(self, f"{field}_addr", None)

    def _read_field(self, field: str) -> Optional[int]:
        addr = getattr(self, f"{field}_addr", None)
        if not addr:
            return None
        tname = self._types.get(field, "int32")
        fmt, size, is_float = MemoryScanner.TYPES.get(tname, ("<i", 4, False))
        data = self.reader.read(addr, size)
        if not data or len(data) < size:
            return None
        val = struct.unpack(fmt, data)[0]
        return int(round(val)) if is_float else int(val)

    def update(self):
        """从内存读取已锁定字段的最新值。"""
        v = self._read_field("gold")
        if v is not None:
            self.gold = v
        v = self._read_field("hp")
        if v is not None:
            self.hp = v
        v = self._read_field("round")
        if v is not None:
            self.current_round = v

    @property
    def is_calibrated(self) -> bool:
        return bool(self.gold_addr or self.hp_addr or self.round_addr)

    def to_dict(self) -> dict:
        return {
            "gold": self.gold,
            "hp": self.hp,
            "round": self.current_round,
            "gold_addr": hex(self.gold_addr) if self.gold_addr else None,
            "hp_addr": hex(self.hp_addr) if self.hp_addr else None,
            "round_addr": hex(self.round_addr) if self.round_addr else None,
        }

    def __repr__(self):
        return (
            f"MemoryGameState(gold={self.gold}, hp={self.hp}, "
            f"round={self.current_round})"
        )
