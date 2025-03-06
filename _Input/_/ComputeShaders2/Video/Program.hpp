#pragma once

namespace NComputeShaders2::NComputeShaders2::NVideo
{
    struct SProgram
    {
        std::uint32_t FIdentifier;
        std::unordered_map<std::string , std::shared_ptr<SShader>> FShaders;

        SProgram(std::unordered_map<std::string , std::shared_ptr<SShader>> const& AShaders);
        void IUse();
        ~SProgram();
    };
}