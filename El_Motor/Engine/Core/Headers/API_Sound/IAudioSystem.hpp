#pragma once
#include <string>
#include <unordered_map>
#include "API_Sound/AudioTypes.hpp"


namespace Engine
{
    class IAudioSystem
    {
    public:
        virtual ~IAudioSystem() = default;

        // Cycle de vie
        virtual bool Init() = 0;
        virtual void Shutdown() = 0;
        virtual void Update(float dt) = 0;

        // Ressources
        virtual EI::SoundHandle LoadSound(const std::string& path, const EI::SoundDesc& desc = {}) = 0;
        virtual void UnloadSound(EI::SoundHandle sound) = 0;

        // Lecture
        virtual EI::VoiceHandle Play(EI::SoundHandle sound, const EI::VoiceParams& params = {}) = 0;
        virtual void Stop(EI::VoiceHandle voice) = 0;

        // Volume global
        virtual void SetMasterVolume(float volume) = 0;
    };
}
