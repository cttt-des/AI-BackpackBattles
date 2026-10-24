shader_type canvas_item;

uniform float wobbliness : hint_range(0, 1) = 0.5;
uniform float centralityFactor : hint_range(0, 4) = 2.0;

uniform sampler2D gradient;
uniform sampler2D thicknessCurve;
//uniform sampler2D intensityCurve;

uniform sampler2D NOISE_PATTERN;
uniform sampler2D NOISE_PATTERN2;

uniform vec2 scroll1 = vec2(1 , 0.4);
uniform vec2 scroll2 = vec2(0.2, 1.2);
uniform float yStretch = 0.1;
uniform float xStretch = 1.0;

void fragment() {
	float laserSize = MODULATE.a; 
	vec2 stretched_UV = UV;
	stretched_UV.y *= yStretch;
	stretched_UV.x *= xStretch;

	float intensity1 = texture(NOISE_PATTERN, stretched_UV + TIME * scroll1).r;
	float intensity2 = texture(NOISE_PATTERN2, stretched_UV + TIME * scroll2).r;
	float intensity = intensity1 * intensity2;
	
	float centrality = (1.0 - abs(UV.y - 0.5))* 0.5;
	float thickness = texture(thicknessCurve, UV).r;
	
	//float intensityFromCurve = texture(intensityCurve, UV).r;
	//centrality *= intensityFromCurve;
	
	float total = (intensity * wobbliness + centrality * centrality * centralityFactor + laserSize);
	
	COLOR = texture(gradient, vec2(total * thickness));
	COLOR.rgb *= MODULATE.rgb;
}