#pragma once
#include "qtis\qtis.h"
unsigned char arms_list[6] = {10, 9, 8, 13, 12, 11};
const bool DUBUGGING = false;
short int GRABBER_READY[] = {600, 1450, 1200, 1200, 1200, 1200};
short int GRABBER_DOWN[] = {600, 1450, 2450, 1200, 1200, 1200};
short int GRABBER_GRAB[] = {1300, 1650, 2550, 1150, 1200, 1250};
short int GRABBER_RELEASE_1[] = {1300, 1800, 1450, 1700, 1400, 1200}; // TODO
short int GRABBER_RELEASE_2[] = {600, 1800, 1450, 1700, 1400, 1200};
short int GRABBER_RUN[] = {1350, 600, 1400, 2150, 1700, 1150};
qtis QTI_LOWDEG[4] = {
    qtis(23, -1), // 前面左边
    qtis(24, 1),  // 前面右边
    qtis(27, -1), // 后面左边
    qtis(26, 1),
}; // 后面右边
qtis QTI_HIGHDEG_L[2] = {
    qtis(23, 1),
    qtis(22, 1),
};
qtis QTI_HIGHDEG_R[2] = {
    qtis(24, 1),
    qtis(25, 1),
};
New_qtis qtis_lowdeg(QTI_LOWDEG); // 低角度旋转的qti
New_qtis qtis_highdeg_L(qtis_highdeg_L);
New_qtis qtis_highdeg_R(qtis_highdeg_R);