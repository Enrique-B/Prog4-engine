#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "ColliderComponent.h"
#include "TransformComponent.h"
#include "StateComponent.h"
#include "BubbleComponent.h"

Fried::Scene::Scene(const std::string& name) noexcept
	: m_Name(name) , timeUntilNextUpdate{0}
{
}

Fried::Scene::~Scene()
{
	size_t size{ m_pObjects.size() };
	for (size_t i = 0; i < size; i++)
	{
		SafeDelete(m_pObjects[i]);
	}
	m_pObjects.clear();
	size = m_pDeactivatedGameObjects.size();
	for (size_t i = 0; i < size; i++)
	{
		SafeDelete(m_pDeactivatedGameObjects[i]);
	}
	m_pDeactivatedGameObjects.clear();
}

void Fried::Scene::AddGameObject(GameObject* pObject)
{
	if (pObject != nullptr)
	{
#ifdef _DEBUG
		if (std::find(m_pObjects.cbegin(), m_pObjects.cend(), pObject) != m_pObjects.cend())
		{
			throw std::runtime_error(std::string("Scene::AddGameObject gameObject is already in the scene \n"));
		}
#endif // _DEBUG
		m_pObjects.push_back(pObject);
		pObject->SetScene(this);
		pObject->Initialize();
		pObject->SetIsActive(true);
	}
	else
	{
		throw std::runtime_error(std::string("Scene::AddGameObject was a nullptr"));
	}
}

void Fried::Scene::AddGameObjectToNonActive(GameObject* pObject) noexcept(false)
{
	if (pObject != nullptr)
	{
#ifdef _DEBUG
		if (std::find(m_pDeactivatedGameObjects.cbegin(), m_pDeactivatedGameObjects.cend(), pObject) != m_pDeactivatedGameObjects.cend())
		{
			throw std::runtime_error(std::string("Scene::AddGameObjectToNonActive is already in the scene \n"));
		}
#endif // _DEBUG
		m_pDeactivatedGameObjects.push_back(pObject);
	}
	else
	{
		throw std::runtime_error(std::string("Scene::AddGameObject was a nullptr"));
	}
}

void Fried::Scene::RemoveGameObject(GameObject* object)
{
	auto it = std::find(m_pObjects.cbegin(), m_pObjects.cend(), object);
#ifdef _DEBUG
	if (std::find(m_pObjects.cbegin(), m_pObjects.cend(), object) == m_pObjects.cend())
	{
		throw std::runtime_error(std::string("Scene::RemoveGameObject gameObject was not in the scene \n"));
	}
#endif
	m_pObjects.erase(it);
	object->SetScene(nullptr);
}

void Fried::Scene::RemoveGameObjectToNonActive(GameObject* pObject) noexcept(false)
{
	auto it = std::find(m_pDeactivatedGameObjects.cbegin(), m_pDeactivatedGameObjects.cend(), pObject);
#ifdef _DEBUG
	if (std::find(m_pDeactivatedGameObjects.cbegin(), m_pDeactivatedGameObjects.cend(), pObject) == m_pDeactivatedGameObjects.cend())
	{
		throw std::runtime_error(std::string("Scene::RemoveGameObjectToNonActive gameObject was not in the scene \n"));
	}
#endif
	m_pDeactivatedGameObjects.erase(it);
	pObject->SetScene(nullptr);

}

void Fried::Scene::AddCollider(ColliderComponent* pCollider)
{
	if (pCollider->GetIsStatic())
	{
#ifdef _DEBUG
		if (std::find(m_StaticColliders.begin(), m_StaticColliders.end(), pCollider) != m_StaticColliders.end())
		{
			throw std::runtime_error(std::string("Collider is already in the scene \n"));
		}
#endif // _DEBUG
		m_StaticColliders.push_back(pCollider);
	}
	else
	{
#ifdef _DEBUG
		if (std::find(m_DynamicColliders.begin(), m_DynamicColliders.end(), pCollider) != m_DynamicColliders.cend())
		{
			throw std::runtime_error(std::string("Collider is already in the scene \n"));
		}
#endif // _DEBUG
		m_DynamicColliders.push_back(pCollider);
	}
}

