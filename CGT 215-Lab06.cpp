#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;
int main() {
    string backgroundPath = "images1/backgrounds/winter.png";
    string foregroundPath = "images1/characters/yoda.png";


    Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile(backgroundPath)) {
        cerr << "Couldn't Load Background Image" << endl;
        return 1;
    }

    Texture foregroundTexture;
    if (!foregroundTexture.loadFromFile(foregroundPath)) {
        cerr << "Couldn't Load Foreground Image" << endl;
        return 1;
    }

    Sprite backgroundSprite(backgroundTexture);
    Sprite foregroundSprite(foregroundTexture);


    Image foregroundImage = foregroundTexture.copyToImage();
    Image backgroundImage = backgroundTexture.copyToImage();
    Vector2u imageSize = foregroundImage.getSize();
    Color greenScreen = foregroundImage.getPixel(0, 0);

    for (unsigned int y = 0; y < imageSize.y; y++) {
        for (unsigned int x = 0; x < imageSize.x; x++) {
            Color pixel = foregroundImage.getPixel(x, y);
            if (pixel == greenScreen) {
                foregroundImage.setPixel(x, y, backgroundImage.getPixel(x, y));
            }
        }
    }

    foregroundTexture.loadFromImage(foregroundImage);
    foregroundSprite.setTexture(foregroundTexture);

    RenderWindow window(VideoMode(800, 600), "Composited Image");
    window.clear();
    window.draw(foregroundSprite);
    window.display();
    while (true);

}