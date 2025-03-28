#pragma once
#include <X11/XF86keysym.h>

static int showsystray                      = 1;         /* 是否显示托盘栏 */
static const int newclientathead            = 0;         /* 定义新窗口在栈顶还是栈底 */
static const unsigned int borderpx          = 2;         /* 窗口边框大小 */
static const unsigned int systraypinning    = 1;         /* 托盘跟随的显示器 0代表不指定显示器 */
static const unsigned int systrayspacing    = 1;         /* 托盘间距 */
static const unsigned int systrayspadding   = 5;        /* 托盘和状态栏的间隙 */
static int gappi                            = 12;        /* 窗口与窗口 缝隙大小 */
static int gappo                            = 12;        /* 窗口与边缘 缝隙大小 */
static const int g_gappo                    = 12;        /* 窗口与窗口 缝隙大小 不可变 用于恢复时的默认值 */
static const int g_gappi                    = 12;        /* 窗口与边缘 缝隙大小 不可变 用于恢复时的默认值 */
static const int vertpad                    = 5;         /* vertical padding of bar */
static const int sidepad                    = 5;         /* horizontal padding of bar */
static const int showbar                    = 1;         /* 是否显示状态栏 */
static const int topbar                     = 1;         /* 指定状态栏位置 0底部 1顶部 */
static const float mfact                    = 0.60f;     /* 主工作区 大小比例 */
static const int   nmaster                  = 1;         /* 主工作区 窗口数量 */
static const unsigned int snap              = 10;        /* 边缘依附宽度 */
static const unsigned int baralpha          = 0xc0;      /* 状态栏透明度 */
static const unsigned int borderalpha       = 0xdd;      /* 边框透明度 */
static const unsigned int null_alpha        = 0x00;
static const char *fonts[]                  = {
        "JetBrainsMono Nerd Font:style=Regular:size=13:antialias=true:autohint=true"
};
static const char dmenufont[]               = "JetBrainsMono Nerd Font:size=13";
static const char *colors[][3] = {
        /* 颜色设置               ColFg：字体颜色      ColBg：背景颜色       ColBorder：边框颜色 */
        [SchemeNorm]        = { "#bbbbbb",          "#333333",          "#444444" },
        [SchemeSel]         = { "#ffffff",          "#37474F",          "#42A5F5" },
        [SchemeSelGlobal]   = { "#ffffff",          "#37474F",          "#FFC0CB" },
        [SchemeHid]         = { "#dddddd",          NULL,               NULL },
        [SchemeSystray]     = { NULL,               "#7799AA",          NULL },
        [SchemeNormTag]     = { "#bbbbbb",          "#333333",          NULL },
        [SchemeSelTag]      = { "#eeeeee",          "#37474F",          NULL },
        [SchemeUnderline]   = { "#7799AA",          NULL,               NULL },
        [SchemeSelTitle]    = { "#ffffff",          "#335566",          NULL },
        [SchemeBarEmpty]    = { NULL,               "#37474F",          NULL },
};
static const unsigned int alphas[][3] = {
        /* 颜色设置               ColFg：字体颜色      ColBg：背景颜色       ColBorder：边框颜色 */
        [SchemeNorm]        = { OPAQUE,             baralpha,           borderalpha },
        [SchemeSel]         = { OPAQUE,             baralpha,           borderalpha },
        [SchemeSelGlobal]   = { OPAQUE,             baralpha,           borderalpha },
        [SchemeNormTag]     = { OPAQUE,             baralpha,           borderalpha },
        [SchemeSelTag]      = { OPAQUE,             baralpha,           borderalpha },
        [SchemeBarEmpty]    = { null_alpha,         0x11,               null_alpha },
        [SchemeStatusText]  = { OPAQUE,             0x88,               null_alpha },
};

