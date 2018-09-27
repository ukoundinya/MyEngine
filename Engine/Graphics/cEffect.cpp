#include "cEffect.h"

namespace eae6320
{
	namespace Graphics
	{
		cResult cEffect::Initialize(std::string i_vertexShaderLocation, std::string i_fragmentShaderLocation, uint8_t i_TypeOfRender)
		{
			auto result = eae6320::Results::Success;

			if (!(result = eae6320::Graphics::cShader::s_manager.Load(i_vertexShaderLocation.c_str(),
				m_vertexShader, eae6320::Graphics::ShaderTypes::Vertex)))
			{
				EAE6320_ASSERT(false);
				goto OnExit;
			}
			if (!(result = eae6320::Graphics::cShader::s_manager.Load(i_fragmentShaderLocation.c_str(),
				m_fragmentShader, eae6320::Graphics::ShaderTypes::Fragment)))
			{
				EAE6320_ASSERT(false);
				goto OnExit;
			}
			//Changing this to enable depth buffering and other state from the game, defaults to 0 if nothing is passed
			{
				if (!(result = s_renderState.Initialize(i_TypeOfRender)))
				{
					EAE6320_ASSERT(false);
					goto OnExit;
				}
			}
#ifdef EAE6320_PLATFORM_GL
			InitGL();
#endif
		OnExit:

			return result;
		}
		cResult cEffect::Shutdown()
		{
			auto result = Results::Success;
#if EAE6320_PLATFORM_GL
			result = ShutdownGL();
#endif
			if (m_vertexShader)
			{
				const auto localResult = cShader::s_manager.Release(m_vertexShader);
				if (!localResult)
				{
					EAE6320_ASSERT(false);
					if (result)
					{
						result = localResult;
					}
				}
			}
			if (m_fragmentShader)
			{
				const auto localResult = cShader::s_manager.Release(m_fragmentShader);
				if (!localResult)
				{
					EAE6320_ASSERT(false);
					if (result)
					{
						result = localResult;
					}
				}
			}
			{
				const auto localResult = s_renderState.CleanUp();
				if (!localResult)
				{
					EAE6320_ASSERT(false);
					if (result)
					{
						result = localResult;
					}
				}
			}
			return result;
		}
	}
}