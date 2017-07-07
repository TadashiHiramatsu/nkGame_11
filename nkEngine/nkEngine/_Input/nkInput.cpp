/**
 * DirectInputクラスの実装.
 */
#include"nkstdafx.h"
#include"nkInput.h"

namespace nkEngine
{
		
	/**
	 * マウスの初期化.
	 */
	void InputSingleton::InitMouse()
	{
		DIOBJECTDATAFORMAT ObjectFormats[] =
		{
			{ &GUID_XAxis, FIELD_OFFSET(MouseStateS, PosX_),	//!< マウスX軸.
			DIDFT_RELAXIS | DIDFT_ANYINSTANCE, 0 },
			{ &GUID_YAxis, FIELD_OFFSET(MouseStateS, PosY_),    //!< マウスY軸.
			DIDFT_RELAXIS | DIDFT_ANYINSTANCE, 0 },
			{ &GUID_ZAxis, FIELD_OFFSET(MouseStateS, Wheel_),    //!< マウスホイール.
			DIDFT_RELAXIS | DIDFT_ANYINSTANCE, 0 },
			{ &GUID_Button, FIELD_OFFSET(MouseStateS, Button_[0]),	//!< 左クリック.
			DIDFT_BUTTON | DIDFT_ANYINSTANCE, 0 },
			{ &GUID_Button, FIELD_OFFSET(MouseStateS, Button_[1]),  //!< 右クリック.
			DIDFT_BUTTON | DIDFT_ANYINSTANCE, 0 },
			{ &GUID_Button, FIELD_OFFSET(MouseStateS, Button_[2]),  //ホイール押し込み.
			DIDFT_BUTTON | DIDFT_ANYINSTANCE, 0 }
		};

		DIDATAFORMAT dfMouse =
		{
			sizeof(DIDATAFORMAT),
			sizeof(DIOBJECTDATAFORMAT),
			DIDF_ABSAXIS,
			sizeof(MouseStateS),
			sizeof(ObjectFormats) / sizeof(DIOBJECTDATAFORMAT),
			ObjectFormats
		};

		DInput_->CreateDevice(GUID_SysMouse, &DInputMouse_, nullptr);

		DInputMouse_->SetDataFormat(&dfMouse);

		DInputMouse_->SetCooperativeLevel(Engine().GetHWND(), DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
	
		DInputMouse_->Acquire();

		isMouse_ = true;

	}

	/**
	 * キーボードの初期化.
	 */
	void InputSingleton::InitKeyboard()
	{
		DInput_->CreateDevice(GUID_SysKeyboard,&DInputKeyboard_, nullptr);

		DInputKeyboard_->SetDataFormat(&c_dfDIKeyboard);

		DInputKeyboard_->SetCooperativeLevel(Engine().GetHWND(),DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);

		isKeyboard_ = true;
	}

	/**
	* 初期化.
	*
	* @param	hWnd		ウィンドウズハンドル.
	* @param	isKeyboard	キーボードを使用するか.
	* @param	isMouse		マウスを使用するか.
	*
	* @return	A hResult.
	*/
	HRESULT InputSingleton::Init(bool isKeyboard, bool isMouse)
	{
		HRESULT hr;

		hr = DirectInput8Create(
			GetModuleHandle(nullptr),
			DIRECTINPUT_VERSION,IID_IDirectInput8, 
			(VOID**)&DInput_, 
			nullptr);

		if (FAILED(hr))
		{
			return hr;
		}

		if (isMouse)
		{
			//マウスの初期化
			InitMouse();
		}

		if (isKeyboard)
		{
			//キーボードの初期化
			InitKeyboard();
		}

		return S_OK;
	}

	/**
	 * 更新.
	 */
	void InputSingleton::Update()
	{
		HRESULT hr;

		if (isMouse_)
		{
			//マウスのポジションを取得
			GetCursorPos(&MousePos_);
			//クライアントサイズに変更
			ScreenToClient(Engine().GetHWND(), &MousePos_);

			//1フレーム前の結果をコピー
			MouseStateBef_ = MouseState_;
			
			hr = DInputMouse_->GetDeviceState(sizeof(MouseStateS), &MouseState_);
			if (FAILED(hr))
			{
				DInputMouse_->Acquire();
				DInputMouse_->GetDeviceState(sizeof(MouseStateS), &MouseState_);
			}
		}

		if (isKeyboard_)
		{
			//1フレーム前の結果をコピー
			memcpy(KeyboardBef_, Keyboard_, 256);

			hr = DInputKeyboard_->GetDeviceState(sizeof(Keyboard_), &Keyboard_);
			if (FAILED(hr))
			{
				DInputKeyboard_->Acquire();
				DInputKeyboard_->GetDeviceState(sizeof(Keyboard_), &Keyboard_);
			}
		}
	}

	/**
	 * 解放.
	 */
	void InputSingleton::Release()
	{
		if (DInputMouse_)
		{
			DInputMouse_->Unacquire();
		}
		if (DInputKeyboard_)
		{
			DInputKeyboard_->Unacquire();
		}

		if (DInputMouse_ != nullptr)
		{
			DInputMouse_->Release();
			DInputMouse_ = nullptr;
		}
		if (DInputKeyboard_ != nullptr)
		{
			DInputKeyboard_->Release();
			DInputKeyboard_ = nullptr;
		}
		if (DInput_ != nullptr)
		{
			DInput_->Release();
			DInput_ = nullptr;
		}
	}

}