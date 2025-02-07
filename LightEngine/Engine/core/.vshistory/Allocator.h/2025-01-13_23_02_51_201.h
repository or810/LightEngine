#pragma once

#include <vector>
#include <stdexcept>
#include <cstddef>
#include <iostream>
#include <new>
#include <memory>
#include <cassert>

namespace Light {
	namespace ECS {
		class Allocator {
		public:
			Allocator(size_t chunkSize) : 
			m_chunkSize(chunkSize), 
			m_currentChunk(nullptr),
			m_currentOffset(0) {
				allocateNewChunk();
				//assert(m_chunkSize > 0 && "Chunk size must be greater than 0");
			}

			~Allocator() 
			{
				for (void* chunk : m_chunks)
					std::free(chunk);
			}

			void* allocate(size_t size, size_t alignment)
			{
				size_t alignedOffset = alignOffset(m_currentOffset, alignment);
				if (alignedOffset + size > m_chunkSize)
				{
					allocateNewChunk();
					alignedOffset = 0;
				}
				void* ptr = static_cast<char*>(m_currentChunk) + alignedOffset;
				m_currentOffset = alignedOffset + size;

				std::cout << "Allocated memory at: " << ptr << " (size: " << size << ")\n";

				return ptr;
			}

			template <typename T, typename... Args>
			T* allocateObject(Args&&... args) {
				void* memory = allocate(sizeof(T), alignof(T));
				return new (memory) T(std::forward<Args>(args)...);
			}

		private:
			size_t m_chunkSize;
			void* m_currentChunk;
			size_t m_currentOffset;
			std::vector<void*> m_chunks;

		private:
			void allocateNewChunk() {
				m_currentChunk = std::malloc(m_chunkSize);
				if (!m_currentChunk)
					throw std::bad_alloc();
				m_chunks.push_back(m_currentChunk);
				m_currentOffset = 0;
			}

			static size_t alignOffset(size_t offset, size_t alignment)
			{
				return (offset + alignment - 1) & ~(alignment - 1);
			}
		};
	}
}