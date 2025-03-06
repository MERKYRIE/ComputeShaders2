#include"ComputeShaders2.hpp"

namespace NComputeShaders2::NComputeShaders2
{
    SSpace::SSpace()
    {
        GSpace = this;
    }

    void SSpace::IUpdate()
    {
        std::vector<float> LVertices
        {
            -0.5F , -0.5F , 0.0F
            ,
            -0.5F , +0.5F , 0.0F
            ,
            +0.5F , +0.5F , 0.0F
            ,
            +0.5F , -0.5F , 0.0F
        };
        GVideo->FPrograms["Compute"]->IUse();
        std::uint32_t LInputBufferObject;
        glGenBuffers(1 , &LInputBufferObject);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER , LInputBufferObject);
        glBufferData(GL_SHADER_STORAGE_BUFFER , std::ssize(LVertices) * sizeof(decltype(LVertices)::value_type) , LVertices.data() , GL_STATIC_READ);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER , 0 , LInputBufferObject);
        std::vector<std::int32_t> LIndices;
        LIndices.resize(std::ssize(LVertices) / 12);
        glDispatchCompute(static_cast<std::uint32_t>(std::ssize(LIndices)) , 1 , 1);
        glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
        glDeleteBuffers(1 , &LInputBufferObject);
        std::uint32_t LOutputBufferObject;
        glGenBuffers(1 , &LOutputBufferObject);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER , LOutputBufferObject);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER , 1 , LOutputBufferObject);
        auto LPointer{static_cast<decltype(LVertices)::pointer>(glMapBufferRange(GL_SHADER_STORAGE_BUFFER , 0 , std::ssize(LIndices) * sizeof(decltype(LIndices)::value_type) , GL_MAP_READ_BIT))};
        for(std::int64_t LIndex{0} ; LIndex < std::ssize(LIndices) ; LIndex++)
        {
            std::cout << LPointer[LIndex] << " ";
        }
        std::cout << "\n";
        glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
        glDeleteBuffers(1 , &LOutputBufferObject);
        GVideo->FPrograms["Graphics"]->IUse();
        glEnable(GL_DEPTH_TEST);
        glm::mat4 LProjection{glm::perspective(glm::radians(90.0F) , 16.0F / 9.0F , 0.0625F , 1'000.0F)};
        GVideo->FPrograms["Graphics"]->FShaders["Vertex"]->FUniforms["Projection"]->ISpecify(LProjection);
        glm::mat4 LView{1.0F};
        LView = glm::translate(LView , -glm::vec3{0.0F , 0.0F , 1.0F});
        GVideo->FPrograms["Graphics"]->FShaders["Vertex"]->FUniforms["View"]->ISpecify(LView);
        glm::mat4 LModel{1.0F};
        GVideo->FPrograms["Graphics"]->FShaders["Vertex"]->FUniforms["Model"]->ISpecify(LModel);
        glm::vec4 LColor{0.0F , 0.5F , 0.5F , 1.0F};
        GVideo->FPrograms["Graphics"]->FShaders["Fragment"]->FUniforms["Color"]->ISpecify(LColor);
        std::vector<std::uint32_t> LElements{0 , 1 , 2 , 3};
        std::uint32_t LVertexArrayObject;
        glGenVertexArrays(1 , &LVertexArrayObject);
        glBindVertexArray(LVertexArrayObject);
        std::uint32_t LVertexBufferObject;
        glGenBuffers(1 , &LVertexBufferObject);
        glBindBuffer(GL_ARRAY_BUFFER , LVertexBufferObject);
        glBufferData(GL_ARRAY_BUFFER , std::ssize(LVertices) * sizeof(decltype(LVertices)::value_type) , LVertices.data() , GL_STATIC_DRAW);
        std::uint32_t LElementBufferObject;
        glGenBuffers(1 , &LElementBufferObject);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER , LElementBufferObject);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER , sizeof(LElements) , LElements.data() , GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0 , 3 , GL_FLOAT , GL_FALSE , 3 * sizeof(float) , nullptr);
        glDrawElements(GL_LINE_LOOP , std::ssize(LElements) * sizeof(decltype(LElements)::value_type) , GL_UNSIGNED_INT , nullptr);
        glDeleteBuffers(1 , &LElementBufferObject);
        glDeleteBuffers(1 , &LVertexBufferObject);
        glDeleteVertexArrays(1 , &LVertexBufferObject);
    }

    SSpace::~SSpace()
    {
        
    }
}