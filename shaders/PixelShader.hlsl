cbuffer ColorBuffer {
	float4 colors;
};
float4 main(float4 colors : COLOR) : SV_TARGET
{
	return colors;//float4(0.5f,0.f,1.f,1.0f);
}