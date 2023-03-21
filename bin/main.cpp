#include <iostream>
#include <fstream>
#include <sstream>

#include "lib/graphSolver.h"

//graph of Europe
std::stringstream europe("Albania: Macedonia, Montenegro, Serbia\n"
                      "Andorra: France, Spain\n"
                      "Austria: Czechia, Germany, Hungary, Italy, Liechtenstein, Slovakia, Slovenia, Switzerland\n"
                      "Belarus: Latvia, Lithuania, Poland, Russia, Ukraine\n"
                      "Belgium: France, Germany, Luxembourg, Netherlands\n"
                      "Bosnia: Croatia, Montenegro, Serbia\n"
                      "Bulgaria: Greece, Macedonia, Romania, Serbia, Turkey\n"
                      "Croatia: Bosnia, Hungary, Montenegro, Serbia, Slovenia\n"
                      "Czechia: Austria, Germany, Poland, Slovakia\n"
                      "Denmark: Germany\n"
                      "Estonia: Latvia, Russia\n"
                      "Finland: Norway, Sweden, Russia\n"
                      "France: Andorra, Belgium, Germany, Italy, Luxembourg, Monaco, Spain, Switzerland\n"
                      "Germany: Austria, Belgium, Czechia, Denmark, France, Luxembourg, Netherlands, Poland, Switzerland\n"
                      "Greece: Albania, Bulgaria, Macedonia, Turkey\n"
                      "Hungary: Austria, Croatia, Romania, Serbia, Slovakia, Slovenia, Ukraine\n"
                      "Italy: Austria, France, San Marino, Slovenia, Switzerland, Vatican\n"
                      "Latvia: Belarus, Estonia, Lithuania, Russia\n"
                      "Liechtenstein: Austria, Switzerland\n"
                      "Lithuania: Belarus, Latvia, Poland, Russia\n"
                      "Luxembourg: Belgium, France, Germany\n"
                      "Macedonia: Albania, Bulgaria, Greece, Serbia\n"
                      "Moldova: Romania, Ukraine\n"
                      "Monaco: France\n"
                      "Montenegro: Albania, Bosnia, Croatia, Serbia\n"
                      "Netherlands: Belgium, Germany\n"
                      "Norway: Finland, Russia, Sweden\n"
                      "Poland: Belarus, Czechia, Germany, Lithuania, Russia, Slovakia, Ukraine\n"
                      "Portugal: Spain\n"
                      "Romania: Bulgaria, Hungary, Moldova, Serbia, Ukraine\n"
                      "Russia: Belarus, Estonia, Finland, Latvia, Lithuania, Norway, Ukraine, Poland\n"
                      "San Marino: Italy\n"
                      "Serbia: Albania, Bosnia, Bulgaria, Croatia, Hungary, Montenegro, Macedonia, Romania\n"
                      "Slovakia: Austria, Czechia, Hungary, Poland, Ukraine\n"
                      "Slovenia: Austria, Croatia, Hungary, Italy\n"
                      "Spain: Andorra, France, Portugal\n"
                      "Sweden: Finland, Norway\n"
                      "Switzerland: Austria, France, Germany, Italy, Liechtenstein\n"
                      "Turkey: Bulgaria, Greece\n"
                      "Ukraine: Belarus, Hungary, Moldova, Poland, Romania, Russia, Slovakia\n"
                      "Vatican: Italy");

