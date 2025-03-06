#pragma once

namespace NComputeShaders2::NComputeShaders2::NVideo
{
    struct SShader
    {
        std::uint32_t FIdentifier;
        std::unordered_map<std::string , std::shared_ptr<SUniform>> FUniforms;

        SShader(std::string const& APath , std::uint32_t const& AType , std::unordered_map<std::string , std::shared_ptr<SUniform>> const& AUniforms);
        void IAttach(SProgram *const& AProgram);
        ~SShader();
    };
}