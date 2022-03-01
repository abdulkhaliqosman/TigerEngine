#include <lionanimation/lionpch.h>
#include "animpose.h"

namespace lion
{
	int AnimPose::GetIndex(const std::string& id) const
	{
		auto it = m_NameJointMap.find(id);
		if (it == m_NameJointMap.end())
		{
			return Joint::INVALID_ID;
		}

		return it->second;
	}

	void AnimPose::AddJoint(const Joint& joint)
	{
		auto it = m_NameJointMap.find(joint.m_Name);
		if (it != m_NameJointMap.end())
		{
			*(int*)nullptr;
		}

		m_NameJointMap[joint.m_Name] = m_Joints.size();
		m_Joints.push_back(joint);
	}

	void AnimPose::ComputeGlobalTransforms()
	{
		auto sz = m_Joints.size();

		for (int i = 0; i < sz; ++i)
		{
			m_Joints[i].computedGlobal = false;
		}

		for (int i = 0; i < sz; ++i)
		{
			ComputeGlobalTransform(i);
		}

		m_JointTransforms.resize(sz);
		for (int i = 0; i < sz; ++i)
		{
			m_JointTransforms[i] = m_Joints[i].globalTransform * m_Joints[i].m_InverseBindMatrices;
		}
	}

	mat4 AnimPose::ComputeGlobalTransform(int id)
	{
		Joint& joint = m_Joints[id];

		if (joint.computedGlobal)
		{
			return joint.globalTransform;
		}

		// TODO: Optimize as a tree
		if (joint.m_ParentId == Joint::INVALID_ID)
		{
			joint.globalTransform = joint.localTransform;;
		}
		else
		{
			joint.globalTransform = ComputeGlobalTransform(joint.m_ParentId) * joint.localTransform;;
		}

		joint.computedGlobal = true;
		return joint.globalTransform;
	}
}