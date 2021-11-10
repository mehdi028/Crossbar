#include "Enemy.h"
#include <DirectXMath.h>

namespace wrl = Microsoft::WRL;
Enemy::Enemy(Graphics& gfx)
	:Drawable(gfx)
{
	struct Vertex {
		float x;
		float y;
	};
	Vertex verticies[] = {
		{0.05f, 0.05f},
		{0.05f, 0.0f},
		{-0.25f, 0.0f},
		{-0.25f, 0.05f}
	};
	
	//short int indicies
	short indicies[] = {
		0,1,2,
		3,0,2
	};
	nverticies = (UINT)std::size(indicies);
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
	GFX_CHECK_ERROR(GetpDevice()->CreateBuffer(&vertexDescr, &vertexData, &pStructure));
	stride = sizeof(Vertex);
	

	// shaders
	wrl::ComPtr<ID3DBlob> pBlob;
	
	GFX_CHECK_ERROR(D3DReadFileToBlob(L"EnemyPShader.cso", &pBlob));

	GFX_CHECK_ERROR(GetpDevice()->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPshader));
	

	

	GFX_CHECK_ERROR(D3DReadFileToBlob(L"EnemyVshader.cso", &pBlob));

	GFX_CHECK_ERROR(GetpDevice()->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVshader));
	
	// input layout
	
	const D3D11_INPUT_ELEMENT_DESC iedesc[] = {
		{"POSITION",0,DXGI_FORMAT_R32G32_FLOAT,0,0, D3D11_INPUT_PER_VERTEX_DATA,0}
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
	wrl::ComPtr<ID3D11Buffer>  pTBuffer;
	D3D11_SUBRESOURCE_DATA transformData;
	transformData.pSysMem = &tbuffer;
	D3D11_BUFFER_DESC transformDescr{};
	transformDescr.ByteWidth = sizeof(TransformBuffer);
	transformDescr.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	transformDescr.Usage = D3D11_USAGE_DYNAMIC;
	transformDescr.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	transformDescr.MiscFlags = 0;

	GFX_CHECK_ERROR(GetpDevice()->CreateBuffer(&transformDescr, &transformData, &pTBuffer));
	

	struct Cbuffer
	{
		DirectX::XMMATRIX transforms;
	};
	 // use current time as seed for random generator
	int random_variable1 = std::rand();
	std::ostringstream ss;
	
	int switches =  (random_variable1 % 10);
	ss << switches << "\n";
	OutputDebugStringA(ss.str().c_str());
	int random_variable2 = std::rand();
	float y;
	float x;
	switch (switches % 5)
	{
	case 0: x = 0.0f; y = 0.8f; break;
	case 1: x = 0.3f; y = 0.5f; break;
	case 2: x = -0.4f; y = -0.2f; break;
	case 3: x = -0.7f; y = -0.6f; break;
	case 4: x = 1.0f; y = 0.8f; break;
	default: x = 0.0f; y = 0.0f; break;
	}
	std::ostringstream sss;
	sss << x << "," << y << "\n";
	OutputDebugStringA(sss.str().c_str());

	const Cbuffer cb =
	{
		{DirectX::XMMatrixTranspose(DirectX::XMMatrixTranslation(x, y, 0.f))}
	};
	D3D11_BUFFER_DESC cbufferDescr{};
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
	GFX_CHECK_ERROR(GetpDevice()->CreateBuffer(&cbufferDescr, &cbData, &pTransformbuffer));
	
}

void Enemy::Draw()
{
	
	const UINT offset = 0u;

	GetpContext()->IASetVertexBuffers(0u, 1u, pStructure.GetAddressOf(), &stride, &offset);
	GetpContext()->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
	GetpContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	GetpContext()->PSSetShader(pPshader.Get(), nullptr, 0u);
	GetpContext()->VSSetShader(pVshader.Get(), nullptr, 0);
	GetpContext()->IASetInputLayout(pinputLayout.Get());
	/*GetpContext()->VSSetConstantBuffers(0, 1u, pTBuffer.GetAddressOf());*/
	GetpContext()->VSSetConstantBuffers(0, 1u, pTransformbuffer.GetAddressOf());
	GetpContext()->DrawIndexed(nverticies, 0u, 0u);
}
