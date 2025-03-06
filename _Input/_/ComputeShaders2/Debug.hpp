#pragma once

namespace NComputeShaders2::NComputeShaders2
{
    inline struct SDebug
    {
        SDebug();
        void IAssert(bool const& ACondition = true , std::string const& AMessage = "" , std::source_location const& ALocation = std::source_location::current());
        void ISimpleDirectMediaLibrary(bool const& ACondition = true , std::source_location const& ALocation = std::source_location::current());
        void ICode(std::int32_t const& AValue , std::source_location const& ALocation = std::source_location::current());
        void IMask(std::int32_t const& AValue , std::source_location const& ALocation = std::source_location::current());
        void IHandle(void *const& AValue , std::source_location const& ALocation = std::source_location::current());
        void IOpenGraphicsLibrary(std::source_location const& ALocation = std::source_location::current());
        ~SDebug();
    }
    *GDebug;
}