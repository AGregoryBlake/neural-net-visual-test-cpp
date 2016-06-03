#include<algorithm>
#include<random>
#include <vector>
#include <math.h>

// Stupid windows workaround since std::random_device()
// doesn't work right on Windows and poor BradPerson
// is currently stuck on a Windows dev environment.
// We'll use the current time to seed the random
// entropy generator instead.
#include <time.h>

class NeuralNetwork {
  public:
    const double _mutationRate;
    const std::vector<int> _nodeLayerSizes;
    const std::vector<double> _edges; // weight values grouped by edge group, terminus, origin.
  
    NeuralNetwork(double mutationRate, const std::vector<int> nodeLayerSizes) // Initial Constructor.
      : _mutationRate(mutationRate),
        _nodeLayerSizes(nodeLayerSizes),
        _edges(edges(nodeLayerSizes)) {}
    /*
    // TODO: Mutate constructor.
    NeuralNetwork(NeuralNetwork* neural) 
      : _mutationRate(neural->_mutationRate),
        _nodeLayerSizes(neural->_nodeLayerSizes),
        _verticeGroups(mutate(neural->_nodeLayerSizes)) {}

*/
    // int *start_addr = my_vector.get() + some_calculated_offset;
    std::vector<double> calculateOutputValues(std::vector<double>& inputs) {
      std::vector<double> *current_input_layer = &inputs;
      std::vector<double> outputs;
      int currentOffset = 0;
      for(int i = 0; i < _nodeLayerSizes.size() - 1; i++) {
        const double* edges = _edges.data() + currentOffset;
        int edgesSize = _nodeLayerSizes[i] * _nodeLayerSizes[i+1];
        outputs = calculateLayerValues(*current_input_layer, edges, edgesSize);
        currentOffset += edgesSize;
        current_input_layer = &outputs;
      }
      return outputs;
    }

    double calculateHighestOutput(std::vector<double>& inputs) {
      
    }

private:
    static std::vector<double> calculateLayerValues(std::vector<double>& inputs, const double* edges, int edgesSize) {
      std::vector<double> outputs;
      int outputSize = edgesSize / inputs.size();
      for(int i = 0; i < outputSize; i++) {
        const double* edgeRange_start = edges + (i * inputs.size());
        outputs.push_back(calculateNodeValue(inputs, edgeRange_start));
      }
      return outputs;
    }

    static double calculateNodeValue(std::vector<double>& inputs, const double* edges) {
      double d = 0.0;
      for(int i = 0; i < inputs.size(); i++) {
        d += inputs[i] * edges[i];
      }
      return squash(d);
    }

    static double squash(const double x) {
      if( x < -10.0 ) return 0.0;
      if( x >  10.0 ) return 1.0;

      // Changed int constants to doubles.
      // '1' is an int, '1.0' is a double, '1.0f' is a float
      return 1.0 / (1.0 + exp(-x));
    }
    
    static std::vector<double> edges(const std::vector<int>& nodeLayerSizes) {
      std::random_device rd;
      //std::mt19937_64 gen(rd());
      std::mt19937_64 gen(time(NULL));
      std::uniform_real_distribution<double> random(-8.0,8.0);
      
      int numEdges = 0;
      for(int i = 0; i < nodeLayerSizes.size() - 1; i++) {
        numEdges += nodeLayerSizes[i] * nodeLayerSizes[i+1];
      }

      // Renamed variable 'edges' to 'random_edges' since it's not good
      // ettiquite... ettiquate... it's not good C++ manners!
      std::vector<double> random_edges;
      for(int i = 0; i < numEdges; i++) { // should be same size for all the vectors declared at the start of this method.
        random_edges.push_back(random(gen));
      }
      return random_edges;
    }
};