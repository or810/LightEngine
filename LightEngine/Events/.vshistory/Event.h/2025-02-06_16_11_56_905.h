#pragma once

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

		// Static Events
		enum class EventType;
		enum class EventData;

		class Event : public BaseEvent{

		private:

			Event(const EventType type, const EventData data)
				: m_type(type), m_data(data) { }

			enum class EventCategory {
				KeyEvent,
				MouseEvent,
				WindowEvent
			};

			enum class EventType {
				KeyPressed,
				KeyReleased,

				MousePressed,
				MouseReleased,
				MouseDragged,

				WindowClosed,
			};

			union EventData {
				
			};

			const EventData m_data;
			const EventCategory m_category;
			const EventType m_type;
		};

		// Dynamic Events
		class CallBack : public BaseEvent {

		};
	}
}
