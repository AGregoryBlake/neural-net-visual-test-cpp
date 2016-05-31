#include<algorithm>
#include<random>
#include <vector>
#include <math.h>

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
      std::vector<double> outputs;
      int currentOffset = 0;
      for(int i = 0; i < _nodeLayerSizes.size() - 1; i++) {
        const double* edges = _edges.data() + currentOffset;
        int edgesSize = _nodeLayerSizes[i] * _nodeLayerSizes[i+1];
        outputs = calculateLayerValues(inputs, edges, edgesSize);
        currentOffset += edgesSize;
      }
      return outputs;
    }

    double calculateHighestOutput(std::vector<double>& inputs) {
      
    }

private:
    static std::vector<double> calculateLayerValues(std::vector<double>& inputs, const double* edges, int edgesSize) {
      std::vector<double> edgeGroup;
      int outputSize = edgesSize / inputs.size();
      for(int i = 0; i < outputSize; i++) {
        const double* edgeRange = edges + (i * outputSize);
        edgeGroup.push_back(calculateNodeValue(inputs, edgeRange));
      }
      return edgeGroup;
    }

    static double calculateNodeValue(std::vector<double>& inputs, const double* edges) {
      double d = 0.0;
      for(int i = 0; i < inputs.size(); i++) {
        d += inputs[i] * edges[i];
      }
      return squash(d);
    }

    static double squash(const double& x) {
      return 1 / (1 + exp(-x));
    }
    
    static std::vector<double> edges(const std::vector<int>& nodeLayerSizes) {
      std::random_device rd;
      std::mt19937_64 gen(rd());
      std::uniform_real_distribution<double> random(-8.0,8.0);
      
      int numEdges = 0;
      for(int i = 0; i < nodeLayerSizes.size() - 1; i++) {
        numEdges += nodeLayerSizes[i] * nodeLayerSizes[i+1];
      }
      
      std::vector<double> edges;
      for(int i = 0; i < numEdges; i++) { // should be same size for all the vectors declared at the start of this method.
        edges.push_back(random(gen));
      }
      return edges;      
    }
};