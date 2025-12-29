#include <algorithm>
#include <iostream>
#include <array>
#include <vector>
#include <map>
#include <cmath>
#include <set>
#include <climits>

const int LINE_SIZE = 4;
const int FIELD_SIZE = LINE_SIZE * LINE_SIZE;
const std::vector<int> FINISH_FIELD = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0};
// const std::vector<int> FINISH_FIELD = {1, 2, 3, 4, 5, 6, 7, 8, 0};


class GameState {
private:
    std::vector<int> field;
    int zero_position;
public:
    GameState() : zero_position(-1) {}
    GameState(const GameState& st) : field(st.field), zero_position(st.zero_position) {}
    GameState(const std::vector<int>& arr) {
        this->field = arr;
        zero_position = -1;
        for (int i = 0; i < field.size(); i++)
            if (field[i] == 0)
                zero_position = i;
    }

    bool can_move_left() const {
        return zero_position % LINE_SIZE > 0;
    }
    bool can_move_right() const {
        return zero_position % LINE_SIZE < LINE_SIZE - 1;
    }
    bool can_move_up() const {
        return zero_position >= LINE_SIZE;
    }
    bool can_move_down() const {
        return zero_position < FIELD_SIZE - LINE_SIZE;
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
        std::swap(new_state.field[zero_position], new_state.field[zero_position - LINE_SIZE]);
        new_state.zero_position -= LINE_SIZE;
        return new_state;
    }
    GameState move_down() const {
        GameState new_state(*this);
        std::swap(new_state.field[zero_position], new_state.field[zero_position + LINE_SIZE]);
        new_state.zero_position += LINE_SIZE;
        return new_state;
    }
    bool is_finish() const {
        return field == FINISH_FIELD;
    }

    int distance() const {
        int res = 0;
        for (int i = 0; i < FIELD_SIZE; i++) {
            int state_x = i % LINE_SIZE;
            int state_y = std::floor(i / LINE_SIZE);
            int target_x, terget_y;
            if (field[i] == 0) {
                target_x = LINE_SIZE - 1;
                terget_y = LINE_SIZE - 1;
            }
            else {
                target_x = (field[i] - 1) % LINE_SIZE;
                terget_y = std::floor((field[i] - 1) / LINE_SIZE);
            }
            res += abs(state_x - target_x) + abs(state_y - terget_y);
        }
        return res;
    }

    std::vector<std::pair<GameState, char>> get_moves() const {
        std::vector<std::pair<GameState, char>> result;
        if (can_move_up()) {
            GameState new_state = move_up();
            result.push_back(std::make_pair(new_state, 'D'));
        }
        if (can_move_down()) {
            GameState new_state = move_down();
            result.push_back(std::make_pair(new_state, 'U'));
        }
        if (can_move_left()) {
            GameState new_state = move_left();
            result.push_back(std::make_pair(new_state, 'R'));
        }
        if (can_move_right()) {
            GameState new_state = move_right();
            result.push_back(std::make_pair(new_state, 'L'));
        }
        return result;
    }

    bool operator==(const GameState& r) const {
        return field == r.field;
    }

    bool operator<(const GameState& r) const {
        return field < r.field;
    }
};

void A_star(const GameState& start, const GameState& end) {
    std::map<GameState, int> distance;
    std::map<GameState, std::pair<GameState, char>> previous;
    distance[start] = 0;
    std::set<std::pair<int, GameState>> set;
    set.insert(std::make_pair(0, start));
    while (!set.empty()) {
        std::pair<int, GameState> current = *set.begin();
        set.erase(set.begin());
        if (current.second == end) {
            set.clear();
            break;
        }
        for (const auto& item : current.second.get_moves()) {
            if (!distance.contains(item.first)) {
                distance[item.first] = INT_MAX;
                previous[item.first] = std::make_pair(current.second, item.second);
                set.insert(std::make_pair(distance[item.first], item.first));
            }
            if (distance[item.first] > distance[current.second] ) {
                set.erase(std::make_pair(distance[item.first], item.first));
                distance[item.first] = distance[current.second];
                previous[item.first] = { current.second, item.second };
                set.insert(std::make_pair(distance[item.first] + item.first.distance(), item.first));
            }
        }
    }
    std::string way;
    auto current = previous[end];
    way += current.second;
    while (current.first != start) {
        current = previous[current.first];
        way += current.second;
    }
    std::cout << way.size() << std::endl;
    std::reverse(way.begin(), way.end());
    std::for_each(way.begin(), way.end(), [](char& c) {
        if (c == 'R')
            c = 'L';
        else if (c == 'U')
            c = 'D';
        else if (c == 'L')
            c = 'R';
        else if (c == 'D')
            c = 'U';
    });
    std::cout << way;
}


int main() {
    std::vector<int> arr(FIELD_SIZE);
    for (int i = 0; i < FIELD_SIZE; i++)
        std::cin >> arr[i];
    GameState start_state(arr);
    GameState end_state(FINISH_FIELD);
    A_star(start_state, end_state);
    return 0;
}
