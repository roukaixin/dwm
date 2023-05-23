#include <X11/XF86keysym.h>

static int showsystray                   = 1;         /* 是否显示托盘栏 */
static const int newclientathead         = 0;         /* 定义新窗口在栈顶还是栈底 */
static const unsigned int borderpx       = 2;         /* 窗口边框大小 */
static const unsigned int systraypinning = 1;         /* 托盘跟随的显示器 0代表不指定显示器 */
static const unsigned int systrayspacing = 1;         /* 托盘间距 */
static const unsigned int systrayspadding = 5;        /* 托盘和状态栏的间隙 */
static int gappi                         = 12;        /* 窗口与窗口 缝隙大小 */
static int gappo                         = 12;        /* 窗口与边缘 缝隙大小 */
static const int _gappo                  = 12;        /* 窗口与窗口 缝隙大小 不可变 用于恢复时的默认值 */
static const int _gappi                  = 12;        /* 窗口与边缘 缝隙大小 不可变 用于恢复时的默认值 */
static const int vertpad                 = 5;         /* vertical padding of bar */
static const int sidepad                 = 5;         /* horizontal padding of bar */
static const int overviewgappi           = 24;        /* overview时 窗口与边缘 缝隙大小 */
static const int overviewgappo           = 60;        /* overview时 窗口与窗口 缝隙大小 */
static const int showbar                 = 1;         /* 是否显示状态栏 */
static const int topbar                  = 1;         /* 指定状态栏位置 0底部 1顶部 */
static const float mfact                 = 0.6;       /* 主工作区 大小比例 */
static const int   nmaster               = 1;         /* 主工作区 窗口数量 */
static const unsigned int snap           = 10;        /* 边缘依附宽度 */
static const unsigned int baralpha       = 0xc0;      /* 状态栏透明度 */
static const unsigned int borderalpha    = 0xdd;      /* 边框透明度 */
static const char *fonts[]               = {
        "JetBrainsMono Nerd Font:style=medium:size=13:antialias=true:autohint=true",
        "WenQuanYi Zen Hei Mono:size=14:type=Regular:antialias=true:autohint=true",
        "monospace:size=15"
};
static const char dmenufont[]            = "WenQuanYi Zen Hei Mono:size=14";
static const char *colors[][3]           = {
        /* 颜色设置               ColFg：字体颜色      ColBg：背景颜色       ColBorder：边框颜色 */
        [SchemeNorm]        = { "#bbbbbb",          "#333333",          "#444444" },
        [SchemeSel]         = { "#ffffff",          "#37474F",          "#42A5F5" },
        [SchemeSelGlobal]   = { "#ffffff",          "#37474F",          "#FFC0CB" },
        [SchemeHid]         = { "#dddddd",          NULL,               NULL },
        [SchemeSystray]     = { NULL,               "#7799AA",          NULL },
        [SchemeUnderline]   = { "#7799AA",          NULL,               NULL },
        [SchemeNormTag]     = { "#bbbbbb",          "#333333",          NULL },
        [SchemeSelTag]      = { "#eeeeee",          "#333333",          NULL },
        [SchemeBarEmpty]    = { NULL,               "#111111",          NULL },
};
static const unsigned int alphas[][3]    = {
        /* 颜色设置               ColFg：字体颜色      ColBg：背景颜色       ColBorder：边框颜色 */
        [SchemeNorm]        = { OPAQUE,             baralpha,           borderalpha },
        [SchemeSel]         = { OPAQUE,             baralpha,           borderalpha },
        [SchemeSelGlobal]   = { OPAQUE,             baralpha,           borderalpha },
        [SchemeNormTag]     = { OPAQUE,             baralpha,           borderalpha },
        [SchemeSelTag]      = { OPAQUE,             baralpha,           borderalpha },
        [SchemeBarEmpty]    = { NULL,               0x11,               NULL },
        [SchemeStatusText]  = { OPAQUE,             0x88,               NULL },
};

// 自启动脚本位置
static const char *autostartshell = "/home/tnt/wm/config/dwm/autostart.sh";
static const char *statusbarscript = "$DWM/statusbar/statusbar.sh";

/* 自定义 scratchpad instance */
static const char scratchpadname[] = "scratchpad";

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", "#222222", "-nf", "#bbbbbb", "-sb", "#005577", "-sf", "#eeeeee", NULL };

/* 自定义tag名称 */
/* 自定义特定实例的显示状态 */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };


