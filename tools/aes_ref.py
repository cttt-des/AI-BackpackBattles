"""Reference AES-256 (ECB) in pure Python, validated against pycryptodome.
Used to (a) confirm correctness and (b) dump the round-key schedule so the
C implementation (tools/aes256.c) can be matched exactly.
"""
import os, struct, random
from Crypto.Cipher import AES

SBOX = [
0x63,0x7c,0x77,0x7b,0xf2,0x6b,0x6f,0xc5,0x30,0x01,0x67,0x2b,0xfe,0xd7,0xab,0x76,
0xca,0x82,0xc9,0x7d,0xfa,0x59,0x47,0xf0,0xad,0xd4,0xa2,0xaf,0x9c,0xa4,0x72,0xc0,
0xb7,0xfd,0x93,0x26,0x36,0x3f,0xf7,0xcc,0x34,0xa5,0xe5,0xf1,0x71,0xd8,0x31,0x15,
0x04,0xc7,0x23,0xc3,0x18,0x96,0x05,0x9a,0x07,0x12,0x80,0xe2,0xeb,0x27,0xb2,0x75,
0x09,0x83,0x2c,0x1a,0x1b,0x6e,0x5a,0xa0,0x52,0x3b,0xd6,0xb3,0x29,0xe3,0x2f,0x84,
0x53,0xd1,0x00,0xed,0x20,0xfc,0xb1,0x5b,0x6a,0xcb,0xbe,0x39,0x4a,0x4c,0x58,0xcf,
0xd0,0xef,0xaa,0xfb,0x43,0x4d,0x33,0x85,0x45,0xf9,0x02,0x7f,0x50,0x3c,0x9f,0xa8,
0x51,0xa3,0x40,0x8f,0x92,0x9d,0x38,0xf5,0xbc,0xb6,0xda,0x21,0x10,0xff,0xf3,0xd2,
0xcd,0x0c,0x13,0xec,0x5f,0x97,0x44,0x17,0xc4,0xa7,0x7e,0x3d,0x64,0x5d,0x19,0x73,
0x60,0x81,0x4f,0xdc,0x22,0x2a,0x90,0x88,0x46,0xee,0xb8,0x14,0xde,0x5e,0x0b,0xdb,
0xe0,0x32,0x3a,0x0a,0x49,0x06,0x24,0x5c,0xc2,0xd3,0xac,0x62,0x91,0x95,0xe4,0x79,
0xe7,0xc8,0x37,0x6d,0x8d,0xd5,0x4e,0xa9,0x6c,0x56,0xf4,0xea,0x65,0x7a,0xae,0x08,
0xba,0x78,0x25,0x2e,0x1c,0xa6,0xb4,0xc6,0xe8,0xdd,0x74,0x1f,0x4b,0xbd,0x8b,0x8a,
0x70,0x3e,0xb5,0x66,0x48,0x03,0xf6,0x0e,0x61,0x35,0x57,0xb9,0x86,0xc1,0x1d,0x9e,
0xe1,0xf8,0x98,0x11,0x69,0xd9,0x8e,0x94,0x9b,0x1e,0x87,0xe9,0xce,0x55,0x28,0xdf,
0x8c,0xa1,0x89,0x0d,0xbf,0xe6,0x42,0x68,0x41,0x99,0x2d,0x0f,0xb0,0x54,0xbb,0x16]
INV_SBOX = [SBOX.index(x) for x in range(256)]

def _xtime(a):
    a <<= 1
    if a & 0x100: a ^= 0x11b
    return a & 0xff

def _mul(a,b):
    r=0
    while b:
        if b&1: r^=a
        a=_xtime(a)
        b>>=1
    return r

RCON = [0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x1b,0x36]

