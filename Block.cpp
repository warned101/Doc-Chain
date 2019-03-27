#include<string.h>
#include<sstream>
#include <unistd.h>
#include "Block.h"
#include "sha256.h"
#include "progress.h"

Block::Block(uint32_t nIndexIn, const string &sDataIn) : _nIndex(nIndexIn), _sData(sDataIn) {
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

  show_progress_bar(std::clog, 100, "progress", '#');

  std::cout << endl << "Index: " << _nIndex << '\n';

  cout << "Proof of Work (PoW): " << _nNonce << endl;

  cout << "ID: " << _sData << endl;

  cout << "Previous Hash: " << "\033[1;31m" << sPrevHash << "\033[0m\n" << '\n';

  cout << "Block mined: " << "\033[1;32m" << _sHash << "\033[0m\n" << endl;

  std::cout << "Timestamp: " << "\033[1;33m" << _tTime << "\033[0m\n" << '\n' << endl;
  delete cstr;
}

inline string Block::_CalculateHash() const{
  std::stringstream ss;

  ss << _nIndex << _tTime << _sData << _nNonce << sPrevHash;

  return sha256(ss.str());
}
