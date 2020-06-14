#pragma once
#include "Minigin.h"
#include <vector>
class GameObject;

namespace Fried
{
	class FriedEngine : public Minigin
	{
	public: 
		FriedEngine() = default;
		FriedEngine(const FriedEngine& other) = delete;
		FriedEngine(FriedEngine&& other) = delete;
		FriedEngine& operator=(const FriedEngine& other) = delete;
		FriedEngine& operator=(FriedEngine&& other) = delete;
		~FriedEngine() = default;
	protected:
		virtual void LoadGame();
	private: 
		void Addstates(); 
		void AddInput(const std::vector<GameObject*>& pCharacters);
		void MakeUIScenes();
	};
}
