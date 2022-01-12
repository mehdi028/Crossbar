#pragma once
#include "Drawable.h"
#include<wrl.h>
#include "Bindable.h"
#include "Drawable.h"
#include<vector>
class LimitLine : public Drawable
{
public:
	LimitLine(Graphics& gfx);
	void Draw() override;
	float getLimitX();
	void UpdatePos(float limit) override;
private:
	std::vector<Bindable> all_Bindables;
	UINT nverticies = 0;
	Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexbuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> pTransformbuffer;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> pinputLayout;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> pVshader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pPshader;
	Microsoft::WRL::ComPtr<ID3D11Buffer> pIndexBuffer;
	UINT stride;
	float limit_x;


};

