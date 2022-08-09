#pragma once

namespace jgr
{
	class iSystem
	{
	public:
		
		inline virtual ~iSystem() {}

		virtual void Setup() = 0;
		virtual void Teardown() = 0;

		virtual void Update() = 0;

	private:
		inline iSystem() {}

		friend class iAppSystem;
		friend class iEngineSystem;
		friend class iSceneSystem;
	};


}
