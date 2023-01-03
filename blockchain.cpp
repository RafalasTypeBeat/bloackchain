#include "blockchain.h"

long Blockchain::get_current_time() {
    auto now = chrono::system_clock::now();
    auto now_s = chrono::time_point_cast<chrono::seconds>(now);
    auto epoch = now_s.time_since_epoch();
    auto epoch_value = chrono::duration_cast<chrono::seconds>(epoch);
    long epoch_time = epoch_value.count();
    return epoch_time;
}

string Blockchain::get_merkleroot(vector<string> transactions)
{
   vector<string> temp;
   int len = temp.size();
   if (len == 1)
   {
        temp.push_back(transactions[0]);
        return temp[0];
   }
   for (int i = 0; i < len - 1; i += 2)
   {
        string hashed_data = transactions[i] + transactions[i + 1];
        temp.push_back(convert(hashed_data));
   }
   if (len % 2 == 1)
   {
        string hashed_data = transactions[len - 1] + transactions[len - 1];
        temp.push_back(convert(hashed_data));
   }
   return get_merkleroot(temp);
}
