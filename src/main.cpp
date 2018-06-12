#include <iostream>
#include <string>
#include "maincontroller.h"
#include "./utilities/rulebst.h"

void testRuleBst() {
    std::string s1("011");
    std::string s2("001");
    RuleBst bst;
    bst.insert(s1, 'a');
    bst.insert(s2, 'd');
    std::cout<<bst.serialize()<<std::endl<<std::flush;
    bst.printTree();
    std::cout<<"#1 ok"<<std::endl<<std::flush;

    RuleBst bst2(bst.serialize());
    bst2.printTree();
    std::cout<<"#2 ok"<<std::endl<<std::flush;
    bst2.deserialize("0f01d11a");
    bst2.printTree();
    std::cout<<bst2.next('0')<<std::endl<<std::flush;
    std::cout<<bst2.next('0')<<std::endl<<std::flush;
    std::cout<<bst2.next('0')<<std::endl<<std::flush;
}

int main(int argc, char *argv[])

{

    QApplication app(argc, argv);
    MainController w;
    w.show();

    testRuleBst();
    //  std::string pause;
    //  std::cin >> pause;

    return app.exec();
}
