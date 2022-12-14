#include "blockchain.h"

void Blockchain::print_transaction(int index)
{
  cout << "Transactions of block " << index << " :\n";
  for (auto t : blockchain[index].tx)
  {
    cout << "Transaction id: "<< t << '\n';
    for (int i = 0; i < validated_transactions.size(); i++)
    {
      if (validated_transactions[i].id == t)
      {
        cout << "From: "<< validated_transactions[i].from << '\n';
        cout << "To: "<< validated_transactions[i].to << '\n';
        cout << "Amount: "<< validated_transactions[i].amount << '\n';
      }
    }
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
  //cout << "selected transactions\n";
  validate_transaction(selected_tx);
  return selected_tx;
}

vector<string> Blockchain::validate_transaction(vector<string> tx)
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
        return find_if_tx.id == t;  //rasti transaction, kad zinotum kuri useri tikrinti
    });
    transaction found_tx = *it_t;
    string from_id = found_tx.from;
    auto it_u = find_if(generated_users.begin(), generated_users.end(), [&](const user& find_user)
    {
        return find_user.public_key == from_id;  //rasti useri, kuris siunte transaction
    });
    user found_user_from = *it_u;  //reikalinga, kad galetum paduoti get_user_utx amount useri

    int available_funds = 0;
    //cout << "Calculating money\n";
    available_funds += get_user_utx_amount(available_funds, found_user_from);
    //cout << "available funds: " << available_funds;
    //cout << " needed funds: " << found_tx.amount << "\n";
    if (found_tx.amount > available_funds) 
    {
      //cout << "erasing tx ";
      tx.erase(tx_it);
      cout << "erased tx\n";
    }
    else tx_it ++;
 }
 cout << "Validated transactions\n";
 return tx;
}

void Blockchain::update_transactions(vector<string> tx)
{
  transaction new_transaction;
  int collected_amount = 0;
  for (auto t : tx)
  {
    vector<txo> spent_txo;
    auto it_t = find_if(generated_transactions.begin(), generated_transactions.end(), [&](const transaction& find_tx)
      {
          return t == find_tx.id;  //rasti transaction kad updeitinti
      });
    new_transaction = *it_t; // updatinti sita transaction ir tada istrinti is generated_transactions()
    int amount_needed = new_transaction.amount;
    // rasti is kurio utxo paimti eurus
    collected_amount = 0;
    for (int i = 0; i < validated_transactions.size(); i++)
    {
      if (new_transaction.from == validated_transactions[i].to || new_transaction.from == validated_transactions[i].from)
      {
        //cout << "tx passed first; ";
        for (auto to_utxo : validated_transactions[i].out) //paimi tx
        {
          vector<txo>::iterator it_used = validated_transactions[i].out.begin();
          if (to_utxo.to == new_transaction.from && to_utxo.unspent == true)
          {
            //cout << "tx passed second; ";
            collected_amount += to_utxo.amount;
            //cout << "tx amount:" << collected_amount<< "\n";
            to_utxo = *it_used;
            to_utxo.unspent = false;
            spent_txo.push_back(to_utxo);
            if (collected_amount >= amount_needed) 
            {
              //cout << "tx passed third\n";
              break;
              i = validated_transactions.size();
            }
          }
          it_used ++;
        }
      }
    }
    // update transaction in and out txo's
    txo send_txo;
    send_txo.transaction_id = new_transaction.id;
    send_txo.to = new_transaction.to;
    send_txo.amount = new_transaction.amount;
    txo return_utxo;
    return_utxo.transaction_id = new_transaction.id;
    return_utxo.to = new_transaction.from;
    return_utxo.amount = collected_amount - new_transaction.amount;
    if (return_utxo.amount < 0) return_utxo.amount += new_transaction.amount;
    new_transaction.out.push_back(send_txo);
    new_transaction.out.push_back(return_utxo);
    new_transaction.in = spent_txo;
    validated_transactions.push_back(new_transaction);
    generated_transactions.erase(it_t); // is find_if funkcijos pradzioje
  }
}

// padaryti coinbase_transactions i validated_transactions
// tada reikes tikrinti tik validated transactions kad rasti kiek kas turi euru
// prideti prie input txo txo is coinbase transaction(yra vectorius)
      // prie output prideti nauja txo kur adresas is transaction.to, amount is transaction.amount
      // prie output prideti nauja txo kurio suma coinbasetransaction - tx.amount, o adresas 
      // transaction.from
      // nustatyti coinbase txo unspent = false
      // isstrinti is userio utx_ids coibase transaction, prideti nauja transaction 
      // validate transaction funkcija turi ziureti visus transactions, kuriuose ir from, ir to sutampa
      // su user.public_key, tada jei to sutampa patikrinti vector<txo> out paziureti ar ten sutampa txo.to
      // jei sutampa from irgi turi paziureti out transactions, kur txo.to sutampa su public_key
      // patikrtinti ar unspent == true
      // pakeisti coinbase transactions i generated_transactions. negali ne selected_transactions gali
      // paimti toki transaction
      // sukurti nauja vektoriu, kuriam validated transactions, ir tikrinti tik ji, kai ieskai 
      // balanso userio.