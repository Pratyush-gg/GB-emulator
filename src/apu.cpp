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
		case 0xFF16:
			AUD2LEN = value;
			channel2.duty_pattern = (value >> 6) & 0x03;
			channel2.length_timer = 64 - (value & 0x3F);
			break;
		case 0xFF17:
			AUD2ENV = value;
			channel2.initial_volume = (value >> 4) & 0x0F;
			channel2.envelope_increasing = value & 0x08;
			channel2.envelope_period = value & 0x07;
			channel2.dac_enabled = (value & 0xF8) != 0;
			if (!channel2.dac_enabled) {
				channel2.enabled = false;
			}
			break;
		case 0xFF18:
			AUD2LOW = value;
			channel2.frequency = (channel2.frequency & 0xFF00) | value;
			break;
		case 0xFF19:
			AUD2HIGH = value;
			channel2.frequency = (channel2.frequency & 0x00FF) | ((value & 0x07) << 8);
			channel2.length_enabled = value & 0x40;
			if (value & 0x80) {
				// Trigger the channel
			}
			break;

		// CHANNEL 3
		case 0xFF1A:
			AUD3ENA = value;
			channel3.dac_enabled = value & 0x80;
			if (!channel3.dac_enabled) {
					channel3.enabled = false;
			}
			break;
		case 0xFF1B:
			AUD3LEN = value;
			channel3.length_timer = 256 - value;
			break;
		case 0xFF1C:
			AUD3LEN = value;
			channel3.output_level = (value >> 5) & 0x03;
		case 0xFF1D:
			AUD3LOW = value;
			channel3.frequency = (channel3.frequency & 0x7000) | value;
			break;
		case 0xFF1E:
			AUD3HIGH = value;
			channel3.frequency = (channel3.frequency & 0x00FF) | ((value & 0x07) << 8);
			channel3.length_enabled = value & 0x40;
			if (value & 0x80) {
				// Trigger the channel
			}
			break;

		// CHANNEL 4
		case 0xFF20:
			AUD4LEN = value;
			channel4.length_timer = 64 - (value & 0x3F);
			break;
		case 0xFF21:
			AUD4ENV = value;
			channel4.initial_volume = (value >> 4) & 0x0F;
			channel4.envelope_increasing = value & 0x08;
			channel4.envelope_period = value & 0x07;
			channel4.dac_enabled = (value & 0xF8) != 0;
			if (!channel4.dac_enabled) {
				channel4.enabled = false;
			}
			break;
		case 0xFF22:
			AUD4POLY = value;
			channel4.clock_shift = (value >> 4) & 0x0F;
			channel4.width_shift = (value >> 3) & 0x01;
			channel4.divisor_code = value & 0x07;
			break;
		case 0xFF23:
			AUD4GO = value;
			channel4.length_enabled = value & 0x40;
			if (value & 0x80) {
				// Trigger the channel
			}
			break;
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
		case 0XFF26:
			return (AUD3ENA & 0x80) |
				(channel1.enabled ? 0x01 : 0) |
				(channel2.enabled ? 0x02 : 0) |
				(channel3.enabled ? 0x04 : 0) |
				(channel4.enabled ? 0x08 : 0) | 0x70;

		// CHANNEL 1
		case 0xFF10: return AUD1SWEEP | 0x80;
		case 0xFF11: return (AUD1LEN & 0xC0) | 0x3F;
		case 0xFF12: return AUD1ENV;
		case 0xFF13: return 0xFF;
		case 0xFF14: return (AUD1HIGH & 0x40) | 0xBF;

		// CHANNEL 2
		case 0xFF16: return (AUD2LEN & 0xC0) | 0x3F;
		case 0xFF17: return AUD2ENV;
		case 0xFF18: return 0xFF;
		case 0xFF19: return (AUD2HIGH & 0x40) | 0xBF;

		// CHANNEL 3
		case 0xFF1A: return (AUD3ENA & 0x80) | 0x7F;
		case 0xFF1B: return 0xFF;
		case 0xFF1C: return (AUD3LEVEL & 0x60) | 0x9F;
		case 0xFF1D: return 0xFF;
		case 0xFF1E: return (AUD3HIGH & 0x40) | 0xBF;

		// CHANNEL 4
		case 0xFF20: return 0xFF;
		case 0xFF21: return AUD4ENV;
		case 0xFF22: return AUD4POLY;
		case 0xFF23: return (AUD4GO & 0x40) | 0xBF;

		default: return 0xFF;
	}
}