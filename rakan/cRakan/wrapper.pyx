# distutils: language = c++

from cython.operator import dereference, preincrement, address

from libcpp.vector cimport vector as cvector

from wrapper cimport Runner as cRunner
from wrapper cimport Graph as cGraph

cdef class Engine:
    cdef cRunner* _runner
    cdef cGraph* _graph
    cpdef int districts
    cpdef int precincts

    def __cinit__(self, int districts, int precincts):
        print('mock init')
        self._runner = new cRunner()
        self.districts = districts
        self.precincts = precincts

    def __dealloc__(self):
        del self._runner

    def addNode(self, int id, int county, int minorityPopulation, int majorityPoplation):
        print('mock addNode')
        print(id, county, minorityPopulation, majorityPoplation)

    def addEdge(self, int id1, int id2):
        print('mock addEdge')

    def setDistricts(self, cvector[int] districts):
        print('mock setDistricts')

    def getMaps(self):
        print('mock getMaps')
        return [[self.districts - 1] * self.precincts]

    def getScores(self):
        print('mock getScores')
        return[{'compactness': 0.1, 'vra': 0.8, 'population':0.6, 'political': 0.76}]

    def seed(self):
        print('mock seed')

    def walk(int stepsToTake, double alpha, double beta, double gamma, double eta):
        print('mock walk')

# dereference(self._runner)