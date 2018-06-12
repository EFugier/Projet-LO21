#include <iostream>
#include <string>
#include "maincontroller.h"
#include "./utilities/rulebst.h"

void testRuleBst() {
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
