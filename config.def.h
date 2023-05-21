/* See LICENSE file for copyright and license details. */


/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* 系统托盘间隙 systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray            = 1;        /* 是否显示系统托盘。0否，1是 */
static const int showbar                = 1;        /* 是否显示 bar 。0否，1是 */
static const int topbar                 = 1;        /* bar 是否在顶部。0底部，1顶部 */
static const int new_client_in_top      = 0;        /* 新打开的窗口是否在顶部。1顶部，0底部 */
static const unsigned int gappih        = 10;       /* 水平窗口和窗口的间隙 */
static const unsigned int gappiv        = 10;       /* 垂直窗口和窗口的间隙 */
static const unsigned int gappoh        = 10;       /* 水平方向：窗口和屏幕边缘之间的间隙 */
static const unsigned int gappov        = 10;       /* 垂直方向：窗口和屏幕边缘之间的间隙 */
static const unsigned int user_bh       = 2;        /* bar 的高度，默认值为 2 */
static const Bool viewontag             = True;     /* 是否开启移动窗口到其他 tag 时，跟随到移动的 tag */
static const char *fonts[]              = {
                                            "JetBrainsMono Nerd Font:style=medium:size=13:antialias=true:autohint=true",
										    "WenQuanYi Zen Hei Mono:size=14:type=Regular:antialias=true:autohint=true",
										    "monospace:size=15"
									    };
static const char dmenufont[]       = "WenQuanYi Zen Hei Mono:size=14";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const unsigned int baralpha = 0xc0;
static const unsigned int borderalpha = 0xdd;
static const char *colors[][3]      = {
	/*               fg(字体颜色)         bg(背景颜色)         border(边框颜色)   */
	[SchemeNorm] = { "#bbbbbb", "#333333", "#444444" },      /* 未激活（未选中） */
	[SchemeSel]  = { "#ffffff", "#37474F", "#42A5F5"  },     /* 激活的选项 */
    [SchemeSystray] = { NULL, "#7799AA", NULL },             /* 系统托盘 */
    [SchemeHov]  = { col_gray4, col_cyan,  col_cyan  },
    [SchemeHid]  = { col_cyan,  col_gray1, col_cyan  },
    [SchemeBarEmpty] = { NULL, "#111111", NULL },
};

static const unsigned int alphas[][3]      = {
        /*               fg      bg        border*/
        [SchemeNorm] = { OPAQUE, baralpha, borderalpha },
        [SchemeSel]  = { OPAQUE, baralpha, borderalpha },
        [SchemeBarEmpty] = { OPAQUE, 0x11, borderalpha },
};

// 自启动脚本位置
static const char *autostartshell = "/home/tnt/wm/config/dwm/autostart.sh";

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/*  xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       		tags mask     isfloating   monitor */
	{ "QQ",       "qq",       "图片查看器",		0,            1,           -1 }, 	// qq图片查看器         浮动
	{ "QQ",       "qq",       "群公告",		    0,            1,           -1 }, 	// qq群公告            浮动
	{ "QQ",       "qq",       "视频播放器",		0,            1,           -1 }, 	// qq视频播放器         浮动
	{ "Gimp",     NULL,       NULL,       		0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       		1 << 8,       0,           -1 },
};

/* layout(s) */
static const double mfact       = 0.55;     /* 主窗口的大小占比 [0.05..0.95] */
static const int nmaster        = 1;        /* master 区域的客户数量 */
static const int resizehints    = 1;        /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1;        /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
    { "󰙀",        tile },         /* 平铺布局 */
	{ "><>",      NULL },         /* 没有布局功能，意味着浮动行为 */
	{ "[M]",      monocle },      /* 单片镜布局 */
    { "󰕰",        grid },         /* 网格布局 */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "80x16", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },	        // 打开 dmenucmd
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },	        // 打开 st 终端
    { MODKEY,                       XK_grave,  togglescratch,  {.v = scratchpadcmd } },     // 打开临时窗口
	{ MODKEY,                       XK_b,      togglebar,      {0} },				        // 隐藏 bar
	// { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },		        // 焦点切换到下一个窗口
	// { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },		        // 焦点切换到上一个窗口
    { MODKEY,                       XK_j,      focusstackvis,  {.i = +1 } },                // 焦点切换到下一个窗口（不包括隐藏窗口）
    { MODKEY,                       XK_k,      focusstackvis,  {.i = -1 } },                // 焦点切换到上一个窗口（不包括隐藏窗口）
    { MODKEY|ShiftMask,             XK_j,      focusstackhid,  {.i = +1 } },                // 焦点切换到下一个窗口（全部窗口）
    { MODKEY|ShiftMask,             XK_k,      focusstackhid,  {.i = -1 } },                // 焦点切换到上一个窗口（全部窗口）
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },		        // 窗口横排序
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },		        // 窗口竖排序
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },		        // 主窗口减少 5%
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },		        // 主窗口增加 5%
	{ MODKEY,                       XK_Return, zoom,           {0} },				        // 把窗口提为主窗口
	{ MODKEY,                       XK_Tab,    view,           {0} },				        // 切换最近的上一个tag
	{ MODKEY,             			XK_c,      killclient,     {0} },				        // 关闭窗口
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },	    // 平铺
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },	    // 没有布局
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },	    // 单片镜
    { MODKEY,                       XK_g,      setlayout,      {.v = &layouts[3]} },        // 网格布局
	{ MODKEY,                       XK_space,  setlayout,      {0} },                       // 恢复到第一布局
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
    { MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },                       // 窗口最大化（全屏）
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
    { MODKEY,                       XK_s,      show,           {0} },
    { MODKEY|ShiftMask,             XK_s,      showall,        {0} },
    { MODKEY|ShiftMask,             XK_h,      hide,           {0} },                       // 隐藏窗口
    { MODKEY|ShiftMask,             XK_Up,     movethrow,      {.ui = DIR_N  }},
    { MODKEY|ShiftMask,             XK_Down,   movethrow,      {.ui = DIR_S  }},
    { MODKEY|ShiftMask,             XK_Left,   movethrow,      {.ui = DIR_W  }},
    { MODKEY|ShiftMask,             XK_Right,  movethrow,      {.ui = DIR_E  }},
    { MODKEY|ShiftMask,             XK_m,      movethrow,      {.ui = DIR_C  }},
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },				// 关闭 dwm
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
//	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
//	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
    { ClkWinTitle,          0,              Button1,        togglewin,      {0} },                  // 切换窗口显示状态
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },                  // 拖动窗口
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },                  // 改变窗口大小
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

