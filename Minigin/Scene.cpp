#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "ColliderComponent.h"
#include "TransformComponent.h"
#include "StateComponent.h"
#include "BubbleComponent.h"
#include "CharacterComponent.h"
#include "ItemComponent.h"
#include "../Game/Observer.h"
#include "../Game/Subject.h"

#include "SceneManager.h"
#include "StateManager.h"

Fried::Scene::Scene(const std::string& name) noexcept
	: m_Name(name), m_TimeUntilNextUpdate{ 0 }, m_TimeUntilNextScene{ 0 }
{
	m_pObservers.push_back(new EnemyObserver{ this });
}

Fried::Scene::~Scene()
{
	size_t size{ m_pObjects.size() };
	for (size_t i = 0; i < size; i++)
	{
		if (!m_pObjects[i]->HasComponent(ComponentName::Bubble))
		{
			SafeDelete(m_pObjects[i]);
		}
	}
	m_pObjects.clear();
	size = m_pDeactivatedGameObjects.size();
	for (size_t i = 0; i < size; i++)
	{
		SafeDelete(m_pDeactivatedGameObjects[i]);
	}
	m_pDeactivatedGameObjects.clear();
	size = m_pObservers.size();
	for (size_t i = 0; i < size; i++)
	{
		SafeDelete(m_pObservers[i]);
	}
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
	object->SetIsActive(false);
	if (object->HasComponent(ComponentName::Collider))
	{
		std::vector<ColliderComponent*> colliders = object->GetComponents<ColliderComponent>(ComponentName::Collider);
		const size_t colliderSize{ colliders.size() };
		for (size_t i = 0; i < colliderSize; i++)
		{
			RemoveCollider(colliders[i]);
		}
	}
	object->SetScene(nullptr);
	const size_t size{ m_pObservers.size() };
	for (size_t i = 0; i < size; i++)
	{
		object->GetSubject()->RemoveObserver(m_pObservers[0]);
	}
}

