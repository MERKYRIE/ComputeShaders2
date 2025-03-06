#include"ComputeShaders2.hpp"

namespace NComputeShaders2::NComputeShaders2::NVideo
{
    SProgram::SProgram(std::unordered_map<std::string , std::shared_ptr<SShader>> const& AShaders)
    {
        FShaders = AShaders;
        FIdentifier = glCreateProgram();
        std::ranges::for_each(FShaders , [&](auto const& AShader){AShader.second->IAttach(this);});
        glLinkProgram(FIdentifier);
        std::int32_t LSuccess;
        glGetProgramiv(FIdentifier , GL_LINK_STATUS , &LSuccess);
        std::int32_t LLength;
        glGetProgramiv(FIdentifier , GL_INFO_LOG_LENGTH , &LLength);
        std::string LLog;
        LLog.resize(LLength);
        glGetProgramInfoLog(FIdentifier , LLength , nullptr , LLog.data());
        GDebug->IAssert(!LSuccess , "Open Graphics Library - " + LLog);
        GDebug->IOpenGraphicsLibrary();
    }

    void SProgram::IUse()
    {
        glUseProgram(FIdentifier);
    }

    SProgram::~SProgram()
    {
        FShaders.clear();
        glDeleteProgram(FIdentifier);
        GDebug->IOpenGraphicsLibrary();
    }
}