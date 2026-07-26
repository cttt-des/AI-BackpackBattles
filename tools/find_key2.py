"""
Advanced search for Godot script encryption key.
Parse PE sections and look for high-entropy 32-byte sequences in .rdata section.
Also try each candidate against a known .gde file.
"""
import struct
import math
import os

exe_path = 'D:/文件资料/学习/自动背包AI/Backpack Battles/BackpackBattles.exe'

with open(exe_path, 'rb') as f:
    data = f.read()

# Parse PE headers
dos_magic = struct.unpack('<H', data[:2])[0]
assert dos_magic == 0x5A4D, "Not a PE file"

pe_offset = struct.unpack('<I', data[0x3C:0x40])[0]
pe_magic = struct.unpack('<I', data[pe_offset:pe_offset+4])[0]
assert pe_magic == 0x00004550, "Invalid PE signature"

# COFF header
num_sections = struct.unpack('<H', data[pe_offset+6:pe_offset+8])[0]
opt_header_size = struct.unpack('<H', data[pe_offset+20:pe_offset+22])[0]

# Section table starts after optional header
section_table_offset = pe_offset + 24 + opt_header_size

print(f"PE sections: {num_sections}")
sections = []
for i in range(num_sections):
    offset = section_table_offset + i * 40
    name = data[offset:offset+8].rstrip(b'\x00').decode('ascii', errors='replace')
    vsize = struct.unpack('<I', data[offset+8:offset+12])[0]
    vaddr = struct.unpack('<I', data[offset+12:offset+16])[0]
    rawsize = struct.unpack('<I', data[offset+16:offset+20])[0]
    rawoffset = struct.unpack('<I', data[offset+20:offset+24])[0]
    chars = struct.unpack('<I', data[offset+36:offset+40])[0]
    sections.append((name, vaddr, vsize, rawoffset, rawsize, chars))
    print(f"  {name}: vaddr=0x{vaddr:08x} vsize=0x{vsize:08x} raw=0x{rawoffset:08x} rawsize=0x{rawsize:08x} chars=0x{chars:08x}")

def entropy(data_bytes):
    """Calculate Shannon entropy of a byte sequence."""
    if len(data_bytes) == 0:
        return 0
    freq = {}
    for b in data_bytes:
        freq[b] = freq.get(b, 0) + 1
    ent = 0
    for count in freq.values():
        p = count / len(data_bytes)
        if p > 0:
            ent -= p * math.log2(p)
    return ent

# Search .rdata section for high-entropy 32-byte sequences
# The encryption key should have high entropy (>3.5 bits/byte)
candidates = []
for name, vaddr, vsize, rawoffset, rawsize, chars in sections:
    if name not in ('.rdata', '.data'):
        continue
    print(f"\nSearching {name} section (raw offset=0x{rawoffset:x}, size=0x{rawsize:x})")
    section_data = data[rawoffset:rawoffset+rawsize]
    
    # Scan for 32-byte windows with high entropy
    for i in range(0, len(section_data) - 32, 1):
        candidate = section_data[i:i+32]
        ent = entropy(candidate)
        if ent > 4.0:  # High entropy threshold
            # Additional checks: no more than 2 null bytes, not all printable ASCII
            null_count = candidate.count(0)
            ascii_count = sum(1 for b in candidate if 0x20 <= b <= 0x7e)
            if null_count > 2 or ascii_count > 28:
                continue
            # Check if it's unique (not a repeating pattern)
            if len(set(candidate)) < 16:
                continue
            candidates.append((rawoffset + i, candidate, ent))

# Sort by entropy and deduplicate
candidates.sort(key=lambda x: -x[2])
# Remove overlapping candidates
unique_candidates = []
seen_ranges = set()
for offset, candidate, ent in candidates:
    # Check if this overlaps with an already seen candidate
    overlap = False
    for seen_start, seen_end in seen_ranges:
        if abs(offset - seen_start) < 32:
            overlap = True
            break
    if not overlap:
        unique_candidates.append((offset, candidate, ent))
        seen_ranges.add((offset, offset + 32))

