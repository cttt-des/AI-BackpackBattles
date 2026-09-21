shader_type canvas_item;

uniform sampler2D spriteSheet;
uniform sampler2D tonemapping;
uniform float numFrames = 1;

//varying float lifetime;
varying float animationOffset;

void vertex() {
	//lifetime = INSTANCE_CUSTOM.y;
	animationOffset = floor(INSTANCE_CUSTOM.z * numFrames) / numFrames;
}

void fragment() {
	vec2 adjustedUV = UV;
	adjustedUV.x /= numFrames;
	adjustedUV.x += animationOffset;
	vec4 tex = texture(spriteSheet, adjustedUV);
	float intensity = tex.r * tex.a;
	vec4 grad = texture(tonemapping, vec2(intensity - (1.0-COLOR.a)));
	COLOR = vec4(grad.rgb * COLOR.rgb, grad.a);// COLOR = particle lifetime gradient+initial ramp
} 