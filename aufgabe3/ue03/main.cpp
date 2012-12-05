#include <iostream>
#include "SkipList.h"

using namespace std;

int main()
{

    SkipList<int, double> sl(0.5f, 5);

    double test = 3.1415926535;
    int key = 42;
    cout << "Test 1: insert\t - ";
    cout << (sl.insert(key, test) ? "OK" : "FAIL");
    cout << endl;

    
    cout << "Test 2: search\t - ";
    cout << (sl.search(key) == test ? "OK" : "FAIL");
    cout << endl;

    cout << "Test 3: search for not existing key\t - ";
    try 
    {
        sl.search(1337);
        cout << "FAIL" << endl;
    }
    catch(NotFoundException e)
    {
        cout << "OK" << endl;
    }


    const unsigned int toalInserts = 100;
    cout << "Test 4: insert a lot of random numbers\t - ";
    
    bool success = true;

    for (unsigned int i = 0; i < toalInserts; i++)
    {
        double randDouble = rand()/double(RAND_MAX)*1000;
        if (!sl.insert(i, randDouble))
        {
            success = false;
            break;
        }
    }

    if (success)
        cout << "OK" << endl;
    else
        cout << "FAIL" << endl;


    cout << "TESTS DONE" << endl;
    

    return 0;
}