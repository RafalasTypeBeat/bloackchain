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

void Blockchain::create_transaction(const string& from, const string& to, const int& amount)
{
  long current_time = get_current_time();

  string hashed_data = from + to + to_string(amount) + to_string(current_time);
  string transaction_id = convert(hashed_data);
  transaction new_transacion {transaction_id, from, to, amount, current_time};
  generated_transactions.push_back(new_transacion);
}

