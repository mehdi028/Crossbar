#include "PixelShader.h"

PixelShader::PixelShader(Graphics& Gfx, const wchar_t* shaderFile)
    :Bindable(Gfx)
{
    Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
    GFX_CHECK_ERROR(D3DReadFileToBlob(shaderFile, &pBlob));

    GFX_CHECK_ERROR(GetpDevice(gfx)->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPshader));
    bufferPointer = pBlob->GetBufferPointer();
    bufferSize = pBlob->GetBufferSize();
}

LPVOID PixelShader::getBufferPointer()
{
    return bufferPointer;
}

SIZE_T PixelShader::getBufferSize()
{
    return bufferSize;
}

void PixelShader::Bind()
{
}
