//
// Created by David Raleigh on 3/6/22.
//

#ifndef CPP_MAPS_CPP_MAPS_H
#define CPP_MAPS_CPP_MAPS_H

#include <vector>
#include <iterator>
#include <cassert>

class int_map
{
private:
    std::vector<int> m_map;
public:
    int_map(int num_values, int initial_val): m_map(num_values, initial_val) {};
    int get(int index) const { return m_map[index]; };
    void set(int index, int value) { m_map[index] = value;};
};

class rle_int_map
{
    struct run_s
    {
        int m_stop;
        int m_value;
    };

    // The first run implicitly starts at 0; all subsequent runs start at the previous run's m_stop
    std::vector<run_s> m_runs;
    int m_size;

public:
    rle_int_map(int num_values, int initial_val)
    {
        m_runs.push_back({ num_values, initial_val });
        m_size = num_values;
    }

    size_t run_count() { return m_runs.size(); }
    int size() { return m_size; }

    run_s binary_search(int p, int r, int stop, run_s best_run) {
        if (p <= r) {
            int mid = (p + r)/2;
            if (stop == m_runs[mid].m_stop)
                return m_runs[mid];

            run_s test_run = m_runs[mid];
            if (test_run.m_stop > stop && test_run.m_stop < best_run.m_stop)
                best_run = test_run;

            if (stop > m_runs[mid].m_stop)
                return binary_search(mid + 1, r, stop, best_run);
            if (stop < m_runs[mid].m_stop){
                return binary_search(p, mid - 1, stop, best_run);
            }
        }
        return best_run;
    }

    int get(int index)
    {
        // It is illegal to pass in an invalid index, for the purposes of this exercise we can
        // just assert()
        assert(0 <= index && index < m_runs.back().m_stop);

        run_s best_run = binary_search(0, m_runs.size() - 1, index + 1, m_runs[m_runs.size() - 1]);
        return best_run.m_value;

        assert(false); // Shouldn't get here
    }

    void set(int index, int value)
    {
        int previous_stop = 0;
        bool has_prev = false;
        bool has_next = true;
        for (auto ptr = m_runs.begin(); ptr < m_runs.end(); ptr ++)
        {
            if (index < (*ptr).m_stop)
            {
                if ((*ptr).m_value == value)
                    // if value is the same exit
                    return;

                // save the old stop and old value
                int current_stop = (*ptr).m_stop;
                int old_value = (*ptr).m_value;

                if (std::next(ptr) == m_runs.end())
                    // if not last item then has next
                    has_next = false;

                if (index > previous_stop && index < current_stop - 1 && current_stop - previous_stop > 2) {
                    // if in the middle of a range of 3 or more split range twice
                    ptr = m_runs.insert(ptr, {index + 1, value});
                    m_runs.insert(ptr, {index, old_value});
                    // no need to recover space with _clean
                    break;
                } else if (current_stop - previous_stop == 1) {
                    // if the current range only has one item
                    (*ptr).m_value = value;
                } else if (index == previous_stop) {
                    // if the item is at the start of a run
                    ptr = m_runs.insert(ptr, {index + 1, value});
                } else if (index + 1 == current_stop) {
                    // if the item is at the end of a run
                    (*ptr).m_value = value;
                    ptr = std::next(m_runs.insert(ptr, {current_stop - 1, old_value}));
                }

                // try to recover memory
                if (has_prev && std::prev(ptr)->m_value == value) {
                    // if only the previous range has the matching value, then change this range's
                    //   value and remove previous range
                    ptr = m_runs.erase(std::prev(ptr));
                }
                if (has_next && std::next(ptr)->m_value == value) {
                    m_runs.erase(ptr);
                }
                break;
            }
            else
            {
                previous_stop = (*ptr).m_stop;
                has_prev = true;
            }
        }
    }
};


#endif //CPP_MAPS_CPP_MAPS_H
