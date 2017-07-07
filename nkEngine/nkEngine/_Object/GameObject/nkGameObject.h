/**
* ゲームオブジェクトクラスの定義.
*/
#pragma once

#include"../nkObject.h"

namespace nkEngine
{

	/**
	* ゲームオブジェクトマネージャに登録する基底クラス.
	* ゲーム開発では基本このクラスを継承させる.
	*/
	class IGameObject : public IObject
	{
	public:

		/**
		* コンストラクタ.
		*/
		IGameObject()
		{
		}

		/**
		* デストラクタ.
		*/
		virtual ~IGameObject()
		{
		}

		/**
		* 優先度を取得.
		*/
		PriorityT GetPriority() const
		{
			return Priority_;
		}

		/**
		* オブジェクトを削除する.
		*
		* @param object	オブジェクトのポインタ.
		*/
		void Destroy(IObject* object);

	public:

		/** トランスフォームクラス. */
		Transform Transform_;

	};

}