#include"ComputeShaders2.hpp"

namespace NComputeShaders2::NComputeShaders2
{
    SSpace::SSpace()
    {
        GSpace = this;
    }

    void SSpace::IUpdate()
    {
        std::uint32_t LBufferObject;
        glGenBuffers(1 , &LBufferObject);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER , LBufferObject);
        std::vector<glm::f32vec3> LVertices
        {
            {0.5F , 0.25F , 0.0F}
            ,
            {1.25F , 0.25F , 0.0F}
            ,
            {0.25F , 1.25F , 0.0F}
            ,
            {1.25F , 1.5F , 0.0F}
        };
        glBufferData(GL_SHADER_STORAGE_BUFFER , std::ssize(LVertices) * sizeof(decltype(LVertices)::value_type) , LVertices.data() , GL_STATIC_READ);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER , 0 , LBufferObject);
        GVideo->FPrograms["Compute"]->IUse();
        glDispatchCompute(static_cast<std::uint32_t>(std::ssize(LVertices) * 3) , 1 , 1);
        glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
        std::vector<glm::i32vec3> LPartitions{LVertices.size()};
        auto LPointer{static_cast<decltype(LPartitions)::pointer>(glMapBufferRange(GL_SHADER_STORAGE_BUFFER , 0 , std::ssize(LPartitions) * sizeof(decltype(LPartitions)::value_type) , GL_MAP_READ_BIT))};
        for(std::int64_t LPartition{0} ; LPartition < std::ssize(LPartitions) ; LPartition++)
        {
            LPartitions[LPartition] = LPointer[LPartition];
        }
        std::cout << "\n";
        glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
        glDeleteBuffers(1 , &LBufferObject);

        GVideo->FPrograms["Graphics"]->IUse();
        glDisable(GL_DEPTH_TEST);

        GVideo->FPrograms["Graphics"]->FShaders["Vertex"]->FUniforms["Projection"]->ISpecify(glm::perspective(glm::radians(90.0F) , 16.0F / 9.0F , 0.0625F , 1'000.0F));
        GVideo->FPrograms["Graphics"]->FShaders["Vertex"]->FUniforms["View"]->ISpecify(glm::translate(glm::mat4{1.0F} , -glm::vec3{0.0F , 0.0F , 2.0F}));
        GVideo->FPrograms["Graphics"]->FShaders["Vertex"]->FUniforms["Model"]->ISpecify(glm::mat4{1.0F});

        std::uint32_t LVertexArrayObject;
        glGenVertexArrays(1 , &LVertexArrayObject);
        glBindVertexArray(LVertexArrayObject);

        std::uint32_t LVertexBufferObject;
        glGenBuffers(1 , &LVertexBufferObject);
        glBindBuffer(GL_ARRAY_BUFFER , LVertexBufferObject);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0 , 3 , GL_FLOAT , GL_FALSE , 3 * sizeof(float) , nullptr);

        std::vector<glm::f32vec3> LSegments
        {
            {0.0F , 0.0F , 0.0F}
            ,
            {1.0F , 0.0F , 0.0F}
            ,
            {0.0F , 0.0F , 0.0F}
            ,
            {0.0F , 1.0F , 0.0F}
            ,
            {1.0F , 1.0F , 0.0F}
            ,
            {1.0F , 0.0F , 0.0F}
            ,
            {1.0F , 1.0F , 0.0F}
            ,
            {0.0F , 1.0F , 0.0F}
            ,
            {1.0F , 1.0F , 0.0F}
            ,
            {2.0F , 1.0F , 0.0F}
            ,
            {1.0F , 1.0F , 0.0F}
            ,
            {1.0F , 2.0F , 0.0F}
            ,
            {2.0F , 2.0F , 0.0F}
            ,
            {2.0F , 1.0F , 0.0F}
            ,
            {2.0F , 2.0F , 0.0F}
            ,
            {1.0F , 2.0F , 0.0F}
            ,
            {1.0F , 0.0F , 0.0F}
            ,
            {2.0F , 0.0F , 0.0F}
            ,
            {1.0F , 0.0F , 0.0F}
            ,
            {1.0F , 1.0F , 0.0F}
            ,
            {2.0F , 1.0F , 0.0F}
            ,
            {2.0F , 0.0F , 0.0F}
            ,
            {2.0F , 1.0F , 0.0F}
            ,
            {1.0F , 1.0F , 0.0F}
            ,
            {0.0F , 1.0F , 0.0F}
            ,
            {1.0F , 1.0F , 0.0F}
            ,
            {0.0F , 1.0F , 0.0F}
            ,
            {0.0F , 2.0F , 0.0F}
            ,
            {1.0F , 2.0F , 0.0F}
            ,
            {1.0F , 1.0F , 0.0F}
            ,
            {1.0F , 2.0F , 0.0F}
            ,
            {0.0F , 2.0F , 0.0F}
        };
        glBufferData(GL_ARRAY_BUFFER , std::ssize(LSegments) * sizeof(decltype(LSegments)::value_type) , LSegments.data() , GL_STATIC_DRAW);
        GVideo->FPrograms["Graphics"]->FShaders["Fragment"]->FUniforms["Color"]->ISpecify({0.0F , 0.0F , 1.0F , 1.0F});
        glDrawArrays(GL_LINES , 0 , static_cast<std::int32_t>(std::ssize(LSegments)));

        std::vector<glm::f32vec3> LPaths;
        for(std::int64_t LPath{0} ; LPath < std::ssize(LVertices) ; LPath++)
        {
            LPaths.emplace_back(LVertices[LPath]);
            LPaths.emplace_back(LPartitions[LPath]);
        }
        glBufferData(GL_ARRAY_BUFFER , std::ssize(LPaths) * sizeof(decltype(LPaths)::value_type) , LPaths.data() , GL_STATIC_DRAW);
        GVideo->FPrograms["Graphics"]->FShaders["Fragment"]->FUniforms["Color"]->ISpecify({0.0F , 1.0F , 0.0F , 1.0F});
        glDrawArrays(GL_LINES , 0 , static_cast<std::int32_t>(std::ssize(LPaths)));

        glDeleteBuffers(1 , &LVertexBufferObject);

        glDeleteVertexArrays(1 , &LVertexBufferObject);
    }

    SSpace::~SSpace()
    {
        
    }
}