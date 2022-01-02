#pragma once
#include<vector>
#include "Window.h"
#include <wrl.h>
#include "Bindable.h"
template<class T>
class IndBuffer
{
public:
	IndBuffer(Graphics& gfx, Microsoft::WRL::ComPtr<ID3D11Buffer>& pIndexbuffer, const std::vector<T>& indicies) noexcept {

		// create index buffer
		D3D11_BUFFER_DESC indexDscr{};
		indexDscr.ByteWidth = sizeof(T) * indicies.size();
		indexDscr.Usage = D3D11_USAGE_DEFAULT;
		indexDscr.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexDscr.CPUAccessFlags = 0;
		indexDscr.MiscFlags = 0;
		indexDscr.StructureByteStride = sizeof(short int);

		D3D11_SUBRESOURCE_DATA indexData;
		indexData.pSysMem = indicies.data();
		indexData.SysMemPitch = 0;
		indexData.SysMemSlicePitch = 0;

		GFX_CHECK_ERROR(Bindable::GetpDevice(gfx)->CreateBuffer(&indexDscr, &indexData, &pIndexbuffer));
	}
};

