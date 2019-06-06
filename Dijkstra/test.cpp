#include "Dijkstra.h"
#include <iostream>
using namespace std;
int main()
{
    Dijkstra test;
    test.SetGoal(8,6);
    test.SetInit(1,1);
    test.Run();
    test.ShowMap();
    return 0;
}