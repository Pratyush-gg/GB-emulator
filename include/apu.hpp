#pragma once

#include <cstdint>
#include "mmu.hpp"
#include <atomic>

/*
	Lock Free audio ring buffer implemented because sfml and other front-ends
	may require concurrent access to the audio stream.
*/
struct AudioRingBuffer {
private:
	std::vector<int16_t> buffer;
	std::atomic<size_t> head{ 0 };
	std::atomic<size_t> tail{ 0 };

	const size_t capacity;

public:
	AudioRingBuffer(size_t size) : buffer(size), capacity(size) {}

	bool push(int16_t sample) {
		size_t next_head = (head.load() + 1) % capacity;
		if (next_head == tail.load()) return false; // buffer overflow
		buffer[head.load()] = sample;
		head.store(next_head);
	}

	bool pop(int16_t &sample) {	// sample is an out-parameter return value is status
		if (tail.load() == head.load()) return false;
		sample = buffer[tail.load()];
		size_t next_tail = (tail.load() + 1) % capacity;
		tail.store(next_tail);
		return true;
	}
};

struct ChannelState {
	int16_t currentSample = 0;
	std::array<int16_t, 265> buffer_history;
	size_t historyIdx = 0;
};

class AudioPU {
private:

	struct AudioChannel {
		int timer;
		virtual float getOutput();	// returns 32 bit float as the amplitude, 
									// will have to convert this to 16 bit before passing it into SFML
		virtual void tick();		// for updating the timer to generate waves and stuff
	};

	struct SquareChannel : AudioChannel {
		float getOutput() override;
		void tick() override;
	};

	struct NoiseChannel : AudioChannel {
		float getOutput() override;
		void tick() override;
	};

	struct WaveChannel : AudioChannel {
		float getOutput() override;
		void tick() override;
	};

	uint8_t AUDVOL;		// FF24 master volume & VIN panning [NR50]
	uint8_t AUDTERM;	// FF25 sound panning [NR51]
	uint8_t AUDENA;		// FF26 audio master control [NR52]

	// CHANNEL 1
	uint8_t AUD1SWEEP;	// FF10 channel 1 sweep [NR10]
	uint8_t AUD1LEN;	// FF11 channel 1 length timier and duty cycle [NR11]
	uint8_t AUD1ENV;	// FF12 audio channel 1 volume and envelope [NR12]
	uint8_t AUD1LOW;	// FF13 audio channel 1 period low bits [NR13] WRITE ONLY
	uint8_t AUD1HIGH;	// FF14 audio channel 1 period high bits [NR14]

	// CHANNEL 2
	uint8_t AUD2LEN;	// FF16 channel 2 length timier and duty cycle [NR21]
	uint8_t AUD2ENV;	// FF17 audio channel 2 volume and envelope [NR22]
	uint8_t AUD2LOW;	// FF18 audio channel 2 period low bits [NR23] WRITE ONLY
	uint8_t AUD2HIGH;	// FF19 audio channel 2 period high bits [NR24]

	// CHANNEL 3
	uint8_t AUD3ENA;	// FF1A channel 3 enable [NR30]
	uint8_t AUD3LEN;	// FF1B channel 3 length timer [NR31] WRITE ONLY
	uint8_t AUD3LEVEL;	// FF1C channel 3 output level [NR32]
	uint8_t AUD3LOW;	// FF1D channel 3 period low [NR33] WRITE ONLY
	uint8_t AUD3HIGH;	// FF1E channel 3 period high & control [NR34]
	static constexpr uint16_t WAVE_PATTERN_RAM_OFFSET = 0xFF30;
	static constexpr uint8_t WAVE_PATTERN_RAM_SIZE = 0xF;
	std::array<uint8_t, 16> wave_pattern;

	// CHANNEL 4
	uint8_t AUD4LEN;	// FF20 channel 4 length timer [NR41] WRITE ONLY
	uint8_t AUD4ENV;	// FF21 channel 4 volume and envelope [NR42]
	uint8_t AUD4POLY;	// FF22 channel 4 frequency and randomness [NR43]
	uint8_t AUD4GO;		// FF23 channel 4 control [NR44]

	SquareChannel channel1;
	SquareChannel channel2;
	NoiseChannel channel3;
	WaveChannel channel4;

	AudioRingBuffer masterRingBuffer; // stores the outgoing buffer for any frontend

public:
	void tick(); // update state on timer tick
	void writeMem(uint16_t address, uint8_t value);
	uint8_t readMem(uint16_t address) const;
};
