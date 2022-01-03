#pragma once
#include<vector>
#include<wrl.h>
#include "Window.h"
#include "Bindable.h"
template <class T>
class ConstantBuffer
{
public:
	ConstantBuffer(Graphics& gfx, Microsoft::WRL::ComPtr<ID3D11Buffer>& pConstantBuffer, const T& cBuffer) noexcept
	{
		D3D11_BUFFER_DESC cbufferDescr{};
		cbufferDescr.ByteWidth = sizeof(cBuffer);
		cbufferDescr.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbufferDescr.MiscFlags = 0;
		cbufferDescr.Usage = D3D11_USAGE_DYNAMIC;
		cbufferDescr.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbufferDescr.StructureByteStride = 0;
		D3D11_SUBRESOURCE_DATA  cbData{};
		cbData.pSysMem = &cBuffer;
		cbData.SysMemPitch = 0;
		cbData.SysMemSlicePitch = 0;
		GFX_CHECK_ERROR(Bindable::GetpDevice(gfx)->CreateBuffer(&cbufferDescr, &cbData, &pConstantBuffer));

	}
};

