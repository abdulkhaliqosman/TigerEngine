#pragma once

#include <vector>
#include <string>
#include <unordered_map>

namespace lion
{
	struct Joint
	{
		vec3 position;
		vec3 scale;
		quat rotation;

		mat4 localTransform = mat4::Identity();
		mat4 globalTransform = mat4::Identity();

		bool computedGlobal = false;

		int m_Id = -1;
		int m_ParentId = -1;
		std::string m_Name;
		std::vector<int> m_ChildrenId;

		mat4 m_InverseBindMatrices = mat4::Identity();

		static constexpr int INVALID_ID = -1;
	};

	using JointIndexMap = std::unordered_map<std::string, int>;

	class AnimPose
	{
	public:
		int GetIndex(const std::string& str) const;

		inline const Joint& GetJoint(int i) const { return m_Joints[i]; }
		inline Joint& GetJoint(int i) { return m_Joints[i]; }

		void AddJoint(const Joint& joint);

		// for now we do the easy way out, later we optimize
		void ComputeGlobalTransforms();

		inline mat4 GetGlobalTransform(int id) const { return m_Joints[id].globalTransform; };
		inline size_t Size() const { return m_Joints.size(); }

		const std::vector<mat4>& GetJointTransforms() const { return m_JointTransforms; }

	private:
		mat4 ComputeGlobalTransform(int id);
		std::vector<Joint> m_Joints;

		std::vector<mat4> m_JointTransforms;

		JointIndexMap m_NameJointMap;
	};
}