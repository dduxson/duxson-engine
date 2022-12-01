#pragma once
/*!********************************************************************
* File:	HUDBuilder.h
*
* \brief	Class that generates an empty HUD that can be rendered with
*			the Duxson Engine.
*
* \author	David Duxson
*
* \date	02/11/2011
*
**********************************************************************/
#include "../DuxsonEngine/Include/Entity.h"
#include "../DuxsonEngine/Include/CameraComponent.h"
#include "IMazeEntityBuilder.h"

class HUDBuilder : public IMazeEntityBuilder
{
public:
	/*!
	*	\brief	Constructor for HUDBuilder class.
	*/
	HUDBuilder();

	/*!
	*	\brief	Destructor for HUDBuilder class.
	*/
	virtual ~HUDBuilder();

	/*!
	*	\brief	Sets the background texture of the HUD.
	*	\remark The alpha values of the texture should be set to alter the
	*			transparency of the HUD.
	*	\param[in] texFilename The texture for the HUD background
	*/
	void setHUDBackgroundTexture(const std::string& texFilename);

	/*!
	*	\brief	Sets the shader program for the background of the HUD.
	*	\param[in] filename The shader program for the HUD background
	*/
	void setHUDBackgroundShader(const std::string& filename);

	/*!
	*	\brief	Sets the created HUD's viewport.
	*	\param[in]	params The viewport parameters.
	*/
	void setViewport(const DE::ViewportParams& params);

	/*!
	*	\brief	Sets the HUD's orthographic projection matrix.
	*	\param[in] left		The left value for the ortho 2d projection matrix.
	*	\param[in] right	The right value for the ortho 2d projection matrix.
	*	\param[in] bottom	The bottom value for the ortho 2d projection matrix.
	*	\param[in] top		The top value for the ortho 2d projection matrix.
	*/
	void setHUDOrthoProjectionMatrix(float left, float right, float bottom, float top);

	/*!
	*	\brief	see IMazeEntityBuilder
	*/
	virtual DE::Entity::SPtr generateEntity(const Maze &maze);

private:
	/*!
	*	\brief	Generates a quad of unit size The transluceny
	*			will depend on the alpha of the colour value
	*			supplied.
	*/
	DE::Entity::SPtr generateQuad();

	/*!
	*	\brief	Creates the HUD camera.
	*/
	DE::Entity::SPtr createHudCam();

private:
	std::string m_texFilename;			///< The texture for the background quad.
	std::string m_shaderProgFilename;	///< The shader program filename.

protected:
	std::string m_quadName;					///< The unique name for the quad for this HUD.
	DE::ViewportParams m_viewportParams;	///< Parameters for the viewport.

	float m_orthoLeft;		///< The left value for the ortho 2d projection matrix.
	float m_orthoRight;		///< The right value for the ortho 2d projection matrix.
	float m_orthoBottom;	///< The bottom value for the ortho 2d projection matrix.
	float m_orthoTop;		///< The top value for the ortho 2d projection matrix.
};