#include "Blockchain.h"

Blockchain::Blockchain() {
  _vChain.emplace_back(Block(0, "Genesis Block", "0"));
  _nDifficulty = 4;
}

void Blockchain::AddBlock(Block bNew) {
  bNew.sPrevHash = _GetLastBlock().GetHash();
  bNew.MineBlock(_nDifficulty);
  _vChain.push_back(bNew);
  bNew.DatabaseAccess();
}

Block Blockchain::_GetLastBlock() const {
  return _vChain.back();
}
