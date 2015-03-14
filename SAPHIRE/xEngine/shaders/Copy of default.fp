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

uniform sampler2D Texture0;
uniform sampler2D Texture1;
uniform sampler2D Texture2;


void main(void)
{

	vVaryingColor = diffuseColor;
	vVaryingColor = texture(Texture0,vUV);
	
	float diff = max(0.0,dot(normalize(vVaryingNormal),normalize(vVaryingLightDir)));
	vVaryingColor *= diff;
	vVaryingColor += ambientColor;	

	
	vec3 vReflection = normalize(reflect(-normalize(vVaryingLightDir),normalize(vVaryingNormal)));
		
	float spec = max(0.0,dot(normalize(vVaryingNormal),vReflection));
	
	if( diff  !=  0) {
		float fSpec = pow(spec,128.0);
		vVaryingColor.rgb += vec3(fSpec,fSpec,fSpec);	
	} else {
		vVaryingColor = normalize(vec4(vVaryingLightDir,1))*diffuseColor+ambientColor;
	}	
	
	vVaryingColor.rgb += vec3(0.1,0.1,0.1);
}

	
	

		
