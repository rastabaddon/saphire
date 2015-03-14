 struct VertexData {
  
    float4 color : COLOR; //vertex color
    
    //SAMPLERY
 	float4 UV0 : TEXCOORD0;	// !MUSI	//ZRODLO?
	uniform sampler2D texture0;

 	float4 UV1 : TEXCOORD1;	// !MUSI	//BLUR
	uniform sampler2D texture1;
	
 	float4 UV2 : TEXCOORD2;	// !MUSI	//CEL?
	uniform sampler2D texture2;
	
 	float4 UV3 : TEXCOORD3;	// !MUSI
	uniform sampler2D texture3;
	
	float4 pos : TEXCOORD4;
	
 };


struct PixelData {
    float4 color : COLOR; //Pixel color
  	
};

float4 allColor : COLOR2;
//Parametr1 - ekspozycja
//Parametr2 - adaptive - oko
PixelData main(VertexData IN,uniform float Parametr1,uniform float Parametr2)
{
	PixelData OUT;
	
	//Kolor usredniony
	
	
	
	//Horizontal
	float4 colorA = tex2D(IN.texture1, float2(IN.pos.x, IN.pos.y)); //Zrodlo
	float4 colorB = tex2D(IN.texture1, float2(IN.pos.x, IN.pos.y)); //Rozmycie
 	

	
	OUT.color = colorA+(colorB*Parametr2);
	
	return OUT;
}

