#include "blockchain.h"

void generate_users(int n, Blockchain &new_bc);
void generate_transactions(int n, Blockchain &new_bc);

int main()
{
  string user_input;
  cout<<"Starting blockchain...";
  cout << "Comands:\n'Generate first block' - generates users with starting balanaces and random transactions. Puts starting balance utxos in first block and creats it";
  cin >> user_input;
  Blockchain new_bc;
  generate_users(10, new_bc);
  
  generate_transactions(1000, new_bc);
  //new_bc.print_transactions();
  new_bc.generate_first_block();
  new_bc.print_users();
  new_bc.print_block(0);
  new_bc.create_new_block();
  //new_bc.print_block(1);
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