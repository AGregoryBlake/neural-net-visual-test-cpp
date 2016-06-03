#include<algorithm>
#include<random>
#include <vector>
#include <math.h>

class NeuralNetwork {
  public:
    const double _mutationRate;
    const std::vector<int> _nodeLayerSizes;
    const std::vector<int> _edgeLayerSizes;
    std::vector<double> _nodes;
    const std::vector<double> _edges; // weight values grouped by edge group, terminus, origin.
    int _currentNodeOffset;
    int _currentEdgeOffset;
  
    NeuralNetwork(double mutationRate, const std::vector<int> nodeLayerSizes) // Initial Constructor.
      : _mutationRate(mutationRate),
        _nodeLayerSizes(nodeLayerSizes),
        _edgeLayerSizes(edgeLayerSizes(nodeLayerSizes)),
        _nodes(nodes(nodeLayerSizes)),
        _edges(edges(nodeLayerSizes)) {}
    /*
    // TODO: Mutate constructor.
    NeuralNetwork(NeuralNetwork* neural) 
      : _mutationRate(neural->_mutationRate),
        _nodeLayerSizes(neural->_nodeLayerSizes),
        _verticeGroups(mutate(neural->_nodeLayerSizes)) {}

*/
    
    void calculateOutputValues(std::vector<double>& inputs) {
      initializeNetForCalculation(inputs);
      calculateLayers();
    }
    
    std::vector<double> getOutputValues() {
      std::vector<double> outputs;
      for(int i = _nodes.size() - _nodeLayerSizes[_nodeLayerSizes.size() - 1]; i < _nodes.size(); i++) {
        outputs.push_back(_nodes[i]);
      }
      return outputs;
    }

    double calculateHighestOutput() {
      
    }

private:
    void initializeNetForCalculation(const std::vector<double>& inputs) {
      for(int i = 0; i < inputs.size(); i++) {
        _nodes[i] = inputs[i];
      }
      _currentNodeOffset = inputs.size();
      _currentEdgeOffset = 0;
    }
    
    void calculateLayers() {
      for(int i = 0; i < _edgeLayerSizes.size(); i++) {
        int originSize = _nodeLayerSizes[i];
        int terminusSize = _nodeLayerSizes[i+1];
        calculateLayer(originSize, terminusSize);
        _currentNodeOffset += terminusSize;
      }
    }
    
    void calculateLayer(const int& originSize, const int& terminusSize) {
      for(int j = 0; j < terminusSize; j++) {
        calculateNode(originSize, terminusSize, j);
      }
    }
    
    void calculateNode(const int& originSize, const int& terminusSize, const int& currentPlaceInLayer) {
      double d = 0.0;
      for(int k = 0; k < originSize; k++) {
        double edgeValue = _edges[_currentEdgeOffset];
        double nodeValue = _nodes[_currentNodeOffset - originSize + k];
        d += nodeValue * edgeValue;
        _currentEdgeOffset++;
      }
      _nodes[_currentNodeOffset + currentPlaceInLayer] = squash(d);
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
    
    static std::vector<int> edgeLayerSizes(const std::vector<int>& nodeLayerSizes) {
      std::vector<int> edgeLayerSizes;
      for(int i = 0; i < nodeLayerSizes.size() - 1; i++) {
        edgeLayerSizes.push_back(nodeLayerSizes[i] * nodeLayerSizes[i+1]);
      }
      return edgeLayerSizes;
    }
    
    static std::vector<double> nodes(const std::vector<int>& nodeLayerSizes) {
      int numNodes = 0;
      for(int i = 0; i < nodeLayerSizes.size(); i++) {
        numNodes += nodeLayerSizes[i];
      }
      
      std::vector<double> nodes;
      for(int i = 0; i < numNodes; i++) {
        nodes.push_back(0.0);
      }
      return nodes;      
    }
};