#include "Blockchain.h"
#include <bits/stdc++.h>
#include <mysql/mysql.h>

using namespace std;

int main() {

  cout << "\t\t\t\t\t########   #######   ######      ######  ##     ##    ###    #### ##    ## "<<endl;
    cout << "\t\t\t\t\t##     ## ##     ## ##    ##    ##    ## ##     ##   ## ##    ##  ###   ## "<<endl;
    cout << "\t\t\t\t\t##     ## ##     ## ##          ##       ##     ##  ##   ##   ##  ####  ## "<<endl;
    cout << "\t\t\t\t\t##     ## ##     ## ##          ##       ######### ##     ##  ##  ## ## ## "<<endl;
    cout << "\t\t\t\t\t##     ## ##     ## ##          ##       ##     ## #########  ##  ##  #### "<<endl;
    cout << "\t\t\t\t\t##     ## ##     ## ##    ##    ##    ## ##     ## ##     ##  ##  ##   ### "<<endl;
    cout << "\t\t\t\t\t########   #######   ######      ######  ##     ## ##     ## #### ##    ## "<<endl;

  string username = "jaadu", password= "jaadu", dbname="blocks";
  MYSQL mysql;

  if (mysql_init(&mysql)==NULL) {
    cout << "Connection to the API failed" << endl;
  }
  // cout << "hello";
  // connection = mysql_real_connect (connection, "localhost", username.c_str (), password.c_str (), dbname.c_str (), 0, NULL, 0);
  if (mysql_real_connect (&mysql, "localhost", username.c_str (), password.c_str (), dbname.c_str (), 0, NULL, 0)) { 
    // cout << "Connection successful" << endl; 
  }
  else { cout << mysql_error(&mysql) <<  endl;  }

  // mysql_query (&mysql, "CREATE TABLE student ( ind int, sap_id int UNIQUE, cert_no int, pow char(255), prevhash char(255), curhash char(255), timestamp int);");

  // MYSQL_RES *res;
  // MYSQL_ROW row;
  // string query = "SELECT MAX(id) FROM table_name WHERE value_1 <> 0"  ;
  // int state;
  // state = mysql_query(&mysql, query.c_str());
  // cout << "Heelo";
  // if(state != 0 )
  //   cout << "error";
  // res = mysql_use_result(&mysql);

  // row = mysql_fetch_row(res);
  // //cout << row[0] << row[1];
  
  // int k = 0;//mysql_query(&mysql,query.c_str());

    string h;

    MYSQL_RES *res;
    MYSQL_ROW row;
    string q = "SELECT MAX(ind) FROM student WHERE ind <> 0";
    int ip = mysql_query (&mysql, q.c_str());
    res = mysql_use_result(&mysql);
    // string h;
    if (ip == 0)
    {
        while ((row = mysql_fetch_row(res)) != NULL)
        {
                h = row[0];
            // h = row[4];
        }
        // return h;
    }

  mysql_close (&mysql);

  // int k = 1;
  int k = stoi(h);

  Blockchain bChain;
  // cout << "hello";
  while(1)
  {
    int t;
    cout <<"##############################################################################################################################################";
    cout << "\nPress\n";
    cout << "\t 1.Student \n\t 2. Employer\n \t 0. exit\n\n";
    cin >> t;
    if(t == 0)
      break;
    else if(t == 1)
    {
          string sap, cert, name, year;
      cout << "\n\tEnter certificate:" << "\t\t";
      cin >> cert;
      cout << "\n\tEnter SAP:        " << "\t\t";
      cin >> sap;
      cout << "\n\tEnter Name:        " << "\t\t";
      cin >> name;
      cout << "\n\tEnter Qualification Year:        " << "\t\t";
      cin >> year;

      k++;

      std::cout<<"\t\nMining block" << k << "...\n";
      bChain.AddBlock(Block(k, sap, cert));
    }
    else if(t == 2)
    {
      
      string input;
      cout << "\n\tEnter the hash of to check\t";
      cin >> input;

      string username = "jaadu", password= "jaadu", dbname="blocks";
      MYSQL mysql;

      if (mysql_init(&mysql)==NULL) {
        cout << "Connection to the API failed" << endl;
      }
  // connection = mysql_real_connect (connection, "localhost", username.c_str (), password.c_str (), dbname.c_str (), 0, NULL, 0);
      if (mysql_real_connect (&mysql, "localhost", username.c_str (), password.c_str (), dbname.c_str (), 0, NULL, 0)) { 
        // cout << "Connection successful" << endl; 
      }
      else { cout << mysql_error(&mysql) <<  endl;  }


    MYSQL_RES *res;
    MYSQL_ROW row;
    string q = "SELECT * FROM student WHERE curhash = '" + input + "';";
    // cout << q;
    int ip = mysql_query (&mysql, q.c_str());
    res = mysql_use_result(&mysql);
    // string h;
    bool flag = false;
    if (ip == 0)
    {
      // if((row = mysql_fetch_row(res)) == NULL)
      //   cout << "\ncertificate not found!";

        while ((row = mysql_fetch_row(res)) != NULL)
        { 
          // cout << "in";
          // if (row[0] == ""){
          //         cout << "certificate not found!";
          //         break;
          //       }
                cout << "\033[1;32m" << "Certificate found!" << "\033[0m\n";
                cout << "Index" << "       " << "SAP" << "     " << "certificate" << endl;
                cout << row[0] << "     " << row[1] << "   "  << row[2] << endl;
                flag = true;
            // h = row[4];
        }
        if(!flag)
          cout << "\033[1;31m" << "\n\tcertificate not found!" << "\033[0m\n" << "\n\n";

        // return h;
    } 

      mysql_close (&mysql);
    }
    else
    {
      cout << "\n\tEnter correct value \n";
    }
  }
  cout << "\nThank you\n\n";
  
  return 0;
}
