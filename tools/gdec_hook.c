/* gdec_hook.c — GDEC decryption-key capture DLL for Backpack Battles research.
 *
 * Hooks the custom GDEC decrypt function at RVA 0x1621820 (handles both .gde
 * scripts and encrypted CSVs). Entry is patched with a 12-byte absolute jump
 * (mov rax,imm64; jmp rax) + 3 NOPs; the 15 stolen prologue bytes are copied
 * verbatim into a trampoline (they are all non-RIP-relative) followed by an
 * absolute jump back.
 *
 * The naked stub (hand-assembled bytes, no compiler dependency) preserves
 * RCX/RDX/R8/R9 (the original arguments), passes r8 (key Vector<uint8_t> ref)
 * and rcx (this) to the C dumper, then jumps to the trampoline.
 *
 * The dumper logs 32-byte key candidates from every plausible layout
 * (direct / +0x20 / dereferenced pointers), VirtualQuery-guarded, deduped.
 * Offline validation (GDSC magic + MD5) picks the real keys.
 *
 * Build:  gcc -O2 -shared -o gdec_hook.dll gdec_hook.c
 */
#include <windows.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define TARGET_RVA   0x1621820
#define PROLOGUE_LEN 15
static const char* LOG_PATH = "C:/Users/Windows/AppData/Local/Temp/bp_hook_candidates.log";
static const char* STAT_PATH = "C:/Users/Windows/AppData/Local/Temp/bp_hook_stats.txt";

static void* g_stub = NULL;
static void* g_tramp = NULL;
static CRITICAL_SECTION g_cs;
static FILE* g_log = NULL;
static volatile LONG g_calls = 0;
static volatile LONG g_logged = 0;
static unsigned char g_seen[256][32];
static int g_nseen = 0;
static unsigned char g_seen_csv[256][32];
static int g_nseen_csv = 0;

/* ---------------- safe read ---------------- */
static int safe_read(uintptr_t addr, void* out, size_t n) {
    MEMORY_BASIC_INFORMATION mbi;
    if (!addr) return 0;
    if (!VirtualQuery((LPCVOID)addr, &mbi, sizeof(mbi))) return 0;
    if (mbi.State != MEM_COMMIT) return 0;
    DWORD p = mbi.Protect & 0xFF;
    if (p == PAGE_NOACCESS || (mbi.Protect & PAGE_GUARD)) return 0;
    if ((uintptr_t)mbi.BaseAddress + mbi.RegionSize < addr + n) return 0;
    memcpy(out, (const void*)addr, n);
    return 1;
}

/* ---------------- candidate logging ---------------- */
static void log_candidate(const char* tag, uintptr_t src, const unsigned char* key32) {
    unsigned char (*seen)[32] = g_seen;
    int* nseen = &g_nseen;
    int is_csv = 0;
    /* tag "c" rows use a separate dedupe pool so both pools stay full */
    if (tag[0] == 'c') { seen = g_seen_csv; nseen = &g_nseen_csv; is_csv = 1; }
    (void)is_csv;
    EnterCriticalSection(&g_cs);
    for (int i = 0; i < *nseen; i++)
        if (!memcmp(seen[i], key32, 32)) { LeaveCriticalSection(&g_cs); return; }
    if (*nseen < 256) memcpy(seen[*nseen], key32, 32), (*nseen)++;
    if (g_log) {
        fprintf(g_log, "%s src=%llx key=", tag, (unsigned long long)src);
        for (int i = 0; i < 32; i++) fprintf(g_log, "%02x", key32[i]);
        fprintf(g_log, "\n");
        fflush(g_log);
    }
    g_logged++;
    LeaveCriticalSection(&g_cs);
}

/* probe one location: log its 32 bytes as a candidate */
static void probe(const char* tag, uintptr_t src, uintptr_t addr) {
    unsigned char buf[32];
    if (safe_read(addr, buf, 32))
        log_candidate(tag, src, buf);
}

/* called from the naked stub; args = (r8, rcx) of the hooked function */
void __cdecl dump_keys(unsigned char* keyvec_ref, unsigned char* this_ptr) {
    InterlockedIncrement(&g_calls);
    if ((g_calls & 0x3FF) == 0) {
        FILE* f = fopen(STAT_PATH, "w");
        if (f) { fprintf(f, "calls=%ld logged=%ld\n", g_calls, g_logged); fclose(f); }
    }
    if (g_calls > 200000 || g_logged > 900) return;

    uintptr_t kv = (uintptr_t)keyvec_ref, th = (uintptr_t)this_ptr;
    /* direct spans */
    probe("k+00", kv, kv);
    probe("k+20", kv, kv + 0x20);
    probe("t+20", th, th + 0x20);
    /* dereferenced pointers at common vector/context offsets */
    uintptr_t ptrs[8];
    for (int i = 0; i < 8; i++) {
        if (!safe_read(kv + 8 * i, &ptrs[i], sizeof(void*))) continue;
        if (ptrs[i] < 0x10000 || ptrs[i] > 0x7FFFFFFEFFFF) continue;
        probe("kd", ptrs[i], ptrs[i]);
        probe("kd2", ptrs[i], ptrs[i] + 0x10);
    }
    uintptr_t tp = 0;
    if (safe_read(th + 0x20, &tp, sizeof(void*)) && tp > 0x10000 && tp < 0x7FFFFFFEFFFF)
        probe("td", tp, tp);
}

/* ---------------- hand-assembled naked stub ---------------- */
/* pushes r15,rcx,rdx,r8,r9; shadow; rcx=keyvec([rsp+0x28]), rdx=this([rsp+0x38]);
   calls dump; restores; absolute-jumps to trampoline. */
