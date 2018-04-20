#include "Tree.h"
#include <iostream>
#include "picosha2.h"

Tree::Tree () {}


int Tree::makeBinary(vector<Node*> &node_vector){

  int vectSize = node_vector.size();

  if((vectSize%2) != 0){
    node_vector.push_back(node_vector.end()[-1]);
    vectSize++;
  }
  return vectSize;
}

void Tree::buildTree(){

  do {
    vector<Node*> new_nodes;
    makeBinary(this->base.end()[-1]);

    for (int i = 0; i < this->base.end()[-1].size(); i = i+2) {
      Node* new_parent = new Node;
      this->base.end()[-1][i]->setParent(new_parent);
      this->base.end()[-1][i+1]->setParent(new_parent);

      new_parent->setHash(this->base.end()[-1][i]->getHash() + this->base.end()[-1][i+1]->getHash());
      new_parent->setChildren(this->base.end()[-1][i],this->base.end()[-1][i+1]);
      new_nodes.push_back(new_parent);
      std::cout << "Hash together: " << this->base.end()[-1][i]->getHash() << " and " << this->base.end()[-1][i+1]->getHash() << " attached: " << &new_parent << endl;
    }

    //printTreeLevel(new_nodes);

    this->base.push_back(new_nodes);
    std::cout << "Hashed level with: " << this->base.end()[-1].size() << '\n';

  } while(this->base.end()[-1].size() > 1);

  this->merkleRoot = this->base.end()[-1][0]->getHash();

  std::cout << "Merkle Root is: " << this->merkleRoot << endl << endl;

}

void Tree::printTreeLevel(vector<Node*> v){

  cout << endl;

  for (Node* el : v) {
      cout << el->getHash() << endl;
  }
}


void Tree::buildBaseLeafes(vector<string> base_leafs){

  vector<Node*> new_nodes;

  std::cout << "Root leafs are: " << '\n';

  for (auto leaf : base_leafs){
    Node* new_node = new Node;
    new_node->setHash(leaf);
    std::cout << new_node->getHash() << '\n';

    new_nodes.push_back(new_node);
  }
  this->base.push_back(new_nodes);
  std::cout  << '\n';
}

string Tree::getMerkleRoot() {
  return merkleRoot;
}


int Tree::verify(string hash){

  Node* el_node = NULL;
  string act_hash = hash;

  for (int i = 0; i < this->base[0].size(); i++) {
    if(this->base[0][i]->getHash() == hash)
      el_node = this->base[0][i];
  }

  std::cout << "Hash verify: " << act_hash << '\n';

  do {

    if(el_node->checkDir() == 0)
      act_hash = picosha2::hash256_hex_string(act_hash + el_node->getSibling()->getHash());
    else
      act_hash = picosha2::hash256_hex_string(el_node->getSibling()->getHash() + act_hash);

    std::cout << "Hash verify: " << act_hash << '\n';

    el_node = el_node->getParent();
  }while ((el_node->getParent()) != NULL);

  return act_hash == merkleRoot ? 1 : 0;
}

void Tree::iterateUp(int element){
  Node* el_node = this->base[0][element];

  do {
    std::cout << "Current Hash: " << el_node->getHash() << '\n';
    /*std::cout << "Next Node: " << el_node << '\n';
    std::cout << "Next Parent: " << el_node->getParent() << '\n';*/
  }while ((el_node = el_node->getParent()) != NULL);
  //std::cout << "Done iterating" << '\n';
}

Tree::~Tree () {}
