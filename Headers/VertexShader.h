#pragma once
#include "Bindable.h"
class VertexShader :
    public Bindable
{
public:
    VertexShader(Graphics& Gfx, const wchar_t* shaderFile);
    LPVOID getBufferPointer();
    SIZE_T getBufferSize();
    
    void Bind() override;
private:
    Microsoft::WRL::ComPtr<ID3D11VertexShader> pVshader;
    LPVOID  bufferPointer;
    SIZE_T bufferSize;

};

