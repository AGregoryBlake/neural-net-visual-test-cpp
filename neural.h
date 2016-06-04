#include<algorithm>
#include<random>
#include <vector>
#include <math.h>

class NeuralNetwork {
    private:
        int _currentNodeOffset;
        int _currentEdgeOffset;
        
    public:
        const double _mutationRate;
        const std::vector<int> _nodeLayerSizes;
        const std::vector<int> _edgeLayerSizes;
        std::vector<double> _nodes;
        const std::vector<double> _edges; // weight values grouped by edge group, terminus, origin.
  
        NeuralNetwork(double mutationRate, const std::vector<int> nodeLayerSizes) // Initial Constructor.
            : _mutationRate(mutationRate),
            _nodeLayerSizes(nodeLayerSizes),
            _edgeLayerSizes(edgeLayerSizes(nodeLayerSizes)),
            _nodes(nodes(nodeLayerSizes)),
            _edges(edges(nodeLayerSizes)) {}

        NeuralNetwork(NeuralNetwork* neural) // Mutate constructor.
            : _mutationRate(neural->_mutationRate),
            _nodeLayerSizes(neural->_nodeLayerSizes),
            _edgeLayerSizes(neural->_edgeLayerSizes),
            _nodes(neural->_nodes),
            _edges(mutate(neural->_edges)) {}
    
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
            int numNodes = std::accumulate(nodeLayerSizes.begin(), nodeLayerSizes.end(), 0, std::plus<int>());
            return std::vector<double>(numNodes);
        }
    
        static std::vector<double> mutate(const std::vector<double>& oldEdges) {
            std::random_device rd;
            std::mt19937_64 gen(rd());
            std::uniform_real_distribution<double> randomDouble(-8.0,8.0);
            std::uniform_int_distribution<int> randomInt(0,oldEdges.size() - 1);
      
            int replaceIndex = randomInt(gen);
            std::vector<double> newEdges;
            for(int i = 0; i < oldEdges.size(); i++) {
                int value = i == replaceIndex ? randomDouble(gen) : oldEdges[i];
                newEdges.push_back(value);
            }
            return newEdges;      
        }
};