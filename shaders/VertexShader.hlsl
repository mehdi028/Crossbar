struct ToPixels {
	float4 col : MyCol;
	float4 positions : SV_POSITION;
	

};
cbuffer TransformBuff {
	matrix transform;
};
ToPixels main(float2 pos : POSITION, float4 colors : COLOR)
{
	ToPixels toPix ;
	toPix.positions = mul(float4(pos.x, pos.y, 0.0f, 1.f), transform); //float4(pos.x, pos.y, 0.0f, 1.f); //mul(float4(pos.x, pos.y, 0.0f, 1.f),transform);
	toPix.col = colors;
	return toPix ;
}