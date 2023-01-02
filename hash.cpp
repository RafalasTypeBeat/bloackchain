#include "hash.h"

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
