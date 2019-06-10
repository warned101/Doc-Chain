#include <cstdint>
#include <iostream>

using namespace std;

class Block {
  public:
    string sPrevHash;

    Block(uint32_t nIndexIn, const string &sDataIn, const string &certificateNoIn);

    string GetHash();

    void MineBlock(uint32_t nDifficulty);

    void DatabaseAccess();

  private:
    uint32_t _nIndex;
    int64_t _nNonce;
    string _sData;
    string certificateNo;
    string _sHash;
    time_t _tTime;

    string _CalculateHash() const;
};
