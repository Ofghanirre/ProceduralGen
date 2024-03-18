// Worley Noise implementation
/*
 * This Noise is often use to generate clouds or cell-like patterns
 * due to the slow algorithms, this noise is pre-generated before usages
 *
 */

#include "../inc/Worley_noise.hpp"


Worley_noise::Worley_noise(int minRange, int maxRange) : _minRange(minRange), _maxRange(maxRange){};
Worley_noise::Worley_noise(){};



std::vector<std::vector<int>> Worley_noise::worley_noise(size_t seed, size_t width, size_t height, size_t gridSize) const{

    /*
     * 1 : Naive
     * 2 : BFS approach (flawed)
     * 3 : Check 2x the gridSize
     * 4 : Check only the 9 nearest points (best)
     */
    int algo_choice = 4;

    // Init a 2D Vector with zeros
    int height_padding = (height%gridSize);
    int width_padding = width%gridSize;
    std::vector<std::vector<float>> pixels(height+height_padding, std::vector<float>(width+width_padding, gridSize*2));
    std::vector<std::vector<int>> pixels_int(height, std::vector<int>(width, 0));
    std::vector<std::vector<bool>> visited(height, std::vector<bool>(width, false));

    // Init random generators
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distrib_width(0, gridSize);
    std::uniform_int_distribution<int> distrib_height(0, gridSize);

    // Generate random points in grid
    std::vector<vec2<float>> points;
    std::queue<int> toVisitQueue;
    for (int gridX = 0; gridX < height+height_padding - gridSize+1; gridX+= gridSize) {

    for (int gridY = 0; gridY < width+width_padding - gridSize+1; gridY+= gridSize) {
            int x = distrib_height(generator);
            int y = distrib_width(generator);
            points.emplace_back(static_cast<float>(x+gridX),static_cast<float>(y+gridY));
            toVisitQueue.emplace((x+gridX)*height+y+gridY);
            visited[x][y] = true;
        }
    }
    float max = 0;

    int newX, newY;
    float dist;
    float minDist = distance(points[0], {static_cast<float>(0), static_cast<float>(0)});


    // For BFS
    int x_offset = 1, y_offset = 1;
    int next_iter_countdown = points.size();
    int nb_visited_this_iter = 0;
    std::vector<vec2<int>> directions_x = {{-1, 0},
                                           {1,  0}};
    std::vector<vec2<int>> directions_y = {{0, 1},
                                           {0, -1}};
    std::vector<vec2<int>> directions_xy = {{-1, -1},
                                            {1,  -1},
                                            {-1, 1},
                                            {1,  1}};

    switch (algo_choice) {
        case 1 :
            // NAIVE
            for (int x = 0; x < height; x++) {
                for (int y = 0; y < width; y++) {
                    // Find closest point
                    float dist;
                    float minDist = distance(points[0], {static_cast<float>(x), static_cast<float>(y)});;
                    for (int i = 1; i < points.size(); i++) {
                        dist = distance(points[i], {static_cast<float>(x), static_cast<float>(y)});
                        minDist = dist < minDist ? dist : minDist;
                    }

                    pixels[x][y] = minDist;
                    if (max < minDist) {
                        max = minDist;
                    }
                }
            }
            break;
        case 2 :
            // Calculate distance BFS, not working


            while (!toVisitQueue.empty()) {
                int currentIndex = toVisitQueue.front();
                int currentPoint_x = currentIndex / height;
                int currentPoint_y = currentIndex % height;
                //std::cout << "sike "<<  currentPoint_x << "----" << currentPoint_y<< std::endl;
                toVisitQueue.pop();

                dist = sqrt(x_offset * x_offset + y_offset * y_offset);
                //std::cout << distance << std::endl;

                pixels[currentPoint_x][currentPoint_y] = dist;
                //visited.emplace(currentPoint_x*height+currentPoint_y);

                for (const vec2<int> &offset: directions_x) {
                    newX = currentPoint_x + offset.x;
                    if (0 <= newX && newX < height && (!visited[newX][currentPoint_y])) {
                        toVisitQueue.emplace(newX * height + currentPoint_y);
                        nb_visited_this_iter++;
                        visited[newX][currentPoint_y] = true;
                    }
                }


                for (const vec2<int> &offset: directions_y) {
                    newY = currentPoint_y + offset.y;
                    if (0 <= newY && newY < width && (!visited[currentPoint_x][newY])) {
                        toVisitQueue.emplace(currentPoint_x * height + newY);
                        nb_visited_this_iter++;
                        visited[currentPoint_x][newY] = true;
                    }
                }

                for (const vec2<int> &offset: directions_xy) {
                    newX = currentPoint_x + offset.x;
                    newY = currentPoint_y + offset.y;
                    if (0 <= newX && newX < height && 0 <= newY && newY < width && (!visited[newX][newY])) {
                        toVisitQueue.emplace(newX * height + newY);
                        nb_visited_this_iter++;
                        visited[newX][newY] = true;
                    }
                }
                next_iter_countdown--;
                if (next_iter_countdown == 0) {
                    next_iter_countdown = nb_visited_this_iter;
                    nb_visited_this_iter = 0;
                    x_offset += 1;
                    y_offset += 1;
                }
                //std::cout << toVisitQueue.size() << "----" << visited.size()<< std::endl;
            }
            max = dist;
            break;

        case 3 :
            // Calculate DIstance  2/ freq2

            for (int i = 0; i < points.size(); i++) {
                for (int x = -gridSize; x <= gridSize; x++) {
                    for (int y = (int) -gridSize; y <= gridSize; y++) {
                        newX = x + points[i].x;
                        newY = y + points[i].y;
                        if (0 <= newX && newX < height && 0 <= newY && newY < width) {
                            dist = distance(points[i], {static_cast<float>(newX), static_cast<float>(newY)});
                            if (dist < pixels[newX][newY]) {
                                minDist = dist;
                                pixels[newX][newY] = minDist;
                            }
                        }
                    }
                }
                if (max < minDist) {
                    max = minDist;
                }
            }
            break;

        case 4 :
            // Calculate DIstance  3/ 9 nearest points
            int nbPointsWidth = (width + width_padding) / gridSize;
            int nbPointsHeight = (height + height_padding) / gridSize;
            int pointIndex = 0;

            int gridX, gridY;
            for (int x = 0; x < height; x++) {
                for (int y = 0; y < width; y++) {

                    gridX = x / gridSize;
                    gridY = y / gridSize;

                    minDist = gridSize * 2;

                    //std::cout << x << "----" << y <<std::endl;

                    //std::cout << gridX << "<---->" << gridY <<std::endl;
                    // Search the minDist through the 9 nearest points
                    for (int xOffset = -1; xOffset < 2; xOffset++) {
                        for (int yOffset = -1; yOffset < 2; yOffset++) {

                            pointIndex = (gridX + xOffset) * nbPointsHeight + (gridY + yOffset);

                            if (0 <= gridX && gridX <= nbPointsHeight && 0 <= gridY && gridY <= nbPointsWidth) {
                                //std::cout << pointIndex <<std::endl;
                                dist = distance(points[pointIndex], {static_cast<float>(x), static_cast<float>(y)});
                                minDist = dist < minDist ? dist : minDist;
                            }
                        }
                    }
                    pixels[x][y] = minDist;
                    if (max < minDist) {
                        max = minDist;
                    }

                }
            }
            // -----------------
            break;
    }









    /*
    for (int x = 0; x < height; x++) {
        for (int y = 0; y < width; y++) {
            // Find closest point
            float dist;
            float minDist = distance(points[0], {static_cast<float>(x), static_cast<float>(y)});;
            for (int i = 1; i < points.size(); i++) {
                dist = distance(points[i], {static_cast<float>(x), static_cast<float>(y)});
                minDist = dist < minDist ? dist : minDist;
            }

            pixels[x][y] = minDist;
            if (max < minDist) {
                max = minDist;
            }
        }
    }*/

    // Normalization scale
    float new_range = _maxRange - _minRange;

    for (int x = 0; x < height; x++) {
        for (int y = 0; y < width; y++) {
            // Fill the new BitMap object
            //bitmap[x*width+y]
            pixels_int[x][y] = (pixels[x][y] / max * new_range + _minRange );
        }
    }
    return pixels_int;


}

