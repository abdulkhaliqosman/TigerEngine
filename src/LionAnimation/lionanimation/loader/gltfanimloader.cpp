#include <lionanimation/lionpch.h>
#include <lionanimation/loader/gltfanimloader.h>

#include "lionanimation/animation/animclip.h"
#include "lionanimation/animation/animpose.h"
#include "jaguarcore/filetypes/gltf/gltfloader.h"
#include "cgltf/cgltf.h"
#include <iostream>
#include <cassert>

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

		AnimClip* LoadClip(const cgltf_animation& anim)
		{
			AnimClip* clip = jgr::New<AnimClip>();

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

				if (idx == Joint::INVALID_ID)
				{
					assert(false);
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

		AnimPose* LoadPose(const cgltf_skin& skin, cgltf_data* data)
		{
			AnimPose* result = jgr::New<AnimPose>();
			const cgltf_node* nodes = data->nodes;
			auto nodes_count = data->nodes_count;

			for (int i = 0; i < skin.joints_count; ++i)
			{
				const cgltf_node* cgltfJoint = skin.joints[i];
				Joint joint;
				joint.m_Id = i;
				joint.m_Name = cgltfJoint->name;

				const cgltf_accessor* accessor = skin.inverse_bind_matrices;
				float mat[16];

				cgltf_accessor_read_float(accessor, i, mat, 16);

				joint.m_InverseBindMatrices = mat4(mat);

				if (cgltfJoint->has_translation)
				{
					joint.position = vec3(cgltfJoint->translation);
				}

				if (cgltfJoint->has_rotation)
				{
					joint.rotation = quat(cgltfJoint->rotation);
				}

				if (cgltfJoint->has_scale)
				{
					joint.scale = vec3(cgltfJoint->scale);
				}

				result->AddJoint(joint);
			}

			for (int j = 0; j < nodes_count; ++j)
			{
				const cgltf_node& cgltfJoint = nodes[j];
				int idx = result->GetIndex(cgltfJoint.name);

				if (idx == Joint::INVALID_ID)
				{
					Joint joint;
					joint.m_Id = result->Size();
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
			}

			for (int j = 0; j < skin.joints_count; ++j)
			{
				const cgltf_node* cgltfJoint = skin.joints[j];
				const cgltf_node* parent = cgltfJoint->parent;
				if (parent != nullptr)
				{
					int idx = result->GetIndex(cgltfJoint->name);
					int parentIdx = result->GetIndex(parent->name);
					if (idx != Joint::INVALID_ID && parentIdx != Joint::INVALID_ID)
					{
						Joint& parentJoint = result->GetJoint(parentIdx);
						Joint& joint = result->GetJoint(idx);

						joint.m_ParentId = parentIdx;
						parentJoint.m_ChildrenId.push_back(idx);
					}
				}
			}

			return result;
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
		m_Path = path;
	}

	void GLTFAnimLoader::UnloadFile()
	{
		if (m_Data)
		{
			cgltf_free(m_Data);
			m_Data = nullptr;
		}
	}

	std::vector<AnimClip*> GLTFAnimLoader::LoadAnimClips() const
	{
		std::vector<AnimClip*> result;

		for (int i = 0; i < m_Data->animations_count; ++i)
		{
			const cgltf_animation& anim = m_Data->animations[i];
			auto* clip = gltfloader::LoadClip(anim);
			clip->SetPath(m_Path);
			result.push_back(clip);
		}

		return result;
	}

	std::vector<AnimPose*> GLTFAnimLoader::LoadPoses() const
	{
		std::vector<AnimPose*> result;

		std::cout << "Loading Animation Poses" << std::endl;

		for (int i = 0; i < m_Data->skins_count; ++i)
		{
			const cgltf_skin& skin = m_Data->skins[i];
			auto* pose = gltfloader::LoadPose(skin, m_Data);
			pose->SetPath(m_Path);
			result.push_back(pose);
		}

		return result;
	}

	
}