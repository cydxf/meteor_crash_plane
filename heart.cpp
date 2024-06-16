#include "heart.h"
#include "config.h"

Heart::Heart()
{
    // 加载爱心资源
    m_Heart.load(HEART_PATH);

    // 爱心坐标
    m_X = GAME_WIDTH*0.7;
    m_Y = GAME_HEIGHT*0.03;

    // 爱心状态
    m_Free = false;
}