void Fried::Scene::RemoveCollider(ColliderComponent* pCollider)
{
	if (pCollider->GetIsStatic())
	{
		auto it = std::find(m_StaticColliders.begin(), m_StaticColliders.end(), pCollider);
#ifdef _DEBUG
		if (it == m_StaticColliders.end())
		{
			throw std::runtime_error(std::string("Scene::RemoveCollider Collider is not in Vector\n"));
		}
#endif
		m_StaticColliders.erase(it);
	}
	else
	{
		auto it = std::find(m_DynamicColliders.begin(), m_DynamicColliders.end(), pCollider);
#ifdef _DEBUG
		if (it == m_DynamicColliders.end())
		{
			throw std::runtime_error(std::string("Scene::RemoveCollider Collider is not in Vector\n"));
		}
#endif
		m_DynamicColliders.erase(it);
	}
}

void Fried::Scene::Update(float elapsedSec)
{
	const size_t size{ m_pObjects.size() };
	for (size_t i = 0; i < size; i++)
	{
		m_pObjects[i]->Update(elapsedSec);
	}
}

void Fried::Scene::CollisionUpdate(float elapsedSec) noexcept
{
	timeUntilNextUpdate += elapsedSec; 
	if (timeUntilNextUpdate > 0.02f) // 1/50 == will run at 50 fps 
	{
		timeUntilNextUpdate = 0;
		const size_t dynamicSize{ m_DynamicColliders.size() };
		const size_t staticSize{ m_StaticColliders.size() };
		HitInfo info{};
		//loop over the dynamic colliders
		for (size_t i = 0; i < dynamicSize; i++)
		{
			m_DynamicColliders[i]->SetTrigger(ColliderTrigger::None);
			//get the collisionLines from the dynamic collider
			const std::vector<CollisionLine> lines{ m_DynamicColliders[i]->GetLines() };
			CheckStaticCollision(i, lines);
			CheckDynamicCollision(i, lines);
		}
	}
}

void Fried::Scene::DeactivateNonActiveGameObjects()
{
	// can't be a range based for loop because i'm going to delete stuff here
	for (size_t i = 0; i < m_pObjects.size(); i++)
	{
		if (!m_pObjects[i]->GetIsActive())
		{
			GameObject* pCopy{ m_pObjects[i] };
			RemoveGameObject(pCopy);
			if (pCopy->HasComponent(ComponentName::collider))
			{
				std::vector<ColliderComponent*> collidersInGameObject{ pCopy->GetComponents<ColliderComponent>(ComponentName::collider) };
				const size_t size = collidersInGameObject.size();
				for (size_t j = 0; j < size; j++)
				{
					RemoveCollider(collidersInGameObject[j]);
				}
			}
			AddGameObjectToNonActive(pCopy);
		}
	}
}

void Fried::Scene::Render() const noexcept
{
	for (const auto& object : m_pObjects)
	{
		object->Render();
	}
}

void Fried::Scene::RenderCollision() const noexcept
{
	for (const auto& object : m_pObjects)
	{
		object->RenderCollision();
	}
}

bool Fried::Scene::Raycast(const Fried::line& line, bool raycastStaticColliders, bool raycastDynamicColiders, Fried::HitInfo& hitInfo)
{
	if (!raycastDynamicColiders && !raycastStaticColliders)
	{
		return false;
	}
	if (raycastStaticColliders)
	{
		const size_t size{m_StaticColliders.size()};
		for (size_t i = 0; i < size; i++)
		{
			line.intersect(m_StaticColliders[i]->GetCollisionRect(), hitInfo);
		}
	}
	if (raycastDynamicColiders)
	{
		const size_t size{ m_DynamicColliders.size() };
		for (size_t i = 0; i < size; i++)
		{
			line.intersect(m_DynamicColliders[i]->GetCollisionRect(), hitInfo);
		}
	}
	return hitInfo.hit;
}

bool Fried::Scene::RaycastPLayer(const Fried::line& line, Fried::HitInfo& hitinfo)
{
	const size_t size{ m_DynamicColliders.size() };
	for (size_t i = 0; i < size; i++)
	{
		Fried::HitInfo info; 
		line.intersect(m_DynamicColliders[i]->GetCollisionRect(), info);
		if (info.hit && !m_DynamicColliders[i]->GetGameObject()->HasComponent(ComponentName::enemy))
		{
			hitinfo.hit = true;
			hitinfo += info; 
		}
	}
	return hitinfo.hit;
}

