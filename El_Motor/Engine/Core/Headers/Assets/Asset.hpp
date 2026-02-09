#pragma once
#include <string>
#include <cstdint>
#include <iostream>

using AssetID = uint64_t;
using namespace std;
class Asset {
public:
	AssetID id;
	string path;
	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual ~Asset() = default;
};