shader_type canvas_item;

uniform sampler2D overlapGradient;
uniform sampler2D tex2;
uniform vec2 scroll1 = vec2(0.2, -0.3);
uniform vec2 scroll2 = vec2(0.1, -0.4);
uniform float tex2_scale = 0.5;
uniform float tex1_scale = 1.0;
varying float particleId;

void vertex(){
	particleId = INSTANCE_CUSTOM.z;
	
}


void fragment() {
	
	float adjustedTime = TIME + particleId * 11374.293247;
	float tex1_intensity = texture(tex2, tex1_scale * (UV + adjustedTime * scroll1)).r;
	float tex2_intensity = texture(tex2, tex2_scale * (UV + adjustedTime * scroll2)).r;
	float mask = texture(TEXTURE,UV).r;
	float intensity = tex1_intensity * tex2_intensity * mask * COLOR.a * MODULATE.a;
	vec4 overlapColor = texture(overlapGradient, vec2(intensity * 2.0));
	COLOR.a = 1.0; // already used in intensity
	COLOR.rgb *= MODULATE.rgb;
	COLOR *= overlapColor;

}