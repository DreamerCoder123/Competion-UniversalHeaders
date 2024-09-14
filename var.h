#pragma once
#include "qtis\qtis.h"
const bool DUBUGGING = false;
short int GRABBER_READY[] = {600, 1450, 1200, 1200, 1200, 1200};
short int GRABBER_DOWN[] = {600, 1450, 2450, 1200, 1200, 1200};
short int GRABBER_GRAB[] = {1300, 1650, 2550, 1150, 1200, 1250};
short int GRABBER_RELEASE_1[] = {1300, 1800, 1450, 1700, 1400, 1200}; // TODO
short int GRABBER_RELEASE_2[] = {600, 1800, 1450, 1700, 1400, 1200};
qtis QTI[6] = {
    qtis(23, -2), // 前面左边
    qtis(22, -1), // 前面左2边
    qtis(24, 1),  // 前面右边
    qtis(25, 2),  // 前面右2边
    qtis(27, -1), // 后面左边
    qtis(26, 1)}; // 后面右边