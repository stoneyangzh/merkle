#include "Node.h"
#include "picosha2.h"


Node::Node (){
  this->parent = NULL;
  this->children[0] = NULL;
  this->children[1] = NULL;
}

void Node::setHash(string hash_str){
  this->hash_str = picosha2::hash256_hex_string(hash_str);
}

Node* Node::getParent(){
  return this->parent;
}

void Node::setParent(Node* parent){
  this->parent = parent;
}

void Node::setChildren(Node* children_l, Node* children_r){
  this->children[0] = children_l;
  this->children[1] = children_r;
}

Node* Node::getSibling(){
  Node* parent = this->getParent();
  return parent->getChildren(0) == this ? parent->getChildren(1) : parent->getChildren(0);

}

Node* Node::getChildren(int index){
  return index <= 1 ? children[index] : NULL;
}

string Node::getHash(){
    return this->hash_str;
}

int Node::checkDir(){
  return parent->getChildren(0) == this ? 0 : 1;
}



Node::~Node () {}
