#include "natural_merge_sort.h"
#include <fstream>
#include <cctype>

bool natural_less(const std::string& a, const std::string& b) {
    size_t i = 0, j = 0;

    while (i < a.size() && j < b.size()) {
        if (std::isdigit(a[i]) && std::isdigit(b[j])) {
            int num_a = 0, num_b = 0;

            while (i < a.size() && std::isdigit(a[i])) {
                num_a = num_a * 10 + (a[i] - '0');
                i++;
            }

            while (j < b.size() && std::isdigit(b[j])) {
                num_b = num_b * 10 + (b[j] - '0');
                j++;
            }

            if (num_a != num_b) {
                return num_a < num_b;
            }
        }
        else {
            if (std::tolower(a[i]) != std::tolower(b[j])) {
                return std::tolower(a[i]) < std::tolower(b[j]);
            }
            i++; j++;
        }
    }

    return a.size() < b.size();
}

void natural_merge_sort(std::vector<std::string>& arr) {
    size_t n = arr.size();
    if (n <= 1) return;

    {
        std::ofstream f_out("f.txt");
        for (const auto& x : arr) f_out << x << '\n';
    }

    bool sorted = false;
    while (!sorted) {
        sorted = true;

        std::ifstream f_in("f.txt");
        std::ofstream g_out("g.txt");
        std::ofstream h_out("h.txt");

        std::string prev, curr;
        bool to_g = true;
        bool first = true;

        while (std::getline(f_in, curr)) {
            if (!first && natural_less(curr, prev)) {
                to_g = !to_g;
                sorted = false;
            }

            if (to_g) g_out << curr << '\n';
            else h_out << curr << '\n';

            prev = curr;
            first = false;
        }

        f_in.close();
        g_out.close();
        h_out.close();

        if (sorted) break;

        std::ifstream g_in("g.txt");
        std::ifstream h_in("h.txt");
        std::ofstream f_out("f.txt");

        std::string g_line, h_line;
        bool g_has = static_cast<bool>(std::getline(g_in, g_line));
        bool h_has = static_cast<bool>(std::getline(h_in, h_line));

        while (g_has && h_has) {
            if (natural_less(g_line, h_line)) {
                f_out << g_line << '\n';
                if (!std::getline(g_in, g_line)) g_has = false;
            }
            else {
                f_out << h_line << '\n';
                if (!std::getline(h_in, h_line)) h_has = false;
            }
        }

        while (g_has) {
            f_out << g_line << '\n';
            if (!std::getline(g_in, g_line)) break;
        }

        while (h_has) {
            f_out << h_line << '\n';
            if (!std::getline(h_in, h_line)) break;
        }

        g_in.close();
        h_in.close();
        f_out.close();
    }

    std::ifstream result_in("f.txt");
    arr.clear();
    std::string line;
    while (std::getline(result_in, line)) {
        arr.push_back(line);
    }

    std::remove("f.txt");
    std::remove("g.txt");
    std::remove("h.txt");
}