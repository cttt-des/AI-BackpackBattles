shader_type canvas_item;

uniform sampler2D tone_mapping;

uniform sampler2D NOISE_PATTERN;
uniform sampler2D NOISE_PATTERN2;
uniform vec2 scroll1 = vec2(1 , 0.4);
uniform vec2 scroll2 = vec2(0.2, 1.2);

uniform float baseIntensity : hint_range(-0.5,1.0) = 0.1;
uniform float intensityFactor : hint_range(-0.5,5.0) = 1.5;

uniform vec2 noise1Scale = vec2(1,1);
uniform vec2 noise2Scale = vec2(1,1);

uniform float staticFactor : hint_range(-1,1) = 0.5;

uniform sampler2D overlayTexture;


void fragment() {
	vec4 texVal = texture(TEXTURE, UV);
	vec4 overlayVal = texture(overlayTexture, UV);
	
	float texAlpha = texVal.a;
	
	float adjustedTime = TIME * MODULATE.a;
	
	float intensity1 = texture(NOISE_PATTERN, UV * noise1Scale + adjustedTime * scroll1).r;
	float intensity2 = texture(NOISE_PATTERN2, UV * noise2Scale + adjustedTime * scroll2).r;
	float intensity = ((intensity1 * intensity2) + baseIntensity+ texVal.r * staticFactor) * intensityFactor * texAlpha;
	intensity = intensity * (0.8 + overlayVal.r * overlayVal.a * 0.6);
	COLOR = texture(tone_mapping, vec2(intensity));
	
	COLOR.rgb += overlayVal.rgb * overlayVal.a * 0.4 * overlayVal.a * overlayVal.a;
	COLOR.rgb *= MODULATE.rgb;
}