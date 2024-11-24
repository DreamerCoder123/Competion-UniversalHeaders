#pragma once
#include "qtis\qtis.h"
#include "Servo\Arm.h"
#include "dcmotor\dcmotor.h"
#include "HUSKYLENS.h"
#define RUN_TOWARDS 90, 90                              // 向前行进
#define RUN_AFTERWARDS -80, -80                         // 向后行进
#define RUN_LEFT 140, -140                              // 向左转弯
#define RUN_RIGHT -100, 100                             // 向右转弯
#define RUN_STOP 0, 0                                   // 停止
short int speedLeft = 70, speedRight = 70;              // 左右轮子速度
unsigned char arms_list[7] = {10, 9, 8, 13, 12, 11, 2}; // 所有角度舵机的集合，包括转盘
short int dur[7] = {1200, 1200, 1200, 1200, 1200, 1200, 1200};
Arm arms;                   // 存储7个机械臂的数组
DcMotor wheels(4, 5, 6, 7); // 左右两边的轮子
qtis QTI_LOWDEG[2] = {
    qtis(23, 2), // 前面左边
    qtis(24, 1), // 前面右边
}; // 在内侧的两个QTI
qtis QTI_HIGHDEG[2] = {
    qtis(22, 1), // 左左
    qtis(25, 2), // 右右
}; // 在外侧的两个QTI
muti_qti qtis_highdeg(QTI_HIGHDEG, 2);
muti_qti qtis_lowdeg(QTI_LOWDEG, 2); // 低角度旋转的qti
short int r_num = 0;                 // 右边书框内书的数量
short int l_num = 0;                 // 左边书框内书的数量
HUSKYLENS husky;                     //?注意，这里不得不将哈士奇的定义放在这里。
// 屎山代码发力了！！！(笑)
namespace Arm_opreations
{
    short int scan[7] = {2300, 2350, 2350, 1200, 650, 1200, 1350};       // husky传感器观测位点
    short int qti_points[7] = {2300, 2350, 2350, 1200, 650, 1200, 1350}; // 灰度传感器巡线位点
    namespace Catch_Book
    {
        namespace constants
        {
            const short int p_base = 1350;            // 运动到书架上抓住书的位置
            const short int rigp1_base = 800;         // 运动到右边的第一本书
            const short int rigp2_base = 765;         // 运动到右边的第二本书
            const short int left1_base = 505;         // 运动到左边的第一本书
            const short int left2_base = 530;         // 运动到左边的第二本书
            const short int catch_tightness = 2450;   // 爪子的紧张程度
            const short int decatch_tightness = 2300; // 未夹书的紧张程度
        }
        // 2270,400,1150,1200,650,1200,1350
        // 2270,550,1550,1200,650,1200,1350
        // 2420,550,1550,1200,650,1200,1350
        // 2420,550,1200,1200,650,1200,1350
        short int p1[] = {constants::decatch_tightness, 400, 1150, 1200, 650, 1200, constants::p_base};
        short int p2[] = {constants::decatch_tightness, 500, 1400, 1200, 650, 1200, constants::p_base};
        short int p3[] = {constants::catch_tightness, 500, 1400, 1200, 650, 1200, constants::p_base};
        short int p4[] = {constants::catch_tightness, 500, 1000, 1200, 650, 1200, constants::p_base};

        // 2380,820,1840,1200,650,1200,830

        short int rigp1[] = {constants::catch_tightness, 900, 1500, 1200, 650, 1200, constants::rigp1_base};
        short int rigp2[] = {constants::catch_tightness, 820, 1840, 1200, 650, 1200, constants::rigp1_base};
        short int rigp3[] = {constants::decatch_tightness, 820, 1840, 1200, 650, 1200, constants::rigp1_base};
        short int rigp4[] = {constants::decatch_tightness, 900, 1500, 1200, 650, 1200, constants::rigp1_base};

        short int rigp_1[] = {constants::catch_tightness, 900, 1500, 1200, 650, 1200, constants::rigp2_base};
        short int rigp_2[] = {constants::catch_tightness, 820, 1840, 1200, 650, 1200, constants::rigp2_base};
        short int rigp_3[] = {constants::decatch_tightness, 820, 1840, 1200, 650, 1200, constants::rigp2_base};
        short int rigp_4[] = {constants::decatch_tightness, 900, 1500, 1200, 650, 1200, constants::rigp2_base};

        short int lefp1[] = {constants::catch_tightness, 900, 1500, 1200, 650, 1200, constants::left1_base};
        short int lefp2[] = {constants::catch_tightness, 820, 1840, 1200, 650, 1200, constants::left1_base};
        short int lefp3[] = {constants::decatch_tightness, 820, 1840, 1200, 650, 1200, constants::left1_base};
        short int lefp4[] = {constants::decatch_tightness, 900, 1500, 1200, 650, 1200, constants::left1_base};