//graph of weighted Europe
std::map<std::string, std::vector<std::pair<std::string, int>>> distances = {
        {"Albania", {{"Montenegro", 160}, {"Serbia", 456}, {"Macedonia", 333}, {"Greece", 856}}},
        {"Andorra", {{"Spain", 615}, {"France", 861}}},
        {"Austria", {{"Germany", 681}, {"Czechia", 334}, {"Slovakia", 80}, {"Hungary", 243}, {"Slovenia", 384},
                            {"Italy", 1122}, {"Liechtenstein", 650}, {"Switzerland", 840}}},
        {"Belarus", {{"Russia", 714}, {"Ukraine", 528}, {"Poland", 553}, {"Lithuania", 183}, {"Latvia", 480}}},
        {"Belgium", {{"France", 312}, {"Luxembourg", 204}, {"Netherlands", 210}, {"Germany", 757}}},
        {"Bosnia", {{"Croatia", 400}, {"Serbia", 292}, {"Montenegro", 230}}},
        {"Bulgaria", {{"Turkey", 1000}, {"Greece", 793}, {"Macedonia", 242}, {"Serbia", 400}, {"Romania", 383}}},
        {"Croatia", {{"Slovenia", 140}, {"Hungary", 300}, {"Serbia", 393}, {"Bosnia", 400}, {"Montenegro", 713}}},
        {"Czechia", {{"Germany", 350}, {"Poland", 637}, {"Slovakia", 329}, {"Austria", 334}}},
        {"Denmark", {{"Germany", 439}}},
        {"Estonia", {{"Latvia", 309}, {"Russia", 1025}}},
        {"Finland", {{"Russia", 1088}, {"Sweden", 524}, {"Norway", 1020}}},
        {"France", {{"Spain", 1276}, {"Andorra", 861}, {"Monaco", 958}, {"Italy", 1420}, {"Switzerland", 571},
                            {"Luxembourg", 373}, {"Belgium", 312}, {"Germany", 1054}}},
        {"Germany",
                {{"Denmark", 439}, {"Netherlands", 656}, {"Luxembourg", 740}, {"Switzerland", 955}, {"Austria", 681},
                            {"Czechia", 350}, {"Poland", 574}, {"Belgium", 757}, {"France", 1054}}},
        {"Greece", {{"Albania", 856}, {"Macedonia", 696}, {"Bulgaria", 793}, {"Turkey", 1546}}},
        {"Hungary", {{"Romania", 837}, {"Serbia", 380}, {"Croatia", 300}, {"Slovenia", 462}, {"Austria", 243},
                            {"Slovakia", 201}, {"Ukraine", 1116}}},
        {"Italy",
                {{"Switzerland", 924}, {"France", 1420}, {"Austria", 1122}, {"Slovenia", 753}, {"San Marino", 313},
                            {"Vatican", 5}}},
        {"Latvia", {{"Lithuania", 295}, {"Estonia", 309}, {"Belarus", 480}, {"Russia", 920}}},
        {"Liechtenstein", {{"Switzerland", 231}, {"Austria", 650}}},
        {"Lithuania", {{"Belarus", 183}, {"Poland", 523}, {"Latvia", 295}, {"Russia", 943}}},
        {"Luxembourg", {{"France", 373}, {"Belgium", 204}, {"Germany", 740}}},
        {"Macedonia", {{"Bulgaria", 242}, {"Serbia", 432}, {"Albania", 333}, {"Greece", 696}}},
        {"Moldova", {{"Romania", 490}, {"Ukraine", 470}}},
        {"Monaco", {{"France", 958}}},
        {"Montenegro", {{"Croatia", 713}, {"Bosnia", 230}, {"Serbia", 456}, {"Albania", 160}}},
        {"Netherlands", {{"Belgium", 210}, {"Germany", 656}}},
        {"Norway", {{"Russia", 2100}, {"Sweden", 522}, {"Finland", 1020}}},
        {"Poland", {{"Lithuania", 523}, {"Belarus", 553}, {"Ukraine", 816}, {"Slovakia", 661}, {"Czechia", 637},
                            {"Germany", 574}, {"Russia", 1260}}},
        {"Portugal", {{"Spain", 624}}},
        {"Romania", {{"Moldova", 490}, {"Ukraine", 919}, {"Bulgaria", 771}, {"Serbia", 596}, {"Hungary", 837}}},
        {"Russia", {{"Estonia", 1025}, {"Latvia", 920}, {"Lithuania", 943}, {"Poland", 1260}, {"Belarus", 714},
                            {"Ukraine", 862}, {"Finland", 1088}, {"Norway", 2100}}},
        {"San Marino", {{"Italy", 313}}},
        {"Serbia", {{"Hungary", 380}, {"Romania", 596}, {"Bulgaria", 400}, {"Macedonia", 432}, {"Albania", 456},
                            {"Montenegro", 456}, {"Bosnia", 292}, {"Croatia", 393}}},
        {"Slovakia", {{"Poland", 661}, {"Ukraine", 1326}, {"Hungary", 201}, {"Austria", 80}, {"Czechia", 329}}},
        {"Slovenia", {{"Austria", 384}, {"Italy", 753}, {"Croatia", 140}, {"Hungary", 462}}},
        {"Spain", {{"Portugal", 624}, {"Andorra", 615}, {"France", 1276}}},
        {"Sweden", {{"Norway", 522}, {"Finland", 524}}},
        {
         "Switzerland", {{"Germany",       955},
                            {"France",        571},
                            {"Liechtenstein", 231},
                            {"Austria",       840},
                            {"Italy",         924}}
        },
        {
         "Turkey", {{"Bulgaria", 1000},
                            {"Greece",   1546}}
        },
        {
         "Ukraine", {{"Moldova",  470},
                            {"Romania",  919},
                            {"Hungary",  1116},
                            {"Slovakia", 1326},
                            {"Poland",   816},
                            {"Belarus",  528},
                            {"Russia",   862}}
        },
        { "Vatican", {{"Italy", 5}}},
};

