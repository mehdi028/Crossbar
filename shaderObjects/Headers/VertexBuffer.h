#pragma once
#include<vector>
#include<wrl.h>
#include "Window.h"
#include "Bindable.h"
template<class T>
class VertexBuffer
{
public:
	
	VertexBuffer(Graphics& gfx,  Microsoft::WRL::ComPtr<ID3D11Buffer>& pVbuffer, const std::vector<T>& verticies) noexcept
		
	{
		
		D3D11_BUFFER_DESC vertexDescr{};
		vertexDescr.ByteWidth = sizeof(T) * verticies.size();
		vertexDescr.Usage = D3D11_USAGE_DEFAULT;
		vertexDescr.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexDescr.CPUAccessFlags = 0;
		vertexDescr.StructureByteStride = sizeof(T);
		vertexDescr.MiscFlags = 0u;
		// fill the vertex buffer with data 
		D3D11_SUBRESOURCE_DATA vertexData{};
		vertexData.pSysMem = verticies.data();
		/*vertexData.SysMemPitch = 0;
		vertexData.SysMemSlicePitch = 0;*/
		GFX_CHECK_ERROR(Bindable::GetpDevice(gfx)->CreateBuffer(&vertexDescr, &vertexData, &pVbuffer));
		//stride = (UINT)sizeof(T);

	}
};

