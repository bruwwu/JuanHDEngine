#include "Device.h"

// Creación de Vertex Shader
HRESULT Device::CreateVertexShader(
    const void* pShaderBytecode,
    unsigned int BytecodeLength,
    ID3D11ClassLinkage* pClassLinkage,
    ID3D11VertexShader** ppVertexShader)
{
    if (!pShaderBytecode || !ppVertexShader) {
        ERROR("Device", "CreateVertexShader", "Invalid parameters");
        return E_INVALIDARG;
    }

    HRESULT hr = m_device->CreateVertexShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppVertexShader);
    if (SUCCEEDED(hr)) {
        MESSAGE("Device", "CreateVertexShader", "Vertex Shader created successfully!");
    }
    else {
        std::wstring errorMsg = L"Failed to create Vertex Shader. HRESULT: " + std::to_wstring(hr);
        ERROR("Device", "CreateVertexShader", errorMsg);
    }

    return hr;
}

// Creación de Input Layout
HRESULT Device::CreateInputLayout(
    D3D11_INPUT_ELEMENT_DESC* pInputElementDescs,
    unsigned int NumElements,
    const void* pShaderBytecodeWithInputSignature,
    unsigned int BytecodeLength,
    ID3D11InputLayout** ppInputLayout)
{
    if (!pInputElementDescs || !ppInputLayout || !pShaderBytecodeWithInputSignature) {
        ERROR("Device", "CreateInputLayout", "Invalid parameters");
        return E_INVALIDARG;
    }

    HRESULT hr = m_device->CreateInputLayout(pInputElementDescs, NumElements, pShaderBytecodeWithInputSignature, BytecodeLength, ppInputLayout);
    if (SUCCEEDED(hr)) {
        MESSAGE("Device", "CreateInputLayout", "Input Layout created successfully!");
    }
    else {
        std::wstring errorMsg = L"Failed to create Input Layout. HRESULT: " + std::to_wstring(hr);
        ERROR("Device", "CreateInputLayout", errorMsg);
    }

    return hr;
}

// Creación de Pixel Shader
HRESULT Device::CreatePixelShader(
    const void* pShaderBytecode,
    unsigned int BytecodeLength,
    ID3D11ClassLinkage* pClassLinkage,
    ID3D11PixelShader** ppPixelShader)
{
    if (!pShaderBytecode || !ppPixelShader) {
        ERROR("Device", "CreatePixelShader", "Invalid parameters");
        return E_INVALIDARG;
    }

    HRESULT hr = m_device->CreatePixelShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppPixelShader);
    if (SUCCEEDED(hr)) {
        MESSAGE("Device", "CreatePixelShader", "Pixel Shader created successfully!");
    }
    else {
        std::wstring errorMsg = L"Failed to create Pixel Shader. HRESULT: " + std::to_wstring(hr);
        ERROR("Device", "CreatePixelShader", errorMsg);
    }

    return hr;
}

// Creación de Buffer
HRESULT Device::CreateBuffer(
    const D3D11_BUFFER_DESC* pDesc,
    const D3D11_SUBRESOURCE_DATA* pInitialData,
    ID3D11Buffer** ppBuffer)
{
    if (!pDesc || !ppBuffer) {
        ERROR("Device", "CreateBuffer", "Invalid parameters");
        return E_INVALIDARG;
    }

    HRESULT hr = m_device->CreateBuffer(pDesc, pInitialData, ppBuffer);
    if (SUCCEEDED(hr)) {
        MESSAGE("Device", "CreateBuffer", "Buffer created successfully!");
    }
    else {
        std::wstring errorMsg = L"Failed to create Buffer. HRESULT: " + std::to_wstring(hr);
        ERROR("Device", "CreateBuffer", errorMsg);
    }

    return hr;
}

// Creación de Sampler State
HRESULT Device::CreateSamplerState(
    const D3D11_SAMPLER_DESC* pSamplerDesc,
    ID3D11SamplerState** ppSamplerState)
{
    if (!pSamplerDesc || !ppSamplerState) {
        ERROR("Device", "CreateSamplerState", "Invalid parameters");
        return E_INVALIDARG;
    }

    HRESULT hr = m_device->CreateSamplerState(pSamplerDesc, ppSamplerState);
    if (SUCCEEDED(hr)) {
        MESSAGE("Device", "CreateSamplerState", "Sampler State created successfully!");
    }
    else {
        std::wstring errorMsg = L"Failed to create Sampler State. HRESULT: " + std::to_wstring(hr);
        ERROR("Device", "CreateSamplerState", errorMsg);
    }

    return hr;
}

// Creación de Texture2D
HRESULT Device::CreateTexture2D(
    D3D11_TEXTURE2D_DESC* pDesc,
    D3D11_SUBRESOURCE_DATA* pInitialData,
    ID3D11Texture2D** ppTexture2D)
{
    if (!pDesc || !ppTexture2D) {
        ERROR("Device", "CreateTexture2D", "Invalid parameters");
        return E_INVALIDARG;
    }

    HRESULT hr = m_device->CreateTexture2D(pDesc, pInitialData, ppTexture2D);
    if (SUCCEEDED(hr)) {
        MESSAGE("Device", "CreateTexture2D", "Texture2D created successfully!");
    }
    else {
        std::wstring errorMsg = L"Failed to create Texture2D. HRESULT: " + std::to_wstring(hr);
        ERROR("Device", "CreateTexture2D", errorMsg);
    }

    return hr;
}

// Creación de Depth Stencil View
HRESULT Device::CreateDepthStencilView(
    ID3D11Resource* pResource,
    D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc,
    ID3D11DepthStencilView** ppDepthStencilView)
{
    if (!pResource || !ppDepthStencilView) {
        ERROR("Device", "CreateDepthStencilView", "Invalid parameters");
        return E_INVALIDARG;
    }

    HRESULT hr = m_device->CreateDepthStencilView(pResource, pDesc, ppDepthStencilView);
    if (SUCCEEDED(hr)) {
        MESSAGE("Device", "CreateDepthStencilView", "Depth Stencil View created successfully!");
    }
    else {
        std::wstring errorMsg = L"Failed to create Depth Stencil View. HRESULT: " + std::to_wstring(hr);
        ERROR("Device", "CreateDepthStencilView", errorMsg);
    }

    return hr;
}
