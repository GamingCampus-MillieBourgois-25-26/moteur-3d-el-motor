#include "API_Sound/IAudioSystem.h"

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio/miniaudio.h"

#include <unordered_map>

namespace EI
{
    class MiniAudioSystem final : public IAudioSystem
    {
    public:
        bool Init() override
        {
            return ma_engine_init(nullptr, &engine_) == MA_SUCCESS;
        }

        void Shutdown() override
        {
            for (auto& [id, v] : voices_)
                ma_sound_uninit(&v.sound);
            voices_.clear();

            sounds_.clear();
            ma_engine_uninit(&engine_);
        }

        void Update(float) override
        {
            for (auto it = voices_.begin(); it != voices_.end(); )
            {
                if (ma_sound_at_end(&it->second.sound))
                {
                    ma_sound_uninit(&it->second.sound);
                    it = voices_.erase(it);
                }
                else
                    ++it;
            }
        }

        SoundHandle LoadSound(const std::string& path, const SoundDesc& desc = {}) override
        {
            SoundHandle id = ++soundId_;
            sounds_[id] = SoundRes{ path, desc };
            return id;
        }

        void UnloadSound(SoundHandle sound) override
        {
            sounds_.erase(sound);
        }

        VoiceHandle Play(SoundHandle sound, const VoiceParams& params = {}) override
        {
            auto it = sounds_.find(sound);
            if (it == sounds_.end())
                return 0;

            VoiceHandle id = ++voiceId_;
            VoiceInst v{};

            ma_uint32 flags = 0;
            if (it->second.desc.stream)
                flags |= MA_SOUND_FLAG_STREAM;

            if (it->second.desc.spatial)
                flags |= MA_SOUND_FLAG_SPATIALIZATION;

            if (ma_sound_init_from_file(&engine_, it->second.path.c_str(), flags, nullptr, nullptr, &v.sound) != MA_SUCCESS)
                return 0;

            ma_sound_set_volume(&v.sound, params.volume);
            ma_sound_set_pitch(&v.sound, params.pitch);
            ma_sound_set_pan(&v.sound, params.pan);
            ma_sound_set_looping(&v.sound, params.loop);

            if (ma_sound_start(&v.sound) != MA_SUCCESS)
            {
                ma_sound_uninit(&v.sound);
                return 0;
            }

            voices_[id] = std::move(v);
            return id;
        }

        void Stop(VoiceHandle voice) override
        {
            auto it = voices_.find(voice);
            if (it == voices_.end())
                return;

            ma_sound_stop(&it->second.sound);
            ma_sound_uninit(&it->second.sound);
            voices_.erase(it);
        }

        void SetMasterVolume(float volume) override
        {
            ma_engine_set_volume(&engine_, volume);
        }

    private:
        struct SoundRes
        {
            std::string path;
            SoundDesc desc;
        };

        struct VoiceInst
        {
            ma_sound sound{};
        };

        ma_engine engine_{};

        float masterVolume_ = 1.0f;

        SoundHandle soundId_ = 0;
        VoiceHandle voiceId_ = 0;

        std::unordered_map<SoundHandle, SoundRes> sounds_;
        std::unordered_map<VoiceHandle, VoiceInst> voices_;
    };
}
