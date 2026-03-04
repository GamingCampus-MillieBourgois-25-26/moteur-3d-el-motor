#include "Assets/MeshAsset/MeshAsset.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cstdio>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

//MeshAsset::MeshAsset(const std::string& path,const DirectX::XMFLOAT3& color): mColor(color)
//{
//    this->path = path;
//}


void MeshAsset::Load()
{
    vertices.clear();
    indices.clear();

    std::string extension;
    size_t dot = path.find_last_of('.');
    if (dot != std::string::npos)
        extension = path.substr(dot + 1);

    // ============================================================
    // FBX / GLTF / DAE / OBJ via Assimp
    // ============================================================

    if (extension == "fbx" || extension == "FBX" ||
        extension == "gltf" || extension == "GLTF" ||
        extension == "dae" || extension == "DAE")
    {
        Assimp::Importer importer;

        const aiScene* scene = importer.ReadFile(
            path,
            aiProcess_Triangulate |
            aiProcess_FlipUVs |
            aiProcess_GenNormals |
            aiProcess_JoinIdenticalVertices
        );

        if (!scene || !scene->HasMeshes())
            throw std::runtime_error("Assimp failed to load mesh: " + path);

        aiMesh* mesh = scene->mMeshes[0];

        // Vertices
        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex v{};

            v.position =
            {
                mesh->mVertices[i].x,
                mesh->mVertices[i].y,
                mesh->mVertices[i].z
            };

            if (mesh->HasNormals())
            {
                v.normal =
                {
                    mesh->mNormals[i].x,
                    mesh->mNormals[i].y,
                    mesh->mNormals[i].z
                };
            }
            else
            {
                v.normal = DirectX::XMFLOAT3(0, 1, 0);
            }

            if (mesh->HasTextureCoords(0))
            {
                v.uv =
                {
                    mesh->mTextureCoords[0][i].x,
                    mesh->mTextureCoords[0][i].y
                };
            }
            else
            {
                v.uv = DirectX::XMFLOAT2(0, 0);
            }

            vertices.push_back(v);
        }

        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            const aiFace& face = mesh->mFaces[i];

            for (unsigned int j = 0; j < face.mNumIndices; j++)
            {
                indices.push_back(face.mIndices[j]);
            }
        }

        if (vertices.empty() || indices.empty())
            throw std::runtime_error("Assimp mesh empty: " + path);

        return;
    }

    std::ifstream file(path);

    if (!file.is_open())
        throw std::runtime_error("Failed to open OBJ file: " + path);

    vertices.clear();
    indices.clear();

    std::vector<Maths::Vec3f> positions;
    std::vector<Maths::Vec3f> normals;
    std::vector<Maths::Vec2f> uvs;

    std::string line;

    while (std::getline(file, line))
    {
        if (line.empty())
            continue;

        std::stringstream ss(line);
        std::string prefix;
        ss >> prefix;

        if (prefix == "v")
        {
            Maths::Vec3f pos{};
            ss >> pos.m_x >> pos.m_y >> pos.m_z;
            positions.push_back(pos);
        }
        else if (prefix == "vn")
        {
            Maths::Vec3f normal{};
            ss >> normal.m_x >> normal.m_y >> normal.m_z;
            normals.push_back(normal);
        }
        else if (prefix == "vt")
        {
            Maths::Vec2f uv{};
            ss >> uv.m_x >> uv.m_y;
            uvs.push_back(uv);
        }
        else if (prefix == "f")
        {
            std::vector<std::string> faceVerts;
            std::string vert;

            while (ss >> vert)
                faceVerts.push_back(vert);

            for (size_t i = 1; i + 1 < faceVerts.size(); ++i)
            {
                std::string triangle[3] =
                {
                    faceVerts[0],
                    faceVerts[i],
                    faceVerts[i + 1]
                };

                for (int j = 0; j < 3; ++j)
                {
                    int v_idx = 0;
                    int vt_idx = 0;
                    int vn_idx = 0;

                    sscanf_s(triangle[j].c_str(), "%d/%d/%d",
                        &v_idx, &vt_idx, &vn_idx);

                    Vertex vertex{};

                    if (v_idx > 0 && v_idx <= positions.size())
                        vertex.position = positions[v_idx - 1];

                    if (vt_idx > 0 && vt_idx <= uvs.size())
                        vertex.uv = uvs[vt_idx - 1];
                    else
                        vertex.uv = Maths::Vec2f(0.0f, 0.0f);

                    if (vn_idx > 0 && vn_idx <= normals.size())
                        vertex.normal = normals[vn_idx - 1];
                    else
                        vertex.normal = Maths::Vec3f(1.0f, 1.0f, 1.0f);

                    vertices.push_back(vertex);
                    indices.push_back((uint32_t)indices.size());
                }
            }
        }
    }

    file.close();

    if (vertices.empty() || indices.empty())
        throw std::runtime_error("OBJ mesh empty: " + path);
}
void MeshAsset::LoadTestCube()
{
    vertices.clear();
    indices.clear();

    Vertex v[] =
    {
        // Face avant (proche)
        {{-0.5f, -0.5f, 0.0f}, {0,0,-1}, {0,1}},
        {{ 0.5f, -0.5f, 0.0f}, {0,0,-1}, {1,1}},
        {{ 0.5f,  0.5f, 0.0f}, {0,0,-1}, {1,0}},
        {{-0.5f,  0.5f, 0.0f}, {0,0,-1}, {0,0}},

        // Face arrière (plus loin, légèrement décalée pour “profil”)
        {{-0.3f, -0.3f, 0.5f}, {0,0,1}, {0,1}},
        {{ 0.7f, -0.3f, 0.5f}, {0,0,1}, {1,1}},
        {{ 0.7f,  0.7f, 0.5f}, {0,0,1}, {1,0}},
        {{-0.3f,  0.7f, 0.5f}, {0,0,1}, {0,0}},
    };

    vertices.assign(std::begin(v), std::end(v));

    uint32_t ind[] =
    {
        0,1,2,
        0,2,3,

        4,6,5,
        4,7,6,

        4,5,1,
        4,1,0,

        3,2,6,
        3,6,7,

        1,5,6,
        1,6,2,

        4,0,3,
        4,3,7
    };
    //this->SetColor(0.0f, 0.0f, 1.0f);

    indices.assign(std::begin(ind), std::end(ind));
}

