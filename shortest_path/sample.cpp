#include <vector>
#include <unordered_map>
#include <queue>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <limits>

using NodeID = unsigned;

template<class CostT>
class Dijkstra
{
public:
	void reset()
	{
		m_nodeSize = 0;
		m_edges.clear();
		m_previousNodes.clear();
	}

	void setNodeSize(size_t nodeSize)
	{
		m_nodeSize = nodeSize;
	}

	void addEdge(NodeID p, NodeID q, const CostT& cost)
	{
		addDirectedEdge(p, q, cost);
		addDirectedEdge(q, p, cost);
	}

	void addDirectedEdge(NodeID from, NodeID to, const CostT& cost)
	{
		m_edges[from].emplace_back(to, cost);
	}

	void buildFrom(NodeID startNode)
	{
		std::vector<std::vector<CostT>> edgeCostMatrix(m_nodeSize, std::vector<CostT>(m_nodeSize, -1.0));
		for(const auto& edge : m_edges)
		{
			const NodeID fromIndex = edge.first;
			const auto& toNodes = edge.second;
			for(const auto& toNode : toNodes)
			{
				const NodeID toIndex = toNode.first;
				const double cost = toNode.second;
				edgeCostMatrix[fromIndex][toIndex] = cost;
			}
		}

		std::priority_queue<std::pair<CostT, NodeID>> nextNodes;
		nextNodes.emplace(CostT(), startNode);

		std::unordered_map<NodeID, CostT> currentCosts;
		currentCosts[startNode] = CostT();

		m_previousNodes.clear();
		m_previousNodes[startNode] = startNode;

		while (!nextNodes.empty())
		{
			const auto currentNode = nextNodes.top();
			nextNodes.pop();

			if (currentCosts.find(currentNode.second) != currentCosts.end() && currentCosts[currentNode.second] < currentNode.first)
			{
				continue;
			}

			const auto& currentEdges = edgeCostMatrix[currentNode.second];
			for (NodeID i = 0; i < m_nodeSize; ++i)
			{
				if (0.0 < currentEdges[i] && (currentCosts.find(i) == currentCosts.end() || (currentNode.first + currentEdges[i] < currentCosts[i])))
				{
					nextNodes.emplace(currentNode.first + currentEdges[i], i);
					currentCosts[i] = currentNode.first + currentEdges[i];
					m_previousNodes[i] = currentNode.second;
				}
			}
		}
	}

	std::deque<NodeID> getPath(NodeID to)const
	{
		const auto it = m_previousNodes.find(to);
		if (it == m_previousNodes.end())
		{
			return {};
		}

		NodeID previousID = to;
		std::deque<NodeID> nodeHistory;
		while (true)
		{
			nodeHistory.push_front(previousID);

			const NodeID newID = m_previousNodes.find(previousID)->second;
			if (previousID == newID)
			{
				break;
			}

			previousID = newID;
		}

		return nodeHistory;
	}

private:
	size_t m_nodeSize;
	std::unordered_map<NodeID, std::vector<std::pair<NodeID, CostT>>> m_edges;

	std::unordered_map<NodeID, NodeID> m_previousNodes;
};

std::deque<unsigned> NearestPath(
  unsigned nodeSize,
  const std::vector<unsigned>& edgeIndices1,
  const std::vector<unsigned>& edgeIndices2,
  const std::vector<double>& edgeDistances,
  unsigned startNode, unsigned goalNode
  )
{
	Dijkstra<double> dijkstra;
	dijkstra.setNodeSize(nodeSize);
	for (size_t i = 0; i < edgeIndices1.size(); ++i)
	{
		dijkstra.addEdge(edgeIndices1[i], edgeIndices2[i], edgeDistances[i]);
	}
	dijkstra.buildFrom(startNode);
	return dijkstra.getPath(goalNode);
}
