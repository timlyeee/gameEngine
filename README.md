# README

## What is learnopengl_to_renderpipeline
### A tiny render pipeline by transforming knowledges from [learnopengl](https://learnopengl-cn.github.io).


## Setup

### *Windows*

`Visual Studio` and `CMake` Should be installed. This project relies on the compile toolchain of Visual Studio. 

Run build.sh on gitbash or powershell, it will trigger cmake compilation. Also, you can modify it by yourself. Compilation options are listed by running `build.sh --help`

Or you can run `cmake . -B out ${BUILD_DIR}` on cmd. Basic knowledge of cmake is nessacary.
### *Mac*

`XCode` and `CMake` should be installed. Run build.sh to build as well as Windows.

## Principle idea

As a tiny render pipeline to run, a simple main function that support us to change from different scene, and handle inputs, is nessacary. Easy to use is what we want, so here shows the propal code in C++.
```c++
int main(){
    LoadEnvironment();

    //main loop, include input logic and render logic
    while(true){
        
        HandleInput();
        
        if(NeedUpdateRenderPipeline)
        {
            LoadingModels();
            LoadingShaders();
            LoadingScripts();
            UpdateRenderPipeline();
        }

        Render();
    }

}
```

So what you will see in this project, or tutariol, is a different way to learn achieve the goal of learnopengl, but a good framework.