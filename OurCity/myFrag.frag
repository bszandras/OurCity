#version 130

in vec3 vs_out_col;
in vec3 vs_out_pos;

out vec4 fs_out_col;

uniform sampler2D textureAtlas;

void main()
{
	vec2 uvCoords = vs_out_col.rg;
	// le kell osztani 10-zel, mert az atlasz 10*10 textúrát tartalmaz
	uvCoords /= 10;
	// kék csatorna tartalmazza a textúra indexet
	// TODO:
	// ez a megoldás jelenleg, csak az elsõ sor 10 textúráját képes kezelni
	// a többi sor nincs implementálva
	uvCoords.x += vs_out_col.b * 0.1;

	vec4 color = texture(textureAtlas, uvCoords);
	
	//fs_out_col = vec4(vs_out_col.rgb, 1.0);

	
	if(color.w <= 0.4)
	{
		discard;
	}
	else
	{
		fs_out_col = color + 0.05;
	}
	
}
