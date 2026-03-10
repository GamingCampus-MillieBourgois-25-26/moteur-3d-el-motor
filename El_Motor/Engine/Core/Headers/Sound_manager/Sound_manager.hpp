#pragma once

#include <memory>
#include <string>

#include "API_Sound/IAudioSystem.hpp"
#include "API_Sound/AudioTypes.hpp"

namespace EI {

    /// <summary>
    /// High-level sound manager that wraps around an IAudioSystem.
    /// Provides functionality for loading, playing, and stopping sounds.
    /// </summary>
    class SoundManager {
    public:

        /// <summary>
        /// Default constructor.
        /// </summary>
        SoundManager();

        /// <summary>
        /// Destructor, shuts down audio system if necessary.
        /// </summary>
        ~SoundManager();

        /// <summary>
        /// Initializes the underlying audio system.
        /// </summary>
        /// <returns>True if initialization succeeded</returns>
        bool Init();

        /// <summary>
        /// Shuts down the audio system and releases resources.
        /// </summary>
        void Shutdown();

        /// <summary>
        /// Updates the audio system (call once per frame).
        /// </summary>
        /// <param name="dt">Delta time in seconds</param>
        void Update(float dt);

        /// <summary>
        /// Loads a sound file into memory and returns a handle.
        /// </summary>
        /// <param name="path">Path to the sound file</param>
        /// <param name="desc">Optional sound description</param>
        /// <returns>SoundHandle to the loaded sound</returns>
        SoundHandle LoadSound(const std::string& path, const SoundDesc& desc = {});

        /// <summary>
        /// Unloads a previously loaded sound.
        /// </summary>
        /// <param name="sound">Handle of the sound to unload</param>
        void UnloadSound(SoundHandle sound);

        /// <summary>
        /// Plays a sound with the given parameters.
        /// </summary>
        /// <param name="sound">Handle of the sound to play</param>
        /// <param name="params">Optional playback parameters</param>
        /// <returns>VoiceHandle representing the playing instance</returns>
        VoiceHandle Play(SoundHandle sound, const VoiceParams& params = {});

        /// <summary>
        /// Stops a currently playing voice.
        /// </summary>
        /// <param name="voice">Handle of the voice to stop</param>
        void Stop(VoiceHandle voice);

        /// <summary>
        /// Sets the global/master volume of the audio system.
        /// </summary>
        /// <param name="volume">Volume value (0.0f = silent, 1.0f = full)</param>
        void SetMasterVolume(float volume);

    private:

        /// <summary>
        /// Underlying audio system implementation (IAudioSystem)
        /// </summary>
        std::unique_ptr<Engine::IAudioSystem> audioSystem_;
    };
}