/* 自定义窗口显示规则 */
/* class instance title 主要用于定位窗口适合哪个规则 */
/* tags mask 定义符合该规则的窗口的tag 0 表示当前tag */
/* isfloating 定义符合该规则的窗口是否浮动 */
/* isglobal 定义符合该规则的窗口是否全局浮动 */
/* isnoborder 定义符合该规则的窗口是否无边框 */
/* monitor 定义符合该规则的窗口显示在哪个显示器上 -1 为当前屏幕 */
/* floatposition 定义符合该规则的窗口显示的位置 0 中间，1到9分别为9宫格位置，例如1左上，9右下，3右上 */
static const Rule rules[] = {
        /**
         * xprop(1):
         * WM_CLASS(STRING) = instance, class
         * WM_NAME(STRING) = title
         *
         * 优先级高 越在上面优先度越高
         */
        /* class                instance                title               togs mosk   isfloating  isglobal    isnoborder  monitor    floatposition */
        { "QQ",                 "qq",                   "图片查看器",         0,          1,          0,          0,          -1,        0 },            // qq图片查看器     浮动
        { "QQ",                 "qq",                   "群公告",            0,          1,          0,          0,           -1,       0 },            // qq群公告        浮动
        { "QQ",                 "qq",                   "视频播放器",         0,          1,          0,          0,          -1,        0 },            // qq视频播放器        浮动
        /* 普通优先级 */
        { "obs",                NULL,                   NULL,               1 << 3,     0,          0,          0,          -1,         0 },            // obs        tag -> 󰕧
        {"chrome",              NULL,                   NULL,               1 << 4,     0,          0,          0,          -1,         0 },            // chrome     tag -> 
        {"Chromium",            NULL,                   NULL,               1 << 4,     0,          0,          0,          -1,         0 },            // Chromium   tag -> 
        {"music",               NULL,                   NULL,               1 << 5,     1,          0,          1,          -1,         0 },            // music      tag ->  浮动、无边框
        { NULL,                 "qq",                   NULL,               1 << 6,     0,          0,          1,          -1,         0 },            // qq         tag -> ﬄ 无边框
        { NULL,                 "wechat.exe",           NULL,               1 << 7,     0,          0,          1,          -1,         0 },            // wechat     tag -> ﬐ 无边框
        { NULL,                 "wxwork.exe",           NULL,               1 << 8,     0,          0,          1,          -1,         0 },            // workwechat tag ->  无边框
        {"Vncviewer",           NULL,                   NULL,               0,          1,          0,          1,          -1,         2 },            // Vncviewer           浮动、无边框 屏幕顶部
        {"flameshot",           NULL,                   NULL,               0,          1,          0,          0,          -1,         0 },            // 火焰截图            浮动
        {"scratchpad",          "scratchpad",           "scratchpad",       TAGMASK,    1,          1,          1,          -1,         2 },            // scratchpad          浮动、全局、无边框 屏幕顶部
        {"Pcmanfm",             NULL,                   NULL,               0,          1,          0,          1,          -1,         3 },            // pcmanfm             浮动、无边框 右上角
        {"wemeetapp",           NULL,                   NULL,               TAGMASK,    1,          1,          0,          -1,         0 },            // !!!腾讯会议在切换tag时有诡异bug导致退出 变成global来规避该问题

        /** 部分特殊class的规则 */
        {"float",               NULL,                   NULL,               0,          1,          0,          0,          -1,         0 },            // class = float       浮动
        {"global",              NULL,                   NULL,               TAGMASK,    0,          1,          0,          -1,         0 },            // class = gloabl      全局
        {"noborder",            NULL,                   NULL,               0,          0,          0,          1,          -1,         0 },            // class = noborder    无边框
        {"FGN",                 NULL,                   NULL,               TAGMASK,    1,          1,          1,          -1,         0 },            // class = FGN         浮动、全局、无边框
        {"FG",                  NULL,                   NULL,               TAGMASK,    1,          1,          0,          -1,         0 },            // class = FG          浮动、全局
        {"FN",                  NULL,                   NULL,               0,          1,          0,          1,          -1,         0 },            // class = FN          浮动、无边框
        {"GN",                  NULL,                   NULL,               TAGMASK,    0,          1,          1,          -1,         0 },            // CLASS = GN          全局、无边框

        /** 优先度低 越在上面优先度越低 */
        { NULL,                 NULL,                   "crx_",             0,          1,          0,          0,          -1,         0 },            // 错误载入时 会有crx_ 浮动
        { NULL,                 NULL,                   "broken",           0,          1,          0,          0,          -1,         0 },            // 错误载入时 会有broken 浮动
};

