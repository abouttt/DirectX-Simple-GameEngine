#pragma once

enum class eKeyCode;

class InputManager
{
public:
	struct KeyState
	{
		bool bPressed = false;
		bool bPressing = false;
		bool bUp = false;
	};

public:
	friend class GameEngine;

public:
	InputManager();
	~InputManager();

public:
	// 키보드.
	bool GetKey(const eKeyCode keyCode) const;
	bool GetKeyDown(const eKeyCode keyCode) const;
	bool GetKeyUp(const eKeyCode keyCode) const;

	// 마우스.
	bool GetMouseButton(const int button) const;
	bool GetMouseButtonDown(const int button) const;
	bool GetMouseButtonUp(const int button) const;
	LONG GetAxisMouseX() const;
	LONG GetAxisMouseY() const;
	LONG GetAxisMouseZ() const;
	void GetMousePosition(int* const outMouseX, int* const outMouseY) const;

private:
	void update();
	void keyboardUpdate();
	void mouseUpdate();
	bool readKeyboard();
	bool readMouse();

	bool init(const HINSTANCE hInstance, const HWND hWnd);
	void clear();
	void release();

private:
	bool mbInit;

	IDirectInput8* mInput;
	IDirectInputDevice8* mKeyboard;
	IDirectInputDevice8* mMouse;

	std::array<unsigned char, 256> mKeyboardKeys;
	std::array<KeyState, 256> mKeyboardState;

	DIMOUSESTATE mMouseButtons;
	std::array<KeyState, 4> mMouseState;
};
