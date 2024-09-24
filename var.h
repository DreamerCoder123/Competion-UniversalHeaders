#pragma once
#include "qtis\qtis.h"
#include "Servo\Arm.h"
#include "qtis\qtis.h"
#include "dcmotor\dcmotor.h"
unsigned char arms_list[6] = {10, 9, 8, 13, 12, 11};
const bool DUBUGGING = false;
Servo turnTable(2);             // 小车转盘 2450-350 脉宽增加顺时针转动
Arm arms;                       // 6机械臂
qtis QTI_LOWDEG[2] = {
    qtis(23, 2), // 前面左边
    qtis(24, 1), // 前面右边
};
qtis QTI_HIGHDEG_L[2] = {
    qtis(23, 1),
    qtis(22, 1),
};
qtis QTI_HIGHDEG_R[2] = {
    qtis(24, 1),
    qtis(25, 1),
};
muti_qti qtis_lowdeg(QTI_LOWDEG, 2);       // 低角度旋转的qti
muti_qti qtis_highdeg_L(QTI_HIGHDEG_L, 2); // 直角旋转qti
muti_qti qtis_highdeg_R(QTI_HIGHDEG_R, 2); // 直角旋转右边qti
namespace Arm_opreations
{
    namespace Arm_points
    {
        short int GRABBER_READY[] = {600, 1450, 1200, 1200, 1200, 1200};
        short int GRABBER_DOWN[] = {600, 1450, 2450, 1200, 1200, 1200};
        short int GRABBER_GRAB[] = {1300, 1650, 2550, 1150, 1200, 1250};
        short int GRABBER_RELEASE_1[] = {1300, 1800, 1450, 1700, 1400, 1200};
        short int GRABBER_RELEASE_2[] = {600, 1800, 1450, 1700, 1400, 1200};
        short int GRABBER_RUN[] = {1350, 600, 1400, 2150, 1700, 1150};
    }
    void arm_grab()
    {
        arms.Slow_move(Arm_points::GRABBER_READY, 100);
        arms.insistace(1000);
        arms.Slow_move(Arm_points::GRABBER_DOWN, 100);
        arms.insistace(1000);
        arms.Slow_move(Arm_points::GRABBER_GRAB, 100);
        arms.insistace(1000);
        arms.Slow_move(Arm_points::GRABBER_RELEASE_1, 100);
        arms.insistace(1000);
        arms.Slow_move(Arm_points::GRABBER_RELEASE_2, 200);
        arms.insistace(1000);
        arms.Slow_move(Arm_points::GRABBER_READY, 100);
        arms.insistace(1000);
    }
}