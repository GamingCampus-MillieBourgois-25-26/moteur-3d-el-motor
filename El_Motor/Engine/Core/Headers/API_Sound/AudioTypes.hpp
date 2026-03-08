#pragma once
#include <cstdint>

namespace EI
{
    /**
     * @brief Handle representing a loaded sound resource.
     *
     * Used to reference a sound file stored in memory.
     */
    using SoundHandle = uint32_t; ///< Loaded sound resource (audio file)

    /**
     * @brief Handle representing a currently playing sound instance.
     *
     * Used to control playback such as stop, pause, or modify parameters.
     */
    using VoiceHandle = uint32_t; ///< Active playback instance

    /**
     * @brief Description of a sound resource.
     *
     * Defines how the audio file should be loaded and used.
     */
    struct SoundDesc
    {
        /// @brief Stream the sound from disk (typically for long music tracks)
        bool stream = false;

        /// @brief Enable 3D spatialization for this sound
        bool spatial = false;
    };

    /**
     * @brief Parameters used to control a playing sound instance.
     */
    struct VoiceParams
    {
        /// @brief Playback volume (0..1+)
        float volume = 1.0f;

        /// @brief Playback pitch (1.0 = normal speed)
        float pitch = 1.0f;

        /// @brief Stereo panning for 2D sounds (-1 = left, +1 = right)
        float pan = 0.0f;

        /// @brief Loop the sound continuously
        bool loop = false;
    };
}