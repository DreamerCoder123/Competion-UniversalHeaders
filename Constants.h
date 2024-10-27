#pragma once
#include "qtis\qtis.h"
#include "Servo\Arm.h"
#include "dcmotor\dcmotor.h"
#define RUN_TOWARDS 150, 150                             // 向后行进
#define RUN_AFTERWARDS -170, -170                        // 向前行进
unsigned char arms_list[7] = {10, 45, 8, 13, 12, 11, 2}; // 所有角度舵机的集合，包括转盘
short int dur[7] = {1200, 1200, 1200, 1200, 1200, 1200, 1200};
Arm arms;                   // 存储7个机械臂的数组
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
/**
 * @brief this namespace contains all opreations could be done to the robot arm.
 * @todo finishing the testing of points
 */
namespace Arm_opreations
{
    namespace Arm_points
    {
        short int qti_points[7] = {1250, 2450, 2350, 1200, 650, 1200, 2200}; // 灰度传感器巡线位点
        namespace Catch_Book
        {
            namespace constants
            {
                const short int p_base = 2100;     // 运动到书架上抓住书的地基
                const short int rigp1_base = 1361; // 运动到右边的第一本书
                const short int rigp2_base = 1425; // 运动到右边的第二本书
                const short int left1_base = 943;  // 运动到左边的第一本书
                const short int left2_base = 907;  // 运动到左边的第二本书

            }
            short int p1[] = {1300, 1250, 1350, 1200, 650, 1200, constants::p_base};
            short int p2[] = {1300, 750, 1750, 1200, 650, 1200, constants::p_base};
            short int p3[] = {1450, 750, 1750, 1200, 650, 1200, constants::p_base};
            short int p4[] = {1450, 1850, 1750, 1200, 650, 1200, constants::p_base};
            // 运动到书框位置抓书 delta=450
            short int rigp1[] = {1450, 1850, 1950, 1200, 650, 1200, constants::rigp1_base};
            short int rigp2[] = {1450, 950, 1950, 1200, 650, 1200, constants::rigp1_base};
            short int rigp3[] = {1400, 950, 1950, 1200, 650, 1200, constants::rigp1_base};
            //
            short int rigp_1[] = {1450, 1850, 1950, 1200, 650, 1200, constants::rigp2_base};
            short int rigp_2[] = {1450, 950, 1950, 1200, 650, 1200, constants::rigp2_base};
            short int rigp_3[] = {1400, 950, 1950, 1200, 650, 1200, constants::rigp2_base};
            // 运动到左边释放书
            short int lefp1[] = {1450, 1650, 1950, 1200, 650, 1200, constants::left1_base};
            short int lefp2[] = {1450, 950, 1950, 1200, 650, 1200, constants::left1_base};
            short int lefp3[] = {1400, 950, 1950, 1200, 650, 1200, constants::left1_base};

            short int lefp1_[] = {1450, 1650, 1950, 1200, 650, 1200, constants::left2_base};
            short int lefp2_[] = {1450, 950, 1950, 1200, 650, 1200, constants::left2_base};
            short int lefp3_[] = {1400, 950, 1950, 1200, 650, 1200, constants::left2_base};
            void catchbook_right()
            {
                arms.Slow_move(Arm_opreations::Arm_points::Catch_Book::p1, 50);
                arms.Slow_move(Arm_opreations::Arm_points::Catch_Book::p2, 50);
                arms.Slow_move(Arm_opreations::Arm_points::Catch_Book::p3, 20);
                arms.Slow_move(Arm_opreations::Arm_points::Catch_Book::p4, 50);
                arms.Slow_move(Arm_opreations::Arm_points::Catch_Book::rigp1, 25);
                arms.Slow_move(Arm_opreations::Arm_points::Catch_Book::rigp2, 40);
                arms.Slow_move(Arm_opreations::Arm_points::Catch_Book::rigp3, 10);
                arms.Slow_move(Arm_opreations::Arm_points::Catch_Book::rigp1, 20);
                arms.Slow_move(Arm_opreations::Arm_points::qti_points, 50);
            }

