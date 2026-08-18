/* test_aes.c - validate AES_ECB_decrypt_block against pycryptodome cases.
 * Usage: test_aes <aes_kat.bin>
 * Also checks the FIPS-197 AES-256 known-answer vector.
 */
#include <windows.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "aes256.h"

static int hexcmp_print(const uint8_t* got, const uint8_t* exp, int n){
    int ok=1,i;
    for(i=0;i<n;i++) if(got[i]!=exp[i]) ok=0;
    if(ok) return 1;
    printf("  got: ");
    for(i=0;i<n;i++) printf("%02x",got[i]);
    printf("\n  exp: ");
    for(i=0;i<n;i++) printf("%02x",exp[i]);
    printf("\n");
    return 0;
}

int main(int argc, char** argv){
    if(argc<2){ printf("usage: %s <aes_kat.bin>\n", argv[0]); return 1; }

    /* ---- FIPS-197 C.3 AES-256 KAT ---- */
    {
        uint8_t key[32]={
            0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,
            0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f};
        uint8_t ct[16]={0x8e,0xa2,0xb7,0xca,0x51,0x67,0x45,0xbf,0xea,0xfc,0x49,0x90,0x4b,0x49,0x60,0x89};
        uint8_t pt[16]={0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff};
        AES_ctx ctx; AES_init_ctx(&ctx,key);
        uint8_t blk[16]; memcpy(blk,ct,16);
        AES_ECB_decrypt_block(&ctx,blk);
        printf("[KAT] FIPS AES-256 decrypt: %s\n", hexcmp_print(blk,pt,16)?"PASS":"FAIL");
    }

    /* ---- pycryptodome random cases ---- */
    FILE* f=fopen(argv[1],"rb");
    if(!f){ printf("cannot open %s\n", argv[1]); return 1; }
    uint32_t N;
    if(fread(&N,4,1,f)!=1){ printf("bad file\n"); fclose(f); return 1; }
    uint8_t rec[64];
    uint32_t pass=0, fail=0;
    for(uint32_t i=0;i<N;i++){
        if(fread(rec,1,64,f)!=64) break;
        uint8_t* key=rec; uint8_t* ct=rec+32; uint8_t* pt=rec+48;
        AES_ctx ctx; AES_init_ctx(&ctx,key);
        uint8_t blk[16]; memcpy(blk,ct,16);
        AES_ECB_decrypt_block(&ctx,blk);
        if(memcmp(blk,pt,16)==0) pass++; else {
            fail++;
            if(fail<=3){ printf("case %u FAIL\n", i); hexcmp_print(blk,pt,16); }
        }
    }
    fclose(f);
    printf("[CASES] AES-256 decrypt: %u/%u passed, %u failed\n", pass, N, fail);

    /* ---- AES-128 cases ---- */
    f=fopen("_aes_kat128.bin","rb");
    if(!f){ printf("cannot open _aes_kat128.bin\n"); return 1; }
    if(fread(&N,4,1,f)!=1){ printf("bad 128 file\n"); fclose(f); return 1; }
    uint8_t rec128[48];
    uint32_t pass128=0, fail128=0;
    for(uint32_t i=0;i<N;i++){
        if(fread(rec128,1,48,f)!=48) break;
        uint8_t* key=rec128; uint8_t* ct=rec128+16; uint8_t* pt=rec128+32;
        AES_ctx ctx; AES128_init_ctx(&ctx,key);
        uint8_t blk[16]; memcpy(blk,ct,16);
        AES128_ECB_decrypt_block(&ctx,blk);
        if(memcmp(blk,pt,16)==0) pass128++; else {
            fail128++;
            if(fail128<=3){ printf("128 case %u FAIL\n", i); hexcmp_print(blk,pt,16); }
        }
    }
    fclose(f);
    printf("[CASES] AES-128 decrypt: %u/%u passed, %u failed\n", pass128, N, fail128);

    int total_fail = fail+fail128;
    printf(total_fail==0 ? "ALL_OK\n" : "HAS_FAILURES\n");
    return total_fail==0?0:1;
}
