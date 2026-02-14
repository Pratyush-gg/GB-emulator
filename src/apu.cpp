#include "../include/apu.hpp"

void AudioPU::writeMem(uint16_t address, uint8_t value) {
	if (address >= WAVE_PATTERN_RAM_OFFSET && \
		address < WAVE_PATTERN_RAM_OFFSET + WAVE_PATTERN_RAM_SIZE) {
		wave_pattern[address - WAVE_PATTERN_RAM_OFFSET] = value;
		return;
	}

	if (address == 0xFF26) {
		AUDENA = value & 0x80;
		if (!(AUDENA & 0x80)) {
			AUD1SWEEP = 0;
			AUD1LEN = 0;
			AUD1ENV = 0;
			AUD1LOW = 0;
			AUD1HIGH = 0;
			channel1.enabled = false;
			channel2.enabled = false;
			channel3.enabled = false;
			channel4.enabled = false;
		}
		return;
	}

	// APU is off
	if (!(AUDENA & 0x80)) {
		return;
	}

	switch (address) {
		// master control
		case 0xFF24: AUDVOL		= value; break;
		case 0xFF25: AUDTERM	= value; break;

		// CHANNEL 1
		case 0xFF10:
			AUD1SWEE = value;
			channel1.sweep_shift = value & 0x7;
			channel1.sweep_period = (value >> 4) & 0x7;
			channel1.sweep_negate = value & 0x8;
			break;
		case 0xFF11:
			AUD1LEN = value;
			channel1.length_timer = 64 - (value & 0x3F);
			channel1.duty_pattern = (value >> 6) & 0x3;
			break;
		case 0xFF12:
			AUD1ENV = value;
			channel1.envelope_period = value & 0x7;
			channel1.envelope_increasing = value & 0x8;
			channel1.initial_volume = (value >> 4) & 0xF;
			channel1.dac_enabled = (value & 0xF8) != 0;
			if (!channel1.dac_enabled) {
				channel1.enabled = false;
			}
			break;
		case 0xFF13:
			AUD1LOW = value;
			channel1.frequency = (channel1.frequency & 0xFF00) | value;
			break;
		case 0xFF14:
			AUD1HIGH = value;
			channel1.frequency = (channel1.frequency & 0x00FF) | ((value & 0x7) << 8);
			channel1.length_enabled = value & 0x40;
			if (value & 0x80) {
				// Trigger the channel
			}

		// CHANNEL 2
		case 0xFF16: AUD2LEN	= value; break;
		case 0xFF17: AUD2ENV	= value; break;
		case 0xFF18: AUD2LOW	= value; break;
		case 0xFF19: AUD2HIGH	= value; break;

		// CHANNEL 3
		case 0xFF1A: AUD3ENA	= value; break;
		case 0xFF1B: AUD3LEN	= value; break;
		case 0xFF1C: AUD3LEVEL	= value; break;
		case 0xFF1D: AUD3LOW	= value; break;
		case 0xFF1E: AUD3HIGH	= value; break;

		// CHANNEL 4
		case 0xFF20: AUD4LEN	= value; break;
		case 0xFF21: AUD4ENV	= value; break;
		case 0xFF22: AUD4POLY	= value; break;
		case 0xFF23: AUD4GO		= value; break;
	}
}

uint8_t AudioPU::readMem(uint16_t address) const {
	if (address >= WAVE_PATTERN_RAM_OFFSET && \
		address < WAVE_PATTERN_RAM_OFFSET + WAVE_PATTERN_RAM_SIZE) {
		return wave_pattern[address - WAVE_PATTERN_RAM_OFFSET];
	}

	switch (address) {
		// master control
		case 0xFF24: return AUDVOL;
		case 0xFF25: return AUDTERM;
		case 0XFF26: return AUDENA;

		// CHANNEL 1
		case 0xFF10: return AUD1SWEEP;
		case 0xFF11: return AUD1LEN;
		case 0xFF12: return AUD1ENV;
		case 0xFF13: return AUD1LOW;
		case 0xFF14: return AUD1HIGH;

		// CHANNEL 2
		case 0xFF16: return AUD2LEN;
		case 0xFF17: return AUD2ENV;
		case 0xFF18: return AUD2LOW;
		case 0xFF19: return AUD2HIGH;

		// CHANNEL 3
		case 0xFF1A: return AUD3ENA;
		case 0xFF1B: return AUD3LEN;
		case 0xFF1C: return AUD3LEVEL;
		case 0xFF1D: return AUD3LOW;
		case 0xFF1E: return AUD3HIGH;

		// CHANNEL 4
		case 0xFF20: return AUD4LEN;
		case 0xFF21: return AUD4ENV;
		case 0xFF22: return AUD4POLY;
		case 0xFF23: return AUD4GO;
	}

	return 0;
}