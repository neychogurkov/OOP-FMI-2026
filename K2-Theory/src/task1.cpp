#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

using namespace std;

struct Tracer {
    int id;

    Tracer(int i) : id(i) {
        cout << "C" << id << ' ';
    }

    ~Tracer() {
        cout << "D" << id << ' ';
    }
};

int main() {
    vector<shared_ptr<Tracer>> v;

    v.push_back(make_shared<Tracer>(1));
    v.push_back(make_shared<Tracer>(2));
    v.push_back(v[0]);

    cout << v[0].use_count() << ' ';

    erase_if(v, [](const auto& p) {
        return p.use_count() == 2 && p->id % 2 == 1;
    });

    cout << v.size() << ' ';

    sort(v.begin(), v.end(),
        [](const auto& a, const auto& b) {
            return a->id > b->id;
        });

    if (!v.empty())
        cout << v.front()->id << ' ';
}