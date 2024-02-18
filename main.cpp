#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <cmath>
#include <cstdlib>

const double PI = 3.14159265;

struct Location
{
    int x;
    int y;
    int number;
    std::string direction;

    Location(int x, int y, int number, std::string direction)
    {
        this->x = x;
        this->y = y;
        this->number = number;
        this->direction = direction;
    }
};

std::array<Location, 20> locations =
{
    Location(28, 42,  1, "North"),
    Location(27, 46,  2, "East"),
    Location(16, 22,  3, "South"),
    Location(40, 50,  4, "West"),
    Location( 8,  6,  5, "North"),
    Location( 6, 19,  6, "East"),
    Location(28,  5,  7, "South"),
    Location(39, 36,  8, "West"),
    Location(12, 34,  9, "North"),
    Location(36, 20, 10, "East"),
    Location(22, 47, 11, "South"),
    Location(33, 19, 12, "West"),
    Location(41, 18, 13, "North"),
    Location(41, 34, 14, "East"),
    Location(14, 29, 15, "South"),
    Location( 6, 49, 16, "West"),
    Location(46, 50, 17, "North"),
    Location(17, 40, 18, "East"),
    Location(28, 26, 19, "South"),
    Location( 2, 12, 20, "West")
};

double degreesToRadians(double degrees)
{
    return degrees * (PI / 180.0);
}

double radiansToDegrees(double radians)
{
    return radians * (180.0 / PI);
}

void cartesianToPolar(double x, double y, double& radius, double& angle)
{
    radius = sqrt(x * x + y * y);
    angle = radiansToDegrees(atan2(y, x));
    if (angle < 0) angle += 360.0;
    angle = fmod(angle, 360.0);
}

void polarToCarteasian(double radius, double angle, double& x, double& y)
{
    x = radius * cos(angle);
    y = radius * sin(angle);
}

std::vector<Location> VisiblePoints(int point, int angle, int range)
{
    std::vector<Location> pointsInCone;

    for (auto& location : locations)
    {
        if (location.number == point)
        {
            double originX = static_cast<double>(location.x);
            double originY = static_cast<double>(location.y);

            double direction{ 0 };  // default is "East"

            if (location.direction == "North")
                direction = 90.0;
            else if (location.direction == "West")
                direction = 180.0;
            else if (location.direction == "South")
                direction = 270.0;

            for (auto& nextPoint : locations)
            {
                if (point != nextPoint.number)
                {
                    double x{ 0 }, y{ 0 }, rho{ 0 }, theta{ 0 };
                    x = nextPoint.x - originX;
                    y = nextPoint.y - originY;
                    cartesianToPolar(x, y, rho, theta);

                    double deviation = abs(theta - direction);

                    if (deviation > 180.0)
                    {
                        deviation = 360.0 - deviation;
                    }

                    if (rho <= range && deviation <= angle)
                    {
                        pointsInCone.push_back(nextPoint);
                    }
                }
            }

            break;
        }
    }

    return pointsInCone;
}

int main()
{
    std::cout << "\nTech. Test Solution.\n" << std::endl;

    while (true)
    {
        int point{ 0 };
        int angle{ 0 };
        int range{ 0 };

        std::cout << "\nEnter reference point [1,20]: ";
        std::cin >> point;
        if (point < 1 || point > 20)
            break;

        std::cout << "Enter degree cone angle [0, 180]: ";
        std::cin >> angle;
        if (angle < 0 || angle > 180)
            break;

        std::cout << "Enter maximum direction: ";
        std::cin >> range;
        if (range <= 0)
            break;

        std::vector<Location> points = VisiblePoints(point, angle, range);

        if (points.empty())
        {
            std::cout << "\nNo points found within specified cone ("<< point << ", " << angle << ", " << range << ")." << std::endl;
        }
        else {
            std::cout << "\nPoints found within specified cone (" << point << ", " << angle << ", " << range << "):" << std::endl;
            for (auto& point : points)
            {
                std::cout << "(" << point.x << ", " << point.y << ", " << point.number << ", " << point.direction << ")" << std::endl;
            }
        }

        std::cout << std::endl;
    }

    return 0;
}
