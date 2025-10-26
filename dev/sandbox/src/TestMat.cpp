#include "TestMat.h"

namespace test {

	numa::Mat<float, 2, 2> CreateMat2Float(float val) {
		return numa::Mat<float, 2, 2>(val);
	}

}