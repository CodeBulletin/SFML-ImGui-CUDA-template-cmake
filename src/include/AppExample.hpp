#include <SFH/App.hpp>
#include <SFH/color.hpp>

class AppExample : public sfh::App
{
    float i = 0.0f;
public:
    AppExample(std::string name, uint32_t width, uint32_t height, uint32_t style = sf::Style::Close | sf::Style::Titlebar, sf::State state = sf::State::Windowed)
    {
        
        this->name = name;
        this->style = style;
        this->state = state;

        create_window({ width, height, 32 });
    }

    void setup() override
    {
    }

    void loop() override
    {
        auto color = sfh::color::HSL_to_RGB({ i * 360.0f , 1.0, 0.5 });
        window.clear(color);
        i += 1.0f/2.0f * frameTime;
        if (i > 1.0f)
            i = 0.0f;
    }

    void ui() override
    {
        ImGui::ShowDemoWindow();
    }
};