/**
* ���f���Ǘ��N���X�̒�`.
*/
#pragma once

namespace nkEngine
{

	/**
	* ���f���Ǘ��N���X.
	*/
	class ModelManager : Noncopyable
	{
	public:

		/**
		* �R���X�g���N�^.
		*/
		ModelManager()
		{
		}

		/**
		* �f�X�g���N�^.
		*/
		~ModelManager()
		{
		}

		/**
		* ������.
		*/
		void Init();

		/**
		* ���.
		*/
		void Release();

		/**
		* FBXSDK�̃������Ǘ��N���X���擾.
		*/
		FbxManager* GetFBXManager()
		{
			return FBXManager_;
		}

	private:

		/** FBXSDK�̃������Ǘ��N���X. */
		FbxManager* FBXManager_ = nullptr;

	};


}