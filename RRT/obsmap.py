import matplotlib.pyplot as plt
import numpy as np
class map(object):
    def __init__(self):
        self.width = 8
        self.depth = 5
        self.obs = ([1.4,1.4,0.25,1],[3.25,0,0.25,1],[5.8,1,1,0.25],[6.35,2.6,0.25,1],[3.5,2.375,1,0.25],[1.2,3.75,1,0.25],[4.5,4,0.25,1])
        print('Init a Map with',self.width,'*',self.depth)
    def print_map(self):
        fig = plt.figure()
        ax = fig.add_subplot(111)
        for rec_info in self.obs:
            rec = plt.Rectangle([rec_info[0],rec_info[1]],rec_info[2],rec_info[3],color = "black")
            ax.add_patch(rec)
        ax.axis('equal')
        plt.plot([0,0],[0,self.depth],'k')
        plt.plot([0,self.width],[0,0],'k')
        plt.plot([self.width,self.width],[0,self.depth],'k')
        plt.plot([0,self.width],[self.depth,self.depth],'k')