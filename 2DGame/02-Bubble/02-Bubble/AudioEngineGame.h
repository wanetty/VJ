#ifndef _AUDIO_ENGINE_GAME_H_
#define _AUDIO_ENINGE_GAME_H_

#include "fmod_studio.hpp"
#include "fmod.hpp"
#include <string>
#include <map>
#include <vector>
#include <math.h>
#include <iostream>

using namespace std;

struct Vector3_game {
	float x;
	float y;
	float z;
};

struct Implementation_game {
	Implementation_game();
	~Implementation_game();

	void Update();

	FMOD::Studio::System* mpStudioSystem;
	FMOD::System* mpSystem;

	int mnNextChannelId;

	typedef map<string, FMOD::Sound*> SoundMap;
	typedef map<int, FMOD::Channel*> ChannelMap;
	typedef map<string, FMOD::Studio::EventInstance*> EventMap;
	typedef map<string, FMOD::Studio::Bank*> BankMap;
	BankMap mBanks;
	EventMap mEvents;
	SoundMap mSounds;
	ChannelMap mChannels;
};

class CAudioEngine_Game {
public:
	static void Init();
	static void Update();
	static void Shutdown();
	static int ErrorCheck(FMOD_RESULT result);

	void LoadBank(const std::string& strBankName, FMOD_STUDIO_LOAD_BANK_FLAGS flags);
	void LoadEvent(const std::string& strEventName);
	void LoadSound(const string &strSoundName, bool b3d = true, bool bLooping = false, bool bStream = false);
	void UnLoadSound(const string &strSoundName);
	int PlaySounds(const string &strSoundName, const Vector3_game& vPos = Vector3_game{ 0, 0, 0 }, float fVolumedB = 0.0f);
	void PlayEvent(const string &strEventName);
	void StopEvent(const string &strEventName, bool bImmediate = false);
	void GetEventParameter(const string &strEventName, const string &strEventParameter, float* parameter);
	void SetEventParameter(const string &strEventName, const string &strParameterName, float fValue);
	void SetChannel3dPosition(int nChannelId, const Vector3_game& vPosition);
	void SetChannelVolume(int nChannelId, float fVolumedB);
	bool IsEventPlaying(const string &strEventName) const;
	float dbToVolume(float dB);
	float VolumeTodB(float volume);
	FMOD_VECTOR VectorToFmod(const Vector3_game& vPosition);
};

#endif