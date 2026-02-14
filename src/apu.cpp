#include "../include/apu.hpp"
#include <cmath>

#include <iostream>

void AudioPU::writeMem(uint16_t address, uint8_t value) {
	if (address >= channel3.WAVE_PATTERN_RAM_OFFSET && \
		address < channel3.WAVE_PATTERN_RAM_OFFSET + channel3.WAVE_PATTERN_RAM_SIZE) {
		channel3.wave_pattern[address - channel3.WAVE_PATTERN_RAM_OFFSET] = value;
		return;
	}

	switch (address) {
		// master control
		case 0xFF24: AUDVOL		= value; break;
		case 0xFF25: AUDTERM	= value; break;
		case 0XFF26: AUDENA		= value; break;

		// CHANNEL 1
		case 0xFF10: channel1.AUD1SWEEP	= value; break;
		case 0xFF11: channel1.AUD1LEN	= value; break;
		case 0xFF12: channel1.AUD1ENV	= value; break;
		case 0xFF13: channel1.AUD1LOW	= value; break;
		case 0xFF14: channel1.AUD1HIGH	= value; break;

		// CHANNEL 2
		case 0xFF16: 
			channel2.AUD2LEN = value; 
			channel2.length_timer = 64 - (value & 0x3F);
			break;
		case 0xFF17: channel2.AUD2ENV	= value; break;
		case 0xFF18: channel2.AUD2LOW	= value; break;
		case 0xFF19: 
			channel2.AUD2HIGH = value; 
			if (value & 0x80) channel2.trigger();
			break;

		// CHANNEL 3
		case 0xFF1A: channel3.AUD3ENA	= value; break; 
		case 0xFF1B: 
			channel3.AUD3LEN = value; 
			channel3.length_timer = 256 - value;
			break;
		case 0xFF1C: channel3.AUD3LEVEL	= value; break;
		case 0xFF1D: channel3.AUD3LOW	= value; break;
		case 0xFF1E: 
			channel3.AUD3HIGH = value; 
			if (value & 0x80) channel3.trigger();
			break;

		// CHANNEL 4
		case 0xFF20: AUD4LEN	= value; break;
		case 0xFF21: AUD4ENV	= value; break;
		case 0xFF22: AUD4POLY	= value; break;
		case 0xFF23: AUD4GO		= value; break;
	}
}

uint8_t AudioPU::readMem(uint16_t address) const {
	if (address >= channel3.WAVE_PATTERN_RAM_OFFSET && \
		address < channel3.WAVE_PATTERN_RAM_OFFSET + channel3.WAVE_PATTERN_RAM_SIZE) {
		return channel3.wave_pattern[address - channel3.WAVE_PATTERN_RAM_OFFSET];
	}

	switch (address) {
		// master control
		case 0xFF24: return AUDVOL;
		case 0xFF25: return AUDTERM;
		case 0XFF26: return AUDENA;

		// CHANNEL 1
		case 0xFF10: return channel1.AUD1SWEEP;
		case 0xFF11: return channel1.AUD1LEN;
		case 0xFF12: return channel1.AUD1ENV;
		case 0xFF13: return channel1.AUD1LOW;
		case 0xFF14: return channel1.AUD1HIGH;

		// CHANNEL 2
		case 0xFF16: return channel2.AUD2LEN;
		case 0xFF17: return channel2.AUD2ENV;
		case 0xFF18: return channel2.AUD2LOW;
		case 0xFF19: return channel2.AUD2HIGH;

		// CHANNEL 3
		case 0xFF1A: return channel3.AUD3ENA;
		case 0xFF1B: return channel3.AUD3LEN;
		case 0xFF1C: return channel3.AUD3LEVEL;
		case 0xFF1D: return channel3.AUD3LOW;
		case 0xFF1E: return channel3.AUD3HIGH;

		// CHANNEL 4
		case 0xFF20: return AUD4LEN;
		case 0xFF21: return AUD4ENV;
		case 0xFF22: return AUD4POLY;
		case 0xFF23: return AUD4GO;
	}

	return 0;
}

// this is triggered every 8192 cycles
	/*
	* Reference of the frame sequencer things
	* Step   Length Ctr  Vol Env     Sweep
	* ---------------------------------------
	* 0      Clock       -           -
	* 1      -           -           -
	* 2      Clock       -           Clock
	* 3      -           -           -
	* 4      Clock       -           -
	* 5      -           -           -
	* 6      Clock       -           Clock
	* 7      -           Clock       -
	* ---------------------------------------
	* Rate   256 Hz      64 Hz       128 Hz
*/


void AudioPU::SquareChannel2::tick() {
	const uint8_t wave_duty = (AUD2LEN & 0xC0) >> 6;

	static constexpr uint8_t duty_cycles[4] = {
		0b00000001,
		0b00000011,
		0b00001111,
		0b11111100
	};

	if (frequency_timer > 0) {
		frequency_timer--;
	}

	if (frequency_timer == 0) {
		const uint16_t frequency = ((AUD2HIGH & 0x07) << 8) | AUD2LOW;
		frequency_timer = (2048 - frequency) * 4; // this formula is hardcoded
		wave_duty_position = (wave_duty_position + 1) % 8;

		const uint8_t wave_duty = (AUD2LEN & 0xC0) >> 6;
		last_bit = (duty_cycles[wave_duty] >> wave_duty_position) & 1;
	}
}

