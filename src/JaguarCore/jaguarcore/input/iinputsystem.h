#pragma once

namespace jgr
{
	class iInputSystem : public iAppSystem
	{
	public:
		inline iInputSystem(iApp& app) : iAppSystem(app) {}
	};
}
