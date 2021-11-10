#pragma once
#include "Bindable.h"
class IndexBuffer :
    public Bindable
{
public:
    IndexBuffer(Graphics& Gfx, const std::vector<short int>& indicies) noexcept;
    void Bind() override;
private:
    Microsoft::WRL::ComPtr<ID3D11Buffer> pIndexBuffer;
    UINT nIndicies;

};

