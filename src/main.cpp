#include <iostream>
#include <string>
#include "./utilities/bst.h"

void testBst() {
  std::string s1("011a");
  std::string s2("001d");
  Bst bst;
  bst.insert(s1);
  bst.insert(s2);

  std::cout<<bst.serialize()<<std::endl;

  Bst bst2(bst.serialize());
  std::cout<<bst2.serialize()<<std::endl;

  std::cout<<bst2.next('0')<<std::endl;
  std::cout<<bst2.next('0')<<std::endl;
  std::cout<<bst2.next('1')<<std::endl;
}

int main(){
  testBst();
//  std::string pause;
//  std::cin >> pause;
  return 0;
}
