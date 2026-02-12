#include "Core/D3D11/D3D11.hpp"

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include <dxgi.h>
#include <d3d11.h>
#include <d3dcommon.h>
#include <Windows.h>

namespace Engine
{
    D3D11::D3D11(GLFWwindow* window)
    {
        myWindow = glfwGetWin32Window(window); // R�cup�re le handle de la fen�tre � partir de GLFW
        DXGI_SWAP_CHAIN_DESC swapChainDesc = initSwapChainDesc(); // variable locale pour la description du swap chain, initialis�e avec les param�tres souhait�s

        D3D11CreateDeviceAndSwapChain(searchForAdapters(), // Adapter
                                      D3D_DRIVER_TYPE_UNKNOWN, // Driver Type
                                      nullptr, // Software
                                      0, // Flags
                                      nullptr, 0, // Feature Levels
                                      D3D11_SDK_VERSION, &swapChainDesc, // Utilise la variable locale, qui est une l-value
                                      &pSwapChain, &pDevice, nullptr, // Feature Level
                                      &pContext);
    }

    D3D11::~D3D11()
    {
        if (pSwapChain != nullptr)
            pSwapChain->Release(); // Lib�re le swap chain
        if (pContext != nullptr)
            pContext->Release(); // Lib�re le contexte de rendu
        if (pDevice != nullptr)
            pDevice->Release(); // Lib�re le device
    }

    IDXGIAdapter1* D3D11::searchForAdapters()
    {
        IDXGIFactory1* pFactory = nullptr;
        CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)&pFactory); // Factory version 1

        IDXGIAdapter1* pAdapter = nullptr;
        IDXGIAdapter1* bestAdapter = nullptr;
        SIZE_T maxVRam = 0;

        for (UINT i = 0; pFactory->EnumAdapters1(i, &pAdapter) != DXGI_ERROR_NOT_FOUND; ++i)
        {
            DXGI_ADAPTER_DESC1 desc;
            pAdapter->GetDesc1(&desc);
            if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
                continue; // Ignore les adaptateurs logiciels
            if (desc.DedicatedVideoMemory > maxVRam)
            {
                maxVRam = desc.DedicatedVideoMemory;
                bestAdapter = pAdapter;
            }
        }
        return bestAdapter;
    }

    DXGI_SWAP_CHAIN_DESC D3D11::initSwapChainDesc()
    {
        DXGI_SWAP_CHAIN_DESC SwapChDesc = {};
        SwapChDesc.BufferDesc.Width = 800; // Largeur du buffer
        SwapChDesc.BufferDesc.Height = 600; // Hauteur du buffer
        SwapChDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // Format du buffer
        SwapChDesc.BufferDesc.RefreshRate.Numerator = 60; // Taux de rafra�chissement (num�rateur)
        SwapChDesc.BufferDesc.RefreshRate.Denominator = 1; // Taux de rafra�chissement (d�nominateur)
        SwapChDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED; // Type de scaling
        SwapChDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED; // Ordre de balayage
        SwapChDesc.SampleDesc.Count = 1; // Nombre d'�chantillons pour l'anti-aliasing
        SwapChDesc.SampleDesc.Quality = 0; // Qualit� de l'anti-aliasing
        SwapChDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // Usage du buffer
        SwapChDesc.BufferCount = 1; // Nombre de buffers
        SwapChDesc.OutputWindow = myWindow; // Fen�tre de sortie
        SwapChDesc.Windowed = TRUE; // Mode fen�tr�
        SwapChDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; // Effet de swap
        SwapChDesc.Flags = 0; // Flags suppl�mentaires
        return SwapChDesc; // Retourne la description du swap chain
    }
}
