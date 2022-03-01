#include <leopardgraphics/leopardpch.h>
#include "gltfmeshloader.h"

#include "jaguarcore/filetypes/gltf/gltfloader.h"
#include <iostream>
#include "leopardgraphics/shapes/mesh.h"
#include "cgltf/cgltf.h"


namespace lpd
{
#define ENUM_TO_STRING(enumname) case enumname: return #enumname;

	const char* GetPrimitiveTypeString(cgltf_primitive_type type)
	{
		switch (type)
		{
			ENUM_TO_STRING(cgltf_primitive_type_points);
			ENUM_TO_STRING(cgltf_primitive_type_lines);
			ENUM_TO_STRING(cgltf_primitive_type_line_loop);
			ENUM_TO_STRING(cgltf_primitive_type_line_strip);
			ENUM_TO_STRING(cgltf_primitive_type_triangles);
			ENUM_TO_STRING(cgltf_primitive_type_triangle_strip);
			ENUM_TO_STRING(cgltf_primitive_type_triangle_fan);
		}
		return "";
	}

	const char* GetAttributeTypeString(cgltf_attribute_type type)
	{
		switch (type)
		{
			ENUM_TO_STRING(cgltf_attribute_type_invalid);
			ENUM_TO_STRING(cgltf_attribute_type_position);
			ENUM_TO_STRING(cgltf_attribute_type_normal);
			ENUM_TO_STRING(cgltf_attribute_type_tangent);
			ENUM_TO_STRING(cgltf_attribute_type_texcoord);
			ENUM_TO_STRING(cgltf_attribute_type_color);
			ENUM_TO_STRING(cgltf_attribute_type_joints);
			ENUM_TO_STRING(cgltf_attribute_type_weights);
		}
		return "";
	}
#undef ENUM_TO_STRING

	std::vector<Mesh*> GLTFMeshLoader::LoadMesh(const std::string& path) const
	{
		cgltf_data* gltf = LoadGLTFFile(path.c_str());
		std::vector<Mesh*> meshGroup;

		auto* nodes = gltf->nodes;
		auto nodes_count = gltf->nodes_count;

		std::cout << "Loading Mesh: " << path << std::endl;
		for (int i = 0; i < nodes_count; ++i)
		{
			cgltf_node& node = nodes[i];
			cgltf_mesh* gltf_mesh = node.mesh;
			if (gltf_mesh)
			{
				std::cout << gltf_mesh->name << std::endl;

				cgltf_size primitives_count = gltf_mesh->primitives_count;
				std::cout << "primitives_count: " << primitives_count << std::endl;
				for (int j = 0; j < primitives_count; ++j)
				{
					Mesh* mesh = new Mesh;
					meshGroup.push_back(mesh);

					const cgltf_primitive& primitive = gltf_mesh->primitives[j];
					std::cout << GetPrimitiveTypeString(primitive.type) << std::endl;

					cgltf_accessor* indices = primitive.indices;
					cgltf_size indices_count = indices->count;
					std::cout << "indices_count: " << indices_count << std::endl;
					for (int idx = 0; idx < indices_count; ++idx)
					{
						mesh->m_Indices.push_back(cgltf_accessor_read_index(indices, idx));
					}

					cgltf_size attributes_count = primitive.attributes_count;
					std::cout << "attributes_count: " << attributes_count << std::endl;
					for (int k = 0; k < attributes_count; ++k)
					{
						const cgltf_attribute& attribute = primitive.attributes[k];
						std::cout << GetAttributeTypeString(attribute.type) << std::endl;

						const cgltf_accessor* accessor = attribute.data;

						if (attribute.type == cgltf_attribute_type_position)
						{
							if (accessor->type == cgltf_type_vec3)
							{
								for (int v = 0; v < accessor->count; v++)
								{
									vec3 vec;
									cgltf_accessor_read_float(accessor, v, &vec[0], 3);

									mesh->m_Position.push_back(vec);
								}
							}
						}
						else if (attribute.type == cgltf_attribute_type_normal)
						{
							if (accessor->type == cgltf_type_vec3)
							{
								for (int v = 0; v < accessor->count; v++)
								{
									vec3 vec;
									cgltf_accessor_read_float(accessor, v, &vec[0], 3);

									mesh->m_Normal.push_back(vec);
								}
							}
						}
						else if (attribute.type == cgltf_attribute_type_joints)
						{
							for (int i = 0; i < accessor->count; ++i)
							{
								unsigned int read[4];

								cgltf_accessor_read_uint(accessor, i, read, 4);

								mesh->m_Joints.push_back(ivec4{ (int)read[0], (int)read[1], (int)read[2], (int)read[3] });
							}
						}
						else if (attribute.type == cgltf_attribute_type_weights)
						{
							if (accessor->type == cgltf_type_vec4)
							{
								if (accessor->component_type == cgltf_component_type_r_32f)
								{
									for (int i = 0; i < accessor->count; ++i)
									{
										vec4 vec;
										cgltf_accessor_read_float(accessor, i, &vec[0], 4);
										mesh->m_Weights.push_back(vec);
									}
								}
							}

						}
					}
				}
			}
		}

		cgltf_accessor* accessors = gltf->accessors;
		auto accessor_count = gltf->accessors_count;

		cgltf_free(gltf);

		return meshGroup;
	}
}

