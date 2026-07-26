"""Check .gde file format to determine if encrypted or compiled."""
import os

# Check a small .gde file
gde_path = 'D:/文件资料/学习/自动背包AI/extracted/Core/Player.gde'
with open(gde_path, 'rb') as f:
    data = f.read()

print(f'Player.gde size: {len(data)} bytes')
print(f'First 64 bytes (hex): {data[:64].hex()}')
print(f'First 64 bytes (repr): {repr(data[:64])}')
print(f'Magic: {data[:4]}')

# Check a larger file
gde_path2 = 'D:/文件资料/学习/自动背包AI/extracted/Core/Inventory.gde'
with open(gde_path2, 'rb') as f:
    data2 = f.read(128)
print(f'\nInventory.gde first 128 bytes (hex): {data2[:128].hex()}')
print(f'Magic: {data2[:4]}')

# Check Game.gde (the big one)
gde_path3 = 'D:/文件资料/学习/自动背包AI/extracted/Core/Game.gde'
with open(gde_path3, 'rb') as f:
    data3 = f.read(128)
print(f'\nGame.gde first 128 bytes (hex): {data3[:128].hex()}')
print(f'Magic: {data3[:4]}')

# Check if there are any readable strings
print(f'\nSearching for readable strings in Player.gde...')
import re
strings = re.findall(b'[\x20-\x7e]{4,}', data)
for s in strings[:20]:
    print(f'  {s.decode("ascii", errors="replace")}')
