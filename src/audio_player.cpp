#include "../include/apu.hpp"
#include "../include/audio_player.hpp"
#include <iostream>

void GBAudioStream::setRingBuffer(AudioRingBuffer* audio_buffer) {
	this->audio_buffer = audio_buffer;
	// sets the Mhz that we need to sample at
	initialize(1, 44100, { sf::SoundChannel::Mono });
}

bool GBAudioStream::onGetData(Chunk& data) {
	if (!audio_buffer) { return false; }

	constexpr size_t desiredSamples = 4096;
	chunkBuffer.resize(desiredSamples, 0);

	int16_t sample;
	size_t counter = 0;

	while (counter < desiredSamples) {
		if (audio_buffer->pop(sample)) {
			chunkBuffer[counter] = sample;
			counter++;
		}
		else {
			break;
		}
	}

	data.samples = chunkBuffer.data();
	data.sampleCount = chunkBuffer.size();

	return true;
}

void GBAudioStream::onSeek(sf::Time timeOffset)
{
}
