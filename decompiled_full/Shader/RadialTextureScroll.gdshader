shader_type canvas_item;

uniform sampler2D tone_mapping;

uniform sampler2D NOISE_PATTERN;
uniform sampler2D NOISE_PATTERN2;
uniform vec2 scroll1 = vec2(1 , 0.4);
uniform vec2 scroll2 = vec2(0.2, 1.2);

uniform float baseIntensity : hint_range(0.0,0.5) = 0.1;
uniform float intensityFactor : hint_range(0.0,5.0) = 1.5;

uniform vec2 noise1Scale = vec2(1,1);
uniform vec2 noise2Scale = vec2(1,1);
uniform float blur : hint_range(0.0, 7.0) = 3.0;

uniform float staticFactor : hint_range(-1.2,1) = 0.5;

uniform float zoomLevel : hint_range(0.0, 10.0) = 1.;
uniform vec2 cen = vec2(0.5);

vec2 polar_coordinates(vec2 uv, vec2 center, float zoom, float repeat)
{
	vec2 dir = uv - center;
	float radius = length(dir) * 2.0;
	float angle = atan(dir.y, dir.x) * 1.0/(3.1416 * 2.0);
	return mod(vec2(radius * zoom, angle * repeat), 1.0);
}

void fragment() {
	vec2 polar_uv = polar_coordinates(UV.xy, cen, zoomLevel, 1.0);

	vec4 texVal = textureLod(TEXTURE, UV, blur);
	float texAlpha = texVal.a;
	
	float intensity1 = textureLod(NOISE_PATTERN, polar_uv * noise1Scale + TIME * scroll1, 0.0).r;
	float intensity2 = textureLod(NOISE_PATTERN2, polar_uv * noise2Scale + TIME * scroll2, 0.0).r;
	float intensity= ((intensity1 * intensity2) + baseIntensity+ texVal.r * staticFactor) * intensityFactor * texAlpha;
	
	COLOR = texture(tone_mapping, vec2(intensity));
}