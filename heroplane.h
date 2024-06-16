#ifndef HEROPLANE_H
#define HEROPLANE_H
#include <QPixmap>
#include <QRect>
#include "bullet.h"

class HeroPlane
{
public:
    HeroPlane();

    // 发射子弹
    void shoot();
    // 设置飞机位置
    void setPosition(int x, int y);
    // 与敌机碰撞后调用该方法
    void collideWithEnemy();
    // 获取碰撞次数
    int getCollisionCount() const;

    //飞机资源 对象
    QPixmap m_Plane;

    // 飞机坐标
    int m_X;
    int m_Y;

    // 飞机的矩形边框
    QRect m_Rect;

    // 弹匣
    Bullet m_bullets[BULLET_NUM];

    // 发射间隔记录
    int m_recorder;

    // 记录空格键是否被按下,按下则开始发射
    bool m_isShooting = false;

};

#endif // HEROPLANE_H
