**请把CMakeLists.txt文件的第9行改为你电脑上的Qt的相应的安装路径**  
**请把工作目录设为项目文件夹**

## 90坦克项目文件说明

### 根目录下：  
* startWidget .h .cpp .ui  
开始窗口，可以注册或登录
* chooseWidget .h .cpp .ui  
模式选择窗口，有单人闯关，双人对战，用户信息查询
* gameWidget .h .cpp .ui  
游戏界面窗口 (其中重写了键盘事件，用于玩家坦克的移动与开火)
* res.qrc   
资源文件
* main.cpp  
程序入口

### gameObjectClasses文件夹下：

此文件夹下存放了所有的游戏对象类

* gameObject .h .cpp  
所有游戏对象类的基类。
* movableObject .h .cpp   
所有可移动的游戏对象类的基类，其子类必须重写Update函数，这将在每帧被调用。Update函数主要用于更新位置与碰撞检测。

其余文件为具体游戏对象类的实现。

### gameManagerClasses文件夹：
* gameDefine .h .cpp   
一些游戏常量。  

~~gameObjectPool .h .cpp~~   
~~游戏对象池，负责创建与回收被移除场景的游戏对象，使同一对象可重复利用，减少性能消耗。~~
* gameControl .h .cpp   
重要的游戏控制类，主要负责每帧的更新，游戏结束的判定。

### database文件夹：

user_info.json文件存储用户信息，其中键为用户名，值有password，times，times记录每关的最短通关时间。  

  
  
  
*有时候会TM莫名其妙闪退，~~不知道为什么~~可能是一些游戏对象没有及时delete。*

