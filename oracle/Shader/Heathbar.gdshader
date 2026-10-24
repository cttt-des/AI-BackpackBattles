shader_type canvas_item;

uniform sampler2D noise;
uniform sampler2D noise2;
uniform sampler2D gradientMapping;

uniform float healthPercentage : hint_range(-0.02, 1) = 1.0;
uniform float lastDamagePercentage : hint_range(-0.02, 1) = 1.0;

uniform vec2 scroll1 = vec2(0.05,0.05);
uniform vec2 scroll2 = vec2(-0.05,-0.05);
uniform vec2 scale1 = vec2(3,0.3);
uniform vec2 scale2 = vec2(1,0.1);

uniform vec4 damageDiffColor : hint_color = vec4(1,1,1,1);
uniform vec4 bonusDiffColor : hint_color = vec4(1,1,1,1);
const vec4 backgroundColor = vec4(0,0,0,1);

void fragment() {
	float adjustedTime = TIME * MODULATE.a;
	float noiseVal1 = texture(noise, UV * scale1 + adjustedTime * scroll1).r;
	float noiseVal2 = texture(noise2, UV * scale2 + adjustedTime * scroll2).r;
	float intensity = noiseVal1*noiseVal2;
	

	if (lastDamagePercentage > healthPercentage) {

	// is UV.x around hp?
	float isDamagePart = smoothstep(lastDamagePercentage-0.07, lastDamagePercentage+0.0, UV.x);
	float isDamageDiffPart = smoothstep(healthPercentage - 0.03, healthPercentage +0.03, UV.x);
	
	intensity *= (1.0 - isDamagePart);
	
	vec4 hurtColor = texture(gradientMapping, vec2(intensity));
	
	hurtColor.rgb = mix(hurtColor.rgb, 1.4 * bonusDiffColor.rgb * hurtColor.r, isDamageDiffPart);
	COLOR = hurtColor;
	} else { // lastDamagePercentage <=  healthPercentage

	float isDamagePart = smoothstep(healthPercentage-0.07, healthPercentage+0.0, UV.x);
	float isDamageDiffPart = smoothstep(lastDamagePercentage - 0.03, lastDamagePercentage +0.03, UV.x);
	
	intensity *= (1.0 - isDamagePart);
	
	vec4 hurtColor = texture(gradientMapping, vec2(intensity));

	hurtColor.rgb = mix(hurtColor.rgb, 1.4 * damageDiffColor.rgb * hurtColor.r, 
		isDamageDiffPart);
	COLOR = hurtColor;
	}

	

}