shader_type canvas_item;

void vertex() {
	VERTEX.x += INSTANCE_CUSTOM.b * 100.0;
}