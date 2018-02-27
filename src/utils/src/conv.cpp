#include <utils/conv.h>

namespace motane {
	s16 make_s16(s8 h, s8 l) {
		return h << 8 + l;
	}

	std::pair<s8, s8> extract_s16(s16 hl) {
		return std::make_pair((hl >> 8) & 255, hl & 255);
	}
}