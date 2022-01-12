#pragma once
#include "Drawable.h"
#include "Window.h"
#include<wrl.h>
#include "Bindable.h"
class Plate :
    public Drawable
    
{public:
	
	Plate(Graphics& gfx) noexcept;
	void UpdatePos(float limit) override;
	void MovePlate(Window& wnd, float limit);
	void Draw() override;
private:
	UINT nverticies = 0;
	Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexbuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> pTransformbuffer;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> pinputLayout;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> pVshader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pPshader;
	Microsoft::WRL::ComPtr<ID3D11Buffer> pIndexBuffer;
	UINT stride;
	float move_plate_val = 0.f;
};

