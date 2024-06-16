#ifndef CONFIG_H
#define CONFIG_H

/*********** 游戏配置数据 **********/
#define GAME_WIDTH 512   // 宽度
#define GAME_HEIGHT 768  // 高度
#define GAME_TITLE "plane_game v1.0@huangjiaxi"   // 标题
#define GAME_RES_PATH "./plane.rcc"    // rcc文件路径
#define GAME_ICON ":/res/PlaneWar.ico" // 游戏图标路径
#define GAME_RATE 15     // 定时器刷新时间间隔 单位毫秒

/*********** 地图配置数据 **********/
#define MAP_PATH ":/res/img_bg_level_%1.jpg" // 地图图片路径
#define MAP_SCROLL_SPEED 2 // 地图滚动速度

/**********  飞机配置数据 **********/
#define HERO_PATH ":/res/hero2.png"

/**********  子弹配置数据 **********/
#define BULLET_PATH ":/res/bullet_11.png"   // 子弹图片路径
#define BULLET_SPEED 5  // 子弹移动速度
#define BULLET_NUM 30   // 弹匣中子弹总数
#define BULLET_INTERVAL 15 // 发射子弹时间间隔

/**********  陨石配置数据 **********/
#define ENEMY_PATH  ":/res/meteor.png"  // 陨石资源图片
#define ENEMY_SPEED 5  // 陨石移动速度
#define ENEMY_NUM   20  // 陨石总数量
#define ENEMY_INTERVAL  45  // 陨石出场时间间隔

/********** 爆炸配置数据 *********/
#define BOMB_PATH  ":/res/bomb-%1.png"   // 爆炸资源图片
#define BOMB_NUM  20     // 爆炸数量
#define BOMB_MAX  7      // 爆炸图片最大索引
#define BOMB_INTERVAL 20   // 爆炸切图时间间隔

/********** 音效配置数据 ********/
#define SOUND_BACKGROUND ":/res/bg.wav"  // 背景音乐路径
#define SOUND_BOMB ":/res/bomb.wav"      // 爆炸音效路径

/********* 生命值配置数据 *******/
#define HEART_PATH ":res/heart.png"  // 爱心图片路径
#define HEART_NUM 3 // 爱心总数 即生命值

#endif // CONFIG_H
