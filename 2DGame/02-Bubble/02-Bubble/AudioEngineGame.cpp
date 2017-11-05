#include "AudioEngineGame.h"

Implementation_game::Implementation_game() {
	mpStudioSystem = NULL;
	CAudioEngine_Game::ErrorCheck(FMOD::Studio::System::create(&mpStudioSystem));
	CAudioEngine_Game::ErrorCheck(mpStudioSystem->initialize(32, FMOD_STUDIO_INIT_LIVEUPDATE, FMOD_INIT_PROFILE_ENABLE, NULL));

	mpSystem = NULL;
	CAudioEngine_Game::ErrorCheck(mpStudioSystem->getLowLevelSystem(&mpSystem));
}

Implementation_game::~Implementation_game() {
	CAudioEngine_Game::ErrorCheck(mpStudioSystem->unloadAll());
	CAudioEngine_Game::ErrorCheck(mpStudioSystem->release());
}

void Implementation_game::Update() {
	vector<ChannelMap::iterator> pStoppedChannels;
	for (auto it = mChannels.begin(), itEnd = mChannels.end(); it != itEnd; ++it)
	{
		bool bIsPlaying = false;
		it->second->isPlaying(&bIsPlaying);
		if (!bIsPlaying)
		{
			pStoppedChannels.push_back(it);
		}
	}
	for (auto& it : pStoppedChannels)
	{
		mChannels.erase(it);
	}
	CAudioEngine_Game::ErrorCheck(mpStudioSystem->update());
}

Implementation_game* sgpImplementation = nullptr;

void CAudioEngine_Game::Init() {
	sgpImplementation = new Implementation_game;
}

void CAudioEngine_Game::Update() {
	sgpImplementation->Update();
}

void CAudioEngine_Game::LoadSound(const std::string& strSoundName, bool b3d, bool bLooping, bool bStream)
{
	auto tFoundIt = sgpImplementation->mSounds.find(strSoundName);
	if (tFoundIt != sgpImplementation->mSounds.end())
		return;
	FMOD_MODE eMode = FMOD_DEFAULT;
	eMode |= b3d ? FMOD_3D : FMOD_2D;
	eMode |= bLooping ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;
	eMode |= bStream ? FMOD_CREATESTREAM : FMOD_CREATECOMPRESSEDSAMPLE;
	FMOD::Sound* pSound = nullptr;
	CAudioEngine_Game::ErrorCheck(sgpImplementation->mpSystem->createSound(strSoundName.c_str(), eMode, nullptr, &pSound));
	if (pSound) {
		sgpImplementation->mSounds[strSoundName] = pSound;
	}
}

void CAudioEngine_Game::UnLoadSound(const std::string& strSoundName)
{
	auto tFoundIt = sgpImplementation->mSounds.find(strSoundName);
	if (tFoundIt == sgpImplementation->mSounds.end())
		return;
	CAudioEngine_Game::ErrorCheck(tFoundIt->second->release());
	sgpImplementation->mSounds.erase(tFoundIt);
}

int CAudioEngine_Game::PlaySounds(const string& strSoundName, const Vector3_game& vPosition, float fVolumedB)
{
	int nChannelId = sgpImplementation->mnNextChannelId++;
	auto tFoundIt = sgpImplementation->mSounds.find(strSoundName);
	if (tFoundIt == sgpImplementation->mSounds.end())
	{
		LoadSound(strSoundName);
		tFoundIt = sgpImplementation->mSounds.find(strSoundName);
		if (tFoundIt == sgpImplementation->mSounds.end())
		{
			return nChannelId;
		}
	}
	FMOD::Channel* pChannel = nullptr;
	CAudioEngine_Game::ErrorCheck(sgpImplementation->mpSystem->playSound(tFoundIt->second, nullptr, true, &pChannel));
	if (pChannel)
	{
		FMOD_MODE currMode;
		tFoundIt->second->getMode(&currMode);
		if (currMode & FMOD_3D) {
			FMOD_VECTOR position = VectorToFmod(vPosition);
			CAudioEngine_Game::ErrorCheck(pChannel->set3DAttributes(&position, nullptr));
		}
		CAudioEngine_Game::ErrorCheck(pChannel->setVolume(dbToVolume(fVolumedB)));
		CAudioEngine_Game::ErrorCheck(pChannel->setPaused(false));
		sgpImplementation->mChannels[nChannelId] = pChannel;
	}
	return nChannelId;
}

void CAudioEngine_Game::SetChannel3dPosition(int nChannelId, const Vector3_game& vPosition)
{
	auto tFoundIt = sgpImplementation->mChannels.find(nChannelId);
	if (tFoundIt == sgpImplementation->mChannels.end())
		return;

	FMOD_VECTOR position = VectorToFmod(vPosition);
	CAudioEngine_Game::ErrorCheck(tFoundIt->second->set3DAttributes(&position, NULL));
}