//
//Pose* GLTFMeshLoader::LoadSkeleton(const std::string& path) const
//{
//	cgltf_data* gltf = LoadGLTFFile(path.c_str());
//
//	// assume 1 skin only
//
//	if (gltf->skins_count == 0)
//	{
//		return nullptr;
//	}
//
//	Pose* skeleton = new Pose;
//
//	const cgltf_skin& skin = gltf->skins[0];
//	for (int i = 0; i < skin.joints_count; ++i)
//	{
//		const cgltf_node* cgltfJoint = skin.joints[i];
//		Joint joint;
//		joint.m_Id = i;
//		joint.m_Name = cgltfJoint->name;
//
//		const cgltf_accessor* accessor = skin.inverse_bind_matrices;
//		float mat[16];
//
//		cgltf_accessor_read_float(accessor, i, mat, 16);
//
//		joint.m_InverseBindMatrices = mat4(mat);
//
//		if (cgltfJoint->has_translation)
//		{
//			auto translate = vec3(cgltfJoint->translation);
//			joint.localTransform.SetTranslate(translate);
//		}
//
//		if (cgltfJoint->has_rotation)
//		{
//			auto rotate = quat(cgltfJoint->rotation);
//			joint.localTransform.SetRotate(rotate);
//		}
//
//		if (cgltfJoint->has_scale)
//		{
//			auto scale = vec3(cgltfJoint->scale);
//			joint.localTransform.SetScale(scale);
//		}
//
//		skeleton->AddJoint(joint);
//	}
//
//	for (int j = 0; j < gltf->nodes_count; ++j)
//	{
//		const cgltf_node& cgltfJoint = gltf->nodes[j];
//		int idx = skeleton->GetIndex(cgltfJoint.name);
//
//		if (idx == Joint::INVALID_ID)
//		{
//			Joint joint;
//			joint.m_Id = skeleton->Size();
//			joint.m_Name = cgltfJoint.name;
//
//			if (cgltfJoint.has_translation)
//			{
//				auto translate = vec3(cgltfJoint.translation);
//				joint.localTransform.SetTranslate(translate);
//			}
//
//			if (cgltfJoint.has_rotation)
//			{
//				auto rotate = quat(cgltfJoint.rotation);
//				joint.localTransform.SetRotate(rotate);
//			}
//
//			if (cgltfJoint.has_scale)
//			{
//				auto scale = vec3(cgltfJoint.scale);
//				joint.localTransform.SetScale(scale);
//			}
//
//			skeleton->AddJoint(joint);
//		}
//
//		
//	}
//
//	for (int j = 0; j < skin.joints_count; ++j)
//	{
//		const cgltf_node* cgltfJoint = skin.joints[j];
//		const cgltf_node* parent = cgltfJoint->parent;
//		if (parent != nullptr)
//		{
//			int idx = skeleton->GetIndex(cgltfJoint->name);
//			int parentIdx = skeleton->GetIndex(parent->name);
//			if (idx != Joint::INVALID_ID && parentIdx != Joint::INVALID_ID)
//			{
//				Joint& parentJoint = skeleton->GetJoint(parentIdx);
//				Joint& joint = skeleton->GetJoint(idx);
//
//				joint.m_ParentId = parentIdx;
//				parentJoint.m_ChildrenId.push_back(idx);
//			}
//		}
//	}
//
//	return skeleton;
//}