# SmashStone AI documentary
SmashStone is an environment for AI(Reinforcement Learning or Rule based AI etc). This documentary helps to build SmashStone project and make your own AI.
  
## Index
* How to clone SmashStone source code.
* How to build SmashStone
* How to make own AI

## 1. How to clone SmashStone source code
First of all, you should install git. And run command that followed:
```
git clone --recursive https://github.com/git-rla/SmashStone.git
```

## 2. How to build SmashStone
You can build SmashStone with CMake

### Visual Studio
1. Open project directory with Visual Studio
2. Create CMake cache
3. Build project (shortcut key: Ctrl+B)

## 3. How to make own AI
1. Create a class that implements SmashStone::Models::IPlayer
2. You should implement Ready, GetAction, and TurnEnd.
3. The method 'void Ready(void)' will be called when your AI puts a stone on the checkerboard. You can use 'Putstone(std::vector<SmashStone::Utils::Vector2D<float>>)', it returns whether it succeeded in placing the stones where you entered it. Example:
```cpp
void Ready(void)
{
    std::vector<SmashStone::Utils::Vector2D<float>> stones;
    do
    {
        stones.clear();
        stones.reserve(8);
        for (int i = 0; i < 8; ++i)
        {
            stones.emplace_back(Random::get<float>(0.0f, 42.0f),
                                Random::get<float>(0.0f, 45.0f);
        }
    } while (!PutStones(stone));
}
```
4. The method 'Action GetAction(void)' will be called when your AI has to choose an action. Example:
```cpp
Action GetAction(void)
{
    Action action;
    
    auto myList = GetMyStones();
    auto opList = GetOpStones();
    
    const int selected = Random::get<int>(0, myList.size() - 1);
    
    SmashStone::Utils::Vector2D<float> dir = (opList.at(Random::get<int>(0, opList.size() - 1)) - 
                                              myList.at(selected)).Normalized();
                                              
    const float speed = Random::get<float>(50.f, 70.f);
    
    return Action(selected. dir * speed);
}
```
5. The method 'void TurnEnd(bool isMyTurn, TurnResult result)' will be called when all stones on the checkerboard are stopped. Example:
```cpp
void TurnEnd(bool isMyTurn, SmashStone::TurnResult result)
{
    if (result == SmashStone::TurnResult::WIN)
    {
        // agent win
    }
    else if (result == SmashStone::TurnResult::DRAW)
    {
        // agent draw
    }
    else if (result == SmashStone::TurnResult::LOSE)
    {
        // agent lose
    }
}
```
6. Last, make game object with passing arguments size of checkerboard, friction acceleration, modulus of elasticity, maximum speed treated as stopped(because of the floating-point error), and maximum stones count. If you don't want to watch the game board , change useGuito false.
```cpp
Game game(45.f, 42.f, 30.f, 0.5f, 0.0001f, 100);
game.useGui = true;
game.PlayGame<YourAgent1, YourAgent2>();
```
