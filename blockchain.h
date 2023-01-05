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
#include <bits/stdc++.h>

#include "hash.h"

using namespace std;

class Blockchain
{
  public:

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
    void print_user(int index);
    void print_transaction(int index);
    void print_block(int block_id);
    block get_block(int block_height);
    void generate_first_block();
    vector<string> select_transactions(); // perkelti i private
    void create_new_block();
    void mine_blocks();
    int get_user_amount();
    void mine_block();
    int blockchain_height = 0;
  private:
    vector<block> block_candidates;
    vector<vector<string>> tx_candidates;
    vector<block> blockchain;
    vector<user> generated_users;
    vector<transaction> generated_transactions;
    vector<transaction> validated_transactions;
    std::mt19937 mt;
    string version = "v1";
    int difficulity_target = 2;
    int max_block_transactions = 100;
    void generate_starting_balances();
    long get_current_time();
    string get_merkleroot(vector<string> transactions);
    vector<string> validate_transaction(vector<string> tx);
    block get_best_block();
    int get_user_utx_amount(int available_funds, user current_user);
    void update_transactions(vector<string> tx);
};