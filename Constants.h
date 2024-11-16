#pragma once
#include "qtis\qtis.h"
#include "Servo\Arm.h"
#include "dcmotor\dcmotor.h"
#define RUN_TOWARDS 80, 80                              // 向前行进
#define RUN_AFTERWARDS -80, -80                         // 向后行进
#define RUN_LEFT 140, -140                              // 向左转弯
#define RUN_RIGHT -140, 140                             // 向右转弯
#define RUN_STOP 0, 0                                   // 停止
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

// 屎山代码发力了！！！(笑)
namespace Arm_opreations
{
    short int scan[] = {2300, 2350, 2350, 1200, 650, 1200, 1350};        // husky传感器观测位点
    short int qti_points[7] = {2300, 2350, 2350, 1200, 650, 1200, 1350}; // 灰度传感器巡线位点
    namespace Catch_Book
    {
        namespace constants
        {
            const short int p_base = 1350;            // 运动到书架上抓住书的位置
            const short int rigp1_base = 775;         // 运动到右边的第一本书
            const short int rigp2_base = 750;         // 运动到右边的第二本书
            const short int left1_base = 500;         // 运动到左边的第一本书
            const short int left2_base = 545;         // 运动到左边的第二本书
            const short int catch_tightness = 2550;   // 爪子的紧张程度
            const short int decatch_tightness = 2300; // 未夹书的紧张程度

            short r_num = 0; // 右边书框内书的数量
            short l_num = 0; // 左边书框内书的数量
        }
        // 1400,900,1850,1200,650,1200,527
        short int p1[] = {constants::decatch_tightness, 1750, 1750, 1200, 650, 1200, constants::p_base};
        short int p2[] = {constants::decatch_tightness, 850, 1750, 1200, 650, 1200, constants::p_base};
        short int p3[] = {constants::catch_tightness, 850, 1750, 1200, 650, 1200, constants::p_base};
        short int p4[] = {constants::catch_tightness, 1850, 1750, 1200, 650, 1200, constants::p_base};
        // 运动到书框位置抓书
        short int rigp1[] = {constants::catch_tightness, 1850, 1950, 1200, 650, 1200, constants::rigp1_base};
        short int rigp2[] = {constants::catch_tightness, 900, 1850, 1200, 650, 1200, constants::rigp1_base};
        short int rigp3[] = {constants::decatch_tightness, 900, 1850, 1200, 650, 1200, constants::rigp1_base};

        short int rigp_1[] = {constants::catch_tightness, 1850, 1950, 1200, 650, 1200, constants::rigp2_base};
        short int rigp_2[] = {constants::catch_tightness, 900, 1850, 1200, 650, 1200, constants::rigp2_base};
        short int rigp_3[] = {constants::decatch_tightness, 900, 1850, 1200, 650, 1200, constants::rigp2_base};
        // 运动到左边释放书
        short int lefp1[] = {constants::catch_tightness, 1650, 1950, 1200, 650, 1200, constants::left1_base};
        short int lefp2[] = {constants::catch_tightness, 900, 1850, 1200, 650, 1200, constants::left1_base};
        short int lefp3[] = {constants::decatch_tightness, 900, 1850, 1200, 650, 1200, constants::left1_base};

        short int lefp1_[] = {constants::catch_tightness, 1650, 1950, 1200, 650, 1200, constants::left2_base};
        short int lefp2_[] = {constants::catch_tightness, 900, 1850, 1200, 650, 1200, constants::left2_base};
        short int lefp3_[] = {constants::decatch_tightness, 900, 1850, 1200, 650, 1200, constants::left2_base};