// 自启动
//        "dunst",                                         NULL,
//        "'xss-lock",    "--",       "bash",     "~/wm/config/lock/blurlock.sh'",     NULL,
static const char *const autostart[] = {
    "fcitx5",   "-d",                                                                                               NULL,
    "nm-applet",                                                                                                    NULL,
    "udiskie",                                                                                                      NULL,
    "numlockx",                                                                                                     NULL,
    // fedora : /usr/libexec/polkit-gnome-authentication-agent-1
    "/usr/lib/polkit-gnome/polkit-gnome-authentication-agent-1",                                                    NULL,
    "blueman-applet",                                                                                               NULL,
    "sh",   "-c",   "while true; do feh --bg-fill --randomize --no-fehbg ~/wm/wallpaper/*.png; sleep 1800; done",   NULL,
    "snipaste",                                                                                                     NULL,
    "slstatus",                                                                                                     NULL,
    "picom",    "--daemon",                                                                                         NULL,
    NULL /* terminate */
};

/* 自定义 scratchpad instance */
static const char scratchpadname[] = "scratchpad";

/* commands */
static char dmenumon[2] = "0";
static const char *dmenucmd[] = {
        "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", "#222222", "-nf", "#bbbbbb", "-sb", "#005577", "-sf", "#eeeeee", NULL
};
/* 增加亮度 */
static const char *brighter[]   = { "brightnessctl", "set", "1%+", NULL };
/* 减少亮度 */
static const char *dimmer[]     = { "brightnessctl", "set", "1%-", NULL };
/* 增加音量 */
static const char *up_vol[]     = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "+5%", NULL };
/* 减少音量 */
static const char *down_vol[]   = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "-5%", NULL };
/* 切换是否为静音 */
static const char *mute_vol[]   = { "pactl", "set-sink-mute", "@DEFAULT_SINK@", "toggle", NULL };

static const char *scratchpad_terminal[]         = { "kitty", "--title", "scratchpad", "--class", "scratchpad", "-o", "initial_window_width=70c", "-o", "initial_window_height=17c", NULL };
static const char *fg_terminal[]                 = { "kitty", "--class", "FG", "-o", "initial_window_width=70c", "-o", "initial_window_height=17c", NULL };
static const char *float_terminal[]              = { "kitty", "--class", "float", "-o", "initial_window_width=70c", "-o", "initial_window_height=17c", NULL };
static const char *lock_monitor[]                = { "/bin/sh", "-c", "sh $DWM/script/blurlock.sh", NULL };
static const char *kill_9[]                      = { "/bin/sh", "-c", "kill -9 $(xprop | grep _NET_WM_PID | awk '{print $3}')", NULL };


/* 显示 tags */
static const char *tags[] = {"󰎤", "󰎧", "󰎪", "󰎭", "󰎱", "󰎳", "󰎶", "󰎹", "󰎼" };

/**
 * 自定义窗口显示规则，越在上面优先级越高
 *
 * class instance title 主要用于定位窗口适合哪个规则
 * tags mask: 定义符合该规则的窗口的tag 0 表示当前tag
 * is_floating: 定义符合该规则的窗口是否浮动。1浮动，0不浮动
 * is_global: 定义符合该规则的窗口是否全局。1全局，0不全局(当前 tag)
 * is_no_border: 定义符合该规则的窗口是否无边框。1无边框，0有边宽
 * monitor: 定义符合该规则的窗口显示在哪个显示器上 -1 为当前屏幕
 * float_position: 定义符合该规则的窗口显示的位置 0中间，1到9分别为9宫格位置，例如1左上，9右下，3右上
 * is_fullscreen: 是否全屏，只有当 isfloating 为 1 时，才有效。true全屏、false不全屏
 * client_type: 窗口类型。0：普通窗口、1：瞬时窗口、2：其他窗口
 */
