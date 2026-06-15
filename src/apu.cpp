#include "../include/apu.hpp"
#include <fstream>
#include <iostream>

namespace {
std::ofstream& apuLenTrace() {
	static std::ofstream file("apu_len_trace.log", std::ios::out | std::ios::trunc);
	return file;
}

void traceLenEvent(const char* tag, int ch, int step, int len, bool len_en, bool en) {
	static int traceCount = 0;
	if (traceCount >= 1500) {
		return;
	}
	apuLenTrace() << tag
		<< " ch=" << ch
		<< " step=" << step
		<< " len=" << len
		<< " len_en=" << (len_en ? 1 : 0)
		<< " en=" << (en ? 1 : 0)
		<< '\n';
	traceCount++;
}
}

constexpr int FRAME_SEQUENCER_CLOCKS = 8192;
constexpr int SAMPLE_RATE = 44100;
constexpr int CLOCK_SPEED = 4194304;
constexpr int CLOCKS_PER_SAMPLE = CLOCK_SPEED / SAMPLE_RATE;

void AudioPU::writeMem(uint16_t address, uint8_t value) {
	if (address >= WAVE_PATTERN_RAM_OFFSET && address < WAVE_PATTERN_RAM_OFFSET + WAVE_PATTERN_RAM_SIZE) {
		wave_pattern[address - WAVE_PATTERN_RAM_OFFSET] = value;
		return;
	}

	if (address == 0xFF26) {
		std::cout << "[DEBUG_NR52] write value=" << (int)value << " (prev AUDENA=" << (int)AUDENA << ") step=" << frame_sequencer_step << std::endl;
		bool was_off = !(AUDENA & 0x80);
		AUDENA = value & 0x80;
		if (!(AUDENA & 0x80)) {
			AUD1SWEEP = 0;
			AUD1LEN = 0;
			AUD1ENV = 0;
			AUD1LOW = 0;
			AUD1HIGH = 0;
			AUDVOL = 0;
			AUDTERM = 0;
			AUD2LEN = 0;
			AUD2ENV = 0;
			AUD2LOW = 0;
			AUD2HIGH = 0;
			AUD3ENA = 0;
			AUD3LEN = 0;
			AUD3LEVEL = 0;
			AUD3LOW = 0;
			AUD3HIGH = 0;
			AUD4LEN = 0;
			AUD4ENV = 0;
			AUD4POLY = 0;
			AUD4GO = 0;

			// Channel 1
			channel1.enabled = false;
			channel1.dac_enabled = false;
			channel1.length_enabled = false;
			channel1.initial_volume = 0;
			channel1.current_volume = 0;
			channel1.envelope_timer = 0;
			channel1.envelope_period = 0;
			channel1.envelope_increasing = false;
			channel1.frequency = 0;
			channel1.timer = 0;
			channel1.sweep_timer = 0;
			channel1.sweep_period = 0;
			channel1.sweep_shift = 0;
			channel1.shadow_frequency = 0;
			channel1.duty_pattern = 0;
			channel1.duty_position = 0;
			channel1.sweep_enabled = false;
			channel1.sweep_negate = false;
			channel1.sweep_negate_used = false;

			// Channel 2
			channel2.enabled = false;
			channel2.dac_enabled = false;
			channel2.length_enabled = false;
			channel2.initial_volume = 0;
			channel2.current_volume = 0;
			channel2.envelope_timer = 0;
			channel2.envelope_period = 0;
			channel2.envelope_increasing = false;
			channel2.frequency = 0;
			channel2.timer = 0;
			channel2.duty_pattern = 0;
			channel2.duty_position = 0;

			// Channel 3
			channel3.enabled = false;
			channel3.dac_enabled = false;
			channel3.length_enabled = false;
			channel3.frequency = 0;
			channel3.timer = 0;
			channel3.position = 0;
			channel3.output_level = 0;

			// Channel 4
			channel4.enabled = false;
			channel4.dac_enabled = false;
			channel4.length_enabled = false;
			channel4.initial_volume = 0;
			channel4.current_volume = 0;
			channel4.envelope_timer = 0;
			channel4.envelope_period = 0;
			channel4.envelope_increasing = false;
			channel4.frequency = 0;
			channel4.timer = 0;
			channel4.lfsr = 0x7FFF;
			channel4.clock_shift = 0;
			channel4.divisor_code = 0;
			channel4.width_mode = false;

			frame_sequencer_step = 7;

			// DMG: frame sequencer step is NOT reset on power-off
			// (CGB would reset it here)
		} else if (was_off) {
			// DMG power-on: reset frame sequencer step to 7 so the next step will be 0.
			frame_sequencer_step = 7;
		}
		return;
	}

	// APU is off — on DMG, only NRx1 length load registers are writable
	if (!(AUDENA & 0x80)) {
		std::cout << "[DEBUG_APU_OFF_WRITE] address=0x" << std::hex << address << " value=0x" << (int)value << std::dec << std::endl;
		switch (address) {
			case 0xFF11: // NR11 - CH1 length
				AUD1LEN = value & 0x3F;
				channel1.length_timer = 64 - (value & 0x3F);
				break;
			case 0xFF16: // NR21 - CH2 length
				AUD2LEN = value & 0x3F;
				channel2.length_timer = 64 - (value & 0x3F);
				break;
			case 0xFF1B: // NR31 - CH3 length
				AUD3LEN = value;
				channel3.length_timer = 256 - value;
				break;
			case 0xFF20: // NR41 - CH4 length
				AUD4LEN = value & 0x3F;
				channel4.length_timer = 64 - (value & 0x3F);
				break;
			default:
				break; // All other writes ignored when APU is off
		}
		return;
	}

	switch (address) {
		// master control
		case 0xFF24: AUDVOL		= value; break;
		case 0xFF25: AUDTERM	= value; break;

		// CHANNEL 1
		case 0xFF10: {
			AUD1SWEEP = value;
			channel1.sweep_shift = value & 0x7;
			channel1.sweep_period = (value >> 4) & 0x7;
			bool was_negate = channel1.sweep_negate;
			channel1.sweep_negate = value & 0x8;
			// Clearing negate after it was used disables the channel
			if (was_negate && !channel1.sweep_negate && channel1.sweep_negate_used) {
				channel1.enabled = false;
			}
			break;
		}
		case 0xFF11:
			AUD1LEN = value;
			channel1.length_timer = 64 - (value & 0x3F);
			channel1.duty_pattern = (value >> 6) & 0x3;
			traceLenEvent("LEN_WRITE", 1, frame_sequencer_step, channel1.length_timer, channel1.length_enabled, channel1.enabled);
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
		case 0xFF14: {
			std::cout << "[DEBUG_NR14] value=" << (int)value << " length_timer=" << (int)channel1.length_timer << " step=" << frame_sequencer_step << " AUDENA=" << (int)AUDENA << std::endl;
			if (value & 0x80) {
				std::cout << "[DEBUG_APU] total_cycles=" << total_cycles << " write NR14=" << (int)value << " (trigger) step=" << frame_sequencer_step << " len=" << channel1.length_timer << " len_en=" << (channel1.length_enabled ? 1 : 0) << std::endl;
			}
			AUD1HIGH = value;
			channel1.frequency = (channel1.frequency & 0x00FF) | ((value & 0x7) << 8);
			bool prev_length_enabled = channel1.length_enabled;
			channel1.length_enabled = value & 0x40;
			traceLenEvent("NRX4_PRE", 1, frame_sequencer_step, channel1.length_timer, channel1.length_enabled, channel1.enabled);

			if (!prev_length_enabled && channel1.length_enabled && (frame_sequencer_step % 2 == 0)) {
				if (channel1.length_timer > 0) {
					channel1.length_timer--;
					if (channel1.length_timer == 0) channel1.enabled = false;
				}
			}

			if (value & 0x80) {
				if (channel1.length_timer == 0) {
					channel1.length_timer = 64;
					if (channel1.length_enabled && (frame_sequencer_step % 2 == 0)) {
						channel1.length_timer--;
					}
				}
				channel1.trigger();
			}
			traceLenEvent("NRX4_POST", 1, frame_sequencer_step, channel1.length_timer, channel1.length_enabled, channel1.enabled);
			break;
		}
		// CHANNEL 2
		case 0xFF16:
			AUD2LEN = value;
			channel2.duty_pattern = (value >> 6) & 0x03;
			channel2.length_timer = 64 - (value & 0x3F);
			traceLenEvent("LEN_WRITE", 2, frame_sequencer_step, channel2.length_timer, channel2.length_enabled, channel2.enabled);
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
		case 0xFF19: {
			std::cout << "[DEBUG_NR24] value=" << (int)value << " length_timer=" << (int)channel2.length_timer << " step=" << frame_sequencer_step << std::endl;
			AUD2HIGH = value;
			channel2.frequency = (channel2.frequency & 0x00FF) | ((value & 0x07) << 8);
			bool prev_length_enabled2 = channel2.length_enabled;
			channel2.length_enabled = value & 0x40;
			traceLenEvent("NRX4_PRE", 2, frame_sequencer_step, channel2.length_timer, channel2.length_enabled, channel2.enabled);

			if (!prev_length_enabled2 && channel2.length_enabled && (frame_sequencer_step % 2 == 0)) {
				if (channel2.length_timer > 0) {
					channel2.length_timer--;
					if (channel2.length_timer == 0) channel2.enabled = false;
				}
			}

			if (value & 0x80) {
				if (channel2.length_timer == 0) {
					channel2.length_timer = 64;
					if (channel2.length_enabled && (frame_sequencer_step % 2 == 0)) {
						channel2.length_timer--;
					}
				}
				channel2.trigger();
			}
			traceLenEvent("NRX4_POST", 2, frame_sequencer_step, channel2.length_timer, channel2.length_enabled, channel2.enabled);
			break;
		}

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
			traceLenEvent("LEN_WRITE", 3, frame_sequencer_step, channel3.length_timer, channel3.length_enabled, channel3.enabled);
			break;
		case 0xFF1C:
			AUD3LEVEL = value;
			channel3.output_level = (value >> 5) & 0x03;
			break;
		case 0xFF1D:
			AUD3LOW = value;
			channel3.frequency = (channel3.frequency & 0x0700) | value;
			break;
		case 0xFF1E: {
			std::cout << "[DEBUG_NR34] value=" << (int)value << " length_timer=" << (int)channel3.length_timer << " step=" << frame_sequencer_step << std::endl;
			AUD3HIGH = value;
			channel3.frequency = (channel3.frequency & 0x00FF) | ((value & 0x07) << 8);
			bool prev_length_enabled3 = channel3.length_enabled;
			channel3.length_enabled = value & 0x40;
			traceLenEvent("NRX4_PRE", 3, frame_sequencer_step, channel3.length_timer, channel3.length_enabled, channel3.enabled);

			if ((!prev_length_enabled3 && channel3.length_enabled && (frame_sequencer_step % 2 == 0))) {
				if (channel3.length_timer > 0) {
					channel3.length_timer--;
					if (channel3.length_timer == 0) channel3.enabled = false;
				}
			}

			if (value & 0x80) {
				if (channel3.length_timer == 0) {
					channel3.length_timer = 256;
					if (channel3.length_enabled && (frame_sequencer_step % 2 == 0)) {
						channel3.length_timer--;
					}
				}
				channel3.trigger();
			}
			traceLenEvent("NRX4_POST", 3, frame_sequencer_step, channel3.length_timer, channel3.length_enabled, channel3.enabled);
			break;
		}

		// CHANNEL 4
		case 0xFF20:
			AUD4LEN = value;
			channel4.length_timer = 64 - (value & 0x3F);
			traceLenEvent("LEN_WRITE", 4, frame_sequencer_step, channel4.length_timer, channel4.length_enabled, channel4.enabled);
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
			channel4.width_mode = (value >> 3) & 0x01;
			channel4.divisor_code = value & 0x07;
			break;
		case 0xFF23: {
			std::cout << "[DEBUG_NR44] value=" << (int)value << " length_timer=" << (int)channel4.length_timer << " step=" << frame_sequencer_step << std::endl;
			AUD4GO = value;
			bool prev_length_enabled4 = channel4.length_enabled;
			channel4.length_enabled = value & 0x40;
			traceLenEvent("NRX4_PRE", 4, frame_sequencer_step, channel4.length_timer, channel4.length_enabled, channel4.enabled);

			if (!prev_length_enabled4 && channel4.length_enabled && (frame_sequencer_step % 2 == 0)) {
				if (channel4.length_timer > 0) {
					channel4.length_timer--;
					if (channel4.length_timer == 0) channel4.enabled = false;
				}
			}

			if (value & 0x80) {
				if (channel4.length_timer == 0) {
					channel4.length_timer = 64;
					if (channel4.length_enabled && (frame_sequencer_step % 2 == 0)) {
						channel4.length_timer--;
					}
				}
				channel4.trigger();
			}
			traceLenEvent("NRX4_POST", 4, frame_sequencer_step, channel4.length_timer, channel4.length_enabled, channel4.enabled);
			break;
		}
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
			return (AUDENA & 0x80) |
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

void AudioPU::stepFrameSequencer() {
	frame_sequencer_step = (frame_sequencer_step + 1) % 8;

	if (frame_sequencer_step % 2 == 0) {

		// step length
		if (channel1.length_enabled && channel1.length_timer > 0) {
			channel1.length_timer--;
			traceLenEvent("LEN_CLK", 1, frame_sequencer_step, channel1.length_timer, channel1.length_enabled, channel1.enabled);
			if (channel1.length_timer == 0) {
				channel1.enabled = false;
				traceLenEvent("LEN_OFF", 1, frame_sequencer_step, channel1.length_timer, channel1.length_enabled, channel1.enabled);
			}
		}
		if (channel2.length_enabled && channel2.length_timer > 0) {
			channel2.length_timer--;
			traceLenEvent("LEN_CLK", 2, frame_sequencer_step, channel2.length_timer, channel2.length_enabled, channel2.enabled);
			if (channel2.length_timer == 0) {
				channel2.enabled = false;
				traceLenEvent("LEN_OFF", 2, frame_sequencer_step, channel2.length_timer, channel2.length_enabled, channel2.enabled);
			}
		}
		if (channel3.length_enabled && channel3.length_timer > 0) {
			channel3.length_timer--;
			traceLenEvent("LEN_CLK", 3, frame_sequencer_step, channel3.length_timer, channel3.length_enabled, channel3.enabled);
			if (channel3.length_timer == 0) {
				channel3.enabled = false;
				traceLenEvent("LEN_OFF", 3, frame_sequencer_step, channel3.length_timer, channel3.length_enabled, channel3.enabled);
			}
		}
		if (channel4.length_enabled && channel4.length_timer > 0) {
			channel4.length_timer--;
			traceLenEvent("LEN_CLK", 4, frame_sequencer_step, channel4.length_timer, channel4.length_enabled, channel4.enabled);
			if (channel4.length_timer == 0) {
				channel4.enabled = false;
				traceLenEvent("LEN_OFF", 4, frame_sequencer_step, channel4.length_timer, channel4.length_enabled, channel4.enabled);
			}
		}
	}

	if (frame_sequencer_step == 7) {
		stepEnvelope();
	}

	if (frame_sequencer_step == 2 || frame_sequencer_step == 6) {
		stepSweep();
	}
}

void AudioPU::stepEnvelope() {
	if (channel1.envelope_period != 0) {
		if (channel1.envelope_timer > 0) {
			channel1.envelope_timer--;
		}
		if (channel1.envelope_timer == 0) {
			channel1.envelope_timer = channel1.envelope_period;
			if (channel1.envelope_increasing && channel1.current_volume < 15) {
				channel1.current_volume++;
			}
			else if (!channel1.envelope_increasing && channel1.current_volume > 0) {
				channel1.current_volume--;
			}
		}
	}

	if (channel2.envelope_period != 0) {
		if (channel2.envelope_timer > 0) {
			channel2.envelope_timer--;
		}
		if (channel2.envelope_timer == 0) {
			channel2.envelope_timer = channel2.envelope_period;
			if (channel2.envelope_increasing && channel2.current_volume < 15) {
				channel2.current_volume++;
			}
			else if (!channel2.envelope_increasing && channel2.current_volume > 0) {
				channel2.current_volume--;
			}
		}
	}
}

void AudioPU::stepSweep() {
	if (channel1.sweep_enabled) {
		if (channel1.sweep_timer > 0) {
			channel1.sweep_timer--;
		}
		if (channel1.sweep_timer == 0) {
			// Reload timer: period=0 treated as 8
			channel1.sweep_timer = (channel1.sweep_period > 0) ? channel1.sweep_period : 8;

			// Only perform frequency calculation when period > 0
			if (channel1.sweep_period > 0) {
				int new_freq = channel1.shadow_frequency >> channel1.sweep_shift;
				if (channel1.sweep_negate) {
					new_freq = channel1.shadow_frequency - new_freq;
					channel1.sweep_negate_used = true;
				}
				else {
					new_freq = channel1.shadow_frequency + new_freq;
				}

				// Overflow check
				if (new_freq > 2047) {
					channel1.enabled = false;
				}

				if (new_freq <= 2047 && channel1.sweep_shift > 0) {
					channel1.shadow_frequency = new_freq;
					channel1.frequency = new_freq;

					AUD1LOW = new_freq & 0xFF;
					AUD1HIGH = (AUD1HIGH & 0xF8) | ((new_freq >> 8) & 0x07);

					// Second overflow check (does NOT update frequency)
					int second_freq = new_freq >> channel1.sweep_shift;
					if (channel1.sweep_negate) {
						second_freq = new_freq - second_freq;
					}
					else {
						second_freq = new_freq + second_freq;
					}
					if (second_freq > 2047) {
						channel1.enabled = false;
					}
				}
			}
		}
	}
}


void AudioPU::SquareChannel::trigger() {
	enabled = dac_enabled;
	timer = (2048 - frequency) * 4;
	current_volume = initial_volume;
	envelope_timer = envelope_period;
	shadow_frequency = frequency;

	if (has_sweep) {
		sweep_negate_used = false;
		sweep_timer = (sweep_period > 0) ? sweep_period : 8;
		sweep_enabled = (sweep_period > 0) || (sweep_shift > 0);
		if (sweep_shift > 0) {
			int delta = shadow_frequency >> sweep_shift;
			int new_freq;
			if (sweep_negate) {
				new_freq = shadow_frequency - delta;
				sweep_negate_used = true;
			}
			else {
				new_freq = shadow_frequency + delta;
			}
			if (new_freq > 2047) {
				enabled = false;
			}
		}
	}
}

void AudioPU::WaveChannel::trigger() {
	enabled = dac_enabled;
	timer = (2048 - frequency) * 2;
	position = 0;
}

void AudioPU::NoiseChannel::trigger() {
	enabled = dac_enabled;
	int divisors[8] = {8, 16, 32, 48, 64, 80, 96, 112};
	timer = divisors[divisor_code] << clock_shift;
	lfsr = 0x7FFF;
	current_volume = initial_volume;
	envelope_timer = envelope_period;
}

void AudioPU::tick(unsigned int cycles) {
	total_cycles += cycles;
	/*
	static bool prev_ch1_enabled = false;
	if (prev_ch1_enabled && !channel1.enabled) {
		std::cout << "[DEBUG_APU] total_cycles=" << total_cycles << " CH1 DISABLED! step=" << frame_sequencer_step << std::endl;
	}
	prev_ch1_enabled = channel1.enabled;
	*/

	if (!(AUDENA & 0x80)) {
		return;
	}

	channel1.tick(cycles);
	channel2.tick(cycles);
	channel3.tick(cycles);
	channel4.tick(cycles);

	sample_timer += cycles;
	if (sample_timer >= CLOCKS_PER_SAMPLE) {
		sample_timer -= CLOCKS_PER_SAMPLE;

		int sample = 0;
		sample += (channel1.enabled && channel1.dac_enabled) ? channel1.getOutput() : 0;
		sample += (channel2.enabled && channel2.dac_enabled) ? channel2.getOutput() : 0;
		sample += (channel3.enabled && channel3.dac_enabled) ? channel3.getOutput() : 0;
		sample += (channel4.enabled && channel4.dac_enabled) ? channel4.getOutput() : 0;

		float normalize = sample / 30.0f;
		normalize -= 1.0f;

		normalize *= 0.5f; // adjust volume

		int16_t output_sample = static_cast<int16_t>(normalize * 32767.0f);
		masterRingBuffer.push(output_sample);
	}
}

void AudioPU::divApuTick() {
	if (!(AUDENA & 0x80)) {
		return;
	}
	stepFrameSequencer();
}

void AudioPU::SquareChannel::tick(unsigned int cycles) {
	if (!enabled) return;
	timer -= cycles;
	while (timer <= 0) {
		timer += (2048 - frequency) * 4;
		duty_position = (duty_position + 1) % 8;
	}
}

void AudioPU::WaveChannel::tick(unsigned int cycles) {
	if (!enabled) return;
	timer -= cycles;
	while (timer <= 0) {
		timer += (2048 - frequency) * 2;
		position = (position + 1) % 32;
	}
}

void AudioPU::NoiseChannel::tick(unsigned int cycles) {
	if (!enabled) return;
	timer -= cycles;
	while (timer <= 0) {
		int divisors[8] = { 8, 16, 32, 48, 64, 80, 96, 112 };
		timer += divisors[divisor_code] << clock_shift;

		int bit = (lfsr & 0x1) ^ ((lfsr >> 1) & 0x1);
		lfsr >>= 1;
		lfsr |= (bit << 14);
		if (width_mode) {
			lfsr &= ~0x40;
			lfsr |= (bit << 6);
		}
	}
}

uint8_t AudioPU::SquareChannel::getOutput() {
	if (!enabled || !dac_enabled) return 0;
	const uint8_t duties[4] = { 0x01, 0x81, 0x87, 0x7E };
	bool output = (duties[duty_pattern] >> duty_position) & 0x1;
	return output ? current_volume : 0;
}

uint8_t AudioPU::WaveChannel::getOutput() {
	if (!enabled || !dac_enabled || wave_ram == nullptr) {
		return 0;
	}
	uint8_t byte = (*wave_ram)[position / 2];
	uint8_t sample = (position % 2 == 0) ? (byte >> 4) : (byte & 0x0F);

	if (output_level == 0) {
		return 0;
	}
	return sample >> (output_level - 1);
}

uint8_t AudioPU::NoiseChannel::getOutput() {
	if (!enabled || !dac_enabled) return 0;
	return (lfsr & 0x1) ? 0 : current_volume;
}