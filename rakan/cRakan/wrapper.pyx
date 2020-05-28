# distutils: language = c++

from cython.operator import dereference, preincrement, address

from libcpp.vector cimport vector as cvector
from libcpp.string cimport string as cstring

from wrapper cimport Runner as cRunner

import json

cdef class Engine:
    cdef cRunner* _runner
    cpdef int _districts
    cpdef int _precincts
    cpdef cstring _filepath;

    def __cinit__(self, jsonLocation):
        "Create an new engine with the initialization data in the jsonLocation"

        print('mock init')
        
        with open(jsonLocation) as json_file:
            data = json.load(json_file)

        self._districts = data['maxDistricts']
        self._precincts = len(data['precincts'])

        self._runner = new cRunner(self._precincts, self._districts)

    def __dealloc__(self):
        del self._runner

    def _addNode(self, int id, int county, int minorityPopulation, int majorityPoplation):
        dereference(self._runner).add_node(id, county, minorityPopulation, majorityPoplation)
        

    def _addEdge(self, int id1, int id2):
        if not dereference(self._runner).add_edge(id1, id2):
            raise Exception()

    def setDistricts(self, cvector[int] districts):
        print('mock setDistricts')

    def getMaps(self):
        print('mock getMaps')
        return [[self._districts - 1] * self._precincts]

    def getScores(self):
        print('mock getScores')
        return[{'compactness': 0.1, 'vra': 0.8, 'population':0.6, 'political': 0.76}]

    def seed(self):
        print('mock seed')

    def walk(self, int stepsToTake, double alpha, double beta, double gamma, double eta):
        print('mock walk')

    @property
    def districts(self):
        graph = dereference(self._runner).GetGraph()

        districts = []
        for node_id in range(self._precincts):
            district = dereference(graph.GetNode(node_id)).GetDistrict()
            districts.append(district)

        return districts

    def visualize(self, output = "output.jpg"):
        "Creates an image with the file name output"
        raise Exception("Not implemented")


# dereference(self._runner)