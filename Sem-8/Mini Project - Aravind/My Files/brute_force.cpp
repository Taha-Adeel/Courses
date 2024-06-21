#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;
using ll = long long;

// Generate all graphs with n vertices and m edges (adjancency matrix)
// Check if graph is valid (no leaves or two 2-degree nodes adjacent)
// Generate all subsets of the vertices
// Check if the subset is a valid P3 2-dominating set
// Get the minimum set size and verify proposition

// O(n^2)
bool get_next_graph(vector<vector<int>> &graph) {
    int n = graph.size();
    auto get_graph_idx = [&]() {
        ll graph_idx = 0, mask = 1;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                graph_idx += graph[i][j] * mask;
                mask <<= 1;
            }
        }
        return graph_idx;
    };
    auto get_ith_graph = [&](ll graph_idx) {
        ll mask = 1;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                graph[i][j] = !!(graph_idx & mask);
                graph[j][i] = graph[i][j];
                mask <<= 1;
            }
        }
    };

    ll graph_idx = get_graph_idx();

    graph_idx++;
    if (graph_idx == (1LL << (n * (n - 1) / 2))) {
        return false;
    }

    get_ith_graph(graph_idx);
    return true;
}

// O(n^2)
bool is_valid_graph(vector<vector<int>> &graph) {
    int n = graph.size();
    vector<int> degree(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            degree[i] += graph[i][j];
        }
    }

    // Check for leaves
    for (int i = 0; i < n; i++) {
        if (degree[i] == 1) {
            return false;
        }
    }
    
    // Check for two 2-degree nodes adjacent
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (graph[i][j] && degree[i] == 2 && degree[j] == 2) {
                return false;
            }
        }
    }

    return true;
}

// O(n^3)
bool is_valid_p3_2_dominating_set(vector<vector<int>> &graph, int subset_mask) {
    int n = graph.size();
    vector<int> degree(n);
    for (int i = 0; i < n; i++) {
        if (subset_mask & (1LL << i)) {
            degree[i] = -1;
        }
        for (int j = i + 1; j < n; j++) {
            degree[i] += graph[i][j] && (subset_mask & (1LL << j));
        }
    }

    // Cycle through all P3s and check if they are 2-dominated
    for (int u1 = 0; u1 < n; u1++) {
        if (subset_mask & (1LL << u1)) {
            continue;
        }
        for (int u2 = u1 + 1; u2 < n; u2++) {
            if ((subset_mask & (1LL << u2)) || !graph[u1][u2]) {
                continue;
            }
            for (int u3 = u2 + 1; u3 < n; u3++) {
                if ((subset_mask & (1LL << u3)) || !graph[u1][u3] || !graph[u2][u3]) {
                    continue;
                }
                // u1, u2, u3 is a P3
                if (max({degree[u1], degree[u2], degree[u3]}) < 2) {
                    return false;
                }
            }
        }
    }

    return true;
}

// O(2^(n*n/2 + n/2) * n^3)
void run_brute_force(int n) {
    auto start_time = chrono::system_clock::now();

    // Cycle through all graphs ( O(2^(n*(n-1)/2)) )
    vector<vector<int>> graph(n, vector<int>(n, 0));
    ll total_graphs = (1LL << (n*(n-1)/2)), valid_graphs = 0, accepted_propositions = 0, failed_propositions = 0;
    cout << "n = " << n << ", total_graphs = " << total_graphs << endl;
    int required_min_size = (2 * n + 4) / 5;
    for(ll i = 0; i < total_graphs; i++, get_next_graph(graph)) {
        if (i % 100000 == 0 && i) {
            cout << "i = " << i << " / " << total_graphs << ", progress = " << 100.0 * i / total_graphs << "%, time left = " << (chrono::duration_cast<chrono::seconds>(chrono::system_clock::now() - start_time).count() / 3600.0) * (total_graphs - i) / i << "hrs\r" << flush;
        }
        if (!is_valid_graph(graph)) {
            continue;
        }
        valid_graphs++;

        // Cycle through all subsets ( O(2^n) * O(n^3) )
        int min_subset_size = n;
        for (int subset_mask = 0; subset_mask < (1 << n) && min_subset_size > required_min_size; subset_mask++) {
            if (__builtin_popcount(subset_mask) >= min_subset_size) {
                continue;
            }
            if (is_valid_p3_2_dominating_set(graph, subset_mask)) {
                min_subset_size = min(min_subset_size, __builtin_popcount(subset_mask));
            }
        }

        if (min_subset_size <= required_min_size) {
            accepted_propositions++;
        } else {
            failed_propositions++;
            cerr << "Failed proposition on n = " << n << ", min_subset_size = " << min_subset_size << ", required_min_size = " << required_min_size << ", adjacency_matrix =\n";
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    cerr << graph[i][j];
                }
                cerr << '\n';
            }
            cerr << '\n';
        }
    }

    auto end_time = chrono::system_clock::now();
    auto elapsed_time = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();
    cout << "\tvalid_graphs = " << valid_graphs << ", accepted_propositions = " << accepted_propositions << ", failed_propositions = " << failed_propositions << ", elapsed_time = " << elapsed_time / 1000.0 << "s\n" << endl;
}

int main() {
    // for (int n = 1; n <= 8; n++) {
    //     run_brute_force(n);
    // }
    run_brute_force(10);

    return 0;
}