#version 130

in vec3 vs_out_col;
in vec3 vs_out_pos;

out vec4 fs_out_col;

uniform sampler2D textureAtlas;
uniform sampler2D lightMask;

uniform vec2 windowSize;
uniform float time_cycle;

void main()
{
	vec2 uvCoords = vs_out_col.rg;
	// le kell osztani 10-zel, mert az atlasz 10*10 text�r�t tartalmaz
	uvCoords /= 10;
	// k�k csatorna tartalmazza a text�ra indexet

	uvCoords.y += (int(vs_out_col.b) / 10) * 0.1;
	uvCoords.x += mod(vs_out_col.b, 10) * 0.1;

	vec4 color = texture(textureAtlas, uvCoords);
	vec4 l_mask = texture(lightMask, uvCoords);

	
	if(color.w <= 0.4)
	{
		discard;
	}
	else
	{
		// kisz�molom, hogy az adott pixel a maszkon mennyire "vil�gos"
		float lum = l_mask.r + l_mask.g + l_mask.b;

		if(lum > 1)
		{
			lum = 1;
		}

		if(lum >= 0.1 && time_cycle < 0.3)
		{
			// ez fade-eli egy kicsit
			lum *= 1 - time_cycle;

			// az eredeti text�r�ra r�keveri a f�nyt
			// lum*lum miatt az alacsony lum-mal rendelkez� pixelek gy�k�sen egyre kevesebb f�nyt kapnak
			vec4 col = vec4(1,0.9,0,1);
			fs_out_col = mix(color, col, lum*lum);
			return;
		}
		else
		{
			// day - night mix
			vec4 night = color - 0.08;
			vec4 day = color + 0.08;

			fs_out_col = mix(night, day, time_cycle);
			return;
		}
		//error
		fs_out_col = vec4(1,0,1,1);
	}
}

