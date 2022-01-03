#pragma once
#include<wrl.h>
#include "Bindable.h"
#include "Drawable.h"
#include<vector>
class Enemy : public  Drawable
{
public:
	Enemy(Graphics& gfx);
	void Draw() override;
	
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

};

