#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <ctime>
#include <random>
#include <unordered_map>

using namespace std;

struct Territory : sf::Sprite {

    string territoryName;
    string owner;
    vector<string> neighbors;
    int soldiers;
    bool isSelected;
    sf::Text soldierText;

    //Default constructor
    Territory();

    //Parameterized constructor
    Territory(string territoryName, string owner, vector<string> neighbors, int soldiers);


    // Override the draw function to draw both the sprite and text

};

Territory::Territory() {
    // Initialize default values or leave them uninitialized based on your requirements
    this->territoryName = "DefaultTerritory";
    this->owner = "DefaultOwner";
    this->soldiers = 0;
    this->neighbors = {};
    this->isSelected = false;

}

Territory::Territory( string territoryName, string owner, vector<string> neighbors, int soldiers) {
    this->owner = owner;
    this->neighbors = neighbors;
    this->soldiers = soldiers;
    this->territoryName = territoryName;
    this->isSelected = false;
}

class Player{
public:
    string color;
    int numCards;
    int numTerritories;

private:

};


class Board {
public:
    int tSelected = 0;
    Territory* attacker;
    Territory* defender;
    Player currentPlayer;

    //Add Territory after it has been initialized
    void addTerritory(const string& name, Territory* territory) {
        // Check if the territory already exists
        if (TerritoryMap.find(name) != TerritoryMap.end()) {
            cout << "Territory with name " << name << " already exists. Cannot add duplicate territories.\n";
        } else {
            TerritoryMap[name] = territory;
        }
    }

    //return vectors of territories
    vector<Territory*> territoriesVect(){
        vector<Territory*> valuesVector;

        for (const auto& pair : TerritoryMap) {
            valuesVector.push_back(pair.second);
        }
        return  valuesVector;
    }

    //begin phase

    //fortify phase

    //attack phase
private:

    unordered_map<string, Territory*> TerritoryMap;

};


//function for centering text
void setText(sf::Text &text, float x, float y){
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f,textRect.top + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x, y));
}

//function for centering position of shapes by returning correct coordinate
//when using standard sf library shapes the set position function puts it to the top left
float centerX(float xcord, float widthShape){
    xcord = xcord - (widthShape/2);
    return xcord;
}

float centerY(float ycord, float heightShape){
    ycord = ycord - (heightShape/2);
    return ycord;
}


int generateRandomNumber() {
    // Use a random device to seed the generator
    random_device rd;

    // Use the Mersenne Twister engine
    mt19937 gen(rd());

    // Define the range for the uniform distribution (1 to 6)
    uniform_int_distribution<int> distribution(1, 6);

    // Generate a random number
    return distribution(gen);
}





