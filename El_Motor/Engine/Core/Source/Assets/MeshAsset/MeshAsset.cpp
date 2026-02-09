#include "../Core/Headers/Assets/MeshAsset/MeshAsset.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cstdio> 

extern ID3D11Device* device;

void MeshAsset::Load() {
    std::ifstream file(path);
    if (!file.is_open()) throw std::runtime_error("Failed to open OBJ file");

    std::vector<DirectX::XMFLOAT3> positions;
    std::vector<DirectX::XMFLOAT3> normals;
    std::vector<DirectX::XMFLOAT2> uvs;

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string prefix;
        ss >> prefix;

        if (prefix == "v") {
            DirectX::XMFLOAT3 pos;
            ss >> pos.x >> pos.y >> pos.z;
            positions.push_back(pos);
        }
        else if (prefix == "vn") {
            DirectX::XMFLOAT3 n;
            ss >> n.x >> n.y >> n.z;
            normals.push_back(n);
        }
        else if (prefix == "vt") {
            DirectX::XMFLOAT2 uv;
            ss >> uv.x >> uv.y;
            uvs.push_back(uv);
        }
        else if (prefix == "f") {
            for (int i = 0; i < 3; ++i) {
                std::string vert;
                ss >> vert;

                int p, t, n;
                sscanf_s(vert.c_str(), "%d/%d/%d", &p, &t, &n);

                Vertex v;
                v.position = positions[p - 1];
                v.uv = uvs[t - 1];
                v.normal = normals[n - 1];

                vertices.push_back(v);
                indices.push_back(static_cast<uint32_t>(indices.size()));
            }
        }
    }

    CreateBuffersDX11();
}

void MeshAsset::CreateBuffersDX11() {
    if (!device) throw std::runtime_error("DX11 device not set");

    D3D11_BUFFER_DESC vbd = {};
    vbd.Usage = D3D11_USAGE_DEFAULT;
    vbd.ByteWidth = static_cast<UINT>(vertices.size() * sizeof(Vertex));
    vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA vinit = {};
    vinit.pSysMem = vertices.data();

    device->CreateBuffer(&vbd, &vinit, &vertexBuffer);

    D3D11_BUFFER_DESC ibd = {};
    ibd.Usage = D3D11_USAGE_DEFAULT;
    ibd.ByteWidth = static_cast<UINT>(indices.size() * sizeof(uint32_t));
    ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;

    D3D11_SUBRESOURCE_DATA iinit = {};
    iinit.pSysMem = indices.data();

    device->CreateBuffer(&ibd, &iinit, &indexBuffer);
}

void MeshAsset::Unload() {
    if (vertexBuffer) {
        vertexBuffer->Release();
        vertexBuffer = nullptr;
    }
    if (indexBuffer) {
        indexBuffer->Release();
        indexBuffer = nullptr;
    }

    vertices.clear();
    indices.clear();
}
