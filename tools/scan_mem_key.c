/* scan_mem_key.c - scan a suspended process for the 32-byte GDEC script key.
 * For each 32-byte window, AES-256-ECB decrypt the first ciphertext block and
 * keep windows whose plaintext starts with "GDSC". Prints candidate keys (hex).
 * Verification (full MD5) is done by the Python wrapper.
 */
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "aes256.h"

/* ---- main ---- */
int main(int argc, char** argv){
    if(argc<4){ printf("usage: %s <pid> <gde_file> <out_candidates_file>\n", argv[0]); return 1; }
    DWORD pid=strtoul(argv[1],0,10);
    FILE* gf=fopen(argv[2],"rb");
    if(!gf){ printf("cannot open gde\n"); return 1; }
    uint8_t hdr[32];
    fread(hdr,1,32,gf);
    fseek(gf,0,SEEK_END);
    long fs=ftell(gf);
    uint8_t* ct=(uint8_t*)malloc(fs-32);
    fseek(gf,32,SEEK_SET);
    fread(ct,1,fs-32,gf);
    fclose(gf);
    uint8_t firstblock[16];
    memcpy(firstblock,ct,16);

    if(!sbox_inited) init_inv();

    HANDLE h=OpenProcess(PROCESS_VM_READ|PROCESS_QUERY_INFORMATION, FALSE, pid);
    if(!h){ printf("OpenProcess failed\n"); free(ct); return 1; }

    MEMORY_BASIC_INFORMATION mbi;
    uintptr_t addr=0x10000;
    uintptr_t maxaddr=0x7fffffffffffULL;
    FILE* out=fopen(argv[3],"w");
    int found=0;
    while(addr<maxaddr){
        SIZE_T got=VirtualQueryEx(h,(void*)addr,&mbi,sizeof(mbi));
        if(!got) { addr=(addr+0x1000)&~(SIZE_T)0xfff; if(!addr) break; continue; }
        uintptr_t base=(uintptr_t)mbi.BaseAddress;
        SIZE_T size=mbi.RegionSize;
        if(mbi.State==MEM_COMMIT && (mbi.Protect & (PAGE_READONLY|PAGE_READWRITE|PAGE_EXECUTE_READ)) && size>0 && size<0x8000000){
            uint8_t* buf=(uint8_t*)malloc(size);
            SIZE_T rd=0;
            if(ReadProcessMemory(h,(void*)base,buf,size,&rd)){
                SIZE_T lim=rd-32;
                SIZE_T i;
                for(i=0;i<lim;i++){
                    AES_ctx ctx;
                    AES_init_ctx(&ctx, buf+i);
                    uint8_t blk[16];
                    memcpy(blk,firstblock,16);
                    AES_ECB_decrypt_block(&ctx, blk);
                    if(blk[0]=='G'&&blk[1]=='D'&&blk[2]=='S'&&blk[3]=='C'){
                        int j;
                        fprintf(out,"%llx ",(unsigned long long)(base+i));
                        for(j=0;j<32;j++) fprintf(out,"%02x",buf[i+j]);
                        fprintf(out,"\n");
                        fflush(out);
                        found++;
                    }
                }
            }
            free(buf);
        }
        addr=base+size;
        if(!addr) break;
    }
    fclose(out);
    CloseHandle(h);
    free(ct);
    printf("SCAN_DONE candidates=%d\n", found);
    return 0;
}
