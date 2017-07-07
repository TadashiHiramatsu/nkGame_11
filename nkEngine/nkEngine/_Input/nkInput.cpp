/**
 * DirectInput�N���X�̎���.
 */
#include"nkstdafx.h"
#include"nkInput.h"

namespace nkEngine
{
		
	/**
	 * �}�E�X�̏�����.
	 */
	void InputSingleton::InitMouse()
	{
		DIOBJECTDATAFORMAT ObjectFormats[] =
		{
			{ &GUID_XAxis, FIELD_OFFSET(MouseStateS, PosX_),	//!< �}�E�XX��.
			DIDFT_RELAXIS | DIDFT_ANYINSTANCE, 0 },
			{ &GUID_YAxis, FIELD_OFFSET(MouseStateS, PosY_),    //!< �}�E�XY��.
			DIDFT_RELAXIS | DIDFT_ANYINSTANCE, 0 },
			{ &GUID_ZAxis, FIELD_OFFSET(MouseStateS, Wheel_),    //!< �}�E�X�z�C�[��.
			DIDFT_RELAXIS | DIDFT_ANYINSTANCE, 0 },
			{ &GUID_Button, FIELD_OFFSET(MouseStateS, Button_[0]),	//!< ���N���b�N.
			DIDFT_BUTTON | DIDFT_ANYINSTANCE, 0 },
			{ &GUID_Button, FIELD_OFFSET(MouseStateS, Button_[1]),  //!< �E�N���b�N.
			DIDFT_BUTTON | DIDFT_ANYINSTANCE, 0 },
			{ &GUID_Button, FIELD_OFFSET(MouseStateS, Button_[2]),  //�z�C�[����������.
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
	 * �L�[�{�[�h�̏�����.
	 */
	void InputSingleton::InitKeyboard()
	{
		DInput_->CreateDevice(GUID_SysKeyboard,&DInputKeyboard_, nullptr);

		DInputKeyboard_->SetDataFormat(&c_dfDIKeyboard);

		DInputKeyboard_->SetCooperativeLevel(Engine().GetHWND(),DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);

		isKeyboard_ = true;
	}

	/**
	* ������.
	*
	* @param	hWnd		�E�B���h�E�Y�n���h��.
	* @param	isKeyboard	�L�[�{�[�h���g�p���邩.
	* @param	isMouse		�}�E�X���g�p���邩.
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
			//�}�E�X�̏�����
			InitMouse();
		}

		if (isKeyboard)
		{
			//�L�[�{�[�h�̏�����
			InitKeyboard();
		}

		return S_OK;
	}

	/**
	 * �X�V.
	 */
	void InputSingleton::Update()
	{
		HRESULT hr;

		if (isMouse_)
		{
			//�}�E�X�̃|�W�V�������擾
			GetCursorPos(&MousePos_);
			//�N���C�A���g�T�C�Y�ɕύX
			ScreenToClient(Engine().GetHWND(), &MousePos_);

			//1�t���[���O�̌��ʂ��R�s�[
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
			//1�t���[���O�̌��ʂ��R�s�[
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
	 * ���.
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