#pragma once

#include "API_Sound/IAudioSystem.hpp"
#include "API_Sound/AudioTypes.hpp"

#include <string>

namespace EI
{
    class SoundManager
    {
    public:
        SoundManager();
        ~SoundManager();

        bool Init();
        void Shutdown();
        void Update(float dt);

        SoundHandle LoadSound(const std::string& path, const SoundDesc& desc = {});
        void UnloadSound(SoundHandle sound);

        VoiceHandle Play(SoundHandle sound, const VoiceParams& params = {});
        void Stop(VoiceHandle voice);

        void SetMasterVolume(float volume);

    private:
        Engine::IAudioSystem* audioSystem_;
    };
}