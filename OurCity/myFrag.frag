#version 130

in vec3 vs_out_col;
in vec3 vs_out_pos;

out vec4 fs_out_col;

uniform sampler2D textureAtlas;
uniform vec2 windowSize;
uniform float time_cycle;

float random (vec2 st) {
    return fract(sin(dot(st.xy,
                vec2(12.9898,78.233)))*
				43758.5453123);
}

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
		//random
		vec2 st = gl_FragCoord.xy/windowSize.xy;
		float rnd = random(st);
		rnd += 0.1;

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

			color *= rnd;
			color.a = 1;

			fs_out_col = color;
			return;
		}
		else
		{
			vec4 night = color - 0.03;
			vec4 day = color + 0.08;

			fs_out_col = mix(night, day, time_cycle);
			return;
		}

		//error
		fs_out_col = vec4(1,0,1,1);
	}
}