void CAudioEngine_Game::SetChannelVolume(int nChannelId, float fVolumedB)
{
	auto tFoundIt = sgpImplementation->mChannels.find(nChannelId);
	if (tFoundIt == sgpImplementation->mChannels.end())
		return;

	CAudioEngine_Game::ErrorCheck(tFoundIt->second->setVolume(dbToVolume(fVolumedB)));
}

void CAudioEngine_Game::LoadBank(const std::string& strBankName, FMOD_STUDIO_LOAD_BANK_FLAGS flags) {
	auto tFoundIt = sgpImplementation->mBanks.find(strBankName);
	if (tFoundIt != sgpImplementation->mBanks.end())
		return;
	FMOD::Studio::Bank* pBank;
	CAudioEngine_Game::ErrorCheck(sgpImplementation->mpStudioSystem->loadBankFile(strBankName.c_str(), flags, &pBank));
	if (pBank) {
		sgpImplementation->mBanks[strBankName] = pBank;
	}
}

void CAudioEngine_Game::LoadEvent(const std::string& strEventName) {
	auto tFoundit = sgpImplementation->mEvents.find(strEventName);
	if (tFoundit != sgpImplementation->mEvents.end())
		return;
	FMOD::Studio::EventDescription* pEventDescription = NULL;
	CAudioEngine_Game::ErrorCheck(sgpImplementation->mpStudioSystem->getEvent(strEventName.c_str(), &pEventDescription));
	if (pEventDescription) {
		FMOD::Studio::EventInstance* pEventInstance = NULL;
		CAudioEngine_Game::ErrorCheck(pEventDescription->createInstance(&pEventInstance));
		if (pEventInstance) {
			sgpImplementation->mEvents[strEventName] = pEventInstance;
		}
	}
}

void CAudioEngine_Game::PlayEvent(const string &strEventName) {
	auto tFoundit = sgpImplementation->mEvents.find(strEventName);
	if (tFoundit == sgpImplementation->mEvents.end()) {
		LoadEvent(strEventName);
		tFoundit = sgpImplementation->mEvents.find(strEventName);
		if (tFoundit == sgpImplementation->mEvents.end())
			return;
	}
	tFoundit->second->start();
}

void CAudioEngine_Game::StopEvent(const string &strEventName, bool bImmediate) {
	auto tFoundIt = sgpImplementation->mEvents.find(strEventName);
	if (tFoundIt == sgpImplementation->mEvents.end())
		return;
	FMOD_STUDIO_STOP_MODE eMode;
	eMode = bImmediate ? FMOD_STUDIO_STOP_IMMEDIATE : FMOD_STUDIO_STOP_ALLOWFADEOUT;
	CAudioEngine_Game::ErrorCheck(tFoundIt->second->stop(eMode));
}

bool CAudioEngine_Game::IsEventPlaying(const string &strEventName) const {
	auto tFoundIt = sgpImplementation->mEvents.find(strEventName);
	if (tFoundIt == sgpImplementation->mEvents.end())
		return false;

	FMOD_STUDIO_PLAYBACK_STATE* state = NULL;
	if (tFoundIt->second->getPlaybackState(state) == FMOD_STUDIO_PLAYBACK_PLAYING) {
		return true;
	}
	return false;
}

void CAudioEngine_Game::GetEventParameter(const string &strEventName, const string &strParameterName, float* parameter) {
	auto tFoundIt = sgpImplementation->mEvents.find(strEventName);
	if (tFoundIt == sgpImplementation->mEvents.end())
		return;
	FMOD::Studio::ParameterInstance* pParameter = NULL;
	CAudioEngine_Game::ErrorCheck(tFoundIt->second->getParameter(strParameterName.c_str(), &pParameter));
	CAudioEngine_Game::ErrorCheck(pParameter->getValue(parameter));
}

void CAudioEngine_Game::SetEventParameter(const string &strEventName, const string &strParameterName, float fValue) {
	auto tFoundIt = sgpImplementation->mEvents.find(strEventName);
	if (tFoundIt == sgpImplementation->mEvents.end())
		return;
	FMOD::Studio::ParameterInstance* pParameter = NULL;
	CAudioEngine_Game::ErrorCheck(tFoundIt->second->getParameter(strParameterName.c_str(), &pParameter));
	CAudioEngine_Game::ErrorCheck(pParameter->setValue(fValue));
}

FMOD_VECTOR CAudioEngine_Game::VectorToFmod(const Vector3_game& vPosition) {
	FMOD_VECTOR fVec;
	fVec.x = vPosition.x;
	fVec.y = vPosition.y;
	fVec.z = vPosition.z;
	return fVec;
}

int CAudioEngine_Game::ErrorCheck(FMOD_RESULT result) {
	if (result != FMOD_OK) {
		cout << "FMOD ERROR " << result << endl;
		return 1;
	}
	// cout << "FMOD all good" << endl;
	return 0;
}

float  CAudioEngine_Game::dbToVolume(float dB)
{
	return powf(10.0f, 0.05f * dB);
}

float  CAudioEngine_Game::VolumeTodB(float volume)
{
	return 20.0f * log10f(volume);
}

void CAudioEngine_Game::Shutdown() {
	delete sgpImplementation;
}