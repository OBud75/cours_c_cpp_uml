#include "registration/services.hpp"
#include "location/services.hpp"
#include "database/services.hpp"
#include "database/data_mappers.hpp"

#include <iostream>
#include <cstdlib>
#include <string>
#include <queue>
#include <map>

using namespace std;


int solve_travelling_salesman_problem();
int encryption();
int create_path_in_graph();
int banking();
int labyrinth();


int main(int argc, char const *argv[]) {
    auto reset_db = "python3 database/repositories/reset.py";
    if (argc == 1) {
        solve_travelling_salesman_problem();
        encryption();
        create_path_in_graph();
        banking();
        labyrinth();

        system(reset_db);
        return 0;
    }

    if (argc != 2) {
        cout << "Please provide a function name as an argument.\n";
        return 1;
    }

    map<string, int(*)()> functions;
    functions["solve_travelling_salesman_problem"] = &solve_travelling_salesman_problem;
    functions["encryption"] = &encryption;
    functions["create_path_in_graph"] = &create_path_in_graph;
    functions["banking"] = &banking;
    functions["labyrinth"] = &labyrinth;

    try {
        functions.at(argv[1])();
    } catch (const out_of_range&) {
        cout << "Unknown function name.\n";
        return 1;
    }
    system(reset_db);
    return 0;
}



int solve_travelling_salesman_problem() {
    srand(time(nullptr));
    vector<Location> locations;
    for (int i(0); i < 6; ++i) {
        int x = rand() % 251;
        int y = rand() % 251;
        locations.push_back(Location(x, y));
    }
    auto best_tour = make_best_tour(&locations);
    cout << "Min dist : " << best_tour.distance() << endl;
    return 0;
}


string db_path = "database/repositories/";
map<string, string> repositories = {
    {"users", "users.txt"},
    {"worlds", "worlds.txt"}
};


int encryption() {
    auto data_mapper = make_data_mapper(db_path, repositories);

    auto world = make_world(100);
    auto user = make_user(world.get());

    string raw_password = "toto123";
    user->set_password(raw_password);
    user->log_in(raw_password);
    cout << "Check 1: " << user->is_logged_in() << endl;

    user->log_out();
    cout << "Check 2: " << user->is_logged_in() << endl;
    user->save(*data_mapper);

    string raw_password2 = "wrong password";
    user->log_in(raw_password2);
    cout << "Check 3: " << user->is_logged_in() << endl;

    auto refreshed_from_db = get_user(*data_mapper, user->id());
    cout << refreshed_from_db->password() << endl;
    refreshed_from_db->log_out();
    string password_from_db = "que";
    refreshed_from_db->log_in(password_from_db);
    cout << "Check 4: " << refreshed_from_db->is_logged_in() << endl;
    return 0;
}


int create_path_in_graph() {
    class create_path_in_graph {
        public:
            create_path_in_graph():
                world_id(1), latitude(10), longitude(10), user_count(5) {
                    auto data_mapper = make_data_mapper(db_path, repositories);
                    load_data();

                    auto world = get_world(*data_mapper, world_id);
                    world->bind_locations();

                    for (auto i(1); i <= user_count; ++i) {
                        to_visit.push(get_user(*data_mapper, i));
                    }

                    player = make_user(world.get());
                    while (not to_visit.empty()) {
                        move_player();
                        to_visit.pop();
                    }
                }

        private:
            int world_id;
            int latitude;
            int longitude;
            int user_count;
            unique_ptr<User> player;
            queue<unique_ptr<User>> to_visit;

            void load_data() {
                auto command = (
                    "python3 database/repositories/load_data.py "
                    + to_string(world_id) + " "
                    + to_string(latitude) + " "
                    + to_string(longitude) + " "
                    + to_string(user_count)
                );
                system(command.c_str());
            }

            void move_player() {
                auto user = move(to_visit.front());
                auto next_location = user->location();
                auto next_lat = next_location->latitude();
                auto next_long = next_location->longitude();

                while (not (player->location() == next_location)) {
                    // ici on compare les pointeurs
                    // si dans WorldMapper::get on enlève le fait
                    // d'aller rechercher l'instance, le pointeur
                    // va changer malgré le fait qu'on créé exactement
                    // le même world depuis la DB
                    // si on compare les objets avec l'ajout de
                    // Location::operator== alors on compare les valeurs
                    auto player_lat = player->location()->latitude();
                    auto player_long = player->location()->longitude();

                    if (player_lat > next_lat) {
                        player->move(User::LEFT);
                    }
                    else if (player_lat < next_lat) {
                        player->move(User::RIGHT);
                    }
                    else if (player_long < next_long) {
                        player->move(User::DOWN);
                    }
                    else if (player_long > next_long) {
                        player->move(User::UP);
                    }
                }
            }
    };
    create_path_in_graph();
    return 0;
}


int banking() {
    return 0;
}


int labyrinth() {
    auto mapper = make_labyrinth_block_mapper(
        db_path, map<string, string>{{"maze", "maze.txt"}}
    );
    auto maze = make_unique<Labyrinth>(move(*mapper));
    return 0;
}
