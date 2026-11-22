#include "native_inline_dispatch.hpp"
#include "frozen_timer_packed_abi.hpp"
#include <cassert>
#include <cstdint>
#include <iostream>
#ifdef GD_TIMER_CLOSED
extern "C" int gd_diag_native_timer_registry_closed();
extern "C" int gd_diag_native_timer_closed_mode();
#endif
static uint64_t run_empty(){PackedSide a{};a.char_class=0;a.health=a.stamina=a.base_max_stamina=a.regen=a.snapshot_stamina=-1;
    BattleOptions options{};options.seed=42;options.round_id=1;options.custom_health_multiplier=100;options.max_ticks=1;options.max_time=1;
    BattleResult result{};gd_sim_run_one(&a,&a,&options,&result);uint64_t h=1469598103934665603ULL;const auto* bytes=reinterpret_cast<const unsigned char*>(&result);for(unsigned i=0;i<sizeof(result);++i)h=(h^bytes[i])*1099511628211ULL;return h;}
int main(){gd_sim_init();gd_sim_register_character(0,"closed_test",100,0,0,0);
#ifdef GD_TIMER_CLOSED
    assert(gd_diag_native_timer_registry_closed()==1);gd::BattleCtx ordinary;assert(!ordinary.native_timer_watch.closed_world);
#endif
    const auto first=run_empty();
#ifdef GD_TIMER_CLOSED
    assert(gd_diag_native_timer_closed_mode()==1);
#endif
    const gd::GdClassMeta custom{65004,"ExternalTimerRegistration","res://external/Timer.gd"};gd::register_class(&custom);
#ifdef GD_TIMER_CLOSED
    assert(gd_diag_native_timer_registry_closed()==0);
#endif
    const auto second=run_empty();
#ifdef GD_TIMER_CLOSED
    assert(gd_diag_native_timer_closed_mode()==0);
#endif
    gd_sim_reset_registry();gd_sim_register_character(0,"closed_test",100,0,0,0);const auto third=run_empty();
#ifdef GD_TIMER_CLOSED
    assert(gd_diag_native_timer_registry_closed()==0 && gd_diag_native_timer_closed_mode()==0);
#endif
    std::cout<<"{\"passed\":true,\"result_hashes\":[\""<<std::hex<<first<<"\",\""<<second<<"\",\""<<third<<"\"],\"result_bytes\":"<<std::dec<<sizeof(BattleResult)<<"}\n";
}
