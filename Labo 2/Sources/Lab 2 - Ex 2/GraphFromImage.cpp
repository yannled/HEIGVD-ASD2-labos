#include "GraphFromImage.h"

namespace ASD2 {

    /**
     * Constructor of a GraphFromImage object.
     * @param i the bitmap image reference
     */
    GraphFromImage::GraphFromImage(const bitmap_image& i) : image(i) {
        /* nothing to do: the reference to the image is already stored */
    }

    /**
     * Private method that returns 1 if two pixels are the same color, 0 o/w.
     * 
     * Two pixels are considered the same if their red, green and blue
     * composants are exactly the same.
     * 
     * This method is used to factorize code and avoid duplication.
     * 
     * @param x1 the x coord of the first pixel
     * @param y1 the y coord of the first pixel
     * @param x2 the x coord of the second pixel
     * @param y2 the y coord of the second pixel
     * @return 1 if same pixel, 0 o/w
     */
    int GraphFromImage::comparePixelColor(int x1, int y1, int x2, int y2) const {
        // pixel 1 colors RGB
        unsigned char red1;
        unsigned char green1;
        unsigned char blue1;
        // pixel 2 colors RGB
        unsigned char red2;
        unsigned char green2;
        unsigned char blue2;
        GraphFromImage::image.get_pixel(x1, y1, red1, green1, blue1);
        GraphFromImage::image.get_pixel(x2, y2, red2, green2, blue2);
        if (red1 == red2 && blue1 == blue2 && green1 == green2) {
            return 1;
        }
        return 0;
    }

    /**
     * Returns the adjacent edges of the edge v, that are the same color.
     * @param v the index of an edge
     * @return the neighbors of v that are the same color
     */
    GraphFromImage::Iterable GraphFromImage::adjacent(int v) const {
        /* the iterable that will be returned, list of indexes */
        std::list<int> neighborsAdjacentSameColor;

        // x/y coordinates of the current pixel
        int xValue = x(v);
        int yValue = y(v);

        // x/y coordinates of the neighbor pixel
        int xNeighbor = xValue;
        int yNeighbor = yValue;

        /* for each neighbor (left, right, up, down), we check if we are
         * on the border. Then we check if the color is the same, 
         * and if so we add the index of the neighbor to the returned neighbors
         */

        // LEFT
        // if x is bigger than 0, we look at its predecessor (x-1)
        if (xValue > 0) {
            xNeighbor = xValue - 1;
            if (comparePixelColor(xValue, yValue, xNeighbor, yNeighbor) != 0) {
                neighborsAdjacentSameColor.push_back(idx(xNeighbor, yNeighbor));
            }
            xNeighbor = xValue;
        }

        // UP
        // if x is bigger than 0, we look at its predecessor (y-1)
        if (yValue > 0) {
            yNeighbor = yValue - 1;
            if (comparePixelColor(xValue, yValue, xNeighbor, yNeighbor) != 0) {
                neighborsAdjacentSameColor.push_back(idx(xNeighbor, yNeighbor));
            }
            yNeighbor = yValue;
        }

        // RIGHT
        // if x is not on the right side, we look at its successor (x+1)
        if (xValue <= GraphFromImage::image.width() - 1) {
            xNeighbor = xValue + 1;
            if (comparePixelColor(xValue, yValue, xNeighbor, yNeighbor) != 0) {
                neighborsAdjacentSameColor.push_back(idx(xNeighbor, yNeighbor));
            }
            xNeighbor = xValue;
        }

        // DOWN
        // if y is not on the border down side, we look at its successor (y+1)
        if (yValue <= GraphFromImage::image.height() - 1) {
            yNeighbor = yValue + 1;
            if (comparePixelColor(xValue, yValue, xNeighbor, yNeighbor) != 0) {
                neighborsAdjacentSameColor.push_back(idx(xNeighbor, yNeighbor));
            }
            yNeighbor = yValue;
        }

        return neighborsAdjacentSameColor;
    }

    /**
     * Returns the index of a pixel given by its x/y coordinate.
     * 
     * It's calculated as the width times the y coordinate (height used), 
     * plus the x coordinate (width used).
     * @param x the x coordinate
     * @param y the y coordinate
     * @return the index of the pixel (y * width + x)
     */
    int GraphFromImage::idx(int x, int y) const {
        /* y x width + x */
        return y * GraphFromImage::image.width() + x;
    }

    /**
     * Returns the x coordinate of the pixel denoted by its index.
     * 
     * It's calculated as the modulo of the index by the width.
     * (remaining number of the last line)
     * @param idx the index of the pixel
     * @return its x coordinate.
     */
    int GraphFromImage::x(int idx) const {
        /* modulo integer division */
        return idx % GraphFromImage::image.width();
    }

    /**
     * Returns the y coordinate of the pixel denoted by its index.
     * 
     * It's calculated as the integer division of the index by the width.
     * (number of line)
     * @param idx the index of the pixel
     * @return its y coordinate.
     */
    int GraphFromImage::y(int idx) const {
        /* integer division without the remainer  */
        return idx / GraphFromImage::image.width();
    }

    /**
     * Return the number of pixels, defined as the width times the height.
     * @return the size of the image.
     */
    int GraphFromImage::V() const {
        /* size = width x height */
        return GraphFromImage::image.width() * GraphFromImage::image.height();
    }

}