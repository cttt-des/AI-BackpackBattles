shader_type canvas_item;

uniform sampler2D noise1;
uniform vec2 scroll1 = vec2(0.05, 0.05);
uniform vec2 scroll2 = vec2(0.05, 0.05);
uniform float waterStr : hint_range(-.1, .1) = 0.01;
//uniform sampler2D topLights;
//uniform sampler2D tone;
uniform float scaleFactor : hint_range(0, 4) = 0.5;
uniform float topLightStart : hint_range(0, 1) = 0.3;
uniform float topLightEnd : hint_range(0, 1) = 0.4;
//uniform float distortionScaleFactor1 : hint_range(-2, 2) = 0.5;
//uniform float distortionScaleFactor2 : hint_range(-2, 2) = 0.5;

uniform vec4 topLightsColor : hint_color = vec4(0,0, 1, 1);
uniform vec4 toneColor : hint_color = vec4(0,0, 1, 1);
const vec3 elecColor = vec3(.9, .9, .2);

void fragment() {
	vec2 perspectiveUV = UV * vec2(1,1.5);
	vec4 tex = texture(TEXTURE, UV); // is this only used for alpha?
	
	vec2 scrolledUV1 = perspectiveUV + scroll1* TIME;
	vec2 scrolledUV2 = perspectiveUV + scroll2* TIME;
	float noise1Int =  texture(noise1, scrolledUV1).r;
	float noise2Int =  texture(noise1, scrolledUV2 * scaleFactor).r;
	float xdiff = (noise1Int + 0.1) * noise2Int ;
	float ydiff = noise1Int * (noise2Int + 0.1) ;
	
	vec4 screenRead = texture(SCREEN_TEXTURE, 
		SCREEN_UV+ (vec2(xdiff, ydiff)-0.25)* waterStr * tex.a);
	COLOR.rgb = screenRead.rgb;
	COLOR.a = tex.a * MODULATE.a;
	//COLOR.rgb = mix(screenRead.rgb, toneColor.rgb, toneColor.a);
	//float intensity = noise1Int * noise2Int;
	//vec4 topL = topLightsColor * smoothstep(topLightStart, topLightEnd, intensity);
	//COLOR.rgb += topL.rgb;
	//COLOR.a = MODULATE.a;
	//COLOR.rgb += elecColor * step(0.21, xdiff)* step(ydiff, 0.22) * 1.0;
}