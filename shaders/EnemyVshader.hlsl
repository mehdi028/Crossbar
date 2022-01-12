struct ToPixels {
	float4 col : MyCol;
	float4 positions : SV_POSITION;


};
cbuffer enemyTransform {

	matrix transform;
};
ToPixels main(float2 pos : POSITION, float4 colors : COLOR) 
{
	ToPixels vertex;
vertex.positions = mul(float4(pos.x, pos.y, 0, 1.0f), transform);
vertex.col = colors;
	
	return vertex ;
}