static const Rule rules[] = {
    /**
     * xprop(1):
     * WM_CLASS(STRING) = instance, class
     * WM_NAME(STRING) = title
     *
     * class、instance、title、tags
     * mask、is_floating、is_global、is_no_border、monitor、float_position
     * 优先级高 越在上面优先度越高
     */
    { "obs", NULL, NULL, 1 << 3, 0, 0, 0, -1, 0, 0, 0 },
    { "Google-chrome", "google-chrome", NULL, 1 << 4, 0, 0, 0, -1, 0,0, 0 },
    { "QQ", "qq", "QQ", 1 << 6, 0, 0, 1, -1, 0, 0, 0 },
    // QQ 规则
    { "QQ", "qq", "图片查看器", 0, 1, 0, 0, -1, 0, 0, 0 },
    { "QQ", "qq", "群公告", 0, 1, 0, 0, -1, 0, 0, 0 },
    { "QQ", "qq", "视频播放器", 0, 1, 0, 0, -1, 0, 0, 0 },
    { "QQ", "qq", "文件管理器", 0, 1, 0, 0, -1, 0, 0, 0 },
    { "QQ", "qq", "收藏", 0, 1, 0, 0, -1, 0, 0, 0 },
    { "wechat", "wechat", "预览", 0, 1, 0, 0, -1, 0, 0, 0 },
    { "TelegramDesktop", "telegram-desktop", "Media viewer", 0, 1, 0,0, -1, 0, 0, 0 },
    { "TelegramDesktop", "telegram-desktop", "媒体查看器", 0, 1, 0,0, -1, 0, 0, 0 },
    { "Gimp", "gimp", "新建模板", 0, 1, 0, 0, -1, 0, 0, 0 },
    { "Gimp", "gimp", "图像", 0, 1, 0, 0, -1, 0, 0, 2 },
    { "Gimp", "script-fu", "Script-Fu：", 0, 1, 0, 0, -1, 0, 0,1 },
    { "Gimp", "gimp", "退出 GIMP", 0, 1, 0, 0, -1, 0, 0, 0 },
    { "Typora", "typora", "保存", 0, 1, 0, 0, -1, 0, 0, 0 },
    { "Pcmanfm", "pcmanfm", "文件", 0, 1, 0, 0, -1, 5, 0, 0 },
    { "polkit-kde-authentication-agent-1", "polkit-kde-authentication-agent-1",NULL, 0, 1, 0, 0, -1, 0, 0, 0 },
    { "jetbrains-toolbox", "JetBrains Toolbox", "JetBrains Toolbox", 0, 1,0, 0, -1, 3, 0, 2 },
    { "Xdg-desktop-portal-gtk", "xdg-desktop-portal-gtk", "所有文件", 0, 1,0, 0, -1, 0, 0, 1 },
    { "Xdg-desktop-portal-gtk", "xdg-desktop-portal-gtk", "打开文件", 0, 1,0, 0, -1, 0, 0, 1 },
    { "Xdg-desktop-portal-gtk", "xdg-desktop-portal-gtk", "打开文件", 0, 1,0, 0, -1, 0, 0, 0 },
    { "Xdg-desktop-portal-gtk", "xdg-desktop-portal-gtk", "选择文件夹", 0, 1,0, 0, -1, 0, 0, 1 },
    { "Nm-applet", "nm-applet", "Wi-Fi 网络", 0, 1, 0, 0, -1, 0,0, 1 },
    { "Electron", "electron", "打开文件", 0, 1, 0, 0, -1, 0, 0,1 },
    // Vncviewer           浮动、无边框 屏幕顶部
    { "Vncviewer", NULL, NULL, 0, 1, 0, 1, -1, 2, 0, 0 },
    // scratchpad          浮动、全局、无边框 屏幕顶部
    { "scratchpad", "scratchpad", "scratchpad", TAGMASK, 1, 1, 1, -1, 2,0, 0 },
    /** 部分特殊class的规则 */
    // class = float       浮动
    { "float", NULL, NULL, 0, 1, 0, 0, -1, 0, 0, 0 },
    // class = gloabl      全局
    { "global", NULL, NULL, TAGMASK, 0, 1, 0, -1, 0, 0, 0 },
    // class = noborder    无边框
    { "noborder", NULL, NULL, 0, 0, 0, 1, -1, 0, 0, 0 },
    // class = FGN         浮动、全局、无边框
    { "FGN", NULL, NULL, TAGMASK, 1, 1, 1, -1, 0, 0, 0 },
    // class = FG          浮动、全局
    { "FG", NULL, NULL, TAGMASK, 1, 1, 0, -1, 0, 0, 0 },
    // class = FN          浮动、无边框
    { "FN", NULL, NULL, 0, 1, 0, 1, -1, 0, 0, 0 },
    // CLASS = GN          全局、无边框
    { "GN", NULL, NULL, TAGMASK, 0, 1, 1, -1, 0, 0, 0 },
    // 错误载入时 会有crx_ 浮动
    { NULL, NULL, "crx_", 0, 1, 0, 0, -1, 0, 0, 0 },
    // 错误载入时 会有broken 浮动
    { NULL, NULL, "broken", 0, 1, 0, 0, -1, 0, 0, 0 },
};

