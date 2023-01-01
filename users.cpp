#include "blockchain.h"
#include "hash.cpp"

void Blockchain::create_user(const string& name) {
    long current_time = get_current_time();
    string hashed_data = name + to_string(current_time);
    string public_key = hashing(hashed_data);
    user new_user {name, public_key, current_time};

    generated_users.push_back(new_user);
    get_users();
}

vector<Blockchain::user> Blockchain::get_users()
{
  return generated_users;
}