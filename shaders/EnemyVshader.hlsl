
cbuffer enemyTransform {

	matrix transform;
};
float4 main( float4 pos : POSITION ) : SV_POSITION
{
	
	return mul(float4(pos.x, pos.y, 0, 1.0f), transform);
}