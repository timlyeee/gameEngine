#include "core/renderWindow/GLRenderWindow.h"

class Application {
    
    public:
        Application();
        ~Application();

        //update scene data like vertex or mesh
        updateScene();
        //use file utils etc.
        loadResources();
        

    private:
        RenderWindow renderWindow;
};