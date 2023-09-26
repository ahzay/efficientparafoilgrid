#include "main.h"
#include <omp.h>

using namespace std;

// TODO: optimisation by eliminating deque
/*deque<deque<State>> gen_grid(const Parameters &p, State &s_init) {
    deque<deque<State>> ans(1, deque<State>(1, s_init));
    while (ans.size() <= p.depth) {
        cout << "at depth: " << ans.size() << endl;
        // preallocated
        deque<State> new_states(ans.back().size() * p.us.size(), s_init);
//#pragma omp parallel for
        for (int i = 0; i < ans.back().size(); i++) {
            const auto &s = ans.back()[i];
            int u_count = 0;
            for (const auto &u: p.us) {
                auto new_state = s.gen_next_state(u, ans.size() * p.dt);
                new_states[i * p.us.size() + u_count] = new_state;
                u_count++;
            }
        }
        ans.push_back(new_states);
    }
    return ans;
}*/
deque<deque<State>> gen_grid(const Parameters &p, State &s_init) {
    deque<deque<State>> ans(1, deque<State>(1, s_init));
    while (ans.size() <= p.depth) {
        //cout << "at depth: " << ans.size() << endl;
        // preallocated
        deque<State> new_states;//(ans.back().size() * p.us.size(), s_init);
        for (int i = 0; i < ans.back().size(); i++) {
            const auto &s = ans.back()[i];
            int u_count = 0;
            for (const auto &u: p.us) {
                auto new_state = s.gen_next_state(u, ans.size() * p.dt);
                if (abs(new_state.a.psi_i) < M_PI)
                    new_states.push_back(new_state);
                u_count++;
            }
        }
        ans.push_back(new_states);
    }
    return ans;
}

void run_main(int argc, char *argv[]) {
    CmdLineOptions o(argc, argv);
    int max_threads = omp_get_max_threads();
    std::cout << "Maximum number of threads available for OpenMP: " << max_threads << std::endl;
    cout << "one instance of State takes " << sizeof(State) << endl;
    system("rm *png *gpt");
    Parameters p(o.V, o.dt, o.depth, o.us);
    Attributes a(o.psi_init, 1e-20, 1e-20, 0, 0);
    State s(a, &p);
    auto grid = gen_grid(p, s);
    // add points
    Visualizer v(0, "red");
    for (const auto step: grid)
        for (const auto s: step)
            v.add_state(s);
    v.save();
    // render plots
    system("parallel -j 24 gnuplot {} \">\" {.}.png ::: *.gpt");
}

void run_tests(int argc, char *argv[]) {
    CmdLineOptions o(argc, argv);
    int max_threads = omp_get_max_threads();
    // loop between 0 and max
    int max_timesteps = 70;
    for (int i = 1; i < max_timesteps; i++) {
        //cout << i << ",";
        o.depth = i;
        Parameters p(o.V, o.dt, o.depth, o.us);
        Attributes a(o.psi_init, 1e-20, 1e-20, 0, 0);
        State s(a, &p);
        auto grid = gen_grid(p, s);
        int count=0;
        for (const auto step: grid)
            for (const auto s: step)
                count++;
        cout<<count<<endl;
    }
}

int main(int argc, char *argv[]) {
    //run_main(argc,argv);
    run_tests(argc,argv);
    return 0;
}
