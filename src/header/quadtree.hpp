#ifndef QUADTREE_H
#define QUADTREE_H

#include <functional>
#include <vector>
#include <cstdint>
#include <string>

using namespace std;

/** Represents an image.*/
struct Image {
    uint8_t* data;  /* Image data. */
    int width;      /* Image width. */
    int height;     /* Image height. */
    int channels;   /* Number of channels. */
    string type;    /* Filetype of the image */
  };

/* Represents a region inside the image */
struct Region {
    int x, y;               /* Coordinates of the region's top-left corner. */
    int width;              /* Width of the region. */
    int height;             /* Height of the region. */
    long long pixel_count;  /* Amount of pixels within a region */
};

/**
 * @brief Represents a node in the Quadtree.
 *
 * Each node corresponds to a rectangular region of the image.
 */
class Quadtree {
    public:
        Region region;                   /* Region of this quadtree instance */
        vector<uint8_t> mean_color; /* Mean color of the pixels in the region. */
        bool isLeaf;                     /* Indicates if the node is a leaf (no children). */
        Quadtree* children[4];           /* Pointers to the four child nodes (NW, NE, SW, SE). */
    
        /**
         * @brief Constructor for the Quadtree node.
         *
         * @param x      X-coordinate of the region's top-left corner.
         * @param y      Y-coordinate of the region's top-left corner.
         * @param width  Width of the region.
         * @param height Height of the region.
         */
        Quadtree(int x, int y, int width, int height);
    
        /**
         * @brief Destructor for the Quadtree node.
         *
         * Recursively deletes all child nodes to prevent memory leaks.
         */
        ~Quadtree();

        /**
         * @brief Calculates the mean color of a region in the image.
         *
         * @param img    Image data.
         * @param region Region to calculate the mean color for.
         * @return       Vector representing the mean color (e.g., RGB).
         */
        vector<uint8_t> calculate_mean_color(const Image& img, const Region& region);

        /**
        * @brief Builds the Quadtree recursively.
        *
        * @param img         Image data.
        * @param min_block   Minimum size of a region.
        * @param threshold   Tolerance for color variance.
        * @param error_func  Function to calculate the error.
        */
        void build(const Image& img, int min_block, double threshold, function<double(const Image&, const Region&, const vector<uint8_t>&)> error_func);

        /**
        * @brief Draws the compressed image based on the Quadtree, the image data is modified into the compressed data.
        *
        * @param img Image data to modify.
        */
        void draw(Image& img);
        };

#endif