static void build_stub(uint8_t* b, uintptr_t dump_fn, uintptr_t tramp) {
    int i = 0;
    b[i++] = 0x41; b[i++] = 0x57;                       /* push r15 */
    b[i++] = 0x51;                                      /* push rcx */
    b[i++] = 0x52;                                      /* push rdx */
    b[i++] = 0x41; b[i++] = 0x50;                       /* push r8  */
    b[i++] = 0x41; b[i++] = 0x51;                       /* push r9  */
    b[i++] = 0x48; b[i++] = 0x83; b[i++] = 0xEC; b[i++] = 0x20;  /* sub rsp,0x20 */
    b[i++] = 0x48; b[i++] = 0x8B; b[i++] = 0x4C; b[i++] = 0x24; b[i++] = 0x28; /* mov rcx,[rsp+28h] */
    b[i++] = 0x48; b[i++] = 0x8B; b[i++] = 0x54; b[i++] = 0x24; b[i++] = 0x38; /* mov rdx,[rsp+38h] */
    b[i++] = 0x45; b[i++] = 0x31; b[i++] = 0xC0;        /* xor r8d,r8d */
    b[i++] = 0x45; b[i++] = 0x31; b[i++] = 0xC9;        /* xor r9d,r9d */
    b[i++] = 0x48; b[i++] = 0xB8;                       /* mov rax, imm64 */
    memcpy(b + i, &dump_fn, 8); i += 8;
    b[i++] = 0xFF; b[i++] = 0xD0;                       /* call rax */
    b[i++] = 0x48; b[i++] = 0x83; b[i++] = 0xC4; b[i++] = 0x20;  /* add rsp,0x20 */
    b[i++] = 0x41; b[i++] = 0x59;                       /* pop r9 */
    b[i++] = 0x41; b[i++] = 0x58;                       /* pop r8 */
    b[i++] = 0x5A;                                      /* pop rdx */
    b[i++] = 0x59;                                      /* pop rcx */
    b[i++] = 0x41; b[i++] = 0x5F;                       /* pop r15 */
    b[i++] = 0x48; b[i++] = 0xB8;                       /* mov rax, imm64 */
    memcpy(b + i, &tramp, 8); i += 8;
    b[i++] = 0xFF; b[i++] = 0xE0;                       /* jmp rax */
}

static DWORD WINAPI setup(LPVOID arg) {
    (void)arg;
    HMODULE base = GetModuleHandleA(NULL);
    uintptr_t target = (uintptr_t)base + TARGET_RVA;
    DWORD pid = GetCurrentProcessId();

    InitializeCriticalSection(&g_cs);
    g_log = fopen(LOG_PATH, "a");
    if (g_log) {
        fprintf(g_log, "=== attach pid=%lu target=%llx ===\n", pid, (unsigned long long)target);
        fflush(g_log);
    }

    unsigned char orig[PROLOGUE_LEN];
    memcpy(orig, (const void*)target, PROLOGUE_LEN);

    /* trampoline: stolen bytes + mov rax,(target+15); jmp rax */
    g_tramp = VirtualAlloc(NULL, 64, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    uint8_t* t = (uint8_t*)g_tramp;
    memcpy(t, orig, PROLOGUE_LEN);
    int i = PROLOGUE_LEN;
    t[i++] = 0x48; t[i++] = 0xB8;
    uintptr_t back = target + PROLOGUE_LEN;
    memcpy(t + i, &back, 8); i += 8;
    t[i++] = 0xFF; t[i++] = 0xE0;

    /* stub */
    g_stub = VirtualAlloc(NULL, 128, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    build_stub((uint8_t*)g_stub, (uintptr_t)&dump_keys, (uintptr_t)g_tramp);

    /* patch entry: mov rax,stub; jmp rax + 3 nop = 15 bytes */
    DWORD oldp;
    VirtualProtect((LPVOID)target, PROLOGUE_LEN, PAGE_EXECUTE_READWRITE, &oldp);
    uint8_t patch[PROLOGUE_LEN];
    patch[0] = 0x48; patch[1] = 0xB8;
    memcpy(patch + 2, &g_stub, 8);
    patch[10] = 0xFF; patch[11] = 0xE0;
    patch[12] = patch[13] = patch[14] = 0x90;
    memcpy((void*)target, patch, PROLOGUE_LEN);
    VirtualProtect((LPVOID)target, PROLOGUE_LEN, oldp, &oldp);
    FlushInstructionCache(GetCurrentProcess(), (LPCVOID)target, PROLOGUE_LEN);
    FlushInstructionCache(GetCurrentProcess(), (LPCVOID)g_stub, 128);
    FlushInstructionCache(GetCurrentProcess(), (LPCVOID)g_tramp, 64);

    FILE* s = fopen(STAT_PATH, "w");
    if (s) { fprintf(s, "hooked pid=%lu target=%llx stub=%p tramp=%p\n",
                     pid, (unsigned long long)target, g_stub, g_tramp); fclose(s); }
    return 0;
}

BOOL APIENTRY DllMain(HMODULE h, DWORD reason, LPVOID rsv) {
    (void)h; (void)rsv;
    if (reason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(h);
        CreateThread(NULL, 0, setup, NULL, 0, NULL);
    }
    return TRUE;
}

/* optional explicit init entry: LoadLibrary("...gdec_hook.dll") then call this
   (used by injectors that cannot rely on DllMain-time environment) */
__declspec(dllexport) void __cdecl arm_hook(void) {
    CreateThread(NULL, 0, setup, NULL, 0, NULL);
}
