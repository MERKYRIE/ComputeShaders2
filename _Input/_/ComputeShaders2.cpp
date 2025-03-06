#pragma comment(lib , "../SimpleDirectMediaLayer/SDL2")
#pragma comment(lib , "../SimpleDirectMediaLayer/SDL2main")

#define GLAD_GL_IMPLEMENTATION

#include"ComputeShaders2.hpp"

namespace NComputeShaders2
{
    SComputeShaders2::SComputeShaders2()
    {
        GComputeShaders2 = this;
        new NComputeShaders2::SDebug;
        NComputeShaders2::GDebug->ICode(SDL_Init(SDL_INIT_EVERYTHING));
        new NComputeShaders2::SVideo;
        new NComputeShaders2::SSpace;
    }

    void SComputeShaders2::IUpdate()
    {
        NComputeShaders2::GVideo->IUpdate();
        NComputeShaders2::GSpace->IUpdate();
        NComputeShaders2::GVideo->IUpdate();
        NComputeShaders2::GDebug->IOpenGraphicsLibrary();
        std::system("Pause");
    }

    SComputeShaders2::~SComputeShaders2()
    {
        delete NComputeShaders2::GSpace;
        delete NComputeShaders2::GVideo;
        SDL_Quit();
        delete NComputeShaders2::GDebug;
    }
}

std::int32_t main(std::int32_t , char**)
{
    new NComputeShaders2::SComputeShaders2;
    NComputeShaders2::GComputeShaders2->IUpdate();
    delete NComputeShaders2::GComputeShaders2;
    return(0);
}