#include "../include/glm/glm.hpp"
#include "../include/Camera.h"
#include "../include/ColorRGB.h"
#include <vector>
#include <iostream>
#include <fstream>

int main() {
	Camera camera{ 600, 600 };

	// öppna textfil för skrivning av linjer skannade
	std::ofstream logFile("../log.txt"); 

	for (int i = 0; i < camera.GetWidth(); i++) {	

		// För debugging enbart
		if (logFile.is_open()){
			std::clog.rdbuf(logFile.rdbuf());
			std::clog << "\rScanlines remaining: " << (camera.GetHeight() - i) << ' ' << std::flush; 
			
		} else {
        	std::cerr << "Kunde inte öppna loggfilen." << std::endl;
    	}
		// ---------------------

		for (int j = 0; j < camera.GetHeight(); j++) {
			auto r = double(i) / (camera.GetWidth()-1);
            auto g = double(j) / (camera.GetHeight()-1);
            auto b = 0;

			int ir = static_cast<int>(255.999 * r);
			int ig = static_cast<int>(255.999 * g);
			int ib = static_cast<int>(255.999 * b);

			camera.pixels[i][j] = ColorRGB(ir, ig, ib);

		}
	}

	// För debugging enbart
	std::clog << "\rDone.                 \n";
	logFile.close();
	//---------------------

	camera.saveImage("../test.ppm",
		camera.GetWidth(), camera.GetHeight(), camera.pixels);
}
