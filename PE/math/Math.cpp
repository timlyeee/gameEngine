#include "math.h"
namespace glm {
	mMath::mMath(): 
		defaultTrans(glm::mat4(1.0f)) {
		
	}

	void mMath::transform(mat4 transMatrix, vec4& vec) {
		vec = transMatrix * vec;
	}
}