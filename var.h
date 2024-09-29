#pragma once
#include "qtis\qtis.h"
#include "Servo\Arm.h"
#include "dcmotor\dcmotor.h"
unsigned char arms_list[7] = {10, 9, 8, 13, 12, 11, 2}; // 所有角度舵机的集合，包括转盘
const bool DUBUGGING = false;
Servo turnTable(2);         // 小车转盘 2450-350 脉宽增加顺时针转动
Arm arms;                   // 6机械臂
DcMotor wheels(4, 5, 6, 7); // 左右两边的轮子
qtis QTI_LOWDEG[2] = {
    qtis(23, 2), // 前面左边
    qtis(24, 1), // 前面右边
};
qtis QTI_HIGHDEG[2] = {
    qtis(22, 1), // 左左
    qtis(25, 2), // 右右
};
muti_qti qtis_highdeg(QTI_HIGHDEG, 2);
muti_qti qtis_lowdeg(QTI_LOWDEG, 2); // 低角度旋转的qti
namespace Arm_opreations
{
    namespace Arm_points
    {
        short int qti_points[7] = {1100, 2500, 2300, 1250, 500, 700, 2400}; // 灰度传感器巡线位点
    }
}
namespace qti_related
{
    void qti_run()
    {
        short int low = qtis_lowdeg._qtiread();
        short int high = qtis_highdeg._qtiread();
        if (high == 3) // 转弯90°
        {
            long long clock = millis();
            wheels.run(255, 255);
            delay(300); // 向前走一小段距离
            wheels.run(-255, 255);
            delay(500); // 向右走一段距离
            while (qtis_lowdeg._qtiread() != 1)
            {
                if (qtis_lowdeg._qtiread() == 2 || millis() - clock > 3000)
                {
                    break;
                    // 如果右转时间大于一段时间，就退出右转
                }
                wheels.run(-255, 255);
            }
            wheels.run(255, 255);
            delay(50);
            return;
        }
        switch (low) // 微调
        {
        case 3:
        case 0:
            wheels.run(255, 255); // 向前走
            break;
        case 2:
            wheels.run(255, 0); // 向右走
            break;
        case 1:
            wheels.run(0, 255); // 向左走
            break;
        default:
            wheels.run(200, 200); // 向前走
        }
    }
}