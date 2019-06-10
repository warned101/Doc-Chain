#include <string.h>
#include <string>
#include <sstream>
#include <unistd.h>
#include <mysql/mysql.h>
#include "Block.h"
#include "sha256.h"
#include "progress.h"
// #include "database.cpp"
using namespace std;

string h;

Block::Block(uint32_t nIndexIn, const string &sDataIn, const string &certificateNoIn) : _nIndex(nIndexIn), _sData(sDataIn), certificateNo(certificateNoIn) {
  _nNonce = -1;
  _tTime = time(nullptr);
}

string Block::GetHash() {
  return _sHash;
}

void Block::MineBlock(uint32_t nDifficulty) {
  char* cstr = new char[nDifficulty + 1];

  for (uint32_t i = 0; i < nDifficulty; ++i) {
    cstr[i] = '0';
  }

  cstr[nDifficulty] = '\0';

  string str(cstr);

  do{
    _nNonce++;
    _sHash = _CalculateHash();
  } while(_sHash.substr(0, nDifficulty) != str);

  show_progress_bar(std::clog, 101, "progress", '#');

  std::cout << endl << "Index: " << _nIndex << '\n';

  cout << "Proof of Work (PoW): " << _nNonce << endl;

  cout << "ID: " << _sData << endl;

  cout << "certificate No: " << certificateNo << endl;

  string username = "jaadu", password= "jaadu", dbname="blocks";
  MYSQL mysql;

  if (mysql_init(&mysql)==NULL) {
    cout << "Connection to the API failed" << endl;
  }
  // connection = mysql_real_connect (connection, "localhost", username.c_str (), password.c_str (), dbname.c_str (), 0, NULL, 0);
  if (mysql_real_connect (&mysql, "localhost", username.c_str (), password.c_str (), dbname.c_str (), 0, NULL, 0)) { cout << "Connection successful" << endl; }
  else { cout << mysql_error(&mysql) <<  endl;  }

  // mysql_query (&mysql, "CREATE TABLE student ( ind int, sap_id int UNIQUE, cert_no int, pow char(255), prevhash char(255), curhash char(255), timestamp int);");

  // string query = "SELECT LAST (curhash) FROM student;"  ;

  string val;

  MYSQL_RES *res;
    MYSQL_ROW row;
    string q = "SELECT MAX(ind) FROM student WHERE ind <> 0";
    int ip = mysql_query (&mysql, q.c_str());
    res = mysql_use_result(&mysql);
    if (ip == 0)
    {
        while ((row = mysql_fetch_row(res)) != NULL)
        {
                 val = row[0];
        }
        // return h;
    }

    string qr = "SELECT curhash FROM student WHERE ind =  " + val;
    int ipr = mysql_query (&mysql, qr.c_str());
    res = mysql_use_result(&mysql);
    
    if (ipr == 0)
    {
        while ((row = mysql_fetch_row(res)) != NULL)
        {
                h = row[0];
            // h = row[4];
        }
        // return h;
    }

  cout << "Previous Hash: " << "\033[1;31m" << h << "\033[0m\n" << '\n';


  mysql_close (&mysql);

  
  cout << "Block mined: " << "\033[1;32m" << _sHash << "\033[0m\n" << endl;

  std::cout << "Timestamp: " << "\033[1;33m" << _tTime << "\033[0m\n" << '\n' << endl;


  delete cstr;


}

inline string Block::_CalculateHash() const{
  std::stringstream ss;

  ss << _nIndex << _tTime << _sData << certificateNo << _nNonce << sPrevHash;

  return sha256(ss.str());
}

void Block::DatabaseAccess() {
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

  // mysql_query (&mysql, "CREATE TABLE student ( ind int, sap_id int UNIQUE, cert_no int, pow char(255), prevhash char(255), curhash char(255), timestamp int);");

  string query = "INSERT INTO student values ('";
  query += to_string(_nIndex) + "','" + _sData + "','" + certificateNo + "','";
  query += to_string(_nNonce) + "','" + h + "','" + _sHash + "','";
  query += to_string(_tTime) + "')";
  // cout << query << "\n";

  mysql_query(&mysql,query.c_str());

  mysql_close (&mysql);
}
