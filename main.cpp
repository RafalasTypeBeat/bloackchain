#include "blockchain.h"

void generate_users(int n, Blockchain &new_bc);
void generate_transactions(int n, Blockchain &new_bc);

int main()
{
  int user_input, index;
  Blockchain new_bc;
  //cout<<"Starting blockchain...";
  cout << "Use numbers for commands: \n*note: you need to generate data and blocks before using other commands.*\n1 'Generate data' - generates users with starting balanaces and random transactions.\n";
  cout << "2 'Generate blocks' - generates blocks until there are no transactions left.\n";
  cout << "3 'Print block' - print chosen block.\n";
  cout << "4 'Print transactions' - print transactions of chosen block.\n";
  cout << "5 'Print user' - print user by index.\n";
  cout << "0 'Exit' - exit the program.\n";
  cin >> user_input;
  if (user_input != 1 && user_input != 2 && user_input != 3 && user_input != 4 && user_input != 5 && user_input != 0) cout << "\n No such command exists! \n ";
  while (user_input != 0)
  {

    if (user_input == 1){
      generate_users(50, new_bc);
      generate_transactions(1000, new_bc);
      cout << "Finished generating users and transactions.\n";
    }
    else if (user_input == 2) {
      cout << "Started mining...\n";
      new_bc.generate_first_block();
      new_bc.mine_blocks();
      cout << "Finished mining blocks.\n";
    }
    else if (user_input == 3)
    {
      cout << "There are " << new_bc.blockchain_height << " blocks. ";
      cout << "Type block index: \n";
      cin >> index;
      if (index > new_bc.blockchain_height) cout << "No such block exists!\n";
      else new_bc.print_block(index);
    }
    else if (user_input == 4)
    {
      cout << "There are " << new_bc.blockchain_height << " blocks. ";
      cout << "Type block index: \n";
      cin >> index;
      if (index > new_bc.blockchain_height) cout << "No such block exists!\n";
      else new_bc.print_transaction(index);
    }
    if (user_input == 5)
    {
      cout << "There are " << new_bc.get_user_amount() << " users. ";
      cout << "Type user index: \n";
      cin >> index;
      if (index > new_bc.get_user_amount()) cout << "No such user exists!\n";
      else new_bc.print_user(index);
    }
    cout << "Command executed. Awaiting new command...\n";
    cin >> user_input;
    if (user_input != 1 && user_input != 2 && user_input != 3 && user_input != 4 && user_input != 5 && user_input != 0) cout << "\n No such command exists! \n ";
  }
  cout << "Program closed\n";
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