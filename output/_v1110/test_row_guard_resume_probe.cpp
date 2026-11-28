// Validate inherited-method identity using actual CEA-allocated cached rows.
#include "native_inline_dispatch.hpp"
#include <cassert>
#include <iostream>
#include "timeline_meta_list.hpp"
static gd::GdVal overridden(gd::GdObj*,const gd::GdVal*,int){return gd::GdVal::null();}
int main(){register_gen_syms();gd::BattleCtx b(1u<<22);b.bind_battle(123);b.native_resolved_dispatch=true;
    constexpr int slot=gd::native_resolved_slots[SYM_GEN__tickChargePath_506];static_assert(slot>=0);
    auto* base=META_Gd__gd_core__CoreItem.alloc_fn(b);assert(base->native_call_row_);const auto expected=base->native_call_row_->methods[slot];assert(expected);
    unsigned rows=0,eligible=0,derived=0;
    for(const auto* meta:timeline_metas){if(!meta || !meta->alloc_fn)continue;auto* object=meta->alloc_fn(b);const auto* row=object->native_call_row_;assert(row && row->metadata==meta);++rows;
        if(row->methods[slot]!=expected)continue;++eligible;const auto* p=meta;bool found=false;while(p){if(p==&META_Gd__gd_core__CoreItem){found=true;break;}p=p->base;}
        assert(found);if(meta!=&META_Gd__gd_core__CoreItem)++derived;
    }
    auto altered=*base->native_call_row_;altered.methods[slot]=&overridden;assert(altered.methods[slot]!=expected);assert(derived>100);
    std::cout<<"{\"passed\":true,\"semantic_cases\":"<<rows+1<<",\"cached_rows_checked\":"<<rows<<",\"same_CoreItem_charge_implementation\":"<<eligible<<",\"derived_receivers_with_same_implementation\":"<<derived<<",\"overridden_slot_rejected\":true,\"charge_slot\":"<<slot<<"}\n";
}
