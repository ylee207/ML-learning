#include <SFML/Graphics.hpp>

const int windowWidth = 800;
const int windowHeight = 600;
const int paddleWidth = 15;
const int paddleHeight = 100;
const float paddleSpeed = 400.f;
const int ballRadius = 8;
const float ballSpeed = 400.f;

int main() {
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Pong");
    window.setVerticalSyncEnabled(true);

    sf::RectangleShape leftPaddle(sf::Vector2f(paddleWidth, paddleHeight));
    leftPaddle.setFillColor(sf::Color::White);
    leftPaddle.setPosition(30, windowHeight / 2 - paddleHeight / 2);

    sf::RectangleShape rightPaddle(sf::Vector2f(paddleWidth, paddleHeight));
    rightPaddle.setFillColor(sf::Color::White);
    rightPaddle.setPosition(windowWidth - 30 - paddleWidth, windowHeight / 2 - paddleHeight / 2);

    sf::CircleShape ball(ballRadius);
    ball.setFillColor(sf::Color::White);
    ball.setOrigin(ballRadius, ballRadius);
    ball.setPosition(windowWidth / 2, windowHeight / 2);

    sf::Vector2f ballVelocity(ballSpeed, 0);

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        float deltaTime = clock.restart().asSeconds();

        // Move paddles
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && leftPaddle.getPosition().y > 0) {
            leftPaddle.move(0, -paddleSpeed * deltaTime);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && leftPaddle.getPosition().y < windowHeight - paddleHeight) {
            leftPaddle.move(0, paddleSpeed * deltaTime);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && rightPaddle.getPosition().y > 0) {
            rightPaddle.move(0, -paddleSpeed * deltaTime);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && rightPaddle.getPosition().y < windowHeight - paddleHeight) {
            rightPaddle.move(0, paddleSpeed * deltaTime);
        }

        // Move ball
        ball.move(ballVelocity * deltaTime);

        // Collision with walls
        if (ball.getPosition().y - ballRadius < 0 || ball.getPosition().y + ballRadius > windowHeight) {
            ballVelocity.y = -ballVelocity.y;
        }

        // Collision with paddles
        if (ball.getGlobalBounds().intersects(leftPaddle.getGlobalBounds()) ||
            ball.getGlobalBounds().intersects(rightPaddle.getGlobalBounds())) {
            ballVelocity.x = -ballVelocity.x;
        }

        // Ball out of bounds (reset)
        if (ball.getPosition().x - ballRadius < 0 || ball.getPosition().x + ballRadius > windowWidth) {
            ball.setPosition(windowWidth / 2, windowHeight / 2);
            ballVelocity.x = -ballVelocity.x;
        }

        window.clear();
        window.draw(leftPaddle);
        window.draw(rightPaddle);
    window.draw(ball);
    window.display();
}

return 0;
