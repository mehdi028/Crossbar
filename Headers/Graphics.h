#pragma once
#include<d3d11.h>
#include<wrl.h>
#include "MyTimer.h"
#include<d3dcompiler.h>
#include<vector>
class Graphics
{
	friend class Drawable;
	friend class Bindable;
private:
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr<IDXGISwapChain> PSwapChain;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pRendTargetView;
	MyTimer timer;
public:
	Graphics(const HWND& hwnd);
	void ClearRendered();
	void DrawTriangle(const float& x, const float& y, float angle);
	void PresentFrame();
	void drawEnemy();

	
	

};

#define GFX_CHECK_ERROR(x) if(FAILED(x)){ throw 1 ;}

