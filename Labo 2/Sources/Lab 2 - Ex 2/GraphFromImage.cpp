#include "GraphFromImage.h"

namespace ASD2 {

    GraphFromImage::GraphFromImage(const bitmap_image& i) : image(i) {
        /* A IMPLEMENTER */
    }

    /**
     * Return 1 if pixels are the same, 0 o/w.
     * @param x1
     * @param y1
     * @param x2
     * @param y2
     * @return 
     */
    int GraphFromImage::compPixel(int x1, int y1, int x2, int y2) const {
        unsigned char red1;
        unsigned char blue1;
        unsigned char green1;
        unsigned char red2;
        unsigned char blue2;
        unsigned char green2;
        GraphFromImage::image.get_pixel(x1, y1, red1, green1, blue1);
        GraphFromImage::image.get_pixel(x2, y2, red2, green2, blue2);
        if (red1 == red2 && blue1 == blue2 && green1 == green2) {
            return 1;
        }
        return 0;
    }

    GraphFromImage::Iterable GraphFromImage::adjacent(int v) const {
        /* A IMPLEMENTER */
        std::list<int> hello;
        int xValue = x(v);
        int yValue = y(v);
        if (xValue > 0) {
            if (compPixel(xValue, yValue, xValue - 1, yValue) != 0) {
                hello.push_back(idx(xValue - 1, yValue));
            }
        }
        if (yValue > 0) {
            if (compPixel(xValue, yValue, xValue, yValue - 1) != 0) {
                hello.push_back(idx(xValue, yValue - 1));
            }
        }

        if (xValue <= GraphFromImage::image.width() - 1) {
            if (compPixel(xValue, yValue, xValue + 1, yValue) != 0) {
                hello.push_back(idx(xValue + 1, yValue));
            }
        }
        if (yValue <= GraphFromImage::image.height() - 1) {
            if (compPixel(xValue, yValue, xValue, yValue + 1) != 0) {
                hello.push_back(idx(xValue, yValue + 1));
            }
        }

        return hello;
    }

    int GraphFromImage::idx(int x, int y) const {
        /* A IMPLEMENTER */
        return y * GraphFromImage::image.width() + x;
    }

    int GraphFromImage::x(int idx) const {
        /* A IMPLEMENTER */
        return idx % GraphFromImage::image.width();
    }

    int GraphFromImage::y(int idx) const {
        /* A IMPLEMENTER */
        return idx / GraphFromImage::image.width();
    }

    int GraphFromImage::V() const {
        /* A IMPLEMENTER */
        return GraphFromImage::image.width() * GraphFromImage::image.height();
    }

}