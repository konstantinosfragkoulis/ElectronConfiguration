#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>

struct Subshell {
    int n, l;
    int curElectrons;
    int maxElectrons() const {
        switch(l) {
        case 0: return 2;
        case 1: return 6;
        case 2: return 10;
        case 3: return 14;
        default: return 0;
        }
    }
};

char getSubshellLetter(int l) {
    switch(l) {
    case 0: return 's';
    case 1: return 'p';
    case 2: return 'd';
    case 3: return 'f';
    default: return '?';
    }
}

bool compare(const Subshell& a, const Subshell& b) {
    if(a.n != b.n) return a.n < b.n;
    return a.l < b.l;
}

int main(int argc, char *argv[]) {
    if(argc != 2) {
        printf("Usage: %s <atomic number>\n", argv[0]);
        return 1;
    }

    int z = atoi(argv[1]);
    if(z < 1 || z > 118) {
        printf("Invalid atomic number\n");
        return 1;
    }

    std::vector<Subshell> order = {
        {1, 0, 0}, {2, 0, 0}, {2, 1, 0}, {3, 0, 0}, {3, 1, 0}, 
        {4, 0, 0}, {3, 2, 0}, {4, 1, 0}, {5, 0, 0}, {4, 2, 0},
        {5, 1, 0}, {6, 0, 0}, {4, 3, 0}, {5, 2, 0}, {6, 1, 0},
        {7, 0, 0}, {5, 3, 0}, {6, 2, 0}, {7, 1, 0}
    };

    for(Subshell& s : order) {
        if(z == 0) break;

        s.curElectrons = std::min(s.maxElectrons(), z);
        z -= s.curElectrons;
    }

    for(int i = 0; i < order.size(); ++i) {
        if(order[i].curElectrons == 0) {
            order.erase(order.begin() + i);
            --i;
        }
    }

    std::sort(order.begin(), order.end(), compare);

    for(int i = 0; i < order.size()-1; ++i) {
        if(order[i].curElectrons == 4 && order[i+1].curElectrons == 2) {
            order[i].curElectrons = 5;
            order[i+1].curElectrons = 1;
        } else if(order[i].curElectrons == 9 && order[i+1].curElectrons == 2) {
            order[i].curElectrons = 10;
            order[i+1].curElectrons = 1;
        }
    }

    for(Subshell& s : order) {
        printf("%d%c^%d  ", s.n, getSubshellLetter(s.l), s.curElectrons);
    }
    printf("\n");


    return 0;
}