#include "./Node.h"

#include <inttypes.h>         // for uint32_t
#include <stdio.h>            // for FILE *, fread, fseek

#include <unordered_set>      // for std::unordered_set
#include <unordered_map>      // for std::unordered_map

using std::unordered_set;
using std::unordered_map;

namespace rakan {

<<<<<<< HEAD
Node::Node(const uint32_t id,
           const uint32_t county,
           const uint32_t district,
           const uint32_t total_pop,
           const uint32_t majority_pop,
           const uint32_t minority_pop) {
=======
Node:: Node(const uint32_t id,
            const uint32_t county,
            const uint32_t majority_pop,
            const uint32_t minority_pop) {
>>>>>>> ae9b611a0d6e2b2ba6f91bec42949825aeadc171
  neighbors_ = new unordered_set<uint32_t>;
  total_pop_ = majority_pop + minority_pop;
}

bool Node::operator==(const Node& other) const {
  return (this->id_ == other.id_ &&
          this->county_ == other.county_ &&
          this->district_ == other.district_ &&
          this->total_pop_ == other.total_pop_ &&
          this->majority_pop_ == other.majority_pop_ &&
          this->minority_pop_ == other.minority_pop_;
}

bool Node::AddNeighbor(const uint32_t other) {
  this->neighbors_->insert(other);
  return true;
}

}   // namespace rakan
