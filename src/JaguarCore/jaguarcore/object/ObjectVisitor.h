#pragma once

namespace jgr
{
	class ObjectVisitor
	{
	public:
		virtual void Visit(int&) = 0;
		virtual void Visit(float&) = 0;
	};
}