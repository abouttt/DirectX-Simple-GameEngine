#pragma once

enum class eRenderingMode
{
	Opaque,
	Transparency,
	Cutout,
};

enum class eLightType
{
	Point = 1,
	Spot = 2,
	Directional = 3,
};

enum class eKeyCode
{
	Esc = 0x01,
	Alpha1 = 0x02,
	Alpha2 = 0x03,
	Alpha3 = 0x04,
	Alpha4 = 0x05,
	Alpha5 = 0x06,
	Alpha6 = 0x07,
	Alpha7 = 0x08,
	Alpha8 = 0x09,
	Alpha9 = 0x0A,
	Alpha0 = 0x0B,
	Minus = 0x0C,
	Equals = 0x0D,
	Backspace = 0x0E,
	Tab = 0x0F,
	Q = 0x10,
	W = 0x11,
	E = 0x12,
	R = 0x13,
	T = 0x14,
	Y = 0x15,
	U = 0x16,
	I = 0x17,
	O = 0x18,
	P = 0x19,
	Leftbracket = 0x1A,
	Rightbracket = 0x1B,
	Return = 0x1C,
	LeftControl = 0x1D,
	A = 0x1E,
	S = 0x1F,
	D = 0x20,
	F = 0x21,
	G = 0x22,
	H = 0x23,
	J = 0x24,
	K = 0x25,
	L = 0x26,
	Semicolon = 0x27,
	Apostrophe = 0x28,
	Grave = 0x29,
	LeftShift = 0x2A,
	BackSlash = 0x2B,
	Z = 0x2C,
	X = 0x2D,
	C = 0x2E,
	V = 0x2F,
	B = 0x30,
	N = 0x31,
	M = 0x32,
	Comma = 0x33,
	Period = 0x34,
	Slash = 0x35,
	RightShift = 0x36,
	Multiply = 0x37,
	LeftAlt = 0x38,
	Space = 0x39,
	Capital = 0x3A,
	F1 = 0x3B,
	F2 = 0x3C,
	F3 = 0x3D,
	F4 = 0x3E,
	F5 = 0x3F,
	F6 = 0x40,
	F7 = 0x41,
	F8 = 0x42,
	F9 = 0x43,
	F10 = 0x44,
	Numlock = 0x45,
	ScrollLock = 0x46,
	Keypad7 = 0x47,
	Keypad8 = 0x48,
	Keypad9 = 0x49,
	Subtract = 0x4A,
	Keypad4 = 0x4B,
	Keypad5 = 0x4C,
	Keypad6 = 0x4D,
	Add = 0x4E,
	Keypad1 = 0x4F,
	Keypad2 = 0x50,
	Keypad3 = 0x51,
	Keypad0 = 0x52,
	Decimal = 0x53,
	OEM_102 = 0x56,			// <> or \| on RT 102-key keyboard (Non-U.S.) 
	F11 = 0x57,				//
	F12 = 0x58,				//
	F13 = 0x64,				// (NEC PC98) 
	F14 = 0x65,				// (NEC PC98) 
	F15 = 0x66,				// (NEC PC98) 
	KANA = 0x70,			// (Japanese keyboard)            
	ABNT_C1 = 0x73,			// /? on Brazilian keyboard 
	CONVERT = 0x79,			// (Japanese keyboard)            
	NOCONVERT = 0x7B,		// (Japanese keyboard)            
	YEN = 0x7D,				// (Japanese keyboard)            
	ABNT_C2 = 0x7E,			// Numpad . on Brazilian keyboard 
	KeypadEquals = 0x8D,	// = on numeric keypad (NEC PC98) 
	PREVTRACK = 0x90,		// Previous Track (DIK_CIRCUMFLEX on Japanese keyboard) 
	AT = 0x91,				// (NEC PC98) 
	Colon = 0x92,			// (NEC PC98) 
	Underline = 0x93,		// (NEC PC98) 
	KANJI = 0x94,			// (Japanese keyboard) 
	Stop = 0x95,			// (NEC PC98) 
	AX = 0x96,				// (Japan AX) 
	Unlabeled = 0x97,		// (J3100) 
	NextTrack = 0x99,
	KeypadEnter = 0x9C,
	RightControl = 0x9D,
	Mute = 0xA0,
	Calculator = 0xA1,
	PlayPause = 0xA2,
	MediaStop = 0xA4,
	VolumeDown = 0xAE,
	VolumeUp = 0xB0,
	Webhome = 0xB2,
	KeypadComma = 0xB3,
	Divide = 0xB5,
	Sysrq = 0xB7,
	RightAlt = 0xB8,
	Pause = 0xC5,
	Home = 0xC7,
	Up = 0xC8,
	PgUp = 0xC9,
	LeftArrow = 0xCB,
	RightArrow = 0xCD,
	End = 0xCF,
	DownArrow = 0xD0,
	PgDn = 0xD1,
	Insert = 0xD2,
	Delete = 0xD3,
	LeftWindows = 0xDB,
	RightWindows = 0xDC,
	AppMenu = 0xDD,
	SystemPower = 0xDE,
	SystemSleep = 0xDF,
	SystemWake = 0xE3,
	WebSearch = 0xE5,
	WebFavorites = 0xE6,
	WebRefresh = 0xE7,
	WebStop = 0xE8,
	WebForward = 0xE9,
	WebBack = 0xEA,
	MyComputer = 0xEB,
	Mail = 0xEC,
	MediaSelect = 0xED,
};