static const char *overviewtag = "OVERVIEW";
static const Layout overviewlayout = { "󰕮",  overview };

/* 自定义布局 */
static const Layout layouts[] = {
        { "󰙀",        tile },               /* 平铺布局 */
        { "󰕰",        magicgrid },          /* 网格布局 */
};

#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG, cmd) \
    { MODKEY,              KEY, view,       {.ui = 1 << TAG, .v = cmd} }, \
    { MODKEY|ShiftMask,    KEY, tag,        {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,  KEY, toggleview, {.ui = 1 << TAG} }, \

static Key keys[] = {
    /* modifier            key              function          argument */
    { MODKEY,              XK_p,            spawn,            {.v = dmenucmd } },	     /* super p            |  打开 dmenucmd */
    { MODKEY,              XK_equal,        togglesystray,    {0} },                     /* super +            |  切换 托盘栏显示状态 */

    { MODKEY,              XK_Tab,          focusstack,       {.i = +1} },               /* super tab          |  本tag内切换聚焦窗口 */
    { MODKEY|ShiftMask,    XK_Tab,          focusstack,       {.i = -1} },               /* super shift tab    |  本tag内切换聚焦窗口 */
    { MODKEY,              XK_Up,           focusstack,       {.i = -1} },               /* super up           |  本tag内切换聚焦窗口 */
    { MODKEY,              XK_Down,         focusstack,       {.i = +1} },               /* super down         |  本tag内切换聚焦窗口 */

    { MODKEY,              XK_Left,         viewtoleft,       {0} },                     /* super left         |  聚焦到左边的tag */
    { MODKEY,              XK_Right,        viewtoright,      {0} },                     /* super right        |  聚焦到右边的tag */
    { MODKEY|ShiftMask,    XK_Left,         tagtoleft,        {0} },                     /* super shift left   |  将本窗口移动到左边tag */
    { MODKEY|ShiftMask,    XK_Right,        tagtoright,       {0} },                     /* super shift right  |  将本窗口移动到右边tag */

    { MODKEY,              XK_a,            toggleoverview,   {0} },                     /* super a            |  显示所有tag 或 跳转到聚焦窗口的tag */

    { MODKEY,              XK_comma,        setmfact,         {.f = -0.05} },            /* super ,            |  缩小主工作区 */
    { MODKEY,              XK_period,       setmfact,         {.f = +0.05} },            /* super .            |  放大主工作区 */

    { MODKEY,              XK_h,            hidewin,          {0} },                     /* super h            |  隐藏 窗口 */
    { MODKEY|ShiftMask,    XK_h,            restorewin,       {0} },                     /* super shift h      |  取消隐藏 窗口 */

    { MODKEY|ShiftMask,    XK_Return,       zoom,             {0} },                     /* super shift enter  |  将当前聚焦窗口置为主窗口 */

    { MODKEY,              XK_t,            togglefloating,   {0} },                     /* super t            |  开启/关闭 聚焦目标的float模式 */
    { MODKEY|ShiftMask,    XK_t,            toggleallfloating,{0} },                     /* super shift t      |  开启/关闭 全部目标的float模式 */
    { MODKEY,              XK_f,            fullscreen,       {0} },                     /* super f            |  开启/关闭 全屏 */
    { MODKEY|ShiftMask,    XK_f,            togglebar,        {0} },                     /* super shift f      |  开启/关闭 状态栏 */
    { MODKEY,              XK_g,            toggleglobal,     {0} },                     /* super g            |  开启/关闭 全局 */
    { MODKEY,              XK_u,            toggleborder,     {0} },                     /* super u            |  开启/关闭 边框 */
    { MODKEY,              XK_e,            incnmaster,       {.i = +1} },               /* super e            |  改变主工作区窗口数量 (1 2中切换) */

    { MODKEY,              XK_b,            focusmon,         {.i = +1} },               /* super b            |  光标移动到另一个显示器 */
    { MODKEY|ShiftMask,    XK_b,            tagmon,           {.i = +1} },               /* super shift b      |  将聚焦窗口移动到另一个显示器 */

    { MODKEY,              XK_c,            killclient,       {0} },                     /* super c            |  关闭窗口 */
    { MODKEY|ControlMask,  XK_c,            forcekillclient,  {0} },                     /* super ctrl c       |  强制关闭窗口(处理某些情况下无法销毁的窗口) */
    { MODKEY|ShiftMask,    XK_q,            quit,             {0} },                     /* super shift q      |  退出dwm */

	{ MODKEY|ShiftMask,    XK_space,        selectlayout,     {.v = &layouts[1]} },      /* super shift space  |  切换到网格布局 */
	{ MODKEY,              XK_o,            showonlyorall,    {0} },                     /* super o            |  切换 只显示一个窗口 / 全部显示 */

    { MODKEY|ControlMask,  XK_equal,        setgap,           {.i = -6} },               /* super ctrl +       |  窗口增大 */
    { MODKEY|ControlMask,  XK_minus,        setgap,           {.i = +6} },               /* super ctrl -       |  窗口减小 */
    { MODKEY|ControlMask,  XK_space,        setgap,           {.i = 0} },                /* super ctrl space   |  窗口重置 */

    { MODKEY|ControlMask,  XK_Up,           movewin,          {.ui = UP} },              /* super ctrl up      |  移动窗口 */
    { MODKEY|ControlMask,  XK_Down,         movewin,          {.ui = DOWN} },            /* super ctrl down    |  移动窗口 */
    { MODKEY|ControlMask,  XK_Left,         movewin,          {.ui = LEFT} },            /* super ctrl left    |  移动窗口 */
    { MODKEY|ControlMask,  XK_Right,        movewin,          {.ui = RIGHT} },           /* super ctrl right   |  移动窗口 */

    { MODKEY|Mod1Mask,     XK_Up,           resizewin,        {.ui = V_REDUCE} },        /* super alt up       |  调整窗口 */
    { MODKEY|Mod1Mask,     XK_Down,         resizewin,        {.ui = V_EXPAND} },        /* super alt down     |  调整窗口 */
    { MODKEY|Mod1Mask,     XK_Left,         resizewin,        {.ui = H_REDUCE} },        /* super alt left     |  调整窗口 */
    { MODKEY|Mod1Mask,     XK_Right,        resizewin,        {.ui = H_EXPAND} },        /* super alt right    |  调整窗口 */

  	{ MODKEY,              XK_k,            focusdir,         {.i = UP } },              /* super k            | 二维聚焦窗口 */
  	{ MODKEY,              XK_j,            focusdir,         {.i = DOWN } },            /* super j            | 二维聚焦窗口 */
  	{ MODKEY,              XK_h,            focusdir,         {.i = LEFT } },            /* super h            | 二维聚焦窗口 */
  	{ MODKEY,              XK_l,            focusdir,         {.i = RIGHT } },           /* super l            | 二维聚焦窗口 */
    { MODKEY|ShiftMask,    XK_k,            exchange_client,  {.i = UP } },              /* super shift k      | 二维交换窗口 (仅平铺) */
    { MODKEY|ShiftMask,    XK_j,            exchange_client,  {.i = DOWN } },            /* super shift j      | 二维交换窗口 (仅平铺) */
    { MODKEY|ShiftMask,    XK_h,            exchange_client,  {.i = LEFT} },             /* super shift h      | 二维交换窗口 (仅平铺) */
    { MODKEY|ShiftMask,    XK_l,            exchange_client,  {.i = RIGHT } },           /* super shift l      | 二维交换窗口 (仅平铺) */

    /* spawn + SHCMD 执行对应命令(已下部分建议完全自己重新定义) */
    { MODKEY,              XK_s,      togglescratch, SHCMD("st -t scratchpad -c float") },                      /* super s          | 打开scratch终端        */
    { MODKEY,              XK_Return, spawn, SHCMD("st") },                                                     /* super enter      | 打开st终端             */
    { MODKEY,              XK_minus,  spawn, SHCMD("st -c FG") },                                               /* super +          | 打开全局st终端         */
    { MODKEY,              XK_space,  spawn, SHCMD("st -c float") },                                            /* super space      | 打开浮动st终端         */
    { MODKEY,              XK_F1,     spawn, SHCMD("killall pcmanfm || pcmanfm") },                             /* super F1         | 打开/关闭pcmanfm       */
    { MODKEY,              XK_d,      spawn, SHCMD("rofi -show run") },                                         /* super d          | rofi: 执行run          */
//    { MODKEY,              XK_p,      spawn, SHCMD("$DWM/DEF/rofi.sh") },                                       /* super p          | rofi: 执行自定义脚本   */
    { MODKEY,              XK_n,      spawn, SHCMD("$DWM/DEF/blurlock.sh") },                                   /* super n          | 锁定屏幕               */
    { MODKEY|ShiftMask,    XK_Up,     spawn, SHCMD("$DWM/DEF/set_vol.sh up") },                                 /* super shift up   | 音量加                 */
    { MODKEY|ShiftMask,    XK_Down,   spawn, SHCMD("$DWM/DEF/set_vol.sh down") },                               /* super shift down | 音量减                 */
    { MODKEY|ShiftMask,    XK_a,      spawn, SHCMD("flameshot gui -c -p ~/Pictures/screenshots") },             /* super shift a    | 截图                   */
    { MODKEY|ShiftMask,    XK_q,      spawn, SHCMD("kill -9 $(xprop | grep _NET_WM_PID | awk '{print $3}')") }, /* super shift q    | 选中某个窗口并强制kill */

    /* super key : 跳转到对应tag (可附加一条命令 若目标目录无窗口，则执行该命令) */
    /* super shift key : 将聚焦窗口移动到对应tag */
    /* key tag cmd */
    TAGKEYS(                        XK_1,                      0,           0)
    TAGKEYS(                        XK_2,                      1,           0)
    TAGKEYS(                        XK_3,                      2,           0)
    TAGKEYS(                        XK_4,                      3,           0)
    TAGKEYS(                        XK_5,                      4,           0)
    TAGKEYS(                        XK_6,                      5,           0)
    TAGKEYS(                        XK_7,                      6,           0)
    TAGKEYS(                        XK_8,                      7,           0)
    TAGKEYS(                        XK_9,                      8,           0)
};

/**
 * Button1 ： 左键
 * Button2 ： 滚轮
 * Button3 ： 右键
 */
static Button buttons[] = {
    /* click               event mask       button            function       argument  */
    /* 点击窗口标题栏操作 */
    { ClkWinTitle,         0,               Button1,          hideotherwins, {0} },                                   // 左键        |  点击标题     |  隐藏其他窗口仅保留该窗口
    { ClkWinTitle,         0,               Button3,          togglewin,     {0} },                                   // 右键        |  点击标题     |  切换窗口显示状态
    /* 点击窗口操作 */
    { ClkClientWin,        MODKEY,          Button1,          movemouse,     {0} },                                   // super+左键  |  拖拽窗口     |  拖拽窗口
    { ClkClientWin,        MODKEY,          Button3,          resizemouse,   {0} },                                   // super+右键  |  拖拽窗口     |  改变窗口大小
    /* 点击tag操作 */
    { ClkTagBar,           0,               Button1,          view,          {0} },                                   // 左键        |  点击tag      |  切换tag
	{ ClkTagBar,           0,               Button3,          toggleview,    {0} },                                   // 右键        |  点击tag      |  切换是否显示tag
    { ClkTagBar,           MODKEY,          Button1,          tag,           {0} },                                   // super+左键  |  点击tag      |  将窗口移动到对应tag
    { ClkTagBar,           0,               Button4,          viewtoleft,    {0} },                                   // 鼠标滚轮上  |  tag          |  向前切换tag
	{ ClkTagBar,           0,               Button5,          viewtoright,   {0} },                                   // 鼠标滚轮下  |  tag          |  向后切换tag
    /* 点击状态栏操作 */
    { ClkStatusText,       0,               Button1,          clickstatusbar,{0} },                                   // 左键        |  点击状态栏   |  根据状态栏的信号执行 ~/scripts/dwmstatusbar.sh $signal L
    { ClkStatusText,       0,               Button2,          clickstatusbar,{0} },                                   // 中键        |  点击状态栏   |  根据状态栏的信号执行 ~/scripts/dwmstatusbar.sh $signal M
    { ClkStatusText,       0,               Button3,          clickstatusbar,{0} },                                   // 右键        |  点击状态栏   |  根据状态栏的信号执行 ~/scripts/dwmstatusbar.sh $signal R
    { ClkStatusText,       0,               Button4,          clickstatusbar,{0} },                                   // 鼠标滚轮上  |  状态栏       |  根据状态栏的信号执行 ~/scripts/dwmstatusbar.sh $signal U
    { ClkStatusText,       0,               Button5,          clickstatusbar,{0} },                                   // 鼠标滚轮下  |  状态栏       |  根据状态栏的信号执行 ~/scripts/dwmstatusbar.sh $signal D
                                                                                                                      //
    /* 点击bar空白处 */
    { ClkBarEmpty,         0,               Button1,          spawn, SHCMD("~/scripts/call_rofi.sh window") },        // 左键        |  bar空白处    |  rofi 执行 window
    { ClkBarEmpty,         0,               Button3,          spawn, SHCMD("~/scripts/call_rofi.sh drun") },          // 右键        |  bar空白处    |  rofi 执行 drun
};
