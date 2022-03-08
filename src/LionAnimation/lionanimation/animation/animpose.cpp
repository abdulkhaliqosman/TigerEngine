#include <lionanimation/lionpch.h>
#include "animpose.h"
#include "optick.h"

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
		OPTICK_EVENT();
		auto sz = m_Joints.size();

		for (int i = 0; i < sz; ++i)
		{
			m_Joints[i].computedGlobal = false;
			m_Joints[i].computedLocal = false;
		}

		for (int i = 0; i < sz; ++i)
		{
			ComputeTransform(i);
		}

		m_JointTransforms.resize(sz);
		for (int i = 0; i < sz; ++i)
		{
			m_JointTransforms[i] = m_Joints[i].globalTransform * m_Joints[i].m_InverseBindMatrices;
		}
	}

	mat4 AnimPose::ComputeTransform(int id)
	{
		Joint& joint = m_Joints[id];
		if (!joint.computedLocal)
		{
			joint.localTransform = jgr::Transform::CreateTransformMatrix(joint.position, joint.rotation, joint.scale);
			joint.computedLocal = true;
		}

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
			joint.globalTransform = ComputeTransform(joint.m_ParentId) * joint.localTransform;
		}

		joint.computedGlobal = true;
		return joint.globalTransform;
	}
}