/* scan_key.c - locate the 32-byte GDEC AES-256 script key.
 *
 * Strategy: for every 32-byte window in the target (a file, or a suspended
 * process's committed memory), treat the window as an AES-256-ECB key and
 * decrypt the FIRST block of a known GDEC ciphertext (Combat.gde). If the
 * result begins with "GDSC" the window is a candidate key. Candidates are
 * written to <out> as "<location> <keyhex>" lines for MD5 verification.
 *
 * Usage:
 *   scan_key file <target_file> <gde_file> <out_candidates>
 *   scan_key <pid>            <gde_file> <out_candidates>
 */
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <psapi.h>
#include "aes256.h"

/* Returns: 0=no, 1=AES-256 (32-byte win). Godot scripts use AES-256-ECB
 * with the 32-byte key used directly (see core/io/file_access_encrypted.cpp). */
static int try_window(const uint8_t* win, const uint8_t* firstblock){
    AES_ctx ctx; uint8_t blk[16];
    AES_init_ctx(&ctx, win);
    memcpy(blk, firstblock, 16); AES_ECB_decrypt_block(&ctx, blk);
    if(blk[0]=='G'&&blk[1]=='D'&&blk[2]=='S'&&blk[3]=='C') return 1;
    return 0;
}

static int scan_buffer(const uint8_t* buf, SIZE_T size, const uint8_t* firstblock,
                       FILE* out, const char* locprefix, uint64_t locbase, int* found, SIZE_T stride){
    if(size < 32) return 0;
    if(stride < 1) stride = 1;
    SIZE_T lim = size - 32;
    SIZE_T i;
    char locbuf[32];
    for(i=0;i<lim;i+=stride){
        if((i & 0xffffff) == 0){
            fprintf(stderr,"  progress %llu/%llu found=%d\n",(unsigned long long)i,(unsigned long long)lim,*found);
            fflush(stderr);
        }
        int t = try_window(buf+i, firstblock);
        if(t==1){
            const uint8_t* kp = buf+i; int klen=32;
            if(locprefix){
                snprintf(locbuf,sizeof(locbuf),"%s+%llx", locprefix, (unsigned long long)(locbase+i));
            } else {
                snprintf(locbuf,sizeof(locbuf),"%llx", (unsigned long long)(locbase+i));
            }
            fprintf(out, "%s 1:", locbuf);
            int j; for(j=0;j<klen;j++) fprintf(out,"%02x", kp[j]);
            fprintf(out, "\n");
            fflush(out);
            (*found)++;
            if(*found >= 50){ fprintf(stderr,"  enough candidates, stopping\n"); return 1; }
        }
    }
    return 1;
}

