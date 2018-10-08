// Includes
//=========

#include "cMyGame.h"
#include <Engine/Graphics/Graphics.h>
#include <Engine/Asserts/Asserts.h>
#include <Engine/UserInput/UserInput.h>

// Inherited Implementation
//=========================

// Run
//----

void eae6320::cMyGame::UpdateCameraPosition()
{
	m_Camera->SetCameraVelocity(Math::sVector(0, 0, 0));
	m_Camera->SetAngularSpeed(0.0f);

	if (UserInput::IsKeyPressed(UserInput::KeyCodes::Down))
	{
		m_Camera->SetCameraVelocity(Math::sVector(0, 0, 10.0f));
	}
	if (UserInput::IsKeyPressed(UserInput::KeyCodes::Up))
	{
		m_Camera->SetCameraVelocity(Math::sVector(0, 0, -10.0f));
	}
	if (UserInput::IsKeyPressed(UserInput::KeyCodes::Right))
	{
		m_Camera->SetCameraVelocity(Math::sVector(10.0f, 0, 0));
	}
	if (UserInput::IsKeyPressed(UserInput::KeyCodes::Left))
	{
		m_Camera->SetCameraVelocity(Math::sVector(-10.0f, 0, 0));
	}
	if (UserInput::IsKeyPressed(UserInput::KeyCodes::Control))
	{
		m_Camera->SetCameraVelocity(Math::sVector(0, 10.0f, 0));
	}
	if (UserInput::IsKeyPressed(UserInput::KeyCodes::Alt))
	{
		m_Camera->SetCameraVelocity(Math::sVector(0, -10.0f, 0));
	}
	if (UserInput::IsKeyPressed('Z'))
	{
		m_Camera->SetAngularSpeed(1.0f);
	}
	if (UserInput::IsKeyPressed('X'))
	{
		m_Camera->SetAngularSpeed(-1.0f);
	}
}

void eae6320::cMyGame::UpdateGameobjectPosition()
{
	for (int i = 0; i < m_NumberOfGameObjects; i++)
	{
		m_GameObjects[i]->SetGameObjectVelocity(Math::sVector(0, 0, 0));
	}
//GO1
	if (UserInput::IsKeyPressed('W'))
	{
		m_GameObjects[0]->SetGameObjectVelocity(Math::sVector(0, 10.0f, 0.0f));
	}
	if (UserInput::IsKeyPressed('A'))
	{
		m_GameObjects[0]->SetGameObjectVelocity(Math::sVector(-10.0f, 0, 0));
	}
	if (UserInput::IsKeyPressed('S'))
	{
		m_GameObjects[0]->SetGameObjectVelocity(Math::sVector(0,-10.0f,0));
	}
	if (UserInput::IsKeyPressed('D'))
	{
		m_GameObjects[0]->SetGameObjectVelocity(Math::sVector(10.0f,0,0));
	}

//GO2
	//m_GameObjects[1]->SetGameObjectVelocity(Math::sVector(0, 0, 0));
	if (UserInput::IsKeyPressed('I'))
	{
		m_GameObjects[1]->SetGameObjectVelocity(Math::sVector(0, 10.0f, 0.0f));
	}
	if (UserInput::IsKeyPressed('J'))
	{
		m_GameObjects[1]->SetGameObjectVelocity(Math::sVector(-10.0f, 0, 0));
	}
	if (UserInput::IsKeyPressed('K'))
	{
		m_GameObjects[1]->SetGameObjectVelocity(Math::sVector(0, -10.0f, 0));
	}
	if (UserInput::IsKeyPressed('L'))
	{
		m_GameObjects[1]->SetGameObjectVelocity(Math::sVector(10.0f, 0, 0));
	}
}


void eae6320::cMyGame::UpdateBasedOnInput()
{
	// Is the user pressing the ESC key?
	if (UserInput::IsKeyPressed(UserInput::KeyCodes::Escape))
	{
		// Exit the application
		const auto result = Exit(EXIT_SUCCESS);
		EAE6320_ASSERT(result);
	}
	Application::cbApplication::SetSimulationRate(UserInput::IsKeyPressed(UserInput::KeyCodes::Shift) ? 0.5f : 1.0f);
	m_NumberOfMeshesToRender = UserInput::IsKeyPressed(UserInput::KeyCodes::F1) ? 1 : m_NumberOfGameObjects;
	if (UserInput::IsKeyPressed(UserInput::KeyCodes::F2))
	{
		if (!isEffectSwapped)
		{
			std::swap(s_Effect, s_Effect2);
			isEffectSwapped = true;
		}
	}
	else
	{
		if (isEffectSwapped)
		{
			std::swap(s_Effect, s_Effect2);
			isEffectSwapped = false;
		}
	}
	if (UserInput::IsKeyPressed(UserInput::KeyCodes::F3))
	{
		if (!isMeshSwapped)
		{
			std::swap(mesh1Handle, mesh3Handle);
			isMeshSwapped = true;
		}
	}
	else
	{
		if (isMeshSwapped)
		{
			std::swap(mesh1Handle, mesh3Handle);
			isMeshSwapped = false;
		}
	}
	UpdateCameraPosition();
	UpdateGameobjectPosition();
}

