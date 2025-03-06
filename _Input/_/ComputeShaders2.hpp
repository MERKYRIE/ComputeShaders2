#pragma once

#include<array>
#include<filesystem>
#include<fstream>
#include<iostream>
#include<numbers>
#include<random>
#include<source_location>
#include<string>
#include<unordered_map>
#include<vector>

#pragma warning(push)
    #pragma warning(disable : 4551 6001 26819)

    #include"../GraphicsLibraryAddress/gl.h"
    #include"../SimpleDirectMediaLayer/SDL.h"
    #include"../GraphicsLibraryMathematics/glm.hpp"
    #include"../GraphicsLibraryMathematics/gtc/matrix_transform.hpp"
    #include"../GraphicsLibraryMathematics/gtc/type_ptr.hpp"
#pragma warning(pop)

namespace NComputeShaders2
{
    inline struct SComputeShaders2
    {
        SComputeShaders2();
        void IUpdate();
        ~SComputeShaders2();
    }
    *GComputeShaders2;
    
    namespace NComputeShaders2
    {
        struct SDebug;
        struct SSpace;
        struct SVideo;

        namespace NVideo
        {
            struct SProgram;
            struct SShader;
            struct SUniform;
        }
    }
}

#include"ComputeShaders2/Debug.hpp"
#include"ComputeShaders2/Space.hpp"
#include"ComputeShaders2/Video.hpp"
#include"ComputeShaders2/Video/Program.hpp"
#include"ComputeShaders2/Video/Shader.hpp"
#include"ComputeShaders2/Video/Uniform.hpp"