shader_type canvas_item;

uniform vec2 direction = vec2(0.5, 0.5);
uniform float angle : hint_range(0.0, 6.5, 0.1);
uniform sampler2D gradient;
uniform sampler2D bubbleNoise;
uniform vec2 noiseScale = vec2(1,1);
uniform float foaminess = 0.2;
uniform vec2 foamOffset = vec2(0,0);
uniform float levelOffset : hint_range(-1.0, 1.0) = 0.0;
//uniform vec4 flashColor : hint_color;
//uniform float flashState : hint_range(0.0, 1.0) = 0.0;

vec2 rotate(vec2 uv, vec2 pivot, float r)
{
	mat2 rotation = mat2(vec2(sin(r), -cos(r)),
						vec2(cos(r), sin(r)));
	
	uv -= pivot;
	uv = uv * rotation;
	uv += pivot;
	return uv;
}

void fragment()
{
	vec2 rotated_uv = rotate(UV, vec2(0.5), angle);
	COLOR = texture(TEXTURE, UV);
//	float dotPr = dot(direction, UV);
//	if (dotPr < 1.0) {
//		COLOR.a = 0.0;
//	}
	//COORDINATE SPACE FOR FOAM OFFSET?
	//COORDINATE SPACE FOR FOAM OFFSET?

	//float bubbles = texture(bubbleNoise, rotated_uv * noiseScale + foamOffset).r;
	float bubbles = texture(bubbleNoise, (SCREEN_UV- foamOffset) * noiseScale).r;
	
	float borderBonus = abs(rotated_uv.x - 0.5);
	borderBonus = pow(borderBonus, 4) * 2.0;
	vec4 gr = texture(gradient, rotated_uv.yy + bubbles * foaminess + borderBonus + levelOffset);

	//COLOR.rgb = mix(COLOR.rgb, gr.rgb, gr.a);
	if (COLOR.a > 0.0)
		//COLOR.a = 1.0;
		COLOR = gr;
	
	//if (flashState > 0.0)
	//	COLOR.rgb = mix(COLOR.rgb, flashColor.rgb, flashState);
	
	//COLOR.rgb = mix(COLOR.rgb, vec3(1), foaminess);
	//if (rotated_uv.y < 0.5) {COLOR.a = 0.0;}
	//COLOR.a *= step(dotPr, 1.0);
}