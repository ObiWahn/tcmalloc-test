#include <iostream>
#include <fstream>
#include <vector>

#ifdef TC
#include <tcmalloc/malloc_extension.h>
#endif

#ifdef TC2
#include <gperftools/malloc_extension.h>
#endif

int main() {
    std::vector<std::vector<int>> res;

    for(std::size_t i = 0; i<= 10000000; i++) {
        res.push_back(std::vector<int>(100));
    }
    res.clear();

    for(std::size_t i = 0; i<= 1000000; i++) {
        res.push_back(std::vector<int>(1000));
    }
    res.clear();

    for(std::size_t i = 0; i<= 100000; i++) {
        res.push_back(std::vector<int>(10000));
    }
    res.clear();
#ifdef TC
    std::ofstream out("./stats.dump");
    out << tcmalloc::MallocExtension::GetStats();
#endif

#ifdef TC2
    std::string data;
    MallocExtension::instance()->GetHeapSample(&data);
    std::ofstream out("./stats.dump2");
    out << data;

    std::cout << "To make this work you need to:\n"
              << "  export TCMALLOC_SAMPLE_PARAMETER=524288 (or some other value)\n"
              << "Then you can inspect the dump with:\n"
              << "  pprof -http localhost:5000 stats.dump2\n"
              << "after running this executable";

#endif
    std::cout << "\n";
    return 0;
}