        void catchbook_right()
        {
            arms.Slow_move(Arm_opreations::Catch_Book::p1, 50);
            arms.Slow_move(Arm_opreations::Catch_Book::p2, 50);
            arms.Slow_move(Arm_opreations::Catch_Book::p3, 20);
            arms.Slow_move(Arm_opreations::Catch_Book::p4, 50);
            arms.Slow_move(Arm_opreations::Catch_Book::rigp1, 25);
            arms.Slow_move(Arm_opreations::Catch_Book::rigp2, 40);
            arms.Slow_move(Arm_opreations::Catch_Book::rigp3, 10);
            arms.Slow_move(Arm_opreations::Catch_Book::rigp1, 20);
            arms.Slow_move(Arm_opreations::qti_points, 50);
        }
        void catchbook_right_()
        {
            arms.Slow_move(Arm_opreations::Catch_Book::p1, 50);
            arms.Slow_move(Arm_opreations::Catch_Book::p2, 50);
            arms.Slow_move(Arm_opreations::Catch_Book::p3, 20);
            arms.Slow_move(Arm_opreations::Catch_Book::p4, 50);
            arms.Slow_move(Arm_opreations::Catch_Book::rigp_1, 25);
            arms.Slow_move(Arm_opreations::Catch_Book::rigp_2, 40);
            arms.Slow_move(Arm_opreations::Catch_Book::rigp_3, 10);
            arms.Slow_move(Arm_opreations::Catch_Book::rigp_1, 20);
            arms.Slow_move(Arm_opreations::qti_points, 50);
        }
        void catchbook_left()
        {
            arms.Slow_move(Arm_opreations::Catch_Book::p1, 50);
            arms.Slow_move(Arm_opreations::Catch_Book::p2, 30);
            arms.Slow_move(Arm_opreations::Catch_Book::p3, 20);
            arms.Slow_move(Arm_opreations::Catch_Book::p4, 50);
            arms.Slow_move(Arm_opreations::Catch_Book::lefp1, 45);
            arms.Slow_move(Arm_opreations::Catch_Book::lefp2, 40);
            arms.Slow_move(Arm_opreations::Catch_Book::lefp3, 10);
            arms.Slow_move(Arm_opreations::Catch_Book::lefp1, 20);
            arms.Slow_move(Arm_opreations::qti_points, 50);
        }
        void catchbook_left_()
        {
            arms.Slow_move(Arm_opreations::Catch_Book::p1, 50);
            arms.Slow_move(Arm_opreations::Catch_Book::p2, 30);
            arms.Slow_move(Arm_opreations::Catch_Book::p3, 20);
            arms.Slow_move(Arm_opreations::Catch_Book::p4, 50);
            arms.Slow_move(Arm_opreations::Catch_Book::lefp1_, 45);
            arms.Slow_move(Arm_opreations::Catch_Book::lefp2_, 40);
            arms.Slow_move(Arm_opreations::Catch_Book::lefp3_, 10);
            arms.Slow_move(Arm_opreations::Catch_Book::lefp1_, 20);
            arms.Slow_move(Arm_opreations::qti_points, 50);
        }
        // 抓书调用此函数即可
        void catchbook(short int ID)
        {
            if (ID == 1)
            {
                // 如果识别到id为1的书籍，就抓到右边去
                if (constants::r_num == 0)
                {
                    // 按顺序执行抓取书籍的任务
                    catchbook_right();
                    constants::r_num = 1;
                }
                else if (constants::r_num == 1)
                {
                    // 按顺序执行抓取书籍的任务
                    catchbook_right_();
                    constants::r_num = 0;
                }
            }
            else if (ID == 2)
            {
                // 如果识别到id为2的书籍，就抓到左边去
                if (constants::l_num == 0)
                {
                    // 按顺序执行抓取书籍的任务
                    catchbook_left();
                    constants::l_num = 1;
                }
                else if (constants::l_num == 1)
                {
                    // 按顺序执行抓取书籍的任
                    catchbook_left_();
                    constants::l_num = 0;
                }
            }
            else
            {
                return;
            }
            return;
        }
    }
    namespace Chan_book
    {
        namespace constants
        {
            const short int right_base = 2100; // 右边的铲子位置
            const short int left_base = 1870;  // 左边的铲子位置
        }

        short int p1[] = {Catch_Book::constants::decatch_tightness, 2450, 2350, 1200, 650, 1200, Arm_opreations::Catch_Book::constants::p_base};
        short int p2[] = {Catch_Book::constants::decatch_tightness, 2450, 2350, 1200, 650, 1200, constants::right_base};
        short int p3[] = {Catch_Book::constants::decatch_tightness, 2450, 2350, 1760, 870, 1710, constants::right_base};
        short int p4[] = {Catch_Book::constants::decatch_tightness, 2450, 2350, 1850, 1140, 1920, constants::right_base};
        short int p_up[] = {Catch_Book::constants::decatch_tightness, 2450, 2350, 2550, 740, 1920, constants::right_base};

        short int p1_[] = {Catch_Book::constants::decatch_tightness, 2450, 2350, 1200, 650, 1200, Arm_opreations::Catch_Book::constants::p_base};
        short int p2_[] = {Catch_Book::constants::decatch_tightness, 2450, 2350, 1200, 650, 1200, constants::left_base};
        short int p3_[] = {Catch_Book::constants::decatch_tightness, 2450, 2350, 2000, 790, 1710, constants::left_base};
        short int p4_[] = {Catch_Book::constants::decatch_tightness, 2450, 2350, 1800, 1040, 1920, constants::left_base};
        short int p_up_[] = {Catch_Book::constants::decatch_tightness, 2450, 2350, 2550, 740, 1920, constants::left_base};
        void chanbook_right()
        {
            arms.Slow_move(Arm_opreations::Chan_book::p1, 50);
            arms.Slow_move(Arm_opreations::Chan_book::p2, 50);
            arms.Slow_move(Arm_opreations::Chan_book::p3, 20);
            arms.Slow_move(Arm_opreations::Chan_book::p4, 20);
            arms.insistace(1000); // 等待机械臂稳定
            arms.Slow_move(Arm_opreations::Chan_book::p_up, 50);
        }
        void chanbook_left()
        {
            arms.Slow_move(Arm_opreations::Chan_book::p1_, 50);
            arms.Slow_move(Arm_opreations::Chan_book::p2_, 50);
            arms.Slow_move(Arm_opreations::Chan_book::p3_, 20);
            arms.Slow_move(Arm_opreations::Chan_book::p4_, 20);
            // arms.insistace(2000); // 等待机械臂稳定
            arms.Slow_move(Arm_opreations::Chan_book::p_up_, 50);
        }
        void chanbook(short int ID)
        {
            const short int Left = 5;  // 右边书框对应识别到好书框id
            const short int Right = 6; // 左边书框对应识别到好书框id
            if (ID == Left)
            {
                // 将左边书框的书籍释放
                chanbook_left();
            }
            else if (ID == Right)
            {
                // 将右边书框的书籍释放
                chanbook_right();
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
            wheels.run(RUN_TOWARDS);
            delay(200); // 向前走一小段距离
            wheels.run(RUN_LEFT);
            delay(400); // 向左走一段距离
            while (qtis_lowdeg._qtiread() != 2)
            {
                if (millis() - clock > 2000)
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
            wheels.run(RUN_TOWARDS); // 向前走
            break;
        case 2:
            wheels.run(255, 0); // 向左走
            break;
        case 1:
            wheels.run(0, 200); // 向右走
            break;
        default:
            wheels.run(RUN_TOWARDS); // 向前走
        }
    }
}