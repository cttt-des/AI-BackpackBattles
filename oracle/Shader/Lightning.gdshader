shader_type canvas_item;
render_mode unshaded;
// plot function 
uniform vec4 color1 : hint_color = vec4(0.0, 0, 0.9, 0.0); 
uniform vec4 color2 : hint_color = vec4(1.0, 1.0, 1.0, 0.0); 
uniform int lightning_number : hint_range(0,20) = 1;
uniform float speed = 2.0;
uniform float thickness = 0.02;
uniform float glow = 0.15;
uniform int wobble_it = 7;

uniform float smear = 1.0;
uniform float frequency= 2.0;
uniform float color_intensity = 1.5;
float plot(vec2 st, float pct, float half_width){
  return  smoothstep( pct-half_width, pct, st.y) -
          smoothstep( pct, pct+half_width, st.y);
}

// rand, noise and fbm function
float rand(vec2 n) {
    return fract(sin(dot(n, vec2(12.9898, 4.1414))) * 43758.5453);
}

float noise(vec2 n) {
    vec2 d = vec2(0.0, 1.0);
    vec2 b = floor(n), f = smoothstep(vec2(0.0), vec2(1.0), fract(n));
    return mix(mix(rand(b), rand(b + d.yx), f.x), mix(rand(b + d.xy), rand(b + d.yy), f.x), f.y);
}

float fbm(vec2 n) {
    float total = 0.0, amplitude = 1.0;
    for (int i = 0; i < wobble_it; i++) {
        total += noise(n) * amplitude;
        n += n;
        amplitude *= 0.5; // blitigkeit lol
    }
    return total;
}


void fragment(){
	vec2 uv = UV;
	vec4 color = vec4(0.0, 0.0, 0.0, 0.0);
	
	vec2 t ;
	float y ;
	float pct ;
	float buffer;	
	
	float effective= 1.0;
	if ( UV.x > 0.9 ) {
		//effective= (1.0-UV.x)*10.0;
		effective = smoothstep(0.0, 1.0, (1.0-UV.x)*10.0);
	} // 1 -> 0
	
	if ( UV.x < 0.1 ) {effective = smoothstep(0.0, 1.0, (UV.x)*10.0);}
	float pointForce = 1.0;
	if ( UV.x > 0.8) {pointForce = smoothstep(0.0, 1.0, (1.0-UV.x)*5.0);}
	if ( UV.x < 0.2) {pointForce = smoothstep(0.0, 1.0, (UV.x)*5.0);} 
	
	float col1 = 0.0;
	float col2 = 0.0;
	
	
	for ( int i = 0; i < lightning_number; i++){
		t = uv * vec2(frequency, smear) + vec2(float(i), -float(i)) - TIME* speed;
		//y = fbm(t)*0.5;
		y = fbm(t)*0.5 * pointForce + (1.0-pointForce)*0.5;
		//y = 0.5;
		
		pct = plot(uv, y, thickness * effective); 
		buffer = plot(uv, y, glow * effective); 
		col1 += pct;

		col2 += buffer * (1.0- col1); 
		
	}
	float colFactor = col1 / (col1 + col2);
	colFactor = clamp(colFactor, 0.0, 1.0);
	color = mix(color1, color2, colFactor);
	float blendadd = color.a;
	//float blendadd = color2.a * colFactor + color1.a * (1.0 - colFactor);
	color.a = (col1 + col2);
	//color.a = (color.r + color.g + color.b) * 0.33 ;
	color.a = clamp(color.a, 0.0, 1.0);
	color.rgb = min(color.rgb, vec3(color_intensity));
	
	COLOR.rgb = color.rgb * 2.0;
	COLOR.a = color.a * max(0.05, blendadd);
	COLOR.rgb = COLOR.rgb / max(0.05, blendadd);
	
}