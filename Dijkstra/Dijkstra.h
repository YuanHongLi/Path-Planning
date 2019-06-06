#ifndef Dijkstra_H
#define Dijkstra_H
#include "iostream"
#include <vector>
#include "assert.h"
#include "queue"
#include "limits"
#include "cmath"
#include <algorithm>
//#include <functional>
using namespace std;
class Dijkstra
{
public:
    Dijkstra();
    ~Dijkstra();
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
    vector<int> path;
    vector<int> parent;
    static vector<int> Dis;
    int XY2Index(int x,int y);
    vector<int> Index2XY(int index);
    void SearchNext(int index,vector<int>& next);
    bool IsVaild(int i,int j);
    int MoveCost(int index1,int index2);
    struct compare
    {
        bool operator() (const int& a, const int& b)
        {
            return Dijkstra::Dis.at(a)>Dijkstra::Dis.at(b);
        }
    };
};
vector<int> Dijkstra::Dis;
Dijkstra::Dijkstra()
{
    //init map
    this->width = 8;
    this->depth = 6;
    this->cost_map.resize(this->depth*this->width,0);
    //add obstacle
    this->cost_map[XY2Index(5,1)]=255;
    this->cost_map[XY2Index(5,2)]=255;
    this->cost_map[XY2Index(5,3)]=255;
    this->cost_map[XY2Index(5,4)]=255;
    this->cost_map[XY2Index(5,5)]=255;
    cout<<"cost_map size "<<this->cost_map.size()<<endl;
    this->Dis.resize(this->depth*this->width,std::numeric_limits<int>::max());
    this->parent.resize(this->depth*this->width,-1);
}
Dijkstra::~Dijkstra()
{
    //std::cout<<"Stop"<<std::endl;
}
int Dijkstra::XY2Index(int x,int y) //Giving a (x,y),return the index in costmap
{
    assert(x>0&&y>0&&x<=this->width&&y<=this->depth);
    return (y-1)*this->width+(x-1);
}
vector<int> Dijkstra::Index2XY(int index)
{
    return {index%this->width+1,index/this->width+1};
}
void Dijkstra::ShowMap()
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
void Dijkstra::Run()
{
    vector<int> state(this->width*this->depth,0);
    priority_queue<int,vector<int>,compare> openlist;
    openlist.push(XY2Index(this->init_x,this->init_y));
    this->Dis.at(XY2Index(this->init_x,this->init_y))=0;
    vector<int> next;
    while(!openlist.empty())
    {
        int cur = openlist.top();
        openlist.pop();
        if(cur==XY2Index(this->goal_x,this->goal_y))
        {
            cout<<"Find Path!"<<endl;
            this->path.clear();
            int temp = this->parent.at(cur);
            while(temp!=XY2Index(this->init_x,this->init_y))
            {
                this->path.push_back(temp);
                temp = this->parent[temp];
            }
            break;
        }
        state[cur]=-1;
        SearchNext(cur,next);
        for(int i=0;i<next.size();++i)
        {
            if(this->cost_map.at(next[i])==255||state[next[i]]==-1)
                continue;
            if(this->Dis.at(next[i])>this->Dis.at(cur)+MoveCost(cur,next[i]))
                {this->Dis.at(next[i])=this->Dis.at(cur)+MoveCost(cur,next[i]);this->parent.at(next[i])=cur;}
            if(state.at(next[i])==0)
            {
                state.at(next[i])=1;
                openlist.push(next[i]);
            }
        }
    }
}
void Dijkstra::SearchNext(int index,vector<int>& next)
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
bool Dijkstra::IsVaild(int i,int j)
{
    return (i>0)&&(i<=this->width)&&(j>0)&&(j<=this->depth);
}
int Dijkstra::MoveCost(int index1,int index2)
{
    if(Index2XY(index1)[0]==Index2XY(index2)[0]||Index2XY(index1)[1]==Index2XY(index2)[1])
        return 10;
    else
        return 15;
}
#endif