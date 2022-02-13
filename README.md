# About

> 原先是做一次libEGL和glew比较所开的仓库，但是后续变成了测试自己架构能力的GL知识重温和进阶。

本仓库是根据[learnopengl](https://learnopengl-cn.github.io)知识依据而构建出来的小引擎仓库，来验证自己的理论知识的完备性。

## 环境搭建

### *Windows*

对于Windows平台使用opengl32的内置库，并且使用glew来调用extension，使用glfw创建窗口。所有的第三方库都已经内置在了external目录下，只需要正常运行build脚本就行。

### *Mac*

对于Mac平台使用OpenGL.framework, 有两种方法来调用第三方库，homebrew创建和引用以及使用内置下载的glew和glfw等第三方库，注：防止版本冲突所以内置external中的第三方库版本是固定的，且没有针对多个架构做适配。



