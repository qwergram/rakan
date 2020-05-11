#ifndef SRC_RUNNER_H_
#define SRC_RUNNER_H_

#include <bits/stdc++.h>      // for std::unordered_set
#include <inttypes.h>         // for uint32_t
#include <stdio.h>            // for FILE *, fread, fseek
#include <unordered_map>      // for std::unordered_map
#include <utility>            // for std::pair
#include <vector>             // for std::vector

#include "./Graph.h"          // for Graph class
#include "./Node.h"           // for Node class
#include "./Queue.h"

using std::pair;
using std::unordered_set;
using std::unordered_map;

namespace rakan {

class Runner {
 public:
  Runner(Queue &queue) : num_steps_(0), queue_(queue) {}

  uint16_t LoadGraph(FILE *file);

  uint16_t SetDistricts(unordered_map<uint32_t, uint32_t> *map);

  uint16_t SeedDistricts();

  uint16_t PopulateGraphData();

  double ScoreCompactness();

  double ScorePopulationDistribution();

  double ScoreExistingBorders();

  double ScoreVRA();

  double LogScore();

  double MetropolisHastings();

  double MakeMove(Node *node, int new_district_id);

  double Walk(int num_steps);

  Graph *GetGraph() { return graph_; }

 private:
  Queue queue_;
  int num_steps_;
  unordered_map<int, int> *changes_;
  Graph *graph_;
  double score_;
};        // class Runner

}         // namespace rakan

#endif    // SRC_RUNNER_H_
