#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    int N;
    std::cin >> N;

    std::vector<int> buildings(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> buildings[i];
    }

    std::vector<std::vector<double>> gradients(N, std::vector<double>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            gradients[i][j] = gradients[j][i] =
                double(buildings[i] - buildings[j]) / (i - j);
        }
    }

    std::vector<int> cnt_watchable_buildings(N);
    for (int i = 0; i < N; ++i) {
        double threshold_gradient = INT_MAX;
        for (int j = i - 1; j >= 0; --j) {
            if (gradients[i][j] < threshold_gradient) {
                threshold_gradient = gradients[i][j];
                cnt_watchable_buildings[i]++;
            }
        }

        threshold_gradient = INT_MIN;
        for (int j = i + 1; j < buildings.size(); ++j) {
            if (gradients[i][j] > threshold_gradient) {
                threshold_gradient = gradients[i][j];
                cnt_watchable_buildings[i]++;
            }
        }
    }

    std::cout << *std::max_element(cnt_watchable_buildings.begin(),
                                   cnt_watchable_buildings.end());

    return 0;
}
