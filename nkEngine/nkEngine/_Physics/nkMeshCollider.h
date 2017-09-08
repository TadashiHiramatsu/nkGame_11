/**
 * ���b�V���R���C�_�[�N���X�̒�`.
 */
#pragma once

#include"nkCollider.h"
#include"_Graphics\3DObject\Model\nkModelData.h"

namespace nkEngine
{

	/**
	 * ���b�V���R���C�_�[�N���X.
	 */
	class MeshCollider : public ICollider
	{
	private:

		/** ���_�o�b�t�@. */
		using VertexBufferT = std::vector<Vector3>;
		/** �C���f�b�N�X�o�b�t�@. */
		using IndexBufferT = std::vector<unsigned int>;

	public:

		/**
		 * �R���X�g���N�^.
		 */
		MeshCollider()
		{
		}

		/**
		 * �f�X�g���N�^.
		 */
		~MeshCollider()
		{
		}

		/**
		 * ModelRender����Mesh�R���C�_�[�𐶐�.
		 *
		 * @param model			�X�L�����f��.
		 * @param offsetMatrix	�I�t�Z�b�g�s��.
		 */
		void Create(ModelData* model, const Matrix* offsetMatrix = nullptr);

		/**
		* ���.
		*/
		void Release()override
		{
			//���_�o�b�t�@�z��̍폜
			for (auto& vb : VertexBufferArray_)
			{
				vb.clear();
			}
			VertexBufferArray_.clear();

			//�C���f�b�N�X�o�b�t�@�̍폜
			for (auto& ib : IndexBufferArray_)
			{
				ib.clear();
			}
			IndexBufferArray_.clear();

			if (StridingMeshInterface_)
			{
				delete StridingMeshInterface_;
				StridingMeshInterface_ = nullptr;
			}
		}

	private:

		/** ���_�o�b�t�@�̔z��. */
		std::vector<VertexBufferT> VertexBufferArray_;
		/** �C���f�b�N�X�o�b�t�@�̔z��. */
		std::vector<IndexBufferT> IndexBufferArray_;

		/** �g���C�A���O���C���f�b�N�X�o�b�t�@. */
		btTriangleIndexVertexArray* StridingMeshInterface_ = nullptr;

	};

}