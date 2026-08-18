#include "aes256.h"
#include <stdint.h>
#include <string.h>

static const uint8_t sbox[256] = {
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
0x8c,0xa1,0x89,0x0d,0xbf,0xe6,0x42,0x68,0x41,0x99,0x2d,0x0f,0xb0,0x54,0xbb,0x16};

static uint8_t getSBox(uint8_t b){return sbox[b];}
/* Rcon values (AES-128 needs 10, AES-256 needs 7). */
static const uint8_t RCON[10] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x1b,0x36};
#define xtime(x) (((x)<<1) ^ ((((x)>>7) & 1) * 0x1b))
static uint8_t Multiply(uint8_t x, uint8_t y){
    uint8_t r=0;
    while(y){ if(y&1) r^=x; x=xtime(x); y>>=1; }
    return r;
}

/* AES-256 key schedule (Nk=8, Nr=14). i is a BYTE index into RoundKey,
 * so the word index is i/4. The Rcon branch fires every 8 words (i%32==0),
 * the SubWord-only branch fires at word%8==4 (i%32==16). */
static void KeyExpansion(uint8_t* RoundKey, const uint8_t* Key){
    uint32_t i,j;
    uint8_t tempa[4];
    int rcon=0;
    for(i=0;i<32;i++) RoundKey[i]=Key[i];
    for(i=32;i<=236;i+=4){
        for(j=0;j<4;j++) tempa[j]=RoundKey[i-4+j];
        if((i/4) % 8 == 0){            /* i % 32 == 0 : RotWord + SubWord + Rcon */
            uint8_t t=tempa[0];
            tempa[0]=tempa[1]; tempa[1]=tempa[2]; tempa[2]=tempa[3]; tempa[3]=t;
            for(j=0;j<4;j++) tempa[j]=getSBox(tempa[j]);
            tempa[0]^=RCON[rcon++];
        } else if((i/4) % 8 == 4){     /* i % 32 == 16 : SubWord only */
            for(j=0;j<4;j++) tempa[j]=getSBox(tempa[j]);
        }
        for(j=0;j<4;j++) RoundKey[i+j]=RoundKey[i-32+j]^tempa[j];
    }
}
void AES_init_ctx(AES_ctx* ctx, const uint8_t* key){ KeyExpansion(ctx->RoundKey, key); }

static uint8_t InvSbox[256];
static int sbox_inited=0;
static void init_inv(){ int i; for(i=0;i<256;i++) InvSbox[sbox[i]]=(uint8_t)i; sbox_inited=1; }

static void InvMixColumns(uint8_t* state){
    uint8_t a[4]; int i;
    for(i=0;i<4;i++){
        a[0]=state[i*4+0]; a[1]=state[i*4+1]; a[2]=state[i*4+2]; a[3]=state[i*4+3];
        state[i*4+0]=(uint8_t)(Multiply(a[0],14)^Multiply(a[1],11)^Multiply(a[2],13)^Multiply(a[3],9));
        state[i*4+1]=(uint8_t)(Multiply(a[0],9)^Multiply(a[1],14)^Multiply(a[2],11)^Multiply(a[3],13));
        state[i*4+2]=(uint8_t)(Multiply(a[0],13)^Multiply(a[1],9)^Multiply(a[2],14)^Multiply(a[3],11));
        state[i*4+3]=(uint8_t)(Multiply(a[0],11)^Multiply(a[1],13)^Multiply(a[2],9)^Multiply(a[3],14));
    }
}
static void InvShiftRows(uint8_t* state){
    uint8_t tmp;
    tmp=state[13]; state[13]=state[9]; state[9]=state[5]; state[5]=state[1]; state[1]=tmp;
    tmp=state[14]; state[14]=state[6]; state[6]=tmp; tmp=state[10]; state[10]=state[2]; state[2]=tmp;
    /* row 3: shift RIGHT by 3 == rotate LEFT by 1 over indices 3,7,11,15 */
    tmp=state[3]; state[3]=state[7]; state[7]=state[11]; state[11]=state[15]; state[15]=tmp;
}
void AES_ECB_decrypt_block(const AES_ctx* ctx, uint8_t* block){
    if(!sbox_inited) init_inv();
    uint8_t state[16]; int round,i;
    for(i=0;i<16;i++) state[i]=block[i];
    for(i=0;i<16;i++) state[i]^=ctx->RoundKey[240-16+i];
    for(round=13;round>=1;round--){
        InvShiftRows(state);
        for(i=0;i<16;i++) state[i]=InvSbox[state[i]];
        for(i=0;i<16;i++) state[i]^=ctx->RoundKey[round*16+i];
        InvMixColumns(state);
    }
    InvShiftRows(state);
    for(i=0;i<16;i++) state[i]=InvSbox[state[i]];
    for(i=0;i<16;i++) state[i]^=ctx->RoundKey[i];
    for(i=0;i<16;i++) block[i]=state[i];
}

/* ---------------- AES-128 (Nk=4, Nr=10) ---------------- */
static void KeyExpansion128(uint8_t* RoundKey, const uint8_t* Key){
    uint32_t i,j;
    uint8_t tempa[4];
    int rcon=0;
    for(i=0;i<16;i++) RoundKey[i]=Key[i];
    for(i=16;i<=176-4;i+=4){
        for(j=0;j<4;j++) tempa[j]=RoundKey[i-4+j];
        if((i/4) % 4 == 0){            /* i % 16 == 0 : RotWord + SubWord + Rcon */
            uint8_t t=tempa[0];
            tempa[0]=tempa[1]; tempa[1]=tempa[2]; tempa[2]=tempa[3]; tempa[3]=t;
            for(j=0;j<4;j++) tempa[j]=getSBox(tempa[j]);
            tempa[0]^=RCON[rcon++];
        }
        for(j=0;j<4;j++) RoundKey[i+j]=RoundKey[i-16+j]^tempa[j];
    }
}
void AES128_init_ctx(AES_ctx* ctx, const uint8_t* key){ KeyExpansion128(ctx->RoundKey, key); }

void AES128_ECB_decrypt_block(const AES_ctx* ctx, uint8_t* block){
    if(!sbox_inited) init_inv();
    uint8_t state[16]; int round,i;
    for(i=0;i<16;i++) state[i]=block[i];
    for(i=0;i<16;i++) state[i]^=ctx->RoundKey[176-16+i];   /* AddRoundKey(10) */
    for(round=9;round>=1;round--){
        InvShiftRows(state);
        for(i=0;i<16;i++) state[i]=InvSbox[state[i]];
        for(i=0;i<16;i++) state[i]^=ctx->RoundKey[round*16+i];
        InvMixColumns(state);
    }
    InvShiftRows(state);
    for(i=0;i<16;i++) state[i]=InvSbox[state[i]];
    for(i=0;i<16;i++) state[i]^=ctx->RoundKey[i];
    for(i=0;i<16;i++) block[i]=state[i];
}
