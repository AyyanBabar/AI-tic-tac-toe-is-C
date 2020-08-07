#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;
double sw, sh, f = 1;
class X
{
    Vector2f pos;

public:
    X()
    {
        pos = {0, 0};
    }
    void set(float x, float y)
    {
        pos = {x, y};
    }
    void draw(RenderWindow &window)
    {
        sf::Vertex line1[] =
            {
                sf::Vertex(sf::Vector2f(pos.x, pos.y)),
                sf::Vertex(sf::Vector2f(pos.x + sw / 3, pos.y + sw / 3))};
        sf::Vertex line2[] =
            {
                sf::Vertex(sf::Vector2f(pos.x + sw / 3, pos.y)),
                sf::Vertex(sf::Vector2f(pos.x, pos.y + sw / 3))};
        window.draw(line1, 2, sf::Lines);
        window.draw(line2, 2, sf::Lines);
    }
};
int equal3(char a, char b, char c)
{
    return a == b && b == c && a != ' ';
}
char winner(char board[3][3])
{
    char win = ' ';
    for (int i = 0; i < 3; i++)
        if (equal3(board[i][0], board[i][1], board[i][2]))
            win = board[i][0];
    for (int i = 0; i < 3; i++)
        if (equal3(board[0][i], board[1][i], board[2][i]))
            win = board[0][i];
    if (equal3(board[0][0], board[1][1], board[2][2]))
        win = board[0][0];

    if (equal3(board[2][0], board[1][1], board[0][2]))
        win = board[2][0];

    return win;
}
int minimax(char board[][3], double depth, bool max)
{
    char win = winner(board);
    if (win == 'x')
        return 1;
    else if (win == 'o')
        return -1;
    bool c = true;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == ' ')
                c = false;
        }
    }
    if (c)
        return 0;
    if (max)
    {
        Vector2i best = {-1, -1};
        int bscore = -200000000;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[j][i] == ' ')
                {
                    board[j][i] = 'x';
                    int score = minimax(board, depth + 1, false);
                    board[j][i] = ' ';
                    if (score > bscore)
                    {
                        bscore = score;
                        best = {i, j};
                    }
                }
            }
        }
        return bscore;
    }
    else
    {
        Vector2i best = {-1, -1};
        int bscore = 200000000;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[j][i] == ' ')
                {
                    board[j][i] = 'o';
                    cout << "\n\n\n";
                    int score = minimax(board, depth + 1, true);
                    board[j][i] = ' ';
                    if (score < bscore)
                    {
                        bscore = score;
                        best = {i, j};
                    }
                }
            }
        }
        return bscore;
    }
}
void aiturn(char board[3][3])
{
    if (f < 1)
    {
        int a, b;
        while (1)
        {
            a = rand() % 3;
            b = rand() % 3;
            if (board[a][b] == ' ')
                break;
        }
        board[a][b] = 'x';
        f++;
    }
    else
    {
        Vector2i best = {-1, -1};
        int bscore = -200000000;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[j][i] == ' ')
                {
                    board[j][i] = 'x';
                    int score = minimax(board, 0, false);
                    board[j][i] = ' ';
                    if (score > bscore)
                    {
                        bscore = score;
                        best = {i, j};
                    }
                }
            }
        }
        if (bscore > -200000000)
            board[best.y][best.x] = 'x';
    }
}
int main()
{
    char board[3][3] = {{' ', ' ', ' '},
                        {' ', ' ', ' '},
                        {' ', ' ', ' '}};
    char win = ' ';
    RenderWindow window;
    ContextSettings settings;
    settings.antialiasingLevel = 8;
    window.create(VideoMode(700, 700), "SFML works!", Style::Fullscreen);
    sw = sf::VideoMode::getDesktopMode().width;
    sh = sf::VideoMode::getDesktopMode().height;
    if (sw < sh)
        sh = sw;
    else
        sw = sh;
    CircleShape hum((sw / 3) / 2 - 3, 300);
    hum.setFillColor(Color::Black);
    //hum.setOrigin(100.f, 100.f);
    hum.setOutlineColor(Color::White);
    hum.setOutlineThickness(3);
    sf::Vertex line1[] =
        {
            sf::Vertex(sf::Vector2f(sw / 3, 0)),
            sf::Vertex(sf::Vector2f(sw / 3, sh))};
    sf::Vertex line2[] =
        {
            sf::Vertex(sf::Vector2f(0, sh / 3)),
            sf::Vertex(sf::Vector2f(sw, sh / 3))};
    sf::Vertex line3[] =
        {
            sf::Vertex(sf::Vector2f((sw / 3) * 2, 0)),
            sf::Vertex(sf::Vector2f((sw / 3) * 2, sh))};
    sf::Vertex line4[] =
        {
            sf::Vertex(sf::Vector2f(0, (sh / 3) * 2)),
            sf::Vertex(sf::Vector2f(sw, (sh / 3) * 2))};
    X xmark;

    Event event;
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == Keyboard::X)
                    window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    for (int i = 0; i < 3; i++)
                    {
                        for (int j = 0; j < 3; j++)
                        {
                            if ((sw / 3) * i < event.mouseButton.x && (sw / 3) * (i + 1) > event.mouseButton.x)
                            {
                                if ((sh / 3) * j < event.mouseButton.y && (sh / 3) * (j + 1) > event.mouseButton.y)
                                {
                                    if (board[j][i] == ' ')
                                    {
                                        board[j][i] = 'o';
                                        aiturn(board);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        window.clear();
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == 'o')
                {
                    hum.setPosition((sw / 3) * j + 3, (sh / 3) * i + 3);
                    window.draw(hum);
                }
                else if (board[i][j] == 'x')
                {
                    xmark.set((sw / 3) * j, (sh / 3) * i);
                    xmark.draw(window);
                }
            }
        } /* 
        xmark.set(0, 0);
        xmark.draw(window);
        hum.setPosition(sw / 3 + 3, 0 + 3); 
        window.draw(hum);*/
        //--------------------------------------------------------------------------------------
        window.draw(line1, 2, sf::Lines);
        window.draw(line2, 2, sf::Lines);
        window.draw(line3, 2, sf::Lines);
        window.draw(line4, 2, sf::Lines);
        window.display();
        win = winner(board);
        bool c = true;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == ' ')
                    c = false;
            }
        }
        if (win != ' ')
        {
            window.close();
            cout << win << " is the winner\n";
        }
        else if (win == ' ' && c)
        {
            window.close();
            cout << "Tie\n";
        }
    }
    system("PAUSE");
    return 0;
}