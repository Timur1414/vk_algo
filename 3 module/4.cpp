#include <vector>
#include <map>
#include <queue>
#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_map>


const int game_side_size = 4;
const int game_field_size = game_side_size * game_side_size;
const std::vector<int> finish_field = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0};
// const std::vector<int> finish_field = {1, 2, 3, 4, 5, 6, 7, 8, 0};


class GameState {
private:
    std::vector<int> field;
    int zero_position;
public:
    GameState() {
        zero_position = -1;
    }
    GameState(const std::vector<int>& field) {
        this->field = field;
        zero_position = -1;
        for (int i = 0; i < field.size(); i++)
            if (field[i] == 0)
                zero_position = i;
    }

    bool can_move_left() const {
        return zero_position % game_side_size > 0;
    }
    bool can_move_right() const {
        return zero_position % game_side_size < game_side_size - 1;
    }
    bool can_move_up() const {
        return zero_position >= game_side_size;
    }
    bool can_move_down() const {
        return zero_position < game_field_size - game_side_size;
    }
    GameState move_left() const {
        GameState new_state(*this);
        std::swap(new_state.field[zero_position], new_state.field[zero_position - 1]);
        new_state.zero_position--;
        return new_state;
    }
    GameState move_right() const {
        GameState new_state(*this);
        std::swap(new_state.field[zero_position], new_state.field[zero_position + 1]);
        new_state.zero_position++;
        return new_state;
    }
    GameState move_up() const {
        GameState new_state(*this);
        std::swap(new_state.field[zero_position], new_state.field[zero_position - game_side_size]);
        new_state.zero_position -= game_side_size;
        return new_state;
    }
    GameState move_down() const {
        GameState new_state(*this);
        std::swap(new_state.field[zero_position], new_state.field[zero_position + game_side_size]);
        new_state.zero_position += game_side_size;
        return new_state;
    }
    bool is_finish() const {
        return field == finish_field;
    }

    bool operator==(const GameState& oth) const {
        return field == oth.field;
    }
    std::vector<int> get_field() const {
        return field;
    }
};

class Hasher {
private:
    int p = 137;
public:
    size_t operator()(const GameState& state) const {
        const auto& field = state.get_field();
        size_t hash = 0;
        for (int i : field)
            hash = hash * p + i;
        return hash;
    }
};


std::string get_solution(const GameState& start_state) {
    std::queue<GameState> queue;
    queue.push(start_state);
    std::unordered_map<GameState, char, Hasher> visited;
    visited[start_state] = 'S';
    while (!queue.empty()) {
        GameState current_state = queue.front();
        queue.pop();
        if (current_state.can_move_left()) {
            GameState next_state = current_state.move_left();
            if (visited.find(next_state) == visited.end()) {
                queue.push(next_state);
                visited[next_state] = 'L';
            }
        }
        if (current_state.can_move_right()) {
            GameState next_state = current_state.move_right();
            if (visited.find(next_state) == visited.end()) {
                queue.push(next_state);
                visited[next_state] = 'R';
            }
        }
        if (current_state.can_move_up()) {
            GameState next_state = current_state.move_up();
            if (visited.find(next_state) == visited.end()) {
                queue.push(next_state);
                visited[next_state] = 'U';
            }
        }
        if (current_state.can_move_down()) {
            GameState next_state = current_state.move_down();
            if (visited.find(next_state) == visited.end()) {
                queue.push(next_state);
                visited[next_state] = 'D';
            }
        }
    }
    std::string result;
    GameState current_state(finish_field);
    char move = visited[current_state];
    while (move != 'S') {
        result += move;
        switch (move) {
            case 'L':
                current_state = current_state.move_right();
                break;
            case 'R':
                current_state = current_state.move_left();
                break;
            case 'U':
                current_state = current_state.move_down();
                break;
            case 'D':
                current_state = current_state.move_up();
                break;
        }
        move = visited[current_state];
    }
    std::reverse(result.begin(), result.end());
    return result;
}


int main() {
    std::vector<int> arr(game_field_size);
    for (int i = 0; i < game_field_size; i++)
        std::cin >> arr[i];
    GameState start_state(arr);
    std::cout << get_solution(start_state);

    return 0;
}