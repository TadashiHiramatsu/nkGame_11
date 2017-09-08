/**
* ヌルノードクラスの実装.
*/
#include"nkstdafx.h"
#include"nkNullNode.h"

namespace nkEngine
{

	/**
	* 作成.
	*
	* @param fbxNode	FBXSDKのノードクラス.
	* @param parent		親のポインタ.
	* @param modelData	モデルデータ.
	*/
	void NullNode::Create(FbxNode * fbxNode, Transform * parent, ModelData * modelData)
	{
		//ヌルタイプに設定.
		NodeType_ = NodeTypeE::Null;

		INode::Create(fbxNode, parent, modelData);
	}

}