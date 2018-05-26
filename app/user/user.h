#ifndef _USER_H_
#define _USER_H_

#include <iostream>
#include <string>

using namespace std;

class User
{
public:
  User();
  ~User();

  void set(int id, string password, string name, double mona, double pool, int count, string PubKey, string SecKey);
  string get();

  void getInformation();
  void usage();

  void getArticle();
  void getMyArticle(string login_name);

  void getAddressInfo(); // rpc connection

private:
  int id;
  string password;
  string name;
  double mona; // your total monacoin
  double pool; // the rest monacoin you may cast
  int count; // the count of getting monacoin
  string PubKey;
  string SecKey;
};

#endif //_USER_H_
