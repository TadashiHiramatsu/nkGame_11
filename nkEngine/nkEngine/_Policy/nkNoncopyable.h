/**
* NoncopyPolicyクラスの定義.
*/
#pragma once

namespace nkEngine
{

	/**
	* NoncopyPolicyクラス.
	* クラスのコピーを禁止するクラス.
	*/
	class Noncopyable
	{
	public:

		/**
		* デフォルトコンストラクタ.
		*/
		Noncopyable() = default;

		/**
		* コピーコンストラクタ.
		* 削除.
		*/
		Noncopyable(const Noncopyable&) = delete;

		/**
		* 代入operator演算子.
		* 削除.
		*/
		Noncopyable& operator=(const Noncopyable&) = delete;

	};

}