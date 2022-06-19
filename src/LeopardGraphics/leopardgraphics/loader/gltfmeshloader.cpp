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

	MeshGroup* GLTFMeshLoader::LoadMesh(const std::string& path) const
	{
		cgltf_data* gltf = LoadGLTFFile(path.c_str());
		MeshGroup* meshGroup = jgr::New<MeshGroup>();

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
					Mesh* mesh = jgr::New<Mesh>();
					meshGroup->m_Meshes.push_back(mesh);

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

									mesh->m_LocalPosition.push_back(vec);
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
