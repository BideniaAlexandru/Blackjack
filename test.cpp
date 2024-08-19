#include <iostream>
#include <random>
#include <unordered_map>
#include <vector>

int getRandomInt() {
    // Create a random device to seed the random number generator
    std::random_device rd;
    
    // Create a Mersenne Twister random number generator
    std::mt19937 gen(rd());
    
    // Define the range [2, 14]
    std::uniform_int_distribution<> distr(2, 14);
    
    // Generate and return the random number
    return distr(gen);
}

bool allNumbersExhausted(const std::unordered_map<int, int>& countMap, int maxGenerations, int totalNumbers) {
    if (countMap.size() < totalNumbers) {
        return false;
    }
    for (const auto& pair : countMap) {
        if (pair.second < maxGenerations) {
            return false;
        }
    }
    return true;
}

int main() {
    int playerCount;
    const int maxPlayers = 6;
    const int minPlayers = 2;

    // Prompt user for the number of players
    std::cout << "Enter the number of players (2 to 6): ";
    std::cin >> playerCount;

    // Validate the number of players
    if (playerCount < minPlayers || playerCount > maxPlayers) {
        std::cout << "Invalid number of players. Please enter a number between 2 and 6." << std::endl;
        return 1;
    }

    std::unordered_map<int, int> countMap;
    const int maxGenerations = 4;
    const int rangeStart = 2;
    const int rangeEnd = 14;
    int totalNumbers = rangeEnd - rangeStart + 1;
    const int winningScore = 21;
    std::vector<int> playerSums(playerCount, 0); // Initialize sums for each player to 0

    for (int player = 0; player < playerCount; ++player) {
        std::cout << "Player " << player + 1 << "'s turn.\n";
        while (true) {
            // Check if all numbers have been generated maxGenerations times
            if (allNumbersExhausted(countMap, maxGenerations, totalNumbers)) {
                std::cout << "No more cards\n";
                return 0;
            }

            // Get a random number
            int num = getRandomInt();

            // Check how many times this number has been generated
            if (countMap[num] < maxGenerations) {
                // Assign the number to the player and update the count
                std::cout << "Generated number: " << num << std::endl;
                playerSums[player] += num;
                std::cout << "Player " << player + 1 << "'s current sum: " << playerSums[player] << std::endl;
                countMap[num]++;
                
                // Check if the player's sum has reached or exceeded 21
                if (playerSums[player] >= winningScore) {
                    std::cout << "Player " << player + 1 << " reached or exceeded " << winningScore << " and moves to the next turn.\n";
                    break;
                }
            } else {
                // Skip this number if it has been generated maxGenerations times already
                continue;
            }

            // Ask the player if they want to continue
            std::cout << "Player " << player + 1 << ", do you want to generate another number? (y/n): ";
            char response;
            std::cin >> response;

            if (response == 'n' || response == 'N') {
                break;
            }
        }
    }

    // Display all player scores at the end
    std::cout << "\nFinal Scores:\n";
    for (int player = 0; player < playerCount; ++player) {
        std::cout << "Player " << player + 1 << ": " << playerSums[player] << std::endl;
    }

    std::cout << "All players have finished.\n";
    return 0;
}
