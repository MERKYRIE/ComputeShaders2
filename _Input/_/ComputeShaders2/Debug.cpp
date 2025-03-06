#include"ComputeShaders2.hpp"

namespace NComputeShaders2::NComputeShaders2
{
    SDebug::SDebug()
    {
        GDebug = this;
    }

    void SDebug::IAssert(bool const& ACondition , std::string const& AMessage , std::source_location const& ALocation)
    {
        if(ACondition)
        {
            std::string LMessage{std::string{} + "File - " + ALocation.file_name() + "\n" + "Function - " + ALocation.function_name() + "\n" + "Line - " + std::to_string(ALocation.line()) + "\n" + "Column - " + std::to_string(ALocation.column()) + (!AMessage.empty() ? "\n" + AMessage : "")};
            if(SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR , "Debug" , LMessage.data() , nullptr) < 0)
            {
                std::cout << "Debug:" << "\n" << LMessage << "\n\n";
            }
            std::exit(0);
        }
    }

    void SDebug::ISimpleDirectMediaLibrary(bool const& ACondition , std::source_location const& ALocation)
    {
        IAssert(ACondition , std::string{} + "Simple DirectMedia Layer - " + SDL_GetError() , ALocation);
    }

    void SDebug::ICode(std::int32_t const& AValue , std::source_location const& ALocation)
    {
        ISimpleDirectMediaLibrary(AValue < 0 , ALocation);
    }

    void SDebug::IMask(std::int32_t const& AValue , std::source_location const& ALocation)
    {
        ISimpleDirectMediaLibrary(!AValue , ALocation);
    }

    void SDebug::IHandle(void *const& AValue , std::source_location const& ALocation)
    {
        ISimpleDirectMediaLibrary(!AValue , ALocation);
    }

    void SDebug::IOpenGraphicsLibrary(std::source_location const& ALocation)
    {
        std::uint32_t LCode{glGetError()};
        IAssert(LCode , std::string{} + "Open Graphics Library - " + std::to_string(LCode) , ALocation);
    }

    SDebug::~SDebug()
    {
    
    }
}