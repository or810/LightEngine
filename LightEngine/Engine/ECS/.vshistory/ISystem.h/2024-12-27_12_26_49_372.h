#pragma once
#include <Engine/ECS/Signature.h>
#include <functional>

namespace Light {

	/*
	* Entities array:
	* 	using EntitiesArray = std::array<Entity, MAX_ENTITIES>;
	*/
	class ISystem
	{
	protected:

		virtual ~ISystem() = default; // Polymorphic cleanup
		virtual uint32_t getId() const { return m_id; } // Example for SystemComparator

		ISystem(Signature& signature)
			: m_signature(signature), m_id(s_count++)
		{}

		virtual void update(EntitiesArray entities) const = 0;

	private:
		static uint32_t s_count;
		uint32_t m_id;
		Signature& m_signature;
	};

	
	class AnonymousSystem : public ISystem
	{
	public:
		AnonymousSystem(Signature& signature)
			: ISystem(signature)
		{}

		AnonymousSystem(Signature& signature, std::function<void(EntitiesArray)> updateFunc)
			: ISystem(signature), m_updateFunc(updateFunc)
		{
		}
	
		void update(EntitiesArray entities) const override { m_updateFunc(entities); }
		
	private:
		std::function<void(EntitiesArray)> m_updateFunc;
	};

}
