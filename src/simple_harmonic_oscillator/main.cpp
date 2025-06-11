#include <SFML/Graphics.hpp>
#include <cmath>

void drawSpring(sf::RenderWindow& window, sf::Vector2f start, sf::Vector2f end, int coils = 10) {
    sf::VertexArray spring(sf::LineStrip);
    
    float totalLength = std::sqrt((end.x - start.x) * (end.x - start.x) + 
                                  (end.y - start.y) * (end.y - start.y));
    float coilWidth = 20.0f;
    
    // Add starting point
    spring.append(sf::Vertex(start, sf::Color::Green));
    
    // Create spring coils
    for (int i = 0; i <= coils * 4; ++i) {
        float t = static_cast<float>(i) / (coils * 4);
        sf::Vector2f point;
        
        // Linear interpolation for the main direction
        point.x = start.x + t * (end.x - start.x);
        point.y = start.y + t * (end.y - start.y);
        
        // Add perpendicular oscillation for spring effect
        float coilOffset = 0.0f;
        if (i % 4 == 1) coilOffset = coilWidth;
        else if (i % 4 == 3) coilOffset = -coilWidth;
        
        // Calculate perpendicular direction
        sf::Vector2f direction = end - start;
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length > 0) {
            direction /= length;
            sf::Vector2f perpendicular(-direction.y, direction.x);
            point += perpendicular * coilOffset;
        }
        
        spring.append(sf::Vertex(point, sf::Color::Green));
    }
    
    // Add ending point
    spring.append(sf::Vertex(end, sf::Color::Green));
    
    window.draw(spring);
}

int main() {
    // Create window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Ball and Spring");
    window.setFramerateLimit(60);

    // Create ball
    sf::CircleShape ball(15.0f);
    ball.setFillColor(sf::Color::Red);
    ball.setOrigin(15.0f, 15.0f); // Center the ball
    
    // Ball position (static)
    sf::Vector2f ballPosition(400.0f, 300.0f);
    ball.setPosition(ballPosition);

    // Fixed point for spring attachment
    sf::Vector2f fixedPoint(100.0f, 300.0f);
    sf::CircleShape fixedPointVisual(8.0f);
    fixedPointVisual.setFillColor(sf::Color::Blue);
    fixedPointVisual.setOrigin(8.0f, 8.0f);
    fixedPointVisual.setPosition(fixedPoint);

    // Font for text display (optional, will work without if font not found)
    sf::Font font;
    bool fontLoaded = font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");
    
    sf::Text infoText;
    if (fontLoaded) {
        infoText.setFont(font);
        infoText.setCharacterSize(20);
        infoText.setFillColor(sf::Color::White);
        infoText.setPosition(10.0f, 10.0f);
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear window
        window.clear(sf::Color::Black);

        // Draw spring between fixed point and ball
        drawSpring(window, fixedPoint, ballPosition, 8);

        // Draw fixed point
        window.draw(fixedPointVisual);

        // Draw ball
        window.draw(ball);

        // Display info text if font is loaded
        if (fontLoaded) {
            infoText.setString("Ball and Spring\n"
                             "Static Display");
            window.draw(infoText);
        }

        // Display everything
        window.display();
    }

    return 0;
}