#pragma once

#include <utils/type.h>
#include <tuple>

namespace motane {
	s16 make_s16(s8 h, s8 l);
	std::pair<s8, s8> extract_s16(s16 hl);
}