        short int lefp_1[] = {constants::catch_tightness, 900, 1500, 1200, 650, 1200, constants::left2_base};
        short int lefp_2[] = {constants::catch_tightness, 820, 1840, 1200, 650, 1200, constants::left2_base};
        short int lefp_3[] = {constants::decatch_tightness, 820, 1840, 1200, 650, 1200, constants::left2_base};
        short int lefp_4[] = {constants::decatch_tightness, 900, 1500, 1200, 650, 1200, constants::left2_base};

        void catchbook_right()
        {
            arms.Slow_move(Arm_opreations::Catch_Book::p1, 50);
            arms.Slow_move(Arm_opreations::Catch_Book::p2, 50);
            arms.Slow_move(Arm_opreations::Catch_Book::p3, 20);
            arms.Slow_move(Arm_opreations::Catch_Book::p4, 50);
            arms.Slow_move(Arm_opreations::Catch_Book::rigp1, 100);
            arms.Slow_move(Arm_opreations::Catch_Book::rigp2, 40);
            arms.Slow_move(Arm_opreations::Catch_Book::rigp3, 10);
            arms.Slow_move(Arm_opreations::Catch_Book::rigp4, 20);
            arms.Slow_move(Arm_opreations::qti_points, 50);
        }
        void catchbook_right_()
        {
            arms.Slow_move(Arm_opreations::Catch_Book::p1, 50);
            arms.Slow_move(Arm_opreations::Catch_Book::p2, 50);
            arms.Slow_move(Arm_opreations::Catch_Book::p3, 20);
            arms.Slow_move(Arm_opreations::Catch_Book::p4, 50);
            arms.Slow_move(Arm_opreations::Catch_Book::rigp_1, 100);
            arms.Slow_move(Arm_opreations::Catch_Book::rigp_2, 40);
            arms.Slow_move(Arm_opreations::Catch_Book::rigp_3, 10);
            arms.Slow_move(Arm_opreations::Catch_Book::rigp_4, 20);
            arms.Slow_move(Arm_opreations::qti_points, 50);
        }
        void catchbook_left()
        {
            arms.Slow_move(Arm_opreations::Catch_Book::p1, 50);
            arms.Slow_move(Arm_opreations::Catch_Book::p2, 30);
            arms.Slow_move(Arm_opreations::Catch_Book::p3, 20);
            arms.Slow_move(Arm_opreations::Catch_Book::p4, 50);
            arms.Slow_move(Arm_opreations::Catch_Book::lefp1, 100);
            arms.Slow_move(Arm_opreations::Catch_Book::lefp2, 40);
            arms.Slow_move(Arm_opreations::Catch_Book::lefp3, 10);
            arms.Slow_move(Arm_opreations::Catch_Book::lefp4, 20);
            arms.Slow_move(Arm_opreations::qti_points, 50);
        }
        void catchbook_left_()
        {
            arms.Slow_move(Arm_opreations::Catch_Book::p1, 50);
            arms.Slow_move(Arm_opreations::Catch_Book::p2, 30);
            arms.Slow_move(Arm_opreations::Catch_Book::p3, 20);
            arms.Slow_move(Arm_opreations::Catch_Book::p4, 50);
            arms.Slow_move(Arm_opreations::Catch_Book::lefp_1, 100);
            arms.Slow_move(Arm_opreations::Catch_Book::lefp_2, 40);
            arms.Slow_move(Arm_opreations::Catch_Book::lefp_3, 10);
            arms.Slow_move(Arm_opreations::Catch_Book::lefp_4, 20);
            arms.Slow_move(Arm_opreations::qti_points, 50);
        }
        // 抓书调用此函数即可
        void catchbook(short int ID)
        {
            if (ID == 1)
            {

                // 如果识别到id为1的书籍，就抓到右边去
                if (r_num == 0)
                {
                    // 按顺序执行抓取书籍的任务
                    catchbook_right();
                    r_num = 1;
                }
                else if (r_num == 1)
                {
                    // 按顺序执行抓取书籍的任务
                    catchbook_right_();
                    r_num = 2;
                }
            }
            else if (ID == 2)
            {
                // 如果识别到id为2的书籍，就抓到左边去
                if (l_num == 0)
                {
                    // 按顺序执行抓取书籍的任务
                    catchbook_left();
                    l_num = 1;
                }
                else if (l_num == 1)
                {
                    // 按顺序执行抓取书籍的任务
                    catchbook_left_();
                    l_num = 2;
                }
            }
            return;
        }
    }
    namespace Chan_book
    {
        namespace constants
        {
            const short int right_base = 2080;   // 右边的铲子位置
            const short int left_base = 1858;    // 左边的铲子位置
            const short int release_base = 2600; // 释放书的位置
        }

        // 2330,2450,2350,2350,900,2150,2110
        // 2330,2450,2350,2300,1050,2150,2110

