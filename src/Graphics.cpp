#include "Graphics.h"
#include<DirectXMath.h>

namespace  wrl = Microsoft::WRL;

Graphics::Graphics(const HWND& hwnd)
{
	// swap chain descriptor
	DXGI_SWAP_CHAIN_DESC swapDesc{};
	swapDesc.BufferDesc.Width = 0;
	swapDesc.BufferDesc.Height = 0;
	swapDesc.BufferDesc.RefreshRate.Numerator = 0;
	swapDesc.BufferDesc.RefreshRate.Denominator = 0;
	swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; 
	swapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapDesc.SampleDesc.Count = 1;
	swapDesc.SampleDesc.Quality = 0;
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapDesc.OutputWindow = hwnd;
	swapDesc.BufferCount = 1;
	swapDesc.Windowed = TRUE;
	

	GFX_CHECK_ERROR(D3D11CreateDeviceAndSwapChain(0, D3D_DRIVER_TYPE_HARDWARE, NULL, D3D11_CREATE_DEVICE_DEBUG,
		NULL, 0, D3D11_SDK_VERSION, &swapDesc, &PSwapChain, &pDevice, nullptr, &pContext));

	wrl::ComPtr<ID3D11Texture2D> pBackBuffer;
	// get index on thebackbuffer
	GFX_CHECK_ERROR(PSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &pBackBuffer));
	D3D11_RENDER_TARGET_VIEW_DESC renderDescr{};
	
	GFX_CHECK_ERROR(pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &pRendTargetView));

	pContext->OMSetRenderTargets(1, pRendTargetView.GetAddressOf(), NULL);

	D3D11_VIEWPORT vp;
	vp.Width = 800;
	vp.Height = 600;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	pContext->RSSetViewports(1, &vp);
	

}

void Graphics::ClearRendered()
{
	
	/*std::ostringstream ss;
	ss << timer.Peek() <<"\n";
	OutputDebugStringA(ss.str().c_str());*/
	
	float colors[] = { 0,0,0, 1 };
	pContext->ClearRenderTargetView(pRendTargetView.Get(), colors);
	
	
}

void Graphics::PresentFrame()
{
	GFX_CHECK_ERROR(PSwapChain->Present(0u, 0u));
}

