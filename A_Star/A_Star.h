#ifndef A_STAR_H
#define A_STAR_H
#include "iostream"
#include <vector>
#include "assert.h"
#include "queue"
#include "limits"
#include "cmath"
#include <algorithm>
//#include <functional>
using namespace std;
class A_Star
{
public:
    A_Star();
    ~A_Star();
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
    static vector<int> F;
    vector<int> G;
    vector<int> parent;
    vector<int> path;
    int XY2Index(int x,int y);
    vector<int> Index2XY(int index);
    int ComputeMHD(int x0_index,int y0_index);
    struct Compare
    {
        bool operator() (const int &index1, const int &index2)
        {
           return A_Star::F.at(index1)>A_Star::F.at(index2);
        }
    };
    void SearchNext(int index,vector<int>& next);
    bool IsVaild(int i,int j);
    int MoveCost(int index1,int index2);
};
vector<int> A_Star::F;
A_Star::A_Star()
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
    this->F.resize(this->depth*this->width,std::numeric_limits<int>::max());
    this->G.resize(this->depth*this->width,std::numeric_limits<int>::max());
    this->parent.resize(this->depth*this->width,std::numeric_limits<int>::max());
}
A_Star::~A_Star()
{
    //std::cout<<"Stop"<<std::endl;
}
int A_Star::XY2Index(int x,int y) //Giving a (x,y),return the index in costmap
{
    assert(x>0&&y>0&&x<=this->width&&y<=this->depth);
    return (y-1)*this->width+(x-1);
}
vector<int> A_Star::Index2XY(int index)
{
    return {index%this->width+1,index/this->width+1};
}
void A_Star::ShowMap()
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
int A_Star::ComputeMHD(int x0_index,int y0_index)
{
    return 10*(std::abs(Index2XY(x0_index)[0]-Index2XY(y0_index)[0])+std::abs(Index2XY(x0_index)[1]-Index2XY(y0_index)[1]));
}
void A_Star::Run()
{
    vector<int> closeset;
    closeset.resize(this->depth*this->width,0);
    priority_queue<int,vector<int>,Compare> openlist;
    int current;
    openlist.push(XY2Index(init_x,init_y));
    G.at(XY2Index(init_x,init_y))=0;
    vector<int> next;
    while(!openlist.empty())
    {
        current = openlist.top();
        if(current == XY2Index(this->goal_x,this->goal_y))
        {
            cout<<"Find Path"<<endl;
            this->path.clear();
            int temp = current;
            while(temp!=XY2Index(this->init_x,init_y))
            {
                path.push_back(temp);
                temp = parent[temp];
            }
            break;
        }
        openlist.pop();
        closeset[current] = -1;
        SearchNext(current,next);
        for(int index_ : next)
        {
            if(closeset[index_]==-1||this->cost_map[index_]==255)
                continue;
            int move_cost = MoveCost(current,index_);
            if(G[index_]>G[current]+move_cost)
            {
                G[index_]=G[current]+move_cost;
                parent[index_] = current;
                F[index_] = G[index_] + ComputeMHD(index_,XY2Index(this->goal_x,this->goal_y));
                if(closeset[index_]==0)
                {
                    openlist.push(index_);
                    closeset[index_]=1;
                }
            }
        }
    }
}
void A_Star::SearchNext(int index,vector<int>& next)
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
bool A_Star::IsVaild(int i,int j)
{
    return (i>0)&&(i<=this->width)&&(j>0)&&(j<=this->depth);
}
int A_Star::MoveCost(int index1,int index2)
{
    if(Index2XY(index1)[0]==Index2XY(index2)[0]||Index2XY(index1)[1]==Index2XY(index2)[1])
        return 10;
    else
        return 15;
}
#endif