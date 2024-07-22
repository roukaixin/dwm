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
    {"obs", NULL, NULL, 1 << 3, false, false, false, -1, 0, false, 0},
    {"Google-chrome", "google-chrome", NULL, 1 << 4, false, false, false, -1, 0,
     false, 0},
    {"QQ", "qq", "QQ", 1 << 6, false, false, true, -1, 0, false, 0},
    // QQ 规则
    {"QQ", "qq", "图片查看器", 0, true, false, false, -1, 0, false, 0},
    {"QQ", "qq", "群公告", 0, true, false, false, -1, 0, false, 0},
    {"QQ", "qq", "视频播放器", 0, true, false, false, -1, 0, false, 0},
    {"QQ", "qq", "文件管理器", 0, true, false, false, -1, 0, false, 0},
    {"QQ", "qq", "收藏", 0, true, false, false, -1, 0, false, 0},
    // 微信规则
    {NULL, NULL, "图片查看", 0, true, false, false, -1, 0, false, 0},
    // telegram-desktop 规则
    {"TelegramDesktop", "telegram-desktop", "Media viewer", 0, true, false,false, -1, 0, false, 0},
    {"TelegramDesktop", "telegram-desktop", "媒体查看器", 0, true, false,false, -1, 0, false, 0},
    {"Gimp", "gimp", "新建模板", 0, true, false, false, -1, 0, false, 0},
    {"Gimp", "gimp", "图像", 0, true, false, false, -1, 0, false, 2},
    {"Gimp", "script-fu", "Script-Fu：", 0, true, false, false, -1, 0, false,
     1},
    {"Gimp", "gimp", "退出 GIMP", 0, true, false, false, -1, 0, false, 0},
    {"Typora", "typora", "保存", 0, true, false, false, -1, 0, false, 0},
    {"polkit-kde-authentication-agent-1", "polkit-kde-authentication-agent-1",
     NULL, 0, true, false, false, -1, 0, false, 0},
    {"jetbrains-toolbox", "JetBrains Toolbox", "JetBrains Toolbox", 0, true,
     false, false, -1, 3, false, 2},
    {"Xdg-desktop-portal-gtk", "xdg-desktop-portal-gtk", "所有文件", 0, true,
     false, false, -1, 0, false, 1},
    {"Xdg-desktop-portal-gtk", "xdg-desktop-portal-gtk", "打开文件", 0, true,
     false, false, -1, 0, false, 1},
    {"Nm-applet", "nm-applet", "Wi-Fi 网络", 0, true, false, false, -1, 0,
     false, 1},
    {"Electron", "electron", "打开文件", 0, true, false, false, -1, 0, false,
     1},
    // Vncviewer           浮动、无边框 屏幕顶部
    {"Vncviewer", NULL, NULL, 0, true, false, true, -1, 2, false, 0},
    // scratchpad          浮动、全局、无边框 屏幕顶部
    {"scratchpad", "scratchpad", "scratchpad", TAGMASK, true, true, true, -1, 2,
     false, 0},
    /** 部分特殊class的规则 */
    // class = float       浮动
    {"float", NULL, NULL, 0, true, false, false, -1, 0, false, 0},
    // class = gloabl      全局
    {"global", NULL, NULL, TAGMASK, false, true, false, -1, 0, false, 0},
    // class = noborder    无边框
    {"noborder", NULL, NULL, 0, false, false, true, -1, 0, false, 0},
    // class = FGN         浮动、全局、无边框
    {"FGN", NULL, NULL, TAGMASK, true, true, true, -1, 0, false, 0},
    // class = FG          浮动、全局
    {"FG", NULL, NULL, TAGMASK, true, true, false, -1, 0, false, 0},
    // class = FN          浮动、无边框
    {"FN", NULL, NULL, 0, true, false, true, -1, 0, false, 0},
    // CLASS = GN          全局、无边框
    {"GN", NULL, NULL, TAGMASK, false, true, true, -1, 0, false, 0},
    // 错误载入时 会有crx_ 浮动
    {NULL, NULL, "crx_", 0, true, false, false, -1, 0, false, 0},
    // 错误载入时 会有broken 浮动
    {NULL, NULL, "broken", 0, true, false, false, -1, 0, false, 0},
};