void Graphics::drawEnemy()
{
	struct Vertex {
		float x;
		float y;
	};

	Vertex enime_triangles[] = {
	{0.05f, 0.05f},
	 {0.05f, 0.0f},
	{-0.25f, 0.0f}
	};

	short indicies[] = {
		0,1,2,
		3,0,2
	};
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
	wrl::ComPtr<ID3D11Buffer> pIndexBuffer;
	pDevice->CreateBuffer(&indexDscr, &indexData, &pIndexBuffer);
	pContext->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);

	// create a buffer
	wrl::ComPtr<ID3D11Buffer> pvBuffer;
	D3D11_BUFFER_DESC vertexDescr{};
	vertexDescr.ByteWidth = sizeof(enime_triangles);
	vertexDescr.Usage = D3D11_USAGE_DEFAULT;
	vertexDescr.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexDescr.CPUAccessFlags = 0;
	vertexDescr.StructureByteStride = sizeof(Vertex);
	vertexDescr.MiscFlags = 0u;
	// fill the vertex buffer with data 
	D3D11_SUBRESOURCE_DATA vertexData{};
	vertexData.pSysMem = enime_triangles;
	/*vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;*/
	GFX_CHECK_ERROR(pDevice->CreateBuffer(&vertexDescr, &vertexData, &pvBuffer));

	const UINT stride = sizeof(Vertex);
	const UINT offset = 0u;

	pContext->IASetVertexBuffers(0u, 1u, pvBuffer.GetAddressOf(), &stride, &offset);
	pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// pixel shader 
	wrl::ComPtr<ID3DBlob> pBlob;
	wrl::ComPtr<ID3D11PixelShader> pPshader;
	GFX_CHECK_ERROR(D3DReadFileToBlob(L"PixelShader.cso", &pBlob));

	GFX_CHECK_ERROR(pDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPshader));
	pContext->PSSetShader(pPshader.Get(), nullptr, 0u);

	wrl::ComPtr<ID3D11VertexShader> pVshader;

	GFX_CHECK_ERROR(D3DReadFileToBlob(L"VertexShader.cso", &pBlob));

	GFX_CHECK_ERROR(pDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVshader));
	pContext->VSSetShader(pVshader.Get(), nullptr, 0);
	// input layout
	wrl::ComPtr<ID3D11InputLayout> pinputLayout;
	const D3D11_INPUT_ELEMENT_DESC iedesc[] = {
		{"POSITION",0,DXGI_FORMAT_R32G32_FLOAT,0,0, D3D11_INPUT_PER_VERTEX_DATA,0},
		/*{"COLOR",0, DXGI_FORMAT_R8G8B8A8_UNORM,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA,0}*/
	};
	GFX_CHECK_ERROR(pDevice->CreateInputLayout(iedesc, (UINT)std::size(iedesc), pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &pinputLayout));

	pContext->IASetInputLayout(pinputLayout.Get());
	


}
void Graphics::DrawTriangle(const float& x, const float& y, float angle)
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
	Vertex verticies[] = {
		{0.05f, 0.05f, 255, 255, 255, 255},
		{0.05f, 0.0f, 0, 255, 255, 255},
		{ -0.25f, 0.0f, 255, 0, 255, 255},
		{-0.25f, 0.05f, 255, 255, 0, 255}
	};
	//short int indicies
	short indicies[] = {
		0,1,2,
		3,0,2
	};
	float transform_x = x;
	
	if (x +0.05f > 1.f)
	{
		transform_x = 1.f -0.05f;


	}
	if (x - 0.25f < -1.f)
	{
		transform_x = -1.f +0.25f;

	}
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
	wrl::ComPtr<ID3D11Buffer> pIndexBuffer;
	pDevice->CreateBuffer(&indexDscr, &indexData, &pIndexBuffer);
	pContext->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);

	// create a buffer
	wrl::ComPtr<ID3D11Buffer> pvBuffer;
	D3D11_BUFFER_DESC vertexDescr{};
	vertexDescr.ByteWidth = sizeof(verticies) ;
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
	GFX_CHECK_ERROR(pDevice->CreateBuffer(&vertexDescr,&vertexData, &pvBuffer));
	
	const UINT stride = sizeof(Vertex);
	const UINT offset = 0u;

	pContext->IASetVertexBuffers(0u, 1u, pvBuffer.GetAddressOf(), &stride,&offset);
	pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// pixel shader 
	wrl::ComPtr<ID3DBlob> pBlob;
	wrl::ComPtr<ID3D11PixelShader> pPshader;
	GFX_CHECK_ERROR(D3DReadFileToBlob(L"PixelShader.cso", &pBlob));

	GFX_CHECK_ERROR(pDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPshader));
	pContext->PSSetShader(pPshader.Get(), nullptr, 0u);

	wrl::ComPtr<ID3D11VertexShader> pVshader;
	
	GFX_CHECK_ERROR(D3DReadFileToBlob(L"VertexShader.cso", &pBlob));

	GFX_CHECK_ERROR(pDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(),nullptr, &pVshader));
	pContext->VSSetShader(pVshader.Get(), nullptr, 0);
	// input layout
	wrl::ComPtr<ID3D11InputLayout> pinputLayout;
	const D3D11_INPUT_ELEMENT_DESC iedesc[] = {
		{"POSITION",0,DXGI_FORMAT_R32G32_FLOAT,0,0, D3D11_INPUT_PER_VERTEX_DATA,0},
		{"COLOR",0, DXGI_FORMAT_R8G8B8A8_UNORM,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA,0}
	};
	GFX_CHECK_ERROR( pDevice->CreateInputLayout(iedesc, (UINT)std::size(iedesc), pBlob->GetBufferPointer(),pBlob->GetBufferSize(), &pinputLayout));

	pContext->IASetInputLayout(pinputLayout.Get());
	
	// const buffer 
	struct ColorBuffer {
		float color[4];
		
	};
	wrl::ComPtr<ID3D11Buffer> pConstBuffer;
	D3D11_BUFFER_DESC cBufferDescr{};
	cBufferDescr.ByteWidth = sizeof(ColorBuffer);
	cBufferDescr.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cBufferDescr.Usage = D3D11_USAGE_DEFAULT;
	cBufferDescr.CPUAccessFlags = 0;
	cBufferDescr.MiscFlags = 0;
	cBufferDescr.StructureByteStride = sizeof(float);
	
	const ColorBuffer cbuffer = { {1.0f,1.0f,1.0f, 1.0f} };
	D3D11_SUBRESOURCE_DATA cdata;
	cdata.pSysMem = &cbuffer;
	cdata.SysMemPitch = 0;
	cdata.SysMemSlicePitch = 0;

	GFX_CHECK_ERROR( pDevice->CreateBuffer(&cBufferDescr, &cdata, &pConstBuffer));
	pContext->PSSetConstantBuffers(0u, 1u, pConstBuffer.GetAddressOf());
	
	struct TransformBuffer {

		DirectX::XMMATRIX transform;
	};
	const TransformBuffer tbuffer = {
		{
			DirectX::XMMatrixTranspose(
				DirectX::XMMatrixTranslation(transform_x,-0.75f,0.f))
			
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

	GFX_CHECK_ERROR(pDevice->CreateBuffer(&transformDescr, &transformData, &pTBuffer));
	pContext->VSSetConstantBuffers(0, 1u, pTBuffer.GetAddressOf());


	
	pContext->DrawIndexed((UINT) std::size(indicies),0u, 0u);



}
