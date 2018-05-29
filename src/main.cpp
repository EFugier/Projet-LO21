#include <iostream>
#include <string>
#include "./utilities/rulebst.h"

void testRuleBst() {
  std::string s1("011a");
  std::string s2("001d");
  RuleBst bst;
  bst.insert(s1);
  bst.insert(s2);
  std::cout<<bst.serialize()<<std::endl<<std::flush;
  bst.printTree();
  std::cout<<"#1 ok"<<std::endl<<std::flush;

  RuleBst bst2(bst.serialize());
  bst2.printTree();
  std::cout<<bst2.next('0')<<std::endl<<std::flush;
  std::cout<<bst2.next('0')<<std::endl<<std::flush;
  std::cout<<bst2.next('1')<<std::endl<<std::flush;
}

int main() {
  testRuleBst();
//  std::string pause;
//  std::cin >> pause;
  return 0;
}
