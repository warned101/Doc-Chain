#include "Blockchain.h"
#include <bits/stdc++.h>

using namespace std;

int main() {
  Blockchain bChain;

  std::cout<<"Mining block 1...\n";
  bChain.AddBlock(Block(1, "Block 1 Data"));
  std::cout<<"Mining block 2...\n";
  bChain.AddBlock(Block(2, "Block 2 Data"));
  std::cout<<"Mining block 2...\n";
  bChain.AddBlock(Block(3, "Block 3 Data"));
  return 0;
}
