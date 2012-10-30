#include <algorithm>
#include <vector>
#include <ctime>

#include "Heap.h"
#include "Number.h"
#include "Tree.h"
#include "AvlTree.h"

using namespace std;


void aufgabe1_1() 
{
    Number n1(2.2f);
    Number n2(1);
    Number n3(55);
    Number n4(42);
    Number n5(32);

    double d1 = 2;
    double d2 = 1;
    double d3 = 55;
    double d4 = 42;
    double d5 = 32;

    Heap<Number> numberHeap(5);
    Heap<double> doubleHeap(5);


    doubleHeap.push(d1);
    doubleHeap.push(d2);
    doubleHeap.push(d3);
    doubleHeap.push(d4);
    doubleHeap.push(d5);

    doubleHeap.print();

    std::cout << std::endl;

    numberHeap.push(n1);
    numberHeap.push(n2);
    numberHeap.push(n3);
    numberHeap.push(n4);
    numberHeap.push(n5);

    numberHeap.print();

}

void aufgabe1_2()
{
    
    vector<int> intVector;
    const int numElements = 10;
    

    cout << endl << "vector with rand values:" << endl;

    for (int i = 0; i < numElements; i++) 
    {
        intVector.push_back(rand()%1000);
        cout << intVector[i] << endl;
    }


    cout << endl << "heapified:" << endl;
    Heap<int> intHeap(numElements);
    
    for (int i = 0; i < numElements; i++) 
    {
        intHeap.push(intVector[i]);
    }

    intHeap.print();

    for (int i = 0; i < numElements; i++) 
    {
        intVector[numElements-1-i] = intHeap.top();
        intHeap.pop();
    }

    cout << endl << "sorted:" << endl;

    for (int i = 0; i < numElements; i++) 
    {
        cout << intVector[i] << endl;
    }

}

void aufgabe1_3()
{
    const int numElements = 10;

    

    for (int multiplier = 1; multiplier <= 10000; multiplier= multiplier*10)
    {
        Tree<double> tree;
        AvlTree<double> avlTree;

		for (int i = 0; i < numElements*multiplier; i ++)
        {
			double randValue = rand()%10000 / 100.0f;
            tree.insert(randValue);
            avlTree.insert(randValue);
        }

        cout << "Total elements: " << numElements * multiplier <<
            "\ttree height: " << tree.height() << 
            "\t avlTree height: " << avlTree.height() << endl;

    }
}

int main()
{
    srand(time(0));


    cout << "---- aufgabe 1 ------------------------" << endl << endl;
    aufgabe1_1();

    cout << "---- aufgabe 2 ------------------------" << endl << endl;
    aufgabe1_2();

    cout << "---- aufgabe 3 ------------------------" << endl << endl;
    aufgabe1_3();

    return 0;
}
