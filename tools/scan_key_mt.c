/* scan_key_mt.c - multithreaded raw GDEC script-key scanner.
 * Enumerates committed memory of a (suspended) process, reads it in chunks,
 * and for every 32-byte window AES-256-ECB decrypts the first GDEC ciphertext
 * block; windows yielding "GDSC" plaintext are written out as candidates.
 *
 * Build:  gcc -O2 -o scan_key_mt.exe scan_key_mt.c aes256.c
 * Usage:  scan_key_mt.exe <pid> <gde_file> <out_candidates_file> [threads]
 */
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "aes256.h"

#define CHUNK (32u << 20)     /* 32 MB read chunks */
#define OVERLAP 31
#define NTHREADS_DEF 8

static uint8_t g_firstblock[16];
static char g_outpath[MAX_PATH];
static CRITICAL_SECTION g_cs;
static FILE* g_out = NULL;
static volatile LONG g_found = 0;
HANDLE g_target = NULL;   /* target process, set in main */

typedef struct { uintptr_t base; size_t size; } Job;
static Job* g_jobs = NULL;
static size_t g_njobs = 0, g_capjobs = 0, g_next = 0;
static volatile LONG g_jobs_done = 0, g_jobs_total = 0;

static void add_job(uintptr_t base, size_t size) {
    if (g_njobs == g_capjobs) {
        g_capjobs = g_capjobs ? g_capjobs * 2 : 1024;
        g_jobs = (Job*)realloc(g_jobs, g_capjobs * sizeof(Job));
    }
    g_jobs[g_njobs].base = base; g_jobs[g_njobs].size = size; g_njobs++;
}

static DWORD WINAPI worker(LPVOID arg) {
    (void)arg;
    uint8_t* buf = (uint8_t*)malloc(CHUNK + OVERLAP);
    for (;;) {
        EnterCriticalSection(&g_cs);
        if (g_next >= g_njobs) { LeaveCriticalSection(&g_cs); break; }
        Job j = g_jobs[g_next++];
        LeaveCriticalSection(&g_cs);

        uintptr_t addr = j.base;
        size_t remaining = j.size;
        while (remaining > 32) {
            size_t take = remaining < CHUNK ? remaining : CHUNK;
            SIZE_T got = 0;
            if (!ReadProcessMemory(g_target, (LPCVOID)addr, buf, take, &got) || got < 32) break;
            size_t lim = got - 32;
            for (size_t i = 0; i <= lim; i++) {
                AES_ctx ctx;
                AES_init_ctx(&ctx, buf + i);
                uint8_t blk[16];
                memcpy(blk, g_firstblock, 16);
                AES_ECB_decrypt_block(&ctx, blk);
                if (blk[0]=='G' && blk[1]=='D' && blk[2]=='S' && blk[3]=='C') {
                    EnterCriticalSection(&g_cs);
                    fprintf(g_out, "%llx ", (unsigned long long)(addr + i));
                    for (int k = 0; k < 32; k++) fprintf(g_out, "%02x", buf[i + k]);
                    fprintf(g_out, "\n"); fflush(g_out);
                    InterlockedIncrement(&g_found);
                    LeaveCriticalSection(&g_cs);
                }
            }
            addr += take - OVERLAP;
            if (remaining <= take - OVERLAP) break;
            remaining -= take - OVERLAP;
        }
        EnterCriticalSection(&g_cs);
        InterlockedIncrement(&g_jobs_done);
        LONG done = g_jobs_done, tot = g_jobs_total;
        LeaveCriticalSection(&g_cs);
        if ((done & 15) == 0 || done == tot) {
            EnterCriticalSection(&g_cs);
            printf("  progress %ld/%ld jobs\n", done, tot);
            fflush(stdout);
            LeaveCriticalSection(&g_cs);
        }
    }
    free(buf);
    return 0;
}

int main(int argc, char** argv) {
    if (argc < 4) { printf("usage: %s <pid> <gde_file> <out> [threads] [max_region_MB]\n", argv[0]); return 1; }
    DWORD pid = (DWORD)strtoul(argv[1], 0, 10);
    int nthr = argc > 4 ? atoi(argv[4]) : NTHREADS_DEF;
    SIZE_T maxreg = argc > 5 ? (SIZE_T)atoi(argv[5]) << 20 : 0;  /* 0 = no limit */

    FILE* gf = fopen(argv[2], "rb");
    if (!gf) { printf("cannot open gde\n"); return 1; }
    fseek(gf, 32, SEEK_SET);
    fread(g_firstblock, 1, 16, gf);
    fclose(gf);
    strcpy(g_outpath, argv[3]);

    g_target = OpenProcess(PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, FALSE, pid);
    if (!g_target) { printf("OpenProcess failed err=%lu\n", GetLastError()); return 1; }

    /* enumerate committed regions, split into chunk jobs */
    MEMORY_BASIC_INFORMATION mbi;
    uintptr_t addr = 0x10000;
    size_t totalbytes = 0;
    while (addr < 0x7FFFFFFF0000) {
        if (!VirtualQueryEx(g_target, (LPCVOID)addr, &mbi, sizeof(mbi))) break;
        if (mbi.State == MEM_COMMIT && !(mbi.Protect & PAGE_GUARD) &&
            (mbi.Protect & (PAGE_READONLY | PAGE_READWRITE | PAGE_EXECUTE_READ |
                            PAGE_EXECUTE_READWRITE | PAGE_WRITECOPY)) &&
            (!maxreg || mbi.RegionSize <= maxreg)) {
            uintptr_t base = (uintptr_t)mbi.BaseAddress;
            SIZE_T size = mbi.RegionSize;
            totalbytes += size;
            uintptr_t p = base;
            SIZE_T left = size;
            while (left > 32) {
                SIZE_T take = left < CHUNK ? left : CHUNK;
                add_job(p, take);
                if (left <= take - OVERLAP) break;
                p += take - OVERLAP;
                left -= take - OVERLAP;
            }
        }
        uintptr_t nxt = (uintptr_t)mbi.BaseAddress + mbi.RegionSize;
        if (nxt <= addr) break;
        addr = nxt;
    }
    g_jobs_total = (LONG)g_njobs;
    printf("target pid=%lu regions_jobs=%zu bytes=%.0f MB threads=%d\n",
           pid, g_njobs, totalbytes / 1e6, nthr);

    g_out = fopen(g_outpath, "w");
    if (!g_out) { printf("cannot open out\n"); return 1; }
    InitializeCriticalSection(&g_cs);

    SYSTEMTIME st; GetLocalTime(&st);
    printf("start %02d:%02d:%02d\n", st.wHour, st.wMinute, st.wSecond);
    HANDLE th[MAXIMUM_WAIT_OBJECTS];
    int n = nthr > MAXIMUM_WAIT_OBJECTS ? MAXIMUM_WAIT_OBJECTS : nthr;
    for (int i = 0; i < n; i++) th[i] = CreateThread(NULL, 0, worker, NULL, 0, NULL);
    WaitForMultipleObjects(n, th, TRUE, INFINITE);
    GetLocalTime(&st);
    printf("done %02d:%02d:%02d candidates=%ld\n", st.wHour, st.wMinute, st.wSecond, g_found);
    fclose(g_out);
    DeleteCriticalSection(&g_cs);
    CloseHandle(g_target);
    free(g_jobs);
    return 0;
}
