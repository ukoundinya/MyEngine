/*
	This is the standard fragment shader

	A fragment shader is responsible for telling the GPU what color a specific fragment should be
*/

#include <Shaders/shaders.inc>

#if defined( EAE6320_PLATFORM_D3D )

// Entry Point
//============

void main(

	// Output
	//=======

	// Whatever color value is output from the fragment shader
	// will determine the color of the corresponding pixel on the screen
	out float4 o_color : SV_TARGET

	)
{
	// Output solid white
	o_color = float4(
		// RGB (color)
		abs(sin(g_elapsedSecondCount_simulationTime)), abs(cos(g_elapsedSecondCount_simulationTime)), abs(sin(g_elapsedSecondCount_simulationTime)/ cos(g_elapsedSecondCount_simulationTime)),
		// Alpha (transparency)
		1.0 );
}

#elif defined( EAE6320_PLATFORM_GL )

// Output
//=======

// Whatever color value is output from the fragment shader
// will determine the color of the corresponding pixel on the screen
out vec4 o_color;

// Entry Point
//============

void main()
{
	// Output solid white
	o_color = vec4(
		// RGB (color)
		abs(sin(g_elapsedSecondCount_simulationTime)), abs(cos(g_elapsedSecondCount_simulationTime)), abs(sin(g_elapsedSecondCount_simulationTime) / cos(g_elapsedSecondCount_simulationTime)),
		// Alpha (transparency)
		1.0 );
}

#endif
