// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Student Name                    Environment : ubuntu:bionic               //
//  Date ......: 2021/02/10                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif
#include <catch/catch.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>
#include <iostream>
#include "color.hpp"
#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include "path.hpp"
#include "path_image.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("True == True", "") { REQUIRE(true == true); }

TEST_CASE("Valid input file") {
    size_t height = 3;
    size_t width = 2;
    ElevationDataset dataset("example-data/ex_input_data/all-tie-row1-2w-3h.dat", width, height);
    REQUIRE(true);
    REQUIRE(dataset.Width() == 2);
    REQUIRE(dataset.Height() == 3);
    REQUIRE(dataset.MinEle() == 7);
    REQUIRE(dataset.MaxEle() == 10);
    REQUIRE(dataset.DatumAt(0, 0) == 9);
    REQUIRE(dataset.DatumAt(0, 1) == 10);
    REQUIRE(dataset.DatumAt(1, 0) == 8);
    REQUIRE(dataset.DatumAt(1, 1) == 10);
    REQUIRE(dataset.DatumAt(2, 0) == 7);
    REQUIRE(dataset.DatumAt(2, 1) == 10);
}

TEST_CASE("dataset file 2") {
    size_t width = 480;
    size_t height = 480;
    ElevationDataset dataset2("example-data/ex_input_data/map-input-w480-h480.dat", width, height);
    REQUIRE(true);
}

TEST_CASE("grayscale image 1") {
    ElevationDataset dataset2("example-data/ex_input_data/map-input-w480-h480.dat", 480, 480);
    GrayscaleImage grayed_image(dataset2);
    const std::vector<std::vector<Color>>& grayed_vect = grayed_image.GetImage();
    Color color = grayed_image.ColorAt(0, 0);

    REQUIRE(true);
}

TEST_CASE("path_image test") {
    size_t width = 5;
    size_t height = 2;
    ElevationDataset dataset2("example-data/ex_input_data/prompt_5w_2h.dat", width, height);
    GrayscaleImage grayscale(dataset2);
    PathImage pathimage(grayscale, dataset2);

    Color kGreen = Color(31,253,13);
    Color kRed = Color(252,25,63);
    pathimage.ToPpm("example-data/ex_output_paths/test.ppm");

    //check outpath folder with corresponding given folder
    const std::vector<std::vector<Color>>& image = pathimage.GetPathImage();

    //comment out these REQUIRES until you have everything compiling
    REQUIRE(image.at(0).at(0).Red() == 252);
    REQUIRE(image.at(0).at(0).Green() == 25);
    REQUIRE(image.at(0).at(0).Blue() == 63);

    REQUIRE(image.at(0).at(1).Red() == 252);
    REQUIRE(image.at(0).at(1).Green() == 25);
    REQUIRE(image.at(0).at(1).Blue() == 63);

    REQUIRE(image.at(1).at(0).Red() == 31);
    REQUIRE(image.at(1).at(0).Green() == 253);
    REQUIRE(image.at(1).at(0).Blue() == 13);

    REQUIRE(image.at(1).at(1).Red() == 31);
    REQUIRE(image.at(1).at(1).Green() == 253);
    REQUIRE(image.at(1).at(1).Blue() == 13);

    REQUIRE(image.at(1).at(2).Red() == 31);
    REQUIRE(image.at(1).at(2).Green() == 253);
    REQUIRE(image.at(1).at(2).Blue() == 13);
}

TEST_CASE("big path_image tests") {
    size_t width = 844;
    size_t height = 480;
    ElevationDataset dataset2("example-data/ex_input_data/map-input-w844-h480.dat", width, height);
    GrayscaleImage grayscale(dataset2);
    PathImage pathimage(grayscale, dataset2);
    
    //CHECK out_paths FOLDER
    pathimage.ToPpm("example-data/ex_output_paths/bigtest.ppm");

    REQUIRE(true == true);
}

TEST_CASE("single row and col") {
    ElevationDataset dataset("example-data/ex_input_data/single-row-col.dat", 1, 1);
    GrayscaleImage grayscale(dataset);
    PathImage pathimage(grayscale, dataset);

    pathimage.ToPpm("example-data/ex_output_paths/singletest.ppm");

    REQUIRE(true == true);
}
/////////////////////////////////////////////////////////////////////////////////////////////