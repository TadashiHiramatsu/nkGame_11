/**
 * シーンクラスの定義.
 */
#pragma once 

namespace nkEngine
{
	/**
	 * シーンの基底クラス.
	 * このクラスを継承するシーンクラスを作成して
	 * シーンマネージャに登録する必要がある
	 */
	class IScene : Noncopyable
	{
	public:

		/**
		 * コンストラクタ.
		 */
		IScene()
		{
		}

		/**
		 * デストラクタ.
		 */
		virtual ~IScene()
		{
		}

	public:

		/**
		 * 初期化.
		 */
		virtual void Start() = 0;

	};
}
