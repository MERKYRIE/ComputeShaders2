#include"ComputeShaders2.hpp"

namespace NComputeShaders2::NComputeShaders2::NVideo
{
    SUniform::SUniform(std::int32_t const& ALocation)
    {
        FLocation = ALocation;
    }

    void SUniform::ISpecify(glm::vec4 const& AVector)
    {
        glUniform4fv(FLocation , 1 , &AVector[0]);
    }

    void SUniform::ISpecify(glm::mat4 const& AMatrix)
    {
        glUniformMatrix4fv(FLocation , 1 , GL_FALSE , &AMatrix[0][0]);
    }
}