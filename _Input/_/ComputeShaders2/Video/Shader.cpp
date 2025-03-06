#include"ComputeShaders2.hpp"

namespace NComputeShaders2::NComputeShaders2::NVideo
{
    SShader::SShader(std::string const& APath , std::uint32_t const& AType , std::unordered_map<std::string , std::shared_ptr<SUniform>> const& AUniforms)
    {
        FUniforms = AUniforms;
        std::fstream LFile{"Shaders" + APath , std::ios::in};
        FIdentifier = glCreateShader(AType);
        std::stringstream LStream;
        LStream << LFile.rdbuf();
        std::string LString{LStream.str()};
        char* LArray{LString.data()};
        glShaderSource(FIdentifier , 1 , &LArray , nullptr);
        glCompileShader(FIdentifier);
        std::int32_t LSuccess;
        glGetShaderiv(FIdentifier , GL_COMPILE_STATUS , &LSuccess);
        std::int32_t LLength;
        glGetShaderiv(FIdentifier , GL_INFO_LOG_LENGTH , &LLength);
        std::string LLog;
        LLog.resize(LLength);
        glGetShaderInfoLog(FIdentifier , LLength , nullptr , LLog.data());
        GDebug->IAssert(!LSuccess , "Open Graphics Library - " + LLog);
        GDebug->IOpenGraphicsLibrary();
    }

    void SShader::IAttach(SProgram *const& AProgram)
    {
        glAttachShader(AProgram->FIdentifier , FIdentifier);
    }

    SShader::~SShader()
    {
        glDeleteShader(FIdentifier);
        GDebug->IOpenGraphicsLibrary();
    }
}