#include "blockchain.h"

void generate_users(int n, Blockchain &new_bc);
void generate_transactions(int n, Blockchain &new_bc);

int main()
{
  Blockchain new_bc;
}

void generate_users(int n, Blockchain &new_bc)
{
  for (int i = 0; i < n; i++)
  {
    string name = "name" + to_string(i);
    new_bc.create_user(name);
  }
  
}

void generate_transactions(int n, Blockchain &new_bc)
{
  auto users = new_bc.get_users();
  mt19937 mt;
  auto now = chrono::system_clock::now();
  auto now_t = chrono::system_clock::to_time_t(now);
  mt.seed(now_t);
  uniform_int_distribution<int> users_distributor(0, users.size() - 1);
  uniform_int_distribution<int> value_distributor(1, 1000);

  for (int i = 0; i < n; i++)
  {
    int sender_index = users_distributor(mt);
    int receiver_index = users_distributor(mt);
    string sender = users[sender_index].public_key;
    string receiver = users[receiver_index].public_key;
    int amount = value_distributor(mt);

    new_bc.create_transaction(sender, receiver, amount);
  }
  
}