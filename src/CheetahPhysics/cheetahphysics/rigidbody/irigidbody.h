#pragma once

#include <jaguarcore\engine\iengine.h>

namespace cht
{
	class iRigidBody
	{
	public:
		virtual float GetMass() const = 0;
		virtual void SetMass(float value) = 0;
	};
}