def key_expansion(key):
    Nk=8; Nr=14
    w=[list(key[4*i:4*i+4]) for i in range(Nk)]
    for i in range(Nk, 4*(Nr+1)):
        temp=list(w[i-1])
        if i % Nk == 0:
            temp=temp[1:]+temp[:1]            # RotWord
            temp=[SBOX[b] for b in temp]      # SubWord
            temp[0]^=RCON[i//Nk - 1]
        elif i % Nk == 4:
            temp=[SBOX[b] for b in temp]
        w.append([w[i-Nk][j]^temp[j] for j in range(4)])
    return w

def _add_round_key(state, w, r):
    for c in range(4):
        for row in range(4):
            state[row][c]^=w[r*4+c][row]

def _sub_bytes(state, box):
    for r in range(4):
        for c in range(4):
            state[r][c]=box[state[r][c]]

def _shift_rows(state):
    state[1][0],state[1][1],state[1][2],state[1][3]=state[1][1],state[1][2],state[1][3],state[1][0]
    state[2][0],state[2][1],state[2][2],state[2][3]=state[2][2],state[2][3],state[2][0],state[2][1]
    state[3][0],state[3][1],state[3][2],state[3][3]=state[3][3],state[3][0],state[3][1],state[3][2]

def _inv_shift_rows(state):
    # inverse of ShiftRows: row r shifts RIGHT by r
    state[1][0],state[1][1],state[1][2],state[1][3]=state[1][3],state[1][0],state[1][1],state[1][2]
    state[2][0],state[2][1],state[2][2],state[2][3]=state[2][2],state[2][3],state[2][0],state[2][1]
    state[3][0],state[3][1],state[3][2],state[3][3]=state[3][1],state[3][2],state[3][3],state[3][0]

def _mix_columns(state):
    for c in range(4):
        a=[state[r][c] for r in range(4)]
        state[0][c]=_mul(a[0],2)^_mul(a[1],3)^a[2]^a[3]
        state[1][c]=a[0]^_mul(a[1],2)^_mul(a[2],3)^a[3]
        state[2][c]=a[0]^a[1]^_mul(a[2],2)^_mul(a[3],3)
        state[3][c]=_mul(a[0],3)^a[1]^a[2]^_mul(a[3],2)

def _inv_mix_columns(state):
    for c in range(4):
        a=[state[r][c] for r in range(4)]
        state[0][c]=_mul(a[0],14)^_mul(a[1],11)^_mul(a[2],13)^_mul(a[3],9)
        state[1][c]=_mul(a[0],9)^_mul(a[1],14)^_mul(a[2],11)^_mul(a[3],13)
        state[2][c]=_mul(a[0],13)^_mul(a[1],9)^_mul(a[2],14)^_mul(a[3],11)
        state[3][c]=_mul(a[0],11)^_mul(a[1],13)^_mul(a[2],9)^_mul(a[3],14)

def _bytes_to_state(b):
    return [[b[r+4*c] for c in range(4)] for r in range(4)]

def _state_to_bytes(s):
    return bytes(s[r][c] for c in range(4) for r in range(4))

def aes_encrypt_block(pt, key):
    w=key_expansion(key)
    state=_bytes_to_state(pt)
    _add_round_key(state,w,0)
    for r in range(1,14):
        _sub_bytes(state,SBOX)
        _shift_rows(state)
        _mix_columns(state)
        _add_round_key(state,w,r)
    _sub_bytes(state,SBOX)
    _shift_rows(state)
    _add_round_key(state,w,14)
    return _state_to_bytes(state)

def aes_decrypt_block(ct, key):
    w=key_expansion(key)
    state=_bytes_to_state(ct)
    _add_round_key(state,w,14)
    for r in range(13,0,-1):
        _inv_shift_rows(state)
        _sub_bytes(state,INV_SBOX)
        _add_round_key(state,w,r)
        _inv_mix_columns(state)
    _inv_shift_rows(state)
    _sub_bytes(state,INV_SBOX)
    _add_round_key(state,w,0)
    return _state_to_bytes(state)

if __name__=="__main__":
    random.seed(1)
    enc_ok=dec_ok=0
    for _ in range(20):
        key=random.randbytes(32); blk=random.randbytes(16)
        mine=aes_encrypt_block(blk,key)
        ref=AES.new(key,AES.MODE_ECB).encrypt(blk)
        enc_ok+= (mine==ref)
        mine_d=aes_decrypt_block(ref,key)
        dec_ok+= (mine_d==blk)
    print(f"encrypt vs pycryptodome: {enc_ok}/20")
    print(f"decrypt vs pycryptodome: {dec_ok}/20")

    k=bytes.fromhex("000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f")
    p=bytes.fromhex("00112233445566778899aabbccddeeff")
    c=aes_encrypt_block(p,k)
    print("FIPS KAT enc:", c.hex(), "OK" if c.hex()=="8ea2b7ca516745bfeafc49904b496089" else "FAIL")
    print("FIPS KAT dec:", aes_decrypt_block(c,k).hex(), "OK" if aes_decrypt_block(c,k)==p else "FAIL")

    w=key_expansion(k)
    print("python w[8]:", bytes(w[8]).hex(), "(C currently prints a573c29f)")
