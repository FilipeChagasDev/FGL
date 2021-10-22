#include "../../fgl/base/list.hpp"
#include <iostream>

int main()
{
    List<int> mylist;

    mylist.pushEnd(1);
    mylist.pushEnd(2);
    mylist.pushEnd(3);
    mylist.pushEnd(4);
    mylist.pushEnd(5);

    std::cout << "Begin: " << mylist.getBegin() << std::endl;
    std::cout << "End: " << mylist.getEnd() << std::endl;
    std::cout << "Len: " << mylist.getLen() << std::endl;
    
    std::cout << std::endl << "Iteration" << std::endl;

    for(Iterator<int> i = mylist.getIteratorBegin(); not i.isNull(); i.foward())
    {
        std::cout << i.getData();
    }

    std::cout << std::endl << std::endl << "Rev. Iteration" << std::endl;

    for(Iterator<int> i = mylist.getIteratorEnd(); not i.isNull(); i.back())
    {
        std::cout << i.getData();
    }

    mylist.clear();
    mylist.pushBegin(1);
    mylist.pushBegin(2);
    mylist.pushBegin(3);
    mylist.pushBegin(4);
    mylist.pushBegin(5);

    std::cout << std::endl << std::endl << "Iteration" << std::endl;

    for(Iterator<int> i = mylist.getIteratorBegin(); not i.isNull(); i.foward())
    {
        std::cout << i.getData();
    }

    std::cout << std::endl << std::endl << "Rev. Iteration" << std::endl;

    for(Iterator<int> i = mylist.getIteratorEnd(); not i.isNull(); i.back())
    {
        std::cout << i.getData();
    }

    mylist.clear();
    mylist.pushEnd(1);
    mylist.pushEnd(2);
    mylist.pushEnd(3);
    mylist.pushEnd(4);
    mylist.pushEnd(5);

    std::cout << std::endl << std::endl << "Pop begin" << std::endl;

    for(int j = 1; j <= 6; j++)
    {
        for(Iterator<int> i = mylist.getIteratorBegin(); not i.isNull(); i.foward())
        {
            std::cout << i.getData();
        }

        std::cout << std::endl << mylist.popBegin() << " Len: " << mylist.getLen() << std::endl;
    }

    mylist.pushEnd(1);
    mylist.pushEnd(2);
    mylist.pushEnd(3);
    mylist.pushEnd(4);
    mylist.pushEnd(5);

    std::cout << std::endl << "Pop end" << std::endl;

    for(int j = 1; j <= 6; j++)
    {
        for(Iterator<int> i = mylist.getIteratorBegin(); not i.isNull(); i.foward())
        {
            std::cout << i.getData();
        }

        std::cout << std::endl << mylist.popEnd() << " Len: " << mylist.getLen() << std::endl;
    }

    mylist.pushEnd(1);
    mylist.pushEnd(2);
    mylist.pushEnd(3);
    mylist.pushEnd(4);
    mylist.pushEnd(5);

    std::cout << std::endl << "Remove pairs" << std::endl;
    for(Iterator<int> i = mylist.getIteratorBegin(); not i.isNull(); i.foward())
    {
        for(Iterator<int> j = mylist.getIteratorBegin(); not j.isNull(); j.foward())
        {
            std::cout << j.getData();
        }
        
        std::cout << std::endl;

        if(i.getData() % 2 == 0)
            std::cout << "removing " << i.getData() << " " << mylist.removeItemAndGoBack(i) << " Len: " << mylist.getLen() << std::endl;
    }

    mylist.clear();
    mylist.pushEnd(1);
    mylist.pushEnd(2);
    mylist.pushEnd(3);
    mylist.pushEnd(4);
    mylist.pushEnd(5);

    std::cout << std::endl << "Remove odds" << std::endl;
    for(Iterator<int> i = mylist.getIteratorBegin(); not i.isNull(); i.foward())
    {
        for(Iterator<int> j = mylist.getIteratorBegin(); not j.isNull(); j.foward())
        {
            std::cout << j.getData();
        }
        
        std::cout << std::endl;

        if(i.getData() % 2 == 1)
        {
            if(i.isBegin())
                std::cout << "removing " << i.getData() << " " << mylist.removeItemAndGoFoward(i) << " Len: " << mylist.getLen() << std::endl;
            else 
                std::cout << "removing " << i.getData() << " " << mylist.removeItemAndGoBack(i) << " Len: " << mylist.getLen() << std::endl;
        }
    }

    mylist.clear();
    mylist.pushEnd(1);
    mylist.pushEnd(2);
    mylist.pushEnd(3);
    mylist.pushEnd(4);
    mylist.pushEnd(5);

    std::cout << std::endl << "Duplicate pairs (PB)" << std::endl;
    for(Iterator<int> i = mylist.getIteratorBegin(); not i.isNull(); i.foward())
    {
        if(i.getData() % 2 == 0)
            mylist.pushBefore(i.getData(), i);

        std::cout << i.getData() << " ";

        for(Iterator<int> j = mylist.getIteratorBegin(); not j.isNull(); j.foward())
        {
            std::cout << j.getData();
        }

        std::cout << " Len: " << mylist.getLen() << std::endl;
    }

    mylist.clear();
    mylist.pushEnd(1);
    mylist.pushEnd(2);
    mylist.pushEnd(3);
    mylist.pushEnd(4);
    mylist.pushEnd(5);

    std::cout << std::endl << "Duplicate pairs (PA)" << std::endl;
    for(Iterator<int> i = mylist.getIteratorBegin(); not i.isNull(); i.foward())
    {
        if(i.getData() % 2 == 0)
        {
            mylist.pushAfter(i.getData(), i);
            i.foward();
        }

        std::cout << i.getData() << " ";

        for(Iterator<int> j = mylist.getIteratorBegin(); not j.isNull(); j.foward())
        {
            std::cout << j.getData();
        }

        std::cout << " Len: " << mylist.getLen() << std::endl;
    }

    mylist.clear();
    mylist.pushEnd(1);
    mylist.pushEnd(2);
    mylist.pushEnd(3);
    mylist.pushEnd(4);
    mylist.pushEnd(5);

    std::cout << std::endl << "Duplicate odds (PB)" << std::endl;
    for(Iterator<int> i = mylist.getIteratorBegin(); not i.isNull(); i.foward())
    {
        if(i.getData() % 2 == 1)
            mylist.pushBefore(i.getData(), i);

        std::cout << i.getData() << " ";

        for(Iterator<int> j = mylist.getIteratorBegin(); not j.isNull(); j.foward())
        {
            std::cout << j.getData();
        }

        std::cout << " Len: " << mylist.getLen() << std::endl;
    }

    mylist.clear();
    mylist.pushEnd(1);
    mylist.pushEnd(2);
    mylist.pushEnd(3);
    mylist.pushEnd(4);
    mylist.pushEnd(5);

    std::cout << std::endl << "Duplicate odds (PA)" << std::endl;
    for(Iterator<int> i = mylist.getIteratorBegin(); not i.isNull(); i.foward())
    {
        if(i.getData() % 2 == 1)
        {
            mylist.pushAfter(i.getData(), i);
            i.foward();
        }

        std::cout << i.getData() << " ";

        for(Iterator<int> j = mylist.getIteratorBegin(); not j.isNull(); j.foward())
        {
            std::cout << j.getData();
        }

        std::cout << " Len: " << mylist.getLen() << std::endl;
    }

    std::cout << std::endl << "Memory leakage test" << std::endl;

    while (true)
    {
        List<int> mylist;
        mylist.pushEnd(1);
        mylist.pushEnd(2);
        mylist.pushEnd(3);
        mylist.pushEnd(4);
        mylist.pushEnd(5);
    }
    
    return 0;
}
