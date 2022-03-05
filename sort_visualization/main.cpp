#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <ctime>

const int width = 1200;
const int height = 800;

typedef struct Rectangle
{
	int width = 3;
	int height = 0;

	int x = 0;
	int y = 0;

	sf::Color color = sf::Color(255, 151, 231);
} Rectangle;

void setImgBackground(sf::Image &img) {
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			img.setPixel(i, j, sf::Color(255, 255, 255));
		}
	}
}
void fillVec(Rectangle rec, std::vector<Rectangle> &recVec) {
	int offset = 0;
	int cnt = 2;
	while (offset < width) {
		rec.height = rand() % height - 30;
		if (rec.height < 5) {
			rec.height = cnt;
			cnt+= 2;
		}
		rec.x = offset;
		rec.y = height - rec.height;

		offset += 5;
		recVec.push_back(rec);
	}
}
void paintVec(std::vector<Rectangle> rec, sf::Image &img) {
	for (int k = 0; k < rec.size(); k++)
	{
		for (int i = 0; i < rec[k].width; i++)
		{
			for (int j = 0; j < rec[k].height; j++)
			{
				img.setPixel(rec[k].x + i, rec[k].y + j, rec[k].color);
			}
		}
	}
}
void boobSort(std::vector<Rectangle> &rec, sf::RenderWindow &window, sf::Image &img, sf::Sprite &sprite, sf::Texture &texture) {
	Rectangle tmpRec;
	int tmpX;

	for (int i = 0; i < rec.size() - 1; i++) 
	{
		for (int j = 0, p = rec.size() - i - 1; j < rec.size() - i - 1; j++, p--) 
		{
			if (rec[j].height > rec[j + 1].height) 
			{	
				window.clear();
				// paint the bigger one j + 1
				for (int x = 0; x < rec[j].width; x++) 
				{
					for (int y = 0; y < rec[j].height; y++) 
					{
						img.setPixel(rec[j + 1].x + x, rec[j].y + y, rec[j].color);
					}
				}
				// clear the original bigger one
				for (int x = 0; x < rec[j].width; x++)
				{
					for (int y = 0; y < rec[j].height; y++)
					{
						img.setPixel(rec[j].x + x, rec[j].y + y, sf::Color(255,255,255));
					}
				}
				// draw the smaller one
				for (int x = 0; x < rec[j].width; x++)
				{
					for (int y = 0; y < rec[j + 1].height; y++)
					{
						img.setPixel(rec[j].x + x, rec[j + 1].y + y, rec[j].color);
					}
				}

				tmpX = rec[j].x;
				rec[j].x = rec[j + 1].x;
				rec[j + 1].x = tmpX;

				tmpRec = rec[j];
				rec[j] = rec[j + 1];
				rec[j + 1] = tmpRec;

				texture.loadFromImage(img);
				sprite.setTexture(texture);
				window.draw(sprite);
				window.display();
			}
		}
	}
}

int main() {
	srand(time(NULL));
	
	sf::RenderWindow window(sf::VideoMode(width, height), "Bubble Sort");
	sf::Event ev;

	sf::Image image;
	image.create(width, height);

	setImgBackground(image);

	sf::Texture texture;
	texture.loadFromImage(image);
	sf::Sprite sprite;
	sprite.setTexture(texture);

	Rectangle rec;
	std::vector<Rectangle> rectangleVec;

	fillVec(rec, rectangleVec);

	paintVec(rectangleVec, image);

	texture.loadFromImage(image);
	sprite.setTexture(texture);

	while (window.isOpen())
	{

		while (window.pollEvent(ev))
		{
			switch (ev.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			}
		}
		boobSort(rectangleVec, window, image, sprite, texture);

		window.clear();
		window.draw(sprite);
		window.display();
	}

	return 0;
}