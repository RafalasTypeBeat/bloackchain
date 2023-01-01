#include "blockchain.h"
#include "hash.cpp"

long Blockchain::get_current_time() {
    auto now = chrono::system_clock::now();
    auto now_s = chrono::time_point_cast<chrono::seconds>(now);
    auto epoch = now_s.time_since_epoch();
    auto epoch_value = chrono::duration_cast<chrono::seconds>(epoch);
    long epoch_time = epoch_value.count();
    return epoch_time;
    // gets current time
}

void Blockchain::create_user(const string& name) {
    long current_time = get_current_time();
    string val_to_hash = name + to_string(current_time);
    string public_key = hashing(val_to_hash);
    user new_user {name, public_key, current_time};

    generated_users.push_back(new_user);
}