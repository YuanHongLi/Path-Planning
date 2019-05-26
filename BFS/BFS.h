#ifndef BFS_H
#define BFS_H
#include "iostream"
#include <vector>
#include "assert.h"
#include "queue"
#include "limits"
#include "cmath"
#include <algorithm>
//#include <functional>
using namespace std;
class BFS
{
public:
    BFS();
    ~BFS();
    void ShowMap();
    void SetGoal(int x,int y){goal_x = x;goal_y = y;};
    void SetInit(int x,int y){init_x = x;init_y = y;};
    void Run();
private:
    int width;
    int depth;
    int goal_x;
    int goal_y;
    int init_x;
    int init_y;
    vector<int> cost_map;
    vector<int> parent;
    vector<int> path;
    int XY2Index(int x,int y);
    vector<int> Index2XY(int index);
    void SearchNext(int index,vector<int>& next);
    bool IsVaild(int i,int j);
};
BFS::BFS()
{
    //init map
    this->width = 8;
    this->depth = 6;
    this->cost_map.resize(this->depth*this->width,0);
    //add obstacle
    this->cost_map[XY2Index(5,3)]=255;
    this->cost_map[XY2Index(5,4)]=255;
    this->cost_map[XY2Index(5,5)]=255;
    cout<<"cost_map size "<<this->cost_map.size()<<endl;
    this->parent.resize(this->depth*this->width,std::numeric_limits<int>::max());
}
BFS::~BFS()
{
    //std::cout<<"Stop"<<std::endl;
}
int BFS::XY2Index(int x,int y) //Giving a (x,y),return the index in costmap
{
    assert(x>0&&y>0&&x<=this->width&&y<=this->depth);
    return (y-1)*this->width+(x-1);
}
vector<int> BFS::Index2XY(int index)
{
    return {index%this->width+1,index/this->width+1};
}
void BFS::ShowMap()
{
    for(int i = this->depth-1;i>=0;--i)
    {
        for(int j = 0;j<this->width;++j)
        {
            assert(this->cost_map[XY2Index(j+1,i+1)]==0||this->cost_map[XY2Index(j+1,i+1)]==255);
            if(i==goal_y-1&&j==goal_x-1)
            {
                std::cout<<'&'<<'\t';
                continue;
            }
            if(i==init_y-1&&j==init_x-1)
            {
                std::cout<<'@'<<'\t';
                continue;
            }
            auto ite = std::find(this->path.begin(),this->path.end(),XY2Index(j+1,i+1));
            if(ite!=path.end())
            {
                std::cout<<'.'<<'\t';
                continue;
            }
            if(this->cost_map[XY2Index(j+1,i+1)]==0)
                std::cout<<'0'<<'\t';
            else if(this->cost_map[XY2Index(j+1,i+1)]==255)
                std::cout<<'*'<<'\t';
        }
        std::cout<<endl;
    }
}
void BFS::Run()
{
    queue<int> openlist;
    vector<int> state(this->width*this->depth,0);
    int current = XY2Index(init_x,init_y);
    openlist.push(current);
    while(!openlist.empty())
    {
        current = openlist.front();
        openlist.pop();
        if(current==XY2Index(goal_x,goal_y))
        {
            std::cout<<"Find Path!"<<std::endl;
            int temp = current;
            while(this->parent.at(temp)!=XY2Index(init_x,init_y))
            {
                this->path.push_back(temp);
                temp = this->parent.at(temp);
            }
            this->path.push_back(temp);
        }
        state[current] = -1;
        vector<int> next;
        SearchNext(current,next);
        for(int i=0;i<next.size();++i)
        {
            if(this->cost_map.at(next[i])==255||state[next[i]]==-1)
                continue;
            else
            {
                openlist.push(next[i]);
                state.at(next[i])=-1;
                this->parent.at(next[i])=current;
            }
        }
    }
    
}
void BFS::SearchNext(int index,vector<int>& next)
{
    next.clear();
    int i = Index2XY(index)[0];
    int j = Index2XY(index)[1];
    if(IsVaild(i-1,j-1))
        next.push_back(XY2Index(i-1,j-1));
    if(IsVaild(i,j-1))
        next.push_back(XY2Index(i,j-1));
    if(IsVaild(i+1,j-1))
        next.push_back(XY2Index(i+1,j-1));
    if(IsVaild(i-1,j))
        next.push_back(XY2Index(i-1,j));
    if(IsVaild(i+1,j))
        next.push_back(XY2Index(i+1,j));
    if(IsVaild(i-1,j+1))
        next.push_back(XY2Index(i-1,j+1));
    if(IsVaild(i,j+1))
        next.push_back(XY2Index(i,j+1));
    if(IsVaild(i+1,j+1))
        next.push_back(XY2Index(i+1,j+1));
}
bool BFS::IsVaild(int i,int j)
{
    return (i>0)&&(i<=this->width)&&(j>0)&&(j<=this->depth);
}
#endif