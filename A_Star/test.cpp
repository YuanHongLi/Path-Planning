#include <iostream>
#include "A_Star.h"
using namespace std;
int main()
{
    A_Star test;
    test.SetGoal(8,5);
    test.SetInit(1,1);
    test.ShowMap();
    test.Run();
    test.ShowMap();
    return 0;
}