            void catchbook_right_()
            {
                arms.Slow_move(Arm_opreations::Arm_points::Catch_Book::p1, 50);
                arms.Slow_move(Arm_opreations::Arm_points::Catch_Book::p2, 50);
                arms.Slow_move(Arm_opreations::Arm_points::Catch_Book::p3, 20);
                arms.Slow_move(Arm_opreations::Arm_points::Catch_Book::p4, 50);
                arms.Slow_move(Arm_opreations::Arm_points::Catch_Book::rigp_1, 25);
                arms.Slow_move(Arm_opreations::Arm_points::Catch_Book::rigp_2, 40);
                arms.Slow_move(Arm_opreations::Arm_points::Catch_Book::rigp_3, 10);
                arms.Slow_move(Arm_opreations::Arm_points::Catch_Book::rigp_1, 20);
                arms.Slow_move(Arm_opreations::Arm_points::qti_points, 50);
            }
            void catchbook_left()
            {
                arms.Slow_move(Arm_opreations::Arm_points::Catch_Book::p1, 50);
                arms.Slow_move(Arm_opreations::Arm_points::Catch_Book::p2, 30);
                arms.Slow_move(Arm_opreations::Arm_points::Catch_Book::p3, 20);
                arms.Slow_move(Arm_opreations::Arm_points::Catch_Book::p4, 50);
                arms.Slow_move(Arm_opreations::Arm_points::Catch_Book::lefp1, 45);
                arms.Slow_move(Arm_opreations::Arm_points::Catch_Book::lefp2, 40);
                arms.Slow_move(Arm_opreations::Arm_points::Catch_Book::lefp3, 10);
                arms.Slow_move(Arm_opreations::Arm_points::Catch_Book::lefp1, 20);
                arms.Slow_move(Arm_opreations::Arm_points::qti_points, 50);
            }
            void catchbook_left_()
            {
                arms.Slow_move(Arm_opreations::Arm_points::Catch_Book::p1, 50);
                arms.Slow_move(Arm_opreations::Arm_points::Catch_Book::p2, 30);
                arms.Slow_move(Arm_opreations::Arm_points::Catch_Book::p3, 20);
                arms.Slow_move(Arm_opreations::Arm_points::Catch_Book::p4, 50);
                arms.Slow_move(Arm_opreations::Arm_points::Catch_Book::lefp1_, 45);
                arms.Slow_move(Arm_opreations::Arm_points::Catch_Book::lefp2_, 40);
                arms.Slow_move(Arm_opreations::Arm_points::Catch_Book::lefp3_, 10);
                arms.Slow_move(Arm_opreations::Arm_points::Catch_Book::lefp1_, 20);
                arms.Slow_move(Arm_opreations::Arm_points::qti_points, 50);
            }
        }
        namespace Chan_book
        {
            namespace constants
            {
                const short int rig_base = 0;
                const short int lef_base = 0;

            }
            // TODO Test points of basement using Qt
            void left()
            {
            }
            void right()
            {
            }
        }
    }

}
namespace qti_related
{
    void qti_run()
    {
        // TODO 将右转逻辑改为左转 已完成
        short int low = qtis_lowdeg._qtiread();
        short int high = qtis_highdeg._qtiread();
        if (high == 3) // 转弯90°
        {
            long long clock = millis();
            wheels.run(255, 255);
            delay(200); // 向前走一小段距离
            wheels.run(255, -255);
            delay(200); // 向左走一段距离
            while (qtis_lowdeg._qtiread() != 2)
            {
                if (qtis_lowdeg._qtiread() == 1 || millis() - clock > 500)
                {
                    break;
                    // 如果左转时间大于一段时间，就退出左转
                }
                wheels.run(255, -255);
            }
            wheels.run(RUN_TOWARDS);
            delay(50);
            return;
        }
        switch (low) // 微调
        {
        case 3:
        case 0:
            wheels.run(RUN_TOWARDS); // 向前走
            break;
        case 2:
            wheels.run(255, 0); // 向右走
            break;
        case 1:
            wheels.run(0, 255); // 向左走
            break;
        default:
            wheels.run(RUN_TOWARDS); // 向前走
        }
    }
}