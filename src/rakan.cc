#include <stdlib.h>
#include <iostream>

#include "./Graph.h"
#include "./Node.h"
#include "./Reader.h"
#include "./Runner.h"

#include "./Queue.h"

using rakan::Runner;

using battledance::Queue;
using battledance::Task;
using std::cout;
using std::cerr;
using std::endl;

void print_seeding(Graph *g) {
  unordered_set<int> *set;
  for (int i = 0; i < g->GetNumDistricts(); i++) {
    cout << "district " << i << " = [";
    set = g->GetNodesInDistrict(i);
    for (auto& id : *set) {
      cout << id << ", ";
    }
    cout << "]" << endl;
  }
}

int main(int argc, char *argv[]) {
  if (argc != 7) {
    cerr << "usage: " << argv[0] << " filepath alpha beta gamma eta num_steps" << endl;
  }

  FILE *file = fopen(argv[1], "rb");
  Queue queue("amqp://guest:guest@bladecaller_queue", "rakan");

  Runner runner(queue);
  runner.LoadGraph(file);
  runner.SeedDistricts();
  runner.PopulateGraphData();
  // print_seeding(runner.GetGraph());

  Graph *g = runner.GetGraph();
  g->SetAlpha(atof(argv[2]));
  g->SetBeta(atof(argv[3]));
  g->SetGamma(atof(argv[4]));
  g->SetEta(atof(argv[5]));

  int i = 0;
  while (i < atoi(argv[6])) {
    cout << "step " << i << endl;
    cout << "score = " << runner.Walk(1) << endl;
    i++;
  }

  return EXIT_SUCCESS;
}
