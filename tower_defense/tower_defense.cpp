#include <vector>
#include <iostream>
#include <windows.h>

const int widght = 15;
const int hight = 10;
int mainTowerHP = 50;

struct Point {
    int x;
    int y;
};

class Enemy {
private:
    int healthpoint = 12;
    int damage = 5;
    int x, y;
    int currentStep = 0;
    std::vector<Point> enemyRoad;
public:

    Enemy(std::vector<Point> road) {
        enemyRoad = road;

        if (!enemyRoad.empty()) {
            x = enemyRoad[0].x;
            y = enemyRoad[0].y;
        }
    }

    void Move() {
        if (currentStep < enemyRoad.size() - 1) {
            currentStep++;
            x = enemyRoad[currentStep].x;
            y = enemyRoad[currentStep].y;
        }
        else {
            x = -1;
            y = -1;
        }
    }

    int getX() {
        return x;
    }

    int getY() {
        return y;
    }

    bool isFinished() {
        return currentStep >= enemyRoad.size() - 1;
    }

    int getEnemyDamage() {
        return damage;
    }

    int getEnemyHP() {
        return healthpoint;
    }


    void TakeDamage_Enemy(int damage) {
        healthpoint -= damage;
    }

};

class Tower {
private:
    int x, y;
    int range = 2;
    int damage = 2;
public:

    Tower(int towerX, int towerY) {
        x = towerX;
        y = towerY;
    }

    bool Attack(Enemy& target) {
       
        int dist = abs(target.getX() - x) + abs(target.getY() - y);

        if (dist <= range) {
            target.TakeDamage_Enemy(damage);
            return true;
        }
        else return false;
    }

    int getX() {
        return x;
    }

    int getY() {
        return y;
    }
};

class Map {
private:
    std::vector<Point> Road;
public:

    Map() {
        for (int i = 0; i < 8; i++) {
            Road.push_back({ i,1 });
        }
        for (int i = 1; i < 8; i++) {
            Road.push_back({ 6,i });
        }
    }


    std::vector<Point> getRoad() {
        return Road;
    }

    void Draw(int enemyX, int enemyY, std::vector<Tower>& towers) {
        system("cls");
        for (int i = 0; i < hight; i++) {
            for (int j = 0; j < widght; j++) {
                if (i == enemyY && j == enemyX) {
                    std::cout << "E";
                }
                else {
                    bool isTower = false;
                    for (int k = 0; k < towers.size(); k++) {
                        if (towers[k].getX() == j && towers[k].getY() == i) {
                            isTower = true;
                            break;
                        }
                    }
                    if (isTower) {
                        std::cout << "T";
                    }
                    else {
                        bool inRoad = false;
                        for (int k = 0; k < Road.size(); k++) {
                            if (Road[k].x == j && Road[k].y == i) {
                                inRoad = true;
                                break;
                            }
                        }
                        if (inRoad) {
                            std::cout << ".";
                        }
                        else {
                            std::cout << " ";
                        }
                    }
                }
            }
            std::cout << std::endl;
        }

    }
};

int main()
{
    Map level;
    std::vector<Point> road = level.getRoad();
    std::vector<Tower> towers;
    towers.push_back({5,3});
    towers.push_back({ 7,5 });
    towers.push_back({ 3,7 });
    Enemy enemy(road);

    while (true) {
        level.Draw(enemy.getX(), enemy.getY(), towers);

        if (enemy.isFinished()) {
            mainTowerHP -= enemy.getEnemyDamage();
        }
        else {
            enemy.Move();
        }
        for (int i = 0; i < towers.size(); i++) {
            if (towers[i].Attack(enemy)) {
                std::cout << "\nEnemy get shot! Enemy HP: " << enemy.getEnemyHP() << std::endl;
            }
        }
        if (enemy.getEnemyHP() <= 0) {
            std::cout << "\nEnemy die" << std::endl;
            break;
        }

        if (mainTowerHP <= 0) {
            std::cout << "\nMain Tower is destroyed" << std::endl;
            break;
        }

        Sleep(200);
    }

}

