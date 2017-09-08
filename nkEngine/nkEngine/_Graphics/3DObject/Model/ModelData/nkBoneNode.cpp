/**
* ボーンノードクラスの実装.
*/
#include"nkstdafx.h"
#include"nkBoneNode.h"

namespace nkEngine
{

	/**
	* 作成.
	*
	* @param fbxNode	FBXSDKのノードクラス.
	* @param parent		親のポインタ.
	* @param modelData	モデルデータ.
	*/
	void BoneNode::Create(FbxNode * fbxNode, Transform * parent, ModelData * modelData)
	{
		//ボーンタイプに設定.
		NodeType_ = NodeTypeE::Bone;

		INode::Create(fbxNode, parent, modelData);
	}

}