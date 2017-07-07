/**
* コンポーネントクラスの定義. 
*/
#pragma once

#include"..\nkObject.h"

namespace nkEngine
{
	
	/**
	* コンポーネントクラス.
	*/
	class IComponent : public IObject
	{
	public:

		/**
		* コンストラクタ.
		*/
		IComponent()
		{
		}

		/**
		* デストラクタ.
		*/
		virtual ~IComponent()
		{
		}

	protected:

		/** トランスフォームのポインタ. */
		Transform* Transform_ = nullptr;

	};

}