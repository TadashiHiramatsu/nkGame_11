/**
 * コリジョンの属性を定義.
 */
#pragma once

namespace nkEngine
{

	/** コリジョンの属性. */
	enum class ECollisionAttr
	{
		Ground,		//!< 地面.
		Character,	//!< キャラクター.
		User,		//!< ユーザー定義.
	};

}