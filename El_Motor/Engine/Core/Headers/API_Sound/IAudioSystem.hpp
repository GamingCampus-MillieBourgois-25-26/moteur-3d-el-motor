#pragma once
#include <string>
#include <unordered_map>
#include "API_Sound/AudioTypes.hpp"

namespace Engine
{
    /**
     * @brief Interface representing the core audio system of the engine.
     *
     * Defines the API used to initialize the audio backend,
     * manage sound resources, and control audio playback.
     * Implementations can use different audio libraries
     * (MiniAudio, FMOD, Wwise, etc.).
     */
    class IAudioSystem
    {
    public:

        /**
         * @brief Virtual destructor
         */
        virtual ~IAudioSystem() = default;

        // =========================
        // Lifecycle
        // =========================

        /**
         * @brief Initializes the audio system and underlying audio backend.
         * @return True if initialization succeeded
         */
        virtual bool Init() = 0;

        /**
         * @brief Shuts down the audio system and releases all audio resources.
         */
        virtual void Shutdown() = 0;

        /**
         * @brief Updates the audio system.
         *
         * Typically called once per frame to process streaming,
         * spatialization, and internal audio updates.
         *
         * @param dt Delta time since the last frame
         */
        virtual void Update(float dt) = 0;

        // =========================
        // Resource Management
        // =========================

        /**
         * @brief Loads a sound resource from a file.
         *
         * @param path Path to the audio file
         * @param desc Sound loading description (streaming, 3D, etc.)
         * @return Handle referencing the loaded sound
         */
        virtual EI::SoundHandle LoadSound(const std::string& path, const EI::SoundDesc& desc = {}) = 0;

        /**
         * @brief Unloads a previously loaded sound resource.
         *
         * @param sound Handle of the sound to unload
         */
        virtual void UnloadSound(EI::SoundHandle sound) = 0;

        // =========================
        // Playback Control
        // =========================

        /**
         * @brief Plays a sound using the specified playback parameters.
         *
         * @param sound Handle of the sound to play
         * @param params Playback parameters (volume, pitch, loop, etc.)
         * @return Handle of the active sound instance
         */
        virtual EI::VoiceHandle Play(EI::SoundHandle sound, const EI::VoiceParams& params = {}) = 0;

        /**
         * @brief Stops a currently playing sound instance.
         *
         * @param voice Handle of the voice to stop
         */
        virtual void Stop(EI::VoiceHandle voice) = 0;

        // =========================
        // Global Controls
        // =========================

        /**
         * @brief Sets the global master volume for the entire audio system.
         *
         * @param volume Master volume value (0.0 = silent, 1.0 = full volume)
         */
        virtual void SetMasterVolume(float volume) = 0;
    };
}