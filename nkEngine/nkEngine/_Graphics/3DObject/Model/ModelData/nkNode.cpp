/**
* ノードクラスの実装.
*/
#include"nkstdafx.h"
#include"nkNode.h"

#include<fbxsdk.h>

namespace nkEngine
{

	/**
	* 作成.
	*
	* @param fbxNode	FBXSDKのノードクラス.
	* @param parent		親のポインタ.
	* @param modelData	モデルデータ.
	*/
	void INode::Create(FbxNode* fbxNode, Transform* parent, ModelData* modelData)
	{
		//名前.
		Name_ = fbxNode->GetName();

		//親を設定.
		Transform_.SetParent(parent);

		IsStart_ = true;

	}

	/**
	* 更新.
	*/
	void INode::Update()
	{
		//トランスフォームの更新.
		Transform_.Update();
	}

}