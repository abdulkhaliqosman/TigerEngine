#pragma once

namespace jgr
{
	class iEngine;

	class iScene : public iEngineSystem
	{
	public:
		inline iScene(iEngine& engine) :iEngineSystem(engine) {}
		virtual ~iScene() {}
	};
}
