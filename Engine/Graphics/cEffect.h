#pragma once
#include "Graphics.h"

#include "cConstantBuffer.h"
#include "ConstantBufferFormats.h"
#include "cRenderState.h"
#include "cShader.h"
#include "sContext.h"
#include "VertexFormats.h"

#include <Engine/Asserts/Asserts.h>
#include <Engine/Concurrency/cEvent.h>
#include <Engine/Logging/Logging.h>
#include <Engine/Platform/Platform.h>
#include <Engine/Time/Time.h>
#include <Engine/UserOutput/UserOutput.h>
#include <utility>

namespace eae6320
{
	namespace Graphics
	{
		class cEffect
		{
		public:
			cResult Initialize();
			void Bind();
			cResult Shutdown();
		private:
#ifdef EAE6320_PLATFORM_D3D
#elif EAE6320_PLATFORM_GL
			eae6320::Graphics::cShader::Handle s_vertexShader;
			eae6320::Graphics::cShader::Handle s_fragmentShader;
			GLuint s_programId = 0;
			eae6320::Graphics::cRenderState s_renderState;
#endif
		};
	}
}