#pragma once
#include <string>
#include <unordered_map>
#include "API_Sound/AudioTypes.hpp"

namespace Engine
{
    /// <summary>
    /// Interface representing the core audio system of the engine.
    /// Defines the API used to initialize the audio backend,
    /// manage sound resources, and control audio playback.
    /// Implementations can use different audio libraries
    /// (MiniAudio, FMOD, Wwise, etc.).
    /// </summary>
    class IAudioSystem
    {
    public:

        /// <summary>
        /// Virtual destructor
        /// </summary>
        virtual ~IAudioSystem() = default;

        // =========================
        // Lifecycle
        // =========================

        /// <summary>
        /// Initializes the audio system and underlying audio backend.
        /// </summary>
        /// <returns>True if initialization succeeded</returns>
        virtual bool Init() = 0;

        /// <summary>
        /// Shuts down the audio system and releases all audio resources.
        /// </summary>
        virtual void Shutdown() = 0;

        /// <summary>
        /// Updates the audio system.
        /// Typically called once per frame to process streaming,
        /// spatialization, and internal audio updates.
        /// </summary>
        /// <param name="dt">Delta time since the last frame</param>
        virtual void Update(float dt) = 0;

        // =========================
        // Resource Management
        // =========================

        /// <summary>
        /// Loads a sound resource from a file.
        /// </summary>
        /// <param name="path">Path to the audio file</param>
        /// <param name="desc">Sound loading description</param>
        /// <returns>Handle referencing the loaded sound</returns>
        virtual EI::SoundHandle LoadSound(const std::string& path, const EI::SoundDesc& desc = {}) = 0;

        /// <summary>
        /// Unloads a previously loaded sound resource.
        /// </summary>
        /// <param name="sound">Handle of the sound to unload</param>
        virtual void UnloadSound(EI::SoundHandle sound) = 0;

        // =========================
        // Playback Control
        // =========================

        /// <summary>
        /// Plays a sound using the specified playback parameters.
        /// </summary>
        /// <param name="sound">Handle of the sound to play</param>
        /// <param name="params">Playback parameters (volume, pitch, loop, etc.)</param>
        /// <returns>Handle of the active sound instance</returns>
        virtual EI::VoiceHandle Play(EI::SoundHandle sound, const EI::VoiceParams& params = {}) = 0;

        /// <summary>
        /// Stops a currently playing sound instance.
        /// </summary>
        /// <param name="voice">Handle of the voice to stop</param>
        virtual void Stop(EI::VoiceHandle voice) = 0;

        // =========================
        // Global Controls
        // =========================

        /// <summary>
        /// Sets the global master volume for the entire audio system.
        /// </summary>
        /// <param name="volume">Master volume value</param>
        virtual void SetMasterVolume(float volume) = 0;
    };
}