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

void Blockchain::print_user(int index)
{
  int tx_num = 0;
  cout << "User " << index << " :\n";
  cout << "User name: " << generated_users[index].name << '\n';
  cout << "User public key: " << generated_users[index].public_key << '\n';
  cout << "User transactions:\n";
  for (auto tx : generated_users[index].utx_ids)
  {
    cout << "Transaction "<< tx_num <<" : "<< tx << '\n';
  }
}

int Blockchain::get_user_utx_amount(int availabe_funds, user current_user)
{
  for (auto tx_id : current_user.utx_ids)
  {
    //cout << "user tx_id: " << tx_id << "\n";
    int size = validated_transactions.size();
    for (int i = 0; i < size; i++)
    {
      if (validated_transactions[i].id == tx_id)
      {
        //cout << "user passed first: " << "\n";
        for (auto to_utxo : validated_transactions[i].out)
        {
          if (to_utxo.to == current_user.public_key && to_utxo.unspent == true) 
          {
            //cout << "user passed second: " << "\n";
            availabe_funds += to_utxo.amount;
          }
        }
      } //amount from transactions sent to current user and amount user sent to himself
    }
  }
  return availabe_funds;
}

int Blockchain::get_user_amount()
{
  return generated_users.size();
}