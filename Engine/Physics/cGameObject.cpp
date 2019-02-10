#include "cGameObject.h"

eae6320::cResult eae6320::Physics::cGameObject::CreateGameObject(cGameObject *& o_GameObject)
{
	cResult result = Results::Success;
	o_GameObject = new cGameObject();
	if (o_GameObject == nullptr) { result = Results::Failure; }
	return result;
}

eae6320::cResult eae6320::Physics::cGameObject::CreateGameObject(Math::sVector i_Position, Math::cQuaternion i_Rotation, cGameObject *& o_GameObject)
{
	cResult result = Results::Success;
	o_GameObject = new cGameObject();
	if (o_GameObject == nullptr) return result = Results::Failure;
	o_GameObject->m_RigidBody.position = i_Position;
	o_GameObject->m_RigidBody.orientation = i_Rotation;
	return result;
}

eae6320::cResult eae6320::Physics::cGameObject::CreateGameObject(Math::sVector i_Position, Math::cQuaternion i_Rotation, Graphics::cMesh * i_Mesh, Graphics::cEffect * i_Effect, cGameObject *& o_GameObject)
{
	cResult result = Results::Success;
	o_GameObject = new cGameObject();
	if (o_GameObject == nullptr) return result = Results::Failure;
	o_GameObject->m_RigidBody.position = i_Position;
	o_GameObject->m_RigidBody.orientation = i_Rotation;
	o_GameObject->m_EffectMeshPairForRigidBody.m_RenderEffect = i_Effect;
	o_GameObject->m_EffectMeshPairForRigidBody.m_RenderMesh = i_Mesh;
	return result;
}

eae6320::cResult eae6320::Physics::cGameObject::CreateGameObject(Math::sVector i_Position, Graphics::cMesh * i_Mesh, Graphics::cEffect * i_Effect, cGameObject *& o_GameObject)
{
	cResult result = Results::Success;
	o_GameObject = new cGameObject();
	if (o_GameObject == nullptr) return result = Results::Failure;
	o_GameObject->m_RigidBody.position = i_Position;
	o_GameObject->m_EffectMeshPairForRigidBody.m_RenderEffect = i_Effect;
	o_GameObject->m_EffectMeshPairForRigidBody.m_RenderMesh = i_Mesh;
	return result;
}

void eae6320::Physics::cGameObject::SetGameObjectPosition(Math::sVector i_Position)
{
	m_RigidBody.position = i_Position;
}

void eae6320::Physics::cGameObject::SetGameObjectRotation(Math::cQuaternion i_Rotation)
{
	m_RigidBody.orientation = i_Rotation;
}

eae6320::Math::sVector eae6320::Physics::cGameObject::GetGameObjectPosition()
{
	return m_RigidBody.position;
}

eae6320::Math::cQuaternion eae6320::Physics::cGameObject::GetGameObjectRotation()
{
	return m_RigidBody.orientation;
}

eae6320::Math::sVector eae6320::Physics::cGameObject::GetGameObjectVelocity()
{
	return m_RigidBody.velocity;
}

void eae6320::Physics::cGameObject::SetGameObjectVelocity(Math::sVector i_Velocity)
{
	m_RigidBody.velocity = i_Velocity;
}

void eae6320::Physics::cGameObject::SetGameObjectAcceleration(Math::sVector i_Acceleration)
{
	m_RigidBody.acceleration = i_Acceleration;
}

void eae6320::Physics::cGameObject::SetGameObjectMesh(Graphics::cMesh * i_Mesh)
{
	m_EffectMeshPairForRigidBody.m_RenderMesh = i_Mesh;
}

void eae6320::Physics::cGameObject::SetGameObjectEffect(Graphics::cEffect * i_Effect)
{
	m_EffectMeshPairForRigidBody.m_RenderEffect = i_Effect;
}

void eae6320::Physics::cGameObject::SetGameObjectHandles(Graphics::cMesh::Handle i_MeshHandle,
	Graphics::cEffect::Handle i_EffectHandle)
{
	m_MeshHandle = i_MeshHandle;
	m_EffectHandle = i_EffectHandle;
}

eae6320::Graphics::cMesh * eae6320::Physics::cGameObject::GetGameObjectMesh() const
{
	return m_EffectMeshPairForRigidBody.m_RenderMesh;
}

eae6320::Graphics::cEffect * eae6320::Physics::cGameObject::GetGameObjectEffect() const
{
	return m_EffectMeshPairForRigidBody.m_RenderEffect;
}

eae6320::Graphics::sEffectsAndMeshesToRender eae6320::Physics::cGameObject::GetMeshEffectPair() const
{
	return m_EffectMeshPairForRigidBody;
}

void eae6320::Physics::cGameObject::UpdateGameObject(float i_elapsedSecondCount_sinceLastUpdate)
{
	m_RigidBody.Update(i_elapsedSecondCount_sinceLastUpdate);
}

eae6320::Math::sVector eae6320::Physics::cGameObject::PredictFuturePosition(float i_secondCountToExtrapolate) const
{
	return m_RigidBody.PredictFuturePosition(i_secondCountToExtrapolate);
}

eae6320::Math::cQuaternion eae6320::Physics::cGameObject::PredictFutureOrientation(float i_secondCountToExtrapolate) const
{
	return m_RigidBody.PredictFutureOrientation(i_secondCountToExtrapolate);
}

eae6320::Math::cMatrix_transformation eae6320::Physics::cGameObject::GetLocalToWorldTransformation(float i_secondCountToExtrapolate)
{
	return eae6320::Math::cMatrix_transformation(m_RigidBody.PredictFutureOrientation(i_secondCountToExtrapolate),
	                                             m_RigidBody.PredictFuturePosition(i_secondCountToExtrapolate));
}