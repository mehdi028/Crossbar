#pragma once
#include<vector>
#include<array>
#include "Bindable.h"

class InputLayout :
    public Bindable
{
public:
    template<int I>
    InputLayout(Graphics& Gfx, const std::vector<D3D11_INPUT_ELEMENT_DESC>& iedesc, LPVOID bufferPointer, const SIZE_T& bufferSize)
        :Bindable(Gfx)
    {
        
        D3D11_INPUT_ELEMENT_DESC ied[I];
        for (int i = 0; i < I; i++)
        {
            ied[i] = iedesc[i];
        }
        GFX_CHECK_ERROR(GetpDevice(gfx)->CreateInputLayout(ied, ARRAYSIZE(ied), bufferPointer, bufferSize, &pinputLayout));

    }


    void Bind() override;
private:
    Microsoft::WRL::ComPtr<ID3D11InputLayout> pinputLayout;

};

