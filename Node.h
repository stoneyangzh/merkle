#include <string>
#include <vector>

using namespace std;

class Node {
private:
  string hash_str;
  Node* parent;
  Node* children[2];

public:
  Node ();
  Node* getParent();
  void setChildren(Node* children_l, Node* children_r);
  Node* getChildren(int index);
  void setParent(Node* parent);
  string getHash();
  int checkDir();
  Node* getSibling();
  void setHash(string hash_str);
  virtual ~Node ();
};
