/**
 * @file
 *
 * @author OmniBlade
 *
 * @brief Cross platform message box invokation function.
 *
 * @copyright CaptainsLog is free software: you can redistribute it and/or
 *            modify it under the terms of the GNU General Public License
 *            as published by the Free Software Foundation, either version
 *            2 of the License, or (at your option) any later version.
 *            A full copy of the GNU General Public License can be found in
 *            LICENSE
 */
#include "captnmessage.h"
#include <malloc.h>
#include <windows.h>

static wchar_t *to_utf16(const char *str)
{
    if (str == NULL) {
        return NULL;
    }

    int len = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);

    if (len == 0) {
        return NULL;
    }

    wchar_t *ret = malloc(len * sizeof(wchar_t));
    MultiByteToWideChar(CP_UTF8, 0, str, -1, ret, len);

    return ret;
}

int captain_message(int level, int buttons, const char *message)
{
    UINT type = MB_APPLMODAL;
    switch (level) {
        default:
        case CAPTMSG_INFO:
            type |= MB_ICONINFORMATION;
            break;
        case CAPTMSG_WARNING:
            type |= MB_ICONWARNING;
            break;
        case CAPTMSG_ERROR:
            type |= MB_ICONERROR;
            break;
    }

    switch (buttons) {
        default:
        case CAPTMSG_OK:
            type |= MB_OK;
            break;
        case CAPTMSG_OK_CANCEL:
            type |= MB_OKCANCEL;
            break;
        case CAPTMSG_YES_NO:
            type |= MB_YESNO;
            break;
        case CAPTMSG_ABRT_RET_IGN:
            type |= MB_ABORTRETRYIGNORE;
            break;
    }

    wchar_t *utf16_msg = to_utf16(message);
    int result = MessageBoxW(GetActiveWindow(), utf16_msg, L"", type);
    free(utf16_msg);

    switch (result) {
        case IDOK:
        case IDYES:
        case IDRETRY:
            return CAPTMSG_YES;
        case IDIGNORE:
            return CAPTMSG_IGN;
        default:
            return CAPTMSG_NO;
    }
}
