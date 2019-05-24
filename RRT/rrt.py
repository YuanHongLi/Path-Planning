import random
from obsmap import *
def sample(x):
    coff = random.uniform(0,1)
    if coff < 0.2 :
        return x
    else:
        return random.uniform(0,8), random.uniform(0,5)

def find_min(T,goal):
    dis = 10000
    num = -1
    for i in range(len(T)):
        temp = (T[i][0]-goal[0])**2+(T[i][1]-goal[1])**2
        if temp <dis:
            dis = temp
            num = i
    return num

def dis(a,b):
    return ((a[0]-b[0])**2+(a[1]-b[1])**2)**0.5

def check(posi,map):
    if posi[0]<0 or posi[0]>map.width or posi[1]>map.depth or posi[1]<0:
        return False
    for i in range(len(map.obs)):
        if posi[0]-map.obs[i][0]<=map.obs[i][2] and posi[0]-map.obs[i][0]>=0 and posi[1]-map.obs[i][1]<=map.obs[i][3] and posi[1]-map.obs[i][1]>=0:
            return False
    return True

def extend(near,goal,dq,obsmap):
    if dis(near,goal)<0.02:
        return [-1,-1]
    temp = [near[0]+(goal[0]-near[0])*(dq)/dis(near,goal),near[1]+(goal[1]-near[1])*(dq)/dis(near,goal)]
    if check(temp,obsmap):
        return temp
    else:
        print('obs exit!')
        return [-1,-1]


def buildRRT(pinit,goal,K,dq,Threshold,map,node,path):
    node.append(pinit)
    path.append(0)
    for k in range(K):
        temp = sample(goal)
        temp_num = find_min(node,goal)
        nearest = node[temp_num]
        if dis(nearest,goal)<Threshold:
            return True
        ext_ = extend(nearest,temp,dq,map)
        if ext_[0]!=-1:
            node.append(ext_)
            path.append(temp_num)
    return False
            
        



