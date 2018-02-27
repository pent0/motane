#pragma once

#include <utils/type.h>

#include <string>

namespace motane {
	namespace gb {
		enum {
			GB_ENTRY_POINT = 0x100,
			GB_TITLE_POINT = 0x134,
			GB_TITLE_MXLEN = 15,
			GB_MANU_POINT = 0x13F,
			GB_MANU_LEN = 4,
			GB_CGB_FLAG_POINT = 0x143,
			GB_OLD_PUB_CODE_POINT = 0x14B,
			GB_NEW_PUB_CODE_POINT = 0x144,
			GB_SGB_FLAG_POINT = 0x146,
			GB_CART_TYPE_POINT = 0x147,
			GB_ROM_SIZE_POINT = 0x148,
			GB_RAM_SIZE_POINT = 0x149,
			GB_SJAP_POINT = 0x14A,
			GB_IS_NEW_PUB_CODE_POINT = 0x33
		};

		enum class GameboyPublisher: u8 {
            #define PUBLISHER(x, y, z) y = x,
                 #include "loader.def"
			LastNoSense
		};

		enum class GameboyCart: u8 {
			ROM_ONLY = 0x00,
			MBC5 = 0x19,
			MBC1 = 0x01,
			MBC5_AND_RAM = 0x1A,
			MBC1_AND_RAM = 0x02,
			MBC5_AND_RAM_AND_BATTERY = 0x1B,
			MBC1_AND_RAM_AND_BATTERY = 0x03,
			MBC5_AND_RUMBLE = 0x1C,
			MBC2 = 0x05,
			MBC5_AND_RUMBLE_AND_RAM = 0x1D,
			MBC2_AND_BATTERY = 0x06,
			MBC5_AND_RUMBLE_AND_RAM_AND_BATTERY = 0x1E,
			ROM_AND_RAM = 0x08,
			MBC6 = 0x20,
			ROM_AND_RAM_AND_BATTERY = 0x09,
			MBC7_AND_SENSOR_AND_RUMBLE_AND_RAM_AND_BATTERY = 0x22,
			MMM01 = 0x0B,
			MMM01_AND_RAM = 0x0C,
			MMM01_AND_RAM_AND_BATTERY = 0x0D,
			MBC3_AND_TIMER_AND_BATTERY = 0x0F,
			MBC3_AND_TIMER_AND_RAM_AND_BATTERY = 0x10,
			POCKET_CAMERA = 0xFC,
			MBC3 = 0x11,
			BANDAI_TAMA5 = 0xFD,
			MBC3_AND_RAM = 0x12,
			HuC3 = 0xFE,
			MBC3_AND_RAM_AND_BATTERY = 0x13,
			HuC1_AND_RAM_AND_BATTERY = 0xFF,
			LAST_NOSENSE
		};

		struct GameboyRom {
			GameboyPublisher publisher;
			GameboyCart      cart;
			std::string      title;
			u32              manufactuerCode;

			u8               cgbFlag, sgbFlag;
			bool             japExclusive;

			u32               romSize, ramSize;
		};

		GameboyRom load(const std::string path);
	}
}