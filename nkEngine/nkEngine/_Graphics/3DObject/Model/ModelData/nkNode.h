/**
* ノードクラスの定義.
*/
#pragma once

namespace nkEngine
{

	class ModelData;

	/**
	* ノードクラス.
	*/
	class INode : public IGameObject
	{
	public:

		/**
		* ノードタイプコード.
		*/
		enum class NodeTypeE
		{
			Unknown,	//!< アンノウン.
			Null,		//!< ヌル.
			Mesh,		//!< メッシュ.
			SkinMesh,	//!< スキンメッシュ.
			Bone,		//!< ボーン.
		};

	public:

		/**
		* コンストラクタ.
		*/
		INode()
		{
		}

		/**
		* デストラクタ.
		*/
		~INode()
		{
		}

		/**
		* 作成.
		*
		* @param fbxNode	FBXSDKのノードクラス.
		* @param parent		親のポインタ.
		* @param modelData	モデルデータ.
		*/
		virtual void Create(FbxNode* fbxNode, Transform* parent, ModelData* modelData);

		/**
		* 更新.
		*/
		virtual void Update();

		/**
		* ノードタイプを取得.
		*/
		NodeTypeE GetNodeType() const
		{
			return NodeType_;
		}

	protected:

		/** ノードタイプ. */
		NodeTypeE NodeType_ = NodeTypeE::Unknown;

	};

}