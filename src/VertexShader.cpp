#include "VertexShader.h"

VertexShader::VertexShader(Graphics& Gfx, const wchar_t* shaderFile)
    :Bindable(Gfx)
{

    Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
    GFX_CHECK_ERROR(D3DReadFileToBlob(shaderFile, &pBlob));

    GFX_CHECK_ERROR(GetpDevice(gfx)->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVshader));
    bufferPointer = pBlob->GetBufferPointer();
    bufferSize = pBlob->GetBufferSize();
}

LPVOID VertexShader::getBufferPointer()
{
    return bufferPointer;
}

SIZE_T VertexShader::getBufferSize()
{
    return bufferSize;
}

void VertexShader::Bind()
{
    GetpContext(gfx)->VSSetShader(pVshader.Get(), nullptr, 0u);
}
