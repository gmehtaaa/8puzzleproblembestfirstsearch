#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <string>
using namespace std;

struct Node {
    vector<vector<int>> state;
    vector<vector<vector<int>>> path;
    int heuristic; // h(n) = misplaced tiles count
};

bool is_goal(const vector<vector<int>>& state) {
    vector<vector<int>> goal = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
    return state == goal;
}

int misplaced_tiles(const vector<vector<int>>& state) {
    vector<vector<int>> goal = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
    int count = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (state[i][j] != 0 && state[i][j] != goal[i][j])
                count++;
    return count;
}

pair<int, int> find_blank(const vector<vector<int>>& state) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (state[i][j] == 0)
                return make_pair(i, j);
    return make_pair(-1, -1);
}

vector<vector<vector<int>>> generate_moves(vector<vector<int>> state) {
    vector<vector<vector<int>>> moves;
    pair<int, int> blank_pos = find_blank(state);
    int x = blank_pos.first;
    int y = blank_pos.second;

    // Move up
    if (x > 0) {
        swap(state[x][y], state[x-1][y]);
        moves.push_back(state);
        swap(state[x][y], state[x-1][y]);
    }
    // Move down
    if (x < 2) {
        swap(state[x][y], state[x+1][y]);
        moves.push_back(state);
        swap(state[x][y], state[x+1][y]);
    }
    // Move left
    if (y > 0) {
        swap(state[x][y], state[x][y-1]);
        moves.push_back(state);
        swap(state[x][y], state[x][y-1]);
    }
    // Move right
    if (y < 2) {
        swap(state[x][y], state[x][y+1]);
        moves.push_back(state);
        swap(state[x][y], state[x][y+1]);
    }

    return moves;
}

void best_first_search(vector<vector<int>> start) {
    struct Compare {
        bool operator()(Node a, Node b) {
            return a.heuristic > b.heuristic; // Min-heap by h(n)
        }
    };

    priority_queue<Node, vector<Node>, Compare> pq;
    set<string> visited;

    pq.push({start, {}, misplaced_tiles(start)});

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        // Create unique key for visited set
        string key;
        for (int i = 0; i < current.state.size(); i++)
            for (int j = 0; j < current.state[i].size(); j++)
                key += to_string(current.state[i][j]);

        if (visited.count(key))
            continue;
        visited.insert(key);

        // Append current state to path
        vector<vector<vector<int>>> path = current.path;
        path.push_back(current.state);

        // Goal check
        if (is_goal(current.state)) {
            cout << "\n--- Solution Found (Best First Search - Misplaced Tiles) ---\n";
            for (int s = 0; s < path.size(); s++) {
                for (int i = 0; i < path[s].size(); i++) {
                    for (int j = 0; j < path[s][i].size(); j++)
                        cout << path[s][i][j] << " ";
                    cout << "\n";
                }
                cout << "---\n";
            }
            return;
        }

        // Generate next moves
        vector<vector<vector<int>>> moves = generate_moves(current.state);
        for (int m = 0; m < moves.size(); m++) {
            string mkey;
            for (int i = 0; i < moves[m].size(); i++)
                for (int j = 0; j < moves[m][i].size(); j++)
                    mkey += to_string(moves[m][i][j]);

            if (!visited.count(mkey))
                pq.push({moves[m], path, misplaced_tiles(moves[m])});
        }
    }

    cout << "No solution found.\n";
}

int main() {
    vector<vector<int>> start(3, vector<int>(3));
    cout << "Enter puzzle (0 for blank):\n";
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            cin >> start[i][j];

    best_first_search(start);
}
