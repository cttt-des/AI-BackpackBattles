shader_type canvas_item;

uniform float progress : hint_range(-1, 2) = 0.5;
uniform vec2 direction = vec2(0, 1);
uniform vec2 atlasTranslation;
uniform vec2 atlasScaling;
uniform vec2 scale = vec2(1,1);
uniform sampler2D noise;
uniform float thickness = 0.05;
uniform float whiteness : hint_range(0, 1) = 0.05;

void fragment() {
	COLOR = texture(TEXTURE, UV);
	//if (progress != 0.0) {
	vec2 atlasUV = (UV - atlasTranslation) / atlasScaling;
	float noiseVal = texture(noise, atlasUV * scale).r;
	float borderBonus = noiseVal * 2.0 * thickness;
	float p = progress + borderBonus;
	//COLOR.rgb = vec3(atlasUV.xy, 0);
	float rotatedV = dot(atlasUV, direction);
	//COLOR.rgb *= 1.0 + 0.5 * smoothstep(p - 0.05, p + 0.05, rotatedV);
	if (rotatedV > p) {
//		float dist = rotatedV - p;
//		if (dist < thickness) {
//			//COLOR.rgb *= 1.5;
//			//COLOR.rgb += borderBrightness_flat + noiseVal * borderBrightness_noise;
//			//COLOR.rgb += borderBrightness_flat*(thickness-dist) + noiseVal * borderBrightness_noise;
//			//COLOR.rgb = mix(COLOR.rgb, vec3(1,1,1), borderBrightness_flat*(thickness-dist));
//		}
//		else {
//		}
		COLOR.rgb = mix(COLOR.rgb, vec3(1,1,1), whiteness);
		COLOR.rgb *= 1.5;
	}
}