int main() {
//graph initializing
////-----------------/////
    graphSolver g;

    europe >> g;
////-----------------////

/// Task b) find radius(g), diameter(g), center(g)

//    auto [country, radius] = g.FindRadius();
//    std::cout << "Country : " << country << " radius : " << radius << '\n';
//
//    auto diameter = g.FindDiameter();
//    std::cout << "Country : " << diameter.first << " diameter : " << diameter.second << '\n';
//
//    auto center = g.FindCenter();
//    std::cout << "Center : ";
//    for (const auto& node : center) {
//        std::cout << node << " ";
//    }
//
//    std::cout << '\n';

///Task e) Find maximum clique

//    auto max_clique = g.Bronkerbosch();
//
//    std::cout << "Max clique: ";
//    for (auto x : max_clique) std::cout << x << " ";
//
//    g.Bronkerbosch();
//
//    for (auto [from, edges] : g.matching_vertex_to_edges) {
//        std :: cout << "From : " << from << '\n';
//        for (auto x : edges) {
//            for (auto y : x) {
//                std :: cout << y << " ";
//            }
//            std::cout << '\n';
//        }
//    }

///Task f) Find maximum stable set

//    auto maximum_stable_set = g.FindMaximumStableSet();
//    std::cout << "\nmaximum stable set : \n";
//    for (const auto& x : maximum_stable_set) {
//        std::cout << x << " ";
//    }

/// Task g) Find maximum matching

//    g.FindMaximumMatching();

/// Task h) Find minimum vertex cover
//    auto minimum_vertex_cover = g.FindMinimumVertexCover();
//
//    std::cout << "Minimum vertex cover : \n";
//    for (auto x : minimum_vertex_cover) {
//        std::cout << x << ' ';
//    }

/// Task k) Find the closed walk U that visits every edges

//    std::stringstream reduced_europe("Albania: Macedonia, Montenegro, Serbia\n"
//                                 "Andorra: France, Spain\n"
//                                 "Austria: Czechia, Germany, Hungary, Italy, Liechtenstein, Slovenia\n"
//                                 "Belarus: Latvia, Lithuania, Russia, Ukraine\n"
//                                 "Belgium: France, Germany, Luxembourg, Netherlands\n"
//                                 "Bosnia: Montenegro, Serbia\n"
//                                 "Bulgaria: Greece, Macedonia, Serbia, Turkey\n"
//                                 "Croatia: Hungary, Montenegro, Serbia, Slovenia\n"
//                                 "Czechia: Austria, Germany, Poland, Slovakia\n"
//                                 "Denmark:\n"
//                                 "Estonia: Latvia, Russia\n"
//                                 "Finland: Sweden, Russia\n"
//                                 "France: Andorra, Belgium, Germany, Italy, Spain, Switzerland\n"
//                                 "Germany: Austria, Belgium, Czechia, France, Luxembourg, Netherlands, Poland, Switzerland\n"
//                                 "Greece: Albania, Bulgaria, Macedonia, Turkey\n"
//                                 "Hungary: Austria, Croatia, Romania, Serbia, Slovakia, Slovenia\n"
//                                 "Italy: Austria, France, Slovenia, Switzerland\n"
//                                 "Latvia: Belarus, Estonia, Lithuania, Russia\n"
//                                 "Liechtenstein: Austria, Switzerland\n"
//                                 "Lithuania: Belarus, Latvia, Poland, Russia\n"
//                                 "Luxembourg: Belgium, Germany\n"
//                                 "Macedonia: Albania, Bulgaria, Greece, Serbia\n"
//                                 "Moldova: Romania, Ukraine\n"
//                                 "Monaco: \n"
//                                 "Montenegro: Albania, Bosnia, Croatia, Serbia\n"
//                                 "Netherlands: Belgium, Germany\n"
//                                 "Norway: Russia, Sweden\n"
//                                 "Poland: Czechia, Germany, Lithuania, Russia, Slovakia, Ukraine\n"
//                                 "Portugal: \n"
//                                 "Romania: Hungary, Moldova, Serbia, Ukraine\n"
//                                 "Russia: Belarus, Estonia, Finland, Latvia, Lithuania, Norway, Ukraine, Poland\n"
//                                 "San Marino: \n"
//                                 "Serbia: Albania, Bosnia, Bulgaria, Croatia, Hungary, Montenegro, Macedonia, Romania\n"
//                                 "Slovakia: Czechia, Hungary, Poland, Ukraine\n"
//                                 "Slovenia: Austria, Croatia, Hungary, Italy\n"
//                                 "Spain: Andorra, France\n"
//                                 "Sweden: Finland, Norway\n"
//                                 "Switzerland: France, Germany, Italy, Liechtenstein\n"
//                                 "Turkey: Bulgaria, Greece\n"
//                                 "Ukraine: Belarus, Moldova, Poland, Romania, Russia, Slovakia\n"
//                                 "Vatican: ");
//
//    graphSolver reduced_g;
//    reduced_europe >> reduced_g;
//
//    reduced_g.FindEulerPath();

/// Task n) Add the weight functionw : E → R denoting the distanc between capitals. Find the minimum
//(w.r.t. the total weight of edges) spanning tree T for the largest connected component of the
//weighted Europe graph G
//∗
//Gw = (V , E,w).
//
//    spanningTree minimum_spanning_tree = g.FindMinimumSpanningTree(distances);
//
//    size_t length_of_spanning_tree = 0;
//
//    for (auto dist : minimum_spanning_tree) {
//        length_of_spanning_tree += dist.second;
//    }
//    std::cout << "Sum of edges in minimum spanning tree : " << length_of_spanning_tree << '\n';
//
//    for (auto [connected, cost] : minimum_spanning_tree) {
//        std::cout << connected.first << " " << connected.second << " " << cost << '\n';
//    }

/// Task o) Find centroid(T ) (w.r.t. the edge weight function w).

    auto T = g.FindMinimumSpanningTree(distances);

    auto centroid = g.FindCentroid(T);

    std::cout << "Founded centroid : " << centroid.first << " " << centroid.second << '\n';

/// Task p) Construct the Prufer code for  ̈ T.

    std::string prufer_code = g.PruferCode(T);

    std::cout << "Constructed the Prufer code : " << std::endl;

    std::cout << prufer_code;
}



