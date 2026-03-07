
#define MINIAUDIO_IMPLEMENTATION
#include "API_Sound/MiniAudioSystem.hpp"
#include <string>
#include <unordered_map>

namespace Engine
{
    bool MiniAudioSystem::Init()
    {
        engine_ = new ma_engine{};
        return ma_engine_init(nullptr, engine_) == MA_SUCCESS;
    }

    void MiniAudioSystem::Shutdown()
    {
        for (auto& [id, v] : voices_)
        {
            ma_sound_uninit(v.soundPtr);
            delete v.soundPtr;
        }

        voices_.clear();
        sounds_.clear();

        if (engine_)
        {
            ma_engine_uninit(engine_);
            delete engine_;
            engine_ = nullptr;
        }
    }

    void MiniAudioSystem::Update(float)
    {
        for (auto it = voices_.begin(); it != voices_.end(); )
        {
            if (ma_sound_at_end(it->second.soundPtr))
            {
                ma_sound_uninit(it->second.soundPtr);
                delete it->second.soundPtr;
                it = voices_.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }

    EI::SoundHandle MiniAudioSystem::LoadSound(const std::string& path, const EI::SoundDesc& desc)
    {
        EI::SoundHandle id = ++soundId_;
        sounds_[id] = SoundRes{ path, desc };
        return id;
    }

    void MiniAudioSystem::UnloadSound(EI::SoundHandle sound)
    {
        sounds_.erase(sound);
    }

    //EI::VoiceHandle MiniAudioSystem::Play(EI::SoundHandle sound, const EI::VoiceParams& params)
    //{
    //    auto it = sounds_.find(sound);
    //    if (it == sounds_.end())
    //        return 0;

    //    ma_uint32 flags = 0;

    //    if (it->second.desc.stream)
    //        flags |= MA_SOUND_FLAG_STREAM;

    //    if (it->second.desc.spatial)
    //        flags |= MA_SOUND_FLAG_SPATIALIZATION;

    //    auto* newSound = new ma_sound{};

    //    if (ma_sound_init_from_file(
    //        engine_,
    //        it->second.path.c_str(),
    //        flags,
    //        nullptr,
    //        nullptr,
    //        newSound) != MA_SUCCESS)
    //    {
    //        delete newSound;
    //        return 0;
    //    }

    //    ma_sound_set_volume(newSound, params.volume);
    //    ma_sound_set_pitch(newSound, params.pitch);
    //    ma_sound_set_pan(newSound, params.pan);
    //    ma_sound_set_looping(newSound, params.loop);

    //    if (ma_sound_start(newSound) != MA_SUCCESS)
    //    {
    //        ma_sound_uninit(newSound);
    //        delete newSound;
    //        return 0;
    //    }

    //    EI::VoiceHandle id = ++voiceId_;
    //    voices_[id] = VoiceInst{ newSound };

    //    return id;
    //}

    void MiniAudioSystem::Stop(EI::VoiceHandle voice)
    {
        auto it = voices_.find(voice);
        if (it == voices_.end())
            return;

        ma_sound_stop(it->second.soundPtr);
        ma_sound_uninit(it->second.soundPtr);
        delete it->second.soundPtr;

        voices_.erase(it);
    }

    void MiniAudioSystem::SetMasterVolume(float volume)
    {
        masterVolume_ = volume;

        if (engine_)
            ma_engine_set_volume(engine_, masterVolume_);
    }

}

std::unique_ptr<Engine::IAudioSystem> CreateMiniAudioSystem()
{
    return std::make_unique<Engine::MiniAudioSystem>();
}
