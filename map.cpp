#include "map.h"
#include "config.h"
#include <cstdlib>
#include <ctime>

Map::Map()
{
    // 初始化随机种子
    srand(time(nullptr));
    // 随机选择背景图片
    QString bgPath = QString(MAP_PATH).arg(rand()%5+1);

    // 初始化加载地图对象
    m_map1.load(bgPath);
    m_map2.load(bgPath);

    // 设置地图起始y轴坐标
    m_map1_posY = -GAME_HEIGHT;
    m_map2_posY = 0;

    // 设置地图滚动速度
    m_scroll_speed = MAP_SCROLL_SPEED;

    // 初始化分数
    m_score = 0;
}

void Map::mapPosition()
{
    // 处理第一张图片滚动
    m_map1_posY += MAP_SCROLL_SPEED;
    if(m_map1_posY >= 0)
    {
        m_map1_posY =-GAME_HEIGHT;
    }

    // 处理第二张图片滚动
    m_map2_posY += MAP_SCROLL_SPEED;
    if(m_map2_posY >= GAME_HEIGHT )
    {
        m_map2_posY =0;
    }
}
