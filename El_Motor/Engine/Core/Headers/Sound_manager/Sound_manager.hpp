#pragma once

#include <memory>
#include <string>

#include "API_Sound/IAudioSystem.hpp"
#include "API_Sound/AudioTypes.hpp"

namespace EI {

    /**
     * @brief High-level sound manager wrapping an IAudioSystem.
     *
     * Provides functionality for loading, playing, stopping, and managing sounds.
     * Acts as a central interface for audio playback in the engine.
     */
    class SoundManager {
    public:

        /**
         * @brief Default constructor.
         */
        SoundManager();

        /**
         * @brief Destructor.
         *
         * Shuts down the audio system and releases resources if necessary.
         */
        ~SoundManager();

        /**
         * @brief Initializes the underlying audio system.
         *
         * Must be called before loading or playing sounds.
         *
         * @return True if initialization succeeded, false otherwise.
         */
        bool Init();

        /**
         * @brief Shuts down the audio system and releases all resources.
         */
        void Shutdown();

        /**
         * @brief Updates the audio system.
         *
         * Should be called once per frame to process audio events.
         *
         * @param dt Delta time in seconds since the last frame.
         */
        void Update(float dt);

        /**
         * @brief Loads a sound file into memory.
         *
         * @param path Path to the sound file.
         * @param desc Optional sound description (looping, 3D, etc.)
         * @return SoundHandle representing the loaded sound.
         */
        SoundHandle LoadSound(const std::string& path, const SoundDesc& desc = {});

        /**
         * @brief Unloads a previously loaded sound.
         *
         * @param sound Handle of the sound to unload.
         */
        void UnloadSound(SoundHandle sound);

        /**
         * @brief Plays a sound.
         *
         * @param sound Handle of the sound to play.
         * @param params Optional playback parameters (volume, pitch, 3D position, etc.)
         * @return VoiceHandle representing the playing instance.
         */
        VoiceHandle Play(SoundHandle sound, const VoiceParams& params = {});

        /**
         * @brief Stops a currently playing voice.
         *
         * @param voice Handle of the voice to stop.
         */
        void Stop(VoiceHandle voice);

        /**
         * @brief Sets the global/master volume of the audio system.
         *
         * @param volume Volume value, where 0.0f = silent, 1.0f = full volume.
         */
        void SetMasterVolume(float volume);

    private:

        /**
         * @brief Underlying audio system implementation.
         */
        std::unique_ptr<Engine::IAudioSystem> audioSystem_;
    };

} // namespace EI