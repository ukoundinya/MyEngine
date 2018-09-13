#pragma once
#include "Graphics.h"
#ifdef EAE6320_PLATFORM_D3D 
#include <d3d11.h>
#include <dxgi.h>
#endif
#include "sContext.h"
#include "cConstantBuffer.h"
#include "ConstantBufferFormats.h"
#include "cRenderState.h"
#include "cShader.h"
#include "VertexFormats.h"

#include <Engine/Asserts/Asserts.h>
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
			cEffect(){}
			cResult Initialize();
			cResult Initialize(std::string i_vertexShaderLocation, std::string i_fragmentShaderLocation)
			{
				auto result = Results::Success;
				m_vertexShaderLocation = i_vertexShaderLocation;
				m_fragmentShaderLocation = i_fragmentShaderLocation;
				result = Initialize();
				return result;
			}
			void Bind();
			cResult Shutdown();
		private:
#ifdef EAE6320_PLATFORM_D3D
			eae6320::Graphics::cShader::Handle m_vertexShader;
			eae6320::Graphics::cShader::Handle m_fragmentShader;
			eae6320::Graphics::cRenderState s_renderState;
#elif EAE6320_PLATFORM_GL
			eae6320::Graphics::cShader::Handle m_vertexShader;
			eae6320::Graphics::cShader::Handle m_fragmentShader;
			GLuint s_programId = 0;
			eae6320::Graphics::cRenderState s_renderState;
			cResult InitGL();
			cResult ShutdownGL();
#endif
			std::string m_vertexShaderLocation;
			std::string m_fragmentShaderLocation;
		};
	}
}