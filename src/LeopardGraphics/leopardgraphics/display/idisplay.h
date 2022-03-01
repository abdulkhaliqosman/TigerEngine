#pragma once

namespace lpd
{
	struct Rect
	{
		int left;
		int right;
		int top;
		int bottom;
	};

	class iDisplay
	{
	public:
		virtual Rect GetClientRect() const = 0;
		virtual bool IsVsyncEnabled() const = 0;

		virtual void SwapBuffers() = 0;
	};
}
