#include"ComputeShaders2.hpp"

namespace NComputeShaders2::NComputeShaders2
{
    SVideo::SVideo()
    {
        GVideo = this;
        GDebug->ICode(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION , 4));
        GDebug->ICode(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION , 6));
        GDebug->ICode(SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK , SDL_GL_CONTEXT_PROFILE_CORE));
        GDebug->IHandle(FWindow = SDL_CreateWindow("ComputeShaders2" , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , 1280 , 720 , SDL_WINDOW_OPENGL));
        GDebug->IHandle(FContext = SDL_GL_CreateContext(FWindow));
        GDebug->ICode(SDL_GL_SetSwapInterval(0));
        GDebug->IAssert(gladLoadGL(reinterpret_cast<GLADloadfunc>(SDL_GL_GetProcAddress)) != 40006);
        FPrograms.emplace("Compute" , std::make_shared<NVideo::SProgram>(std::unordered_map<std::string , std::shared_ptr<NVideo::SShader>>{{"Compute" , std::make_shared<NVideo::SShader>("/Compute.ogl" , GL_COMPUTE_SHADER , std::unordered_map<std::string , std::shared_ptr<NVideo::SUniform>>{})}}));
        FPrograms.emplace
        (
            "Graphics" , std::make_shared<NVideo::SProgram>
            (
                std::unordered_map<std::string , std::shared_ptr<NVideo::SShader>>
                {
                    {
                        "Vertex" , std::make_shared<NVideo::SShader>
                        (
                            "/Vertex.ogl" , GL_VERTEX_SHADER , std::unordered_map<std::string , std::shared_ptr<NVideo::SUniform>>
                            {
                                {"Projection" , std::make_shared<NVideo::SUniform>(1)}
                                ,
                                {"View" , std::make_shared<NVideo::SUniform>(2)}
                                ,
                                {"Model" , std::make_shared<NVideo::SUniform>(3)}
                            }
                        )
                    }
                    ,
                    {
                        "Fragment" , std::make_shared<NVideo::SShader>
                        (
                            "/Fragment.ogl" , GL_FRAGMENT_SHADER , std::unordered_map<std::string , std::shared_ptr<NVideo::SUniform>>
                            {
                                {"Color" , std::make_shared<NVideo::SUniform>(4)}
                            }
                        )
                    }
                }
            )
        );
    }

    void SVideo::IUpdate()
    {
        SDL_GL_SwapWindow(FWindow);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    SVideo::~SVideo()
    {
        FPrograms.clear();
        SDL_GL_DeleteContext(FContext);
        SDL_DestroyWindow(FWindow);
    }
}