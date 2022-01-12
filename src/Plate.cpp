#include "Plate.h"
//#include "..\Headers\Plate.h"
#include <DirectXMath.h>
#include "ShaderObjects.h"


namespace  wrl = Microsoft::WRL;
Plate::Plate(Graphics& gfx) noexcept
	:Drawable(gfx)
{
	struct Vertex
	{
		float x;
		float y;
		unsigned char r;
		unsigned char g;
		unsigned char b;
		unsigned char a;
	};
	// create a  triangle 
	std::vector<Vertex> verticies = {
		{0.05f, 0.05f, 255, 255, 255, 255},
		{0.05f, 0.0f, 0, 255, 255, 255},
		{ -0.25f, 0.0f, 255, 0, 255, 255},
		{-0.25f, 0.05f, 255, 255, 0, 255}
	};
	//short int indicies
	std::vector<short> indicies = {
		0,1,2,
		3,0,2
	};
	nverticies = (UINT)indicies.size();
	IndBuffer<short> Ibuffer(gfx, pIndexBuffer, indicies);

	VertexBuffer<Vertex> Vbuffer(gfx, pVertexbuffer, verticies);

	stride = sizeof(Vertex);

	/*
	// create index buffer
	D3D11_BUFFER_DESC indexDscr{};
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

	GetpDevice()->CreateBuffer(&indexDscr, &indexData, &pIndexBuffer);*/

	/*
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

	GFX_CHECK_ERROR(D3DReadFileToBlob(L"PlatePixelShader.cso", &pBlob));

	GFX_CHECK_ERROR(GetpDevice()->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPshader));

	GFX_CHECK_ERROR(D3DReadFileToBlob(L"PlateVertexShader.cso", &pBlob));

	GFX_CHECK_ERROR(GetpDevice()->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVshader));

	// input layout

	const D3D11_INPUT_ELEMENT_DESC iedesc[] = {
		{"POSITION",0,DXGI_FORMAT_R32G32_FLOAT,0,0, D3D11_INPUT_PER_VERTEX_DATA,0},
		{"COLOR",0, DXGI_FORMAT_R8G8B8A8_UNORM,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA,0}

	};
	GFX_CHECK_ERROR(GetpDevice()->CreateInputLayout(iedesc, (UINT)std::size(iedesc), pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &pinputLayout));

	struct TransformBuffer {

		DirectX::XMMATRIX transform;
	};
	const TransformBuffer tbuffer = {
		{
			DirectX::XMMatrixTranspose(
			DirectX::XMMatrixTranslation(0.f,0.f,0.f))

		}
	};
	/*wrl::ComPtr<ID3D11Buffer>  pTBuffer;
	D3D11_SUBRESOURCE_DATA transformData;
	transformData.pSysMem = &tbuffer;
	D3D11_BUFFER_DESC transformDescr{};
	transformDescr.ByteWidth = sizeof(TransformBuffer);
	transformDescr.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	transformDescr.Usage = D3D11_USAGE_DYNAMIC;
	transformDescr.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	transformDescr.MiscFlags = 0;

	GFX_CHECK_ERROR(GetpDevice()->CreateBuffer(&transformDescr, &transformData, &pTBuffer));*/


	struct Cbuffer
	{
		DirectX::XMMATRIX transforms;
	};
	
	float x = 0.f;
	float y = 0.f;
	const Cbuffer cb =
	{
		{DirectX::XMMatrixTranspose(DirectX::XMMatrixTranslation(x, -0.75f, 0.f))}
	};
	/*D3D11_BUFFER_DESC cbufferDescr{};
	cbufferDescr.ByteWidth = sizeof(cb);
	cbufferDescr.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbufferDescr.MiscFlags = 0;
	cbufferDescr.Usage = D3D11_USAGE_DYNAMIC;
	cbufferDescr.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbufferDescr.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA  cbData{};
	cbData.pSysMem = &cb;
	cbData.SysMemPitch = 0;
	cbData.SysMemSlicePitch = 0;
	GFX_CHECK_ERROR(GetpDevice()->CreateBuffer(&cbufferDescr, &cbData, &pTransformbuffer));*/
	ConstantBuffer<Cbuffer> moveBuffer(gfx, pTransformbuffer, cb);
}

void Plate::UpdatePos(float limit)
{
	float transform_x = move_plate_val;

	if (move_plate_val + 0.05f > limit)
	{
		transform_x = limit - 0.05f;
		move_plate_val = transform_x;


	}
	else if (move_plate_val - 0.25f < -1.f)
	{
		transform_x = -1.f + 0.25f;
		move_plate_val = transform_x;

	}
	struct Cbuffer
	{
		DirectX::XMMATRIX transforms;
	};
	const Cbuffer cb =
	{
		{DirectX::XMMatrixTranspose(DirectX::XMMatrixTranslation(transform_x, -0.75f, 0.f))}
	};

	ConstantBuffer<Cbuffer>::UpdateBuffer(pGfx, pTransformbuffer, cb);
	/*D3D11_MAPPED_SUBRESOURCE msr;
	GetpContext()->Map(pTransformbuffer.Get(), 0u, D3D11_MAP_WRITE_DISCARD, 0u, &msr);
	memcpy(msr.pData, &cb, sizeof(cb));
	GetpContext()->Unmap(pTransformbuffer.Get(), 0u);*/

}

void Plate::MovePlate(Window& wnd, float limit)
{
	;
	auto kb_event = wnd.kb.GetKeysEvent();
	if (kb_event.Unicode == VK_RIGHT) {

		move_plate_val += 0.05f;
		UpdatePos(limit);
	}
	else if (kb_event.Unicode == VK_LEFT)
	{
		move_plate_val -= 0.05f;
		UpdatePos(limit);

	}
}

void Plate::Draw()
{
	const UINT offset = 0u;

	GetpContext()->IASetVertexBuffers(0u, 1u, pVertexbuffer.GetAddressOf(), &stride, &offset);
	GetpContext()->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
	GetpContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	GetpContext()->PSSetShader(pPshader.Get(), nullptr, 0u);
	GetpContext()->VSSetShader(pVshader.Get(), nullptr, 0);
	GetpContext()->IASetInputLayout(pinputLayout.Get());
	/*GetpContext()->VSSetConstantBuffers(0, 1u, pTBuffer.GetAddressOf());*/
	GetpContext()->VSSetConstantBuffers(0, 1u, pTransformbuffer.GetAddressOf());
	GetpContext()->DrawIndexed(nverticies, 0u, 0u);
}
