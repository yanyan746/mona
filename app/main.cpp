/*
todo
 *the way to access database
 *when an user name someone typed is wrong
 *typing password, make the text color black
 *AdminUser class

*/

#include "user/user.h"

#include <stdlib.h>
#include <iostream>
#include <string>

#include "json11/json11.hpp"
#include <mysql_connection.h>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

using namespace std;

int main(void){
  User loginUser;
  cout << "Connecting database..." << endl;

  // connect to database and make an user instance
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

    // enter your name
    string user_name;
    string query;
    string user_password = "";
    int password_time = 3;
    int i = 0;
    cout << "What's your name? : ";
    cin >> user_name;
    // SQL query with your name
    query = "SELECT * from test.user where name=";
    query += '\"';
    query += user_name;
    query += '\"';
    query += ";";
    pstmt = con->prepareStatement(query);
    res = pstmt->executeQuery();
    res->next();

    // cout << res->getString("name") << endl;

    // confirm user_password
    bool confirm = false;

    for (int i = 0; i < password_time; ++i) {
      cout << "enter your password. : ";
      cin >> user_password;
      if ( res->getString("password") == user_password ) {
        confirm = true;
        cout << "you logged in." << endl;
        break;
      }
      cout << "try again." << endl;
    }

    if ( !confirm )  {
      cout << "you cannot login." << endl;
      exit(1);
    }

    // making user instance
    loginUser.set(res->getInt("id"), res->getString("password"), res->getString("name"), res->getDouble("mona"), res->getDouble("pool"), res->getInt("count"), res->getString("PubKey"), res->getString("SecKey"));

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


  for (;;) {
    string typedCommand;
    //string login_name = loginUser.get();

    cout << loginUser.get() << "$ ";
    cin >> typedCommand;

    if ( typedCommand == "-g" || typedCommand == "--get" ) {
      loginUser.getInformation();
    } else if ( typedCommand == "-l" || typedCommand == "--list" ) {
      loginUser.getArticle();
    } else if ( typedCommand == "exit" ) {
      exit(1);
    } else if ( typedCommand == "-ml" ) {
      loginUser.getMyArticle(loginUser.get());
    } else if ( typedCommand == "--address") {
      loginUser.getAddressInfo();
    } else {
      loginUser.usage();
    }
  }

  return 0;
}
