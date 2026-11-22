extern "C" {

struct PackedEffect {
    int16_t trigger_type;
    int16_t stack_type;
};

struct PackedAffectedGroup {
    int32_t color;
    uint16_t count;
    uint16_t offset;  // offset into side.cells_xy
};

struct PackedItem {
    int32_t item_id;
    int32_t rotation;
    int8_t crafted;  // -1 unset, 0 false, 1 true
    int8_t storage;  // 0 placed, 1 storage (skip)
    int16_t charge_frame_x;
    int16_t charge_frame_y;
    uint16_t n_occupied;
    uint16_t occupied_off;   // index into cells_xy (pairs)
    uint16_t n_collision;
    uint16_t collision_off;  // index into cells_xy (pairs)
    uint16_t n_affected_groups;
    uint16_t affected_group_off;  // index into affected_groups
    uint8_t n_gems;
    uint8_t n_effects;
    int16_t n_sockets;   // -1 = 未指定(回落 proto.sockets)；>=0 = 实例真值(夹具 gem_lens)
    uint16_t n_placement_effects;
    int32_t gems[8];
    PackedEffect effects[8];
};

struct PackedSide {
    int32_t char_class;
    double health;            // < 0 -> from g_chars[char_class]
    double stamina;           // < 0 -> from g_chars[char_class]
    double base_max_stamina;  // < 0 -> use stamina
    double regen;             // < 0 -> from g_chars[char_class]
    double snapshot_stamina;  // < 0 -> unset
    int32_t n_items;
    const PackedItem* items;
    const int16_t* cells_xy;  // pairs (x, y) -> 2 * count int16_t
    const PackedAffectedGroup* affected_groups;
    // 夹具 activation_order 直通（真 Godot 全局链洗牌终序，下标相对输入装配序）。
    // n_activation_order == 0 -> 未指定，走 native_activation_order 自己洗牌。
    int32_t n_activation_order;
    const int32_t* activation_order;
};

struct PackedFlicker {
    double position, speed, length, min_dist, max_dist, min_speed, max_speed;
    int32_t playing;
    int32_t attachment;  // 0 off tree, 1 attached, 2 attached under Opponent
    int32_t loop, n_pending;
    const double* pending;
};

struct ReplayInitial {
    int32_t has_activation_state;
    uint64_t activation_state;
    double player_idle_left;
    double opponent_idle_left;
    int32_t n_flickers;
    const PackedFlicker* flickers;
};

struct PackedReplayBuff {
    int32_t side, type, current, permanent;
};

struct ReplayBuffState {
    int32_t count;
    const PackedReplayBuff* rows;
};

struct ReplayEngineRng {
    int64_t prepare_seed, activate_seed;
    int32_t prepare_offset, activate_offset, label_mode;
};

struct BattleOptions {
    uint64_t seed;
    int32_t round_id;
    int32_t below_master;
    double custom_health_multiplier;
    int32_t label_rng_enabled;
    int32_t native_activation_order;
    int32_t reseed_after_player_character;
    int32_t formal_ev_gate;
    int32_t max_ticks;
    double max_time;  // <= 0 -> keep default (600.0)
    int32_t record_per_item;
    // rng_state 注入（oracle rng_state.txt 直灌）。-1 = 未指定。
    uint64_t rng_state;     // state= 原值（uint64 全值域）
    int32_t has_rng_state;  // 1 = 注入（-1 会与合法负值冲突，故用独立标志）
};

struct BattleResult {
    int32_t player_wins;
    int32_t timed_out;
    int32_t formal_ev_capped;
    double combat_time;
    int32_t ticks;
    int32_t fatigue_counter;
    double player_hp;
    double player_max_hp;
    double player_block;
    double opponent_hp;
    double opponent_max_hp;
    double opponent_block;
    int32_t out_of_stamina_count;
    int32_t event_count;
    double player_damage_dealt;
    double opponent_damage_dealt;
    double player_healing_done;
    double opponent_healing_done;
    int32_t player_crits;
    int32_t opponent_crits;
    int32_t player_misses;
    int32_t opponent_misses;
    int32_t n_placed_items;
    int32_t item_activations[64];
};

void gd_sim_init();
void gd_sim_reset_registry();
void gd_sim_register_character(int32_t,const char*,double,double,double,int32_t);
void gd_sim_run_one(const PackedSide*,const PackedSide*,const BattleOptions*,BattleResult*);
}