int main() {

    //for testing
    sf::CircleShape originDot(5); // Create a small circle shape for the dot
    originDot.setFillColor(sf::Color::Red);
    //

    //Create board
    auto* gameBoard = new Board;

    //Load textures
    sf::Texture phillipines;
    phillipines.loadFromFile(R"(C:\Users\1vinc\CLionProjects\Risk\files\phillipines.png)");

    sf::Texture usatexture;
    usatexture.loadFromFile(R"(C:\Users\1vinc\CLionProjects\Risk\files\USA.png)");

    //Later this should be extracted from a CSV file instead of being manual
    //Load Territories
    auto* PH = new Territory;
    PH->territoryName = "Phillipines";
    PH->setTexture(phillipines);
    PH->setScale(0.3, 0.3);
    //Set the correct origin (maybe create a function later for this)
    sf::FloatRect bounds = PH->getLocalBounds();
    PH->setOrigin(bounds.width / 2, bounds.height / 2);
    PH->setPosition(200, 500);
    PH->soldiers = 3;

    auto* USA = new Territory;
    USA->territoryName = "USA";
    USA->setTexture(usatexture);
    USA->setScale(0.1,0.1);
    sf::FloatRect bounds2 = USA->getLocalBounds();
    USA->setOrigin(bounds2.width / 2, bounds2.height / 2);
    USA->setPosition(800, 500);
    USA->soldiers = 3;

    auto* USA2 = new Territory;
    USA2->territoryName = "USA2";
    USA2->setTexture(usatexture);
    USA2->setScale(0.1,0.1);
    sf::FloatRect bounds3 = USA2->getLocalBounds();
    USA2->setOrigin(bounds3.width / 2, bounds3.height / 2);
    USA2->setPosition(1300, 500);
    USA2->soldiers = 6;

    //Put territories into the map
    gameBoard->addTerritory(PH->territoryName, PH);
    gameBoard->addTerritory(USA->territoryName, USA);
    gameBoard->addTerritory(USA2->territoryName, USA2);


    //booleans for window states
    bool gWindow = false;

    //This is how to you take a big png and set the shown image to be a portion of it
    //Digits1->setTextureRect(sf::IntRect(0,0,21,32));

    //start button
    sf::CircleShape attackButton;
    attackButton.setRadius(50.0f);
    attackButton.setPosition(300,1000);
    attackButton.setFillColor(sf::Color::Green);



    //Load font
    sf::Font font;
    font.loadFromFile("files/font.ttf");

    sf::Text welcomeText;
    welcomeText.setString("Welcome to Risk!");
    welcomeText.setCharacterSize(60);
    welcomeText.setFillColor(sf::Color::Black);
    welcomeText.setFont(font);
    welcomeText.setStyle(sf::Text::Bold | sf::Text::Underlined);
    setText(welcomeText,960, 400);

    //Button for Start
    float width = 200.f;
    float height = 100.f;
    sf::RectangleShape startButton(sf::Vector2f(width, height));
    startButton.setFillColor(sf::Color::Green);
    startButton.setPosition(centerX(960, width), centerY(600,height));
    //text
    sf::Text yesText;
    sf::Vector2f positionY = startButton.getPosition();
    yesText.setString("Play");
    yesText.setCharacterSize(30);
    yesText.setFillColor(sf::Color::Black);
    yesText.setFont(font);
    yesText.setStyle(sf::Text::Bold);
    setText(yesText,positionY.x + 100, positionY.y + 50);


    // Create the SFML window
    sf::RenderWindow welcomeWindow(sf::VideoMode(1920, 1280), "Game Menu" ,sf::Style::Close);
    welcomeWindow.setFramerateLimit(30);


    // Game window is opened to display
    while(welcomeWindow.isOpen()){
        sf::Event event;

        while (welcomeWindow.pollEvent(event))
        {
            //mouse
            sf::Vector2f mouse = welcomeWindow.mapPixelToCoords(sf::Mouse::getPosition(welcomeWindow));
            //If pressed then create the game window and then break

            if((sf::Mouse::isButtonPressed(sf::Mouse::Left))){
                sf::FloatRect boundsStart = startButton.getGlobalBounds();

                if(boundsStart.contains(mouse)){
                    welcomeWindow.close();
                    gWindow = true;
                }



            }

            //Press the attack button



            if (event.type == sf::Event::Closed){
                welcomeWindow.close();
            }

        }

        welcomeWindow.clear(sf::Color::Blue);
        welcomeWindow.draw(welcomeText);
        welcomeWindow.draw(startButton);
        welcomeWindow.draw(yesText);
        welcomeWindow.display();

    }



    //GameWindow
    if(gWindow){
        sf::RenderWindow gameWindow(sf::VideoMode(1920, 1280), "Game Menu" ,sf::Style::Close);
        gameWindow.setFramerateLimit(30);

        Territory tempSprite1;
        Territory tempSprite2;

        vector<Territory*> tempVector = gameBoard->territoriesVect();

        while(gameWindow.isOpen()){
            sf::Vector2f mouse = gameWindow.mapPixelToCoords(sf::Mouse::getPosition(gameWindow));


            bool highlighted = false;
            bool select = false;
            sf::Event event;

            int numDice1 = 0;
            int numDice2 = 0;
            int numWins = 0;
            int numLosses = 0;
            int randomAttacker = 0;
            int randomDefender = 0;


            while (gameWindow.pollEvent(event))
            {

                sf::FloatRect boundsAttack = attackButton.getGlobalBounds();

                if (sf::Mouse::isButtonPressed(sf::Mouse::Left) and gameBoard->tSelected == 2) {
                    if(boundsAttack.contains(mouse)){
                        //do math of calculations here
                        //assign amount of dice

                        //How it works
                        //First need to find out how to scale the number of dice when greater than 3
                        //Then you roll dice. Each dice faces off each other individually not in total
                        //if they are equal the defending territory wins if the attacking has higher number it wins
                        //the number of wins for one territory equals the number of troops that is subtracted from the
                        //defender

                        if(gameBoard->defender->soldiers <= 3 and gameBoard->attacker->soldiers <= 3){
                            numDice1 = gameBoard->attacker->soldiers;
                            numDice2 = gameBoard->defender->soldiers;
                            for(int i = 0; i < min(numDice1, numDice2); i++){
                                randomAttacker = generateRandomNumber();
                                randomDefender = generateRandomNumber();
                                if(randomAttacker > randomDefender){
                                    numWins += 1;
                                } else if (randomAttacker <= randomDefender){
                                    numLosses += 1;
                                }
                            }
                            if(numDice1 < numDice2){
                                
                            }

                        } else{

                        }
                        gameBoard->defender->soldiers -= 1;
                    }
                }

                //Selecting a territory
                //only allowed for certain amount of territories 2 for attack and defend
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left) and gameBoard->tSelected < 3) {
                    cout << gameBoard->tSelected;

                    for(auto i : tempVector){
                        sf::FloatRect bounds = i->getGlobalBounds();

                        if (bounds.contains(mouse)) {
                            //deselecting a territory
                            if(i->isSelected){
                                gameBoard->tSelected -= 1;
                                i->isSelected = !i->isSelected;


                            }
                            //selecting a territory
                            else if(gameBoard->tSelected <= 1){
                                gameBoard->tSelected += 1;
                                i->isSelected = !i->isSelected;
                                //assigning attacker and defender
                                if(gameBoard->tSelected == 1){
                                    gameBoard->attacker = i;
                                }
                                if(gameBoard->tSelected == 2){
                                    gameBoard->defender = i;
                                }
                            }
                        }
                    }
                }



                //closing the game
                if (event.type == sf::Event::Closed){
                    gameWindow.close();
                }

            }



            gameWindow.clear(sf::Color::Blue);

            //Maybe later combine the two for loops

            //Drawing all territories
            for (auto i : tempVector) {
                if (i->isSelected) {
                    i->setColor(sf::Color::Green);
                } else {
                    i->setColor(sf::Color::White);
                }
                gameWindow.draw(*i);


                //testing
                originDot.setPosition(i->getPosition());
                gameWindow.draw(originDot);
                //

            }

            //code for checking to outline
            for(auto i : tempVector){
                sf::FloatRect bounds = i->getGlobalBounds();

                if(bounds.contains(mouse) and !i->isSelected){
                    tempSprite2 = *i;
                    tempSprite2.setColor(sf::Color::Cyan);
                    tempSprite2.setPosition(i->getPosition());
                    highlighted = true;
                }
            }

            //highlighting if selected
            if(highlighted && !select){
                gameWindow.draw(tempSprite2);
            }

            //drawing the numbers
            for(auto i: tempVector){
                sf::Text temp;
                temp.setString(to_string(i->soldiers));
                temp.setCharacterSize(60);
                temp.setFillColor(sf::Color::Black);
                temp.setFont(font);
                temp.setStyle(sf::Text::Bold);
                temp.setPosition(i->getPosition());
                gameWindow.draw(temp);

            }

            //draw attacking UI
            if(gameBoard->tSelected == 1){
                sf::Text temp;
                temp.setString(gameBoard->attacker->territoryName + " Attack: Choose");
                temp.setCharacterSize(60);
                temp.setFillColor(sf::Color::Black);
                temp.setFont(font);
                temp.setStyle(sf::Text::Bold);
                temp.setPosition(400,1000);
                gameWindow.draw(temp);

            } else if(gameBoard->tSelected == 2){
                sf::Text temp;
                temp.setString(gameBoard->attacker->territoryName + " Attack: " + gameBoard->defender->territoryName);
                temp.setCharacterSize(60);
                temp.setFillColor(sf::Color::Black);
                temp.setFont(font);
                temp.setStyle(sf::Text::Bold);
                temp.setPosition(400,1000);
                gameWindow.draw(temp);
            }

            //attacking another player
            if(gameBoard->tSelected == 2){
                gameWindow.draw(attackButton);
            }

            gameWindow.display();
        }
    }


    delete gameBoard;
    return 0;
}



