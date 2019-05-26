#include "BFS.h"
using namespace std;
int main()
{
    BFS test;
    //test.ShowMap();
    test.SetGoal(7,5);
    test.SetInit(1,1);
    test.Run();
    test.ShowMap();
    return 0 ;
}