#pragma once
#include "miniaudio/miniaudio.h"
#include "API_Sound/IAudioSystem.hpp"
#include "API_Sound/AudioTypes.hpp"

#include <memory>
#include <unordered_map>
#include <string>

// Forward declarations from miniaudio
struct ma_engine;
struct ma_sound;

namespace Engine
{
    /// <summary>
    /// Audio system implementation using MiniAudio.
    /// Handles loading, playing, and managing audio resources
    /// in the engine. Implements the IAudioSystem interface.
    /// </summary>
    class MiniAudioSystem final : public IAudioSystem
    {
    public:

        /// <summary>
        /// Default constructor
        /// </summary>
        MiniAudioSystem() = default;

        /// <summary>
        /// Destructor
        /// </summary>
        ~MiniAudioSystem() override = default;

        // =========================
        // Lifecycle
        // =========================

        /// <summary>
        /// Initializes the MiniAudio engine.
        /// </summary>
        /// <returns>True if initialization succeeded</returns>
        bool Init() override;

        /// <summary>
        /// Shuts down the MiniAudio engine and frees all resources.
        /// </summary>
        void Shutdown() override;

        /// <summary>
        /// Updates the MiniAudio engine (streaming, spatialization, etc.).
        /// </summary>
        /// <param name="deltaTime">Time elapsed since last frame</param>
        void Update(float deltaTime) override;

        // =========================
        // Resource management
        // =========================

        /// <summary>
        /// Loads a sound file into the audio system.
        /// </summary>
        /// <param name="path">Path to the audio file</param>
        /// <param name="desc">Sound description (streaming, spatial, etc.)</param>
        /// <returns>Handle referencing the loaded sound</returns>
        EI::SoundHandle LoadSound(const std::string& path, const EI::SoundDesc& desc = {}) override;

        /// <summary>
        /// Unloads a previously loaded sound resource.
        /// </summary>
        /// <param name="sound">Handle of the sound to unload</param>
        void UnloadSound(EI::SoundHandle sound) override;

        // =========================
        // Playback control
        // =========================

        /// <summary>
        /// Plays a sound with the specified parameters.
        /// </summary>
        /// <param name="sound">Sound handle to play</param>
        /// <param name="params">Playback parameters (volume, pitch, loop, pan)</param>
        /// <returns>Handle of the active sound instance (voice)</returns>
        EI::VoiceHandle Play(EI::SoundHandle sound, const EI::VoiceParams& params = {}) override;

        /// <summary>
        /// Stops a currently playing sound instance.
        /// </summary>
        /// <param name="voice">Voice handle to stop</param>
        void Stop(EI::VoiceHandle voice) override;

        // =========================
        // Global control
        // =========================

        /// <summary>
        /// Sets the global master volume for all sounds.
        /// </summary>
        /// <param name="volume">Volume value (0..1+)</param>
        void SetMasterVolume(float volume) override;


    private:

        /// <summary>
        /// Structure representing a loaded sound resource.
        /// </summary>
        struct SoundRes
        {
            std::string path;     // Path to the sound file
            EI::SoundDesc desc;   // Sound description (stream/spatial)
        };

        /// <summary>
        /// Structure representing an active sound instance (voice).
        /// </summary>
        struct VoiceInst
        {
            ma_sound* soundPtr;   // Opaque pointer to MiniAudio sound
        };

    private:

        /// <summary>
        /// Pointer to the MiniAudio engine instance
        /// </summary>
        ma_engine* engine_ = nullptr;

        /// <summary>
        /// Master volume applied to all sounds
        /// </summary>
        float masterVolume_ = 1.0f;

        /// <summary>
        /// Incremental ID used to assign unique sound handles
        /// </summary>
        EI::SoundHandle soundId_ = 0;

        /// <summary>
        /// Incremental ID used to assign unique voice handles
        /// </summary>
        EI::VoiceHandle voiceId_ = 0;

        /// <summary>
        /// Map of loaded sounds indexed by their handle
        /// </summary>
        std::unordered_map<EI::SoundHandle, SoundRes> sounds_;

        /// <summary>
        /// Map of active sound instances (voices) indexed by their handle
        /// </summary>
        std::unordered_map<EI::VoiceHandle, VoiceInst> voices_;
    };
}

/// <summary>
/// Factory function to create a MiniAudioSystem instance.
/// </summary>
/// <returns>Unique pointer to a new MiniAudioSystem</returns>
std::unique_ptr<Engine::IAudioSystem> CreateMiniAudioSystem();