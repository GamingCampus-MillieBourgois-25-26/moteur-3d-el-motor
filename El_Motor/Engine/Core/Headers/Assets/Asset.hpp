#pragma once
#include <string>
#include <cstdint>
#include <d3d11.h>

// Type unique pour identifier chaque asset
using AssetID = uint64_t;

// Classe de base pour tous les assets du moteur
class Asset {
public:
    AssetID id;           // Identifiant unique de l'asset
    std::string path;     // Chemin vers le fichier source

    // Charge les données CPU de l'asset
    virtual void Load() = 0;

    // Libère les ressources CPU et GPU si nécessaire
    virtual void Unload() = 0;

    // Crée les ressources GPU (vertex/index buffers, textures, etc.)
    virtual void CreateBuffers(ID3D11Device* device) {}

    // Bind l'asset dans le pipeline si applicable (ex: textures, meshes)
    virtual void Bind(ID3D11DeviceContext* context) const {}

    virtual ~Asset() = default;
};