## 快速拓展随机树

### 食用方法

-  打开 test.py，运行
-  修改起始点和目标点都在在 test.py 一开头的pint 和 goal 中
-  地图包括障碍物在obsmap.py中。
-  规划空间以ICRA2019的场地为例，路径连通性判断暂时用的简单的起始和终止点判断，事实上这是不对的。不过采用BRT（Backwards Reachability Tube）可以给障碍物加个“气泡”，从而保证不撞上。具体参考FaSTrack论文。
