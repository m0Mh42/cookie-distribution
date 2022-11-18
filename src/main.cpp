#include <iostream>
#include <random>
#include <vector>
#include <ctime>

uint32_t playerCount = 30;
uint32_t cycleCount = 0xFFFF;
uint32_t maxCookieCount = 100;

typedef struct
{
    uint32_t index;
    uint32_t cookies;
} Player;

std::vector<Player> InitPlayers(uint32_t player_count)
{
    std::vector<Player> players;
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_int_distribution<int> distr(1, maxCookieCount);
    int i = 0;
    while (i < player_count)
    {
        uint32_t random = distr(generator);
        Player player;
        player.index = i + 1;
        player.cookies = random;
        // std::cout << "Player " << player.index << " init with " << player.cookies << "\n";
        players.push_back(player);
        i++;
    }
    return players;
}

void CycleCookies(std::vector<Player> &players, uint32_t player_count)
{
    int i = 0;
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_int_distribution<int> distr(0, player_count - 1); // player count
    while (i < player_count)
    {
        // std::cout << "C";
        if (players.at(i).cookies < 1)
        {
            // std::cout << players.at(i).cookies;
            i++;
            continue;
        }
        int r = distr(generator);
        players.at(i).cookies -= 1;
        players.at(r).cookies += 1;
        i++;
    }
}

void ShowResults(std::vector<Player> &players, uint32_t player_count)
{
    int i = 0;
    uint64_t sum = 0;
    while (i < playerCount)
    {
        std::cout << "Player " << players.at(i).index << " has: " << players.at(i).cookies << " cookies.\n";
        sum += players.at(i).cookies;
        i++;
    }
    std::cout << "Average: " << sum / player_count << "\n";
}

int main(int argc, char **argv)
{
    std::vector<Player> players = InitPlayers(playerCount);
    uint32_t i = 0;
    while (i < cycleCount)
    {
        CycleCookies(players, playerCount);
        i++;
    }
    ShowResults(players, playerCount);
    return 0;
}