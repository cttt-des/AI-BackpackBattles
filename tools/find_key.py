"""
Search the Godot exe binary for the script encryption key.
In Godot 3.x, the 32-byte AES-256 key is compiled into the binary.
"""
import struct
import re
import os

exe_path = 'D:/文件资料/学习/自动背包AI/Backpack Battles/BackpackBattles.exe'

with open(exe_path, 'rb') as f:
    data = f.read()

print(f"Exe size: {len(data)} bytes")

# Method 1: Search for "script_encryption_key" string
pattern = b'script_encryption_key'
positions = []
start = 0
while True:
    pos = data.find(pattern, start)
    if pos == -1:
        break
    positions.append(pos)
    start = pos + 1

print(f"\n'script_encryption_key' found at positions: {positions}")
for pos in positions:
    # Show context around the string
    ctx_start = max(0, pos - 64)
    ctx_end = min(len(data), pos + 128)
    print(f"  Context around offset {pos}:")
    print(f"  {data[ctx_start:ctx_end]}")

# Method 2: Search for "ScriptEncryptionKey" or similar
for pattern in [b'ScriptEncryptionKey', b'encryption_key', b'ENCRYPT_KEY', b'script_key']:
    positions = []
    start = 0
    while True:
        pos = data.find(pattern, start)
        if pos == -1:
            break
        positions.append(pos)
        start = pos + 1
    if positions:
        print(f"\n'{pattern.decode()}' found at positions: {positions}")

# Method 3: Search for hex string patterns (64 hex chars = 32 bytes)
# Godot stores the key as a hex string in project settings
hex_pattern = re.compile(rb'[0-9a-fA-F]{64}')
hex_matches = list(hex_pattern.finditer(data))
print(f"\nFound {len(hex_matches)} 64-char hex strings")
for m in hex_matches[:10]:
    hex_str = m.group().decode()
    print(f"  Offset {m.start()}: {hex_str}")
    # Convert to bytes and check if it looks like a key
    try:
        key_bytes = bytes.fromhex(hex_str)
        print(f"  As bytes: {key_bytes.hex()}")
    except:
        pass

# Method 4: Look for the GDEC string in the binary (used by the decryption code)
gdec_pos = data.find(b'GDEC')
print(f"\n'GDEC' found at offset: {gdec_pos}")
if gdec_pos >= 0:
    # Show context
    ctx_start = max(0, gdec_pos - 256)
    ctx_end = min(len(data), gdec_pos + 256)
    print(f"  Context: {data[ctx_start:ctx_end]}")

# Method 5: Search for AES S-box pattern (first 16 bytes of AES S-box)
# This indicates where AES is used, and the key might be nearby
aes_sbox_start = bytes([0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5,
                        0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76])
sbox_pos = data.find(aes_sbox_start)
print(f"\nAES S-box found at offset: {sbox_pos}")

# Method 6: Look for potential 32-byte keys near the GDEC reference
# In the code, the key is loaded before the GDEC check
if gdec_pos >= 0:
    # Search backwards from GDEC for potential key data
    search_start = max(0, gdec_pos - 4096)
    search_end = gdec_pos
    # Look for 32-byte sequences that aren't all zeros or all same byte
    region = data[search_start:search_end]
    for i in range(0, len(region) - 32, 4):
        candidate = region[i:i+32]
        # Skip if all zeros, all same byte, or mostly ASCII
        unique_bytes = len(set(candidate))
        if unique_bytes < 8:  # Key should have high entropy
            continue
        if all(0x20 <= b <= 0x7e for b in candidate):  # Skip ASCII strings
            continue
        # Check if it looks like a key (high entropy, no null bytes in the middle)
        null_count = candidate.count(0)
        if null_count > 4:
            continue
        print(f"  Potential key at offset {search_start + i}: {candidate.hex()}")
