#pragma once
#include<vector>
#include<wrl.h>
#include "Window.h"
#include "Bindable.h"
template <class T>
class ConstantBuffer
{
private:
	Microsoft::WRL::ComPtr<ID3D11Buffer>& pConstantBuffer;
	
public:
	ConstantBuffer(Graphics& gfx, Microsoft::WRL::ComPtr<ID3D11Buffer>& pConstantBuffer, const T& cBuffer) noexcept
		: pConstantBuffer(pConstantBuffer)
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
	static void UpdateBuffer(Graphics& gfx, Microsoft::WRL::ComPtr<ID3D11Buffer>& pConstantBuffer, const T& cBuffer)
	{
		D3D11_MAPPED_SUBRESOURCE msr;
		Bindable::GetpContext(gfx)->Map(pConstantBuffer.Get(), 0u, D3D11_MAP_WRITE_DISCARD, 0u, &msr);
		memcpy(msr.pData, &cBuffer, sizeof(cBuffer));
		Bindable::GetpContext(gfx)->Unmap(pConstantBuffer.Get(), 0u);
	}
};

