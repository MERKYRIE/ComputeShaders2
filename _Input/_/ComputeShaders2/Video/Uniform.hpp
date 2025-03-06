#pragma once

namespace NComputeShaders2::NComputeShaders2::NVideo
{
    struct SUniform
    {
        std::int32_t FLocation;

        SUniform(std::int32_t const& ALocation);
        void ISpecify(glm::vec4 const& AVector);
        void ISpecify(glm::mat4 const& AMatrix);
    };
}