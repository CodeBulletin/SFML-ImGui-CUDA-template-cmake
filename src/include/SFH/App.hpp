#ifndef SFH_APP_HPP
#define SFH_APP_HPP


#include <SFML/Graphics.hpp>

#include <string>
#include <cmath>

#include <SFH/Noncopyable.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

namespace sfh
{
	class App : public Noncopyable
	{
	public:
		App() = default;
		~App()
		{
			if (window.isOpen()) {
				window.close();
				ImGui::SFML::Shutdown();
			}
		}

		virtual void create_window(sf::Vector3<uint32_t> size)
		{
			// settings.antialiasingLevel = 8;
			vid = sf::VideoMode({size.x, size.y}, size.z);

			window.create(vid, name, style, state, settings);

			width = vid.size.x;
			height = vid.size.y;

			window.setVerticalSyncEnabled(true);

			if (!ImGui::SFML::Init(window)) {
				throw std::runtime_error("Failed to initialize ImGui-SFML");
			}
		}

		virtual void run()
		{
			setup();
			while (window.isOpen())
			{
				frameTime = clock.getElapsedTime().asSeconds();
				clock.restart();
				frameRate = std::round(1.0f / frameTime);
				while (window.pollEvent(event))
				{
					ImGui::SFML::ProcessEvent(window, event);
					eventManager();
				}
				loop();
				ImGui::SFML::Update(window, sf::seconds(frameTime));
				ui();
				ImGui::SFML::Render(window);
				window.display();	
			}
		}

		virtual void setup() = 0;
		virtual void loop() = 0;
		virtual void ui() = 0;

		virtual void Close()
		{
			window.close();
		}

		virtual void KeyPressedEvent() {}
		virtual void KeyReleasedEvent() {}
		virtual void MouseButtonPressedEvent() {}
		virtual void MouseButtonReleasedEvent() {}
		virtual void ClosedEvent()
		{
			Close();
		}
		virtual void LostFocusEvent() {}
		virtual void GainedFocusEvent() {}
		virtual void MouseEnteredEvent() {}
		virtual void MouseLeftEvent() {}
		virtual void MouseMovedEvent() {}
		virtual void MouseWheelScrolledEvent() {}
		virtual void TextEnteredEvent() {}

		virtual void eventManager()
		{
			switch (event.type)
			{
			case sf::Event::KeyPressed:
				KeyPressedEvent();
				break;
			case sf::Event::KeyReleased:
				KeyReleasedEvent();
				break;
			case sf::Event::MouseButtonPressed:
				MouseButtonPressedEvent();
				break;
			case sf::Event::MouseButtonReleased:
				MouseButtonReleasedEvent();
				break;
			case sf::Event::Closed:
				ClosedEvent();
				break;
			case sf::Event::LostFocus:
				LostFocusEvent();
				break;
			case sf::Event::GainedFocus:
				GainedFocusEvent();
				break;
			case sf::Event::MouseEntered:
				MouseEnteredEvent();
				break;
			case sf::Event::MouseLeft:
				MouseLeftEvent();
				break;
			case sf::Event::MouseMoved:
				MouseMovedEvent();
				break;
			case sf::Event::MouseWheelScrolled:
				MouseWheelScrolledEvent();
				break;
			case sf::Event::TextEntered:
				TextEnteredEvent();
				break;
			default:
				break;
			}
		}

	protected:
		sf::RenderWindow window;
		sf::VideoMode vid;
		sf::ContextSettings settings;
		std::string name;
		sf::Event event = sf::Event();
		sf::Clock clock;
		uint32_t style;
		sf::State state;
		int width = 0, height = 0;
		float frameTime;
		int frameRate;
	};
}

#endif // SFH_APP_HPP