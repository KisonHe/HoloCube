## 安装lvgl字体与图片工具
```bash
npm i lv_font_conv 
npm i lv_img_conv
```
[Download](https://github.com/googlefonts/noto-cjk/raw/main/Sans/Mono/NotoSansMonoCJKsc-Regular.otf)


## ESP32 能力
OK,在`lvgl/src/core/lv_refr.c`的`lv_label_set_text_fmt(perf_label, "%"LV_PRIu32" FPS\n%"LV_PRIu32"%% CPU", fps, cpu);`后面添加hook,使用假的disp flush（立刻报告成功）后发现fps还是只有大约11帧，未知原因为什么这么慢。需要进一步研究或者~~更换Linux~~

## OTA
参考 
1. https://docs.platformio.org/en/latest/platforms/espressif32.html#over-the-air-ota-update
2. https://github.com/platformio/bintray-secure-ota

2的这个repo基本就是想做的了（

有空了仔细看一下，看是否能用github actions自动化掉

我草，pio真牛逼，test也还没有看