struct ToPixels {
	float4 col : MyCol;
	float4 positions : SV_POSITION;


};
ToPixels main(float4 pos : POSITION, float4 colors : COLOR) //: SV_POSITION
{
	ToPixels topixel;
	topixel.col = colors;
	topixel.positions = pos;

	return topixel;
}