#pragma once
#include <string>
#include <cstdint>
#include <d3d11.h>

using AssetID = uint64_t;

class Asset {
public:
    AssetID id;
    std::string path;

    virtual void Load() = 0;    
    virtual void Unload() = 0;
    virtual void CreateBuffers(ID3D11Device* device) {}

    virtual void Bind(ID3D11DeviceContext* context) const {}
    virtual ~Asset() = default;
};
