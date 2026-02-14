#pragma once

#include <SFML/Audio.hpp>
#include "apu.hpp"

class GBAudioStream : public sf::SoundStream {
private:
	AudioRingBuffer* audio_buffer = nullptr;
	std::vector<int16_t> chunkBuffer;

public:
	void setRingBuffer(AudioRingBuffer* audio_buffer);
	bool onGetData(Chunk& data) override;
	// this is not required to be implemented
	// we only need live streaming from the emulator..
	void onSeek(sf::Time timeOffset) override;
};
