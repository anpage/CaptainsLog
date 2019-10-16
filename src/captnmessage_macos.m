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
#include <AppKit/AppKit.h>
#include <Availability.h>

int captain_message(int level, int buttons, const char *message)
{
	@autoreleasepool {

	NSWindow *key_window = [[NSApplication sharedApplication] keyWindow];

	NSAlert *alert = [[NSAlert alloc] init];

	switch (level) {
		default:
#ifdef __MAC_10_12
		case CAPTMSG_INFO:
            [alert setAlertStyle:NSAlertStyleInformational];
            break;
		case CAPTMSG_WARNING:
            [alert setAlertStyle:NSAlertStyleWarning];
            break;
		case CAPTMSG_ERROR:
            [alert setAlertStyle:NSAlertStyleCritical];
            break;
#else
		case CAPTMSG_INFO:
            [alert setAlertStyle:NSInformationalAlertStyle];
            break;
		case CAPTMSG_WARNING:
            [alert setAlertStyle:NSWarningAlertStyle];
            break;
		case CAPTMSG_ERROR:
            [alert setAlertStyle:NSCriticalAlertStyle];
            break;
#endif
	}

	switch (buttons) {
		default:
		case CAPTMSG_OK:
			[alert addButtonWithTitle:@"OK"];
			break;
		case CAPTMSG_OK_CANCEL:
			[alert addButtonWithTitle:@"OK"];
			[alert addButtonWithTitle:@"Cancel"];
			break;
		case CAPTMSG_YES_NO:
			[alert addButtonWithTitle:@"Yes"];
			[alert addButtonWithTitle:@"No"];
			break;
        case CAPTMSG_ABRT_RET_IGN:
			[alert addButtonWithTitle:@"Abort"];
			[alert addButtonWithTitle:@"Retry"];
			[alert addButtonWithTitle:@"Ignore"];
			break;
	}

	NSString *msg_string = [NSString stringWithUTF8String:message];
	[alert setMessageText:msg_string];
	NSInteger button = [alert runModal];
	[key_window makeKeyAndOrderFront:nil];

    switch(button) {
        case NSAlertFirstButtonReturn:
            return CAPTMSG_YES;
        case NSAlertThirdButtonReturn:
            return CAPTMSG_IGN;
        default:
            return CAPTMSG_NO;
    }

	} /* @autoreleasepool */
}