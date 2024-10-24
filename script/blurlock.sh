#! /bin/bash
# 依赖包： i3lock-color

# --radius : 圆的半径。默认90
# --bar-indicator : 解锁时按键显示为条形。默认是圆形
# --bar-direction ： 条形的方向。0，1，2
# --bar-max-height ： 一个条形的最大高度
# --bar-color ： 设置条形的颜色
# --keyhl-color : 设置按键圆环上高亮弧线的颜色。
# --bshl-color : 设置退格键时圆环上高亮弧线的颜色。
# --redraw-thread : 启动一个单独的线程来重绘屏幕。从安全的角度来看可能更糟，但使条形指示器仍然发挥作用,当 PAM 进行身份验证时，通常会定期重绘。
# --date-str : 日期格式
# --{time, date, layout, verif, wrong, greeter}-size : 字体大小
# --time-color : 颜色(rrggbbaa) aa透明度

# -k, --clock, --force-clock : 显示时间

#    --blur 5 \
#    --bar-indicator \
#    --bar-pos y+h \
#    --bar-direction 1 \
#    --bar-max-height 50 \
#    --bar-base-width 50 \
#    --bar-color 00000022 \
#    --bar-periodic-step 50 \
#    --bar-step 20 \
#    --status-pos x+5:y+h-16 \

# 中英文适配
case "$LANG" in
  "zh_CN.UTF-8")
  verify_text="身份验证"
  wrong_text="验证失败"
  no_input_text="没有输入"
  date_format="%A, %Y年 %m月 %d日 "
  ;;
  "en_US.UTF-8")
  verify_text="verifying…"
  wrong_text="wrong!"
  no_input_text="no input"
  date_format="%A,  %m %Y "
  ;;
esac

i3lock \
    --blur 5 \
    --radius 100 \
    --keyhl-color ffffffcc \
    --clock \
    --force-clock \
    --time-pos x+70:h-100 \
    --time-color bbbbbbff \
    --time-align 1 \
    --time-size 100 \
    --date-pos tx:ty+50 \
    --date-color bbbbbbff \
    --date-align 1 \
    --date-str "$date_format" \
    --date-size 30 \
    --ringver-color ffffff00 \
    --ringwrong-color ffffff88 \
    --noinput-text "$no_input_text" \
    --wrong-align 0 \
    --wrong-color ffffffff \
    --wrong-text  "$wrong_text" \
    --verif-text "$verify_text" \
    --verif-align 0 \
    --verif-color ffffffff \
    --modif-pos -50:-50