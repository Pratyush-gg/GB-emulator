#pragma once

#include <cstdint>
#include "mmu.hpp"


class AudioPU {
private:
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
	static constexpr uint8_t WAVE_PATTERN_RAM_OFFSET = 0xFF30;
	static constexpr uint8_t WAVE_PATTERN_RAM_SIZE = 0xF;
	std::array<uint8_t, 16> wave_pattern;

	// CHANNEL 4
	uint8_t AUD4LEN;	// FF20 channel 4 length timer [NR41] WRITE ONLY
	uint8_t AUD4ENV;	// FF21 channel 4 volume and envelope [NR42]
	uint8_t AUD4POLY;	// FF22 channel 4 frequency and randomness [NR43]
	uint8_t AUD4GO;		// FF23 channel 4 control [NR44]
};
