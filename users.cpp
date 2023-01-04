#include "blockchain.h"

void Blockchain::create_user(const string& name) {
    long current_time = get_current_time();
    string hashed_data = name + to_string(current_time);
    string public_key = convert(hashed_data);
    user new_user {name, public_key, current_time};
    generated_users.push_back(new_user);
}

vector<Blockchain::user> Blockchain::get_users()
{
  return generated_users;
}

void Blockchain::print_users()
{
  cout << "Users:\n";
  for (auto u : generated_users)
  {
    cout << u.name << '\n';
    cout << u.public_key << '\n';
    cout << u.time_created << '\n';
    //cout << u.time_created << '\n';
  }
}

int Blockchain::get_user_utx_amount(int &availabe_funds)
{
  return 0;
}