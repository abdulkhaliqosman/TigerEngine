#pragma once

namespace tgr
{
	class CameraMovementComponent : public Component
	{
		void Startup() override;
		void Update() override;
		void Shutdown() override;

	public:
		void SetRotation(const jgr::EulerAngles& rotation) { m_Rotation = rotation; }
	private:
		jgr::EulerAngles m_Rotation;
	};
}