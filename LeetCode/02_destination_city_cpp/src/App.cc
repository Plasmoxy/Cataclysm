#include "App.h"
#include <iostream>
#include <string>
#include <fmt/format.h>

using namespace std;

class Solution {
public:
    string destCity(vector<vector<string>> paths) {
        for(int i = 0; i < paths.size(); i++){

            int g = 0;
            for(int x = 0; x < paths.size(); x++){
                printf("paths[%d] last = paths[%d] first -> %d\n", i, x, paths[i][1] == paths[x][0]);

                if(paths[i][1] == paths[x][0]){
                    g++;
                }
            }
            if(g == 0){return paths[i][1];}
        }
        return "nic";
    }
};

int main(int argc, char* argv[]) {
	
    vector<vector<string>> test {{"London","New York"}, {"New York","Lima"}, {"Lima","Sao Paulo"}
    };

    cout << ("test size = %d\n", test.size());

    cout << Solution().destCity(test) << endl;

	return 0;
}