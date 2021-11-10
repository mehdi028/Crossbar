#include "Drawable.h"

Microsoft::WRL::ComPtr<ID3D11Device> Drawable::GetpDevice()
{
	return pGfx.pDevice;
}

Microsoft::WRL::ComPtr<IDXGISwapChain> Drawable::GetpSwapChain()
{
	return pGfx.PSwapChain;
}

Microsoft::WRL::ComPtr<ID3D11DeviceContext> Drawable::GetpContext()
{
	return pGfx.pContext;
}

Drawable::Drawable(Graphics& pgfx)
	:pGfx(pgfx)
{
}
