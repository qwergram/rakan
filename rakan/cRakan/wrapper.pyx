# distutils: language = c++

from cython.operator import dereference, preincrement, address

from libcpp.vector cimport vector as cvector
from libcpp.string cimport string as cstring
from libc.stdint cimport uint32_t as cuint32_t

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

        self._districts = data['numDistricts']
        self._precincts = data['numPrecincts']

        self._runner = new cRunner(self._precincts, self._districts)
        
        # first pass to add all nodes
        for prec in data['precincts']:
            self._addNode(prec['precID'], prec['county'], prec['minPopulation'], prec['majPopulation'])
        
        #second pass to add all edges
        edgesFrom = set()
        for prec in data['precincts']:
            for neighbor in prec['neighbors']:
                if neighbor not in edgesFrom:
                    self._addEdge(prec['precID'], neighbor)
                
            edgesFrom.add(prec['precID'])

    def __dealloc__(self):
        del self._runner

    def _addNode(self, int id, int county, int minorityPopulation, int majorityPoplation):
        print('mock addNode')
        print(id, county, minorityPopulation, majorityPoplation)
        dereference(self._runner).add_node(id, county, minorityPopulation, majorityPoplation);

    def _addEdge(self, int id1, int id2):
        print('mock addEdge')
        dereference(self._runner).add_edge(id1, id2)

    def setDistricts(self, cvector[cuint32_t] districts):
        print('mock setDistricts')
        dereference(self._runner).set_districts(districts)

    def getMaps(self):
        print('mock getMaps')
        return [[self._districts - 1] * self._precincts]
        dereference(self._runner).getMaps()

    def getScores(self):
        print('mock getScores')
        return[{'compactness': 0.1, 'vra': 0.8, 'population':0.6, 'political': 0.76}]
        dereference(self._runner).getScores()

    def seed(self):
        print('mock seed')
        return dereference(self._runner).seed()

    def walk(self, int stepsToTake, double alpha, double beta, double gamma, double eta):
        print('mock walk')
        return dereference(self._runner).Walk(stepsToTake, alpha, beta, gamma, eta)

    @property
    def districts(self):
        return self._districts[:]

    def visualize(self, output = "output.jpg"):
        "Creates an image with the file name output"
        raise Exception("Not implemented")


# dereference(self._runner)