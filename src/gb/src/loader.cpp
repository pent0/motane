#include <gb/loader.h>

#include <fstream>
#include <cassert>

namespace motane {
	namespace gb {
		GameboyRom load(const std::string path) {
			GameboyRom res; 
			s16 tempPub;
			std::ifstream file(path);
			assert(file);

			res.title.resize(15);

			file.seekg(GB_TITLE_POINT);
			file.read(&res.title[0], 15);

			file.seekg(GB_CART_TYPE_POINT);
			file.read(reinterpret_cast<char*>(&res.cart), sizeof(GameboyCart));

			file.seekg(GB_OLD_PUB_CODE_POINT);
			file.read(reinterpret_cast<char*>(&tempPub), sizeof(GameboyPublisher));

			if (tempPub == GB_IS_NEW_PUB_CODE_POINT) {
				file.seekg(GB_NEW_PUB_CODE_POINT);
				file.read(reinterpret_cast<char*>(&res.publisher), sizeof(GameboyPublisher));
			} else {
				res.publisher = static_cast<GameboyPublisher>(tempPub);
			}

			u8 temp1, temp2;

			file.seekg(GB_ROM_SIZE_POINT);
			file.read(reinterpret_cast<char*>(&temp1), sizeof(u8));
			file.read(reinterpret_cast<char*>(&temp2), sizeof(u8));

			res.ramSize = (32 * 1024) << temp2;
			res.romSize = (32 * 1024) << temp1;

			file.seekg(GB_SJAP_POINT);
			file.read(reinterpret_cast<char*>(&res.japExclusive), sizeof(bool));

			file.seekg(GB_CGB_FLAG_POINT);
			file.read(reinterpret_cast<char*>(&res.cgbFlag), sizeof(u8));

			file.seekg(GB_SGB_FLAG_POINT);
			file.read(reinterpret_cast<char*>(&res.sgbFlag), sizeof(u8));

			file.seekg(GB_MANU_POINT);
			file.read(reinterpret_cast<char*>(&res.manufactuerCode), sizeof(u32));

			return res;
		}
	}
}