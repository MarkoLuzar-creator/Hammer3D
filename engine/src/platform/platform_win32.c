#include "platform.h"

#ifdef PLATFORM_WINDOWS

#include <windows.h>
#include <windowsx.h>

#include <stdlib.h>

#include "core/logger.h"

#include "core/input.h"

#include <stdio.h>

typedef struct internal_state
{
    HINSTANCE h_instance;
    HWND hwnd;
} internal_state;

static f64 clock_frequency;
static LARGE_INTEGER start_time;

LRESULT CALLBACK win32_process_message(HWND hwnd, u32 msg, WPARAM w_param, LPARAM l_param)
{
    switch (msg)
    {
        case WM_ERASEBKGND:
        {
            return 1;
        }
        case WM_CLOSE:
        {
            MOJINFO("close");
            return 0;
        }
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }
        case WM_SIZE: 
        {
            RECT r;
            GetClientRect(hwnd, &r);
            //u32 width = r.right - r.left;
            //u32 height = r.bottom - r.top;
        } break;
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
        case WM_KEYUP:
        case WM_SYSKEYUP: 
        {
            b8 pressed = (msg  == WM_KEYDOWN || msg == WM_SYSKEYDOWN);
            keys key = (u16)w_param;
            input_process_key(key, pressed);
        } break;
        case WM_MOUSEMOVE:
        {
            i32 x_position = GET_X_LPARAM(l_param);
            i32 y_position = GET_Y_LPARAM(l_param);
            input_process_button_mouse_move(x_position, y_position);
        } break;
        case WM_MOUSEWHEEL:
        {
            i32 z_delta = GET_WHEEL_DELTA_WPARAM(w_param);
            if (!z_delta)
            {
                z_delta = (z_delta < 0) ? -1 : 1;
                input_process_mouse_wheel(z_delta);
            } 
        } break;
        case WM_LBUTTONDOWN:
        case WM_MBUTTONDOWN:
        case WM_RBUTTONDOWN:
        case WM_LBUTTONUP:
        case WM_MBUTTONUP:
        case WM_RBUTTONUP:
        {
            b8 pressed = msg == WM_LBUTTONDOWN || msg == WM_RBUTTONDOWN || msg == WM_MBUTTONDOWN;
            buttons mouse_button = BUTTON_MAX_BUTTONS;
            switch(msg)
            {
                case WM_LBUTTONDOWN:
                case WM_LBUTTONUP:
                    mouse_button = BUTTON_LEFT;
                break;
                case WM_MBUTTONDOWN:
                case WM_MBUTTONUP:
                    mouse_button = BUTTON_MIDDLE;
                break;
                case WM_RBUTTONDOWN:
                case WM_RBUTTONUP:
                    mouse_button = BUTTON_RIGHT;
            }

            if (mouse_button != BUTTON_MAX_BUTTONS)
            {
                input_process_button(mouse_button, pressed);
            }
        } break;
    }

    return DefWindowProcA(hwnd, msg, w_param, l_param);
}

b8 platform_startup(platform_state* plat_state, const char* application_name, u16 x, u16 y, u16 width, u16 height)
{
    internal_state *i_state = malloc(sizeof(internal_state));
    plat_state->internal_state = i_state;

    i_state->h_instance = GetModuleHandleA(0);

    WNDCLASS wc;
    memset(&wc, 0, sizeof(wc));
    HICON icon = LoadIcon(i_state->h_instance, IDI_APPLICATION);
    wc.style = CS_DBLCLKS;
    wc.lpfnWndProc = win32_process_message;
    wc.cbClsExtra  = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = i_state->h_instance;
    wc.hIcon = icon;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = NULL;
    wc.lpszClassName = "moj_window_class";

    if(!RegisterClassA(&wc))
    {
        MessageBoxA(0, "Window registration failed!", "Error", MB_ICONEXCLAMATION | MB_OK);
        MOJFATAL("Window registration failed!");
        return FALSE;
    }

    u16 window_x = x;
    u16 window_y = y;
    u16 window_width = width;
    u16 window_height = height;

    u32 window_style = WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_THICKFRAME;
    u32 window_ex_style = WS_EX_APPWINDOW | WS_EX_ACCEPTFILES;

    RECT border_rect = {0, 0, 0, 0};
    AdjustWindowRectEx(&border_rect, window_style, 0, window_ex_style);
    window_width += border_rect.right - border_rect.left;
    window_height += border_rect.bottom - border_rect.top;

    HWND handle = CreateWindowExA(window_ex_style, "moj_window_class", application_name,
         window_style, window_x, window_y, window_width, window_height, 0, 0, i_state->h_instance, 0);

    if (!handle)
    {
        MessageBoxA(NULL, "Window creation failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        MOJFATAL("Window creation failed!");
        return FALSE;
    } 

    i_state->hwnd = handle;

    ShowWindow(i_state->hwnd, SW_SHOW);

    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);
    clock_frequency = 1.0 / (f64)frequency.QuadPart;
    QueryPerformanceCounter(&start_time);

    return TRUE;
}

void platform_shutdown(platform_state* plat_state)
{
    internal_state *i_state = plat_state->internal_state;
    if (i_state->hwnd)
    {
        DestroyWindow(i_state->hwnd);
        i_state->hwnd = 0;
    }
}

b8 platform_pump_messages(platform_state* plat_state)
{
    MSG message;
    while(PeekMessageA(&message, NULL, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }
    return TRUE;
}

void* platform_allocate(u64 size, b8 aligned)
{
    return malloc(size);
}

void platform_free(void* block, b8 aligned)
{
    free(block);
}

void* platform_zero_memory(void* block, u64 size)
{
    return memset(block, 0, size);
}

void* platform_copy_memory(void* dest, const void *source, u64 size)
{
    return memcpy(dest, source, size);
}

void* platform_set_memory(void* dest, i32 value, u64 size)
{
    return memset(dest, value, size);
}

void platform_console_write(const char* msg, u8 colour)
{
    HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    static u8 levels[6] = {64, 4, 6, 2, 1, 8};
    SetConsoleTextAttribute(console_handle, levels[colour]);

    OutputDebugStringA(msg);
    WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), msg, (DWORD)strlen(msg), 0, 0);
}

void platform_console_write_error(const char* msg, u8 colour)
{
    HANDLE console_handle = GetStdHandle(STD_ERROR_HANDLE);
    static u8 levels[6] = {64, 4, 6, 2, 1, 8};
    SetConsoleTextAttribute(console_handle, levels[colour]);

    OutputDebugStringA(msg);
    WriteConsoleA(GetStdHandle(STD_ERROR_HANDLE), msg, (DWORD)strlen(msg), 0, 0);
}

f64 platform_get_absolute_time()
{
    LARGE_INTEGER now_time;
    QueryPerformanceCounter(&now_time);
    return (f64)now_time.QuadPart * clock_frequency;
}

void platform_sleep(u64 ms)
{
    Sleep(ms);
}

#endif