#include "LimitLine.h"
#include "ShaderObjects.h"

namespace wrl = Microsoft::WRL;
LimitLine::LimitLine(Graphics& gfx)
	:Drawable(gfx)
{
	struct Vertex {
		float x;
		float y;
		unsigned char r;
		unsigned char g;
		unsigned char b;
		unsigned char a;
	};
	limit_x = 0.80f;
	std::vector<Vertex> verticies = {
		{limit_x, 1.f, 255, 255, 255, 255},
		{0.85f, 1.0f, 0, 255, 255, 255},
		{0.85f, -1.0f, 255, 0, 255, 255},
		{limit_x, -1.f, 255, 255, 0, 255}
	};

	//short int indicies
	std::vector<short> indicies = {
		0,1,2,
		3,0,2
	};
	nverticies = (UINT)std::size(indicies);
	IndBuffer<short> Ibuffer(gfx, pIndexBuffer, indicies);

	VertexBuffer<Vertex> Vbuffer(gfx, pVertexbuffer, verticies);
	stride = sizeof(Vertex);


	// create index buffer
	/*D3D11_BUFFER_DESC indexDscr{};
	indexDscr.ByteWidth = sizeof(indicies);
	indexDscr.Usage = D3D11_USAGE_DEFAULT;
	indexDscr.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexDscr.CPUAccessFlags = 0;
	indexDscr.MiscFlags = 0;
	indexDscr.StructureByteStride = sizeof(short int);

	D3D11_SUBRESOURCE_DATA indexData;
	indexData.pSysMem = indicies;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	GetpDevice()->CreateBuffer(&indexDscr, &indexData, &pIndexBuffer);

	// create a buffer
	D3D11_BUFFER_DESC vertexDescr{};
	vertexDescr.ByteWidth = sizeof(verticies);
	vertexDescr.Usage = D3D11_USAGE_DEFAULT;
	vertexDescr.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexDescr.CPUAccessFlags = 0;
	vertexDescr.StructureByteStride = sizeof(Vertex);
	vertexDescr.MiscFlags = 0u;
	// fill the vertex buffer with data 
	D3D11_SUBRESOURCE_DATA vertexData{};
	vertexData.pSysMem = verticies;
	/*vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;*/
	//GFX_CHECK_ERROR(GetpDevice()->CreateBuffer(&vertexDescr, &vertexData, &pVertexbuffer));


	// shaders
	wrl::ComPtr<ID3DBlob> pBlob;

	GFX_CHECK_ERROR(D3DReadFileToBlob(L"LimitPShader.cso", &pBlob));

	GFX_CHECK_ERROR(GetpDevice()->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPshader));

	GFX_CHECK_ERROR(D3DReadFileToBlob(L"LimitVshader.cso", &pBlob));

	GFX_CHECK_ERROR(GetpDevice()->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVshader));

	// input layout

	const D3D11_INPUT_ELEMENT_DESC iedesc[] = {
		{"POSITION",0,DXGI_FORMAT_R32G32_FLOAT,0,0, D3D11_INPUT_PER_VERTEX_DATA,0},
		{"COLOR",0, DXGI_FORMAT_R8G8B8A8_UNORM,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA,0}
	};
	GFX_CHECK_ERROR(GetpDevice()->CreateInputLayout(iedesc, (UINT)std::size(iedesc), pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &pinputLayout));
}

void LimitLine::Draw()
{
	const UINT offset = 0u;

	GetpContext()->IASetVertexBuffers(0u, 1u, pVertexbuffer.GetAddressOf(), &stride, &offset);
	GetpContext()->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
	GetpContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	GetpContext()->PSSetShader(pPshader.Get(), nullptr, 0u);
	GetpContext()->VSSetShader(pVshader.Get(), nullptr, 0);
	GetpContext()->IASetInputLayout(pinputLayout.Get());
	/*GetpContext()->VSSetConstantBuffers(0, 1u, pTBuffer.GetAddressOf());*/
	//GetpContext()->VSSetConstantBuffers(0, 1u, pTransformbuffer.GetAddressOf());
	GetpContext()->DrawIndexed(nverticies, 0u, 0u);
}

float LimitLine::getLimitX()
{
	return limit_x;
}

void LimitLine::UpdatePos(float limit)
{
}
