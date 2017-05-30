/**
* �X�R�[�v�𔲂���Ǝ����ŉ������郊�\�[�X.
*/
#pragma once

namespace nkEngine
{

	/**
	* �X�R�[�v�𔲂���Ǝ����ŉ������郊�\�[�X�N���X.
	*/
	template<class T>
	class ScopedResource
	{
	public:
		
		/**
		* �f�X�g���N�^.
		*/
		~ScopedResource()
		{
			if (res) {
				res->Release();
			}
		}

	public:

		/** ���\�[�X. */
		T* res = nullptr;

	};

}