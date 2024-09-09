# 简单复合机械臂控制程序
## 使用方法 Usage
    1.在你的.ino文件中输入#include "Arm.h"
    2.在setup()函数中进行初始化
## 开放接口与使用方法 functions&usages
### Arm类方法
#### 1.void init(short int *pins, short int length)
    pins:传入一个包含所有引脚的变量或常亮数组
    length:传入数组的长度
    这个函数的作用是进行Arm类的初始化，在每一条机械手臂创建变量之后都需要进行初始化
#### 2.void test_arm()
    对手臂进行测试 Development!
#### 3.void Slow_move(short int *pulse_array, short int speed)
    缓慢进行运动
    pulse_array:输入脉宽数组
    speed:speed 越大越慢
#### 4.void insistace(short int time)
    对机械臂的姿势进行保持
    time:机械臂保持的时间