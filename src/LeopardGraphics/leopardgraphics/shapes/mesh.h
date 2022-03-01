#pragma once

#include <jaguarcore/math/math.h>
#include <leopardgraphics/graphics/glgraphics/glgraphics.h>

#include <leopardgraphics/shapes/shape.h>
#include <vector>

namespace lpd
{
	class Shader;
	class Pose;

	class Mesh : public Shape
	{
	public:
		void Set();
		void Bind(Shader& shader) override;
		void Unbind(Shader& shader) override;

		void Render(const Shader& shader);

		inline void SetPose(const Pose* pose) { m_Pose = pose; }

		std::vector<vec3> m_Position;
		std::vector<vec3> m_Normal;
		
		std::vector<ivec4> m_Joints;
		std::vector<vec4> m_Weights;

		std::vector<unsigned int> m_Indices;

		Attribute<vec3> m_PosAttrib;
		Attribute<vec3> m_NormalAttrib;

		Attribute<ivec4> m_JointsAttrib;
		Attribute<vec4> m_WeightsAttrib;

		ElementBuffer m_ElementBuffer;

	private:
		const Pose* m_Pose;
	};

}