void AudioPU::WaveChannel::tick() {
	if (frequency_timer > 0) {
		frequency_timer--;
	}

	if (frequency_timer == 0) {
		const uint16_t frequency = ((AUD3HIGH & 0x07) << 8) | AUD3LOW;
		frequency_timer = (2048 - frequency) * 2;
		wave_sample_index = (wave_sample_index + 1) % 32; // 32 coz 16 entries, each entry is 2 vals

		if (wave_sample_index % 2 == 0) {
			uint8_t address = wave_sample_index / 2;
			sample_buffer = wave_pattern[address];
		}
	}
}

void AudioPU::SquareChannel2::trigger() {
	//std::cout << "Square channel 2 triggered" << std::endl;
	enabled = true;

	wave_duty_position = 0;

	const uint16_t frequency = ((AUD2HIGH & 0x07) << 8) | AUD2LOW;
	frequency_timer = (2048 - frequency) * 4; // this formula is hardcoded

	current_volume = (AUD2ENV & 0xF0) >> 4;
	envelope_timer = (AUD2ENV & 0x07);

	if (length_timer == 0) length_timer = 64;

	bool dac = (AUD2ENV & 0xF8) != 0;
	if (!dac) {
		enabled = false;
	}
}

void AudioPU::WaveChannel::trigger() {
	enabled = true;

	wave_sample_index = 0;

	const uint16_t frequency = ((AUD3HIGH & 0x07) << 8) | AUD3LOW;
	frequency_timer = (2048 - frequency) * 2;

	if (length_timer == 0) length_timer = 256;

	bool dac = (AUD3ENA & 0x80) != 0;
	if (!dac) {
		enabled = false;
	}
}

void AudioPU::SquareChannel2::tickLength() {
	if ((AUD2HIGH & 0x40) && length_timer > 0) {
		length_timer--;
		if (length_timer == 0) {
			enabled = false;
		}
	}
}

void AudioPU::WaveChannel::tickLength() {
	if ((AUD3HIGH & 0x40) && length_timer > 0) {
		length_timer--;
		if (length_timer == 0) {
			enabled = false;
		}
	}
}

void AudioPU::SquareChannel2::tickEnvelope() {
	uint8_t pace = AUD2ENV & 0x07;
	if (pace == 0) return;

	if (envelope_timer > 0) {
		envelope_timer--;
	}

	if (envelope_timer == 0) {
		envelope_timer = pace;
		bool increase = (AUD2ENV & 0x08) != 0; // Bit 3 -> gives direction 
		if (increase && current_volume < 15) {
			current_volume++;
		}
		else if (!increase && current_volume > 0) {
			current_volume--;
		}
	}
}

float AudioPU::SquareChannel2::getOutput() {
	if (!enabled) return 0;
	uint8_t vol = (last_bit == 1) ? current_volume : 0;
	return vol / 15.0f;
}

float AudioPU::WaveChannel::getOutput() {
	if (!enabled) return 0.0f;

	uint8_t vol;
	if (wave_sample_index % 2 == 0) vol = (sample_buffer >> 4);
	else vol = (sample_buffer & 0xF);


	uint8_t shift_code = (AUD3LEVEL & 0x60) >> 5;

	if (shift_code == 0) return 0.0f;

	uint8_t shifted_vol = (vol >> (shift_code - 1));
	return shifted_vol / 15.0f;
}


void AudioPU::updateFrameSequencer() {
	frame_sequencer_counter = (frame_sequencer_counter + 1) % 8;
	switch (frame_sequencer_counter) {
		case 0:
			channel2.tickLength(); 
			channel3.tickLength();
			break;
		case 2:
			channel2.tickLength();
			channel3.tickLength();
			break;
		case 4:
			channel2.tickLength();
			channel3.tickLength();
			break;
		case 6:
			channel2.tickLength();
			channel3.tickLength();
			break;
		case 7:
			channel2.tickEnvelope();
			break;
	}
}


void AudioPU::tick(int num_cycles) {
	while (num_cycles--) {
		this->tick();
	}
}

void AudioPU::tick() {
	//channel1.tick();
	channel2.tick();
	channel3.tick();
	//channel4.tick();

	cycle_accumulator++;
	if (cycle_accumulator >= 8192) {
		cycle_accumulator = 0;
		updateFrameSequencer();
	}

	// just doing it in mono for now coz i'm too lazy to handle stereo
	//float current_mono = (channel1.getOutput() +
	//	channel2.getOutput() +
	//	channel3.getOutput() +
	//	channel4.getOutput()) / 4.0f;

	float current_mono = (channel2.getOutput() + channel3.getOutput()) / 2.0f;

	sample_accumulator += current_mono;
	sample_count++;

	//std::cout << sample_count << std::endl;

	if (sample_count >= 95) {
		float final_sample = sample_accumulator / (float)sample_count;
		int16_t sample_output = static_cast<int16_t>(std::round(final_sample * 30000.0f));

		masterRingBuffer.push(sample_output);

		sample_accumulator = 0.0f;
		sample_count = 0;
	}
}

float AudioPU::AudioChannel::getOutput() { return 0.0f; }

void AudioPU::AudioChannel::tick() { }

AudioRingBuffer* AudioPU::getAudioBuffer() {
	return &this->masterRingBuffer;
}
