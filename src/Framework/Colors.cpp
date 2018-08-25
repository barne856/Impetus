#include "Colors.hpp"

bool PROF::Colors::seeded = false;

const float PROF::Colors::red[4] = {0.956f, 0.262f, 0.211f, 1.0f};
const float PROF::Colors::green[4] = {0.298f, 0.686f, 0.313f, 1.0f};
const float PROF::Colors::blue[4] = {0.129f, 0.588f, 0.952f, 1.0f};
const float PROF::Colors::magenta[4] = {1.0f, 0.0f, 1.0f, 1.0f};
const float PROF::Colors::purple[4] = {0.611f, 0.152f, 0.690f, 1.0f};
const float PROF::Colors::indigo[4] = {0.247f, 0.317f, 0.709f, 1.0f};
const float PROF::Colors::orange[4] = {1.0f, 0.596f, 0.0f, 1.0f};
const float PROF::Colors::gray[4] = {0.5f, 0.5f, 0.5f, 1.0f};
const float PROF::Colors::blueGray[4] = {0.376f, 0.490f, 0.545f, 1.0f};
const float PROF::Colors::pink[4] = {0.913f, 0.117f, 0.388f, 1.0f};
const float PROF::Colors::teal[4] = {0.0f, 0.588f, 0.533f, 1.0f};
const float PROF::Colors::brown[4] = {0.474f, 0.333f, 0.282f, 1.0f};
const float PROF::Colors::black[4] = {0.0f, 0.0f, 0.0f, 1.0f};
const float PROF::Colors::white[4] = {1.0f, 1.0f, 1.0f, 1.0f};
const float PROF::Colors::spaceGray[4] = {0.1f, 0.1f, 0.1f, 1.0f};
const float PROF::Colors::cream[4] = {1.0f, 0.992f, 0.815f, 1.0f};
const float PROF::Colors::ivory[4] = {1.0f, 1.0f, 0.941f, 1.0f};
const float PROF::Colors::silver[4] = {0.9f, 0.9f, 0.9f, 1.0f};
const float PROF::Colors::beige[4] = {0.960f, 0.960f, 0.862f, 1.0f};
const float PROF::Colors::gold[4] = {1.0f, 0.843f, 0.0f, 1.0f};
const float PROF::Colors::yellow[4] = {1.0f, 0.921f, 0.231f, 1.0f};
const float PROF::Colors::cyan[4] = {0.0f, 1.0f, 1.0f, 1.0f};
const float PROF::Colors::aquamarine[4] = {0.4f, 0.803f, 0.666f, 1.0f};

const float *PROF::Colors::randomColor()
{
    if (seeded == false)
    {
        srand(time(NULL));
        seeded = true;
    }

    int numberOfColors = 21;

    const float *colorArray[21]{
        red, green, blue, magenta, purple, indigo,
        orange, gray, blueGray, pink, teal, brown,
        black, white, spaceGray, cream, ivory, silver,
        beige, gold, yellow};

    int randNum = rand() % (numberOfColors);

    return colorArray[randNum];
}