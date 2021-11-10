#pragma once
#include<vector>
#include "Bindable.h"
class Vbuffer : public Bindable
{
public:
	template<class T>
	Vbuffer(Graphics& Gfx, const std::vector<T>& verticies) noexcept
		:Bindable(Gfx)
	{
		D3D11_BUFFER_DESC vertexDescr{};
		vertexDescr.ByteWidth = sizeof(verticies);
		vertexDescr.Usage = D3D11_USAGE_DEFAULT;
		vertexDescr.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexDescr.CPUAccessFlags = 0;
		vertexDescr.StructureByteStride = sizeof(T);
		vertexDescr.MiscFlags = 0u;
		// fill the vertex buffer with data 
		D3D11_SUBRESOURCE_DATA vertexData{};
		vertexData.pSysMem = verticies;
		/*vertexData.SysMemPitch = 0;
		vertexData.SysMemSlicePitch = 0;*/
		GFX_CHECK_ERROR(Bindable::GetpDevice(gfx)->CreateBuffer(&vertexDescr, &vertexData, &pVbuffer));
		stride = (UINT)sizeof(T);

	}
	void Bind() override;
private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> pVbuffer;
	UINT stride;
	

};

