/**
* デバッグウィンドウクラスの定義.
*/
#pragma once

namespace nkEngine
{

	/**
	* デバッグウィンドウクラス.
	*/
	class IDebugWindow : Noncopyable
	{
	public:

		/**
		* コンストラクタ.
		*/
		IDebugWindow()
		{
		}

		/**
		* デストラクタ.
		*/
		virtual ~IDebugWindow()
		{
		}

		/**
		* 初期化.
		*/
		virtual void Start()
		{
		}

		/**
		* 描画.
		*/
		virtual void Render() = 0;

		/**
		* 有効フラグを設定.
		*/
		void SetActive(bool is)
		{
			IsActive_ = is;
		}

		/**
		* 名前を取得.
		*/
		const string& GetName() const
		{
			return Name_;
		}

	public:

		/**
		* 描画.
		* 管理クラスから呼ばれる.
		*/
		void RenderWrapper()
		{
			if (IsActive_)
			{
				Render();
			}
		}

	protected:

		/** 名前. */
		string Name_ = "";

		/** 有効フラグ. */
		bool IsActive_ = true;

	};

}