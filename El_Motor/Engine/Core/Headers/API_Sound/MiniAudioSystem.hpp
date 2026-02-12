#pragma once

#include "API_Sound/IAudioSystem.hpp"

#include <string>
#include <unordered_map>

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

        SoundHandle LoadSound(const std::string& path, const SoundDesc& desc = {}) override;
        void UnloadSound(SoundHandle sound) override;

        VoiceHandle Play(SoundHandle sound, const VoiceParams& params = {}) override;
        void Stop(VoiceHandle voice) override;

        void SetMasterVolume(float volume) override;

    private:
        struct SoundRes
        {
            std::string path;
            SoundDesc desc;
        };

        struct VoiceInst
        {
            ma_sound* soundPtr; // Pointeur opaque (défini dans le .cpp)
        };

    private:
        ma_engine* engine_ = nullptr;

        float masterVolume_ = 1.0f;

        SoundHandle soundId_ = 0;
        VoiceHandle voiceId_ = 0;

        std::unordered_map<SoundHandle, SoundRes> sounds_;
        std::unordered_map<VoiceHandle, VoiceInst> voices_;
    };
}