// 环境变量
static const Env envs[] = {
    { "LANG",                                "zh_CN.UTF-8" },
    { "LANGUAGE",                            "zh_CN:en_US" },
    { "GTK_IM_MODULE",                       "fcitx" },
    { "QT_IM_MODULE",                        "fcitx" },
    { "XMODIFIERS",                          "@im=fcitx" },
    { "SDL_IM_MODULE",                       "fcitx" },
    { "GLFW_IM_MODULE",                      "ibus" },
};

/* 自定义布局 */
static const Layout layouts[] = {
        { "󰙀", tile },               /* 平铺布局 */
        { "󰕰", magicgrid },          /* 网格布局 */
        { "", scroll },          /* 网格布局 */
};

#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG, cmd) \
    { MODKEY,              KEY, view,       {.ui = 1 << TAG, .v = cmd} }, \
    { MODKEY|ShiftMask,    KEY, tag,        {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,  KEY, toggleview, {.ui = 1 << TAG} }, \


/*
Mod4Mask : win
ShiftMask : shift
ControlMask : ctrl
Mod1Mask : alt
space : 空格
*/
static const Key keys[] = {
    /* modifier            key              function          argument */
    { MODKEY,              XK_equal,        togglesystray,    {0} },                        /* super =            |   切换显示系统托盘 */
    { MODKEY,              XK_Tab,          focusstack,       {.i = +1} },                  /* super tab          |   本 tag 向下切换聚焦窗口 */
    { MODKEY|ShiftMask,    XK_Tab,          focusstack,       {.i = -1} },                  /* super shift tab    |   本 tag 向上切换聚焦窗口 */
    { MODKEY,              XK_Left,         viewtoleft,       {0} },                        /* super left         |   切换到左边的 tag */
    { MODKEY,              XK_Right,        viewtoright,      {0} },                        /* super right        |   切换到右边的 tag */
    { MODKEY|ShiftMask,    XK_Left,         tagtoleft,        {0} },                        /* super shift left   |   将本窗口移动到左边 tag */
    { MODKEY|ShiftMask,    XK_Right,        tagtoright,       {0} },                        /* super shift right  |   将本窗口移动到右边 tag */
    { MODKEY,              XK_a,            previewallwin,    {0} },                        /* super a            |   overview */
    { MODKEY,              XK_comma,        setmfact,         {.f = -0.05f} },              /* super ,            |   缩小主工作区 */
    { MODKEY,              XK_period,       setmfact,         {.f = +0.05f} },              /* super .            |   放大主工作区 */
    { MODKEY,              XK_i,            hidewin,          {0} },                        /* super i            |   隐藏窗口 */
    { MODKEY|ShiftMask,    XK_i,            restorewin,       {0} },                        /* super shift i      |   取消隐藏窗口 */
    { MODKEY,              XK_Return,       spawn,            SHCMD("kitty") },             /* super enter        |   打开终端 */
    { MODKEY|ShiftMask,    XK_Return,       zoom,             {0} },                        /* super shift enter  |   将当前聚焦窗口置为主窗口 */
    { MODKEY,              XK_v,            togglefloating,   {0} },                        /* super v            |   切换浮动模式(聚焦窗口) */
    { MODKEY|ShiftMask,    XK_v,            toggleallfloating,{0} },                        /* super shift v      |   切换浮动模式(tag下全部窗口 */
    { MODKEY,              XK_f,            togglefullscreen, {0} },                        /* super f            |   打开/关闭全屏 */
    { MODKEY,              XK_b,            togglebar,        {0} },                        /* super b            |   切换 bar */
    { MODKEY,              XK_g,            toggleglobal,     {0} },                        /* super g            |  开启/关闭 全局 */
    { MODKEY,              XK_u,            toggleborder,     {0} },                        /* super u            |  开启/关闭 边框 */
    { MODKEY,              XK_e,            incnmaster,       {.i = +1} },                  /* super e            |  改变主工作区窗口数量 (1 2中切换) */
    { MODKEY,              XK_m,            focusmon,         {.i = +1} },                  /* super m            |  光标移动到另一个显示器 重复按键 */
    { MODKEY|ShiftMask,    XK_m,            tagmon,           {.i = +1} },                  /* super shift m      |  将聚焦窗口移动到另一个显示器 */
    { MODKEY,              XK_c,            killclient,       {0} },                        /* super c            |  关闭窗口 */
    { MODKEY|ControlMask,  XK_c,            forcekillclient,  {0} },                        /* super ctrl c       |  强制关闭窗口(处理某些情况下无法销毁的窗口) */
    { MODKEY|ShiftMask,    XK_q,            quit,             {0} },                        /* super shift q      |  退出 */
    { MODKEY|ShiftMask,    XK_space,        toggle_layout,    {0} },         /* super shift space  |  切换布局 */
    { MODKEY,              XK_o,            showonlyorall,    {0} },                        /* super o            |  切换 只显示一个窗口 / 全部显示 */
    { MODKEY|ControlMask,  XK_equal,        setgap,           {.i = -6} },                  /* super ctrl +       |  窗口增大 */
    { MODKEY|ControlMask,  XK_minus,        setgap,           {.i = +6} },                  /* super ctrl -       |  窗口减小 */
    { MODKEY|ControlMask,  XK_space,        setgap,           {.i = 0} },                   /* super ctrl space   |  窗口重置 */
    { MODKEY|ControlMask,  XK_Up,           movewin,          {.ui = UP} },                 /* super ctrl up      |  移动窗口 */
    { MODKEY|ControlMask,  XK_Down,         movewin,          {.ui = DOWN} },               /* super ctrl down    |  移动窗口 */
    { MODKEY|ControlMask,  XK_Left,         movewin,          {.ui = LEFT} },               /* super ctrl left    |  移动窗口 */
    { MODKEY|ControlMask,  XK_Right,        movewin,          {.ui = RIGHT} },              /* super ctrl right   |  移动窗口 */
    { MODKEY|Mod1Mask,     XK_Up,           resizewin,        {.ui = V_REDUCE} },           /* super alt up       |  调整窗口 */
    { MODKEY|Mod1Mask,     XK_Down,         resizewin,        {.ui = V_EXPAND} },           /* super alt down     |  调整窗口 */
    { MODKEY|Mod1Mask,     XK_Left,         resizewin,        {.ui = H_REDUCE} },           /* super alt left     |  调整窗口 */
    { MODKEY|Mod1Mask,     XK_Right,        resizewin,        {.ui = H_EXPAND} },           /* super alt right    |  调整窗口 */
    { MODKEY,              XK_k,            focusdir,         {.i = UP } },                 /* super k            | 二维聚焦窗口 */
    { MODKEY,              XK_j,            focusdir,         {.i = DOWN } },               /* super j            | 二维聚焦窗口 */
    { MODKEY,              XK_h,            focusdir,         {.i = LEFT } },               /* super h            | 二维聚焦窗口 */
    { MODKEY,              XK_l,            focusdir,         {.i = RIGHT } },              /* super l            | 二维聚焦窗口 */
    { MODKEY|ShiftMask,    XK_k,            exchange_client,  {.i = UP } },                 /* super shift k      | 二维交换窗口 (仅平铺) */
    { MODKEY|ShiftMask,    XK_j,            exchange_client,  {.i = DOWN } },               /* super shift j      | 二维交换窗口 (仅平铺) */
    { MODKEY|ShiftMask,    XK_h,            exchange_client,  {.i = LEFT} },                /* super shift h      | 二维交换窗口 (仅平铺) */
    { MODKEY|ShiftMask,    XK_l,            exchange_client,  {.i = RIGHT } },              /* super shift l      | 二维交换窗口 (仅平铺) */
    { MODKEY,              XK_s,            togglescratch,    {.v = scratchpad_terminal} }, /* super s            | 打开scratch终端 */
    { MODKEY,              XK_minus,        spawn,            {.v = fg_terminal} },         /* super -            | 打开全局终端 */
    { MODKEY,              XK_space,        spawn,            {.v = float_terminal} },      /* super space        | 打开浮动终端 */
    { MODKEY,              XK_n,            spawn,            {.v = lock_monitor} },        /* super n            | 锁定屏幕 */
    { MODKEY|ShiftMask,    XK_c,            spawn,            {.v = kill_9} },              /* super shift c      | 选中某个窗口并强制kill */
    { MODKEY,              XK_p,            spawn,          {.v = dmenucmd } },             /* super p            | 打开启动器 */
    { 0,                   XF86XK_MonBrightnessDown,    spawn,          {.v = dimmer } },   /*                    | 降低亮度（window下的调节快捷键） */
    { 0,                   XF86XK_MonBrightnessUp,      spawn,          {.v = brighter } }, /*                    | 升高亮度（window下的调节快捷键） */
    { 0,                   XF86XK_AudioMute,            spawn,          {.v = mute_vol } }, /*                    | 切换是否为静音（window下的调节快捷键 */
    { 0,                   XF86XK_AudioLowerVolume,     spawn,          {.v = down_vol } }, /*                    | 降低音量（window下的调节快捷键） */
    { 0,                   XF86XK_AudioRaiseVolume,     spawn,          {.v = up_vol } },   /*                    | 升高音量（window下的调节快捷键 */
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
static const Button buttons[] = {
    /* click               event mask       button            function       argument  */
    /* 点击窗口标题栏操作 */
    { ClkWinTitle,         0,               Button1,          hideotherwins, {0} },                                   // 左键        |  点击标题     |  隐藏其他窗口仅保留该窗口
    { ClkWinTitle,         0,               Button3,          togglewin,     {0} },                                   // 右键        |  点击标题     |  切换窗口显示状态
    /* 点击窗口操作 */
    { ClkClientWin,        MODKEY,          Button1,          movemouse,     {0} },                                   // super+左键  |  拖拽窗口     |  拖拽窗口
    { ClkClientWin,        MODKEY,          Button3,          resizemouse,   {0} },                                   // super+右键  |  拖拽窗口     |  改变窗口大小
    /* 点击 tag 操作 */
    { ClkTagBar,           0,               Button1,          view,          {0} },                                   // 左键        |  点击tag      |  切换tag
	{ ClkTagBar,           0,               Button3,          toggleview,    {0} },                                   // 右键        |  点击tag      |  切换是否显示tag
    { ClkTagBar,           MODKEY,          Button1,          tag,           {0} },                                   // super+左键  |  点击tag      |  将窗口移动到对应tag
    { ClkTagBar,           0,               Button4,          viewtoleft,    {0} },                                   // 鼠标滚轮上   |  tag          |  向前切换tag
	{ ClkTagBar,           0,               Button5,          viewtoright,   {0} },                                   // 鼠标滚轮下   |  tag          |  向后切换tag
};
