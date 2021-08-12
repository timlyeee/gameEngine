
#include <stb_image.h>
#include <exception>
#include <functional>
#include <algorithm>
#include <vector>
#include <cassert>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <exception>
#include <functional>
#include <algorithm>
#include <vector>
#include <cassert>
#include "SDL_main.h"
#include "SDL_syswm.h"
#define INTERNAL_GLEW
#ifdef INTERNAL_GLEW
	#include <GLES3Wrangler.h>
	#include <gles3w.h>
#endif
#ifdef EXTERNAL_GLEW
	#include "GL/glew.h"
	#include <SDL_egl.h>
#endif
#include <SDL.h>

#include <learnopengl/shader_m.h>
#include <learnopengl/camera.h>
#include <learnopengl/model.h>

#include <iostream>

#define GL_CHECK(x)                                                            \
  do {                                                                         \
    x;                                                                         \
    GLenum err = glGetError();                                                 \
    if (err != GL_NO_ERROR) {                                                  \
      printf("%s returned GL error: 0x%x\n", #x, err);                         \
      __debugbreak();                                                          \
    }                                                                          \
  } while (0)
#define EGL_CHECK(x)                                                           \
  do {                                                                         \
    x;                                                                         \
    EGLint err = eglGetError();                                                \
    if (err != EGL_SUCCESS) {                                                  \
      printf("%s returned EGL error: 0x%x\n", #x, err);                        \
      __debugbreak();                                                          \
    }                                                                          \
  } while (0)

std::function<void()> loop;
void main_loop() { loop(); }

bool eglSetup(HWND window);

namespace {
    EGLContext eglContext;
    EGLDisplay eglDisplay;
    EGLSurface eglSurface;
    EGLConfig eglConfig;
    HDC nativeDisplay;
    uint32_t sampleBuffers;
    uint32_t sampleCount;
}

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = (float)SCR_WIDTH / 2.0;
float lastY = (float)SCR_HEIGHT / 2.0;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main(int argc, char** argv)
{
    

    // glfw: initialize and configure
    // ------------------------------
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        assert(false);
    }
    uint32_t flags = SDL_WINDOW_SHOWN |
        SDL_WINDOW_RESIZABLE |
        SDL_WINDOW_INPUT_FOCUS;

    //sdl create window
    auto wnd(SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, 640, 480,
		flags));
    //SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    //SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    
    HWND window;
    {
        SDL_SysWMinfo wmInfo;
        SDL_VERSION(&wmInfo.version);
        SDL_GetWindowWMInfo(wnd, &wmInfo);
        window = wmInfo.info.win.window;
    }
    
#ifdef INTERNAL_GLEW
	if (!gles3wInit()) {
		std::cout << "Init error";
		return -1;
	}
#endif
	//eglSetup
    eglSetup(window);
	//glewExperimental = GL_TRUE;
#ifdef EXTERNAL_GLEW
	if (glewInit() != GLEW_OK) {
		std::cout << "Init error";
		return -1;
	}
#endif
	glEnable(GL_DEPTH_TEST);


    
    // configure global opengl state
    // -----------------------------
    

    // build and compile shaders
    // -------------------------
    Shader shaderRed("E:\\Cases\\petitEngine\\include\\8.advanced_glsl.vs", "E:\\Cases\\petitEngine\\include\\8.red.fs");
    Shader shaderGreen("E:\\Cases\\petitEngine\\include\\8.advanced_glsl.vs", "E:\\Cases\\petitEngine\\include\\8.green.fs");
    Shader shaderBlue("E:\\Cases\\petitEngine\\include\\8.advanced_glsl.vs", "E:\\Cases\\petitEngine\\include\\8.blue.fs");
    Shader shaderYellow("E:\\Cases\\petitEngine\\include\\8.advanced_glsl.vs", "E:\\Cases\\petitEngine\\include\\8.yellow.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float cubeVertices[] = {
        // positions         
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
    };
    
    // cube VAO
    GLuint cubeVAO;
    GL_CHECK(glGenVertexArrays(1, &cubeVAO));
    GL_CHECK(glBindVertexArray(cubeVAO));

    // cube vbo
    GLuint cubeVBO;
    GL_CHECK(glGenBuffers(1, &cubeVBO));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, cubeVBO));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));

    // configure a uniform buffer object
    // ---------------------------------
    // first. We get the relevant block indices
    unsigned int uniformBlockIndexRed = glGetUniformBlockIndex(shaderRed.ID, "Matrices");
    unsigned int uniformBlockIndexGreen = glGetUniformBlockIndex(shaderGreen.ID, "Matrices");
    unsigned int uniformBlockIndexBlue = glGetUniformBlockIndex(shaderBlue.ID, "Matrices");
    unsigned int uniformBlockIndexYellow = glGetUniformBlockIndex(shaderYellow.ID, "Matrices");
    // then we link each shader's uniform block to this uniform binding point
    glUniformBlockBinding(shaderRed.ID, uniformBlockIndexRed, 0);
    glUniformBlockBinding(shaderGreen.ID, uniformBlockIndexGreen, 0);
    glUniformBlockBinding(shaderBlue.ID, uniformBlockIndexBlue, 0);
    glUniformBlockBinding(shaderYellow.ID, uniformBlockIndexYellow, 0);
    // Now actually create the buffer
    unsigned int uboMatrices;
    glGenBuffers(1, &uboMatrices);
    glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
    glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);

	glBindBuffer(GL_UNIFORM_BUFFER, 0);
    // define the range of the buffer that links to a uniform binding point
	GLint buffer_offset;
	glGetIntegerv(GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT, &buffer_offset);
	std::cout << "GLenum:" << sizeof(GLenum) << "GLUINT:" << sizeof(GLuint) << " GLUINTPTR:" << sizeof(GLintptr) << " GLsizeiptr:" << sizeof(GLsizeiptr);
    GL_CHECK(glBindBufferRange(GL_UNIFORM_BUFFER, 0, uboMatrices, static_cast< signed   long long int>( 0), static_cast< signed   long long int> (2 * sizeof(glm::mat4))));
	std::cout << "GLenum:" << sizeof(GLenum) << "GLUINT:" << sizeof(GLuint) << " GLUINTPTR:" << sizeof(GLintptr) << " GLsizeiptr:" << sizeof(GLsizeiptr);
    // store the projection matrix (we only do this once now) (note: we're not using zoom anymore by changing the FoV)
    glm::mat4 projection = glm::perspective(45.0f, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    // render loop
    // -----------

    loop = [&] {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                std::terminate();
        }

        // Clear the screen to black
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);


        // set the view and projection matrix in the uniform block - we only have to do this once per loop iteration.
        glm::mat4 view = camera.GetViewMatrix();
        glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
        glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
        glBindBuffer(GL_UNIFORM_BUFFER, 0);

        // draw 4 cubes 
        // RED
        glBindVertexArray(cubeVAO);
        try {
            shaderRed.use();
        }
        catch (exception e) {
            std::cout << "use shader failed";
            __debugbreak();
        }

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-0.75f, 0.75f, 0.0f)); // move top-left
        shaderRed.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        // GREEN
        shaderGreen.use();
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.75f, 0.75f, 0.0f)); // move top-right
        shaderGreen.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        // YELLOW
        shaderYellow.use();
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-0.75f, -0.75f, 0.0f)); // move bottom-left
        shaderYellow.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        // BLUE
        shaderBlue.use();
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.75f, -0.75f, 0.0f)); // move bottom-right
        shaderBlue.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);



        //SDL_GL_SwapWindow(wnd); 
        eglSwapBuffers(eglDisplay, eglSurface);
    };
    while (true)
        main_loop();
   
    return 0;
}


