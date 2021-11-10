#pragma once
#include "Graphics.h"
class Bindable
{
public:
	Bindable(Graphics& pgfx)noexcept ;
	void virtual Bind() = 0;
	static Microsoft::WRL::ComPtr<ID3D11Device> GetpDevice(Graphics& pgfx);
	static Microsoft::WRL::ComPtr<IDXGISwapChain> GetpSwapChain(Graphics& pgfx);
	static Microsoft::WRL::ComPtr<ID3D11DeviceContext> GetpContext(Graphics& pgfx);
protected:
	Graphics& gfx;
};

