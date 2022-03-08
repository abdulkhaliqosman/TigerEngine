#pragma once

namespace jgr
{
	class GameObject;

	class Component
	{
	public:
		virtual void Startup();
		virtual void Update();
		virtual void Shutdown();

		GameObject* GetGameObject() const { return m_GameObject; }
		void SetGameObject(GameObject* gameObject) { m_GameObject = gameObject; }

	private:
		GameObject* m_GameObject = nullptr;
	};
}
