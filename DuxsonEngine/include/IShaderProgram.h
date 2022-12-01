#pragma once
#include <memory>

namespace DE
{
	class IVisualEngine;

	class IShaderProgram
	{
		public:
			typedef std::shared_ptr<IShaderProgram> SPtr;

			IShaderProgram() {}
			virtual ~IShaderProgram() {}

			/*!
			*	\brief	Gets whether we are currently holding a sucessfully linked
			*			shader program.
			*	\return True if have sucessfully linked shader program, false otherwise.
			*/
			virtual bool isSuccessfullyLinked() = 0;

			/*!
			*	\brief	Binds this shader program so it will be used.
			*/
			virtual void bind() = 0;

			/*!
			*	\brief	Updates all the uniforms in the shader ready for rendering.
			*	\param[in] The visual engine for the current setup. This is used for
			*			   accessing a map of values for uniforms.
			*/
			virtual void updateUniforms(std::shared_ptr<IVisualEngine> visualEngine) = 0;
	};
}