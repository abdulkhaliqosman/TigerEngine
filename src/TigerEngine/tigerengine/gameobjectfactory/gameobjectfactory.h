#pragma once



namespace jgr
{
	class GameObject;
}

namespace tgr
{
	class GameObjectFactory
	{
	public:
		jgr::GameObject* CreateGameObject();

	private:
	};
}