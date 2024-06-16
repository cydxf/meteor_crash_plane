#include "mainscene.h"
#include "config.h"
#include <QIcon>
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QTimer>
#include <ctime>
#include <QFont>
#include <QMessageBox>
#include <QSound>

MainScene::MainScene(QWidget *parent)
    : QWidget(parent)
{
    // 调用初始化场景
    initScene();

    // 启动游戏
    playGame();

}

MainScene::~MainScene()
{
}

void MainScene::initScene()
{
    // 初始化窗口大小
    setFixedSize(GAME_WIDTH, GAME_HEIGHT);

    // 设置窗口标题
    setWindowTitle(GAME_TITLE);

    // 加载图标
    setWindowIcon(QIcon(GAME_ICON));

    // 定时器设置
    m_Timer.setInterval(GAME_RATE);

    // 陨石出场时间间隔初始化
    m_recorder = 0;

    //随机数种子
    srand((unsigned int)time(NULL));
}

void MainScene::playGame()
{
    // 启动背景音乐
    QSound::play(SOUND_BACKGROUND);

    // 启动定时器
    m_Timer.start();

    // 监听定时器发送的信号
    connect(&m_Timer, &QTimer::timeout, [=](){
        // 陨石出场
        enemyToScene();
        // 更新游戏中元素的坐标
        updatePosition();
        // 处理键盘控制飞机移动
        handleKeyPress();
        // 绘制到屏幕中
        update();
        // 子弹与陨石碰撞检测
        collisionDetection();
        // 英雄飞机与陨石碰撞检测
        checkCollisions();
    });
}

void MainScene::updatePosition()
{
    // 更新地图的坐标
    m_map.mapPosition();

    // 发射子弹
    if (m_hero.m_isShooting)
    {
        m_hero.shoot();
    }
        // 计算子弹坐标
        for(int i = 0 ;i < BULLET_NUM;i++)
        {
            // 如果子弹状态为非空闲，计算发射位置
            if(!m_hero.m_bullets[i].m_Free)
            {
                m_hero.m_bullets[i].updatePosition();
            }
        }

        // 计算陨石坐标
        for(int i = 0 ; i< ENEMY_NUM;i++)
        {
            //非空闲陨石 更新坐标
            if(m_enemys[i].m_Free == false)
            {
                  m_enemys[i].updatePosition();
            }
        }
        //计算爆炸播放的图片
        for(int i = 0 ; i < BOMB_NUM;i++)
        {
            if(m_bombs[i].m_Free == false)
            {
                   m_bombs[i].updateInfo();
            }
        }
}

void MainScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    // 绘制地图
    painter.drawPixmap(0, m_map.m_map1_posY, m_map.m_map1);
    painter.drawPixmap(0, m_map.m_map2_posY, m_map.m_map2);

    // 绘制英雄飞机
    painter.drawPixmap(m_hero.m_X, m_hero.m_Y, m_hero.m_Plane);

    // 绘制子弹
        for(int i = 0 ;i < BULLET_NUM;i++)
        {
            // 如果子弹状态为非空闲，计算发射位置
            if(!m_hero.m_bullets[i].m_Free)
            {
                painter.drawPixmap(m_hero.m_bullets[i].m_X,m_hero.m_bullets[i].m_Y,m_hero.m_bullets[i].m_Bullet);
            }
        }

    // 绘制陨石
        for(int i = 0 ; i< ENEMY_NUM;i++)
        {
            if(m_enemys[i].m_Free == false)
            {
                    painter.drawPixmap(m_enemys[i].m_X,m_enemys[i].m_Y,m_enemys[i].m_enemy);
            }
        }

    // 绘制爆炸图片
       for(int i = 0 ; i < BOMB_NUM;i++)
       {
            if(m_bombs[i].m_Free == false)
            {
                   painter.drawPixmap(m_bombs[i].m_X,m_bombs[i].m_Y,m_bombs[i].m_pixArr[m_bombs[i].m_index]);
            }
       }

    // 绘制爱心
       for(int i = 0 ; i < HEART_NUM;i++)
       {
            if(m_Heart[i].m_Free == false)
            {
                   painter.drawPixmap(m_Heart[i].m_X + 50*i, m_Heart[i].m_Y, m_Heart[i].m_Heart);
            }
       }

    // 绘制分数
       QFont font;
       font.setPointSize(20);
       painter.setFont(font);
       painter.setPen(Qt::white);
       painter.drawText(10, 30, QString("Score: %1").arg(m_map.m_score++));

}

void MainScene::mouseMoveEvent(QMouseEvent *event)    // 实现鼠标拖拽飞机
{
    int x = event->x() - m_hero.m_Rect.width() * 0.5; //鼠标位置 - 飞机矩形的一半
    int y = event->y() - m_hero.m_Rect.height() * 0.5;

    //边界检测
    if (x <= 0)
    {
        x = 0;
    }
    if (x >= GAME_WIDTH - m_hero.m_Rect.width())
    {
        x = GAME_WIDTH - m_hero.m_Rect.width();
    }
    if (y <= 0)
    {
        y = 0;
    }
    if (y >= GAME_HEIGHT - m_hero.m_Rect.height())
    {
        y = GAME_HEIGHT - m_hero.m_Rect.height();
    }
    m_hero.setPosition(x, y);
}

void MainScene::keyPressEvent(QKeyEvent *event)    // 实现键盘控制飞机
{
    switch (event->key())
    {
    case Qt::Key_W:
    case Qt::Key_Up:
        m_upPressed = true;
        break;
    case Qt::Key_S:
    case Qt::Key_Down:
        m_downPressed = true;
        break;
    case Qt::Key_A:
    case Qt::Key_Left:
        m_leftPressed = true;
        break;
    case Qt::Key_D:
    case Qt::Key_Right:
        m_rightPressed = true;
        break;
    default:
        QWidget::keyPressEvent(event);
    }

    if (event->key() == Qt::Key_Space)
     {
         m_hero.m_isShooting = true;
     }
}