void Fried::Scene::RemoveGameObjectFromNonActive(GameObject* pObject) noexcept(false)
{
	auto it = std::find(m_pDeactivatedGameObjects.cbegin(), m_pDeactivatedGameObjects.cend(), pObject);
#ifdef _DEBUG
	if (std::find(m_pDeactivatedGameObjects.cbegin(), m_pDeactivatedGameObjects.cend(), pObject) == m_pDeactivatedGameObjects.cend())
	{
		throw std::runtime_error(std::string("Scene::RemoveGameObjectFromNonActive gameObject was not in the scene \n"));
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
	pCollider->SetTrigger(ColliderTrigger::None);
}

void Fried::Scene::Update(float elapsedSec)
{
	const size_t size{ m_pObjects.size() };
	for (size_t i = 0; i < size; i++)
	{
		m_pObjects[i]->Update(elapsedSec);
	}
	if (static_cast<EnemyObserver*>(m_pObservers[0])->IsNextLevelUnlocked())
	{
		m_TimeUntilNextScene += elapsedSec;
	}
}

void Fried::Scene::CollisionUpdate(float elapsedSec) noexcept
{
	m_TimeUntilNextUpdate += elapsedSec; 
	if (m_TimeUntilNextUpdate > 0.02f) // 1/50 == will run at 50 fps 
	{
		m_TimeUntilNextUpdate = 0;
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

void Fried::Scene::DeactivateNonActiveGameObjects()noexcept
{
	// can't be a range based for loop because i'm going to delete stuff here
	for (size_t i = 0; i < m_pObjects.size(); i++)
	{
		if (!m_pObjects[i]->GetIsActive())
		{
			GameObject* pCopy{ m_pObjects[i] };
			RemoveGameObject(pCopy);
			if (!pCopy->HasComponent(ComponentName::Bubble))
			{
				AddGameObjectToNonActive(pCopy);
			}
		}
	}
	
	if (static_cast<EnemyObserver*>(m_pObservers[0])->IsNextLevelUnlocked() && m_TimeUntilNextScene > 3.f)
	{
		m_TimeUntilNextScene = 0;
		NextLevel();
	}
}

void Fried::Scene::NextLevel() noexcept
{
	const size_t size{ m_pObjects.size() };
	GameObject* pCharacters[2];
	std::vector<GameObject*> pBubbles; 
	size_t bubbles{};
	size_t children{};
	for (size_t i = 0; i < size; i++)
	{
		if (m_pObjects[i]->HasComponent(ComponentName::Character))
		{
			pCharacters[children] = m_pObjects[i];
			++children;
		}
		else if (m_pObjects[i]->HasComponent(ComponentName::Bubble))
		{
			pBubbles.push_back(m_pObjects[i]);
			++bubbles;
		}
	}
	Fried::SceneManager* pSceneManager = Fried::SceneManager::GetInstance();
	Fried::Scene* pNextScene{ pSceneManager->GetNextScene() };
	for (size_t i = 0; i < children; i++)
	{
		RemoveGameObject(pCharacters[i]);
		pNextScene->AddGameObject(pCharacters[i]);
	}
	for (size_t i = 0; i < bubbles; i++)
	{
		if (pBubbles[i]->GetIsActive())
		{
			RemoveGameObject(pBubbles[i]);
		}
	}
	pSceneManager->NextScene();
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

bool Fried::Scene::Raycast(const Fried::line& line, bool raycastStaticColliders, bool raycastDynamicColiders, Fried::HitInfo& hitInfo)const noexcept
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

bool Fried::Scene::RaycastPLayer(const Fried::line& line, Fried::HitInfo& hitinfo)const noexcept
{
	const size_t size{ m_DynamicColliders.size() };
	for (size_t i = 0; i < size; i++)
	{
		Fried::HitInfo info; 
		line.intersect(m_DynamicColliders[i]->GetCollisionRect(), info);
		if (info.hit && m_DynamicColliders[i]->GetGameObject()->HasComponent(ComponentName::Character))
		{
			hitinfo.hit = true;
			hitinfo += info; 
		}
	}
	return hitinfo.hit;
}

void Fried::Scene::AddObserver(Observer* pObserver) noexcept(false)
{
	const auto it = std::find(m_pObservers.cbegin(), m_pObservers.cend(), pObserver);
	if (it == m_pObservers.cend())
	{
		m_pObservers.push_back(pObserver);
	}
}

void Fried::Scene::CheckStaticCollision(size_t index, const std::vector<CollisionLine>& lines)
{
	HitInfo info{};
	const size_t staticSize{ m_StaticColliders.size() };
	const size_t lineSize{ lines.size() };
	//loop over the static colliders and the lines so i can see if they intersect
	StateComponent *state = m_DynamicColliders[index]->GetGameObject()->GetComponent<StateComponent>(ComponentName::State);
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
						if (( m_DynamicColliders[index]->GetGameObject()->HasComponent(ComponentName::Bubble) 
							&& m_StaticColliders[j]->HasTrigger(ColliderTrigger::Ignore)))
						{
							if (!m_DynamicColliders[index]->HasTrigger(ColliderTrigger::Top))
							{
								move.y = (info.intersectPoint[h].y - lines[l].line.p2.y) + 1;
								m_DynamicColliders[index]->SetTrigger(ColliderTrigger::Top);
							}
						}
						if (m_StaticColliders[j]->HasTrigger(ColliderTrigger::Teleport))
						{
							move.y = -24 * 24;
						}
					}
					if (lines[l].collision & ColliderTrigger::Bottom)
					{
						if (velocity.y > 0)
						{
							if (!m_DynamicColliders[index]->HasTrigger(ColliderTrigger::Bottom) && 
								!m_StaticColliders[j]->HasTrigger(ColliderTrigger::Ignore) && 
								!m_StaticColliders[j]->HasTrigger(ColliderTrigger::Teleport))
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
	const bool isCurrentObjectPlayer{ pCurrentObject->HasComponent(ComponentName::Character) };
	const bool isCurrentObjectBubble{ pCurrentObject->HasComponent(ComponentName::Bubble) };
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
					const bool isLoopedObjectEnemy{ pLoopedObject->HasComponent(ComponentName::Enemy) };
					const bool isLoopedObjectBubble{ pLoopedObject->HasComponent(ComponentName::Bubble) };
					bool isLoopedObjectCharacter{ pLoopedObject->HasComponent(ComponentName::Character) };
					if (isLoopedObjectCharacter)
					{
						if (pLoopedObject->GetComponent<StateComponent>(ComponentName::State)->GetLifeState() == 
							Fried::StateManager::GetInstance()->GetLifeState("DeathState"))
						{
							continue;
						}
					}
					if (isCurrentObjectPlayer && isLoopedObjectEnemy)
					{
						// do damage to player 
						m_DynamicColliders[index]->SetTrigger(ColliderTrigger::Player);
					}
					else if (isLoopedObjectEnemy && isCurrentObjectBubble)
					{
						BubbleComponent* pBubble = pCurrentObject->GetComponent<BubbleComponent>(ComponentName::Bubble);
						if (!pBubble->IsHitByEnemy()&& !pBubble->HasReachedPos() && !m_DynamicColliders[index]->HasTrigger(ColliderTrigger::Enemy))
						{
							m_DynamicColliders[index]->SetTrigger(ColliderTrigger::Enemy);
							// capture enemy in bubble
							pBubble->SetEnemyType(pLoopedObject->GetComponent<EnemyComponent>(ComponentName::Enemy)->GetEnemyType());
							// set enemy to non active
							pLoopedObject->SetIsActive(false);
						}
					}
					else if ((isCurrentObjectBubble && isLoopedObjectCharacter))
					{
						if (!m_DynamicColliders[index]->HasTrigger(ColliderTrigger::Player)) // otherwise it ors it multiple times and than it fails
						{
							m_DynamicColliders[index]->SetTrigger(ColliderTrigger::Player);
						}
					}
					else if (pCurrentObject->HasComponent(ComponentName::Item) && isLoopedObjectCharacter)
					{
						if (!m_DynamicColliders[index]->HasTrigger(ColliderTrigger::Player)) // otherwise it ors it multiple times and than it fails
						{
							m_DynamicColliders[index]->SetTrigger(ColliderTrigger::Player);
							pCurrentObject->GetComponent<ItemComponent>(ComponentName::Item)->
								AddCharacterNumber(pLoopedObject->GetComponent<CharacterComponent>(ComponentName::Character)->GetCharacterNumber());
						}
					}
					info.hit = false;
					info.intersectPoint.clear();
				}
			}
		}
	}
}