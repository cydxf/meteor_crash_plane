#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QWidget>
#include <QTimer>
#include <QKeyEvent>
#include "map.h"
#include "heroplane.h"
#include "meteor.h"
#include "bomb.h"
#include "heart.h"


class MainScene : public QWidget
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();

    // 初始化场景
    void initScene();

    // 启动游戏  用于启动定时器对象
    void playGame();

    //更新所有游戏中元素的坐标
    void updatePosition();

    //绘图事件
    void paintEvent(QPaintEvent *event);

    //地图对象
    Map m_map;

    // 定时器
    QTimer m_Timer;

    // 飞机对象
    HeroPlane m_hero;

    // 鼠标移动事件
    void mouseMoveEvent(QMouseEvent *);

    // 处理键盘按下事件
    void keyPressEvent(QKeyEvent *event);

    // 处理键盘释放事件
    void keyReleaseEvent(QKeyEvent *event);

    // 处理键盘控制飞机移动
    void handleKeyPress();

    // 陨石出场
    void enemyToScene();

    // 陨石数组
    METEOR m_enemys[ENEMY_NUM];

    // 陨石出场间隔记录
    int m_recorder;

    // 子弹与陨石的碰撞检测
    void collisionDetection();

    // 爆炸数组
    Bomb m_bombs[BOMB_NUM];

    // 爱心对象
    Heart m_Heart[HEART_NUM];

    // 检查英雄飞机与陨石的碰撞
    void checkCollisions();


private:
    // 用于记录按键状态的变量
    bool m_leftPressed = false;
    bool m_rightPressed = false;
    bool m_upPressed = false;
    bool m_downPressed = false;

};
#endif // MAINSCENE_H
