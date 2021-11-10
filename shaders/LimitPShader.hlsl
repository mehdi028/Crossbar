cbuffer ColorBuffer {
	float4 colors;
};
float4 main(float4 colors: MyCol) : SV_TARGET
{
	return colors;
}