void Fried::Scene::CheckStaticCollision(size_t index, const std::vector<CollisionLine>& lines)
{
	HitInfo info{};
	const size_t staticSize{ m_StaticColliders.size() };
	const size_t lineSize{ lines.size() };
	//loop over the static colliders and the lines so i can see if they intersect
	StateComponent *state = m_DynamicColliders[index]->GetGameObject()->GetComponent<StateComponent>(ComponentName::state);
	Fried::float2 velocity = state->GetVelicity();
	for (size_t j = 0; j < staticSize; j++)
	{
		const SDL_Rect staticCollider{ m_StaticColliders[j]->GetCollisionRect() };
		for (size_t l = 0; l < lineSize; l++)
		{
			// to be continued
			lines[l].line.intersect(staticCollider, info);
			if (info.hit)
			{
				const size_t hitinfoVectorSize{ info.intersectPoint.size() };
				for (size_t h = 0; h < hitinfoVectorSize; h++)
				{
					float2 move{};
					if (lines[l].collision & ColliderTrigger::left)
					{
						move.x = -(lines[l].line.p2.x - info.intersectPoint[h].x);
						if (!m_DynamicColliders[index]->HasTrigger(ColliderTrigger::left))
						{
							m_DynamicColliders[index]->SetTrigger(ColliderTrigger::left);
						}
					}
					if (lines[l].collision & ColliderTrigger::right)
					{
						move.x = -(lines[l].line.p2.x - info.intersectPoint[h].x);
						if (!m_DynamicColliders[index]->HasTrigger(ColliderTrigger::right))
						{
							m_DynamicColliders[index]->SetTrigger(ColliderTrigger::right);
						}
					}
					if (lines[l].collision & ColliderTrigger::Top)
					{
						if (velocity.y > 0)
						{
							if (!m_DynamicColliders[index]->HasTrigger(ColliderTrigger::Top))
							{
								move.y = (info.intersectPoint[h].y - lines[l].line.p2.y) + 1;
								m_DynamicColliders[index]->SetTrigger(ColliderTrigger::Top);
							}
						}
					}
					if (lines[l].collision & ColliderTrigger::Bottom)
					{
						if (velocity.y > 0)
						{
							if (!m_DynamicColliders[index]->HasTrigger(ColliderTrigger::Bottom))
							{
								move.y = (info.intersectPoint[h].y - lines[l].line.p2.y) + 1;
								m_DynamicColliders[index]->SetTrigger(ColliderTrigger::Bottom);
							}
						}
					}
					m_DynamicColliders[index]->GetGameObject()->GetTransform()->Move(move);
					m_DynamicColliders[index]->Update(0);
				}
				info.hit = false;
				info.intersectPoint.clear();
			}
		}
	}
}

void Fried::Scene::CheckDynamicCollision(size_t index, const std::vector<CollisionLine>& lines)
{
	const size_t dynamicSize{ m_DynamicColliders.size() };
	const size_t lineSize{ lines.size() };
	HitInfo info{};
	GameObject* pCurrentObject{m_DynamicColliders[index]->GetGameObject()};
	const bool isCurrentObjectPlayer{ !pCurrentObject->HasComponent(ComponentName::bubble) && !pCurrentObject->HasComponent(ComponentName::enemy) };
	const bool isCurrentObjectBubble{ pCurrentObject->HasComponent(ComponentName::bubble) };

	for (size_t i = 0; i < dynamicSize; i++)
	{
		GameObject* pLoopedObject = m_DynamicColliders[i]->GetGameObject();
		if (index != i && pLoopedObject->GetIsActive()) // don't want to check itself
		{
			for (size_t l = 0; l < lineSize; l++)
			{
				lines[l].line.intersect(m_DynamicColliders[i]->GetCollisionRect(), info);
				if (info.hit)
				{
					const bool isLoopedObjectEnemy{ pLoopedObject->HasComponent(ComponentName::enemy) };
					const bool isLoopedObjectBubble{ pLoopedObject->HasComponent(ComponentName::bubble) };
					if (isCurrentObjectPlayer && isLoopedObjectEnemy)
					{
						// do damage to player 
						m_DynamicColliders[index]->SetTrigger(ColliderTrigger::PlayerHit);
					}
					else if (isLoopedObjectEnemy && isCurrentObjectBubble)
					{
						BubbleComponent* pBubble = pCurrentObject->GetComponent<BubbleComponent>(ComponentName::bubble);
						if (!pBubble->IsHitByEnemy())
						{
							m_DynamicColliders[index]->SetTrigger(ColliderTrigger::EnemyHit);
							// capture enemy in bubble
							pBubble->SetEnemyType(pLoopedObject->GetComponent<EnemyComponent>(ComponentName::enemy)->GetEnemyType());
							// set enemy to non active
							pLoopedObject->SetIsActive(false);
						}
					}
					else if (isCurrentObjectPlayer && isLoopedObjectBubble)
					{
						m_DynamicColliders[i]->SetTrigger(ColliderTrigger::PlayerHit);
					}
					info.hit = false;
					info.intersectPoint.clear();
				}
			}
		}
	}
}

