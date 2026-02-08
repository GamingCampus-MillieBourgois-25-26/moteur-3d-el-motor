#pragma once
#include <cstdint>

namespace EI
{
    using SoundHandle = uint32_t; // ressource (fichier chargé)
    using VoiceHandle = uint32_t; // instance (lecture en cours)

    struct SoundDesc
    {
        bool stream = false;   // musique longue
        bool spatial = false;  // 3D 
    };

    struct VoiceParams
    {
        float volume = 1.0f;   // 0..1+
        float pitch = 1.0f;   // 1 = normal
        float pan = 0.0f;   // -1..+1 (2D)
        bool  loop = false;
    };
}
