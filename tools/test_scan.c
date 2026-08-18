#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "aes256.h"
volatile size_t g_i = 0;
void handler(int sig){
    fprintf(stderr,"SIGSEGV near window i=%llu\n",(unsigned long long)g_i);
    fflush(stderr);
    _exit(2);
}
int main(int argc, char** argv){
    signal(SIGSEGV, handler);
    FILE* f=fopen("D:/steam/steamapps/common/Backpack Battles/BackpackBattles.exe","rb");
    fseek(f,0,SEEK_END); long ts=ftell(f); fseek(f,0,SEEK_SET);
    uint8_t* buf=(uint8_t*)malloc(ts);
    fread(buf,1,ts,f); fclose(f);
    FILE* gf=fopen("Combat.gde","rb");
    uint8_t hdr[32]; fread(hdr,1,32,gf);
    fseek(gf,0,SEEK_END); long fs=ftell(gf);
    uint8_t* ct=(uint8_t*)malloc(fs-32);
    fseek(gf,32,SEEK_SET); fread(ct,1,fs-32,gf); fclose(gf);
    uint8_t firstblock[16]; memcpy(firstblock,ct,16);
    size_t lim=(size_t)ts-32;
    size_t start=0,end=lim;
    if(argc>=3){ start=(size_t)strtoull(argv[1],0,10); end=(size_t)strtoull(argv[2],0,10); }
    size_t i; int found=0;
    for(i=start;i<end;i++){
        g_i=i;
        AES_ctx ctx; AES_init_ctx(&ctx, buf+i);
        uint8_t blk[16]; memcpy(blk,firstblock,16);
        AES_ECB_decrypt_block(&ctx, blk);
        if(blk[0]=='G'&&blk[1]=='D'&&blk[2]=='S'&&blk[3]=='C'){ found++; printf("HIT %llu\n",(unsigned long long)i); }
    }
    printf("range %llu..%llu done found=%d\n",(unsigned long long)start,(unsigned long long)end,found);
    return 0;
}
