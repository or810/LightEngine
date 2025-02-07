#pragma once

#include "Input.h"
#include <variant>

namespace Light {

	namespace Events {


		class BaseEvent {
		public:

			virtual ~BaseEvent() = default;

		
		private:
			// To ensure only 'CallBack', and 'Event' can inherit this class
			BaseEvent() = default;

			friend class Event;
			friend class CallBack;
		};

		// ---------Static Events----------
			enum class EventCategory {
				KeyEvent,
				MouseEvent,
				WindowEvent
			};

			enum class EventType {
				KeyPressed,
				KeyReleased,
				KeyTyped,

				MousePressed,
				MouseReleased,
				MouseMoved,
				MouseDragged,
				MouseScrolled,

				WindowClosed,
				WindowMoved,
				WindowFocus,
				WindowLostFocus,
				WindowResize
			};

			struct MousePosition {
				int x, y; // Mouse position
			};

			struct MouseScroll {
				float xOffset, yOffset; // Scroll deltas
			};

			struct WindowSize {
				int width, height; // Window size
			};

		enum class EventType;
		using EventData = std::variant<Key, Button, MousePosition, MouseScroll, WindowSize>;


		class Event : public BaseEvent{

		private:

			Event(EventType type, EventData data)
				: m_type(type), m_data(data), m_category(determineCategory(m_type)) { }

			const EventData m_data;
			const EventCategory m_category;
			const EventType m_type;

		private:
			EventCategory determineCategory(EventType type) {
				switch (type) {
				case EventType::KeyPressed:
				case EventType::KeyReleased:
				case EventType::KeyTyped:
					return EventCategory::KeyEvent;
				case EventType::MousePressed:
				case EventType::MouseReleased:
				case EventType::MouseMoved:
				case EventType::MouseDragged:
				case EventType::MouseScrolled:
					return EventCategory::MouseEvent;
				case EventType::WindowClosed:
				case EventType::WindowMoved:
				case EventType::WindowFocus:
				case EventType::WindowLostFocus:
				case EventType::WindowResize:
					return EventCategory::WindowEvent;
				default:
					throw std::invalid_argument("Unknown EventType");
				}
			}
		};

		// Dynamic Events
		class Alert : public BaseEvent {
			
		};
	}
}
