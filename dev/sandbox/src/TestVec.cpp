#include "TestVec.h"

namespace test {

	numa::Vec<float, 2> CreateVec2Float(float val) {
		return numa::Vec<float, 2>(val);
	}

}