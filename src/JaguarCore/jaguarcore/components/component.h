#pragma once

namespace jgr
{
	class GameObject;

	class Component
	{
	public:
		JAGUAR_DLL virtual void Startup();
		JAGUAR_DLL virtual void Update();
		JAGUAR_DLL virtual void Shutdown();

		GameObject* GetGameObject() const { return m_GameObject; }
		void SetGameObject(GameObject* gameObject) { m_GameObject = gameObject; }

	private:
		GameObject* m_GameObject = nullptr;
	};
}
