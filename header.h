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

struct TransactionData
{
  double amount;
  string sender;
  string receiver;
  time_t timestamp;
};