void MainScene::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_W:
    case Qt::Key_Up:
        m_upPressed = false;
        break;
    case Qt::Key_S:
    case Qt::Key_Down:
        m_downPressed = false;
        break;
    case Qt::Key_A:
    case Qt::Key_Left:
        m_leftPressed = false;
        break;
    case Qt::Key_D:
    case Qt::Key_Right:
        m_rightPressed = false;
        break;
    default:
        QWidget::keyReleaseEvent(event);
    }

    if (event->key() == Qt::Key_Space)
    {
        m_hero.m_isShooting = false;
    }
}

void MainScene::handleKeyPress()
{
    int x = m_hero.m_X;
    int y = m_hero.m_Y;

    if (m_upPressed)
    {
        y -= 5;
    }
    if (m_downPressed)
    {
        y += 5;
    }
    if (m_leftPressed)
    {
        x -= 5;
    }
    if (m_rightPressed)
    {
        x += 5;
    }

    // 边界检测
    if (x <= 0)
    {
        x = 0;
    }
    if (x >= GAME_WIDTH - m_hero.m_Rect.width())
    {
        x = GAME_WIDTH - m_hero.m_Rect.width();
    }
    if (y <= 0)
    {
        y = 0;
    }
    if (y >= GAME_HEIGHT - m_hero.m_Rect.height())
    {
        y = GAME_HEIGHT - m_hero.m_Rect.height();
    }

    m_hero.setPosition(x, y);

}

void MainScene::enemyToScene()
{
    m_recorder++;
    // 未达到出场间隔，直接return
    if(m_recorder < ENEMY_INTERVAL)
    {
        return;
    }

    m_recorder = 0;

    for(int i = 0 ; i< ENEMY_NUM;i++)
    {
        // 如果是空闲陨石 出场
        if(m_enemys[i].m_Free)
        {
            // 陨石空闲状态改为false
            m_enemys[i].m_Free = false;
            // 设置坐标
            m_enemys[i].m_X = rand() % (GAME_WIDTH - m_enemys[i].m_Rect.width());
            m_enemys[i].m_Y = -m_enemys[i].m_Rect.height();
            break;
        }
    }
}

void MainScene::collisionDetection()  // 子弹与陨石碰撞检测
{
    // 遍历所有非空闲的陨石
    for(int i = 0 ;i < ENEMY_NUM;i++)
    {
        if(m_enemys[i].m_Free)
        {
            // 空闲 跳转下一次循环
            continue;
        }

        // 遍历所有 非空闲的子弹
        for(int j = 0 ; j < BULLET_NUM;j++)
        {
            if(m_hero.m_bullets[j].m_Free)
            {
                // 空闲子弹 跳转下一次循环
                continue;
            }

            // 如果子弹矩形框和陨石矩形框相交，发生碰撞，同时变为空闲状态即可
            if(m_enemys[i].m_Rect.intersects(m_hero.m_bullets[j].m_Rect))
            {
                m_enemys[i].m_Free = true;
                m_hero.m_bullets[j].m_Free = true;

                // 播放爆炸效果
                for(int k = 0 ; k < BOMB_NUM;k++)
                {
                    if(m_bombs[k].m_Free)
                    {
                        // 播放爆炸音效
                        QSound::play(SOUND_BOMB);
                        //爆炸状态设置为非空闲
                        m_bombs[k].m_Free = false;
                        //更新坐标
                        m_bombs[k].m_X = m_enemys[i].m_X;
                        m_bombs[k].m_Y = m_enemys[i].m_Y;
                        break;
                    }
                }
            }
        }
    }
}

void MainScene::checkCollisions()   // 飞机与陨石碰撞检测
{
    static bool gameOver = false; // 静态变量，用来记录游戏是否已经结束
    static int collidedEnemies = 0; // 记录已经撞到的陨石数量
    static int HeartCount = 0; // 记录生命值

    if (gameOver) {
        return; // 如果游戏已经结束，直接返回，不再进行碰撞检测
    }

    // 遍历每一块陨石
    for (auto &enemy : m_enemys)
    {
        // 如果英雄飞机和陨石矩形框相交，发生碰撞
        if (!enemy.m_Free && m_hero.m_Rect.intersects(enemy.m_Rect))
        {

            // 将陨石状态设置为空闲
            enemy.m_Free = true;

            // 播放爆炸效果
            for (int k = 0; k < BOMB_NUM; k++)
            {
                if (m_bombs[k].m_Free)
                {
                    // 播放爆炸音效
                    QSound::play(SOUND_BOMB);
                    // 设置炸弹状态为非空闲
                    m_bombs[k].m_Free = false;
                    // 更新炸弹坐标为陨石坐标
                    m_bombs[k].m_X = enemy.m_X;
                    m_bombs[k].m_Y = enemy.m_Y;
                    break;
                }
            }

           collidedEnemies++; // 撞到陨石数量加一
           m_Heart[HeartCount++].m_Free = true; // 撞到陨石生命值减一 一颗爱心消失

            // 累计撞到三次陨石，游戏结束
            if (collidedEnemies >= 3)
            {
                gameOver = true; // 设置标志，防止重复显示对话框
                // 游戏结束处理
                QMessageBox::information(this, "游戏结束", "你已累计撞到3块陨石，游戏结束!");
                close(); // 关闭游戏窗口
            }
            break;
        }
    }
}
