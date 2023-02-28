
#include "ReShade.fxh"

uniform float horiz_offset <
ui_type = "drag";
ui_min = -25;
ui_max = 25;
ui_label = "Horizontal Offset";
ui_tooltip = "Move center of crosshair off-center side to side";
> = 5;

uniform float vert_offset <
ui_type = "drag";
ui_min = -25;
ui_max = 25;
ui_label = "Vertical Offset";
ui_tooltip = "Move center of crosshair off-center up and down";
> = 7;

uniform float size <
ui_type = "drag";
ui_min = 2;
ui_max = 16;
ui_label = "Crosshair Size";
ui_tooltip = "Size of the crosshair in pixels";
> = 14;

uniform float thick <
ui_type = "drag";
ui_min = 0.1;
ui_max = 4;
ui_label = "Crosshair Thickness";
ui_tooltip = "Thickness of the crosshair in pixels";
> = 0.5;

uniform int crosshair_color_r <
ui_type ="drag";
ui_min = 0;
ui_max = 255;
ui_label = "Crosshair color red";
ui_tooltip = "Color Red";
> = 255;

uniform int crosshair_color_g <
ui_type ="drag";
ui_min = 0;
ui_max = 255;
ui_label = "Crosshair color green";
ui_tooltip = "Color Green";
> = 142;

uniform int crosshair_color_b <
ui_type ="drag";
ui_min = 0;
ui_max = 255;
ui_label = "Crosshair color blue";
ui_tooltip = "Color Blue";
> = 255;

#define crosshair_color float3( crosshair_color_r/255, crosshair_color_g/255, crosshair_color_b/255)

float3 PS_crosshairRing(float4 pos : SV_Position, float2 texcoord : TexCoord) : SV_Target {
	float3 color = tex2D(ReShade::BackBuffer, texcoord).rgb;
	float2 center = float2( (BUFFER_WIDTH / 2)+horiz_offset, (BUFFER_HEIGHT / 2)+vert_offset);

	float3 invertedColor = float3(1.0,1.0,1.0) - color;
	float3 crosshairDisplayColor =  crosshair_color * invertedColor;

	float dist_fromCenter = distance(center, pos);
	float dist_fromIdeal = abs(dist_fromCenter - size);
	float mix = max(thick - dist_fromIdeal,0) / thick;
	color = lerp(color, crosshairDisplayColor, mix);

	return color;
}

technique Ring {
	pass crosshairRing {
		VertexShader=PostProcessVS;
		PixelShader=PS_crosshairRing;
	}
}
