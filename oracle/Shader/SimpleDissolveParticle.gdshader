shader_type canvas_item;

//uniform float blur : hint_range(0,10) = 5.0;
uniform sampler2D tonemapping;
//uniform float numFrames = 1;
//uniform float textureFactor : hint_range(0,2) = 1.0;

//varying float lifetime;
//
//void vertex() {
//	lifetime = INSTANCE_CUSTOM.y;
//}

void fragment() {
	float tex = texture(TEXTURE, UV).r;
	vec4 grad = texture(tonemapping, vec2(tex - (1.0 - COLOR.a)));
	COLOR = vec4(grad.rgb * COLOR.rgb, grad.a); // COLOR = particle lifetime gradient+initial ramp
} 