void MeshAsset::CreateBuffers(ID3D11Device* device)
{
    if (!device)
        throw std::runtime_error("Device is null");

    if (vertices.empty() || indices.empty())
        throw std::runtime_error("Cannot create buffers");

    D3D11_BUFFER_DESC vbd{};
    vbd.Usage = D3D11_USAGE_DEFAULT;
    vbd.ByteWidth = UINT(vertices.size() * sizeof(Vertex));
    vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;



    D3D11_SUBRESOURCE_DATA vinit{};
    vinit.pSysMem = vertices.data();

    HRESULT hr = device->CreateBuffer(&vbd, &vinit, vertexBuffer.GetAddressOf());

    if (FAILED(hr))
        throw std::runtime_error("Failed to create vertex buffer");

    D3D11_BUFFER_DESC ibd{};
    ibd.Usage = D3D11_USAGE_DEFAULT;
    ibd.ByteWidth = UINT(indices.size() * sizeof(uint32_t));
    ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;

    D3D11_SUBRESOURCE_DATA iinit{};
    iinit.pSysMem = indices.data();

    hr = device->CreateBuffer(&ibd, &iinit, indexBuffer.GetAddressOf());

    if (FAILED(hr))
        throw std::runtime_error("Failed to create index buffer");
}

void MeshAsset::Bind(ID3D11DeviceContext* context) const
{
    UINT stride = sizeof(Vertex);
    UINT offset = 0;

    context->IASetVertexBuffers(
        0,
        1,
        vertexBuffer.GetAddressOf(),
        &stride,
        &offset
    );

    context->IASetIndexBuffer(
        indexBuffer.Get(),
        DXGI_FORMAT_R32_UINT,
        0
    );

    context->IASetPrimitiveTopology(
        D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP
    );
}


bool MeshAsset::IsReady() const
{
    return vertexBuffer && indexBuffer;
}

UINT MeshAsset::GetIndexCount() const
{
    return (UINT)indices.size();
}

void MeshAsset::Unload()
{
    vertices.clear();
    indices.clear();

    vertexBuffer.Reset();
    indexBuffer.Reset();
}