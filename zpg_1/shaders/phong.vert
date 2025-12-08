#version 400
layout(location=0) in vec3 vp;
layout(location=1) in vec3 vn;
layout(location=2) in vec2 vt;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float w; // třeba w = 500
uniform bool useGeneratedUv;
out vec3 worldPos;
out vec3 worldNorm;
out vec2 textCoord;

const float PI = 3.14159265359;

void main () {
	worldPos = vec3(model * vec4(vp, 1.0));
	worldNorm = normalize(transpose(inverse(mat3(model))) * vn);
	if(useGeneratedUv)
	{
		vec3 d = normalize(vp); 
        	float u = 0.5 - atan(d.z, d.x) / (2.0 * PI);
        	float v = 0.5 + asin(d.y) / PI;
       		textCoord = vec2(u, v);
	}
	else {
		textCoord = vt;
	}

	gl_Position = projection * view * model * vec4(w * vp, w);
}