Noise Worley_noise::genNoise(size_t seed, size_t width, size_t height, size_t frequency) const {
    BitMap<int> bitmap(width,height, worley_noise(seed, width, height, frequency));
    return Noise(bitmap, seed, width, height, frequency);

}

void Worley_noise::test(size_t width, size_t height, size_t seed, size_t gridSize, size_t minRange, size_t maxRange) {
    //Worley_noise::test(24,8,5,7,5,10);
    std::cout << "Worley noise test" << std::endl;
    Worley_noise worleyNoiseGenerator = Worley_noise(minRange,maxRange);
    Noise worleyNoise = worleyNoiseGenerator.genNoise(seed, width, height, gridSize);
    BitMap img = worleyNoise.getBitmap();

    for (int x = 0; x < height; x++) {
        for (int y = 0; y < width; y++) {
            std::cout << img.get(y,x)<< "\t";
        }
        std::cout << std::endl;
    }
    std::vector<std::unique_ptr<INoiseGenerator>> genVector;
    genVector.emplace_back(std::make_unique<Worley_noise>(minRange,maxRange));

    for (const auto &noise_gen: genVector) {
        Noise testNoise = noise_gen->genNoise(seed, width, height, gridSize);
        std::cout << "Height " << testNoise.getHeight() << std::endl;
        std::cout << "Width " << testNoise.getWidth() << std::endl;
    }
}
