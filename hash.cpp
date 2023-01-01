#include "blockchain.h"

string toBinary(int x);
string convert(string input);
string hashing(int pow, string s);
void read_file(string input, bool type);
string rightrotate(string s, int d);
string sigma0(string s);
string sigma1(string s);
string sigma2(string s);
string sigma3(string s);
string sigma4(string a, string b, string c);
string sigma5(string a, string b, string c);
string toHex(string bin);
string XOR(string a, string b);
void generateBlocks(vector<string> s);

const string hashes[8] = 
        {
          "01101010000010011110011001100111",
          "10111011011001111010111010000101",
          "00111100011011101111001101110010",
          "10100101010011111111010100111010",
          "01010001000011100101001001111111",
          "10011011000001010110100010001100",
          "00011111100000111101100110101011",
          "01011011111000001100110100011001"
        };

const string sha256_k[64] = 
        {
        "01000010100010100010111110011000", "01110001001101110100010010010001", "10110101110000001111101111001111", "11101001101101011101101110100101", 
        "00111001010101101100001001011011", "01011001111100010001000111110001", "10010010001111111000001010100100", "10101011000111000101111011010101", 
        "11011000000001111010101010011000", "00010010100000110101101100000001", "00100100001100011000010110111110", "01010101000011000111110111000011", 
        "01110010101111100101110101110100", "10000000110111101011000111111110", "10011011110111000000011010100111", "11000001100110111111000101110100", 
        "11100100100110110110100111000001", "11101111101111100100011110000110", "00001111110000011001110111000110", "00100100000011001010000111001100", 
        "00101101111010010010110001101111", "01001010011101001000010010101010", "01011100101100001010100111011100", "01110110111110011000100011011010", 
        "10011000001111100101000101010010", "10101000001100011100011001101101", "10110000000000110010011111001000", "10111111010110010111111111000111", 
        "11000110111000000000101111110011", "11010101101001111001000101000111", "00000110110010100110001101010001", "00010100001010010010100101100111", 
        "00100111101101110000101010000101", "00101110000110110010000100111000", "01001101001011000110110111111100", "01010011001110000000110100010011", 
        "01100101000010100111001101010100", "01110110011010100000101010111011", "10000001110000101100100100101110", "10010010011100100010110010000101", 
        "10100010101111111110100010100001", "10101000000110100110011001001011", "11000010010010111000101101110000", "11000111011011000101000110100011", 
        "11010001100100101110100000011001", "11010110100110010000011000100100", "11110100000011100011010110000101", "00010000011010101010000001110000", 
        "00011001101001001100000100010110", "00011110001101110110110000001000", "00100111010010000111011101001100", "00110100101100001011110010110101", 
        "00111001000111000000110010110011", "01001110110110001010101001001010", "01011011100111001100101001001111", "01101000001011100110111111110011", 
        "01110100100011111000001011101110", "01111000101001010110001101101111", "10000100110010000111100000010100", "10001100110001110000001000001000", 
        "10010000101111101111111111111010", "10100100010100000110110011101011", "10111110111110011010001111110111", "11000110011100010111100011110010", 
        };

string hashing(string input)
{
	convert(input);
}

string toBinary(int x)
{
  std::bitset<8> bin_x(x);
  return bin_x.to_string();
}

string convert(string input)
{
  string s = "";
  int orgL = input.length();
  std::bitset<32> orgLenght(orgL);
  //cout<<input.length()<<endl;
  for (int i = 0; i < orgL; i++)
    {
        s += toBinary(input[i]);
    }                                 //convert to binary

  s += '1';                           //pazymeti, nuo kur prasideda pridetiniai nuliai
  int newL = s.length();
  int pow = ((newL + 32) / 256) + 1;  // koks 256 laipsnis
  int apendZeros = (256 * pow) - newL - 32; //32bitai saugoti string ilgiui
  s.append(apendZeros, '0');          //padaro 224 bitu ilgio
  s += orgLenght.to_string();
  int size = pow * 8;

  return hashing(pow, s);
}

