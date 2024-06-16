#include "meteor.h"
#include "config.h"

METEOR::METEOR()
{
    // 陨石资源加载
    m_enemy.load(ENEMY_PATH);

    // 陨石位置
    m_X = 0;
    m_Y = 0;

    // 陨石状态
    m_Free = true;

    // 陨石速度
    m_Speed = ENEMY_SPEED;

    // 陨石矩形
    m_Rect.setWidth(m_enemy.width());
    m_Rect.setHeight(m_enemy.height());
    m_Rect.moveTo(m_X,m_Y);
}

void METEOR::updatePosition()
{
    // 空闲状态，不计算坐标
    if(m_Free)
    {
        return;
    }

    m_Y += m_Speed;
    m_Rect.moveTo(m_X,m_Y);

    if(m_Y >= GAME_HEIGHT + m_Rect.height())
    {
        m_Free = true;
    }
}