int main(int argc, char** argv){
    if(argc<4){ printf("usage:\n  %s file <target_file> <gde_file> <out>\n  %s <pid> <gde_file> <out>\n", argv[0], argv[0]); return 1; }
    const char* gde;
    const char* outp;
    if(strcmp(argv[1],"file")==0){ gde=argv[3]; outp=argv[4]; }
    else if(strcmp(argv[1],"module")==0){ gde=argv[3]; outp=argv[4]; }
    else { gde=argv[2]; outp=argv[3]; }

    FILE* gf=fopen(gde,"rb");
    if(!gf){ printf("cannot open gde %s\n", gde); return 1; }
    uint8_t hdr[32];
    if(fread(hdr,1,32,gf)!=32){ printf("gde too small\n"); fclose(gf); return 1; }
    if(memcmp(hdr,"GDEC",4)!=0){ printf("gde missing GDEC magic\n"); fclose(gf); return 1; }
    fseek(gf,0,SEEK_END); long fs=ftell(gf);
    uint8_t* ct=(uint8_t*)malloc(fs-32);
    fseek(gf,32,SEEK_SET); fread(ct,1,fs-32,gf); fclose(gf);
    uint8_t firstblock[16]; memcpy(firstblock,ct,16);

    FILE* out=fopen(outp,"w");
    if(!out){ printf("cannot open out %s\n", outp); free(ct); return 1; }

    int found=0;

    if(strcmp(argv[1],"file")==0){
        const char* target=argv[2];
        FILE* tf=fopen(target,"rb");
        if(!tf){ printf("cannot open target %s\n", target); fclose(out); free(ct); return 1; }
        fseek(tf,0,SEEK_END); long ts=ftell(tf); fseek(tf,0,SEEK_SET);
        uint8_t* buf=(uint8_t*)malloc(ts);
        if(fread(buf,1,ts,tf)==(size_t)ts){
            fprintf(stderr,"scanning file %s (%ld bytes)\n", target, ts);
            scan_buffer(buf, (SIZE_T)ts, firstblock, out, "file", 0, &found, 1);
        }
        free(buf); fclose(tf);
    } else if(strcmp(argv[1],"module")==0){
        DWORD pid=strtoul(argv[2],0,10);
        HANDLE h=OpenProcess(PROCESS_VM_READ|PROCESS_QUERY_INFORMATION, FALSE, pid);
        if(!h){ printf("OpenProcess(%lu) failed (run as admin?)\n", pid); fclose(out); free(ct); return 1; }
        HMODULE mods[1024]; DWORD needed=0;
        if(!EnumProcessModules(h, mods, sizeof(mods), &needed)){
            printf("EnumProcessModules failed\n"); CloseHandle(h); fclose(out); free(ct); return 1;
        }
        DWORD nmod=needed/sizeof(HMODULE);
        int scanned=0;
        for(DWORD m=0; m<nmod; m++){
            MODULEINFO mi; char mname[MAX_PATH]={0};
            if(!GetModuleInformation(h, mods[m], &mi, sizeof(mi))) continue;
            GetModuleBaseNameA(h, mods[m], mname, sizeof(mname));
            /* only scan the main game module image */
            if(_stricmp(mname,"BackpackBattles.exe")!=0) continue;
            SIZE_T size=(SIZE_T)mi.SizeOfImage;
            if(size<32 || size>0x8000000) continue;
            uint8_t* buf=(uint8_t*)malloc(size);
            SIZE_T rd=0;
            if(ReadProcessMemory(h,(void*)mi.lpBaseOfDll,buf,size,&rd) && rd>32){
                fprintf(stderr,"scanning module %s base=%p size=%llu\n", mname,
                        (void*)mi.lpBaseOfDll, (unsigned long long)rd);
                scan_buffer(buf, rd, firstblock, out, "module", (uint64_t)(uintptr_t)mi.lpBaseOfDll, &found, 1);
                scanned++;
            }
            free(buf);
        }
        if(scanned==0) fprintf(stderr,"no main module scanned\n");
        CloseHandle(h);
    } else {
        DWORD pid=strtoul(argv[1],0,10);
        HANDLE h=OpenProcess(PROCESS_VM_READ|PROCESS_QUERY_INFORMATION, FALSE, pid);
        if(!h){ printf("OpenProcess(%lu) failed (run as admin?)\n", pid); fclose(out); free(ct); return 1; }
        MEMORY_BASIC_INFORMATION mbi;
        uintptr_t addr=0x10000;
        uintptr_t maxaddr=0x7fffffffffffULL;
        while(addr<maxaddr){
            SIZE_T got=VirtualQueryEx(h,(void*)addr,&mbi,sizeof(mbi));
            if(!got){ addr=(addr+0x1000)&~(SIZE_T)0xfff; if(!addr) break; continue; }
            uintptr_t base=(uintptr_t)mbi.BaseAddress;
            SIZE_T size=mbi.RegionSize;
            if(mbi.State==MEM_COMMIT &&
               (mbi.Protect & (PAGE_READONLY|PAGE_READWRITE|PAGE_EXECUTE_READ)) &&
               size>0 && size<0x80000000){
                uint8_t* buf=(uint8_t*)malloc(size);
                SIZE_T rd=0;
                if(ReadProcessMemory(h,(void*)base,buf,size,&rd) && rd>32){
                    /* runtime key is heap-allocated and 16-byte aligned -> stride 16 */
                    scan_buffer(buf, rd, firstblock, out, NULL, (uint64_t)base, &found, 16);
                    if(found >= 50) { free(buf); break; }
                }
                free(buf);
            }
            addr=base+size;
            if(!addr) break;
        }
        CloseHandle(h);
    }

    fclose(out);
    free(ct);
    printf("SCAN_DONE candidates=%d\n", found);
    return 0;
}
