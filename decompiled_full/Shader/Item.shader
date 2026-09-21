shader_type canvas_item;

uniform float progress : hint_range(-1, 2) = 0.5;
uniform vec2 direction = vec2(0, 1);
uniform vec2 atlasTranslation;
uniform vec2 atlasScaling = vec2(1,1);

void fragment() {
	COLOR = texture(TEXTURE, UV);
	//if (progress != 0.0) {
		vec2 atlasUV = (UV - atlasTranslation) / atlasScaling;
		//COLOR.rgb = vec3(atlasUV.xy, 0);
		COLOR.rgb *= 1.0 + 0.5 * smoothstep(progress - 0.05, progress + 0.05, dot(atlasUV, direction));
	//}
}