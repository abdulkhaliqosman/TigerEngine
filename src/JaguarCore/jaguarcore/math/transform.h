#pragma once

#include "vector.h"
#include "matrix.h"
#include "quaternion.h"

namespace jgr
{
	namespace Transform
	{
		inline mat4 CreateTranslateMatrix(vec3 translate)
		{
			auto ret = mat4::Identity();

			ret[3] = vec4{ translate.x(), translate.y(), translate.z(), 1.0f };

			return ret;
		}

		inline mat4 CreateRotateMatrix(quat rotate)
		{
			auto ret = mat4::Identity();

			ret[0] = rotate * vec4::Right();
			ret[1] = rotate * vec4::Up();
			ret[2] = rotate * vec4::Forward();

			return ret;
		}

		inline mat4 CreateScaleMatrix(vec3 scale)
		{
			auto ret = mat4::Identity();

			ret[0][0] = scale.x();
			ret[1][1] = scale.y();
			ret[2][2] = scale.z();

			return ret;
		}

		inline mat4 CreateTransformMatrix(vec3 translate, quat rotate, vec3 scale)
		{
			return CreateTranslateMatrix(translate) * CreateRotateMatrix(rotate) * CreateScaleMatrix(scale);
		}
	};
}
