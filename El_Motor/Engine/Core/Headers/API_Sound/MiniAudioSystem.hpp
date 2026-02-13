#pragma once
#include "miniaudio/miniaudio.h"
#include "API_Sound/IAudioSystem.hpp"
#include "API_Sound/AudioTypes.hpp"

// Forward declaration miniaudio
struct ma_engine;
struct ma_sound;

namespace Engine
{
    class MiniAudioSystem final : public IAudioSystem
    {
    public:
        MiniAudioSystem() = default;
        ~MiniAudioSystem() override = default;

        bool Init() override;
        void Shutdown() override;
        void Update(float deltaTime) override;

        EI::SoundHandle LoadSound(const std::string& path, const EI::SoundDesc& desc = {}) override;
        void UnloadSound(EI::SoundHandle sound) override;

        EI::VoiceHandle Play(EI::SoundHandle sound, const EI::VoiceParams& params = {}) override;
        void Stop(EI::VoiceHandle voice) override;

        void SetMasterVolume(float volume) override;

    private:
        struct SoundRes
        {
            std::string path;
            EI::SoundDesc desc;
        };

        struct VoiceInst
        {
            ma_sound* soundPtr; // Pointeur opaque (défini dans le .cpp)
        };

    private:
        ma_engine* engine_ = nullptr;

        float masterVolume_ = 1.0f;

        EI::SoundHandle soundId_ = 0;
        EI::VoiceHandle voiceId_ = 0;

        std::unordered_map<EI::SoundHandle, SoundRes> sounds_;
        std::unordered_map<EI::VoiceHandle, VoiceInst> voices_;
    };
}