bool eglSetup(HWND windowHandle) {
    bool _vsyncMode = false;
    auto* window = reinterpret_cast<EGLNativeWindowType>(
        windowHandle); // NOLINT(performance-no-int-to-ptr)

	
		

    //////////////////////////////////////////////////////////////////////////


    nativeDisplay = GetDC(window);
    if (!nativeDisplay) {
        return false;
    }

    EGL_CHECK(eglDisplay = eglGetDisplay(nativeDisplay));
    if (eglDisplay == EGL_NO_DISPLAY) {
        EGL_CHECK(eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY));
    }

    // If a display still couldn't be obtained, return an error.
    if (eglDisplay == EGL_NO_DISPLAY) {
        printf("eglGetDisplay() - FAILED.");
        return false;
    }

    EGLint major = 3;
    EGLint minor = 0;
    if (eglInitialize(eglDisplay, &major, &minor) != EGL_TRUE) {
        printf("Couldn't initialize EGLDisplay.");
        return false;
    }

    //    Make OpenGL ES the current API.
    //    EGL needs a way to know that any subsequent EGL calls are going to be
    //    affecting OpenGL ES, rather than any other API (such as OpenVG).
    EGL_CHECK(eglBindAPI(EGL_OPENGL_ES_API));


    bool msaaEnabled = false;
    EGLint redSize{ 8 };
    EGLint greenSize{ 8 };
    EGLint blueSize{ 8 };
    EGLint alphaSize{ 8 };
    EGLint depthSize{ 24 };
    EGLint stencilSize{ 8 };
    EGLint sampleBufferSize{ msaaEnabled ? EGL_DONT_CARE : 0 };
    EGLint sampleSize{ msaaEnabled ? EGL_DONT_CARE : 0 };

    EGLint defaultAttribs[] = {
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT | EGL_PBUFFER_BIT, EGL_RENDERABLE_TYPE,
        EGL_OPENGL_ES2_BIT,
        // EGL_BUFFER_SIZE, colorBuffSize,
        EGL_BLUE_SIZE, blueSize, EGL_GREEN_SIZE, greenSize, EGL_RED_SIZE,
        redSize, EGL_ALPHA_SIZE, alphaSize, EGL_DEPTH_SIZE, depthSize,
        EGL_STENCIL_SIZE, stencilSize, EGL_SAMPLE_BUFFERS, sampleBufferSize,
        EGL_SAMPLES, sampleSize, EGL_NONE };

    int numConfig = 0;

    std::vector<EGLConfig> vecEGLConfig{};
    EGLConfig cfgs[128];

    EGL_CHECK(eglGetConfigs(eglDisplay, cfgs, 128, &numConfig));
    if (eglChooseConfig(eglDisplay, defaultAttribs, nullptr, 0, &numConfig)) {
        vecEGLConfig.resize(numConfig);
    }
    else {
        printf("Query configuration failed.");
        return false;
    }

    int count = numConfig;
    if (eglChooseConfig(eglDisplay, defaultAttribs, vecEGLConfig.data(),
        count, &numConfig) == EGL_FALSE ||
        !numConfig) {
        printf("eglChooseConfig configuration failed.");
        return false;
    }

    EGLint depth{ 0 };
    EGLint stencil{ 0 };
    const uint8_t attrNums = 8;
    EGLint params[attrNums] = { 0 };
    bool matched = false;
    const bool qualityPreferred = true;
    uint64_t lastScore = qualityPreferred
        ? (std::numeric_limits<uint64_t>::min)()
        : (std::numeric_limits<uint64_t>::max)();

    for (int i = 0; i < numConfig; i++) {
        int depthValue{ 0 };
        EGL_CHECK(eglGetConfigAttrib(eglDisplay, vecEGLConfig[i], EGL_RED_SIZE,
            &params[0]));
        EGL_CHECK(eglGetConfigAttrib(eglDisplay, vecEGLConfig[i], EGL_GREEN_SIZE,
            &params[1]));
        EGL_CHECK(eglGetConfigAttrib(eglDisplay, vecEGLConfig[i], EGL_BLUE_SIZE,
            &params[2]));
        EGL_CHECK(eglGetConfigAttrib(eglDisplay, vecEGLConfig[i], EGL_ALPHA_SIZE,
            &params[3]));
        EGL_CHECK(eglGetConfigAttrib(eglDisplay, vecEGLConfig[i], EGL_DEPTH_SIZE,
            &params[4]));
        EGL_CHECK(eglGetConfigAttrib(eglDisplay, vecEGLConfig[i], EGL_STENCIL_SIZE,
            &params[5]));
        EGL_CHECK(eglGetConfigAttrib(eglDisplay, vecEGLConfig[i], EGL_SAMPLE_BUFFERS,
            &params[6]));
        EGL_CHECK(eglGetConfigAttrib(eglDisplay, vecEGLConfig[i], EGL_SAMPLES,
            &params[7]));
        /*EGL_CHECK(eglGetConfigAttrib(eglDisplay, vecEGLConfig[i], EGL_DEPTH_ENCODING_NV,
            &depthValue));*/

        int bNonLinearDepth =
            (depthValue == EGL_DEPTH_ENCODING_NONLINEAR_NV) ? 1 : 0;

        /*------------------------------------------ANGLE's
         * priority-----------------------------------------------*/
         // Favor EGLConfigLists by RGB, then Depth, then Non-linear Depth, then
         // Stencil, then Alpha
        uint64_t currScore{ 0 };
        EGLint colorScore = std::abs(params[0] - redSize) +
            std::abs(params[1] - greenSize) +
            std::abs(params[2] - blueSize);
        currScore |= static_cast<uint64_t>((std::min)((std::max)(params[6], 0), 15))
            << 29;
        currScore |= static_cast<uint64_t>((std::min)((std::max)(params[7], 0), 31))
            << 24;
        currScore |= static_cast<uint64_t>((std::min)(colorScore, 127)) << 17;
        currScore |=
            static_cast<uint64_t>((std::min)(std::abs(params[4] - depthSize), 63))
            << 11;
        currScore |=
            static_cast<uint64_t>((std::min)(std::abs(1 - bNonLinearDepth), 1))
            << 10;
        currScore |=
            static_cast<uint64_t>((std::min)(std::abs(params[5] - stencilSize), 31))
            << 6;
        currScore |=
            static_cast<uint64_t>((std::min)(std::abs(params[3] - alphaSize), 31))
            << 0;
        /*------------------------------------------ANGLE's
         * priority-----------------------------------------------*/

         // if msaaEnabled, sampleBuffers and sampleCount should be greater than 0,
         // until iterate to the last one(can't find).
        bool msaaLimit = (msaaEnabled ? (params[6] > 0 && params[7] > 0)
            : (params[6] == 0 && params[7] == 0));
        // performancePreferred ? [>=] : [<] , egl configurations store in
        // "ascending order"
        bool filter = (currScore < lastScore) ^ qualityPreferred;
        if ((filter && msaaLimit) || (!matched && i == numConfig - 1)) {
            eglConfig = vecEGLConfig[i];
            depth = params[4];
            stencil = params[5];
            sampleBuffers = static_cast<uint8_t>(params[6]);
            sampleCount = static_cast<uint8_t>(params[7]);
            lastScore = currScore;
            matched = true;
        }
    }

    //    Find a suitable EGLConfig
    //    eglChooseConfig is provided by EGL to provide an easy way to select an
    //    appropriate configuration. It takes in the capabilities specified in
    //    the attribute list, and returns a list of available configurations
    //    that match or exceed the capabilities requested. Details of all the
    //    possible attributes and how they are selected for by this function are
    //    available in the EGL reference pages here:
    //    http://www.khronos.org/registry/egl/sdk/docs/man/xhtml/eglChooseConfig.html
    //    It is also possible to simply get the entire list of configurations
    //    and use a custom algorithm to choose a suitable one, as many advanced
    //    applications choose to do. For this application however, taking the
    //    first EGLConfig that the function returns suits its needs perfectly,
    //    so we limit it to returning a single EGLConfig.

    //if (depth == 16 && stencil == 0) {
    //  _depthStencilFmt = Format::D16;
    //} else if (depth == 16 && stencil == 8) {
    //  _depthStencilFmt = Format::D16S8;
    //} else if (depth == 24 && stencil == 0) {
    //  _depthStencilFmt = Format::D24;
    //} else if (depth == 24 && stencil == 8) {
    //  _depthStencilFmt = Format::D24S8;
    //} else if (depth == 32 && stencil == 0) {
    //  _depthStencilFmt = Format::D32F;
    //} else if (depth == 32 && stencil == 8) {
    //  _depthStencilFmt = Format::D32F_S8;
    //} else {
    //  printf("Unknown depth stencil format.");
    //  return false;
    //}


    /**
     * EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
     * guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
     * As soon as we picked a EGLConfig, we can safely reconfigure the
     * ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID.
     */


    EGL_CHECK(eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig,
        window, NULL));
    if (eglSurface == EGL_NO_SURFACE) {
        printf("Window surface created failed.");
        return false;
    }


    auto majorVersion = 3;
    auto minorVersion = 0;
    EGLint ctxAttribs[32];
    uint32_t n = 0;


    ctxAttribs[n++] = EGL_CONTEXT_CLIENT_VERSION;
    ctxAttribs[n++] = majorVersion;
    ctxAttribs[n] = EGL_NONE;

    EGL_CHECK(eglContext = eglCreateContext(eglDisplay, eglConfig, nullptr,
        ctxAttribs));
    if (!eglContext) {
        printf("Create EGL context failed.");
        return false;
    }

    EGL_CHECK(eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext));

	
    return true;
}
