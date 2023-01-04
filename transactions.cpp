#include "blockchain.h"

void Blockchain::print_transactions()
{
  cout << "Transactions:\n";
  for (auto t : generated_transactions)
  {
    cout << "Transaction id: "<< t.id << '\n';
    cout << "From: "<< t.from << '\n';
    cout << "To: "<< t.to << '\n';
    cout << "Amount: "<< t.amount << '\n';
    cout << "Transaction time: "<< t.time << '\n';
    //cout << u.time_created << '\n';
  }
}

void Blockchain::create_transaction(const string& from, const string& to, const int& amount)
{
  long current_time = get_current_time();

  string hashed_data = from + to + to_string(amount) + to_string(current_time);
  string transaction_id = convert(hashed_data);
  transaction new_transacion {transaction_id, from, to, amount, current_time};
  generated_transactions.push_back(new_transacion);
}

vector<string> Blockchain::select_transactions()
{
  auto tx = generated_transactions;
  int size = tx.size();
  int tx_amount = max_block_transactions;
  vector<string> selected_tx;
  auto now = chrono::system_clock::now();
  auto now_t = chrono::system_clock::to_time_t(now);
  mt.seed(now_t);
  uniform_int_distribution<int> transaction_dist(0, INT_MAX);
  auto begin = tx.begin();
  auto end = tx.end();
  //cout << "Selected transactions: ";
  while(tx_amount > 0)
  {
    auto transaction_it = begin;
    advance(transaction_it, transaction_dist(mt) % size);
    selected_tx.push_back(transaction_it->id);
    begin ++;
    -- size;
    -- tx_amount;
    //cout << "transaction id: " << transaction_it->id << "\n";
  }
  validate_transaction(selected_tx);
  return selected_tx;
}

vector<string> Blockchain::validate_transaction(vector<string> &tx)
{
  /*
  paimti kiekviena transaction
  paziureti ar useris kuris siuncia transaction turi utxo tiek vertu
  */
 auto tx_it = tx.begin();  //track current transaction
 for (auto t : tx)
 {
    auto it_t = find_if(generated_transactions.begin(), generated_transactions.end(), [&](const transaction& find_if_tx)
    {
        return find_if_tx.id == t;  //rasti transaction
    });
    transaction found_tx = *it_t;
    string from_id = found_tx.from;
    auto it_u = find_if(generated_users.begin(), generated_users.end(), [&](const user& find_user)
    {
        return find_user.public_key == from_id;  //rasti useri, kuris siunte transaction
    });
    user found_user_from = *it_u;

    auto it_c = find_if(coinbase_transactions.begin(), coinbase_transactions.end(), [&](const transaction& find_coinbase)
    {
        return find_coinbase.to == found_user_from.public_key;  //rasti coinbase transaction userio, kuris sius transaction
    });
    transaction coinbase_transaction = *it_c;  // turima valiuta is coinbase transaction
    int available_funds = coinbase_transaction.amount;
    get_user_utx_amount(available_funds);
    if (found_tx.amount > available_funds) tx.erase(tx_it);
    else tx_it ++;
 }
 return tx;
}