print(f"\nFound {len(unique_candidates)} unique high-entropy 32-byte candidates (top 30):")
for offset, candidate, ent in unique_candidates[:30]:
    print(f"  Offset 0x{offset:08x}: entropy={ent:.2f} key={candidate.hex()}")

# Now try to decrypt Player.gde with each candidate
# Read Player.gde
gde_path = 'D:/文件资料/学习/自动背包AI/extracted/Core/Player.gde'
with open(gde_path, 'rb') as f:
    gde_data = f.read()

# GDEC format: 4 bytes magic, 4 bytes version, rest is encrypted
# In Godot 3.x, the encrypted data uses AES-256-CBC
# The IV is typically zeros or the first 16 bytes of the encrypted data

print(f"\nTrying to decrypt Player.gde ({len(gde_data)} bytes) with each candidate...")
print(f"GDE header: magic={gde_data[:4]}, version={struct.unpack('<I', gde_data[4:8])[0]}")
print(f"Encrypted data size: {len(gde_data) - 8} bytes")

# Try installing pycryptodome for AES decryption
try:
    from Crypto.Cipher import AES
    has_crypto = True
    print("pycryptodome available!")
except ImportError:
    has_crypto = False
    print("pycryptodome not available, installing...")

if not has_crypto:
    import subprocess
    subprocess.run(['C:/Users/Windows/.workbuddy/binaries/python/envs/backpack_ai/Scripts/pip.exe', 
                    'install', '--no-cache-dir', 'pycryptodome'], capture_output=True)
    from Crypto.Cipher import AES
    print("pycryptodome installed!")

# Try decryption with each candidate
# Godot 3.x uses AES-256-CBC with the first 16 bytes of encrypted data as IV
# Actually, looking at the Godot source more carefully:
# The encrypted data after the 8-byte header is: IV (16 bytes) + encrypted_data
# OR: the IV is all zeros

encrypted_data = gde_data[8:]  # After GDEC + version

for offset, candidate, ent in unique_candidates[:50]:
    try:
        # Try with first 16 bytes as IV
        if len(encrypted_data) > 16:
            iv = encrypted_data[:16]
            ct = encrypted_data[16:]
            if len(ct) % 16 != 0:
                # Try with zero IV
                iv = b'\x00' * 16
                ct = encrypted_data
                if len(ct) % 16 != 0:
                    continue
            cipher = AES.new(candidate, AES.MODE_CBC, iv)
            pt = cipher.decrypt(ct)
            # Check if decrypted data looks like valid GDScript bytecode
            # GDScript bytecode starts with a version number and has specific structure
            if pt[:4] in [b'\x00\x00\x00\x00', b'\x01\x00\x00\x00', b'\x02\x00\x00\x00']:
                print(f"\n  *** POSSIBLE MATCH at offset 0x{offset:08x}! ***")
                print(f"  Key: {candidate.hex()}")
                print(f"  Decrypted first 64 bytes: {pt[:64].hex()}")
                # Check for readable strings
                import re
                strings = re.findall(b'[\x20-\x7e]{4,}', pt)
                if strings:
                    print(f"  Strings found: {[s.decode() for s in strings[:10]]}")
            elif any(pt[i:i+4] == b'\\x00\\x00\\x00\\x00' for i in range(0, min(32, len(pt)-4), 4)):
                pass  # Skip, just zeros
        
        # Also try with zero IV
        iv = b'\x00' * 16
        ct = encrypted_data
        if len(ct) % 16 == 0:
            cipher = AES.new(candidate, AES.MODE_CBC, iv)
            pt = cipher.decrypt(ct)
            if pt[:4] in [b'\x01\x00\x00\x00', b'\x02\x00\x00\x00']:
                print(f"\n  *** POSSIBLE MATCH (zero IV) at offset 0x{offset:08x}! ***")
                print(f"  Key: {candidate.hex()}")
                print(f"  Decrypted first 64 bytes: {pt[:64].hex()}")
    except Exception as e:
        pass

print("\nDone searching.")
