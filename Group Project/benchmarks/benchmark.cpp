#define main smart_change_original_main
#include "../src/main.cpp"
#undef main

int main() {
    ofstream output("benchmarks.csv");

    if (!output.is_open()) {
        cerr << "Error creating benchmarks.csv\n";
        return 1;
    }

    output << "amount,trial,greedy_us,dp_us,"
           << "greedy_ops,dp_ops,greedy_coins,dp_coins\n";

    vector<int> coins = {1, 10, 25};
    vector<int> amounts = {100, 500, 1000, 2500, 5000, 10000};

    cout << "SMART CHANGE CALCULATOR - BENCHMARK\n";
    cout << "Running performance tests...\n\n";

    for (int amount : amounts) {
        double greedyTotal = 0;
        double dpTotal = 0;

        for (int trial = 1; trial <= 30; trial++) {
            Result g = greedy(amount, coins);
            Result d = dynamicProgramming(amount, coins);

            greedyTotal += g.microseconds;
            dpTotal += d.microseconds;

            output << amount << ","
                   << trial << ","
                   << g.microseconds << ","
                   << d.microseconds << ","
                   << g.operations << ","
                   << d.operations << ","
                   << g.coins.size() << ","
                   << d.coins.size() << "\n";
        }

        cout << "Amount: " << amount << " cents\n";
        cout << "Average Greedy Time: "
             << greedyTotal / 30 << " us\n";
        cout << "Average DP Time: "
             << dpTotal / 30 << " us\n\n";
    }

    output.close();

    cout << "Benchmark completed successfully!\n";
    cout << "Results saved to benchmarks.csv\n";

    return 0;
}
