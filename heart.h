#ifndef HEART_H
#define HEART_H
#include <QPixmap>

class Heart
{
public:
    Heart();

    // 更新坐标
    void updatePosition();
public:
    // 爱心资源对象
    QPixmap m_Heart;

    // 位置
    int m_X;
    int m_Y;

    // 爱心状态
    bool m_Free;
};

#endif // HEART_H
