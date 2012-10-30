#include <iostream>
#include "mergelist.cpp"

using namespace std;

int main()


{
    intlist lists[3];

        intlist list_1;
        intlist list_2;
        intlist list_3;
        intlist list_4;

    list_1.push_front (1);
    list_1.push_front (30);
    list_2.push_front (5);
    list_2.push_front (20);
    list_3.push_front (2);
    list_3.push_front (13);

        lists[0] = list_1;
        lists[1] = list_2;
        lists[2] = list_3;


    list_4 = merge_lists(lists, 3);

    for (intlist::reverse_iterator it = list_4.rbegin();it!=list_4.rend();it++)

        {
    	    std::cout<<*it<<"";
        }

    std::cout<<std::endl;

    for (intlist::iterator it = list_4.begin();it!=list_4.end();it++)

    	    {
    	    	std::cout<<*it<<"";
    	    }

        std::cout<<std::endl;

    






    return 0;

}
