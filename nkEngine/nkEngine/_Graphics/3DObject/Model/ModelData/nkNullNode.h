/**
* ヌルノードクラスの定義.
*/
#pragma once

#include"nkNode.h"

namespace nkEngine
{

	/**
	* ヌルノードクラス.
	*/
	class NullNode : public INode
	{
	public:

		/**
		* コンストラクタ.
		*/
		NullNode()
		{
		}

		/**
		* デストラクタ.
		*/
		~NullNode()
		{
		}

		/**
		* 作成.
		*
		* @param fbxNode	FBXSDKのノードクラス.
		* @param parent		親のポインタ.
		* @param modelData	モデルデータ.
		*/
		void Create(FbxNode* fbxNode, Transform* parent, ModelData* modelData)override;

	private:

	};

}