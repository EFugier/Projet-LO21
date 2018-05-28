#include <iostream>
#include <string>
#include "./utilities/bst.h"

void testBst() {
  std::string s1("011a");
  std::string s2("001d");
  Bst bst;
  bst.insert(s1);
  bst.insert(s2);
  std::cout<<bst.serialize()<<std::endl<<std::flush;
  bst.printTree();
  std::cout<<"#1 ok"<<std::endl<<std::flush;

  Bst bst2(bst.serialize());
  bst2.printTree();
  std::cout<<bst2.next('0')<<std::endl<<std::flush;
  std::cout<<bst2.next('0')<<std::endl<<std::flush;
  std::cout<<bst2.next('1')<<std::endl<<std::flush;
}

int main() {
  testBst();
//  std::string pause;
//  std::cin >> pause;
  return 0;
}
