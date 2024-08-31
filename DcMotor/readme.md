# 直流电机的控制--DcMotor
## 使用方法
1. 头文件引入DcMotor.h
2. 使用全局变量定义哈
## 函数及其定义
### void run(int leftspeed,int rightspeed)
    1.leftspeed:左轮速度（我们这里默认你有两个轮子）
    2.rightspeed:右轮速度
    两个轮子的速度范围都是从-255~255
### DcMotor(short int red_l, short int black_l, short int red_r, short int black_r)
    此为类的构造函数，直流电机依靠两端的电势差进行运动，电势差越大，直流电机转动的速度越快。

    如此，我们需要引入4个pin，注意，这里的pin引入是有顺序的。正极（red）先，负极后，左边先，右边后。

    l=左边,r=右边,black=负极,red=正极