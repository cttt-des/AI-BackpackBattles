shader_type canvas_item;

uniform sampler2D spriteSheet;
uniform float numFrames = 1;
uniform float whiteMix : hint_range(0.0, 2.0) = 0.5;
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
	float tex = texture(spriteSheet, adjustedUV).r;
	float energy = tex - (1.0-COLOR.a);
	//COLOR = vec4(COLOR.rgb + energy, COLOR.a - energy);// COLOR = particle lifetime gradient+initial ramp
	COLOR = vec4(mix(COLOR.rgb, vec3(1,1,1), energy * energy * whiteMix), clamp(energy, 0.0 , 1.0));// COLOR = particle lifetime gradient+initial ramp
} 