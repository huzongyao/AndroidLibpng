# AndroidLibpng
A Project To Study how to parse png with libpng api and build app with NDK.

[![Travis](https://img.shields.io/appveyor/ci/gruntjs/grunt.svg)](https://github.com/huzongyao/AndroidLibpng)
[![Travis](https://img.shields.io/badge/libpng-v1.6.37-brightgreen.svg)](https://sourceforge.net/projects/libpng/files/)

#### Screenshot
![screenshot](https://github.com/huzongyao/AndroidLibpng/blob/master/misc/screen.png?raw=true)

### Introduction
is an open source project to develop and maintain the reference library for use in applications that read, create, 
and manipulate PNG (Portable Network Graphics) raster image files.

* Official Document: http://png-mng.sourceforge.net/pub/png/libpng.html
* Android itself support varies media format decode/encode, so this project is useless but for study libpng.
* libpng depends on zlib, I just use the ndk provided zlib instead of the source code.
* libpng for ARM support RTTI, just add APP_CPPFLAGS := -frtti to enable it.
* Simplied API for libpng is easy to use:
``` c
macros:
    PNG_FORMAT_*
    PNG_IMAGE_*
structures:
    png_control
    png_image
read functions
    png_image_begin_read_from_file()
    png_image_begin_read_from_stdio()
    png_image_begin_read_from_memory()
    png_image_finish_read()
    png_image_free()
write functions
    png_image_write_to_file()
    png_image_write_to_memory()
    png_image_write_to_stdio()
```

* I just need two functions to read png from memory:
``` c
png_image_begin_read_from_memory();
png_image_finish_read();
```

* Libpng support different kinds of color format(PNG_FORMAT_BGRA just fit android Bitmap.Config.ARGB_8888 int buffer model):
``` c
#define PNG_FORMAT_GRAY 0
#define PNG_FORMAT_GA   PNG_FORMAT_FLAG_ALPHA
#define PNG_FORMAT_AG   (PNG_FORMAT_GA|PNG_FORMAT_FLAG_AFIRST)
#define PNG_FORMAT_RGB  PNG_FORMAT_FLAG_COLOR
#define PNG_FORMAT_BGR  (PNG_FORMAT_FLAG_COLOR|PNG_FORMAT_FLAG_BGR)
#define PNG_FORMAT_RGBA (PNG_FORMAT_RGB|PNG_FORMAT_FLAG_ALPHA)
#define PNG_FORMAT_ARGB (PNG_FORMAT_RGBA|PNG_FORMAT_FLAG_AFIRST)
#define PNG_FORMAT_BGRA (PNG_FORMAT_BGR|PNG_FORMAT_FLAG_ALPHA)
#define PNG_FORMAT_ABGR (PNG_FORMAT_BGRA|PNG_FORMAT_FLAG_AFIRST)
```

#### 相关信息
* 网站：https://libpng.sourceforge.io/

### About Me
 * GitHub: [https://huzongyao.github.io/](https://huzongyao.github.io/)
 * ITEye博客：[http://hzy3774.iteye.com/](http://hzy3774.iteye.com/)
 * 新浪微博: [http://weibo.com/hzy3774](http://weibo.com/hzy3774)

### Contact To Me
 * QQ: [377406997](http://wpa.qq.com/msgrd?v=3&uin=377406997&site=qq&menu=yes)
 * Gmail: [hzy3774@gmail.com](mailto:hzy3774@gmail.com)
 * Foxmail: [hzy3774@qq.com](mailto:hzy3774@qq.com)
 * WeChat: hzy3774

 ![image](https://raw.githubusercontent.com/hzy3774/AndroidP7zip/master/misc/wechat.png)
