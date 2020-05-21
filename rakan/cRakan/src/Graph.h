#ifndef SRC_GRAPH_H_
#define SRC_GRAPH_H_

#include <inttypes.h>       // for uint32_t
#include <stdio.h>          // for FILE *

#include <unordered_set>    // for std::unordered_set
#include <vector>           // for std::vector
#include <map>           // for std::map

#include "./Edge.h"         // for Edge class

using std::unordered_set;
using std::unordered_map;
using std::vector;

namespace rakan {

class Graph {
 public:

  /////////////////////////////////////////////////////////////////////////////
  // Constructors and destructors
  /////////////////////////////////////////////////////////////////////////////

  /*
  * Default constructor. Used ONLY for testing.
  */
  Graph() = default;

  /*
  * Supplies the number of precincts and districts on this graph. Number of precincts,
  * districts, and state population must be non-negative.
  * 
  * @param    num_precincts       the number of precincts on this graph, must be >= 0
  * @param    num_districts   the number of districts on this graph, must
  *                           be >= 0
  */
 Graph(const uint32_t num_precincts,
       const uint32_t num_districts,
       const uint32_t state_pop);

  /*
  * Default destructor. Also destructs precincts on this graph.
  */
  ~Graph();

  /////////////////////////////////////////////////////////////////////////////
  // Graph mutators
  /////////////////////////////////////////////////////////////////////////////

  /*
  * Adds a precinct to this graph. Assumes that the precinct is new.
  * 
  * @param    county                the county this precinct belongs to.
  * @param    minority_population   the min. pop for this precinct. 
  * @param    majority_population   the maj. pop for this precinct.
  * 
  * 
  */
  void AddPrecinct(uint32_t county, uint32_t minority_population, uint32_t majority_population);

  /*
  * Adds an edge between the two supplied precincts. If either precinct does not
  * exist, adds precincts before adding edge.
  * 
  * @param    precinct1    the neighbor of precinct2
  * @param    precinct2    the neighbor of precinct1
  * 
  * @return true iff adding edge successful, false otherwise
  */
  bool AddEdge(uint32_t precinct1, uint32_t precinct2);

  /*
  * Adds to the state population.
  * 
  * @param    val   the value to add to the state population
  */
  void AddStatePop(uint32_t val) { state_pop_ += val; } 

  /*
  * Updates precinct to be inside of the district. Also updates district's
  * population data
  * 
  * @param      precinct        the precinct to add
  * @param      district    the district to add the precinct to
  * 
  * @return true iff precinct does not already belong in district and addition
  *         successful, false otherwise
  */
  bool AddPrecinctToDistrict(uint32_t precinct, uint32_t district);

  /*
  * Removes the given precinct from the given district. Precinct must exist in district
  * before removal. Updates the population and demographics of the district
  * accordingly. Precinct will belong to a non-existent district afterwards.
  * 
  * @param      precinct_id        the precinct to remove
  * @param      district    the district to remove precinct from
  * 
  * @return true iff precinct exists in district and removal successful, false
  *         otherwise
  */
  bool SetPrecinctToDistrict(uint32_t precinct_id, uint32_t district);


  /////////////////////////////////////////////////////////////////////////////
  // Queries
  /////////////////////////////////////////////////////////////////////////////

  /*
  * Queries whether or not the precinct exists in the graph.
  * 
  * @param    precinct    the precinct to test for existence
  * 
  * @return true iff the precinct exists in the graph, false otherwise
  */
  bool ContainsPrecinct(uint32_t precinct) const { return precinct < curr_precincts_; }

  /*
  * Queries whether or not an edge exists between the two precincts.
  * 
  * @param    precinct1   the first precinct to test for an edge relationship
  * @param    precinct2   the second precinct to test for an edge relationship
  * 
  * @return true iff the precincts exist and an edge exists between them, false
  *         otherwise
  */
  bool ContainsEdge(uint32_t precinct1, uint32_t precinct2) const; 

  /*
  * Queries whether or not the precinct exists in the district.
  * 
  * @param    precinct        the precinct id to test for existence
  * @param    district    the district to test whether it contains precinct
  * 
  * @return true iff the precinct exists on the graph and is in distric, false
  *         otherwise
  */
  bool PrecinctExistsInDistrict(uint32_t precinct, uint32_t district) const;


  /////////////////////////////////////////////////////////////////////////////
  // Accessors
  /////////////////////////////////////////////////////////////////////////////

