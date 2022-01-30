# About

From Learnopengl-cn
-----
libEGL和glew比较。

在glBindBufferRange方法的效果上，两者并不相同。
在sdlMain.cpp中修改宏为EXTERNAL_GLEW可使用开源库glew,修改宏为INTERNAL_GLEW可使用engine-native的gles3wrangler

此外需要修改cmake去改变engine native的路径


