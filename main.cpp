#include <iostream>
#include "Tree.h"
#include "picosha2.h"

using namespace std;

int main(int argc, char const *argv[]) {

  //验证节点
  string proof_leaf = "";

  std::cout << "输入叶子节点(空格分隔 ';'结束): " << '\n';
  std::vector<string> v;

  while(true) {
    string merkle_leaves;
    std::cin >> merkle_leaves;
    if(merkle_leaves != ";")
      v.push_back(merkle_leaves);
    else
      break;
  }

  std::cout << "输入验证叶子节点: " << '\n';

  cin >> proof_leaf;

  proof_leaf = picosha2::hash256_hex_string(proof_leaf);


  Tree theTree;

  //构建叶子节点
  theTree.buildBaseLeafes(v);
  //构建Merkle Tree
  theTree.buildTree();

  std::cout << "验证: " << proof_leaf << "是否存在" << '\n';

  if(theTree.verify(proof_leaf)){
    std::cout << "验证：存在" << '\n';
  } else {
      std::cout << "验证：不存在" << '\n';
  }



  return 0;
}
