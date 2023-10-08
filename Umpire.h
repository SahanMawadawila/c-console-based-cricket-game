#include<iostream>
using namespace std;

class Umpire {
    string name;
public:
    Umpire(string Name) : name(Name) {}
    string GetName() {
        return name;
    }
    void chageName(string Name) {
        name = Name;
    }

};
