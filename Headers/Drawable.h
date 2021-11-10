#pragma once
#include"Graphics.h"

class Drawable {

public:
	Drawable(Graphics& pgfx);
	void virtual Draw() = 0;
	
	virtual ~Drawable() = default;

protected:
	Graphics& pGfx;
	Microsoft::WRL::ComPtr<ID3D11Device> GetpDevice();
	Microsoft::WRL::ComPtr<IDXGISwapChain> GetpSwapChain();
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> GetpContext();
	


};