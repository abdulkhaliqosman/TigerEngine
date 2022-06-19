#include <tigerengine/tigerpch.h>
#include <tigerengine/app/windows/wininput.h>


constexpr int HID_USAGE_PAGE_GENERIC = 0x01;
constexpr int HID_USAGE_GENERIC_MOUSE = 0x02;
constexpr int HID_USAGE_GENERIC_KEYBOARD = 0x06;


namespace tgr
{
    void WinInput::Startup()
    {

    }

    void WinInput::Update()
    {

    }

    void WinInput::Shutdown()
    {

    }

    void WinInput::RegisterRawInputDevices(HWND hWnd)
    {
        RAWINPUTDEVICE Rid[2];

        Rid[0].usUsagePage = HID_USAGE_PAGE_GENERIC; // HID_USAGE_PAGE_GENERIC
        Rid[0].usUsage = HID_USAGE_GENERIC_MOUSE;    // HID_USAGE_GENERIC_MOUSE
        Rid[0].dwFlags = RIDEV_INPUTSINK;            // adds mouse and also ignores legacy mouse messages
        Rid[0].hwndTarget = hWnd;

        Rid[1].usUsagePage = HID_USAGE_PAGE_GENERIC; // HID_USAGE_PAGE_GENERIC
        Rid[1].usUsage = HID_USAGE_GENERIC_KEYBOARD; // HID_USAGE_GENERIC_KEYBOARD
        Rid[1].dwFlags = RIDEV_INPUTSINK;            // adds keyboard and also ignores legacy keyboard messages
        Rid[1].hwndTarget = hWnd;

        if (::RegisterRawInputDevices(Rid, 2, sizeof(Rid[0])) == FALSE)
        {
            //registration failed. Call GetLastError for the cause of the error
        }
    }

    void WinInput::ProcessInput(LPARAM lParam)
    {
        UINT dwSize;

        GetRawInputData((HRAWINPUT)lParam, RID_INPUT, NULL, &dwSize, sizeof(RAWINPUTHEADER));
        LPBYTE lpb = new BYTE[dwSize];
        if (dwSize == 0)
        {
            return;
        }

        RAWINPUT rawInput;
        dwSize = sizeof(RAWINPUT);

        if (GetRawInputData((HRAWINPUT)lParam, RID_INPUT, &rawInput, &dwSize, sizeof(RAWINPUTHEADER)) != dwSize)
            OutputDebugString(TEXT("GetRawInputData does not return correct size !\n"));

        if (rawInput.header.dwType == RIM_TYPEKEYBOARD)
        {
            if ((rawInput.data.keyboard.Flags & 0x1) == RI_KEY_MAKE) // TODO make this work legitly
            {
                m_Keys[rawInput.data.keyboard.VKey] = true;
            }
            else if ((rawInput.data.keyboard.Flags & 0x1) == RI_KEY_BREAK)
            {
                m_Keys[rawInput.data.keyboard.VKey] = false;
            }
        }
        else if (rawInput.header.dwType == RIM_TYPEMOUSE)
        {

        }
    }
}