#pragma once
#include <string>
#include <cstdint>

using AssetID = uint64_t;

class Asset {
public:
    AssetID id;
    std::string path;

    virtual void Load() = 0;    
    virtual void Unload() = 0;

    virtual ~Asset() = default;
};
