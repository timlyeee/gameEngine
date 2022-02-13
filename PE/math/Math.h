#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
namespace glm {

	class mMath {
	public:
		mMath();
		void transform(mat4 transMatrix, vec4& vec);

	private:
		mat4 defaultTrans;
	};

}
