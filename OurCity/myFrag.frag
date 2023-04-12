#version 130

in vec3 vs_out_col;
in vec3 vs_out_pos;

out vec4 fs_out_col;

uniform sampler2D textureAtlas;

uniform float time_cycle;

void main()
{
	vec2 uvCoords = vs_out_col.rg;
	// le kell osztani 10-zel, mert az atlasz 10*10 textúrát tartalmaz
	uvCoords /= 10;
	// kék csatorna tartalmazza a textúra indexet

	uvCoords.y += (int(vs_out_col.b) / 10) * 0.1;
	uvCoords.x += mod(vs_out_col.b, 10) * 0.1;

	vec4 color = texture(textureAtlas, uvCoords);

	
	if(color.w <= 0.4)
	{
		discard;
	}
	else
	{
		//brightness adjust
		//fs_out_col = color + 0.05;
		//color += 0.05;
		//float time = time_cycle / 1000;

		//fs_out_col = mix(color, vec4(229.0,103.0,23.0,color.a), time);
		//fs_out_col = mix(color, vec4(0.0,0.0,0.0,color.a), time);

		//vec4 night = mix(color, vec4(229,103,23, color.a), 0.002);
		if(color == vec4(0,1,0,1))
		{

			if(time_cycle < 0.3)
			{
				color = vec4(1,0.95,0,1);
			}
			else
			{
				color = vec4(0.25,0.38,0.44,1);
			}
			fs_out_col = color;
		}
		else
		{
			vec4 night = color - 0.03;
			vec4 day = color + 0.08;
			fs_out_col = mix(night, day, time_cycle);
		}

		//fs_out_col = mix(vec4(1,0,0,1), vec4(0,1,0,1), time_cycle);
	}
	
}
