#include<algorithm>
#include<random>
#include <vector>

class NeuralNetwork {
  public:
    const double _mutationRate;
    const std::vector<int> _nodeLayerSizes;
    const std::vector<std::vector<std::vector<double>>> _verticeGroups; // weight values grouped by vertice group, terminus, origin.
  
    NeuralNetwork(double mutationRate, const std::vector<int> nodeLayerSizes) // Initial Constructor.
      : _mutationRate(mutationRate),
        _nodeLayerSizes(nodeLayerSizes),
        _verticeGroups(verticeGroups(nodeLayerSizes)) {}
    /*
    // TODO: Mutate constructor.
    NeuralNetwork(NeuralNetwork* neural) 
      : _mutationRate(neural->_mutationRate),
        _nodeLayerSizes(neural->_nodeLayerSizes),
        _verticeGroups(mutate(neural->_nodeLayerSizes)) {}
    */
    
    /* TODO: 
    std::vector<double> calculateOutputValues(std::vector<double> inputs) {
    
    }
    */
    
    /* TODO: 
    double calculateHighestOutput(std::vector<double> inputs) {
    
    }
    */
    
private:
    /* TODO:
    static std::vector<double> calculateLayerValues(std::vector<double> inputs, std::vector<std::vector<double>> verticeGroup) {
    
    }
    */
    
    static std::vector<std::vector<std::vector<double>>> verticeGroups(const std::vector<int>& nodeLayerSizes) {
      std::vector<int> originLayerSizes(nodeLayerSizes.begin(), nodeLayerSizes.end() -1);
      std::vector<int> terminusLayerSizes(nodeLayerSizes.begin() + 1, nodeLayerSizes.end());
      std::vector<int> numVerticesByLayer;

      std::random_device rd;
      std::mt19937_64 gen(rd());
      std::uniform_real_distribution<double> random(-8.0,8.0);
      
      for(int i = 0; i < originLayerSizes.size(); i++) { // zip the origins and termini together to determine the size of each node layer.
        numVerticesByLayer.push_back(originLayerSizes[i] * terminusLayerSizes[i]);
      }
      
      std::vector<std::vector<std::vector<double>>> verticeGroups;
      for(unsigned long i = 0; i < originLayerSizes.size(); i++) { // should be same size for all the vectors declared at the start of this method.
        std::vector<std::vector<double>> verticeGroup;
        for(int j = 0; j < numVerticesByLayer[i]; j++) {
          std::vector<double> verticesByOrigin;
          for(int k = 0; k < originLayerSizes[i]; k++) {
            verticesByOrigin.push_back(random(gen));
          }
          verticeGroup.push_back(verticesByOrigin);
        }
        verticeGroups.push_back(verticeGroup);
      }
      return verticeGroups;
      
    }
};