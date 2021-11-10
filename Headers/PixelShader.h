#pragma once
#include "Bindable.h"
class PixelShader :
    public Bindable
{
public:
    PixelShader(Graphics& Gfx, const wchar_t* shaderFile);
    LPVOID getBufferPointer();
    SIZE_T getBufferSize();
    void Bind() override ;
private:
    Microsoft::WRL::ComPtr<ID3D11PixelShader> pPshader;
    LPVOID  bufferPointer;
    SIZE_T bufferSize;

};

