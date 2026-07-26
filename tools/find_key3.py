"""
Brute-force search for Godot script encryption key.
Try all 32-byte aligned sequences in .rdata section as AES keys.
"""
import struct
import os
import sys
from Crypto.Cipher import AES

exe_path = 'D:/文件资料/学习/自动背包AI/Backpack Battles/BackpackBattles.exe'
gde_path = 'D:/文件资料/学习/自动背包AI/extracted/Core/Player.gde'

with open(exe_path, 'rb') as f:
    exe_data = f.read()

with open(gde_path, 'rb') as f:
    gde_data = f.read()

# Parse PE to find .rdata section
pe_offset = struct.unpack('<I', exe_data[0x3C:0x40])[0]
num_sections = struct.unpack('<H', exe_data[pe_offset+6:pe_offset+8])[0]
opt_header_size = struct.unpack('<H', exe_data[pe_offset+20:pe_offset+22])[0]
section_table_offset = pe_offset + 24 + opt_header_size

rdata_raw_offset = None
rdata_raw_size = None
for i in range(num_sections):
    off = section_table_offset + i * 40
    name = exe_data[off:off+8].rstrip(b'\x00').decode('ascii', errors='replace')
    rawoffset = struct.unpack('<I', exe_data[off+20:off+24])[0]
    rawsize = struct.unpack('<I', exe_data[off+16:off+20])[0]
    if name == '.rdata':
        rdata_raw_offset = rawoffset
        rdata_raw_size = rawsize
        print(f".rdata: raw=0x{rawoffset:08x} size=0x{rawsize:08x}")

# Also check .data section
data_raw_offset = None
data_raw_size = None
for i in range(num_sections):
    off = section_table_offset + i * 40
    name = exe_data[off:off+8].rstrip(b'\x00').decode('ascii', errors='replace')
    rawoffset = struct.unpack('<I', exe_data[off+20:off+24])[0]
    rawsize = struct.unpack('<I', exe_data[off+16:off+20])[0]
    if name == '.data':
        data_raw_offset = rawoffset
        data_raw_size = rawsize
        print(f".data: raw=0x{rawoffset:08x} size=0x{rawsize:08x}")

# GDEC format: 4 bytes "GDEC" + 4 bytes version + encrypted data
# AES-256-CBC with zero IV, no padding
encrypted_data = gde_data[8:]
print(f"\nGDE: magic={gde_data[:4]}, ver={struct.unpack('<I', gde_data[4:8])[0]}")
print(f"Encrypted data: {len(encrypted_data)} bytes")

# Pad to 16-byte boundary if needed
if len(encrypted_data) % 16 != 0:
    padded = encrypted_data + b'\x00' * (16 - len(encrypted_data) % 16)
else:
    padded = encrypted_data
print(f"Padded: {len(padded)} bytes")

# GDScript bytecode starts with:
# - uint32 version (should be small, like 1-3)
# - uint32 token count
# - uint32 line count
# - uint32 identifier count
# - uint32 constant count
# - uint32 function count
# These are all small numbers, so the first 4 bytes should be a small uint32

def check_decryption(key, encrypted, iv=b'\x00'*16):
    """Try to decrypt and check if result looks like valid GDScript bytecode."""
    try:
        if len(encrypted) % 16 != 0:
            return None
        cipher = AES.new(key, AES.MODE_CBC, iv)
        pt = cipher.decrypt(encrypted)
        # Check if first 4 bytes look like a version number (1-5)
        ver = struct.unpack('<I', pt[:4])[0]
        if 1 <= ver <= 5:
            # Check next few uint32s - they should be reasonable sizes
            vals = struct.unpack('<6I', pt[:24])
            if all(0 <= v < 100000 for v in vals):
                return pt
        return None
    except:
        return None

# Search .rdata section
print("\nSearching .rdata section...")
found = False
search_sections = []
if rdata_raw_offset:
    search_sections.append(('.rdata', rdata_raw_offset, rdata_raw_size))
if data_raw_offset:
    search_sections.append(('.data', data_raw_offset, data_raw_size))

for sec_name, sec_offset, sec_size in search_sections:
    print(f"\nScanning {sec_name} ({sec_size} bytes, ~{sec_size//4} candidates)...")
    count = 0
    for i in range(0, sec_size - 32, 4):
        key = exe_data[sec_offset + i: sec_offset + i + 32]
        # Quick filter: skip if too many null bytes or low diversity
        if key.count(0) > 4:
            continue
        if len(set(key)) < 16:
            continue
        
        pt = check_decryption(key, padded)
        if pt is not None:
            print(f"\n*** FOUND KEY at {sec_name}+0x{i:08x} (file offset 0x{sec_offset+i:08x}) ***")
            print(f"Key (hex): {key.hex()}")
            print(f"Decrypted first 64 bytes: {pt[:64].hex()}")
            # Look for readable strings
            import re
            strings = re.findall(b'[\x20-\x7e]{4,}', pt[:200])
            if strings:
                print(f"Strings: {[s.decode() for s in strings[:15]]}")
            found = True
            break
        
        count += 1
        if count % 200000 == 0:
            print(f"  Scanned {count} candidates...")
    
    if found:
        break

if not found:
    print("\nKey not found in aligned scan. Trying unaligned scan in .rdata...")
    # Try 1-byte alignment for a smaller region
    if rdata_raw_offset:
        # Focus on regions near known patterns
        # The GDEC comparison is at offset 23204042 in the file
        # The .rdata section starts at 0x0187e000
        # Let's search nearby regions
        gdec_file_offset = 23204042
        # Search in a 64KB window around GDEC in .rdata
        # GDEC is in .text section, but the key reference might be nearby in .rdata
        
        # Actually, let's try searching the entire .rdata with 1-byte alignment
        # but only for high-entropy candidates
        print(f"Full 1-byte alignment scan of .rdata ({sec_size} bytes)...")
        count = 0
        for i in range(0, rdata_raw_size - 32, 1):
            key = exe_data[rdata_raw_offset + i: rdata_raw_offset + i + 32]
            if key.count(0) > 2:
                continue
            if len(set(key)) < 20:
                continue
            # Only try keys with high entropy
            pt = check_decryption(key, padded)
            if pt is not None:
                print(f"\n*** FOUND KEY at .rdata+0x{i:08x} ***")
                print(f"Key (hex): {key.hex()}")
                print(f"Decrypted first 64 bytes: {pt[:64].hex()}")
                import re
                strings = re.findall(b'[\x20-\x7e]{4,}', pt[:200])
                if strings:
                    print(f"Strings: {[s.decode() for s in strings[:15]]}")
                found = True
                break
            count += 1
            if count % 500000 == 0:
                print(f"  Scanned {count} candidates...")

if not found:
    print("\nKey not found.")
