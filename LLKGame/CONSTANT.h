#pragma once
//游戏地图初始化
#define MAXMAPROW 18     
#define MAXMAPCOL 24	 //地图为16*22  边缘为空位置 必须为2的倍数

#define ELEMENTWIDTH 40 //游戏图宽度
#define ELEMENTHEIGHT 40 //游戏图长度
#define STARTTOPLOC 50		//游戏元素初始绘制位置距界面顶端长度
#define STARTLEFTLOC 50		//游戏元素初始绘制位置距界面左端位置
//游戏难度
#define EASY 1
#define MEDIUM 2
#define DIFFICULT 3
//游戏各级难度地图大小
#define EASYMAPROW 8
#define EASYMAPCOL 10 //简单地图为6*8
#define MEDIUMMAPROW 12
#define MEDIUMMAPCOL 16 //中级地图为10*14
#define DIFFICULTMAPROW 18
#define DIFFICULTMAPCOL 24//高级地图为16*22
//两点间连线时点数组
#define MAXLNNUM 4  //三段线时可以有两个起始节点两个拐点  线上最多四个点 画线时使用

//空白元素
#define BLANK -1		//元素已经消除

//用户点击响应返回
#define SELECTBLANK 1 //点击空白元素
#define FIRSTSELECT 2 //非空白元素且为第一次选中
#define CLEARSELECT 3 //第二次选中且两点可消除
#define CLEARSELECTUSETOOL 4 //使用道具进行消子
#define RESELECT 5 //第二次选择且两点不可消除

//定时器
#define PLAY_TIMER_ID 1   //定时器ID

//游戏状态
#define GAME_GOING 1 //游戏正在进行中
#define GAME_PAUSE 2 //游戏暂停

//游戏主要界面
#define GAME_MAIN_FRAME 0  //主界面
#define GAME_MODEL_BASE 1 //基本模式
#define GAME_MODEL_EASY 2 //休闲模式
#define GAME_MODEL_LEVEL 3 //关卡模式

//提示结果
#define TIPS_GET 1 //成功获得提示
#define TIPS_NOTFIND 2 //没有可达路径
#define TIPS_SCORENOTENOUGH 3//积分不足

//文件相关
#define RANKFILEPATH _T("file\\score.txt")  //积分信息路径
#define CONFIGFILEPATH _T("file\\config.ini") //配置信息路径

#define MAXRANKMES 1000 //最多信息数量
#define MAXFILEPATHLENGTH 32 //最大路径长度

#define DEFAULTELEMENT _T("source\\element\\smile.bmp") 
#define DEFAULTMASK _T("source\\element\\smile_mask.bmp")
#define DEFAULTPICTURE _T("source\\theme\\theme0.bmp")
#define DEFAULTMUSIC _T("source\\music\\default.wav")

//排行榜
#define MAXRANKLEVEL 10//排行榜最大数量