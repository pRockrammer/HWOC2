#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>
using namespace sf;
#define pi 3.14159265 

int factorial(int n) {
	if (n == 0)
		return 1;
	else
		return n * factorial(n - 1);
}
int main(int len, char* args[])
{
	// создаём окно
	RenderWindow app(VideoMode(800, 600, 32), "Hello World - SFML");
	int angle = 90;
	Vector2i mousepos(0, 0);
	if (len > 1)
		angle = 360 / (len - 1);
	else
		len = 5;
	std::vector<Vector2f> selected;
	int countOfAll = (factorial(len - 1)) / (2 * factorial(len-1 - 2));//число сочетаний из n по 2
	// основной цикл
	Font font;
	if (!font.loadFromFile("ArialBlack.ttf")) {
		printf("Error!");
		return -1;
	}
	Text text;
	text.setFont(font);
	while (app.isOpen())
	{
		// проверяем события (нажатие кнопки, закрытие окна и т.д.)
		Event event;
		while (app.pollEvent(event))
		{
			// если событие "закрытие окна":
			if (event.type == Event::Closed)
				// закрываем окно 
				app.close();
		}
		if (Mouse::isButtonPressed(Mouse::Left)) {
			Mouse ms;
			mousepos = ms.getPosition(app);
		}
		// очищаем экран и заливаем его белым цветом
		std::vector<Vector2f> lst;
		app.clear(Color(255, 255, 255));
		CircleShape circle(10);
		circle.setFillColor(Color(255, 0, 0));
		for (int i = 0; i < 360; i += angle) {
			circle.setPosition(150 + 100*cos(i*pi/180) + 100 -10, 150 - 100*sin(i*pi/180) + 100 - 10);
			lst.push_back(Vector2f(150 + 100 * cos(i * pi / 180) + 100 - 10, 150 - 100 * sin(i * pi / 180) + 100 - 10));
			app.draw(circle);
		}
		for (int i = 0; i < len-1; i++) {
			if (mousepos.x >= (lst.at(i).x+10 - 20) && mousepos.x <= ((lst.at(i).x+10 + 20)) && mousepos.y >= (lst.at(i).y+10 - 20) && mousepos.y <= (lst.at(i).y+10 + 20)) {
				//если ткнули в круг то..
				if (selected.size() == 0 || selected.size() > 0 && selected.at(selected.size() - 1) != lst.at(i)) {
					selected.push_back(lst.at(i));
					printf("Coords are right! %i : %i\n", mousepos.x, mousepos.y);

					if (countOfAll * 2 > selected.size())
						printf("Graph is not connected\n");
					else
						printf("Graph is connected\n");
				}
			}
		}
		
		for (int i = 0; i < selected.size(); i++) {
			if (i % 2 != 0) {
				Vertex line[] = {Vertex(Vector2f(selected.at(i).x+10, selected.at(i).y+10)), Vertex(Vector2f(selected.at(i-1).x + 10, selected.at(i-1).y + 10))};
				line[0].color = Color::Black;
				line[1].color = Color::Black;
				app.draw(line, 2, Lines);
			}
		}
		text.setString(std::to_string(mousepos.x) + ":" + std::to_string(mousepos.y));
		text.setCharacterSize(10);
		text.setFillColor(Color::Black);
		text.setPosition(Vector2f(0, 0));
		app.draw(text);
		for (int i = 1; i < len; i++) {
			text.setString(args[i]);
			text.setPosition(lst.at(i-1));
			app.draw(text);
		}
		app.display();
	}

	return 0;
}