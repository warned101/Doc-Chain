#include "Blockchain.h"
#include <bits/stdc++.h>

using namespace std;

int main() {
  Blockchain bChain;

  std::cout<<"Mining block 1...\n";
  bChain.AddBlock(Block(1, "500054210"));
  std::cout<<"Mining block 2...\n";
  bChain.AddBlock(Block(2, "500054707"));
  std::cout<<"Mining block 3...\n";
  bChain.AddBlock(Block(3, "500054128"));
  std::cout<<"Mining block 4...\n";
  bChain.AddBlock(Block(4, "500053268"));
  std::cout<<"Mining block 5...\n";
  bChain.AddBlock(Block(5, "500053487"));
  return 0;
}
