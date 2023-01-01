#pragma once

#include <vector>
#include <string>
#include <ctime>
#include <iostream>
#include <sstream>
#include <cmath>
#include <bitset>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <chrono>

using namespace std;

class Blockchain
{
  public:
    Blockchain(); //constructor
    ~Blockchain();

    struct txo {
        string transaction_id;
        string to;
        int amount;
        bool unspent = true;
        };

    struct transaction {
        string id;
        string from;
        string to;
        int amount;
        long time;
        vector<txo> in;
        vector<txo> out;
        };

    struct user {
        string name;
        string public_key;
        long time_created;
        vector<string> utx_ids;
        };

    struct block {
        string hash;
        int height;
        string prev_block_hash;
        long time;
        string version;
        string merkleroot;
        unsigned long long nonce;
        int difficulity_target;
        vector<string> tx;
        };

    void create_user(const string& name);

  private:
    vector<user> generated_users;
    long get_current_time();
};