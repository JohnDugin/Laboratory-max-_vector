#include "Vector.h"
#include <iostream>

using namespace std;

int main() {

    //ТЕСТЫ------------------------------------------------

    //auto coef = 2;
    //Vector l1(10, ResizeStrategy::Multiplicative, coef);

    /*for(int i = -100; i < 100; i++)
        l1.pushBack(100);
    l1.print();*/

    /*l1.pushFront(1);
    l1.pushBack(2);
    l1.pushFront(3);
    l1.pushBack(4);
    l1.print();*/

    /*l1.insert(0,0);
    l1.insert(1,1);
    l1.insert(2,2);
    l1.insert(2,3);
    l1.insert(4,4);
    l1.print();*/

    /*l1.pushBack(0);
    l1.pushBack(1);
    l1.pushBack(2);
    l1.print();
    Vector l2;
    l2.pushBack(-1);
    l2.print();
    l2.insert(1, l1);
    l2.print();*/

    /*l1.pushBack(0);
    l1.pushBack(1);
    l1.pushBack(2);
    l1.popBack();
    l1.popBack();
    l1.pushBack(3);
    l1.print();*/

    /*l1.pushBack(1);
    l1.pushBack(2);
    l1.pushBack(3);
    l1.pushFront(0);
    l1.erase(0);
    l1.erase(2);
    l1.print();
    l1.pushBack(3);
    l1.pushBack(4);
    l1.pushBack(5);
    l1.erase(0,2);
    l1.print();*/

    /*l1.pushBack(0);
    l1.pushBack(1);
    l1.pushBack(2);
    l1.pushBack(3);
    l1.pushBack(0);
    l1.print();
    cout << l1.find(2, true) << "\t";
    cout << l1.find(0, true) << "\t";
    cout << l1.find(0, false) << "\t";
    cout << "\n";*/

    /*l1.pushBack(0);
    l1.pushBack(1);
    l1.pushBack(2);
    l1.pushBack(3);
    Vector l2 = l1; //-----
    l1.print();
    l2.print();

    l1.pushBack(111);
    l1.print();
    l2.print();

    l2.pushBack(222);
    l1.print();
    l2.print();*/

    /*l1.pushBack(0);
    l1.pushBack(1);
    l1.pushBack(2);
    l1.pushBack(3);
    Vector l2(l1); //-----
    l1.print();
    l2.print();

    l1.pushBack(111);
    l1.print();
    l2.print();

    l2.pushBack(222);
    l1.print();
    l2.print();*/

    auto coef = 2;
    Vector v1(10, 1, ResizeStrategy::Multiplicative, coef);
    cout << "v1:\n";
    v1.print();
    cout << endl;

    v1.resize(19);
    cout << "v1:\n";
    v1.print();
    cout << endl;

    return 0;
}
