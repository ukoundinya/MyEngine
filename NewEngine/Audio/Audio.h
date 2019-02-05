#pragma once
#include "xaudio2.h"
#include "x3daudio.h"

namespace Sound
{
	class Audio
	{
	public:
		Audio();
		~Audio();
		HRESULT PlayBuffer(const XAUDIO2_BUFFER i_Buffer, const WAVEFORMATEX* i_WaveFormat) const;

	private:
		IXAudio2* pXAudio = nullptr;
		IXAudio2MasteringVoice* pMasteringVoice = nullptr;
	};
}

