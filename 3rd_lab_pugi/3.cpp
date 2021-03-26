#include <iostream>
#include "pugixml.hpp"
#include <string>
#include <map>

using namespace std;

typedef map<string, int> msi;

class Route66 {
private:
    msi vehicles_routes;
    int max_route = -1;
    string max_stops_street;
    string vehicle_type;
    double max_way = -1;
public:
    Route66(string vehicle) {
        this->vehicle_type = vehicle;
    }
    void parse() {
        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load_file("data123.xml");
        if (!result) {
            cout << "Parse error, loaded wrong file" << endl;
        }
        // dataset
        pugi::xml_node tool = doc.first_child();
        map<string, int> mapping;
        // i love it very much
        mapping["type_of_vehicle"] = 1;
        mapping["object_type"] = 2;
        mapping["name_stopping"] = 3;
        mapping["the_official_name"] = 5;
        mapping["location"] = 6;
        mapping["routes"] = 7;
        mapping["coordinates"] = 8;
        // all <transport_station> 
        for (pugi::xml_node tool1 = tool.first_child(); tool1; tool1 = tool1.next_sibling()) {
            string vehicle;
            // cout << tool1.name() << endl;
            // going through all childs of <transport_station>
            for (pugi::xml_node tool2 = tool1.first_child(); tool2; tool2 = tool2.next_sibling()) {
                string name = tool2.name();
                string value = tool2.child_value();
                // cout <<  value <<  endl;
                switch (mapping[name]) {
                case 1:
                    vehicle = tool2.child_value();
                    // cout << vehicle << endl;
                    break;
                case 7:
                    if (vehicle == vehicle_type) {
                        string temp_value;
                        for (int i = 0; i < value.size(); i++) {
                            char ch = value[i];                            
                                switch (ch) {
                                case('.'):
                                    vehicles_routes[temp_value]++;
                                    temp_value = "";
                                    break;
                                case(','):
                                    vehicles_routes[temp_value]++;
                                    temp_value = "";
                                    break;
                                default:
                                    temp_value += ch;
                                    break;
                                }
                            }                       
                        if (temp_value != "") {
                            vehicles_routes[temp_value]++;
                        }
                    }
                    break;
                }
            }
        }

    }

    void print_all_routes() {
        for (msi::iterator it = vehicles_routes.begin(); it != vehicles_routes.end(); ++it) {
            std::cout << "Route number " << it->first  << ' '<< "Number of stops" << ' ' << it->second << std::endl;
        }
    }

    void max_stops() {
        for (msi::iterator it = vehicles_routes.begin(); it != vehicles_routes.end(); ++it) {
            if (it->second > max_route) {
                this->max_route = it->second;
                this->max_stops_street = it->first;
            }
        }
        cout << "Route "   << max_stops_street << " "<< "Number of stops " << max_route << std::endl;
    }

};

int main() {
    
    string bus = "Bus";
    string trolleybus = "Trolleybus";
    string tram = "Tram";
    Route66 route(trolleybus);
    route.parse();
    route.print_all_routes();
    cout << endl;
    route.max_stops();
    return 0;
}