  /*
  * Gets the county number for this precinct.
  * Assumes that the precinct exists!
  * 
  * @param    id    the id of the precinct to get
  * 
  * @return the county number
  */
  uint32_t GetPrecinctCounty(const uint32_t id) const { return precinct_info[id][0]; }

  /*
  * Gets the minority population number for this precinct.
  * Assumes that the precinct exists!
  * 
  * @param    id    the id of the precinct to get
  * 
  * @return the minority population number
  */
  uint32_t GetPrecinctMin(const uint32_t id) const { return precinct_info[id][1]; }

  /*
  * Gets the majority population number for this precinct.
  * Assumes that the precinct exists!
  * 
  * @param    id    the id of the precinct to get
  * 
  * @return the majority population number
  */
  uint32_t GetPrecinctMaj(const uint32_t id) const { return precinct_info[id][2]; }

  /*
  * Gets the number of precincts on this graph.
  * 
  * @return the number of precincts on this graph as an unsigned 32-bit int
  */
  uint32_t GetNumPrecincts() const { return num_precincts_ ;} 

  /*
  * Gets the number of districts on this graph.
  * 
  * @return the number of districts on this graph as an unsigned 32-bit int
  */
  uint32_t GetNumDistricts() const { return num_districts_; }

  /*
  * Gets the state population of this graph.
  * 
  * @return the state population of this graph as an unsigned 32-bit int
  */
  uint32_t GetStatePop() const { return state_pop_; }

  /*
  * Gets the set of precincts in the given district.
  * 
  * @param    district      the district to get the precincts from
  * 
  * @return a pointer to the set of precincts in the district; nullptr if the
  *         district does not exist
  */
  unordered_set<uint32_t>* GetPrecinctsInDistrict(const uint32_t district) const { 
    if(district < num_districts_) { return precincts_in_district_[district]; } 
    else { return nullptr; }
  }

  /*
  * Returns a set of all of the edges that are crossing district boundaries.
  * Returns as a const variable.
  */
  const unordered_set<Edge>* GetCrossingEdges() const 
    { return const_cast <unordered_set<Edge>*> (&edges_crossing_); }

  /*
  * Gets the total population of the given district.
  * 
  * @param    district    the district to get the total population of
  * 
  * @return the total population of the given district; 0 if the district
  *         does not exist
  */
  uint32_t GetDistrictPop(const uint32_t district) const {
    if(district < num_districts_) { return pop_of_district_[district]; } 
    else { return 0; }
  }

  /*
  * Gets the total minority population of the given district.
  * 
  * @param    district    the district to get the total minority population from.
  * 
  * @return the total minority population of the given district; 0 if the
  *         district does not exist
  */
  uint32_t GetMinorityPop(const uint32_t district) const {
    if(district < num_districts_) { return pop_of_district_[district]; } 
    else { return 0; }
  }

  /*
  * Gets the edges crossing into other districts for this district.
  * 
  * @param    district    the district to get the edges from.
  * 
  * @return A vector containing the edges crossing into other districts.
  */
  vector<Edge> GetOutgoing(uint32_t district) const { return outgoing_edges_.at(district) ; }

 private:
  // The intended total precincts in this graph.
  uint32_t num_precincts_;

  // The precincts in the graph so far.
  uint32_t curr_precincts_;

  // The number of districts on this graph.
  uint32_t num_districts_;

  // The total state population of this graph.
  uint32_t state_pop_;

  // An array of pointers to sets. The index of the array
  // is the district ID, and the pointer at the index points
  // to a set of precinct ids in that district.
  unordered_set<uint32_t> **precincts_in_district_;

  // A set of edges that cross a district boundary in the graph.
  unordered_set<Edge> edges_crossing_;
  
  // An array of arrays, with the index of the overall array referring to the
  // precinct id and the array at each index containing:
  // 0 : The county number
  // 1 : The minority pop number
  // 2 : The majority pop number
  // for that certain precinct.
  uint32_t** precinct_info;

  // An array of populations. The index of the array is the district
  // ID. The value at that index corresponds to the population in
  // that district.
  uint32_t *pop_of_district_;

  // An array of minority populations. The index of the array is
  // the district ID. The value at that index corresponds to the
  // minority population in that district.
  uint32_t *min_pop_of_district_;

  // An array of array of Edges. The index of the general array
  // corresponds to the precinct id, and the array at each index is
  // all of the edges associated to that id.
  Edge** all_edges_;

  unordered_map<uint32_t, vector<Edge>> outgoing_edges_;

  // Needed for populating data structures in graph from file.
  friend class Runner;
};        // class Graph

}         // namespace rakan

#endif    // SRC_GRAPH_H_
