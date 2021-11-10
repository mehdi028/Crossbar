#include "Bindable.h"

Bindable::Bindable( Graphics& pgfx) noexcept
    :gfx(pgfx)
{
}

Microsoft::WRL::ComPtr<ID3D11Device> Bindable::GetpDevice(Graphics& pgfx)
{
    return pgfx.pDevice;
}

Microsoft::WRL::ComPtr<IDXGISwapChain> Bindable::GetpSwapChain(Graphics& pgfx)
{
    return pgfx.PSwapChain ;
}

Microsoft::WRL::ComPtr<ID3D11DeviceContext> Bindable::GetpContext(Graphics& pgfx)
{
    return pgfx.pContext ;
}
