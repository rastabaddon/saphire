#version 330 

out vec4 vVaryingColor;

//COLORS
uniform vec4 ambientColor;
uniform vec4 diffuseColor;
uniform vec4 specularColor;

smooth in vec4 vColor;
smooth in vec3 vVaryingNormal;
smooth in vec3 vVaryingLightDir;
smooth in vec2 vUV;
smooth in vec3 vVaryingLight;
varying vec2 texPos;

uniform sampler2D Texture0;
uniform sampler2D Texture1;
uniform sampler2D Texture2;
uniform sampler2D Texture3;

void main(void)
{

	vVaryingColor = vColor;
	vVaryingColor *= texture(Texture0,texPos);
	//vVaryingColor *= texture(Texture1,texPos);
	//vVaryingColor *= texture(Texture2,texPos);
	//vVaryingColor *= texture(Texture3,texPos);
	
	
	//guardian shade ================================
	
	float diff = max(0.0,dot(normalize(vVaryingNormal),normalize(vVaryingLightDir)));
	vec3 vReflection = normalize(reflect(-normalize(vVaryingLightDir),normalize(vVaryingNormal)));
		
	float spec = max(0.0,dot(normalize(vVaryingNormal),vReflection));
	
	if( diff  !=  0) {
		vVaryingColor += diffuseColor;
		float fSpec = pow(spec,1.1);
		vVaryingColor.rgb += vec3(fSpec,fSpec,fSpec);
		
	} else {
		 vVaryingColor = normalize(vec4(vVaryingLightDir,1))*ambientColor;


		float fSpec = pow(spec,1);
		vVaryingColor.rgb -= vec3(fSpec,fSpec,fSpec);
		vVaryingColor.rgb -= vec3(1.9,1.9,1.9);	
	}	
	
	//guardian shade ================================
	
	//Light to dark
		vVaryingColor.rgb -= vec3(1,1,1);	
}

	
	

		