void eae6320::cMyGame::UpdateSimulationBasedOnTime(const float i_elapsedSecondCount_sinceLastUpdate)
{
	m_Camera->Update(i_elapsedSecondCount_sinceLastUpdate);
	for (int i = 0; i < m_NumberOfGameObjects; i++)
	{
		m_GameObjects[i]->UpdateGameObject(i_elapsedSecondCount_sinceLastUpdate);
	}
}

void eae6320::cMyGame::SubmitDataToBeRendered(const float i_elapsedSecondCount_systemTime, const float i_elapsedSecondCount_sinceLastSimulationUpdate)
{
	//Submit The value of Backbuffer
	eae6320::Graphics::SetBackBufferValue(eae6320::Graphics::sColor
		{
			abs(sin(i_elapsedSecondCount_systemTime)),
			abs(cos(i_elapsedSecondCount_systemTime)) ,
			abs(cos(i_elapsedSecondCount_systemTime)) ,
			1
		});


	m_GameObjects[0]->SetGameObjectEffect(s_Effect);
	m_GameObjects[0]->SetGameObjectMesh(eae6320::Graphics::cMesh::s_Manager.Get(mesh1Handle));
	m_GameObjects[1]->SetGameObjectEffect(s_Effect2);
	m_GameObjects[1]->SetGameObjectMesh(eae6320::Graphics::cMesh::s_Manager.Get(mesh2Handle));

	m_EffectsAndMeshes[0] = m_GameObjects[0]->GetMeshEffectPair();
	m_EffectsAndMeshes[1] = m_GameObjects[1]->GetMeshEffectPair();

	for (size_t i = 0; i < m_NumberOfGameObjects; i++)
	{
		m_GameObjectLocalToWorldTransforms[i] = m_GameObjects[i]->GetLocalToWorldTransformation(i_elapsedSecondCount_sinceLastSimulationUpdate);
	}

	eae6320::Graphics::SetCameraToRender(m_Camera, i_elapsedSecondCount_sinceLastSimulationUpdate);

	eae6320::Graphics::SetEffectsAndMeshesToRender(m_EffectsAndMeshes, m_GameObjectLocalToWorldTransforms, m_NumberOfMeshesToRender);
}

// Initialization / Clean Up
//--------------------------

eae6320::cResult eae6320::cMyGame::Initialize()
{
	std::string m_vertShader1Location = "data/Shaders/Vertex/standard.shader";
	std::string m_fragShader1Location = "data/Shaders/Fragment/animatedshader.shader";
	std::string m_vertShader2Location = "data/Shaders/Vertex/standard.shader";
	std::string m_fragShader2Location = "data/Shaders/Fragment/standard.shader";

	eae6320::Graphics::cCamera::CreateCamera(m_Camera);

	m_Camera->SetCameraPosition(Math::sVector(0, 0, 10));

	eae6320::Physics::cGameObject::CreateGameObject(m_GameObjects[0]);
	eae6320::Physics::cGameObject::CreateGameObject(m_GameObjects[1]);

	m_GameObjects[0]->SetGameObjectPosition(Math::sVector(1, 0, 0));

	m_GameObjects[1]->SetGameObjectPosition(Math::sVector(0, 0, 0));

	std::string fname = "data/Meshes/TestMesh.txt";
	eae6320::Graphics::cMesh::s_Manager.Load(fname.c_str(), mesh1Handle);
	fname = "data/Meshes/Mesh2.txt";
	eae6320::Graphics::cMesh::s_Manager.Load(fname.c_str(), mesh2Handle);
	fname = "data/Meshes/Mesh3.txt";
	eae6320::Graphics::cMesh::s_Manager.Load(fname.c_str(), mesh3Handle);


	if (!(eae6320::Graphics::cEffect::CreateEffect(m_vertShader1Location, m_fragShader1Location, eae6320::Graphics::RenderStates::DepthBuffering, s_Effect)))
	{
		EAE6320_ASSERT(false);
		//goto OnExit;
	}
	if (!(eae6320::Graphics::cEffect::CreateEffect(m_vertShader2Location, m_fragShader2Location, eae6320::Graphics::RenderStates::DepthBuffering, s_Effect2)))
	{
		EAE6320_ASSERT(false);
		//goto OnExit;
	}
	if (!(eae6320::Graphics::cEffect::CreateEffect(m_vertShader2Location, m_fragShader2Location, eae6320::Graphics::RenderStates::DepthBuffering, s_Effect3)))
	{
		EAE6320_ASSERT(false);
		//goto OnExit;
	}
	return Results::Success;
}

eae6320::cResult eae6320::cMyGame::CleanUp()
{
	s_Effect->DecrementReferenceCount();
	s_Effect2->DecrementReferenceCount();
	s_Effect3->DecrementReferenceCount();
	eae6320::Graphics::cMesh::s_Manager.Release(mesh1Handle);
	eae6320::Graphics::cMesh::s_Manager.Release(mesh2Handle);
	eae6320::Graphics::cMesh::s_Manager.Release(mesh3Handle);
	for (int i = 0; i < m_NumberOfGameObjects; i++)
	{
		m_GameObjects[i]->DecrementReferenceCount();
	}
	m_Camera->DecrementReferenceCount();
	return Results::Success;
}
