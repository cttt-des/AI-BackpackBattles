#include "preflight_screen_snapshot.hpp"
#include <cassert>
#include <iostream>
namespace gd {void native_dispatch_chain_hit(unsigned){}}
int main(){register_gen_syms();gd::BattleCtx c;c.native_resolved_dispatch=true;c.native_resolved_audit=true;Gd__gd_core__PlatinCustomerCard item(&c);gd::GdVal unused;(void)gd::try_native_resolved_property(c,&item,SYM_GEN_ctx_3,unused);gd::GdStr malformed{"onCombatStart",13u,0u};gd::GdVal name=gd::GdVal::from_str(&malformed);auto original=item.fn__hasBehaviorMethod(&name,1);auto prototype=candidate__hasBehaviorMethod(item,&name,1);assert(original.kind==gd::GdVal::Kind::Bool && !original.b && prototype.kind==gd::GdVal::Kind::Bool && prototype.b);std::cout<<"{\"reproduced\":true,\"original\":false,\"pre_hash_guard_prototype\":true,\"boundary\":\"String bytes match but stored hash differs\"}\n";}
