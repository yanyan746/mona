#include "user.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#include "../json11/json11.hpp"
#include <curl/curl.h>
#include <mysql_connection.h>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>


using namespace std;

User::User() {
  cout << "Hello." << endl;
}

User::~User() {
  cout << "logout." << endl;
}

void User::set(int id, string password, string name, double mona, double pool, int count, string PubKey, string SecKey) {
  this->id = id;
  this->password = password;
  this->name = name;
  this->mona = mona;
  this->pool = pool;
  this->count = count;
  this->PubKey = PubKey;
  this->SecKey = SecKey;
}

string User::get() {
  return this->name;
}

void User::getInformation() {
  cout << "your total mona : " << this->mona << "mona" << endl;
  cout << "mona that you may cast : " << this->pool << "mona" << endl;
  cout << "your mona address : " << this->PubKey << endl;
}

void User::usage() {
  cout << "Usage:" << endl;
  cout << "-l --list      - show all articles" << endl;
  cout << "-ml            - show your articles" << endl;
  cout << "-g --get       - show your information about mona" << endl;
  cout << "-g --get       - show your information about mona" << endl;
  cout << "-g --get       - show your information about mona" << endl;
  cout << "-g --get       - show your information about mona" << endl;
  cout << "exit           - finish this app" << endl;
}

void User::getArticle() {
  try {
    sql::Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::ResultSet *res;
    sql::PreparedStatement *pstmt;
    /* Create a connection */
    driver = get_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root", "password");
    /* Connect to the MySQL test database */
    con->setSchema("test");
    string query = "SELECT * from test.article;";
    pstmt = con->prepareStatement(query);
    res = pstmt->executeQuery();

    /* Fetch in reverse = descending order! */
    //res->afterLast();
    //while (res->previous())
    while (res->next()) {
      cout << "date: " << res->getString("date") << ", ";
      cout << "title: " << res->getString("title") << ", ";
      cout << "writer: " << res->getString("writer") << ", ";
      cout << "mona: " << res->getDouble("mona") << endl;
    }

    delete res;
    delete pstmt;
    delete con;

  } catch (sql::SQLException &e) {
    cout << "# ERR: SQLException in " << __FILE__;
    cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
    cout << "# ERR: " << e.what();
    cout << " (MySQL error code: " << e.getErrorCode();
    cout << ", SQLState: " << e.getSQLState() << " )" << endl;
  }
}

void User::getMyArticle(string login_name) {
  try {
    sql::Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::ResultSet *res;
    sql::PreparedStatement *pstmt;
    /* Create a connection */
    driver = get_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root", "password");
    /* Connect to the MySQL test database */
    con->setSchema("test");
    string query = "SELECT * from test.article where writer=";
    query += '\"';
    query += login_name;
    query += '\"';
    query += ";";
    pstmt = con->prepareStatement(query);
    res = pstmt->executeQuery();

    /* Fetch in reverse = descending order! */
    //res->afterLast();
    //while (res->previous())
    while (res->next()) {
      cout << "date: " << res->getString("date") << ", ";
      cout << "title: " << res->getString("title") << ", ";
      cout << "writer: " << res->getString("writer") << ", ";
      cout << "mona: " << res->getDouble("mona") << endl;
    }

    delete res;
    delete pstmt;
    delete con;

  } catch (sql::SQLException &e) {
    cout << "# ERR: SQLException in " << __FILE__;
    cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
    cout << "# ERR: " << e.what();
    cout << " (MySQL error code: " << e.getErrorCode();
    cout << ", SQLState: " << e.getSQLState() << " )" << endl;
  }
}

void User::getAddressInfo() {
  CURL *curl = curl_easy_init();
  struct curl_slist *headers = NULL;
  string buf;

  // for curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, LocalFunc::call_back)
  struct LocalFunc {
    static size_t call_back(char* ptr, size_t size, size_t nmemb, void* stream) {
      ((string*) stream)->append(string(ptr, size * nmemb));
      return size * nmemb;
    }
  };

  if (curl) {
    // command : curl --user 'yanyan:password' --data-binary '{"jsonrpc":"1.0","id":"curltext","method":"getblockchaininfo","params":[]}' -H 'content-type:text/plain;' http://127.0.0.1:9042
    const char *query = "{\"jsonrpc\": \"1.0\", \"id\":\"curltext\", \"method\": \"getblockchaininfo\", \"params\": [] }";

  	headers = curl_slist_append(headers, "content-type: text/plain;");
  	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
  	curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:9042/");
  	//curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long) strlen(query));
  	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, query);
  	curl_easy_setopt(curl, CURLOPT_USERPWD, "yanyan:password");
  	curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_TRY);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl");
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buf);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, LocalFunc::call_back);
  	curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    cout << buf << endl;
    string err;
    json11::Json v = json11::Json::parse(buf, err);
    auto k = v["result"]["blocks"].int_value();
    cout << k << endl;
  }
}
