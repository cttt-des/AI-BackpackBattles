"""Analyze extracted game data files."""
import os

# Read ItemData_e.csv
csv_path = 'D:/文件资料/学习/自动背包AI/extracted/Sheets/CSV/ItemData_e.csv'
with open(csv_path, 'rb') as f:
    raw = f.read()

# Check encoding
print(f"ItemData_e.csv size: {len(raw)} bytes")
print(f"First 4 bytes: {raw[:4].hex()}")
# Check for BOM
if raw[:3] == b'\xef\xbb\xbf':
    text = raw[3:].decode('utf-8', errors='replace')
    print("Has UTF-8 BOM")
elif raw[:2] == b'\xff\xfe':
    text = raw[2:].decode('utf-16-le', errors='replace')
    print("Has UTF-16 LE BOM")
else:
    try:
        text = raw.decode('utf-8', errors='replace')
        print("No BOM, decoded as UTF-8")
    except:
        text = raw.decode('latin-1', errors='replace')
        print("Decoded as Latin-1")

lines = text.split('\n')
print(f"Total lines: {len(lines)}")
print(f"\n=== Header (first line) ===")
header = lines[0].strip()
cols = header.split(',')
print(f"Columns ({len(cols)}): {cols}")

print(f"\n=== First 10 items ===")
for line in lines[1:11]:
    parts = line.strip().split(',')
    if len(parts) > 5:
        # Print first few columns
        print(f"  {parts[0]:30s} | {parts[1]:20s} | {parts[2]:10s} | ...")

# Count items
item_count = sum(1 for line in lines[1:] if line.strip())
print(f"\nTotal items: {item_count}")

# Read project.binary
print("\n\n=== project.binary ===")
proj_path = 'D:/文件资料/学习/自动背包AI/extracted/project.binary'
with open(proj_path, 'rb') as f:
    proj_data = f.read()
print(f"Size: {len(proj_data)} bytes")
print(f"First 64 bytes (hex): {proj_data[:64].hex()}")
print(f"First 64 bytes (repr): {repr(proj_data[:64])}")

# Try to find readable strings in project.binary
import re
strings = re.findall(b'[\x20-\x7e]{4,}', proj_data)
print(f"\nReadable strings in project.binary ({len(strings)} found):")
for s in strings[:50]:
    print(f"  {s.decode('ascii', errors='replace')}")

# Read a .remap file
print("\n\n=== Sample .remap file ===")
remap_files = []
for root, dirs, files in os.walk('D:/文件资料/学习/自动背包AI/extracted'):
    for f in files:
        if f.endswith('.remap'):
            remap_files.append(os.path.join(root, f))
            if len(remap_files) >= 3:
                break
    if len(remap_files) >= 3:
        break

for rf in remap_files[:3]:
    with open(rf, 'r', errors='replace') as f:
        content = f.read()
    print(f"\n{rf}:")
    print(content)

# Read plugin_version.txt
print("\n=== plugin_version.txt ===")
with open('D:/文件资料/学习/自动背包AI/extracted/plugin_version.txt', 'r', errors='replace') as f:
    print(f.read())
