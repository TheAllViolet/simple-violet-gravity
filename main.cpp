#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>



class GravitySource
{
    sf::Vector2f pos;
    float strength;
    sf::CircleShape s;


public:
    GravitySource(float pos_x, float pos_y, float strength)
    {
        pos.x = pos_x;
        pos.y = pos_y;
        this->strength = strength;

        s.setPosition(pos);
        s.setFillColor(sf::Color::White);
        s.setRadius(10);
    }

    void render(sf::RenderWindow& wind)
    {
        wind.draw(s);
    }

    sf::Vector2f get_pos()
    {
        return pos;
    }

    float get_strength()
    {
        return strength;
    }
};



class Particle
{
    sf::Vector2f pos;
    sf::Vector2f vel;
    sf::CircleShape s;


public:
    Particle(float pos_x, float pos_y, float vel_x, float vel_y)
    {
        pos.x = pos_x;
        pos.y = pos_y;

        vel.x = vel_x;
        vel.y = vel_y;

        s.setPosition(pos);
        s.setFillColor(sf::Color::White);
        s.setRadius(6);
    }

    void render(sf::RenderWindow& wind)
    {
        s.setPosition(pos);
        wind.draw(s);
    }

    void set_color(sf::Color col)
    {
        s.setFillColor(col);
    }

    void update_physics(GravitySource& s)
    {
        float distance_x = s.get_pos().x - pos.x;
        float distance_y = s.get_pos().y - pos.y;

        float distance = sqrt(distance_x * distance_x + distance_y * distance_y);

        float inverse_distance = 1.f / distance;

        float normalized_x = inverse_distance * distance_x;
        float normalized_y = inverse_distance * distance_y;

        float inverse_square_dropoff = inverse_distance * inverse_distance;

        float acceleration_x = normalized_x * s.get_strength() * inverse_square_dropoff;
        float acceleration_y = normalized_y * s.get_strength() * inverse_square_dropoff;

        vel.x += acceleration_x;
        vel.y += acceleration_y;

        pos.x += vel.x;
        pos.y += vel.y;

    }

};


sf::Color map_val_to_color(float value) // value is 0-1
{
    // Clamp value to 0-1 range
    value = value < 0.0f ? 0.0f : (value > 1.0f ? 1.0f : value);

    // Define our color points
    const sf::Color violet(148, 0, 211);   // #9400D3
    const sf::Color purple(128, 0, 128);   // #800080
    const sf::Color magenta(255, 0, 255);  // #FF00FF

    // Determine which segment we're in and interpolate
    if (value < 0.5f) {
        // Interpolate between violet and purple (0.0-0.5)
        float t = value * 2.0f;  // Convert to 0.0-1.0 range for this segment
        return sf::Color(
            static_cast<sf::Uint8>(violet.r + t * (purple.r - violet.r)),
            static_cast<sf::Uint8>(violet.g + t * (purple.g - violet.g)),
            static_cast<sf::Uint8>(violet.b + t * (purple.b - violet.b))
        );
    } else {
        // Interpolate between purple and magenta (0.5-1.0)
        float t = (value - 0.5f) * 2.0f;  // Convert to 0.0-1.0 range for this segment
        return sf::Color(
            static_cast<sf::Uint8>(purple.r + t * (magenta.r - purple.r)),
            static_cast<sf::Uint8>(purple.g + t * (magenta.g - purple.g)),
            static_cast<sf::Uint8>(purple.b + t * (magenta.b - purple.b))
        );
    }
}



int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 1000), "My Program");
    window.setFramerateLimit(60);

    std::vector<GravitySource> sources;

    sources.push_back(GravitySource(500, 500, 7000));
    sources.push_back(GravitySource(1200, 500, 7000));

    int num_particles = 10000;

    std::vector<Particle> particles;

    for (int i = 0; i < num_particles; i++)
    {
        particles.push_back(Particle(600, 700, 4, 0.2 + (0.1 / num_particles) * i));

        //change colors
        float val = (float)i / (float)num_particles;

        sf::Color col = map_val_to_color(val);


        particles[i].set_color(col);

    }




    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
        }


        window.clear();

        for (int i = 0; i < sources.size(); i++) {
            for (int j = 0; j < particles.size(); j++)
            {
                particles[j].update_physics(sources[i]);
            }
        }

        for (int i = 0; i < sources.size(); i++) {
            sources[i].render(window);
        }

        for (int j = 0; j < particles.size(); j++)
        {
            particles[j].render(window);
        }




        window.display();
    }



    return 0;
}