"""
解密 Backpack Battles 的 Godot 加密脚本 (.gde / GDEC)。

Godot 3.x 加密脚本格式:
  [4B "GDEC"][4B 保留/版本][AES-256-CBC 密文]
密文解密后得到 "GDSC" 开头的编译后脚本(GDScript bytecode)。
密钥 = project.binary / exe 中的 script_encryption_key(64 个十六进制字符 = 32 字节)。

用法:
  python tools/decrypt_gde.py <file.gde> [--key HEX] [--exe PATH] [--grep STR]
"""
import argparse
import os
import re
import struct

try:
    from Crypto.Cipher import AES
except ImportError:  # 兜底：优先 pycryptodome，缺失时提示
    AES = None


def find_key_in_exe(exe_path: str) -> str | None:
    """在 exe 中定位 script_encryption_key 对应的 64 位十六进制密钥。"""
    data = open(exe_path, "rb").read()
    # 方式 A: 直接搜 64 位 hex 串
    for m in re.finditer(rb"[0-9a-fA-F]{64}", data):
        return m.group().decode()
    # 方式 B: 找 'script_encryption_key' 字符串，其附近应有 hex key
    idx = data.find(b"script_encryption_key")
    if idx >= 0:
        region = data[idx: idx + 256]
        m = re.search(rb"[0-9a-fA-F]{64}", region)
        if m:
            return m.group().decode()
    return None


def decrypt_gde(path: str, key_hex: str) -> bytes | None:
    if AES is None:
        raise RuntimeError("需要 pycryptodome: pip install pycryptodome")
    raw = open(path, "rb").read()
    if raw[:4] != b"GDEC":
        # 也许已经是明文/未加密
        return raw
    key = bytes.fromhex(key_hex)
    if len(key) != 32:
        raise ValueError("密钥必须为 32 字节(64 个十六进制字符)")
    cipher_text = raw[8:]  # 跳过 GDEC(4) + 保留(4)
    # Godot 3.x 使用 AES-256-CBC，IV 为 16 字节全 0
    aes = AES.new(key, AES.MODE_CBC, b"\x00" * 16)
    plain = aes.decrypt(cipher_text)
    if plain[:4] != b"GDSC":
        return None  # 密钥错误
    return plain


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("file")
    ap.add_argument("--key")
    ap.add_argument("--exe", default="Backpack Battles/BackpackBattles.exe")
    ap.add_argument("--grep", default=None, help="在解密结果中搜索字符串(可多个, 逗号分隔)")
    args = ap.parse_args()

    key = args.key or find_key_in_exe(args.exe)
    if not key:
        print("ERROR: 未在 exe 中找到 script_encryption_key，请用 --key 指定")
        return 1

    plain = decrypt_gde(args.file, key)
    if plain is None:
        print("ERROR: 解密失败(密钥错误或非 GDEC 文件)")
        return 1

    print(f"# 解密成功: {args.file}  ({len(plain)} bytes, magic={plain[:4]})")
    if args.grep:
        needles = [n.strip().encode("utf-8", "ignore") for n in args.grep.split(",")]
        for line in re.findall(rb"[\x20-\x7e]{3,}", plain):
            low = line.lower()
            if any(n.lower() in low for n in needles):
                try:
                    print("  ", line.decode("ascii", "replace"))
                except Exception:
                    pass
    else:
        # 默认打印所有可读串(前若干)
        seen = 0
        for line in re.findall(rb"[\x20-\x7e]{4,}", plain):
            try:
                print("  ", line.decode("ascii", "replace"))
            except Exception:
                pass
            seen += 1
            if seen > 400:
                print("  ... (截断)")
                break
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
