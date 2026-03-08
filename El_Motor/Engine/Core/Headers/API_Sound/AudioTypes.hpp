#pragma once
#include <cstdint>

namespace EI
{
    /// <summary>
    /// Handle representing a loaded sound resource.
    /// Used to reference a sound file stored in memory.
    /// </summary>
    using SoundHandle = uint32_t; // Loaded sound resource (audio file)

    /// <summary>
    /// Handle representing a currently playing sound instance.
    /// Used to control playback such as stop, pause, or modify parameters.
    /// </summary>
    using VoiceHandle = uint32_t; // Active playback instance

    /// <summary>
    /// Description of a sound resource.
    /// Defines how the audio file should be loaded and used.
    /// </summary>
    struct SoundDesc
    {
        /// Indicates if the sound should be streamed from disk
        /// (typically used for long music tracks)
        bool stream = false;

        /// Indicates if the sound should be spatialized in 3D space
        bool spatial = false;
    };

    /// <summary>
    /// Parameters used to control a playing sound instance.
    /// </summary>
    struct VoiceParams
    {
        /// Playback volume (0..1+)
        float volume = 1.0f;

        /// Playback pitch (1.0 = normal speed)
        float pitch = 1.0f;

        /// Stereo panning for 2D sounds (-1 = left, +1 = right)
        float pan = 0.0f;

        /// Indicates if the sound should loop
        bool loop = false;
    };
}