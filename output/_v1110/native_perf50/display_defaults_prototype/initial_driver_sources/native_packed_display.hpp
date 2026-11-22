#pragma once
#include "gd_rt.hpp"
struct Gd__gd_core__CoreCharacter;

namespace gd {
// Used only by the owned PackedSide bridge, after startBattle. Ordinary C++
// callers do not acquire a scope. Canonical arrays remain independently mutable.
class NativePackedDisplayScope {
public:
    NativePackedDisplayScope(BattleCtx&,Gd__gd_core__CoreCharacter*,Gd__gd_core__CoreCharacter*);
    ~NativePackedDisplayScope();
    NativePackedDisplayScope(const NativePackedDisplayScope&)=delete;
    NativePackedDisplayScope& operator=(const NativePackedDisplayScope&)=delete;
private:
    BattleCtx* context_;
    uint64_t version_=0,epoch_=0;
    NativePackedDisplayScope* previous_;
    static thread_local NativePackedDisplayScope* current_;
    friend uint64_t native_default_display_version(BattleCtx&);
    friend void native_default_display_field_changed(BattleCtx*);
};
uint64_t native_default_display_version(BattleCtx&);
void native_default_display_field_changed(BattleCtx*);
void native_default_display_hit(unsigned,uint64_t amount=1);

// Rechecked for each owner, including the original-scan recovery suffix.
// A phase-constant true flag would miss writes in an earlier owner's callback.
inline bool native_default_display_valid(const BattleCtx& ctx,uint64_t version,uint64_t epoch) {
    const auto& w=ctx.native_timer_watch;
    return version && ctx.gid_epoch==epoch && w.version==version && w.enabled &&
        w.closed_world && w.usable && !w.depth && native_timer_registry_closed();
}
}
