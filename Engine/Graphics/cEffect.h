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
#include <Engine/Assets/ReferenceCountedAssets.h>
#include <utility>

#include "sContext.h"

namespace eae6320
{
	namespace Graphics
	{
		class cEffect
		{
		public:

			using Handle = Assets::cHandle<cEffect>;
			static Assets::cManager<cEffect> s_Manager;

			static cResult Load(const std::string& i_FilePath, cEffect*& o_Effect);

			EAE6320_ASSETS_DECLAREREFERENCECOUNTINGFUNCTIONS()
			EAE6320_ASSETS_DECLAREDELETEDREFERENCECOUNTEDFUNCTIONS(cEffect)
			void Bind();
			static cResult CreateEffect(std::string i_vertexShaderLocation, std::string i_fragmentShaderLocation, uint8_t i_TypeOfRender, cEffect*& o_Effect)
			{
				cResult result = Results::Success;
				o_Effect = new cEffect();
				result = o_Effect->Initialize(i_vertexShaderLocation, i_fragmentShaderLocation, i_TypeOfRender);
				return result;
			}

			static cResult CreateEffect(std::string i_vertexShaderLocation, std::string i_fragmentShaderLocation, cEffect*& o_Effect)
			{
				cResult result = Results::Success;
				o_Effect = new cEffect();
				result = o_Effect->Initialize(i_vertexShaderLocation, i_fragmentShaderLocation, 0);
				return result;
			}
		private:
			cEffect() {}
			~cEffect() 
			{
				Shutdown();
			}
			cResult Initialize(std::string i_vertexShaderLocation, std::string i_fragmentShaderLocation, uint8_t i_TypeOfRender);
			cResult Shutdown();
#ifdef EAE6320_PLATFORM_D3D
			eae6320::Graphics::cShader::Handle m_vertexShader;
			eae6320::Graphics::cShader::Handle m_fragmentShader;
			eae6320::Graphics::cRenderState s_renderState;
//			eae6320::Graphics::cRenderState::Handle s_renderStateHandle;
#elif EAE6320_PLATFORM_GL
			eae6320::Graphics::cShader::Handle m_vertexShader;
			eae6320::Graphics::cShader::Handle m_fragmentShader;
			GLuint s_programId = 0;
			eae6320::Graphics::cRenderState s_renderState;
			cResult InitGL();
			cResult ShutdownGL();
#endif
			EAE6320_ASSETS_DECLAREREFERENCECOUNT()
		};
	}
}