        short int p1[] = {Catch_Book::constants::decatch_tightness, 2450, 2350, 1200, 650, 1200, Arm_opreations::Catch_Book::constants::p_base};
        short int p2[] = {Catch_Book::constants::decatch_tightness, 2450, 2350, 1200, 650, 1200, constants::right_base};
        short int p3[] = {2330, 2450, 2350, 2400, 900, 2150, constants::right_base};
        short int p4[] = {2330, 2450, 2350, 2250, 1200, 2160, constants::right_base};
        short int p_up[] = {Catch_Book::constants::decatch_tightness, 2450, 2350, 2450, 740, 1760, constants::right_base};

        short int p1_[] = {Catch_Book::constants::decatch_tightness, 2450, 2350, 1200, 650, 1200, Arm_opreations::Catch_Book::constants::p_base};
        short int p2_[] = {Catch_Book::constants::decatch_tightness, 2450, 2350, 1200, 650, 1200, constants::left_base};
        short int p3_[] = {2330, 2450, 2350, 2400, 900, 2150, constants::left_base};
        short int p4_[] = {2330, 2450, 2350, 2250, 1050, 2160, constants::left_base};
        short int p_up_[] = {Catch_Book::constants::decatch_tightness, 2450, 2350, 2450, 740, 1760, constants::left_base};

        short int r_p1[] = {2180, 2450, 2350, 1950, 590, 1120, constants::release_base};
        short int r_p2[] = {2180, 2450, 2350, 1900, 1190, 1870, constants::release_base};
        short int r_p3[] = {2180, 2450, 2350, 1350, 1190, 1670, constants::release_base};
        short int r_p4[] = {2180, 2450, 2350, 1000, 2040, 2170, constants::release_base};
        short int r_p5[] = {2180, 2450, 2350, 1200, 590, 1370, constants::release_base};

        // 2180,2450,2350,1700,590,1120,2600
        // 2180,2450,2350,1700,890,1620,2600
        // 2180,2450,2350,1650,690,1420,2600
        // 2180,2450,2350,1350,790,1370,2600
        // 2180,2450,2350,1300,940,1520,2600
        void release_book()
        {
            arms.Slow_move(Arm_opreations::Chan_book::r_p1, 50);
            arms.Slow_move(Arm_opreations::Chan_book::r_p2, 50);
            arms.Slow_move(Arm_opreations::Chan_book::r_p3, 10);
            arms.Slow_move(Arm_opreations::Chan_book::r_p4, 20);
            arms.Slow_move(Arm_opreations::Chan_book::r_p5, 50);
            arms.Slow_move(Arm_opreations::qti_points, 50);
        }

        void chanbook_right()
        {
            arms.Slow_move(Arm_opreations::Chan_book::p1, 50);
            arms.Slow_move(Arm_opreations::Chan_book::p2, 50);
            arms.Slow_move(Arm_opreations::Chan_book::p3, 30);
            arms.Slow_move(Arm_opreations::Chan_book::p4, 5);
            arms.insistace(500); // 等待机械臂稳定
            arms.Slow_move(Arm_opreations::Chan_book::p_up, 50);
        }
        void chanbook_left()
        {
            arms.Slow_move(Arm_opreations::Chan_book::p1_, 50);
            arms.Slow_move(Arm_opreations::Chan_book::p2_, 50);
            arms.Slow_move(Arm_opreations::Chan_book::p3_, 30);
            arms.Slow_move(Arm_opreations::Chan_book::p4_, 5);
            arms.insistace(500); // 等待机械臂稳定
            arms.Slow_move(Arm_opreations::Chan_book::p_up_, 50);
        }
        void chanbook(short int ID)
        {
            const short int Left = 6;  // 右边书框对应识别到整齐书框id
            const short int Right = 7; // 左边书框对应识别到整齐书框id
            if (ID == Left)
            {
                // 将左边书框的书籍释放
                chanbook_left();
                l_num = 0;
            }
            else if (ID == Right)
            {
                // 将右边书框的书籍释放
                chanbook_right();
                r_num = 0;
            }
            release_book();
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
        if (high != 0) // 转弯90°
        {
            long long clock = millis();
            wheels.run(RUN_TOWARDS);
            delay(400); // 向前走一小段距离
            wheels.run(RUN_LEFT);
            delay(400); // 向左走一段距离
            while (qtis_lowdeg._qtiread() != 2)
            {
                if (millis() - clock > 10000)
                {
                    break;
                    // 如果左转时间大于一段时间，就退出左转,或者右边qti识别到灰色线，就退出左转
                }
                wheels.run(RUN_LEFT);
            }
            return;
        }
        switch (low) // 微调
        {
        case 3:
        case 0:
            wheels.run(speedLeft, speedRight); // 向前走
            break;
        case 2:
            wheels.run(150, 0); // 向左走
            break;
        case 1:
            wheels.run(0, 150); // 向右走
            break;
        default:
            wheels.run(RUN_TOWARDS); // 向前走
        }
    }
}