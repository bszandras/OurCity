#version 130

// VBO-ból érkező változók
in vec3 vs_in_pos;
in vec3 vs_in_col;

// a pipeline-ban tovább adandó értékek
out vec3 vs_out_pos;
out vec3 vs_out_col;

//uniformok
uniform vec3 camData;
uniform vec2 windowSize;

void main()
{
	//kell egy ilyen scale-er
	float zoomScale = 1;

	//world space -> screen space
	//create converted vert
	vec3 convertedVert = vs_in_pos;

	//normalize to screencenter
	convertedVert.xy += windowSize/2;

	//move according to camera position
	convertedVert.xy -= camData.xy;

	//screen space -> shader space
	//div by window width and height
	convertedVert.xy /= windowSize.xy;
	//[0,1] data -> [0,2] data
	convertedVert.xy *= 2;
	//[0,2] -> [-1,1]
	convertedVert.xy -= 1;
	
	//scale coords according to camera zoom
	convertedVert.xy *= camData.z;

	gl_Position = vec4(convertedVert, 1);

	vs_out_pos = vs_in_pos;
	vs_out_col = vs_in_col;
}