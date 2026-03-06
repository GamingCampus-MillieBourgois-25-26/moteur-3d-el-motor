#include "Sound_manager/Sound_manager.hpp"
#include "API_Sound/MiniAudioSystem.hpp"

namespace EI
{
    SoundManager::SoundManager()
        : audioSystem_(nullptr)
    {
    }

    SoundManager::~SoundManager()
    {
        Shutdown();
    }

    bool SoundManager::Init()
    {
        if (!audioSystem_)
            audioSystem_ = CreateMiniAudioSystem();

        if (!audioSystem_)
            return false;

        return audioSystem_->Init();
    }

    void SoundManager::Shutdown()
    {
        if (!audioSystem_)
            return;

        audioSystem_->Shutdown();
        delete audioSystem_;
        audioSystem_ = nullptr;
    }

    void SoundManager::Update(float dt)
    {
        if (!audioSystem_)
            return;

        audioSystem_->Update(dt);
    }

    SoundHandle SoundManager::LoadSound(const std::string& path, const SoundDesc& desc)
    {
        if (!audioSystem_)
            return 0;

        return audioSystem_->LoadSound(path, desc);
    }

    void SoundManager::UnloadSound(SoundHandle sound)
    {
        if (!audioSystem_)
            return;

        audioSystem_->UnloadSound(sound);
    }

    VoiceHandle SoundManager::Play(SoundHandle sound, const VoiceParams& params)
    {
        if (!audioSystem_)
            return 0;

        return audioSystem_->Play(sound, params);
    }

    void SoundManager::Stop(VoiceHandle voice)
    {
        if (!audioSystem_)
            return;

        audioSystem_->Stop(voice);
    }

    void SoundManager::SetMasterVolume(float volume)
    {
        if (!audioSystem_)
            return;

        audioSystem_->SetMasterVolume(volume);
    }
}