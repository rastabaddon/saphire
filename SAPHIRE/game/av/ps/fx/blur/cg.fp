 struct VertexData {
  
    float4 color : COLOR; //vertex color
    
    //SAMPLERY
 	float4 UV0 : TEXCOORD0;	// !MUSI
	uniform sampler2D texture0;

 	float4 UV1 : TEXCOORD1;	// !MUSI
	uniform sampler2D texture1;
	
 	float4 UV2 : TEXCOORD2;	// !MUSI
	uniform sampler2D texture2;
	
 	float4 UV3 : TEXCOORD3;	// !MUSI
	uniform sampler2D texture3;
	
	float4 pos : TEXCOORD4;
	
 };


struct PixelData {

    float4 color : COLOR; //Pixel color
    
    

 };

const float blurSize = 1.0/512.0; 

PixelData main(VertexData IN,uniform float Parametr1,uniform float Parametr2)
{
	PixelData OUT;
	
	//Kolor usredniony
	float4 color = 0;
	
	//Horizontal
	
	color += tex2D(IN.texture0, float2(IN.pos.x - 4.0*blurSize, IN.pos.y)) * (0.05+Parametr1);
	color += tex2D(IN.texture0, float2(IN.pos.x - 3.0*blurSize, IN.pos.y)) * (0.09+Parametr1);
	color += tex2D(IN.texture0, float2(IN.pos.x - 2.0*blurSize, IN.pos.y)) * (0.12+Parametr1);
	color += tex2D(IN.texture0, float2(IN.pos.x - blurSize, IN.pos.y)) * (0.15+Parametr1);
	color += tex2D(IN.texture0, float2(IN.pos.x, IN.pos.y)) * (0.16+Parametr1);
	color += tex2D(IN.texture0, float2(IN.pos.x + blurSize, IN.pos.y)) * (0.15+Parametr1);
	color += tex2D(IN.texture0, float2(IN.pos.x + 2.0*blurSize, IN.pos.y)) * (0.12+Parametr1);
	color += tex2D(IN.texture0, float2(IN.pos.x + 3.0*blurSize, IN.pos.y)) * (0.09+Parametr1);
	color += tex2D(IN.texture0, float2(IN.pos.x + 4.0*blurSize, IN.pos.y)) * (0.05+Parametr1);
 
 	//vertical
 		
 	color += tex2D(IN.texture0, float2(IN.pos.x, IN.pos.y - 4.0*blurSize)) * (0.05+Parametr1);
    color += tex2D(IN.texture0, float2(IN.pos.x, IN.pos.y - 3.0*blurSize)) * (0.09+Parametr1);
    color += tex2D(IN.texture0, float2(IN.pos.x, IN.pos.y - 2.0*blurSize)) * (0.12+Parametr1);
    color += tex2D(IN.texture0, float2(IN.pos.x, IN.pos.y - blurSize)) * (0.15+Parametr1);
    color += tex2D(IN.texture0, float2(IN.pos.x, IN.pos.y)) * (0.16+Parametr1);
    color += tex2D(IN.texture0, float2(IN.pos.x, IN.pos.y + blurSize)) * (0.15+Parametr1);
    color += tex2D(IN.texture0, float2(IN.pos.x, IN.pos.y + 2.0*blurSize)) * (0.12+Parametr1);
    color += tex2D(IN.texture0, float2(IN.pos.x, IN.pos.y + 3.0*blurSize)) * (0.09+Parametr1);
    color += tex2D(IN.texture0, float2(IN.pos.x, IN.pos.y + 4.0*blurSize)) * (0.05+Parametr1);
 
 	
	OUT.color =  color;
	
	return OUT;
}

