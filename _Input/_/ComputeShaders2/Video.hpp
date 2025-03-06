#pragma once

namespace NComputeShaders2::NComputeShaders2
{
    inline struct SVideo
    {
        SDL_Window* FWindow;
        SDL_GLContext FContext;
        std::unordered_map<std::string , std::shared_ptr<NVideo::SProgram>> FPrograms;

        SVideo();
        void IUpdate();
        ~SVideo();
    }
    *GVideo;
}