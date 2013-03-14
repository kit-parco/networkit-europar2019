/*
 * METISGraphReader.cpp
 *
 *  Created on: 17.01.2013
 *      Author: Christian Staudt (christian.staudt@kit.edu)
 */

#include "METISGraphReader.h"

namespace EnsembleClustering {

METISGraphReader::METISGraphReader() {
	// TODO Auto-generated constructor stub

}

METISGraphReader::~METISGraphReader() {
	// TODO Auto-generated destructor stub
}


Graph METISGraphReader::read(std::string path) {

	METISParser parser(path);


	std::pair<int64_t, int64_t> header = parser.getHeader();
	int64_t n = header.first;
	int64_t m = header.second;

	Graph G(n);
	std::string graphName = Aux::StringTools::split(Aux::StringTools::split(path, '/').back(), '.').front();

	G.setName(graphName);

	std::cout << "[BEGIN] reading graph G(n=" << n << ", m=" << m << ") from METIS file: " << std::flush;	// progress bar follows


	double p = 0.0; // percentage for progress bar
	node u = 0; // begin with 0
	while (parser.hasNext()) {
		std::vector<node> adjacencies = parser.getNext();

		for (node v : adjacencies) {
			v = v - 1; 	// METIS-indices are 1-based
			assert (v >= 0);
			if (u <= v) { // self-loops are allowed
			  G.insertEdge(u, v);
			}
		}
		u += 1; // next node
		if ((u % 0x10000) == 0) {
			p = ((double) u / (double) n) * 100;
			std::cout << p << "% " << std::flush;
		}
	}

	// end progress bar
	std::cout << "[DONE]" << std::endl;

	assert (G.numberOfNodes() == n);
	assert (G.numberOfEdges() == m);

	return G;
}

} /* namespace EnsembleClustering */
