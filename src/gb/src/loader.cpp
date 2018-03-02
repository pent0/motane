/*
	Motane
	Copyright (C) 2018 Do Trong Thu

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <gb/loader.h>

#include <fstream>
#include <cassert>

namespace motane {
	namespace gb {
		Rom load(const std::string path) {
			Rom res; 
			s16 tempPub;
			std::ifstream file(path);
			assert(file);

			res.title.resize(15);

			file.seekg(GB_TITLE_POINT);
			file.read(&res.title[0], 15);

			file.seekg(GB_CART_TYPE_POINT);
			file.read(reinterpret_cast<char*>(&res.cart), sizeof(Cart));

			file.seekg(GB_OLD_PUB_CODE_POINT);
			file.read(reinterpret_cast<char*>(&tempPub), sizeof(Publisher));

			if (tempPub == GB_IS_NEW_PUB_CODE_POINT) {
				file.seekg(GB_NEW_PUB_CODE_POINT);
				file.read(reinterpret_cast<char*>(&res.publisher), sizeof(Publisher));
			} else {
				res.publisher = static_cast<Publisher>(tempPub);
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