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

void Blockchain::print_block(int block_height)
{
    block chosen_block = get_block(block_height);
    cout << "Printing block: " << chosen_block.height << '\n';
    cout << "Block hash: " << chosen_block.hash << '\n';
    cout << "Prev block hash: " << chosen_block.prev_block_hash << '\n';
    cout << "Block creation time: " << chosen_block.time << '\n';
    cout << "Block version: " << chosen_block.version << '\n';
    cout << "Block merkleroot: " << chosen_block.merkleroot << '\n';
    cout << "Block nonce: " << chosen_block.nonce << '\n';
    cout << "Block difficulity target: " << chosen_block.difficulity_target << '\n';
    cout << "Block transactions: " << chosen_block.difficulity_target << '\n';
}

Blockchain::block Blockchain::get_block(int block_height)
{
    if (block_height > blockchain_height)
    {
        cout << "No such block exists!";
        return blockchain[0]; // change to latest block
    }
    auto it = find_if(blockchain.begin(), blockchain.end(), [&](const block& b)
    {
        return b.height == block_height;
    });
    block found_block = *it;
    return found_block;
}