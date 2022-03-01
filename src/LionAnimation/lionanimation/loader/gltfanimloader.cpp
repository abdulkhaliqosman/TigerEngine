#include <lionanimation/lionpch.h>
#include "gltfanimloader.h"

#include "lionanimation/animation/animclip.h"
#include "lionanimation/animation/animpose.h"
#include "jaguarcore/filetypes/gltf/gltfloader.h"
#include "cgltf/cgltf.h"
#include <iostream>


namespace lion
{

	namespace gltfloader
	{
		InterpolationType InterpolationGLTFToAnim(cgltf_interpolation_type type)
		{
			switch (type)
			{
			case cgltf_interpolation_type_linear:
				return InterpolationType::Linear;
			case cgltf_interpolation_type_step:
				return InterpolationType::Step;
			case cgltf_interpolation_type_cubic_spline:
				return InterpolationType::Cubic;
			}

			return InterpolationType::Invalid;
		}

		AnimPoseClip* LoadClip(const cgltf_animation& anim)
		{
			AnimPoseClip* clip = new AnimPoseClip;

			for (int i = 0; i < anim.channels_count; ++i)
			{
				const cgltf_animation_channel& channel = anim.channels[i];

				int idx = clip->GetIndex(channel.target_node->name);
				if (idx == Joint::INVALID_ID)
				{
					JointTrack track;
					track.m_Name = channel.target_node->name;
					clip->AddTrack(track);
					idx = clip->GetIndex(channel.target_node->name);
				}

				const cgltf_animation_sampler& sampler = *channel.sampler;

				cgltf_animation_path_type type = channel.target_path;

				InterpolationType interpType = InterpolationGLTFToAnim(sampler.interpolation);

				std::vector<float> time;

				cgltf_accessor* inAccessor = sampler.input;
				for (int j = 0; j < inAccessor->count; ++j)
				{
					float val;
					cgltf_accessor_read_float(inAccessor, j, &val, 1);
					time.push_back(val);

					if (clip->GetEndTime() < val)
					{
						clip->SetEndTime(val);
					}
				}

				cgltf_accessor* outAccessor = sampler.output;

				switch (type)
				{
				case cgltf_animation_path_type_invalid:
					// cry
					break;

				case cgltf_animation_path_type_translation:
				{
					if (outAccessor->type == cgltf_type_vec3)
					{
						auto& positionTrack = clip->GetTrack(idx).m_TransformTrack.positionTrack;
						positionTrack.SetInterpolationType(interpType);

						for (int j = 0; j < outAccessor->count; ++j)
						{
							vec3 vec;
							AnimFrameVec3 frame;
							cgltf_accessor_read_float(outAccessor, j, &vec[0], 3);
							frame.value = vec;
							frame.time = time[j];

							positionTrack.AddFrame(frame);
						}
					}
				}
				break;

				case cgltf_animation_path_type_rotation:
				{
					if (outAccessor->type == cgltf_type_vec4)
					{
						auto& rotationTrack = clip->GetTrack(idx).m_TransformTrack.rotationTrack;
						rotationTrack.SetInterpolationType(interpType);

						for (int j = 0; j < outAccessor->count; ++j)
						{
							quat quat;
							AnimFrameQuat frame;
							cgltf_accessor_read_float(outAccessor, j, &quat[0], 4);
							frame.value = quat;
							frame.time = time[j];

							rotationTrack.AddFrame(frame);
						}
					}
				}
				break;

				case cgltf_animation_path_type_scale:
				{
					if (outAccessor->type == cgltf_type_vec3)
					{
						auto& scaleTrack = clip->GetTrack(idx).m_TransformTrack.scaleTrack;
						scaleTrack.SetInterpolationType(interpType);

						for (int j = 0; j < outAccessor->count; ++j)
						{
							vec3 vec;
							AnimFrameVec3 frame;
							cgltf_accessor_read_float(outAccessor, j, &vec[0], 3);
							frame.value = vec;
							frame.time = time[j];

							scaleTrack.AddFrame(frame);
						}
					}
				}
				break;

				case cgltf_animation_path_type_weights:
					break;

				default:
					break;
				}

			}

			std::cout << anim.name;
			return clip;
		}
	}

	GLTFAnimLoader::~GLTFAnimLoader()
	{
		UnloadFile();
	}

	void GLTFAnimLoader::LoadFile(const std::string& path)
	{
		UnloadFile();
		m_Data = LoadGLTFFile(path.c_str());
	}

	void GLTFAnimLoader::UnloadFile()
	{
		if (m_Data)
		{
			cgltf_free(m_Data);
			m_Data = nullptr;
		}
	}

	std::vector<AnimPoseClip*> GLTFAnimLoader::LoadAnimClips() const
	{
		std::vector<AnimPoseClip*> result;

		for (int i = 0; i < m_Data->animations_count; ++i)
		{
			const cgltf_animation& anim = m_Data->animations[i];
			result.push_back(gltfloader::LoadClip(anim));
		}

		return result;
	}

	AnimPose* GLTFAnimLoader::LoadPose() const
	{
		AnimPose* result = new AnimPose;

		const cgltf_node* nodes = m_Data->nodes;
		auto nodes_count = m_Data->nodes_count;

		std::cout << "Loading Animation Poses" << std::endl;

		for (int j = 0; j < nodes_count; ++j)
		{
			const cgltf_node& cgltfJoint = nodes[j];
			std::cout << "joint name: " << cgltfJoint.name << " addr: " << &cgltfJoint << std::endl;

			Joint joint;
			joint.m_Id = j;
			joint.m_Name = cgltfJoint.name;

			if (cgltfJoint.has_translation)
			{
				joint.position = vec3(cgltfJoint.translation);
			}

			if (cgltfJoint.has_rotation)
			{
				joint.rotation = quat(cgltfJoint.rotation);
			}

			if (cgltfJoint.has_scale)
			{
				joint.scale = vec3(cgltfJoint.scale);
			}

			result->AddJoint(joint);
		}

		for (int j = 0; j < nodes_count; ++j)
		{
			const cgltf_node& cgltfJoint = nodes[j];
			const cgltf_node* parent = cgltfJoint.parent;
			if (parent != nullptr)
			{
				int idx = result->GetIndex(cgltfJoint.name);
				int parentIdx = result->GetIndex(parent->name);
				if (idx != Joint::INVALID_ID && parentIdx != Joint::INVALID_ID)
				{
					Joint& parentJoint = result->GetJoint(parentIdx);
					Joint& joint = result->GetJoint(idx);

					joint.m_ParentId = parentIdx;
					parentJoint.m_ChildrenId.push_back(idx);
				}
			}

			if (cgltf_skin* skin = cgltfJoint.skin)
			{
				for (int k = 0; k < skin->joints_count; ++k)
				{
					cgltf_node* cgltfSkinJoint = skin->joints[k];
					int idx = result->GetIndex(cgltfSkinJoint->name);
					if (idx != Joint::INVALID_ID)
					{
						Joint& joint = result->GetJoint(idx);
						const cgltf_accessor* accessor = skin->inverse_bind_matrices;
						float mat[16];

						cgltf_accessor_read_float(accessor, k, mat, 16);

						joint.m_InverseBindMatrices = mat4(mat);
					}
				}
			}
		}

		return result;
	}
}