// DictionaryBST_.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "BST.h"
using namespace std;

int main()
{
    Dictionary d = Dictionary();


    d.insert(6, "Lisbon");
    d.displayTree();
    d.insert(2, "Madrid");
    d.insert(3, "Nottingham");
    d.insert(0, "London");
    d.insert(10, "Bologna");
    d.insert(12, "Birmingham");
    d.insert(20, "Rio de Janeiro");
    d.insert(18, "Istanbul");
    d.insert(8, "Porto");
    d.insert(7, "Manchester");
    d.insert(9, "Berlin");


    cout << "Item with key 0 is" << *(d.lookup(0)) << endl;
    cout << "Item with key 1 is" << *(d.lookup(7)) << endl;
    cout << "Item with key 2 is" << *(d.lookup(2)) << endl;
    cout << "Item with key 3 is" << *(d.lookup(3)) << endl;
    cout << "The height is: " << d.getHeight() << endl;

    string* s = d.lookup(4);
    if (s == nullptr) {
        cout << "No item with key 4\n";
    }
    else {
        cout << "Item with key 3 is" << *s << endl;
    }

    d.displayEntries();
    d.displayTree();
    cout << "Rotating to the right on 10\n";
    d.rotateRightOn(10);
    d.displayTree();

    cout << "Rotating to the left on 8\n";
    d.rotateLeftOn(8);
    d.displayTree();

    cout << "Removing 12 (Birmingham)\n";
    d.remove(12);
    cout << "The height is: " << d.getHeight() << endl;
    d.displayTree();

    return 0;
}