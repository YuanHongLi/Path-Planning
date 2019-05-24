from obsmap import *
from rrt import *
map_ = map()
pint = [0.5,0.5]
goal = [7.5,4.5]
K = 400 #迭代此时
dq = 0.2 #拓展距离
Threshold = 0.2 #是否到达终点的阈值
T=[]
path = []
result = buildRRT(pint,goal,K,dq,Threshold,map_,T,path)
map_.print_map()
test = [0,1,2]
for node in T:
    plt.plot(node[0],node[1],'.')
#print(len(T))
plt.plot(goal[0],goal[1],'*')
if result==True :
    print('successfully planning a path')
    path_ = [goal]
    path_index = -1
    counter = 0
    #print(path)
    while path_index !=0:
        path_.append(T[path_index])
        path_index = path[path_index]
        counter = counter+1
    path_.append(pint)
    for i in range(1,len(path_)):
        plt.plot([path_[i-1][0],path_[i][0]],[path_[i-1][1],path_[i][1]],'r',lw = 3)

plt.show()