string hashing(int pow, string s)
{
  vector<string> data;
  int index = 0;
  string buffer;

  for (int i = 0; i < pow * 8; i++)
  {
    buffer.assign(s, index, 32);
    data.push_back(buffer);
    index += 32;
  }                                 //padalina string i 32 bitu blokus
  index = 0;
  vector<string> values;
  string calc = "";
  string H1 = hashes[0], H2 = hashes[1], H3 = hashes[2], H4 = hashes[3], H5 = hashes[4], H6 = hashes[5], H7 = hashes[6], H8 = hashes[7], T1 = "", T2 = "";

  for (int i = 0; i < pow; i++)
  {
    vector<string> values;
    for (int k = 0; k < 8; k++)
    {
      buffer.assign(s, index, 32);
      values.push_back(buffer);
      index += 32;
    }
    for (int i = 8; i < 32; i++)
    {
      calc = XOR(XOR(sigma1(values[i-1]), values[i-3]), XOR(sigma0(values[i-7]), values[i-8]));
      values.push_back(calc);
    }
    string a = H1, b = H2, c = H3, d = H4, e = H5, f = H6, g = H7, h = H8;

    for (int i = 0; i < 32; i++)
    {
      T1 = XOR(XOR(XOR(XOR(h, sigma3(e)), sigma4(e, f, g)), sha256_k[i]), values[i]);
      T2 = XOR(sigma2(a), sigma5(a, b, c));
      h = g;
      g = f;
      f = e;
      e = d + T1;
      d = c;
      c = b;
      b = a;
      a = T1 + T2;
    }
    H1 = XOR(H1, a);
    H2 = XOR(H2, b);
    H3 = XOR(H3, c);
    H4 = XOR(H4, d);
    H5 = XOR(H5, e);
    H6 = XOR(H6, f);
    H7 = XOR(H7, g);
    H8 = XOR(H8, h);
  }
  string rez = toHex(H1) + toHex(H2) + toHex(H3) + toHex(H4) + toHex(H5) + toHex(H6) + toHex(H7) + toHex(H8);
  return rez;
}

string rightrotate(string s, int d)    
{
    std::reverse(s.begin(), s.end() - d);   
    std::reverse(s.end() - d, s.end());     
    std::reverse(s.begin(), s.end());
    return s;
}

string sigma0(string s)
{
  return XOR(rightrotate(s, 7), rightrotate(s, 18));
}

string sigma1(string s)
{
  return XOR(rightrotate(s, 17), rightrotate(s, 19));
}

string sigma2(string s)
{
  return XOR(XOR(rightrotate(s, 2), rightrotate(s, 13)), rightrotate(s, 22));
}

string sigma3(string s)
{
  return XOR(XOR(rightrotate(s, 6), rightrotate(s, 11)), rightrotate(s, 25));
}

string sigma4(string a, string b, string c)
{
  string ans1 = "", ans2 = "";
  for (int i = 0; i < 32; i++)
  {
      if (a[i] == '1' || b[i] == '1')
          ans1 += "1";
      else
          ans1 += "0";
      if (a[i] != '1' || c[i] == 1)
          ans2 += "1";
      else
          ans2 += "0";
  }
  return XOR(ans1, ans2);
}

string sigma5(string a, string b, string c)
{
  string ans1 = "", ans2 = "", ans3 = "";
  for (int i = 0; i < 32; i++)
  {
      if (a[i] == '1' || b[i] == '1')
          ans1 += "1";
      else
          ans1 += "0";
      if (a[i] == '1' || c[i] == 1)
          ans2 += "1";
      else
          ans2 += "0";
      if (b[i] != '1' || c[i] == 1)
          ans2 += "1";
      else
          ans2 += "0";
  }
  return XOR(XOR(ans1, ans2), ans3);
}

string XOR(string a, string b)
{
  string ans = "";
  for (int i = 0; i < 32; i++)
  {
      if (a[i] == b[i])
          ans += "0";
      else
          ans += "1";
  }
  return ans;
}

string toHex(string bin)
{
    int result = 0;
    int binL = bin.length();
    for(size_t count = 0; count < binL ; ++count)
    {
        result *=2;
        result += bin[count]=='1'? 1 :0;
    }  

    std::stringstream ss;
    ss << std::hex << std::setw(8) << std::setfill('0')  << result;

    return (ss.str());
}
