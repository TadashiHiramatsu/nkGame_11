/**
* ���f���f�[�^�N���X�̒�`.
*/
#pragma once

#include"ModelData\nkMesh.h"

namespace nkEngine
{

	/**
	* ���f���f�[�^�N���X.
	*/
	class ModelData : Noncopyable
	{
	public:

		/**
		* �R���X�g���N�^.
		*/
		ModelData()
		{
		}

		/**
		* �f�X�g���N�^.
		*/
		~ModelData()
		{
		}

		/**
		* �ǂݍ���.
		*
		* @param fileName	�t�@�C����.
		*/
		void Load(string fileName, Transform* parent);

		/**
		* �X�V.
		*/
		void Update();

		/**
		* ���b�V�����X�g�̎擾.
		*/
		vector<Mesh*>& GetMeshList()
		{
			return MeshList_;
		}

	private:
		 
		/**
		* ���b�V���쐬.
		*
		* @param fbxScene	FBXSDK�̃V�[���N���X.
		*/
		void CreateMesh(FbxScene* fbxScene, Transform* parent);

		/**
		* �m�[�h�T��.
		*
		* @param fbxNode	FBXSDK�̃m�[�h�N���X.
		* @param parent		�e�̃g�����X�t�H�[���|�C���^. 
		*/
		void ProbeNode(FbxNode* fbxNode,Transform* parent);

	private:

		/** ���b�V�����X�g. */
		vector<Mesh*> MeshList_;

	};

}