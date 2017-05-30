/**
* スコープを抜けると自動で解放されるリソース.
*/
#pragma once

namespace nkEngine
{

	/**
	* スコープを抜けると自動で解放されるリソースクラス.
	*/
	template<class T>
	class ScopedResource
	{
	public:
		
		/**
		* デストラクタ.
		*/
		~ScopedResource()
		{
			if (res) {
				res->Release();
			}
		}

	public:

		/** リソース. */
		T* res = nullptr;

	};

}