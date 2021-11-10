#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(Graphics& Gfx, const std::vector<short int>& indicies) noexcept
	:Bindable(Gfx)
{
	nIndicies = (UINT) indicies.size();
	// create index buffer
	D3D11_BUFFER_DESC indexDscr{};
	indexDscr.ByteWidth = sizeof(indicies);
	indexDscr.Usage = D3D11_USAGE_DEFAULT;
	indexDscr.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexDscr.CPUAccessFlags = 0;
	indexDscr.MiscFlags = 0;
	indexDscr.StructureByteStride = sizeof(short int);

	D3D11_SUBRESOURCE_DATA indexData;
	indexData.pSysMem = &indicies;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	GFX_CHECK_ERROR(GetpDevice(Gfx)->CreateBuffer(&indexDscr, &indexData, &pIndexBuffer));

}

void IndexBuffer::Bind()
{
	GetpContext(gfx)->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0u);
}
