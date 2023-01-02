#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <cmath>
#include <bitset>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <chrono>
#include <random>
#include <ctime>

#include "hash.h"

using namespace std;

class Blockchain
{
  public:
    Blockchain(); //constructor
    ~Blockchain();

    struct txo 
    {
        string transaction_id;
        string to;
        int amount;
        bool unspent = true;
    };

    struct transaction 
    {
        string id;
        string from;
        string to;
        int amount;
        long time;
        vector<txo> in;
        vector<txo> out;
    };

    struct user 
    {
        string name;
        string public_key;
        long time_created;
        vector<string> utx_ids;
    };

    struct block 
    {
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
    vector<user> get_users();
    void create_transaction(const string& from, const string& to, const int& amount);

  private:
    vector<user> generated_users;
    vector<transaction> generated_transactions;
    std::mt19937 mt;
    string version = "v1";
    int difficulity_target = 1;
    int blockchain_height = 0;
    void generate_starting_balances();
    long get_current_time();
    bool generate_first_block();
};