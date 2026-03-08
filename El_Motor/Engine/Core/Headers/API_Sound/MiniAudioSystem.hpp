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
    /**
     * @brief Audio system implementation using MiniAudio.
     *
     * Handles loading, playing, and managing audio resources
     * in the engine. Implements the IAudioSystem interface.
     */
    class MiniAudioSystem final : public IAudioSystem
    {
    public:

        /**
         * @brief Default constructor
         */
        MiniAudioSystem() = default;

        /**
         * @brief Destructor
         */
        ~MiniAudioSystem() override = default;

        // =========================
        // Lifecycle
        // =========================

        /**
         * @brief Initializes the MiniAudio engine.
         * @return True if initialization succeeded
         */
        bool Init() override;

        /**
         * @brief Shuts down the MiniAudio engine and frees all resources.
         */
        void Shutdown() override;

        /**
         * @brief Updates the MiniAudio engine (streaming, spatialization, etc.).
         * @param deltaTime Time elapsed since last frame
         */
        void Update(float deltaTime) override;

        // =========================
        // Resource management
        // =========================

        /**
         * @brief Loads a sound file into the audio system.
         * @param path Path to the audio file
         * @param desc Sound description (streaming, spatial, etc.)
         * @return Handle referencing the loaded sound
         */
        EI::SoundHandle LoadSound(const std::string& path, const EI::SoundDesc& desc = {}) override;

        /**
         * @brief Unloads a previously loaded sound resource.
         * @param sound Handle of the sound to unload
         */
        void UnloadSound(EI::SoundHandle sound) override;

        // =========================
        // Playback control
        // =========================

        /**
         * @brief Plays a sound with the specified parameters.
         * @param sound Sound handle to play
         * @param params Playback parameters (volume, pitch, loop, pan)
         * @return Handle of the active sound instance (voice)
         */
        EI::VoiceHandle Play(EI::SoundHandle sound, const EI::VoiceParams& params = {}) override;

        /**
         * @brief Stops a currently playing sound instance.
         * @param voice Voice handle to stop
         */
        void Stop(EI::VoiceHandle voice) override;

        // =========================
        // Global control
        // =========================

        /**
         * @brief Sets the global master volume for all sounds.
         * @param volume Volume value (0..1+)
         */
        void SetMasterVolume(float volume) override;


    private:

        /**
         * @brief Structure representing a loaded sound resource.
         */
        struct SoundRes
        {
            std::string path;     /**< Path to the sound file */
            EI::SoundDesc desc;   /**< Sound description (stream/spatial) */
        };

        /**
         * @brief Structure representing an active sound instance (voice).
         */
        struct VoiceInst
        {
            ma_sound* soundPtr;   /**< Opaque pointer to MiniAudio sound */
        };

    private:

        ma_engine* engine_ = nullptr;                    /**< Pointer to the MiniAudio engine instance */
        float masterVolume_ = 1.0f;                      /**< Master volume applied to all sounds */
        EI::SoundHandle soundId_ = 0;                   /**< Incremental ID for unique sound handles */
        EI::VoiceHandle voiceId_ = 0;                   /**< Incremental ID for unique voice handles */
        std::unordered_map<EI::SoundHandle, SoundRes> sounds_; /**< Map of loaded sounds indexed by handle */
        std::unordered_map<EI::VoiceHandle, VoiceInst> voices_; /**< Map of active voices indexed by handle */
    };
}

/**
 * @brief Factory function to create a MiniAudioSystem instance.
 * @return Unique pointer to a new MiniAudioSystem
 */
std::unique_ptr<Engine::IAudioSystem> CreateMiniAudioSystem();