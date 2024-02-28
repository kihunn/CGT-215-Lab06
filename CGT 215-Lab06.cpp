#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;
int main() {
    // Paths to the images
    string backgroundPath = "images1/backgrounds/winter.png";
    string foregroundPath = "images1/characters/yoda.png";

    // Load the background image
    Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile(backgroundPath)) {
        cerr << "Couldn't Load Background Image" << endl;
        return 1;
    }

    // Load the foreground image (Yoda with green background)
    Texture foregroundTexture;
    if (!foregroundTexture.loadFromFile(foregroundPath)) {
        cerr << "Couldn't Load Foreground Image" << endl;
        return 1;
    }

    // Create a window to display the composited image
    RenderWindow window(VideoMode(800, 600), "Composited Image");

    // Create sprites for background and foreground images
    Sprite backgroundSprite(backgroundTexture);
    Sprite foregroundSprite(foregroundTexture);

    // Loop through each pixel of the foreground (Yoda) image
    Image foregroundImage = foregroundTexture.copyToImage();
    Image backgroundImage = backgroundTexture.copyToImage();
    Vector2u imageSize = foregroundImage.getSize();
    Color greenScreen = foregroundImage.getPixel(0, 0); // Green screen color in the corner

    // Replace green screen pixels with corresponding pixels from the background image
    for (unsigned int y = 0; y < imageSize.y; y++) {
        for (unsigned int x = 0; x < imageSize.x; x++) {
            Color pixel = foregroundImage.getPixel(x, y);
            if (pixel == greenScreen) {
                // Replace green screen pixel with corresponding pixel from background
                foregroundImage.setPixel(x, y, backgroundImage.getPixel(x, y));
            }
        }
    }

    // Update the texture with the modified foreground image
    foregroundTexture.loadFromImage(foregroundImage);
    foregroundSprite.setTexture(foregroundTexture);

    // Main loop
    while (window.isOpen()) {
        // Handle events
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        // Clear the window
        window.clear();

        // Draw the background first
        window.draw(backgroundSprite);

        // Draw the modified foreground over the background
        window.draw(foregroundSprite);

        // Display the content
        window.display();
    }

    return 0;
}