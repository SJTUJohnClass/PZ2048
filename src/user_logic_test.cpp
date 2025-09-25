#include "game_logic.h"
#include "user_logic.h"

#include <chrono>
#include <iostream>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <vector>


int output_pts(double avg_score) {
    int final_score = static_cast<int>(avg_score + 0.5);
    int res = 0;
    if (final_score < 1000) {
        res = 0;
    } else if (final_score < 3000) {
        res = static_cast<int>(std::ceil(final_score * final_score / 200000.0)) + 30;
    } else if (final_score < 8000) {
        res = static_cast<int>(std::ceil(12.27 * std::log2(final_score / 1000.0) + 55.55));
    } else {
        res = std::min(static_cast<int>(std::ceil(42.92 * std::sqrt(std::log2(final_score / 1000.0)) + 18.16)), 110);
    }
    return res;
}

int main() {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    auto start_time = std::chrono::steady_clock::now(); // or high resolution clock
    int total_score = 0;
    int total_steps = 0;
    int games = 10000;
    int target = 2048;
    int row_num = 4, col_num = 4;

    for (int i = 0; i < games; ++i) {
        uint seed = i + 1;
        PZ2048::ClientPrepare(row_num, col_num);
        PZ2048::Start(row_num, col_num, target, seed);

        double current_avg_score = (i > 0) ? total_score * 1.0 / i : 0;
        double current_avg_steps = (i > 0) ? total_steps * 1.0 / i : 0;
        double current_avg_time = (i > 0)
          ? (std::chrono::duration_cast<std::chrono::microseconds>(
              std::chrono::steady_clock::now() - start_time).count() * 0.001 * 0.001 / i)
          : 0;
        int progress_percent = (i * 100) / games;

        auto local_start_time = std::chrono::steady_clock::now();

        while (true) {
            std::ostringstream oss;
            auto *obuf = std::cout.rdbuf(oss.rdbuf());
            PZ2048::PrintBoard();
            std::istringstream iss(oss.str());
            std::cout.rdbuf(obuf);
            auto *ibuf = std::cin.rdbuf(iss.rdbuf());
            PZ2048::ReadBoard();
            std::cin.rdbuf(ibuf);
            char oper = PZ2048::Decide();
            if (oper != 'w' && oper != 's' && oper != 'a' && oper != 'd') {
                continue;
            }
            PZ2048::TryRun(oper);

            auto local_end_time = std::chrono::steady_clock::now();
            std::cout << "\rLoading";
            for (int j = 0; j < (i / 100) % 4 + 1; j++) std::cout << ".";
            for (int j = (i / 100) % 4 + 1; j < 4; j++) std::cout << " ";
            std::cout << " [" << std::setw(3) << progress_percent << "%]";
            std::cout << " | Game: " << std::setw(5) << i << "/" << games;
            std::cout << " | Total time: " << std::setw(5) << std::fixed << std::setprecision(2) <<
                std::chrono::duration_cast<std::chrono::microseconds>(local_end_time - start_time).count()
                * 0.001 * 0.001 << "s";
            std::cout << " | Steps: " << std::setw(4) << PZ2048::Steps();
            std::cout << " | Score: " << std::setw(4) << PZ2048::Score();
            std::cout << " | Time: " << std::setw(5) << std::fixed << std::setprecision(2) <<
                std::chrono::duration_cast<std::chrono::microseconds>(local_end_time - local_start_time).count()
                * 0.001 * 0.001 << "s";
            std::cout << " | Avg Score: " << std::setw(6) << std::fixed << std::setprecision(2) << current_avg_score;
            std::cout << " | Avg Steps: " << std::setw(6) << std::fixed << std::setprecision(2) << current_avg_steps;
            std::cout << " | Avg Time: " << std::setw(5) << std::fixed << std::setprecision(2) << current_avg_time << "s";
            std::cout.flush();

            if (PZ2048::HasReachedTarget() || PZ2048::Stuck()) {
                auto [steps, score] = PZ2048::EndGame();
                total_score += score;
                total_steps += steps;
                break;
            }
        }
    }

    std::cout << "\r" << std::string(100, ' ') << "\r";
    std::cout.flush();

    auto end_time = std::chrono::steady_clock::now();
    double avg_score = total_score * 1.0 / games;
    double avg_steps = total_steps * 1.0 / games;
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    std::cout << "Average score over " << games << " games: " << avg_score << std::endl;
    std::cout << "Average steps over " << games << " games: " << avg_steps << std::endl;
    std::cout << "Total run time: " << std::fixed << std::setprecision(2) << ms * 0.001 << "s";
    std::cout << " (" << ms / 60000 << "min " << std::fixed << std::setprecision(2) <<
        (ms % 60000) * 0.001 << "s)" << std::endl;
    std::cout << "Score by formula: " << output_pts(avg_score) << std::endl;
    std::cout.flush();
    return 0;
}

/*
void SingleTest() {
    int row_num, col_num;
    uint seed;
    int target = 2048;
    std::cin >> row_num >> col_num >> seed;

    ClientPrepare(row_num, col_num);
    Start(row_num, col_num, target, seed);
    while(true) {

        std::ostringstream oss;
        auto *obuf = std::cout.rdbuf(oss.rdbuf()); // redirect std::cout.

        PrintBoard();

        std::istringstream iss(oss.str());
        std::cout.rdbuf(obuf);                     // reset std:cout.
        auto *ibuf = std::cin.rdbuf(iss.rdbuf());  // redirect std::cin.

        ReadBoard();                               // read what PrintBoard() has output.

        std::cin.rdbuf(ibuf);                      // reset std::cin.

        char oper = Decide();
        // must be a valid move. No undo allowed. No Steins-Gate.
        if(oper != 'w' && oper != 's' && oper != 'a' && oper != 'd') {
            std::cout << " Invalid Operation.\n";
            continue;
        }

        TryRun(oper);

    if(flag) {
      std::cout << "Operation succeeded.\n";
    } else {
      std::cout << "Operation failed.\n";
    }
    std::cout << RowNum() << ' ' << ColNum() << ' ' << Steps() << ' ' << Score() << '\n';
    PrintBoard();


    if(HasReachedTarget()) {
      std::cout << "You've merged an 2048 tile!\n";
      auto [steps, score] = EndGame();
      std::cout << "Steps: " << steps << "\nScore: " << score << '\n';
      std::cout << "Final Score: " << score << std::endl;
      break;
    }
    if(Stuck()) {
      std::cout << "You've stuck.\n";
      auto [steps, score] = EndGame();
      std::cout << "Steps: " << steps << "\nScore: " << score << '\n';
      std::cout << "Final Score: " << score << std::endl;
      break;
    }
  }
}
*/
